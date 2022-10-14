# Liste des logiciles à installer/installées dans la machine virtuelle

## Dépendances
*Nous listons ici que les binaires paquets APT pour un OS Linux Ubuntu*
```bash
autofs pythonpip jq python3 pythondev git curl wget pythonvenv lsrelease dstat nload dnsutils g++ gcc firefox meld
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
