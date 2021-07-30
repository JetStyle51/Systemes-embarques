# Hardware

Dans cette partie, nous allons apprendre à simuler, créer nos propres cartes d'électronique.
Avec nos schemas electriques (schematics) et schemas de conception Printed Circuit Board (PCB).

# Construire sa carte électronique
Dans cette partie nous allons apprendre à créer Schematic & PCB.
Pour cela il existe de nombreux logiciels de CAO pour le faire (EAGLE, Cadence, KiCAD, ECAD ...) personnellement j'ai choisi Altium Designer qui offre une interface complète et assez simple au final à prendre en main pour créer ses propres cartes électroniques.

## Construire son outline
Le manufacturier a besoin des lignes extérieurs de la carte, celle ci peut être généré rapidement en créant un "outline" tout autour de la board.
Pour cela :
1. Create an outline around the board cutout by using: Design ► Board Shape ► Created Primitives from Board Shape.
![img1](https://www.altium.com/documentation/sites/default/files/resize/remote/66c212b1c45cb64ce23b273c37a54979-520x387.jpeg)

2. With the Line/Arc Primitives from Board Shape panel, set the width to be a small value (such as .001mil) and set the layer to be a Mechanical Layer.

3. Enable the option Include Cutouts and select 'OK' to confirm. This will generate an outline around the board and all cutouts.

![img2](https://www.altium.com/documentation/sites/default/files/resize/remote/ffb528d4967c7145ca5f68764bd9a9b8-519x245.jpeg)

4. Generate your Gerber output files and make sure that to enable the Mechanical Layer, specified in step 2 above, to have the outlines exported in the mechanical Gerber layer.

![img3](https://www.altium.com/documentation/sites/default/files/resize/remote/7b0722c93c58e2c890117b9368f7044b-624x560.jpeg)


This will generate a Gerber file for Mechanical Layer that represents the cutouts.


# Commander son PCB
Plusieurs constructeur en france sont plutôt réputé dans le monde de l'électronique.
En premier lieux j'utilise :
JLCPCB : https://jlcpcb.com/


# Commander ses composants

Plusieurs fournisseurs en france sont plutôt réputé dans le monde de l'électronique.
En premier lieux je citerais :
RS Components France : https://fr.rs-online.com/web/
Farnell France : https://fr.farnell.com/
Mouser France : https://www.mouser.fr/
Digikey : https://www.digikey.fr/



## La connection SWD

SWD est l'acronyme de Serial Wire Debug, c'est une interface utilisant trois fils SWDIO et SWCLK et GND, c'est une alterative à l'utilisation du JTAG

## La connection JTAG (Joint Test Action Group) ou Boundary Scan: Port d'accès de test

Le bus JTAG est un bus série synchrone composé des cinq signaux de contrôle suivants :

- TMS, (Test Mode Select) Signal d'activation de la communication JTAG,
- TCK, (Test ClocK) Horloge,
- TDI, (Test Data Input) Entrée des données,
- TDO, (Test Data Output) Sortie des données,
- TRST, (Test ReSeT) Réinitialisation. Ce signal optionnel est actif au niveau bas.

Il est à noter que certaines applications plus modernes sont dotées de signaux additionnels, tels que :

- RTCK, (Returned Test Clock) Signal optionnel permettant de dialoguer sur une fréquence automatiquement corrigée. Plutôt qu'un réglage manuel en Hz
- NRST, (Neutral Test Reset) Réinitialisation neutre matérielle. Signal commutant tout le matériel sur un statut connu du programmeur afin d'initier une communication plus facilement.