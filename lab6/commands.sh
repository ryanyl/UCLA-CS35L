#!/usr/bin/env bash

for com in `ls /usr/bin | awk '(NR-005131227)%251 == 0'`; do
	echo com
done