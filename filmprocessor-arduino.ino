// *********************************************************************
// includes
// *********************************************************************

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <LCDMenuLib2.h>
#include "FomadonPDeveloper.h"
#include <AccelStepper.h>
#include <MultiStepper.h>

//*********************************************************************
//Temp sensor settings
//*********************************************************************
#define aref_voltage 1.0567 // we tie 1.1V to ARef and measure it with a multimeter!
//TMP36 Pin Variables
int tempPin = A2; //the analog pin the TMP36's Vout (sense) pin is connected to   
float tempC; // Celsius             

// *********************************************************************
// LCDML display settings
// *********************************************************************
// settings for LCD
#define _LCDML_DISP_cols 20
#define _LCDML_DISP_rows 4

#define _LCDML_DISP_cfg_cursor 0x7E // cursor Symbol
#define _LCDML_DISP_cfg_scrollbar 1 // enable a scrollbar

// LCD object
LiquidCrystal_I2C lcd(0x3F, _LCDML_DISP_cols, _LCDML_DISP_rows);

const uint8_t scroll_bar[5][8] = {
    {B10001, B10001, B10001, B10001, B10001, B10001, B10001, B10001}, // scrollbar top
    {B11111, B11111, B10001, B10001, B10001, B10001, B10001, B10001}, // scroll state 1
    {B10001, B10001, B11111, B11111, B10001, B10001, B10001, B10001}, // scroll state 2
    {B10001, B10001, B10001, B10001, B11111, B11111, B10001, B10001}, // scroll state 3
    {B10001, B10001, B10001, B10001, B10001, B10001, B11111, B11111}  // scrollbar bottom
};

// *********************************************************************
// Prototypes
// *********************************************************************
void lcdml_menu_display();
void lcdml_menu_clear();
void lcdml_menu_control();

// *********************************************************************
// Global variables
// *********************************************************************
// Motor pin definitions for stepper motor:
#define motorPin1  52 // IN1 on the ULN2003 driver
#define motorPin2  50 // IN2 on the ULN2003 driver
#define motorPin3  48 // IN3 on the ULN2003 driver
#define motorPin4  46 // IN4 on the ULN2003 driver

//Motor type interface for the accel stepper lib
#define MotorInterfaceType 4

//Global variable, for the seelcted film
Film gFilm;
//Global variable for the selected developer
FomadonDeveloper *gFilmDeveloper;
//Initialize the stepper
AccelStepper stepper = AccelStepper(MotorInterfaceType, motorPin4, motorPin2, motorPin3, motorPin1);

// *********************************************************************
// Program menu
// *********************************************************************
LCDMenuLib2_menu LCDML_0(255, 0, 0, NULL, NULL); // root menu element (do not change)
LCDMenuLib2 LCDML(LCDML_0, _LCDML_DISP_rows, _LCDML_DISP_cols, lcdml_menu_display, lcdml_menu_clear, lcdml_menu_control);

LCDML_add(0, LCDML_0, 1, "Parameter setup", NULL);
LCDML_addAdvanced(1, LCDML_0_1, 1, NULL, "Film", NULL, 0, _LCDML_TYPE_default); 
LCDML_addAdvanced(2, LCDML_0_1_1, 1, NULL, "Fomapan 100", mFunc_param_film, 1, _LCDML_TYPE_default); 
LCDML_addAdvanced(3, LCDML_0_1_1, 2, NULL, "Fomapan 200", mFunc_param_film, 2, _LCDML_TYPE_default); 
LCDML_addAdvanced(4, LCDML_0_1_1, 3, NULL, "Fomapan 320", mFunc_param_film, 3, _LCDML_TYPE_default); 
LCDML_addAdvanced(5, LCDML_0_1_1, 4, NULL, "Fomapan 400", mFunc_param_film, 4, _LCDML_TYPE_default); 
LCDML_add(6, LCDML_0_1_1, 5, "Back", mFunc_back); 

