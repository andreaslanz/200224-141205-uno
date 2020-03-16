#ifndef main_h
#define main_h

//GEN 1
//#include <LiquidCrystal.h>
//#include <GSM.h>
/* Module Ein/Aus */
#define GSM_ENABLE true         // GSM Ein/Aus  __VA_ARGS__
#define SERIAL_ENABLE true      // Seriel Ausgabe Ein/Aus
#define GEN2
#define GEN1

//GEN 2
#include <DFRobot_LCD_Shield.h>
#include "stop.h"

//GEN 2

extern DFRobot_LCD_Shield my_dfRobotLcdShield;
extern STOP my_stop;
extern int screen;
extern bool screen_setup;
extern long looptime; //Loop Time





//GEN 1
void setup_LCD();
void LCD (const __FlashStringHelper* s);
void LCD (char* s);

//Weideüberwachung
//GSM_SMS sms;
void wdt_reset();



//Pumpensteuerung
void setup_pumpensteuerung();
void loop_pumpensteuerung();
void send_status_sms();
void display();

//Stop
void wire_loop() ;
void wire_init();

//GSM Shield
void GSM_Init();
void send_SMS(const __FlashStringHelper* s) ;
void send_SMS(char s[]);
bool recieve_SMS(char* s); 

//DFRobot_LCD_Shield
void loop_LCD();

#endif



