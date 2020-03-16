//
// Created by andi on 05.03.2020.
//

#ifndef INC_200224_141205_UNO_DFROBOT_LCD_SHIELD_H
#define INC_200224_141205_UNO_DFROBOT_LCD_SHIELD_H

#include <LiquidCrystal.h>

#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5

//GEN 1
int read_LCD_buttons();       // read the buttons
void setup_LCD();             // DFRobot_LCD_Output Setup
void loop_LCD();              // DFRobot_LCD_Output Loop
void LCD (char* s);           // DFRobot_LCD_Output Output
void LCD (const __FlashStringHelper* s);  //DFRobot_LCD_Output Output

//GEN 2
class DFRobot_LCD_Shield : public LiquidCrystal
{
public:

    //lcd (8, 9, 4, 5, 6, 11);
    //a.l. Pin 11! nicht Pin 7 (von GSM-Shield verwendet
    DFRobot_LCD_Shield(uint8_t rs, uint8_t enable, uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3
                      ,uint8_t analog_read_pin);




    int DFRobot_read_LCD_buttons();       // read the buttons
    void DFRobot_setup_LCD();             // DFRobot_LCD_Output Setup
    void DFRobot_loop_LCD();              // DFRobot_LCD_Output Loop
    void DFRobot_LCD_Output (char* s);           // DFRobot_LCD_Output Output
    void DFRobot_LCD_Output (const __FlashStringHelper* s);  //DFRobot_LCD_Output Output

private:
    // define some values used by the panel and buttons
    int DFRobot_lcd_key     = 0;
    int DFRobot_adc_key_in  = 0;
    uint8_t  DFRobot_analog_read_pin;




};

#endif //INC_200224_141205_UNO_DFROBOT_LCD_SHIELD_H
