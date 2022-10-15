#!/bin/bash
# Copyright - Centrale Nantes
# Version 1.0 @ Fri Oct 14 19:24:50 UTC 2022
# source: https://eigen.tuxfamily.org/index.php?title=Main_Page#Requirements
#
set -x

FILE_VER=${1:-3.4.0}
FILE_CODE=eigen
#FILE_SRC=${FILE_CODE}-${FILE_VER}.tar.gz
FILE_URL="https://gitlab.com/libeigen/${FILE_CODE}.git"
WORK_DIR=`mktemp -d`

[ -d $FILE_CODE ] && {
   echo "*** Répertoire [$FILEC_CODE] existe, merci de le supprimer avant... ***"
   exit 1
}
git clone $FILE_URL && \
cd ${WORK_DIR} && {
    mkdir build && (
      cd build
      cmake ..
      make install 
    )
} || exit 1 

echo "--- Eigin version $FILE_VER installed."
rm -rf $WORK_DIR 2>/dev/null
exit 0
