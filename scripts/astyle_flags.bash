readonly ASTYLE_FLAGS=(
	--style=java
	--indent=tab
	--pad-oper
	--pad-header
	--unpad-paren
	--align-pointer=name
	--add-brackets
)
readonly ASTYLE_FILES=(src/*.h src/*.c test/*.c)
