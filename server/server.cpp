/// @file
/// @brief
/// @copyright Copyright (c) InfoTeCS. All Rights Reserved.

#include <server/server.h>

#include <array>
#include <iostream>

#include <boost/throw_exception.hpp>

#include <fcgiapp.h>
#include <fcgio.h>

#include <server/environment.h>
#include <server/request_handler.h>


namespace alexen {
namespace server {
namespace fcgi {


Server::Server( RequestHandler& handler )
     : handler_{ handler }
{
     if( FCGX_Init() != 0 )
     {
          BOOST_THROW_EXCEPTION( Error{ "FCGI initialization error" } );
     }
}


void Server::run()
{
     FCGX_Request request;

     static constexpr auto noSocket = 0;
     static constexpr auto noFlags = 0;

     if( FCGX_InitRequest( &request, noSocket, noFlags ) != 0 )
     {
          BOOST_THROW_EXCEPTION( Error{ "FCGI request initialization error" } );
     }

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


} // namespace fcgi
} // namespace server
} // namespace alexen
