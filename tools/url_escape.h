/// @file
/// @brief
/// @copyright Copyright (c) InfoTeCS. All Rights Reserved.

#pragma once

#include <iosfwd>
#include <string_view>


namespace alexen {
namespace server {
namespace tools {


std::string escape( std::string_view source );
std::string unescape( std::string_view source );

} // namespace tools
} // namespace server
} // namespace alexen
