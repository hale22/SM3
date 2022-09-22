#!/usr/bin/env bash

set -e

cd build || (echo "Run ./build.sh [<args>] at first" && exit 1)

echo "Running base tests"
ctest -V -R Base

