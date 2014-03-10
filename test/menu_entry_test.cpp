#include "tpunit++.hpp"

#include "../src/menu_entry.h"

namespace mjwm
{
	struct menu_entry_test : tpunit::TestFixture
	{
		menu_entry_test() : tpunit::TestFixture(
			TEST(menu_entry_test::test_menu_entry_parses_name),
			TEST(menu_entry_test::test_menu_entry_parses_icon),
			TEST(menu_entry_test::test_menu_entry_parses_executable),
			TEST(menu_entry_test::test_menu_entry_parses_categories),
			TEST(menu_entry_test::test_menu_entry_escapes_tokens)
		) {}

		void test_menu_entry_parses_name()
		{
			menu_entry entry;
			entry.populate("Name=Mousepad\n");
			EXPECT_EQUAL("Mousepad", entry.name());
		}

		void test_menu_entry_parses_icon()
		{
			menu_entry entry;
			entry.populate("Icon=accessories-text-editor\n");
			EXPECT_EQUAL("accessories-text-editor", entry.icon());
		}

		void test_menu_entry_parses_executable()
		{
			menu_entry entry;
			entry.populate("Exec=mousepad %F\n");
			EXPECT_EQUAL("mousepad %F", entry.executable());
		}

		void test_menu_entry_parses_categories()
		{
			menu_entry entry;
			entry.populate("Categories=Application;Utility;TextEditor;GTK;\n");
			EXPECT_EQUAL("Application;Utility;TextEditor;GTK;", entry.categories());
		}

		void test_menu_entry_escapes_tokens()
		{
			menu_entry entry;
			entry.populate("Name=<'Complicated' & \"Fun\">\n");
			EXPECT_EQUAL("&lt;&apos;Complicated&apos; &amp; &quot;Fun&quot;&gt;", entry.name());
		}
	} __menu_entry_test;
}
