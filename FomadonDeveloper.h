#ifndef FOMADONDEVELOPER_H
#define FOMADONDEVELOPER_H
#include "Film.h"

class FomadonDeveloper { 
    
  private:
    Film _film;   
    float _temperature = 1.0;                    //get auto
    float devTimeMultiplicator = 1.0;     //get
    
   
    long developmentTime;                //get
    long agitationInitialSeconds = 31;  //get
    long agitationSeconds = 10; //get
    int  agitationIntervalSeconds = 60; //get

    long totalTime; //get
    bool agitate = false;
  
  protected:
    String developerName;                  //get   
    void InterpolateCorrection(float temperature); 
     int timeCompensationPercentage = 0;    //get set

  public:    
    FomadonDeveloper();
    FomadonDeveloper(Film *film);
    FomadonDeveloper(Film *film, float temperature);   
      
    // Factory Method
    static FomadonDeveloper* Create(int devType); 
    Film getFilm();       
    void setFilm(Film *film);
    void setTimeCompensationPercentage (int timeCompensationPercentage);    
    long getAgitationInitialSeconds();
    long getAgitationSeconds();  
    int getAgitationIntervalSeconds();
    float getTemperature();
    void setTemperature(float temperature);   
    float getDevTimeMultiplicator();
    virtual String getDeveloperName() = 0;  
    virtual int getTimeCompensationPercentage () = 0;
    virtual long getTotalTime() = 0;
    virtual long getDevelopmentTime() = 0;
};
 
#endif

