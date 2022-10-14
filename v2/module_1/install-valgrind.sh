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
        ./configure && \
        make && make install
    }
} || exit 1 

rm -rf $WORK_DIR 2>/dev/null

# --- if install succeed, remove temp directory
if [ -d /usr/local/include/lib/valgrind -o -d /usr/local/libexec/valgrind ]; then
   echo "--- valgrind installed [/usr/local/bin/{include,lib,share/doc,libexec}/valgrind] ... "
   exit 0
fi

echo "*** valgrind failed during installation ... "
exit 1
