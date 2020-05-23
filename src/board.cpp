#include "core_simulation.h"
#include "mydevices.h"
#include "environnement.h"


int main(){
  // creation d'une board
  Board esp8266;
  // achat des senseurs et actionneurs
  AnalogSensorTemperature temperature(0.0,DELAY,TEMP);
  AnalogSensorLuminosity lumiere(0.0,DELAY,LUM);
  AnalogSensorHumidity humidite(0.0,DELAY, HUM);
  AnalogSensorCO2 dioxyde(0.0,DELAY, DIOX);
  
  MoteurFenetre turbo(DELAY);
  Chauffage feu(DELAY);
  Ventilateur AirFrais(DELAY);
  Lampe Loupiote(DELAY);
  Arrosage Tuyau(DELAY);
  
  I2CActuatorScreen screen;
  
  // branchement des capteurs
  esp8266.pin(1,temperature);
  esp8266.pin(0,humidite);
  esp8266.pin(2,lumiere);
  esp8266.pin(3,dioxyde);
  
  // branchement des actionneurs
  esp8266.pin(4,turbo);
  esp8266.pin(5,feu);
  esp8266.pin(6,AirFrais);
  esp8266.pin(7,Loupiote);
  esp8266.pin(8,Tuyau);
  
  esp8266.i2c(1,screen);
  Environnement appartement;
  Plante cactus;
  
  // allumage de la carte
  esp8266.run();
  //Destructeurs a appeler ?
  return 0;
}