LCDML_add(7, LCDML_0_1, 2, "Developer", NULL); 
LCDML_addAdvanced(8, LCDML_0_1_2, 1, NULL, "Fomadon P (D76)", mFunc_param_developer,1, _LCDML_TYPE_default);   
LCDML_addAdvanced(9, LCDML_0_1_2, 2, NULL, "Fomadon xcel(XTol)", mFunc_param_developer, 2, _LCDML_TYPE_default); 
LCDML_addAdvanced(10, LCDML_0_1_2, 3, NULL,"Fomadon R09", mFunc_param_developer, 3,_LCDML_TYPE_default); 
LCDML_add(11, LCDML_0_1_2, 4, "Back", mFunc_back); 

LCDML_add(12, LCDML_0_1, 3, "Temperature", NULL);
LCDML_addAdvanced(13, LCDML_0_1_3, 1, NULL, "Auto C", mFunc_param_temperature, 1, _LCDML_TYPE_default); 
LCDML_addAdvanced(14, LCDML_0_1_3, 2, NULL, "16 C", mFunc_param_temperature, 16, _LCDML_TYPE_default);       
LCDML_addAdvanced(15, LCDML_0_1_3, 3, NULL, "18 C", mFunc_param_temperature, 18, _LCDML_TYPE_default);       
LCDML_addAdvanced(16, LCDML_0_1_3, 4, NULL, "20 C", mFunc_param_temperature, 20, _LCDML_TYPE_default);       
LCDML_addAdvanced(17, LCDML_0_1_3, 5, NULL, "22 C", mFunc_param_temperature, 22, _LCDML_TYPE_default);      
LCDML_addAdvanced(18, LCDML_0_1_3, 6, NULL, "24 C", mFunc_param_temperature, 24, _LCDML_TYPE_default);       
LCDML_addAdvanced(19, LCDML_0_1_3, 7, NULL, "26 C", mFunc_param_temperature, 26, _LCDML_TYPE_default);       
LCDML_add(20, LCDML_0_1_3, 8, "Back", mFunc_back); 

LCDML_add(21, LCDML_0_1, 4, "Time compensation", NULL);
LCDML_addAdvanced(22, LCDML_0_1_4, 1, NULL, "0%", mFunc_param_compensation, 0, _LCDML_TYPE_default);        
LCDML_addAdvanced(23, LCDML_0_1_4, 2, NULL, "+5%", mFunc_param_compensation, 5, _LCDML_TYPE_default);        
LCDML_addAdvanced(24, LCDML_0_1_4, 3, NULL, "+10%", mFunc_param_compensation, 10, _LCDML_TYPE_default);       
LCDML_addAdvanced(25, LCDML_0_1_4, 4, NULL, "+15%", mFunc_param_compensation, 15, _LCDML_TYPE_default);       
LCDML_addAdvanced(26, LCDML_0_1_4, 5, NULL, "+20%", mFunc_param_compensation, 20, _LCDML_TYPE_default);        
LCDML_addAdvanced(27, LCDML_0_1_4, 6, NULL, "+25%", mFunc_param_compensation, 25, _LCDML_TYPE_default);       
LCDML_addAdvanced(28, LCDML_0_1_4, 7, NULL, "+30%", mFunc_param_compensation, 30, _LCDML_TYPE_default);       
LCDML_addAdvanced(29, LCDML_0_1_4, 8, NULL, "+35%", mFunc_param_compensation, 35, _LCDML_TYPE_default);       
LCDML_addAdvanced(30, LCDML_0_1_4, 9, NULL, "+40%", mFunc_param_compensation, 40, _LCDML_TYPE_default);       
LCDML_addAdvanced(31, LCDML_0_1_4, 10, NULL, "+45%", mFunc_param_compensation, 45, _LCDML_TYPE_default);       
LCDML_addAdvanced(32, LCDML_0_1_4, 11,NULL, "+50%", mFunc_param_compensation, 50, _LCDML_TYPE_default);      
LCDML_addAdvanced(33, LCDML_0_1_4, 12,NULL, "+55%", mFunc_param_compensation, 55, _LCDML_TYPE_default);      
LCDML_addAdvanced(34, LCDML_0_1_4, 14,NULL, "+60%", mFunc_param_compensation, 60, _LCDML_TYPE_default);       
LCDML_addAdvanced(35, LCDML_0_1_4, 15,NULL, "+133% 1 push Tmax", mFunc_param_compensation, 133, _LCDML_TYPE_default);       
LCDML_addAdvanced(36, LCDML_0_1_4, 16,NULL, "+140% 1 push comp", mFunc_param_compensation, 140, _LCDML_TYPE_default);      
LCDML_addAdvanced(37, LCDML_0_1_4, 17,NULL, "+150% 1 stop push", mFunc_param_compensation, 150, _LCDML_TYPE_default);      
LCDML_addAdvanced(38, LCDML_0_1_4, 18,NULL, "+160%", mFunc_param_compensation, 166, _LCDML_TYPE_default);      
LCDML_addAdvanced(39, LCDML_0_1_4, 19,NULL, "+166% 3 push Tmax", mFunc_param_compensation, 166, _LCDML_TYPE_default);      
LCDML_addAdvanced(40, LCDML_0_1_4, 20,NULL, "+170%", mFunc_param_compensation, 166, _LCDML_TYPE_default);      
LCDML_addAdvanced(41, LCDML_0_1_4, 21,NULL, "+185% 2 push comp", mFunc_param_compensation, 185, _LCDML_TYPE_default);      
LCDML_addAdvanced(42, LCDML_0_1_4, 22,NULL, "+225% 2 stop push", mFunc_param_compensation, 225, _LCDML_TYPE_default);      
LCDML_addAdvanced(43, LCDML_0_1_4, 23,NULL, "+250% 3 push comp", mFunc_param_compensation, 250, _LCDML_TYPE_default);       
LCDML_addAdvanced(44, LCDML_0_1_4, 24,NULL, "+450% 3 stop push", mFunc_param_compensation, 450, _LCDML_TYPE_default);      
LCDML_add(45, LCDML_0_1_4, 25, "Back", mFunc_back);

