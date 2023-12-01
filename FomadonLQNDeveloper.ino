#include "FomadonLQNDeveloper.h"
        
    FomadonLQNDeveloper::FomadonLQNDeveloper(){        
    };
    
    FomadonLQNDeveloper::FomadonLQNDeveloper(Film *film) : FomadonDeveloper(film){                
    };

    FomadonLQNDeveloper::FomadonLQNDeveloper(Film *film, float temperature) : FomadonDeveloper(film, temperature){                
    };

    String FomadonLQNDeveloper::getDeveloperName()
    {
        return FomadonLQNDeveloper::developerName;
    }

    int FomadonLQNDeveloper::getTimeCompensationPercentage ()
    {
        return timeCompensationPercentage;
    }

    //TODO: Implement total processing time
    long FomadonLQNDeveloper::getTotalTime()
    {
        return 0;
    }
    
    /*
    *These values are from the foma technical sheet and if operating in auto mode, the 
    *temperature is measured wtih a temp sensor.
    *The tempereature is corrected by various parameters set on the display menu. (Push/pull...etc)
    */
     
    long FomadonLQNDeveloper::getDevelopmentTime()
    {
        String filmCode = FomadonLQNDeveloper::getFilm().getFilmCode();

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
            //10 minutes            
            long devTime = 600000 * getDevTimeMultiplicator();
            return devTime + (devTime * getTimeCompensationPercentage()/100);
        }        

        else return 0;                
    }
