/// @file
/// @brief
/// @copyright Copyright (c) InfoTeCS. All Rights Reserved.

#include <array>
#include <string_view>
#include <stdexcept>
#include <iostream>

#include <boost/core/ignore_unused.hpp>
#include <boost/exception/diagnostic_information.hpp>

#include <server/server.h>
#include <server/request_handler.h>
#include <server/environment.h>


using alexen::server::fcgi::Server;
using alexen::server::fcgi::RequestHandler;
using alexen::server::fcgi::Environment;


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
