#!/usr/bin/env bash

set -o errexit
set -o nounset

source scripts/astyle_flags.bash

astyle "${ASTYLE_FLAGS[@]}" "${ASTYLE_FILES[@]}"
