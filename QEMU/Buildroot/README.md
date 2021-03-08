# Emulation de Linux avec Buildroot

Prérequis :
```

apt-get install qemu-system-arm
apt-get install libncurses5-dev libncursesw5-dev

```
Cloner le dépot :
```
git clone git://git.busybox.net/buildroot
```

Pour information le manuel d'utilisation est dans /docs/manual/manual.pdf

Rentrer dans le menu de configuration
```
make menuconfig
```

```
make list-defconfigs
```

```
make qemu_arm_versatile_defconfig
```

