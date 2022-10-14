#!/bin/bash
# Copyright - Centrale Nantes
# Version 1.0 @ Thu Oct 13 18:19:11 CEST 2022
#
set -x

FILE_VER=3.19.0
FILE_SRC=valgrind-${FILE_VER}.tar.bz2
FILE_URL="https://sourceware.org/pub/valgrind/${FILE_SRC}"
WORK_DIR=`mktemp -d`

# --- update apt db
apt purge valgrind

# --- download source
cd $WORK_DIR && {
    wget -q -c $FILE_URL && \ 
    bzip2 -d -c ${FILE_SRC} | tar xf -
    cd valgrind-${FILE_VER} && {
        ./autogen.sh && \
        ./configure --prefix=/usr/local/bin && \
        make && make install
    }
}

rm -rf $WORK_DIR 2>/dev/null
