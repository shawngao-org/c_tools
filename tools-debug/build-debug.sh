#!/bin/bash

DIRECTORY="build"
echo -e "\033[0;33mCheck if the $DIRECTORY directory exists..."
if [ -d "$DIRECTORY" ]; then
  echo -e "\033[0;34mThe $DIRECTORY directory already exists. Deleting $DIRECTORY directory..."
  rm -rf "$DIRECTORY"
fi
echo -e "\033[0;33mCreating directory and enter $DIRECTORY"
mkdir "$DIRECTORY"
cd "$DIRECTORY"
echo -e "\033[0;33mCMaking..."
cmake ..
echo -e "\033[0;33mMaking..."
make -j 2
if [ $? -eq 0 ]; then
  echo -e "\033[0;32mBuild Successful!\033[0m"
else
  echo -e "\033[0;31mBuild Failed!\033[0m"
  exit 1
fi

export DYLD_LIBRARY_PATH=/usr/local/lib
system=`uname`
if [ "$system" != "Darwin" ]; then
  strace -f ./tools_debug
else
  ./tools_debug
fi

if [ $? -eq 0 ]; then
  echo -e "\033[0;32mTests Successful!\033[0m"
else
  echo -e "\033[0;31mTests Failed!\033[0m"
  exit 1
fi
