#!/bin/bash
set -x
apt-get --purge valgrind
hash git || exit 1
git clone https://sourceware.org/git/valgrind.git && \
cd valgrind && \
./autogen.sh && \
./configure && \
make
