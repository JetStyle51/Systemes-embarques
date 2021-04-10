# Driver LCD pour environnement embarqué Linux :

Inspiré du tutoriel :
https://www.circuitbasics.com/raspberry-pi-i2c-lcd-set-up-and-programming/

## Ecrire en sortie :

```
import I2C_LCD_driver
from time import *

mylcd = I2C_LCD_driver.lcd()

mylcd.lcd_display_string("Hello World!", 1)
```

## Position du texte :


```
import I2C_LCD_driver
from time import *

mylcd = I2C_LCD_driver.lcd()

mylcd.lcd_display_string("Hello World!", 2, 3)
```

## Nettoyer l'écran :


```
import I2C_LCD_driver
from time import *

mylcd = I2C_LCD_driver.lcd()

mylcd.lcd_display_string("This is how you", 1)
sleep(1)

mylcd.lcd_clear()

mylcd.lcd_display_string("clear the screen", 1)
sleep(1)

mylcd.lcd_clear()
```

## Faire clignoter le texte : 


```
import time
import I2C_LCD_driver
mylcd = I2C_LCD_driver.lcd()

while True:
    mylcd.lcd_display_string(u"Hello world!")
    time.sleep(1)
    mylcd.lcd_clear()
    time.sleep(1)
```

## Afficher Date & Heure :

```
import I2C_LCD_driver
import time
mylcd = I2C_LCD_driver.lcd()


while True:
    mylcd.lcd_display_string("Time: %s" %time.strftime("%H:%M:%S"), 1)
    
    mylcd.lcd_display_string("Date: %s" %time.strftime("%m/%d/%Y"), 2)
```

## Afficher Addresse Ip :
```
import I2C_LCD_driver
import socket
import fcntl
import struct

mylcd = I2C_LCD_driver.lcd()

def get_ip_address(ifname):
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    return socket.inet_ntoa(fcntl.ioctl(
        s.fileno(),
        0x8915, 
        struct.pack('256s', ifname[:15])
    )[20:24])

mylcd.lcd_display_string("IP Address:", 1) 

mylcd.lcd_display_string(get_ip_address('eth0'), 2)
```

## Scroller le texte de gauche à droite :
```
import I2C_LCD_driver
from time import *

mylcd = I2C_LCD_driver.lcd()

str_pad = " " * 16
my_long_string = "This is a string that needs to scroll"
my_long_string = str_pad + my_long_string

while True:
    for i in range (0, len(my_long_string)):
        lcd_text = my_long_string[i:(i+16)]
        mylcd.lcd_display_string(lcd_text,1)
        sleep(0.4)
        mylcd.lcd_display_string(str_pad,1)
```

## Scroller de droite à gauche :

```
import I2C_LCD_driver
from time import *

mylcd = I2C_LCD_driver.lcd()

str_pad = " " * 16
my_long_string = "This is a string that needs to scroll"
my_long_string = str_pad + my_long_string

for i in range (0, len(my_long_string)):
 lcd_text = my_long_string[i:(i+16)]
 mylcd.lcd_display_string(lcd_text,1)
 sleep(0.4)
 mylcd.lcd_display_string(str_pad,1)
```