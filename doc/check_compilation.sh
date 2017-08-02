#! /bin/bash

makefiles=`find . | grep Makefile$`
for file in ${makefiles}; do 
    basedir=dirname ${file}
    

