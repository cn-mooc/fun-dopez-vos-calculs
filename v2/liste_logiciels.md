# Liste des logiciles à installer/installées dans la machine virtuelle

## Compilation
*Nous listons ici que les binaires paquets APT pour un OS Linux Ubuntu*
```bash
g++
gcc
automake
```

## Valgrind
*source: https://valgrind.org/downloads/repository.html*

```bash
git clone https://sourceware.org/git/valgrind.git && \
cd valgrind && \
./autogen.sh && \
./configure && \
make && make install
```
