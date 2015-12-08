#include <boost/test/unit_test.hpp>
#include "../lib/text/text.hpp"

BOOST_AUTO_TEST_SUITE(libtext)

/*
Centered text will have no whitespace after it. So, if we pass the string "lhs",
for example, the function should return "   lhs" instead of "   lhs   ", if the
field has nine characters.

Why? This was easier to make. :P
*/
BOOST_AUTO_TEST_CASE(simple_centered_text) {
    BOOST_CHECK_EQUAL(txt::centerTextLine("lhs", 9),
                      "   lhs");
}

BOOST_AUTO_TEST_SUITE_END()
