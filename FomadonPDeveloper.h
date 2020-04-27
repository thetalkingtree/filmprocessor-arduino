#ifndef FOMADONPDEVELOPER_H
#define FOMADONPDEVELOPER_H
#include "Film.h"
#include "FomadonDeveloper.h"

class FomadonPDeveloper : public FomadonDeveloper { 
  
  private:
   
    float _temperature = 1.0;           //get
    float devTimeMultiplicator = 1.0;   //get            
    long totalTime; //get
  
  protected:
    String developerName; //get    

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