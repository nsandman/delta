#! /bin/bash

# Get the biggest string length of all the 
# command line arguments and return it.
# by Noah Sandman

biggest=${#1}

for i in "$@"; do
	if [ ${#i} -gt $biggest ]; then
		biggest="${#i}"
	fi
done

echo "$biggest"