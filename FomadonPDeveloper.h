#ifndef FOMADONPDEVELOPER_H
#define FOMADONPDEVELOPER_H
#include "Film.h"
#include "FomadonDeveloper.h"

class FomadonPDeveloper : public FomadonDeveloper { 
  
  private:
   
    float _temperature = 1.0;  //If set to 1, the the temp is et to auto mode and is measured by a temp sensor
    float devTimeMultiplicator = 1.0; //Depends on configuration from the display menu         
    long totalTime; //Depends on configuration from the display menu
  
  protected:
    String developerName = "Fomadon P (D76)"; 

  public:        
    FomadonPDeveloper();
    FomadonPDeveloper(Film *film);
    FomadonPDeveloper(Film *film, float temperature);                          
    virtual String getDeveloperName(); 
    virtual int getTimeCompensationPercentage();
    virtual long getTotalTime();
    virtual long getDevelopmentTime();
};
 
#endif