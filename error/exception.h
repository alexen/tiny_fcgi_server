/// @file
/// @brief
/// @copyright Copyright (c) InfoTeCS. All Rights Reserved.

#pragma once

#include <stdexcept>
#include <boost/exception/exception.hpp>
#include <boost/exception/error_info.hpp>


namespace alexen {
namespace error {


struct Exception : std::runtime_error, virtual boost::exception
{
     Exception( const std::string& what ) : std::runtime_error{ what } {}
};


using Details = boost::error_info< struct Details_, std::string >;


} // namespace error
} // namespace alexen
