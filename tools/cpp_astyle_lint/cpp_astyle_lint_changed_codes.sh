#!/bin/sh

if git rev-parse --verify HEAD >/dev/null 2>&1
then
	against=HEAD
else
	# Initial commit: diff against an empty tree object
	against=4b825dc642cb6eb9a060e54bf8d69288fbee4904
fi

# We should pass only added or modified C/C++ source files to cppcheck.
changed_files=$(git diff-index --cached $against | \
	grep -E '[MA]	.*\.(c|cpp|h)$' | cut -d'	' -f 2)

astyle_args="--style=google --delete-empty-lines --suffix=none --indent=spaces=4 --min-conditional-indent=2 --align-pointer=type --align-reference=type --indent-switches --indent-cases --indent-col1-comments --pad-oper --pad-header --unpad-paren --close-templates --convert-tabs --mode=c"
ignore_lists="-legal/copyright,-whitespace/line_length"

cpp_astyle_lint_Dir="./tools/cpp_astyle_lint"

cp $cpp_astyle_lint_Dir/astyle $cpp_astyle_lint_Dir/astyle.exe

	
if [ -n "$changed_files" ]; then
	$cpp_astyle_lint_Dir/astyle.exe $astyle_args $changed_files
	python $cpp_astyle_lint_Dir/cpplint.py --filter=$ignore_lists $changed_files
	exit $?
fi
