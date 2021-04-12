# Partitionner un disque

Outils :
- gparted

# Créer une image à partir d'un périphérique /dev/sd?

Une fois le périphérique monté sur /dev/sdX :
Rentrer la commande : (en adaptant sdX à votre périphérique) : bs défini

```
sudo dd bs=4M if=~/SDCardBackup.img of=/dev/sdX
```
