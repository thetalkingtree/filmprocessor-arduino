#ifndef FOMADONDEVELOPER_H
#define FOMADONDEVELOPER_H
#include "Film.h"

class FomadonDeveloper { 
    
  private:
    Film _film;   
    float _temperature = 1.0; //If set to 1, the the temp is et to auto mode and is measured by a temp sensor
    float devTimeMultiplicator = 1.0; //Depends on configuration from the display menu
    
   
    long developmentTime; //Depends on configuration from the display menu                
    long agitationInitialSeconds = 31;  //From the Foma technical sheets
    long agitationSeconds = 10; ////From the Foma technical sheets
    int  agitationIntervalSeconds = 60; ////From the Foma technical sheets

    long totalTime; //Depends on configuration from the display menu
    bool agitate = false;
  
  protected:
    String developerName;  //Depends on configuration from the display menu   
    //Find the development time for an unlisted temperature in the technical sheets
    void InterpolateCorrection(float temperature); 
     int timeCompensationPercentage = 0; //Depends on configuration from the display menu   

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

