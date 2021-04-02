/// @file
/// @brief
/// @copyright Copyright (c) InfoTeCS. All Rights Reserved.

#pragma once

#include <unordered_map>

#include <error/exception.h>


struct FCGX_Request;


namespace alexen {
namespace server {
namespace fcgi {


class Environment
{
public:
     struct Error : error::Exception
     {
          Error( const std::string& what ) : Exception{ what } {}
     };
     struct NoKeyFound : Error
     {
          NoKeyFound( std::string_view key )
               : Error{ "no key " + std::string{ key } + " found" } {}
     };

     using KeyValue = std::unordered_map< std::string_view, std::string_view >;

     explicit Environment( const FCGX_Request& request );

     KeyValue::const_iterator begin() const noexcept;
     KeyValue::const_iterator end() const noexcept;

     std::string_view get( std::string_view key ) const;

private:
     void parse( char** envp );

     KeyValue env_;
};

} // namespace fcgi
} // namespace server
} // namespace alexen