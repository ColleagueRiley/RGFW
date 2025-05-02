#!/bin/sh
(
	OBJS="`find src -not -name "grammar.c" -and -name "*.c" | sed -E 's/\.c$/.o/g' | tr '\n' ' '`"
	echo "OBJS =$OBJS"
) > objects.mk
