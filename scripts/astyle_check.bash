#!/usr/bin/env bash

set -o nounset

source scripts/astyle_flags.bash

success=true

for file in "${ASTYLE_FILES[@]}"; do
	echo "$file"
	# Run astyle on the file and diff it with the file itself. If astyle
	# made changes, the format wasn't correct.
	if ! astyle "${ASTYLE_FLAGS[@]}" < "$file" | diff - "$file"; then
		success=false
	fi
done

if $success; then
	echo 'No astyle checker errors'
fi

# $success will call either the `true' or `false' shell builtins, and
# we will exit with their exit code.
exit $($success)
