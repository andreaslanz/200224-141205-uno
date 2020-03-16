#ifndef _pumpensteuerung_
#define _pumpensteuerung_

//#include <Arduino.h>
#include <stdint.h>
#include <WString.h>
#include <pins_arduino.h>

class PUMPENSTEUERUNG
{
public:
    PUMPENSTEUERUNG(uint8_t PIN_Power_OUT, uint8_t PIN_Schwimmer_IN);
    void setup_pumpensteuerung();
    char* loop_pumpensteuerung();
    void send_status_sms();
    void display();
private:
    String get_Min_Sec(long ms);       /* String MIN:SEC aus Zeit machen */
    String get_Hour_Min_Sec(long ms);  /* String Stunden:Minuten:Sec aus Milliseckunden machen */
    void Pumpe_Intervall();
    void print_to(int to, const __FlashStringHelper *s);
    /* Debuging */
    /* Enable GSM Messaging */

    /* Pin Definitionen */
    int schwimmerPin;     //Nummer des Eingangs des Schwimmer Schalters Pins
    int PumpePowerPin;   // Nummer des Eingangs des Pumpen Power Pins

    /* Debouncing */
    int schwimmerState = 1;  //Variable für Schwimmer-Schalter Status
    int schwimmerReading{};       //Spanung am Schwimer Eingang Pin
    int schwimemrLastReading{};   //Letzter gelesener Wert am Schwimmer Eingang
    long last_debounce_time_schwimmer{};  //Entprellung
    const long debounce_time=5000L;  

    /* Schrittkette Status Variablen */
    int Status_Wasser_leer = true;
    int Status_Wasser_voll = false;
    int Status_Pumpe_On   = false;
    int Status_Pumpe_Off =  true;
    int Status_send_SMS_kein_Wasser = false;
    int Status_send_SMS_Test = false;


    /* Timer Variablen */
    long       Time_Stamp_Pumpe_On= 0L;      //Zeit wenn Pumpe ein
    long       Time_Stamp_Pumpe_Off= 0L;     //Zeit wenn Pumpe aus
    const long Time_Pumpe_On= 30*1000L;      //Laufzeit der Pumpe 30 sec
    const long Time_Pumpe_Off= 30L*60L*1000L;//Pause der Pumpe  30 min

    long       Time_Stamp_Wasser_voll{};        //Zeit seit der Schwimmer oben ist
    long       Time_Stamp_Wasser_leer{};        //Zeit seit der Schwimmer unten ist
    long       Time_Total_Wasser_leer= 0L;    //Gesamtzeit Schimmer unten
    long       Time_schwimmer_down=0L;        //Aktuelle Zeit in Sec. wo Schwimmer unten ist
    long       Temp_Time_Schwimmer_down=0L;    //= Time_schwimmer_down/1000 + Time_Total_Wasser_leer
    long       Total_Time_Waser_leer_array[25]{}; //Array mit Stündlichen total Zeiten Schwimmer unten
    int        Time_Total_Wasser_leer_last_24_houer=0;  //Total Zeit Schwimmer unten in letzten 24 Stunden
    int        Counter_Schimmer_Down=0;        //wie oft ging der Schwimmer nach unten

    const long Time_Leer_to_SMS= 2*60L*60L*1000L;    //nach welcher Zeit seit Wanne leer wird SMS gesendet 2std.
    long       Time_Stamp_last_test_SMS{};             //wann wurde letzte Test-SMS gesendet;
    long       Time_Stamp_next_SMS{};                  // Nächste SMS
    const long Time_SMS_interval= 86400000L; //24L*60L*60L*1000L; // Status SMS senden Interval 24 Stunden

    long       Time_Stamp_next_houer{};          //Stundenzähler
    long       Time_Stamp_last_houer{};          //Stundenzähler
    int        houer=0;                       //Aktuelle Stunde
    const long Time_one_houer = 60L*60L*1000L; //1 Std. in ms



};



#endif
