/// @file
/// @brief
/// @copyright Copyright (c) InfoTeCS. All Rights Reserved.

#include <stdexcept>
#include <iostream>

#include <boost/core/ignore_unused.hpp>
#include <boost/exception/diagnostic_information.hpp>

#include <fcgiapp.h>
#include <fcgio.h>


#define THROW_EXCEPTION_IF( cond, msg, exc ) \
     do { if( cond ){ BOOST_THROW_EXCEPTION( exc{ msg } ); } } while( false )

#define THROW_RUNTIME_ERROR_IF( cond, msg ) \
     THROW_EXCEPTION_IF( cond, msg, std::runtime_error )


void handle( std::istream& request, std::ostream& response )
{
}


int main( int argc, char** argv )
{
     boost::ignore_unused( argc, argv );
     try
     {
          THROW_RUNTIME_ERROR_IF( FCGX_Init() != 0, "FCGX initialization error" );

          FCGX_Request request;

          static constexpr auto noSocket = 0;
          static constexpr auto noFlags = 0;

          THROW_RUNTIME_ERROR_IF(
               FCGX_InitRequest( &request, noSocket, noFlags ) != 0
               , "FCGX request initialization error"
               );

          while( FCGX_Accept_r( &request ) == 0 )
          {
               fcgi_istream is{ request.in };
               fcgi_ostream os{ request.out };

               handle( is, os );
          }
     }
     catch( const std::exception& e )
     {
          std::cerr << "exception: " << boost::diagnostic_information( e ) << '\n';
          return 1;
     }
     return 0;
}
