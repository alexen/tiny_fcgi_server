/// @file
/// @brief
/// @copyright Copyright (c) InfoTeCS. All Rights Reserved.

#include <boost/test/unit_test.hpp>

#include <tools/url_escape.h>


BOOST_AUTO_TEST_SUITE( TestTools )
BOOST_AUTO_TEST_CASE( TestEscapeFunction )
{
     using alexen::server::tools::escape;
     BOOST_TEST( escape( "LettersOnlyString" ) == "LettersOnlyString" );
     BOOST_TEST( escape( "Letters with spaces" ) == "Letters%20with%20spaces" );
     BOOST_TEST( escape( "Hello, world!" ) == "Hello%2C%20world%21" );
     BOOST_TEST( escape( "User Name=Surname Name&Birth Date=1969-11-07&Gender=MALE" )
          == "User%20Name%3DSurname%20Name%26Birth%20Date%3D1969-11-07%26Gender%3DMALE" );
}
BOOST_AUTO_TEST_CASE( TestUnescapeFunction )
{
     using alexen::server::tools::unescape;
     BOOST_TEST( unescape( "LettersOnlyString" ) == "LettersOnlyString" );
     BOOST_TEST( unescape( "Letters%20with%20spaces" ) == "Letters with spaces" );
     BOOST_TEST( unescape( "Hello%2C%20world%21" ) == "Hello, world!" );
     BOOST_TEST( unescape( "User%20Name%3DSurname%20Name%26Birth%20Date%3D1969-11-07%26Gender%3DMALE" )
          == "User Name=Surname Name&Birth Date=1969-11-07&Gender=MALE" );
}
BOOST_AUTO_TEST_CASE( TestUsingEmptyString )
{
     using alexen::server::tools::escape;
     using alexen::server::tools::unescape;

     BOOST_TEST( escape( "" ) == "" );
     BOOST_TEST( unescape( "" ) == "" );
}
BOOST_AUTO_TEST_SUITE_END()
