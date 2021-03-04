# Emuler Uboot sur Linux :

Pour emuler et lancer UBoot sur une plateforme émulé c'est très simple : 
il faut

Télécharger la dernière version de uboot :
```
git clone https://github.com/u-boot/u-boot.git
```

Générer le fichier de configuration lié à qemu:
```
cd u-boot/
make ARCH=arm CROSS_COMPILE=arm-none-eabi- qemu_arm_config
```

Compiler Uboot avec cette configuration :
```
make all ARCH=arm CROSS_COMPILE=arm-none-eabi-
```

Lancer l'émulateur après l'avoir installé :
```
apt-get install qemu-system
qemu-system-arm -M virt -nographic -kernel u-boot
```

C'est fait !
