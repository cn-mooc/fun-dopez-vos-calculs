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

   ajouter le chemin binaire dans `$PATH`
   ```bash
   export PATH=$PATH:/usr/local/go/bin 
   ```

3. installer `golangci-lint`
   ```bash
   curl -sSfL https://raw.githubusercontent.com/golangci/golangci-lint/master/install.sh | \
     sh -s -- -b $(go env GOPATH)/bin v1.43.0
   ```
   
   ajouter le chemin binaire dans `$PATH`
   ```bash
   export PATH=$PATH:$(go env GOPATH)/bin
   ```

4. cloner le dépôt Apptainer
   ```bash
   git clone https://github.com/apptainer/apptainer.git && cd apptainer
  ```
  et récupérer la version `1.1.3`
  ```bash
  git checkout v1.1.3
  ```
  
5. compiler Apptainer
   ```bash
   ./mconfig
   cd ./builddir && make && sudo make install
   ```



## Slurm
