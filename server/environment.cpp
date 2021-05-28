/// @file
/// @brief
/// @copyright Copyright (c) InfoTeCS. All Rights Reserved.

#include <server/environment.h>

#include <boost/throw_exception.hpp>
#include <fcgiapp.h>


namespace alexen {
namespace server {
namespace fcgi {


Environment::Environment( const FCGX_Request& request )
     : Environment{ request.envp }
{}


Environment::Environment( const char* const env[] )
{
     parse( env );
}


Environment::KeyValue::const_iterator Environment::begin() const noexcept
{
     return env_.cbegin();
}


Environment::KeyValue::const_iterator Environment::end() const noexcept
{
     return env_.cend();
}


std::string_view Environment::get( std::string_view key ) const
{
     const auto found = env_.find( key );
     if( found == env_.end() )
     {
          BOOST_THROW_EXCEPTION( KeyNotFound{ key } );
     }
     return found->second;
}


bool Environment::has( std::string_view key ) const noexcept
{
     return env_.count( key ) != 0u;
}


void Environment::parse( const char* const envp[] )
{
     for( auto curr = envp; *curr; ++curr )
     {
          std::string_view kv{ *curr };
          const auto eq = kv.find( '=' );
          auto& valueRef = env_[ kv.substr( 0u, eq ) ];
          if( eq != std::string_view::npos )
          {
               valueRef = kv.substr( eq + 1u );
          }
     }
}


} // namespace fcgi
} // namespace server
} // namespace alexen
