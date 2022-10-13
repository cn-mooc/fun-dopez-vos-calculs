#!/bin/bash
# Copyright - Centrale Nantes
# Version 1.0 @ Thu Oct 13 18:19:11 CEST 2022
#
set -x
apt-get --purge valgrind
hash git || exit 1
git clone https://sourceware.org/git/valgrind.git && \
cd valgrind && \
./autogen.sh && \
./configure && \
make
