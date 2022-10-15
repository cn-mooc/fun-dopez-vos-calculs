#!/bin/bash
# Copyright - Centrale Nantes
# Version 1.0 @ Fri Oct 14 19:24:50 UTC 2022
# source: https://www.open-mpi.org/software/ompi/v4.1/
#
set -x

FILE_VER=${1:-2.31.1}
FILE_CODE=tau
FILE_SRC=${FILE_CODE}.tgz
FILE_URL="http://tau.uoregon.edu/${FILE_SRC}"
WORK_DIR=`mktemp -d`

# --- download source
cd ${WORK_DIR} && {
    wget -q -c ${FILE_URL} && tar zxf ${FILE_SRC}
    cd ${FILE_CODE}-${FILE_VER} && {
        ( ./configure -bfd=download -dwarf=download -unwind=download -iowrapper ) && \
        ( make && make install ) || exit 1
        ./tau_validate --run x86_64
    } 
} || exit 1 

# --- if install succeed, remove temp directory
echo "--- tau version installed."
rm -rf $WORK_DIR 2>/dev/null
exit 0
