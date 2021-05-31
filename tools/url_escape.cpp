/// @file
/// @brief
/// @copyright Copyright (c) InfoTeCS. All Rights Reserved.

#include <tools/url_escape.h>

#include <stdexcept>
#include <memory>

#include <boost/throw_exception.hpp>

#include <curl/curl.h>


namespace alexen {
namespace server {
namespace tools {


namespace {
namespace aux {
namespace curl {


using CurlUptr = std::unique_ptr< CURL, decltype( &curl_easy_cleanup ) >;
CurlUptr makeCurl()
{
     auto curl = curl_easy_init();
     if( !curl )
     {
          BOOST_THROW_EXCEPTION( std::runtime_error{ "bad curl init" } );
     }
     return std::unique_ptr< CURL, decltype( &curl_easy_cleanup ) >{ curl, curl_easy_cleanup };
}


using CurlResourceUptr = std::unique_ptr< void, decltype( &curl_free ) >;
CurlResourceUptr makeCurlResource( void* v )
{
     return CurlResourceUptr{ v, curl_free };
}


} // namespace curl
} // namespace aux
} // namespace {unnamed}



std::string escape( std::string_view source )
{
     const auto curl = aux::curl::makeCurl();
     const auto res = aux::curl::makeCurlResource( curl_easy_escape( curl.get(), source.data(), source.size() ) );
     return std::string{ static_cast< std::string::value_type* >( res.get() ) };
}


std::string unescape( std::string_view source )
{
     const auto curl = aux::curl::makeCurl();
     int resultLen = 0;
     const auto res = aux::curl::makeCurlResource( curl_easy_unescape( curl.get(), source.data(), source.size(), &resultLen ) );
     return std::string{
          static_cast< std::string::value_type* >( res.get() )
          , static_cast< std::string::size_type >( resultLen )
     };
}


} // namespace tools
} // namespace server
} // namespace alexen
