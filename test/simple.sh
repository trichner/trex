#!/bin/bash

# Simple helper to assert two strings match
assert () {

DIFF=$(diff <(echo $1) <(echo $2))

echo "==========="

if [ -z "$DIFF" ]
then
	echo "SUCCESS"
else
	echo "FAIL"
	echo "$DIFF"
	echo "$1"
fi
}

# Test if simple decimal group match works
OUT=$(../trex '\(([0-9\.]+) short tons\)' tyrannosaurus.txt)

assert "$OUT" "11.2"

# Test if multi groups work
OUT=$(../trex '([0-9\.]+)[ ]{0,1}m' tyrannosaurus.txt)

assert "$OUT" "66 12.3"
