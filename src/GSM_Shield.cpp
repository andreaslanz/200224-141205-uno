/*
 *   Arduino GSM Shield V2 für Ardunio
 *   kann SMS senden und empfangen
 */
#include <Arduino.h>
#include <main.h>
#include <GSM_Shield.h>

GSM gsmAccess;
GSM_SMS sms;


char senderNumber[20]; // Array to hold the number a SMS is retreived from

extern LiquidCrystal lcd;


void GSM_Init()           /* GSM Initialisierung
---------------           */
{
  LCD( F("GSM Intitialis.") );

  // connection state
  boolean notConnected = true;

  /* 
   *  Start GSM shield
   *  If your SIM has PIN, pass it as a parameter of begin() in quotes
   */
  
  while (notConnected)
  {
    if (gsmAccess.begin("") == GSM_READY)
    {
      notConnected = false;
      LCD( F("GSM initialized") );
    }
    else
    {
       LCD( F("Not connected") );
       delay(1000);
       
    }
  }
  
  
}

bool recieve_SMS(char* s)             /* SMS empfangen
-------------------------             */
{  
  char c;
  int count=0;
  if (sms.available())
  { 
    if(SERIAL_ENABLE)
      Serial.println(F("Message received from:"));

    // Get remote number
    sms.remoteNumber(senderNumber, 20);
    if(SERIAL_ENABLE)
      Serial.println(senderNumber);

    // An example of message disposal
    // Any messages starting with # should be discarded
    if (sms.peek() == '#')
    {
      if(SERIAL_ENABLE)
        Serial.println(F("Discarded SMS"));
      sms.flush();
    }
    /*
     * Read message bytes and print them
     */ 
    lcd.setCursor(0,0);             // set the DFRobot_LCD_Output cursor   position
    while (c = sms.read()){
      if(SERIAL_ENABLE) 
        Serial.print(c);
      s[count++]=c;
      lcd.write(c);
    }
    s[count]=0;

    if(SERIAL_ENABLE)
      Serial.println(F("\nEND OF MESSAGE"));

    // Delete message from modem memory
    sms.flush();
    if(SERIAL_ENABLE)
      Serial.println(F("MESSAGE DELETED"));
    return true;
  } 
  else
  {
    s[count]=0;
    return false;
  }
  
}

void send_SMS(const __FlashStringHelper* s)   /* SMS aus Flash senden
------------------------------------------    */
{

  LCD(F("Send SMS"));
  
  // send the message
  sms.beginSMS("0794118653");
  sms.print(s);
  sms.endSMS();
  
  LCD(F("Send COMPLETE!"));
    
  delay(1000);
}

void send_SMS(char s[])                        /* SMS Senden
----------------------                         */
{
  LCD(F("Send SMS"));
  
  // send the message
  sms.beginSMS("0794118653");
  sms.print(s);
  sms.endSMS();
  
  LCD(F("Send COMPLETE!"));
    
  delay(1000);
  
}

