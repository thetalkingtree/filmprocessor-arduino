#include "FomadonPDeveloper.h"
    
    FomadonPDeveloper::FomadonPDeveloper()
    {
        developerName = "Fomadon P (D76)";
    }
    
    FomadonPDeveloper::FomadonPDeveloper(Film *film) : FomadonDeveloper(film){        
        developerName = "Fomadon P (D76)";
    };

    FomadonPDeveloper::FomadonPDeveloper(Film *film, float temperature) : FomadonDeveloper(film, temperature){        
        developerName = "Fomadon P (D76)";
    };

    String FomadonPDeveloper::getDeveloperName()
    {
        return FomadonPDeveloper::developerName;
    }

    int FomadonPDeveloper::getTimeCompensationPercentage ()
    {
        return timeCompensationPercentage;
    }

    long FomadonPDeveloper::getTotalTime()
    {
        return 0;
    }
    
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

        if(filmCode == "Fomapan200")
        {
            //10:30 minutes            
            long devTime = 630000 * getDevTimeMultiplicator();
            return devTime + (devTime * getTimeCompensationPercentage()/100);
        }        

        else return 0;                
    }
