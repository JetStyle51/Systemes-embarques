# Beaglebone
BeagleBone sont des ordinateur monocarte destiné aux développeurs. Il existe en plusieurs format : BeagleBone Al, Blue, Pocket, Black Wireless, Black, White etc ... Un tableau de comparaison est disponible ici : https://fr.farnell.com/b/beagleboard

BeagleBone® Black est la carte de développement la plus populaire chez les développeurs et les amateurs d’électronique. C’est un outil faible coût, avec beaucoup d’extension axé sur la BeagleBoard® avec un processeur ARM Cortex A8 Sitara AM3358BZCZ100 de Texas Instruments. La carte démarre sous Linux en moins de 10 sec et l’utilisateur peut commencer le développement en moins de 5 min avec un simple câble USB.

Nous utiliserons la carte BeagleBoneBlack pour la suite mais la démarche reste identique peut importe la carte.

## Flasher une nouvelle carte BeagleBone

Sous Windows : se rendre sur le site : https://beagleboard.org/latest-images
Télécharger la dernière version de Debian disponible :
AM5729 : Pour BeagleBoard-X15 et BeagleBone Al
AM3358 : Pour PocketBeagle, BeagleBone, BeagleBone Black, BeagleBone Black Wireless, BeagleBone Black Industrial, BeagleBone Blue, SeeedStudio BeagleBone Green, SeeedStudio BeagleBone Green Wireless, SanCloud BeagleBone Enhanced, Arrow BeagleBone Black Industrial and Mentorel BeagleBone uSomIQ

Pour flasher facilement une image : j'utilise l'outil ElenaBatcher https://www.balena.io/etcher/

Il suffit simplement de connecter une carte SD sur l'ordinateur (avec adaptateur si besoin).

De sélectionner le fichier image de beaglebone précédement téléchargé : de choisir le bon périphérique et de cliquer sur le boutton "Flasher".

Attendre quelques minutes : c'est FAIT !

Mettre la carte SD dans le Beaglebone (hors tension) puis brancher le beaglebone.

Pour rendre le flash persistant : il faut aller dans le fichier :
*/boot/uEnv.txt*

Et à la fin du fichier il suffit de décommenter cette ligne :
```
#cmdline=init=/opt/scripts/tools/eMMC/init-eMMC-flasher-v3.sh
```

Et lancer un reboot.

Un jeu de chenillard au niveau des leds utilisateur commence alors : le flash est terminé lorsque toutes les leds sont eteintes.

Il suffit alors de débrancher le beaglebone, retirer la carte sd et rebrancher.
C'est Terminé !
