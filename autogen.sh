#! /bin/sh

aclocal -I .
autoheader -I .
automake --add-missing --copy --gnu
autoconf
