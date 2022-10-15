# LISEZ MOI AVANT...
Ce fichier README se trouve dans le dépôt officiel ci-dessous que vous pouvez soit le clôner:

```bash
$ git clone https://github.com/cn-mooc/fun-dopez-vos-calculs.git
$ cd fun-dopez-vos-calculs/v2
```

ou faire un `pull` pour avoir les dernières mises à jour:

```bash
$ cd fun-dopez-vos-calculs/v2
$ git pull
```

## Comment installer votre machine virtuelle
Afin de suivre les exercices et les cours des prochaines semaines, il est vivement conseillé de commencer à prendre en main sur l’environnement Linux Ubuntu dans une machine virtuelle (VM) en l’installant sur votre machine local. Pour ce faire, vous allez utiliser VirtualBox que vous installerez localement, si vous ne l’avez pas encore.

### Installer VirtualBox
On vous invite à suivre pas-à-pas le tutoriel officiel de chez Canonical Ubuntu ci-dessous pour vous aider à installer et configurer à la fois votre environnement Linux Ubuntu avec VirtualBox. Il est en anglais mais les captures d’écran sont nombreuses pour que vous ne soyez pas perdus dans les textes.

> [Comment installer une machine virtuelle Linux ou Windows avec VirtualBox](https://lecrabeinfo.net/virtualbox-installer-windows-linux-dans-une-machine-virtuelle.html) ([version anglaise](https://ubuntu.com/tutorials/how-to-run-ubuntu-desktop-on-a-virtual-machine-using-virtualbox))


Toutefois si vous rencontrez le moindre souci, venez nous rejoindre en live dans le forum prévu à cet effet pour poser vos questions et vos problèmes, tous les **jeudis de 12h30 à 14h**.

Dès que vous avez réussi cette 1ère étape dans l’installation de votre 1ere VM sous Ubuntu avec VirtualBox, passez à l’étape suivante celle des installations de logiciels opensource nécessaires dans les prochaines semaines. 

### Configurer une OS Ubuntu
Nous vous proposons de suivre les instructions suivantes:

1. Connectez-vous sur votre VM avec le login par défaut, ici généralement `ubuntu`.

2. Au prompt, lancez la commande suivante pour connaître la date et l’heure mais surtout activer le cache sudo utile pour effectuer des actions « système » à suivre sans saisir de mot de passe à chaque exécution.

   ```bash
   $ sudo date
   ```

3. Vérifiez que vous avez internet avec la commande ping qui doit vous retourner que le site destination (ici un des dns de google à l’adresse `8.8.8.8`, qui est censé être toujours accessible ;-) Si vous voyez comme résultat des paquets perdus ou un temps de réponse long, vérifiez alors qu’il n’y a pas de problème avec votre connexion internet avant de continuer l’étape suivante:

   ```bash
   $ ping 8.8.8.8
   PING 8.8.8.8 (8.8.8.8): 56 data bytes
   64 bytes from 8.8.8.8: icmp_seq=0 ttl=116 time=9.744 ms
   ...
   ```

4. Lancez ensuite une mise à jour de la base de données des paquets système Ubuntu avec `apt` et installez un autre installateur `snap` pour des paquets spécifiques.

   ```bash
   $ sudo apt update
   $ sudo apt install -y snapd
   ```
   
5. Puis faites une mise à jour complète du système pour sécuri

ser votre Linux avec les dernières corrections des logiciels déjà installés par défaut. Lancez la commande suivante. Attention, ça pourrait prendre un peu de temps.

   ```bash
   $ sudo apt -y upgrade
   ```
   
6. Installez des outils indispensables et nécessaires pour la suite des actions. Utilisez un script automatique pour ces installations décrites dans le fichier *liste_logiciels.md*

   ```bash
	$ cd fun-dopez-vos-calculs/v2/module_1
	$ sudo bash ./config_vm.sh
   ```

Si toutefois vous rencontrez des erreurs lors de l’installation automatique ci-dessus, vous pouvez toujours suivre pas à pas l’installation manuelle de chaque logiciel expliquée dans le fichier [`liste_logiciels.md`](https://github.com/cn-mooc/fun-dopez-vos-calculs/blob/main/v2/liste_logiciels.md) qui se trouve dans le répertoire `fun-dopez-vos-calculs/v2`
.

## Des références tutoriels complémentaires
- [Vidéo pour installer un Ubuntu sur une machine virtuelle avec VirtualBox](https://youtu.be/36g17uWC1VY) (6min)
- [VirtualBox: installer une machine virtuelle Linux ou Windows](https://lecrabeinfo.net/virtualbox-installer-windows-linux-dans-une-machine-virtuelle.html)
- [VirtualBox: créer un dossier partagé entre l’hôte et l’invité (Windows, Linux)](https://lecrabeinfo.net/virtualbox-creer-dossier-partage-entre-hote-et-invite-windows-linux.html)
- [OpenClassRoom vous aide à installer VirtualBox](https://openclassrooms.com/fr/courses/2035806-virtualisez-votre-architecture-et-vos-environnements-de-travail/6313946-installez-virtualbox)


