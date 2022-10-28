
#!/bin/bash
# Copyright - Centrale Nantes
# Version 1.0 @ Fri Oct 28 09:22:18 CEST 2022
# source: https://github.com/apptainer/apptainer/blob/main/INSTALL.md
# tested on Debian-based systems, including Ubuntu
#
set -x

# --- Variables ---
WORK_DIR=`mktemp -d`
export GOVERSION=1.19.2 OS=linux ARCH=amd64

# --- Install system dependencies ---
#
sudo apt-get update
sudo apt-get install -y \
 build-essential \
 libseccomp-dev \
 pkg-config \
 uidmap \
 squashfs-tools \
 squashfuse \
 fuse2fs \
 fuse-overlayfs \
 fakeroot \
 cryptsetup \
 curl wget git \
 autoconf automake libtool pkg-config libfuse-dev zlib1g-dev

# --- Install GO ---
# source: https://go.dev/dl
#
wget -O ${WORK_DIR}/go${GOVERSION}.${OS}-${ARCH}.tar.gz \
  https://dl.google.com/go/go${GOVERSION}.${OS}-${ARCH}.tar.gz
sudo tar -C /usr/local -xzf ${WORK_DIR}/go${GOVERSION}.${OS}-${ARCH}.tar.gz
export PATH=$PATH:/usr/local/go/bin 

# --- Install Apptainer
# source: https://github.com/apptainer
cd ${WORK_DIR} && {
  git clone https://github.com/apptainer/apptainer.git && cd apptainer
  git checkout v1.1.3
  ./mconfig -b ./buildtree -p /usr/local
  cd ./buildtree && make && sudo make install
}
rm -rf ${WORK_DIR}

# --- Test if installation is ok
hash apptainer 2>/dev/null || {
  echo "** ERROR ** installation echouee **"
  exit 1
}
clear
apptainer --version
apptainer exec docker://alpine uname -a
