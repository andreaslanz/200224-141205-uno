/***************************************

   Weide Ueberwachung (Stop / Wasser)

   SMS Alarmierung

****************************************/
//GEN 1
#include <Arduino.h>
#include <main.h>
#include <avr/wdt.h>
//GEN 2
#include <DFRobot_LCD_Shield.h>
#include <IO.h>
#include <stop.h>
#include <PUMPENSTEUERUNG.h>

/*
 *
 * Globale Variablen
 *
 * */


// GEN 2
/*Module*/
DFRobot_LCD_Shield my_dfRobotLcdShield(IO_my_UNO_PINS_DFROBOTSHIELD);
PUMPENSTEUERUNG my_pumpensteurung(IO_my_UNO_PUMPENSTEUERUNG_PINS);
STOP my_stop(IO_my_UNO_STOP_BAT_PINS,1000);




//GEN 1
/* LoopTime */
long looptime=0L; //Loop Time 

/* Display Screens */
int screen=0;
const int screen_numbers=6;
long screen_timmer=millis();
long screen_display_time= 3000L; 
bool screen_setup;

/* Watchdog Timer */
const int num_watch_dog_overflows =3; //Anzahl Watchdog-Timer-Overflows bis reset
int volatile wd_count; //Reset nach Anzahl Overflows
const long Time_SMS_interval= 86400000L; //24L*60L*60L*1000L; // Status SMS senden Interval 24 Stunden

/* DFRobot DFRobot_LCD_Output Shield Stuff */
extern LiquidCrystal lcd;
extern int lcd_key; //Taste


/* Externe Variablen */
extern int Status_Pumpe_On;
extern int Status_Pumpe_Off;
/* externe Variablen */
/* Pumpensteuerung */
extern long       Time_Stamp_next_SMS;                  // Nächste SMS
extern long       Time_Stamp_last_SMS;                  // Letzte SMS
extern long       Time_Stamp_last_test_SMS;             // Letzte Test-SMS


ISR(WDT_vect) {
  wdt_reset(); // reset watchdog counter
  lcd.clear();
  lcd.print("Overflow ");
  lcd.print(String(wd_count,DEC));
  if(wd_count-- > 0) //Overflowzähler bei 0 Reset
    WDTCSR |= (1<<WDIE); // reenable interrupt to prevent system reset
}



/*************
SETUP Function 
***************/
void setup()
{
    //GEN2
    my_dfRobotLcdShield.DFRobot_setup_LCD();
    my_pumpensteurung.setup_pumpensteuerung();
    my_stop.wire_init();
    my_dfRobotLcdShield.DFRobot_setup_LCD();




    //GEN 1
      /* Setup Serial */
      if(SERIAL_ENABLE) 
      {        
        Serial.begin(9600);         
        while (!Serial) {  }
      }
      /* Setup DFRobot_LCD_Output Shield */
       setup_LCD();                

      /* Begrüssungszext anzeigen */
      LCD(F("WeideUeberwacher"));
      delay(2000);
      
    
      /* Setup GSM Shield  */
      if(GSM_ENABLE)
        GSM_Init();                 
    
      /* Setup Pumpen Steuerung  */
      setup_pumpensteuerung();
    
      /* I2C Wire zu Stop initialisierung  */
       wire_init();                
    
      /* Watchdog enable 8 Sekunden  */
      wdt_enable(WDTO_8S) ;         
      WDTCSR |= (1<<WDCE) | (1<<WDIE); //Set Watchdog Interrupt Enable
      wd_count = num_watch_dog_overflows; //Overflowzähler
      sei(); // globally enable interrupts

    
}/* Ende Setup */



/********* 
Main loop 
***********/
void loop()                  
{
      /* Debugg */
      static unsigned long last_print;
      long loop_start =millis();
      

      /* Pumpensteuerung   */
      loop_pumpensteuerung();
      //GEN 2
      my_pumpensteurung.loop_pumpensteuerung();
      my_stop.wire_loop();
      my_dfRobotLcdShield.DFRobot_loop_LCD();
      my_pumpensteurung.loop_pumpensteuerung();

      
    
      /* Send Test SMS bei Knopf SELECT   */
      if(lcd_key==btnSELECT)       
      {
        
        if(GSM_ENABLE)
          send_SMS(F("Test2"));
      }
      
      /* Pumpe mit Tast ein   */
      if(lcd_key==btnUP)       
      {
        Status_Pumpe_On=true; Status_Pumpe_Off=false;   // Pumpe ein
      }
       /* Pumpe mit Taste aus   */
      if(lcd_key==btnDOWN)       
      {
        Status_Pumpe_On=false; Status_Pumpe_Off=true;   // Pumpe aus
      }
   
    
    
      /* GSM Shield auf SMS abfragen */
      char anser[128];                
      if(GSM_ENABLE)
      {
        /* Recieve SMS  */
        if (recieve_SMS(anser))
        {
          LCD(anser);
          /* Pump On  */
          if( anser[0] == '1')
          {            
            LCD("Pumpe On");
            Status_Pumpe_On=true; Status_Pumpe_Off=false;   // Pumpe ein
          }
          /* Pumpe Aus  */
          if( anser[0] == '0')
          {            
            LCD("Pumpe Aus");
            Status_Pumpe_On=false; Status_Pumpe_Off=true;   // Pumpe aus
          }
          /* Test SMS  */
          if( anser[0] == 't')
          {            
            LCD("Send Test");
            send_SMS("hello i got your message");
          }
          /* Status SMS  */
          if( anser[0] == 's')
          {
            LCD("Send Status");
            send_status_sms();
            Time_Stamp_next_SMS = millis() + Time_SMS_interval;
            Time_Stamp_last_test_SMS = millis();
          }
        }

        /* Intervall SMS Time_Stamp_last_test_SMS*/
        //if( millis() > Time_Stamp_next_SMS )
        if( millis() - Time_Stamp_last_test_SMS >  Time_SMS_interval)
        {
          send_status_sms();
          Time_Stamp_next_SMS = millis() + Time_SMS_interval;
          Time_Stamp_last_test_SMS = millis();
        }
    
    
      }/* ende GSM enable
      
      /* Stop Spannung abfragen */
      wire_loop(); /* Wire Loop Stop Spannung abfragen  */                 
     
      /* Text auf DFRobot_LCD_Output Display anzeigen */
      loop_LCD(); /*  Loop DFRobot_LCD_Output Shield  */
      //GEN 2

    
      /* Screen Display Managment. Zwischen verschieden Anzeigen wechseln  */
      if (millis() - screen_timmer > screen_display_time) 
      {
        screen_timmer = millis();
        screen_setup = true;
        screen++;  /* Nächster Bildschirm */                        
        if (screen > screen_numbers)  screen = 1;
      }
    
      /* Watchdog reset  */
      //__asm__ __volatile__ ("wdr");
      wdt_reset(); //WD Zähler auf 0
      wd_count = num_watch_dog_overflows;  //WD-Overflow-Zähler                 

       /* Debugg  */
      //looptime = millis()-loop_start;
      if(SERIAL_ENABLE && millis()-last_print>1000){


        Serial.println(millis()-loop_start); 
        last_print=millis();

      }
}
/* Ende Loop */


