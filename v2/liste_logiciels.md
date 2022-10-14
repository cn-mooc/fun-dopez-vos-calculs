# Liste des logiciles à installer/installées dans une machine virtuelle Linux
*Tous les logiciels listés ici ont été testés et validés pour fonctionner sous l'OS Ubuntu >20.04*

## Dépendances
Nous listons ici que les binaires paquets APT pour un OS Linux Ubuntu.

*Copiez la liste ci-dessous en une ligne et collez-la à la commande d'installateur de paquets APT* comme suit `apt install <liste>`
```bash
autofs pythonpip jq python3 pythondev git curl wget pythonvenv lsrelease dstat nload dnsutils g++ gcc firefox meld cmake automake cowsay lolcat
```

## OpenMPI

## Valgrind
*source: https://valgrind.org*

### Installation par compilation à partir du code source.

```bash
git clone https://sourceware.org/git/valgrind.git && \
cd valgrind && \
./autogen.sh && \
./configure --prefix=/usr/bin/ && \
make && \
sudo make install
```

Sinon vous pouvez exécuter le script fourni par notre équipe dans le répertoire de ce dépôt dans `v2/module_1`
```bash
# version par défaut 3.19.0
sudo bash ./install-valgrind.sh <numero de version>
```

Pour tester si l'installation s'est bien passée, affichez le numéro de version
```bash
valgrind --version
```


## Kcachegrind
*source: https://kcachegrind.github.io/html/Home.html*

- à partir de la version 0.7.x `KCachegrind` est disponible dans les packages avec la distribution [KDE 4.x](https://kde.org)
- téléchargez le code source ici >> https://kcachegrind.github.io/html/Download.html et décompressez le fichier tar.gz
- lisez les fichiers INSTALL et README, notamment sur comment installer KDE 
  - https://techbase.kde.org/Getting_Started/Build/KDE4
  - https://techbase.kde.org/Getting_Started/Build

## Massif-Visualizer
*source: https://snapcraft.io/install/massif-visualizer/ubuntu*

```bash
sudo apt update
sudo apt install snapd
sudo snap install massif-visualizer --edge
```

## Scalasca / Blade
*source: https://www.scalasca.org/scalasca/software/scalasca-2.x/download.html*

L'installation de cet outil étant complexe et fastidieuse, il est préférable de suivre pas-à-pas les instructions de l'éditeur:
- https://www.scalasca.org/scalasca/software/scalasca-2.x/requirements.html
- **attention** il y a beaucoup de libraires à installer auparavant.
  - 

## Tau / Jumpshot
*source: https://www.cs.uoregon.edu/research/tau/home.php*

- suivre les instructions d'installation >> https://www.cs.uoregon.edu/research/tau/downloads.php
- **attention** il faudra télécharger la source compressée http://tau.uoregon.edu/tau.tgz qui fait 70M!
- 
