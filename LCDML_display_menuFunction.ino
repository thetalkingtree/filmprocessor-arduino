long g_func_timer_info = 0;  // time counter (global variable)
unsigned long g_timer_1 = 0; // timer variable (global variable)
bool g_isAgitationStopped = false;
long g_agitationTime = 0;
bool g_isPresoak = true;

void mFunc_param_film(uint8_t param)
// *********************************************************************
{
  if (LCDML.FUNC_setup()) // ****** SETUP *********
  {
    LCDML.FUNC_setLoopInterval(100); // starts a trigger event for the loop function every 100 milliseconds
  }

  if (LCDML.FUNC_loop()) // ****** LOOP *********
  {
    // For example
    switch (param)
    {
    case 1:
      gFilm = Film("Fomapan", 100);
      break;

    case 2:
      gFilm = Film("Fomapan", 200);
      break;

    case 3:
      gFilm = Film("Fomapan", 320);
      break;

    case 4:
      gFilm = Film("Fomapan", 400);
      break;

    default:
      // do nothing
      break;
    }

    LCDML.OTHER_setCursorToID(7);
  }

  if (LCDML.FUNC_close()) // ****** CLEANUP *********
  {
    
  }
}

void mFunc_param_developer(uint8_t param)
// *********************************************************************
{
  if (LCDML.FUNC_setup()) // ****** SETUP *********
  {
    LCDML.FUNC_setLoopInterval(100); // starts a trigger event for the loop function every 100 milliseconds
  }

  if (LCDML.FUNC_loop()) // ****** LOOP *********
  {
    // For example
    switch (param)
    {
    case 1:
      gFilmDeveloper = FomadonDeveloper::Create(param);
      break;

    case 2:
      Serial.println(F("Fomadon excel (XTol)"));
      break;

    case 3:
      Serial.println(F("Fomadon R09"));
      break;

    default:
      // do nothing
      break;
    }

    gFilmDeveloper->setFilm(&gFilm);
    LCDML.OTHER_setCursorToID(12);
  }

  if (LCDML.FUNC_close()) // ****** CLEANUP *********
  {
    
  }
}

void mFunc_param_temperature(uint8_t param)
// *********************************************************************
{
  if (LCDML.FUNC_setup()) // ****** SETUP *********
  {
    LCDML.FUNC_setLoopInterval(100); // starts a trigger event for the loop function every 100 milliseconds
  }

  if (LCDML.FUNC_loop()) // ****** LOOP *********
  {
    gFilmDeveloper->setTemperature(param);
    LCDML.OTHER_setCursorToID(21);
  }

  if (LCDML.FUNC_close()) // ****** CLEANUP *********
  {
    
  }
}

void mFunc_param_compensation(uint8_t param)
// *********************************************************************
{
  if (LCDML.FUNC_setup()) // ****** SETUP *********
  {
    LCDML.FUNC_setLoopInterval(100); // starts a trigger event for the loop function every 100 milliseconds
  }

  if (LCDML.FUNC_loop()) // ****** LOOP *********
  {
    gFilmDeveloper->setTimeCompensationPercentage(param);
    LCDML.OTHER_setCursorToID(57);
  }

  if (LCDML.FUNC_close()) // ****** CLEANUP *********
  {
   
  }
}

// *********************************************************************
void mFunc_confirm_dev_setup(uint8_t param)
// *********************************************************************
{
  if (LCDML.FUNC_setup()) // ****** SETUP *********
  {
    LCDML.FUNC_setLoopInterval(100); // starts a trigger event for the loop function every 100 milliseconds

    lcd.setCursor(0, 0); // set LCD cursor pos
    lcd.print(gFilmDeveloper->getFilm().getFilmCode());
    lcd.setCursor(0, 1);
    lcd.print(gFilmDeveloper->getDeveloperName());
    lcd.setCursor(0, 2);
    lcd.print(F("Temperature :"));
    lcd.setCursor(13, 2);
    lcd.print(gFilmDeveloper->getTemperature());
    lcd.setCursor(18, 2);
    lcd.print(F("C"));
    lcd.setCursor(0, 3);
    lcd.print("Press OK to start");
  }

  if (LCDML.FUNC_loop()) // ****** LOOP *********
  {    
    LCDML.SCREEN_resetTimer();
    float currentTemp = 0;
    //Temp is set to auto, so measure and display continuously
    if (gFilmDeveloper->getTemperature() == 1)
    {
      lcd.setCursor(13, 2);
      lcd.print(checkTemperature());
    }

    if (LCDML.BT_checkEnter())
    {
      //If auto temp set measured temp
      if (gFilmDeveloper->getTemperature() == 1)
      {
        gFilmDeveloper->setTemperature(checkTemperature());
      }
      LCDML.OTHER_jumpToFunc(mFunc_presoak);
    }
  }

  if (LCDML.FUNC_close()) // ****** STABLE END *********
  {
  }
}

