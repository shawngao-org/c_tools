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
echo -e "\033[0;38mDo you want to install this lib? (Y/N): "
read REPLY
if [ $REPLY = Y ] || [ $REPLY = y ]; then
  echo -e "\033[0;33mInstalling..."
  make install
  if [ $? -eq 0 ]; then
    echo -e "\033[0;32mInstall Successful!"
  else
    echo -e "\033[0;31mInstall Failed!"
    exit 1
  fi
fi
