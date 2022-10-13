#!/bin/bash
set -x
hash git || exit 1
git clone https://sourceware.org/git/valgrind.git && \
cd valgrind && \
./autogen.sh && \
./configure && \
make