LCDML_add(46, LCDML_0_1, 5, "Back", mFunc_back);

LCDML_add(47, LCDML_0, 2, "Customize process", NULL);
LCDML_add(48, LCDML_0_2, 1, "Presoak 4 min", mFunc_presoak);
LCDML_add(49, LCDML_0_2, 2, "Develop only", mFunc_develop);
LCDML_add(50, LCDML_0_2, 3, "Fix", mFunc_fix);
LCDML_add(51, LCDML_0_2, 4, "B&W", NULL);       
LCDML_add(52, LCDML_0_2, 5, "C41", NULL);       
LCDML_add(53, LCDML_0_2, 6, "E6", NULL);         
LCDML_add(54, LCDML_0_2, 7, "Back", mFunc_back);

LCDML_add(55, LCDML_0, 3, "Caffenol", NULL);
LCDML_add(56, LCDML_0_3, 1, "Back", mFunc_back);

LCDML_add(57, LCDML_0, 4, "Start developing", mFunc_confirm_dev_setup);

// menu element count - last element id
// this value must be the same as the last menu element
#define _LCDML_DISP_cnt 57

// create menu
LCDML_createMenu(_LCDML_DISP_cnt);

// *********************************************************************
// SETUP
// *********************************************************************
void setup()
{
  // serial init; only be needed if serial control is used
  Serial.begin(9600);                // start serial
  analogReference(INTERNAL1V1);
  Serial.println(F("Semi auto film processor")); 
  
  stepper.setMaxSpeed(500);
  stepper.setAcceleration(480);
  stepper.moveTo(1200);
  stepper.setSpeed(500);

  // LCD Begin
  lcd.init();
  lcd.backlight();
 
  // set special chars for scrollbar
  lcd.createChar(0, (uint8_t *)scroll_bar[0]);
  lcd.createChar(1, (uint8_t *)scroll_bar[1]);
  lcd.createChar(2, (uint8_t *)scroll_bar[2]);
  lcd.createChar(3, (uint8_t *)scroll_bar[3]);
  lcd.createChar(4, (uint8_t *)scroll_bar[4]);

  // LCDMenuLib Setup
  LCDML_setup(_LCDML_DISP_cnt);

  // Enable Menu Rollover
  LCDML.MENU_enRollover();
}

// *********************************************************************
// LOOP
// *********************************************************************
void loop()
{
  LCDML.loop(); 
}
