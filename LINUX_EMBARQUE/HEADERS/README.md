# Installation des headers sur un linux embarqué

## Installation 
Il peut arriver que les headers ne soient pas installé pour une raison ou pour une autre et que ceci peut empêcher la compilation d'une application ou d'un module.

Pour installer un module sur cible embarqué faites les commandes suivantes :
```
sudo apt update
```
Afin de mettre à jours la liste des packets apt-get :
et installer les headers
```
sudo apt-get install linux-headers-`uname -r`
```