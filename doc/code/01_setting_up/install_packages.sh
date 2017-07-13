#! /usr/bin/bash

PACKAGES="vim gcc openssh-server gdb tree ctags cscope"

for package in ${PACKAGES}; do
    sudo apt-get install package
done
