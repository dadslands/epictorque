#!/usr/bin/bash

A=$(grep -B 5 "; total TS size" tunerstudio/generated/rusefi_*.ini | grep sparkDuration4)
if [ "$A" ]; then
	echo "yay"
else
	echo "nay"
#	kill $PPID
fi

