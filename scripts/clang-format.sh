#!/bin/sh

find                                    \
    "${MESON_SOURCE_ROOT}/src"          \
    "${MESON_SOURCE_ROOT}/include/pyrodb" \
    "${MESON_SOURCE_ROOT}/test"         \
    -iname '*.cpp' -o -iname '*.hpp' | xargs clang-format -i -style=file

