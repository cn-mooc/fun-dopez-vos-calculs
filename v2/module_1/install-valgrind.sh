#!/bin/bash
# Copyright - Centrale Nantes
# Version 1.0 @ Fri Oct 14 19:24:50 UTC 2022
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

# --- if install succeed, remove temp directory
if [ -d /usr/local/include/lib/valgrind -o -d /usr/local/libexec/valgrind ]; then
   echo "--- valgrind version $FILE_VER installed."
   echo "--- Files installed in [/usr/local/bin/{include,lib,share/doc,libexec}/valgrind]"
   rm -rf $WORK_DIR 2>/dev/null
   exit 0
fi

echo "*** valgrind failed during installation ... try to recompile [$WORK_DIR/valgrind-${FILE_VER}] "
exit 1
