/// @file
/// @brief
/// @copyright Copyright (c) InfoTeCS. All Rights Reserved.

#pragma once

#include <iosfwd>


namespace alexen {
namespace server {
namespace fcgi {


class Environment;


class RequestHandler
{
public:
     virtual ~RequestHandler() {}
     virtual void operator()(
          const Environment& env
          , std::istream& request
          , std::ostream& response
     ) = 0;
};


} // namespace fcgi
} // namespace server
} // namespace alexen
