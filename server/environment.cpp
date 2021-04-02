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
{
     parse( request.envp );
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
          BOOST_THROW_EXCEPTION( NoKeyFound{ key } );
     }
     return found->second;
}


void Environment::parse( char** envp )
{
     for( auto curr = envp; *curr; ++curr )
     {
          std::string_view kv{ *curr };
          const auto idx = kv.find( '=' );
          if( idx != std::string_view::npos )
          {
               env_.insert({ kv.substr( 0u, idx ), kv.substr( idx + 1u ) });
          }
     }
}


} // namespace fcgi
} // namespace server
} // namespace alexen
