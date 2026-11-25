#!/usr/bin/env bash
# Syntax-check every exercise template that has no CMakeLists.txt of its own.
#   CXX=g++ bash scripts/check-exercises.sh [part-glob]
set -uo pipefail
cd "$(dirname "$0")/.."
CXX="${CXX:-g++}"
fail=0
for dir in exercises/${1:-part*}/*/; do
    [ -f "$dir/CMakeLists.txt" ] && continue
    if ! $CXX -std=c++23 -o /tmp/check-exercise.out -Wall -Wextra -Wno-unused-parameter -Wno-unused-variable -I"$dir" $(find "$dir" -name '*.cpp') 2> /tmp/check-err.txt; then
        echo "FAIL: $dir"; head -20 /tmp/check-err.txt; fail=1
    fi
done
[ $fail -eq 0 ] && echo "All templates compile."
exit $fail
