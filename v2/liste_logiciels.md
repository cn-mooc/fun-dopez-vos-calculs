# Liste des logiciles à installer/installées dans la machine virtuelle
*Tous les logiciels listés ici ont été testés et validés pour fonctionner sous l'OS Linux Ubuntu >20.04*

## Dépendances
Nous listons ici que les binaires paquets APT pour un OS Linux Ubuntu.

*Copiez la liste ci-dessous en une ligne et collez-la à la commande d'installateur de paquets APT* comme suit `apt install <liste>`
```bash
autofs pythonpip jq python3 pythondev git curl wget pythonvenv lsrelease dstat nload dnsutils g++ gcc firefox meld
```

## Valgrind
*source: https://valgrind.org*

Installation par compilation à partir du code source.

```bash
git clone https://sourceware.org/git/valgrind.git && \
cd valgrind && \
./autogen.sh && \
./configure --prefix=/usr/bin/ && \
make && \
sudo make install
```

## Kcachegrind
*source: https://kcachegrind.github.io/html/Home.html*


## Massif-Visualer
*source: https://snapcraft.io/install/massif-visualizer/ubuntu*

```bash
sudo apt update
sudo apt install snapd
sudo snap install massif-visualizer --edge
```
