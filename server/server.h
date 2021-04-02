/// @file
/// @brief
/// @copyright Copyright (c) InfoTeCS. All Rights Reserved.

#pragma once

#include <error/exception.h>


namespace alexen {
namespace server {
namespace fcgi {


class RequestHandler;


class Server
{
public:
     struct Error : error::Exception {
          Error( const std::string& what ) : error::Exception{ what } {}
     };

     Server( RequestHandler& handler );

     void run();

private:
     static constexpr auto RequestBufferSize = 4096u;

     RequestHandler& handler_;
};


} // namespace fcgi
} // namespace server
} // namespace alexen
