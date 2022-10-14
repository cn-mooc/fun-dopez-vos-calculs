# Liste des logiciles à installer/installées dans la machine virtuelle

## Dépendances
*Nous listons ici que les binaires paquets APT pour un OS Linux Ubuntu*
```bash
autofs
curl
dstat
firefox
g++
gcc
git
jq
lsrelease
meld
nload
python3
pythondev
pythonpip
pythonvenv
wget
```

## Valgrind
*source: https://valgrind.org/downloads/repository.html*

Installation

```bash
git clone https://sourceware.org/git/valgrind.git && \
cd valgrind && \
./autogen.sh && \
./configure && \
make && make install
```
