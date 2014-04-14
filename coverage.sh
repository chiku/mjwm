#!/bin/sh

validate() {
  which lcov > /dev/null 2>&1
  if [ $? != 0 ]
  then
    echo "Please install lcov"
    exit 1
  fi
  if [ $CXX != "g++" ]
  then
    echo "Can't generate coverage if compiler is not g++"
    exit 0
  fi
}

reconfigure_with_coverage_support() {
  CXXFLAGS="-g -O0 --coverage" CFLAGS="-g -O0 --coverage" LDFLAGS="--coverage" ./configure --disable-shared
}

generate_coverage_output() {
  make clean
  make -j8
  make check -j8
}

generate_html_report() {
  lcov --capture --directory src --output-file coverage.info
  lcov --remove coverage.info "/usr*" --output-file filtered.coverage.info
  genhtml filtered.coverage.info --num-spaces 4 --output-directory coverage
}

cleanup() {
  find . -name *.gcda -delete
  find . -name *.gcno -delete
  find . -name *.coverage.info -delete
}

set -e
trap "cleanup" SIGTERM

validate
cleanup
rm -rf coverage
reconfigure_with_coverage_support
generate_coverage_output
generate_html_report
