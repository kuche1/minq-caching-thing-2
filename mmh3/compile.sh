#! /usr/bin/env bash

set -euo pipefail

HERE=$(dirname -- "$BASH_SOURCE")

g++ -Ofast -c -o "$HERE/MurmurHash3.o" "$HERE/MurmurHash3.cpp"
