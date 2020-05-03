#ifndef FILM_H
#define FILM_H
#include <Arduino.h>

/*
 * This is the Film object class
 * Contains only getters and setters
*/
class Film {
  
  private:
    //Film code, for example Fomapan100
    String fcode;
    //Film name for example Fomapan
    String name;
    //Film speed ,for example 100
    int speed;
    //Incicator, by how much we want to push the given film
    int pushByStops = 0;
    //Incicator, by how much we want to pull the given film
    int pullByStops = 0;
    
  public:    
    Film();
    Film(String name, int speed);
    String getFilmCode();         
    String getName();        
    int getSpeed();
    int getPushByStops();
    void setPushByStops(int pushByStops);
    int getPullByStops();
    void setPullByStops(int pullByStops);  
};   

#endif
