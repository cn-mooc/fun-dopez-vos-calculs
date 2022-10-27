# Guide d'installation des outils

## Apptainer (ex. Singularity)
*[source](https://github.com/apptainer/apptainer/blob/main/INSTALL.md)*

1. installer les dépendances
   ```bash
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
    curl wget git
   ```
 
2. installer Go
   ```bash
   OUTPUTDIR=`mktemp -d`
   export GOVERSION=1.19.2 OS=linux ARCH=amd64
   wget -O ${OUTPUTDIR}/go${GOVERSION}.${OS}-${ARCH}.tar.gz \
     https://dl.google.com/go/go${GOVERSION}.${OS}-${ARCH}.tar.gz
   sudo tar -C /usr/local -xzf ${OUTPUTDIR}/go${GOVERSION}.${OS}-${ARCH}.tar.gz
   rm -rf ${OUTPUTDIR}
   ```

## Slurm