void mFunc_presoak(uint8_t param)
{
  if (LCDML.FUNC_setup()) // ****** SETUP *********
  {
    Serial.println(F("==========================================="));
    Serial.println(F("================ Presoak ===================="));
    Serial.println(F("==========================================="));
    Serial.println(F("Wait 4 minutes or press back button"));

    g_func_timer_info = 180; // reset and set timer
    g_agitationTime = g_func_timer_info;
    g_isAgitationStopped = false;
    g_isPresoak = true;
    LCDML.FUNC_setLoopInterval(0); // starts a trigger event for the loop function by CPU scan time
    LCDML.TIMER_msReset(g_timer_1);
    lcd.setCursor(0, 0); // set LCD cursor pos
    lcd.print(F("Presoak: "));
    printTimeFromSec(g_func_timer_info, 9, 0);
    printDevelopTemperature();    
  }

  if (LCDML.FUNC_loop()) // ****** LOOP *********
  {
    // reset screensaver timer
    LCDML.SCREEN_resetTimer();
    checkAgitate();
    // this method checks every 1000 milliseconds if it is called
    if (LCDML.TIMER_ms(g_timer_1, 1000))
    { 
      g_agitationTime--;
      g_func_timer_info--; // decrement the value every second
      if (g_func_timer_info < 0)
      {
        lcd.setCursor(0, 1); // set cursor pos
        lcd.print(F("Press OK to develop"));        
      }

      else
      {
        printTimeFromSec(g_func_timer_info, 9, 0);
      }
    }

    if (g_func_timer_info <= 0)
    {
      if (LCDML.BT_checkEnter())
      {
        LCDML.OTHER_jumpToFunc(mFunc_develop);
      }
    }
  }

  if (LCDML.FUNC_close()) // ****** CLEANUP *********
  {    
    g_isPresoak = false;    
  }
}

void mFunc_develop(uint8_t param)
// *********************************************************************
{
  if (LCDML.FUNC_setup()) // ****** SETUP *********
  {
    Serial.println(F("==========================================="));
    Serial.println(F("================  Develop ===================="));
    Serial.println(F("==========================================="));
    Serial.println(F("wait or press back button"));
    g_func_timer_info = gFilmDeveloper->getDevelopmentTime() / 1000; // reset and set timer
    g_agitationTime = gFilmDeveloper->getAgitationInitialSeconds();
    g_isAgitationStopped = false;

    LCDML.FUNC_setLoopInterval(0); // starts a trigger event for the loop function by CPU scan time
    LCDML.TIMER_msReset(g_timer_1);
    lcd.setCursor(0, 0); // set LCD cursor pos
    lcd.print(F("Develop: "));
    printTimeFromSec(g_func_timer_info, 9, 0);
    printDevelopTemperature();       
  }

  if (LCDML.FUNC_loop()) // ****** LOOP *********
  {   
    LCDML.SCREEN_resetTimer();
    checkAgitate();        
    // this method checks every 1000 milliseconds if it is called
    if (LCDML.TIMER_ms(g_timer_1, 1000))
    {
      
      g_func_timer_info--; // increment the value every second
      g_agitationTime--;

      if (g_func_timer_info < 0)
      {
        lcd.setCursor(0, 1); // set cursor pos
        lcd.print(F("Press OK to fix"));
        // leave this function
      }
      else
      {
        printTimeFromSec(g_func_timer_info, 9, 0);
      }
    }
    
    if (g_func_timer_info <= 0)
    {
      if (LCDML.BT_checkEnter())
      {
        LCDML.OTHER_jumpToFunc(mFunc_fix);
      }
    }
  }

  if (LCDML.FUNC_close()) // ****** CLEANUP *********
  {
   
  }
}

void mFunc_fix(uint8_t param)
// *********************************************************************
{
  if (LCDML.FUNC_setup()) // ****** SETUP *********
  {
    Serial.println(F("==========================================="));
    Serial.println(F("================  Fix ===================="));
    Serial.println(F("==========================================="));
    Serial.println(F("Wait 4 minutes or press back button"));
    g_func_timer_info = 240;       // reset and set timer
    g_isAgitationStopped = false;
    g_agitationTime = 15;

    LCDML.FUNC_setLoopInterval(0); // starts a trigger event for the loop function every CPU scan time   
    LCDML.TIMER_msReset(g_timer_1);
    lcd.setCursor(0, 0); // set LCD cursor pos
    lcd.print(F("Fix"));
    printTimeFromSec(g_func_timer_info, 9, 0);
    printDevelopTemperature();    
  }

  if (LCDML.FUNC_loop()) // ****** LOOP *********
  {   
    LCDML.SCREEN_resetTimer();   
    checkAgitate();        
    // this method checks every 1000 milliseconds if it is called
    if (LCDML.TIMER_ms(g_timer_1, 1000))
    {          
      g_func_timer_info--; // decrement the value every second
      g_agitationTime--;
      if (g_func_timer_info < 0)
      {
        lcd.setCursor(0, 1); // set cursor pos
        lcd.print(F("Press OK to finish"));        
      }
      else
      {
        printTimeFromSec(g_func_timer_info, 9, 0);
      }
    }
    
    if (g_func_timer_info <= 0)
    {
      if (LCDML.BT_checkEnter())
      {
        LCDML.MENU_goRoot();
      }     
    }
  }

  if (LCDML.FUNC_close()) // ****** CLEANUP *********
  {    
    developmentFinished();
  }
}

