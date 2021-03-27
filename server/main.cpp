/// @file
/// @brief
/// @copyright Copyright (c) InfoTeCS. All Rights Reserved.

#include <stdexcept>
#include <iostream>

#include <boost/core/ignore_unused.hpp>
#include <boost/exception/diagnostic_information.hpp>


int main( int argc, char** argv )
{
     boost::ignore_unused( argc, argv );
     try
     {

     }
     catch( const std::exception& e )
     {
          std::cerr << "exception: " << boost::diagnostic_information( e ) << '\n';
          return 1;
     }
     return 0;
}
