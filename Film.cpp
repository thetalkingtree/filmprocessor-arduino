  #include "Film.h"
  

Film::Film()
{

}

Film::Film(String name, int speed){
  this->name = name;
  this->speed = speed;
}

String Film::getFilmCode(){
  return this->name + this->speed;  
}

String Film::getName(){
  return this->name; 
}

int Film::getSpeed(){
  return this->speed;
}

int Film::getPushByStops(){   
  return this->pullByStops;
}

int Film::getPullByStops(){
  return this->pullByStops;
}

void Film::setPushByStops(int pushByStops){
  pushByStops +=1;
  this->pushByStops = pushByStops;
}

void Film::setPullByStops(int pullByStops){
  pullByStops +=1;
  this->pullByStops = pullByStops;
}
