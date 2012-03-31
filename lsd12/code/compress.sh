#!/bin/bash
file="ast.c ast.h check.c check.h lsd12.l lsd12.y pcode.c pcode.h sym.c sym.h"
zip_file="LSD.zip"

if [ -f "$zip_file" ]; then
echo "-- delete old lsd.zip"
rm -f $zip_file
fi

zip $zip_file $file
