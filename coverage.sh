#!/bin/bash

lcov --version > /dev/null 2>&1

if [ $? -ne 0 ]; then
  system=`uname`
  if [ "$system" != "Darwin" ]; then
    sudo apt install -y lcov || { echo -e "\033[0;31mError: Failed to install lcov. Exiting...\033[0m" >&2; exit 1; }
  else
    brew install lcov || { echo -e "\033[0;31mError: Failed to install lcov. Exiting...\033[0m" >&2; exit 1; }
  fi
fi

cd build
echo -e "\033[0;33mGenerating coverage report...\033[0m"
lcov --directory . --capture --output-file coverage.info
genhtml coverage.info --output-directory=coverage-html
echo -e "\033[0;32mCoverage report generated at build/coverage-html/index.html\033[0m"
