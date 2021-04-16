#!/usr/bin/python
# coding: utf-8

# GPIO50 : Led Rouge
# GPIO60 : Led Verte
# GPIO3 : Led Bleue
# GPIO62 POTENTIO
import time

PWM = "51"


LED_list = [PWM]

T_REF_1 = 0.000195
T_REF_3 = 0.000860
T_REF_32 = 0.010518


def Init_GPIO():
    try:
        f = open("/sys/devices/bone_capemgr.9/slots", "w")
        f.write("am33xx_pwm")
        f.close()
        f = open("sys/devices/bone.captemgr.9/slots","w")
        f.write("bone_pwm_P9_14")
        f.close()
    except:
        pass

    # Configuration des GPIO en sortie
    for buff in LED_list:
        try:
            # Creation du point d'entree au niveau du Kernel
            f = open("/sys/class/gpio/export", "w")
            f.write(buff)
            f.close()

            # Configuration du GPIO en sortie

            f = open("/sys/class/gpio/gpio" + buff + "/direction", "w")
            f.write("out")
            f.close()
        except:
            pass


def generateSymbol(f, delai1, delai0):

    f.flush()
    f.write("1")
    f.flush()
    time.sleep(delai1)
    f.write("0")
    f.flush()
    time.sleep(delai0)


    return 0


def trans_data_433MHz (f, data):

     for i in data:
        if i == '0':
            generateSymbol(f, T_REF_1, T_REF_3)
            generateSymbol(f, T_REF_1, T_REF_3)
        elif i == '1':
            generateSymbol(f, T_REF_1, T_REF_3)
            generateSymbol(f, T_REF_3, T_REF_1)
        elif i == '2':
            generateSymbol(f, T_REF_3, T_REF_1)
            generateSymbol(f, T_REF_3, T_REF_1)
        elif i == 'S':
            generateSymbol(f, T_REF_1, T_REF_32)

def trans_tram_433Mhz(f, maison,objet,activation,repetition):

    for i in range(repetition):
        if maison == "A":
            trans_data_433MHz(f, ['0', '1', '1', '1'])
        elif maison == "B":
            trans_data_433MHz(f, ['1', '0', '1', '1'])
        elif maison == "C":
            trans_data_433MHz(f, ['1', '0', '1', '1'])
        elif maison == "D":
            trans_data_433MHz(f, ['1', '1', '1', '0'])

        if objet == "1":
            trans_data_433MHz(f, ['0', '1', '1'])
        elif objet == "2":
            trans_data_433MHz(f, ['1', '0', '1'])
        elif objet == "3":
            trans_data_433MHz(f, ['1', '1', '0'])

        trans_data_433MHz(f, ['1', '0', '0', '1'])

        if activation == "0":
            trans_data_433MHz(f, ['0'])
        else:
            trans_data_433MHz(f, ['1'])

        trans_data_433MHz(f, ["S"])




def 



def main():
    print("Demarrage du PWM")
    Init_GPIO()
    time.sleep(5)
    f = open("/sys/class/gpio/gpio" + PWM + "/value", "w")
    time.sleep(5)

    #Allumage du tube rouge
    trans_tram_433Mhz(f, "D","1","1",20)
    time.sleep(1)
    trans_tram_433Mhz(f, "D","1","0",20)
    time.sleep(1)

    # Allumage du tube bleu
    trans_tram_433Mhz(f, "B", "3", "1", 20)
    time.sleep(1)
    trans_tram_433Mhz(f, "B", "3", "0", 20)
    time.sleep(1)

    f.close()

    return 0

if __name__ == "__main__":
    main()
