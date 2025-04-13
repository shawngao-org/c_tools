#!/bin/bash

system=`uname`
if [ "$system" != "Darwin" ]; then
  apt install -y lcov
fi
DIRECTORY="build"
echo -e "\033[0;33mCheck if the $DIRECTORY directory exists...\033[0m"
if [ -d "$DIRECTORY" ]; then
  echo -e "\033[0;34mThe $DIRECTORY directory already exists. Deleting $DIRECTORY directory...\033[0m"
  rm -rf "$DIRECTORY"
fi
echo -e "\033[0;33mCreating directory and enter $DIRECTORY\033[0m"
mkdir "$DIRECTORY"
cd "$DIRECTORY"
echo -e "\033[0;33mCMaking...\033[0m"
cmake -DENABLE_COVERAGE=ON ..
echo -e "\033[0;33mMaking...\033[0m"
make -j 2
if [ $? -eq 0 ]; then
  echo -e "\033[0;32mBuild Successful!\033[0m"
else
  echo -e "\033[0;31mBuild Failed!\033[0m"
  exit 1
fi
./test
echo -e "\033[0;33mGenerating coverage result...\033[0m"
lcov -capture -directory . -output-file coverage.info
