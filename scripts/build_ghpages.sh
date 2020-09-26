#!/usr/bin/env bash
TMPDIR=$(mktemp -d)

trap "{ rm -rf $TMPDIR; }" EXIT


git clone --branch gh-pages $(git remote get-url origin) $TMPDIR &&\
  pushd $TMPDIR &&\
  git rm -rf ./* &&\
  popd &&\
  rm -rf ./build_docs &&\
  mkdir -p build_docs &&\
  cd build_docs&&\
  cmake .. &&\
  make doxygen &&\
  cp -rf doc/html $TMPDIR &&\
  cd $TMPDIR &&\
  git add ./* &&\
  git commit &&\
  git push
