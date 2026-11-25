#!/usr/bin/env bash
# Compile (without linking) every graphical exercise against raylib/raygui headers.
#   RAYLIB_SRC=path/to/raylib/src RAYGUI_SRC=path/to/raygui/src SQLITE_SRC=path/to/sqlite CXX=g++ bash scripts/check-graphical.sh
set -uo pipefail
cd "$(dirname "$0")/.."
CXX="${CXX:-g++}"
fail=0
for marker in $(find exercises -name .graphical | sort); do
    dir="$(dirname "$marker")"
    for src in $(find "$dir" -name '*.cpp'); do
        if ! $CXX -std=c++23 -c -o /tmp/check-graphical.o -Wall -Wextra -Wno-unused-parameter -Wno-unused-variable \
             -I"$dir" -isystem "$RAYLIB_SRC" -isystem "$RAYGUI_SRC" ${SQLITE_SRC:+-isystem "$SQLITE_SRC"} "$src" 2> /tmp/check-graphical-err.txt; then
            echo "FAIL: $src"; head -20 /tmp/check-graphical-err.txt; fail=1
        fi
    done
done
[ $fail -eq 0 ] && echo "All graphical templates compile."
exit $fail
