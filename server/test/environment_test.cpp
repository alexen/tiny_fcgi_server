/// @file
/// @brief
/// @copyright Copyright (c) InfoTeCS. All Rights Reserved.

#include <boost/test/unit_test.hpp>

#include <server/environment.h>


BOOST_AUTO_TEST_SUITE( EnvironmentParsingTest )
BOOST_AUTO_TEST_CASE( ParseValidFcgiEnvironment )
{
     const char* const params[] = {
          "HTTP_REQUEST_VERB=GET",
          "HTTP_VERSION=1.0",
          "HTTP_CONTENT_TYPE=application/json",
          "HTTP_CONTENT_LENGTH=123456",
          "REQUEST_URI=/fcgi/service/name",
          "REQUEST_METHOD=method",
          nullptr
     };

     using alexen::server::fcgi::Environment;

     Environment env{ params };
     BOOST_CHECK_EQUAL( env.get( "HTTP_REQUEST_VERB" ), "GET" );
     BOOST_CHECK_EQUAL( env.get( "HTTP_VERSION" ), "1.0" );
     BOOST_CHECK_EQUAL( env.get( "HTTP_CONTENT_TYPE" ), "application/json" );
     BOOST_CHECK_EQUAL( env.get( "HTTP_CONTENT_LENGTH" ), "123456" );
     BOOST_CHECK_EQUAL( env.get( "REQUEST_URI" ), "/fcgi/service/name" );
     BOOST_CHECK_EQUAL( env.get( "REQUEST_METHOD" ), "method" );
}
BOOST_AUTO_TEST_CASE( ParseFcgiEnvironmentWithEmptyValues )
{
     const char* const params[] = {
          "KEY_HAS_EQUAL_SIGN=",
          "KEY_HAS_NO_EQUAL_SIGN",
          nullptr
     };

     using alexen::server::fcgi::Environment;

     Environment env{ params };
     BOOST_CHECK_EQUAL( env.get( "KEY_HAS_EQUAL_SIGN" ), "" );
     BOOST_CHECK_EQUAL( env.get( "KEY_HAS_NO_EQUAL_SIGN" ), "" );
}
BOOST_AUTO_TEST_CASE( CheckEnvironmentKeyPresence )
{
     const char* const params[] = {
          "HTTP_REQUEST_VERB=GET",
          "HTTP_VERSION=1.0",
          "HTTP_CONTENT_TYPE=application/json",
          nullptr
     };

     using alexen::server::fcgi::Environment;

     Environment env{ params };
     BOOST_CHECK( env.has( "HTTP_REQUEST_VERB" ) );
     BOOST_CHECK( env.has( "HTTP_VERSION" ) );
     BOOST_CHECK( env.has( "HTTP_CONTENT_TYPE" ) );

     BOOST_CHECK( not env.has( "http_request_verb" ) );
     BOOST_CHECK( not env.has( "NO_SUCH_KEY" ) );
}
BOOST_AUTO_TEST_SUITE_END()
