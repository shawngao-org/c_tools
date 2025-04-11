#!/bin/bash

DIRECTORY="build"
echo -e "\033[0;33mCheck if the $DIRECTORY directory exists..."
if [ -d "$DIRECTORY" ]; then
  echo -e "\033[0;34mThe $DIRECTORY directory already exists. Deleting $DIRECTORY directory..."
  rm -rf $DIRECTORY
fi
echo -e "\033[0;33mCreating directory and enter $DIRECTORY"
mkdir $DIRECTORY
cd $DIRECTORY
echo -e "\033[0;33mCMaking..."
cmake ..
echo -e "\033[0;33mMaking..."
make -j 2
if [ $? -eq 0 ]; then
  echo -e "\033[0;32mBuild Successful!"
else
  echo -e "\033[0;31mBuild Failed!"
  exit 1
fi
echo -e "\033[0;38mDo you want to install this lib to system? (Y/N) [default in 5s: Y]: "
read -t 5 REPLY
if [ -z $REPLY ]; then
  REPLY="Y"
fi
if [ $REPLY = Y ] || [ $REPLY = y ]; then
  echo -e "\033[0;33mInstalling..."
  sudo make install
  system=`uname`
  if [ "$system" == "Darwin" ]; then
    # Mac OS
  else
    ldconfig
  fi
  if [ $? -eq 0 ]; then
    echo -e "\033[0;32mInstall Successful!\033[0m"
  else
    echo -e "\033[0;31mInstall Failed!\033[0m"
    exit 1
  fi
fi
