#!/bin/sh

validate() {
  cover="0"

  if [ "$CXX" != "g++" ]
  then
    echo ">>> Won't generate coverage: set CXX to g++ explicitly <<<"
    return
  fi
  which lcov > /dev/null 2>&1
  if [ $? != 0 ]
  then
    echo ">>> Won't generate coverage: lcov not found in PATH <<<"
    return
  fi

  cover="1"
}

reconfigure() {
  ./autogen.sh
  CXXFLAGS="-g -O0 --coverage" CFLAGS="-g -O0 --coverage" LDFLAGS="--coverage" ./configure --prefix /tmp/mjwm
}

build_with_test_run() {
  make clean
  make -j4
  make check -j4
}

generate_html_report() {
  if [ $cover -eq "1" ]
  then
    lcov --capture --directory src --output-file coverage.info
    lcov --remove coverage.info "/usr*" --output-file filtered.coverage.info
    genhtml filtered.coverage.info --num-spaces 4 --output-directory coverage
  fi
}

cleanup() {
  find . -name *.gcda -delete
  find . -name *.gcno -delete
  find . -name *.coverage.info -delete
}

set -e

validate
cleanup
rm -rf coverage
reconfigure
build_with_test_run
generate_html_report
cleanup
