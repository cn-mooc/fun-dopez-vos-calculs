#!/bin/bash

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
