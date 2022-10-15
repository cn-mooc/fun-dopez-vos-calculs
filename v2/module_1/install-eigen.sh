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

cd ${WORK_DIR} && {
   [ -d $FILE_CODE ] && {
      echo "*** Répertoire [$FILEC_CODE] existe, merci de le supprimer avant... ***"
      exit 1
   }
   git clone $FILE_URL && cd ${FILE_CODE} &&\
   mkdir build && (
      cd build
      cmake ..
      make install
   )
} || exit 1

[ -d /usr/local/include/eigen3 ] || {
   echo "*** Eigen erreur d'installation... merci re-essayer manuellement étape par étape ***"
   echo "--- Allez dans le répertoire ${WORK_DIR}/eigin et lisez le fichier INSTALL ---"
   exit 1
}
rm -rf $WORK_DIR 2>/dev/null
echo "--- Eigin version $FILE_VER installed."
exit 0
