#!/usr/bin/env sh
SOURCE_DIR=${PWD}
BUILD_DIR=$(mktemp -d)
cd $BUILD_DIR &&\
  cmake $SOURCE_DIR &&\
  make -j &&\
  make test