// *********************************************************************
void mFunc_back(uint8_t param)
// *********************************************************************
{
  if (LCDML.FUNC_setup()) // ****** SETUP *********
  {
    // end function and go an layer back
    LCDML.FUNC_goBackToMenu(1); // leave this function and go a layer back
  }
}

// *********************************************************************
void mFunc_goToRootMenu(uint8_t param)
// *********************************************************************
{
  if (LCDML.FUNC_setup()) // ****** SETUP *********
  {
    // go to root and display menu
    LCDML.MENU_goRoot();
  }
}

void printTimeFromSec(int allSeconds, int lcdCol, int lcdRow)
{
  char buf[20];
  int secsRemaining = allSeconds % 3600;
  int runHours = allSeconds / 3600;
  int runMinutes = secsRemaining / 60;
  int runSeconds = secsRemaining % 60;

  sprintf(buf, "%02d:%02d:%02d", runHours, runMinutes, runSeconds);
  lcd.setCursor(lcdCol, lcdRow);
  lcd.print(buf);
}

float checkTemperature()
{
   for (int x = 0; x < 256; x++) { // 255(max) analogue readings for averaging
    total = total + analogRead(tempPin); // add each value
  }

  //unsigned long average = total /257; //Slight temp calibration
  unsigned long average = total * 0.00389105;
  tempReading = average;
 
  Serial.print("Temp reading = ");
  Serial.print(tempReading);     // the raw analog reading
 
  // convert that reading to voltage, which is based off the reference voltage
  float voltage = tempReading * aref_voltage;
  voltage /= 1024.0; 
 
  // print out the voltage
  Serial.print(" - ");
  Serial.print(voltage); Serial.println(" volts");
 
  // now print out the temperature
  float temperatureC = (voltage - 0.5) * 100 ;  //converting from 10 mv per degree wit 500 mV offset
                                               //to degrees ((volatge - 500mV) times 100)
  Serial.print(temperatureC + 1.56); 
  Serial.println(" degrees C");   
  total = 0;
  return temperatureC + 1.56;

}

void stopAgitate()
{
  stepper.stop();
  stepper.setCurrentPosition(1200);
  stepper.setAcceleration(480);
  stepper.setMaxSpeed(500);
  stepper.setSpeed(500);
  g_isAgitationStopped = true;
}

void checkAgitate()
{
  //Inital agitation not executed yet
  if (!g_isAgitationStopped && g_agitationTime == gFilmDeveloper->getAgitationInitialSeconds())
  {
    g_isAgitationStopped = false;
  }

  //each 60 seconds
  else if (!g_isPresoak && (g_func_timer_info > 0) && (g_func_timer_info % gFilmDeveloper->getAgitationIntervalSeconds()) == 0 && (stepper.distanceToGo() == 0))
  {
    g_agitationTime = gFilmDeveloper->getAgitationSeconds();
    g_isAgitationStopped = false;
  }

  else
  {
  }

  if (g_agitationTime <= 0)
  {
    stopAgitate();
  }

  else
  {
    if (stepper.distanceToGo() == 0 && !g_isAgitationStopped)
    {
      stepper.moveTo(-stepper.currentPosition());
    }
  }
  stepper.run();
}

void developmentFinished()
{
  g_agitationTime == gFilmDeveloper->getAgitationInitialSeconds();
  stopAgitate();
}

void printDevelopTemperature()
{
    lcd.setCursor(0, 2);
    lcd.print(F("Dev. temp. :"));
    lcd.setCursor(13, 2);
    lcd.print(gFilmDeveloper->getTemperature());
    lcd.setCursor(18, 2);
    lcd.print(F("C"));
}

void printActualTemperature()
{
  lcd.setCursor(0, 3);
   lcd.print(F("Actual temp.:"));
    lcd.setCursor(13, 3);
    lcd.print(checkTemperature());
    lcd.setCursor(18, 3);
    lcd.print(F("C"));

}
