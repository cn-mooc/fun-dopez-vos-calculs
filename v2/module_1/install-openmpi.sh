#!/bin/bash
# Copyright - Centrale Nantes
# Version 1.0 @ Fri Oct 14 19:24:50 UTC 2022
# source: https://www.open-mpi.org/software/ompi/v4.1/
#
set -x

SERIES=v4.1
FILE_VER=4.1.4
FILE_CODE=openmpi
FILE_SRC=${FILE_CODE}-${FILE_VER}.tar.gz
FILE_URL="https://download.open-mpi.org/release/open-mpi/$SERIES/${FILE_SRC}"
WORK_DIR=`mktemp -d`

# --- download source
cd ${WORK_DIR} && {
    wget -q -c ${FILE_URL} && tar zxf ${FILE_SRC} &>/dev/null
    cd ${FILE_CODE}-${FILE_VER} && {
        ( ./configure --prefix=/usr/local ) &>/dev/null && \
        ( make && make install ) &>/dev/null
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
