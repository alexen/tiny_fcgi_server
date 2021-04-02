/// @file
/// @brief
/// @copyright Copyright (c) InfoTeCS. All Rights Reserved.

#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>

#include <server/environment.h>


BOOST_AUTO_TEST_SUITE( EnvironmentParsingTest )
BOOST_AUTO_TEST_CASE( ParseValidFcgiEnvironment )
{
     const char* params[] = {
          "HTTP_REQUEST_VERB=GET",
          "HTTP_VERSION=1.0",
          "HTTP_CONTENT_TYPE=application/json",
          "HTTP_CONTENT_LENGTH=123456",
          "REQUEST_URI=/fcgi/service/name",
          "REQUEST_METHOD=method",
     };

     using alexen::server::fcgi::Environment;

     Environment env{ params };
     BOOST_CHECK_EQUAL( env.get( "HTTP_REQUEST_VERB" ), "GET" );
}
BOOST_AUTO_TEST_SUITE_END()
