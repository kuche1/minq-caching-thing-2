#! /usr/bin/env bash

set -euo pipefail

HERE=$(dirname -- "$BASH_SOURCE")

clear

# compile library

"$HERE/mmh3/compile.sh"

# compile executable

FLAGS_STANDARD='-std=c++23'

FLAGS_STRICT='-Werror -Wextra -Wall -pedantic -Wfatal-errors -Wshadow'

FLAGS_MISC='-static -Ofast'
# -static
# -Ofast

FLAGS="$FLAGS_STANDARD $FLAGS_STRICT $FLAGS_MISC"

g++ $FLAGS -o "$HERE/mct2-file" "$HERE/0-mct2-file.cpp" "$HERE/mmh3/MurmurHash3.o"
