#include "tpunit++.hpp"

namespace mjwm
{
	struct menu_entry_test : tpunit::TestFixture
	{
		menu_entry_test() : tpunit::TestFixture(
			TEST(menu_entry_test::test_pass),
			TEST(menu_entry_test::test_fail),
			TEST(menu_entry_test::test_pass_again)
		) {}

		void test_pass()
		{
			ASSERT_TRUE(1==1);
		}

		void test_fail()
		{
			ASSERT_TRUE(1==0);
		}

		void test_pass_again()
		{
			ASSERT_TRUE(0==0);
		}
	} __menu_entry_test;

}
