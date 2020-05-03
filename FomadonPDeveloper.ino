#include "FomadonPDeveloper.h"
        
    FomadonPDeveloper::FomadonPDeveloper(){        
    }
    
    FomadonPDeveloper::FomadonPDeveloper(Film *film) : FomadonDeveloper(film){                
    };

    FomadonPDeveloper::FomadonPDeveloper(Film *film, float temperature) : FomadonDeveloper(film, temperature){                
    };

    String FomadonPDeveloper::getDeveloperName()
    {
        return FomadonPDeveloper::developerName;
    }

    int FomadonPDeveloper::getTimeCompensationPercentage ()
    {
        return timeCompensationPercentage;
    }

    //TODO: Implement total processing time
    long FomadonPDeveloper::getTotalTime()
    {
        return 0;
    }
    
    /*
    *These values are from the foma technical sheet and if operating in auto mode, the 
    *temperature is measured wtih a temp sensor.
    *The tempereature is corrected by various parameters set on the display menu. (Push/pull...etc)
    */
     
    long FomadonPDeveloper::getDevelopmentTime()
    {
        String filmCode = FomadonPDeveloper::getFilm().getFilmCode();

        if(filmCode == "Fomapan100")
        {
            //7:30 minutes
            long devTime = 450000 * getDevTimeMultiplicator();
            return devTime + (devTime * getTimeCompensationPercentage()/100);
        }

        if(filmCode == "Fomapan200")
        {
            //5:30 minutes
            long devTime = 330000 * getDevTimeMultiplicator();
            return devTime + (devTime * getTimeCompensationPercentage()/100);
        }

        if(filmCode == "Fomapan400")
        {
            //10:30 minutes            
            long devTime = 630000 * getDevTimeMultiplicator();
            return devTime + (devTime * getTimeCompensationPercentage()/100);
        }        

        else return 0;                
    }
