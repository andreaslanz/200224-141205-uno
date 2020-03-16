//
// Created by andi on 07.03.2020.
//

#ifndef INC_200224_141205_UNO_IO_H
#define INC_200224_141205_UNO_IO_H

// !!! ACHTUNG PIN 7 wird nicht vom DFRoobotLCDShield benuzt SONDERN vom GSM-Schield
// !!! Anstelle von PIN 7 verwendet das DFRoobotLCDShield PIN 11

#include <pins_arduino.h>
#define IO_my_UNO_DFROBOTSHIELD_RS 8
#define IO_my_UNO_DFROBOTSHIELD_EN 9
#define IO_my_UNO_DFROBOTSHIELD_D0 4
#define IO_my_UNO_DFROBOTSHIELD_D1 5
#define IO_my_UNO_DFROBOTSHIELD_D2 6
#define IO_my_UNO_DFROBOTSHIELD_D3 11  //!!! ACHTUNG
#define IO_my_UNO_DFROBOTSHIELD_BUT A0
#define IO_my_UNO_PINS_DFROBOTSHIELD IO_my_UNO_DFROBOTSHIELD_RS, IO_my_UNO_DFROBOTSHIELD_EN, IO_my_UNO_DFROBOTSHIELD_D0, IO_my_UNO_DFROBOTSHIELD_D1,\
                       IO_my_UNO_DFROBOTSHIELD_D2, IO_my_UNO_DFROBOTSHIELD_D3, IO_my_UNO_DFROBOTSHIELD_BUT

#define IO_my_UNO_PUMPENSTEUERUNG_POWER_OUT A1
#define IO_my_UNO_PUMPENSTEUERUNG_SCHWIMMER_IN A3
#define IO_my_UNO_PUMPENSTEUERUNG_PINS IO_my_UNO_PUMPENSTEUERUNG_POWER_OUT, IO_my_UNO_PUMPENSTEUERUNG_SCHWIMMER_IN

#define IO_my_UNO_BAT_PIN A2
#define IO_my_UNO_STOP_PIN A5
#define IO_my_UNO_STOP_BAT_PINS IO_my_UNO_BAT_PIN, IO_my_UNO_STOP_PIN

#define IO_my_UNO_GSM_SHIELD_TX 3
#define IO_my_UNO_GSM_SHIELD_RX 2
#define IO_my_UNO_GSM_SHIELD_RESET 7


#ifndef Arduino-Art
/*
                    +-----+
                    +----[PWR]-------------------| USB |--+
                    |                            +-----+  |
                    |         GND/RST2  [ ][ ]            |
                    |       MOSI2/SCK2  [ ][ ]  A5/SCL[ ] |   C5
                    |          5V/MISO2 [ ][ ]  A4/SDA[ ] |   C4
                    |                             AREF[ ] |
                    |                              GND[ ] |
                    | [ ]N/C                    SCK/13[ ] |   B5
                    | [ ]IOREF                 MISO/12[ ] |   .
                    | [ ]RST                   MOSI/11[ ]~|   .  DF-Robot d2 !!Nicht PIN 7!!
                    | [ ]3V3    +---+               10[ ]~|   .
                    | [ ]5v     | A |                9[ ]~|   .  DF-Robot en
                    | [ ]GND   -| R |-               8[ ] |   B0 DF-Robot rs
                    | [ ]GND   -| D |-                    |
                    | [ ]Vin   -| U |-               7[ ] |   D7 GSM-Shield Reset !!Normal DFRobot
                    |          -| I |-               6[ ]~|   .  DF-Robot d2
       DF-Robot But.| [ ]A0    -| N |-               5[ ]~|   .  DF-Robot d1
       Pumpe Power  | [ ]A1    -| O |-               4[ ] |   .  DF-Robot d0
       Bat.Volt     | [ ]A2     +---+           INT1/3[ ]~|   .  GSM-Shield TX
       Schwimmer    | [ ]A3                     INT0/2[ ] |   .  GSM-Shield RX
                    | [ ]A4/SDA  RST SCK MISO     TX>1[ ] |   .
       Stop Volt    | [ ]A5/SCL  [ ] [ ] [ ]      RX<0[ ] |   D0
                    |            [ ] [ ] [ ]              |
                    |  UNO_R3    GND MOSI 5V  ____________/
                    \_______________________/

http://busyducks.com/ascii-art-arduinos
*/
#endif //Arduino-Art





#endif //INC_200224_141205_UNO_IO_H
