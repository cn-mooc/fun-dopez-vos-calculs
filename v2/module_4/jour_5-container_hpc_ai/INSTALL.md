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
    curl wget git \
    autoconf automake libtool pkg-config libfuse-dev zlib1g-dev
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

   ajouter le chemin binaire dans `$PATH`
   ```bash
   export PATH=$PATH:/usr/local/go/bin 
   ```

3. (optionnel) installer `golangci-lint`
   ```bash
   curl -sSfL https://raw.githubusercontent.com/golangci/golangci-lint/master/install.sh | \
     sh -s -- -b $(go env GOPATH)/bin v1.43.0
   ```
   
   ajouter le chemin binaire dans `$PATH`
   ```bash
   export PATH=$PATH:$(go env GOPATH)/bin
   ```

4. cloner le dépôt Apptainer version **1.1.3**
   ```bash
   git clone https://github.com/apptainer/apptainer.git && cd apptainer
   ```
   et récupérer la version `1.1.3`
   ```bash
   git checkout v1.1.3
   ```
  
5. compiler Apptainer
   ```bash
   ./mconfig -b ./buildtree -p /usr/local
   cd ./buildtree && make && sudo make install
   ```

6. (optionnel) optimiser la performance de squashfuse_ll
   ```bash
   export SQUASHFUSEVERSION=0.1.105
   export SQUASHFUSEPRS="70 77"
   SQUASHFILE=squashfuse-$SQUASHFUSEVERSION
   curl -L -O https://github.com/vasi/squashfuse/archive/$SQUASHFUSEVERSION/${SQUASHFILE}.tar.gz
   for PR in $SQUASHFUSEPRS; do
      curl -L -O https://github.com/vasi/squashfuse/pull/$PR.patch
   done
   if [[  -f ${SQUASHFILE}.tar.gz ]]; then
      tar xzf ${SQUASHFILE}.tar.gz
      cd $SQUASHFILE
      for PR in $SQUASHFUSEPRS; do
         patch -p1 <../$PR.patch
      done
      ./autogen.sh
      CFLAGS=-std=c99 ./configure --enable-multithreading
      make squashfuse_ll
      sudo cp squashfuse_ll /usr/local/libexec/apptainer/bin
   fi
   ```

7. tester si installation ok
   ```bash
   apptainer --version
   # ou
   singularity --version
   ```
   

## Slurm
