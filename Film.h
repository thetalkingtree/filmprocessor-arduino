#ifndef FILM_H
#define FILM_H
#include <Arduino.h>
class Film {
  
  private:
    String fcode;
    String name;
    int speed;
    int pushByStops = 0;
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
