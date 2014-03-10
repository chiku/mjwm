#include "tpunit++.hpp"

#include "../src/menu_entry.h"

namespace mjwm
{
	struct menu_entry_test : tpunit::TestFixture
	{
		menu_entry_test() : tpunit::TestFixture(
			TEST(menu_entry_test::test_menu_entry_parses_name)
		) {}

		void test_menu_entry_parses_name()
		{
			menu_entry entry;
			entry.populate("Name=foo\n");
			EXPECT_EQUAL("foo", entry.name());
		}

	} __menu_entry_test;

}
