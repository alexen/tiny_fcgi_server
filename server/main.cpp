/// @file
/// @brief
/// @copyright Copyright (c) InfoTeCS. All Rights Reserved.

#include <array>
#include <string_view>
#include <stdexcept>
#include <iostream>

#include <boost/core/ignore_unused.hpp>
#include <boost/exception/diagnostic_information.hpp>
#include <boost/exception/error_info.hpp>

#include <fcgiapp.h>
#include <fcgio.h>


#define THROW_EXCEPTION_IF( cond, msg, exc ) \
     do { if( cond ){ BOOST_THROW_EXCEPTION( exc{ msg } ); } } while( false )

#define THROW_RUNTIME_ERROR_IF( cond, msg ) \
     THROW_EXCEPTION_IF( cond, msg, std::runtime_error )


struct Exception : std::runtime_error, virtual boost::exception
{
     Exception( const std::string& what ) : std::runtime_error{ what } {}
};

using Details = boost::error_info< struct Details_, std::string >;


class Environment
{
public:
     struct Error : Exception {
          Error( const std::string& what )
               : Exception{ what } {} };
     struct NoKeyFound : Error{
          NoKeyFound( std::string_view key )
               : Error{ "no key " + std::string{ key } + " found" } {} };

     using KeyValue = std::unordered_map< std::string_view, std::string_view >;

     explicit Environment( const FCGX_Request& request )
     {
          parse( request.envp );
     }

     KeyValue::const_iterator begin() const noexcept
     {
          return env_.cbegin();
     }

     KeyValue::const_iterator end() const noexcept
     {
          return env_.cend();
     }

     std::string_view get( std::string_view key ) const
     {
          const auto found = env_.find( key );
          if( found != env_.end() )
          {
               return found->second;
          }
          BOOST_THROW_EXCEPTION( NoKeyFound{ key } );
          return {};
     }

private:
     void parse( char** envp )
     {
          for( auto curr = envp; *curr; ++curr )
          {
               std::string_view kv{ *curr };
               const auto idx = kv.find( '=' );
               if( idx != std::string_view::npos )
               {
                    env_.insert({ kv.substr( 0u, idx ), kv.substr( idx + 1u ) });
               }
          }
     }
     KeyValue env_;
};


class RequestHandler;


class Server
{
     static constexpr auto RequestBufferSize = 4096u;
public:
     Server( RequestHandler& handler );

     void run();

private:
     RequestHandler& handler_;
};


Server::Server( RequestHandler& handler )
     : handler_{ handler }
{
     THROW_RUNTIME_ERROR_IF( FCGX_Init() != 0, "FCGX initialization error" );
}


class RequestHandler
{
public:
     virtual ~RequestHandler() {}
     virtual void operator()( const Environment& env, std::istream& request, std::ostream& response ) = 0;
};


void Server::run()
{
     FCGX_Request request;

     static constexpr auto noSocket = 0;
     static constexpr auto noFlags = 0;

     THROW_RUNTIME_ERROR_IF(
          FCGX_InitRequest( &request, noSocket, noFlags ) != 0
          , "FCGX request initialization error"
          );

     std::array< char, RequestBufferSize > buffer;

     while( FCGX_Accept_r( &request ) == 0 )
     {
          fcgi_streambuf in{ request.in, buffer.data(), buffer.size() };
          fcgi_streambuf out{ request.out };

          std::istream is{ &in };
          std::ostream os{ &out };

          handler_( Environment{ request }, is, os );
     }
}


class SimpleHandler : public RequestHandler
{
public:
     void operator()( const Environment& env, std::istream& request, std::ostream& response ) override
     {
          for( auto&& kv: env )
          {
               std::cout << kv.first << ": " << kv.second << '\n';
          }
          std::copy( std::istreambuf_iterator< char >{ request }, {},
               std::ostreambuf_iterator< char >{ std::cout }
               );
          std::cout << '\n';
          response <<
               "\n<html>"
               "\n    <head>"
               "\n        <title>FCGI Server</title>"
               "\n    </head>"
               "\n    <body>"
               "\n        <h1>This is FCGI response handler!</h1>"
               "\n        Response has been processed at"
               "\n    </body>"
               "\n</html>";
     }
};


int main( int argc, char** argv )
{
     boost::ignore_unused( argc, argv );
     try
     {
          SimpleHandler handler;
          Server{ handler }.run();
     }
     catch( const std::exception& e )
     {
          std::cerr << "exception: " << boost::diagnostic_information( e ) << '\n';
          return 1;
     }
     catch( ... )
     {
          std::cerr << "exception: unknown: "
               << boost::current_exception_diagnostic_information() << '\n';
     }
     return 0;
}
