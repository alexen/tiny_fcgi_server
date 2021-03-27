/// @file
/// @brief
/// @copyright Copyright (c) InfoTeCS. All Rights Reserved.

#include <stdexcept>
#include <iostream>

#include <boost/core/ignore_unused.hpp>
#include <boost/exception/diagnostic_information.hpp>

#include <fcgiapp.h>


#define THROW_EXCEPTION_IF( cond, msg, exc ) \
     do { if( !(cond) ){ BOOST_THROW_EXCEPTION( exc{ msg } ); } } while( false )

#define THROW_RUNTIME_ERROR_IF( cond, msg ) \
     THROW_EXCEPTION_IF( cond, msg, std::runtime_error )


int main( int argc, char** argv )
{
     boost::ignore_unused( argc, argv );
     try
     {
          THROW_RUNTIME_ERROR_IF( FCGX_Init() != 0, "FCGX initialization error" );
     }
     catch( const std::exception& e )
     {
          std::cerr << "exception: " << boost::diagnostic_information( e ) << '\n';
          return 1;
     }
     return 0;
}
