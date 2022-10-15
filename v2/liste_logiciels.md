# Liste des logiciles à installer
📌 *Tous les logiciels listés ici ont été testés et validés pour fonctionner sous l'OS Ubuntu >20.04*<br>
📌 *Prévoyez au minimun 30min pour installer tous ces logiciels*

## Avant de commencer, si ce n'est pas encore fait...
### Clôner le dépôt GIT
- Clonez le dépôt GIT pour ce MOOC
  ```bash
  git clone https://github.com/cn-mooc/fun-dopez-vos-calculs.git
  cd fun-dopez-vos-calculs/v2
  ```
 
  ou faire un `pull` pour avoir les dernières mises à jour:

  ```bash
  $ cd fun-dopez-vos-calculs/v2
  $ git pull
  ```
- Installez les logiciels ci-dessous en suivant les étapes décrites.

### Résoudre les dépendances
Nous listons ici que les binaires paquets APT pour un OS Linux Ubuntu.

- Mettre à jour la base APT
  ```bash
  $ sudo apt update
  ```
  
- Copiez et exécutez la commande qui suit pour installer les dépendances recommandées.
  ```bash
  sudo apt install binutils \
    autofs pythonpip jq python3 pythondev git curl \
    wget pythonvenv lsrelease dstat nload dnsutils \
    g++ gcc firefox meld cmake automake cowsay lolcat
  ```
  
## OpenMPI - version 4.1.4
*source: https://www.open-mpi.org/*
<br> 🟩 *inclus dans l'installation automatique par le script de configuration*

- téléchargez le code source >> https://download.open-mpi.org/release/open-mpi/v4.1/openmpi-4.1.4.tar.gz
- lisez les notes sur [cette version](https://github.com/open-mpi/ompi/blob/v4.1.x/contrib/dist/linux/README)

### Installation manuelle par compilation
```bash
wget -c https://download.open-mpi.org/release/open-mpi/v4.1/openmpi-4.1.4.tar.gz && tar zxf openmpi-4.1.4.tar.gz \
cd openmpi-4.1.4 && \
  ./configure --prefix=/usr/local/ && \
  make && sudo make install
```

### Installation via APT
```bash
sudo apt install openmpi-bin openmpi-common
```

### Installation script automatique
```bash
$ cd fun-dopez-vos-calculs/v2/module_1 && git pull
$ sudo bash ./install-openmpi.sh 4.1.4
```

## Eigin - version 3.4.0
*source: https://eigen.tuxfamily.org/index.php?title=Main_Page*
<br> 🟩 *inclus dans l'installation automatique par le script de configuration*

### Installation avec compilation via `Cmake`
```
  git clone https://gitlab.com/libeigen/eigen.git
  cd eigen && {
    mkdir build && cd build && (
      cmake ..
      make install
    )
  }
```

### Installation automatique
Lancez simplement le script fait pour le MOOC,
```bash
$ cd fun-dopez-vos-calculs/v2/module_1 && git pull
$ sudo bash ./install-eigen 3.4.0
```

## Valgrind - version 3.19.0
*source: https://valgrind.org*
<br> 🟩 *inclus dans l'installation automatique par le script de configuration*

### Installation par compilation à partir du code source.

```bash
git clone https://sourceware.org/git/valgrind.git && \
cd valgrind && \
./autogen.sh && \
./configure --prefix=/usr/bin/ && \
make && \
sudo make install
```

### Installation script automatique
Sinon vous pouvez exécuter le script fourni par notre équipe dans le répertoire de ce dépôt dans `v2/module_1`
```bash
$ cd fun-dopez-vos-calculs/v2/module_1 && git pull
$ sudo bash ./install-valgrind.sh 3.19.0
```

Pour tester si l'installation s'est bien passée, affichez le numéro de version
```bash
valgrind --version
```


## Kcachegrind - version 0.7.x
*source: https://kcachegrind.github.io/html/Home.html*
<br> 🟩 *inclus dans l'installation automatique par le script de configuration*

- à partir de la version 0.7.x `KCachegrind` est disponible dans les packages avec la distribution [KDE 4.x](https://kde.org)
- téléchargez le code source ici >> https://kcachegrind.github.io/html/Download.html et décompressez le fichier tar.gz
- lisez les fichiers INSTALL et README, notamment sur comment installer KDE 
  - https://techbase.kde.org/Getting_Started/Build/KDE4
  - https://techbase.kde.org/Getting_Started/Build

## Massif-Visualizer
*source: https://snapcraft.io/install/massif-visualizer/ubuntu*
<br> 🟩 *inclus dans l'installation automatique par le script de configuration*

```bash
sudo apt update
sudo apt install snapd
sudo snap install massif-visualizer --edge
```

## Scalasca / Blade - version 2.x
*source: https://www.scalasca.org/scalasca/software/scalasca-2.x/download.html*
<br> 🟥 *exclus de l'installation automatique par le script de configuration*


L'installation de cet outil étant complexe et fastidieuse, il est préférable de suivre pas-à-pas les instructions de l'éditeur:
- https://www.scalasca.org/scalasca/software/scalasca-2.x/requirements.html
- **attention** il y a beaucoup de libraires à installer auparavant.
  - [Score-P](http://www.score-p.org/) - *Minimum version: v1.2 	Tested up to: v7.0*
  - [Cube C++ library and tools](http://scalasca.org/scalasca/front_content.php?idart=1089) - *Minimum version: v4.4 	Tested up to: v4.6*
  - [Cube GUI](http://scalasca.org/scalasca/front_content.php?idart=1089) - *Minimum version: v4.4 	Tested up to: v4.6*

## Tau / Jumpshot - version 2.31.1
*source: https://www.cs.uoregon.edu/research/tau/home.php*
<br> 🟩 *inclus dans l'installation automatique par le script de configuration*

- suivre les instructions d'installation >> https://www.cs.uoregon.edu/research/tau/downloads.php
- **attention** il faudra télécharger la source compressée http://tau.uoregon.edu/tau.tgz qui fait 70M! Décompressez le fichier .tgz
- commencez par ces étapes

### Installation manuelle
Suivez les instructions du fichier INSTALL.

```bash
./configure -bfd=download -dwarf=download -unwind=download -iowrapper
make && sudo make install
```

### Installation automatique
Lancez simplement le script fait pour le MOOC,
```bash
$ cd fun-dopez-vos-calculs/v2/module_1 && git pull
$ sudo bash ./install-tau.sh 2.31.1
```

### Tests
- validate tau installation

```bash
./tau_validate --run x86_64
```
