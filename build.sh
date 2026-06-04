#!/bin/bash

set -e

case "$1" in
  build)
    cmake -S . -B out
    cmake --build out
    ;;
  run)
    cmake -S . -B out
    cmake --build out
    $0 $2
    ;;
  clean)
    rm -rf out bin
    ;;
  *)
    echo "usage: build | run | clean"
    ;;
esac