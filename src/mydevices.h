#ifndef MYDEVICES_H
#define MYDEVICES_H

#include <fstream>
#include <iostream>
#include <thread>
#include <unistd.h>
#include <string.h>
#include "core_simulation.h"

//int global luminosite_environnement=LUM;

//////////////////////////// CLASSE CAPTEUR //////////////////////////////////////////
class Capteur : public Device{

protected :
	float alea ; //ecart entre les differentes valeurs mesurees
	int temps ; //temps ecoule entre deux mesures
	float val ; //valeur lue par le capteur

	
public :
	Capteur();
	Capteur(float a, int d, float v);
	float Get_val();
	void Set_val(float v) ; //sorte de reset




	//valeurs statiques avec les valeurs de l'environnement ?

};
//////////////////////////// CLASSE CAPTEUR DE LUMINOSITE //////////////////////////////////////////
class AnalogSensorLuminosity: public Capteur {
public :
	AnalogSensorLuminosity(float a, int d, float v);
	//int static luminosite_environnement;
	float Get_val();
	
	virtual void run();
			
	
};
//int AnalogSensorLuminosity::luminosite_environnement=LUM;


//////////////////////////// CLASSE CAPTEUR TEMPERATURE //////////////////////////////////////////
class AnalogSensorTemperature: public Capteur {
  
public:
  //constructeur
  AnalogSensorTemperature(float a, int d, float v);
  float Get_val();
  // thread representant le capteur et permettant de fonctionner independamment de la board
  virtual void run();
};


//////////////////////////// CLASSE CAPTEUR HUMIDITE //////////////////////////////////////////
class AnalogSensorHumidity: public Capteur {

public:
  //constructeur
  AnalogSensorHumidity (float a, int d, float v);
  // thread representant le capteur et permettant de fonctionner independamment de la board
  float Get_val();
  virtual void run();
};


//////////////////////////// CLASSE CAPTEUR CO2 //////////////////////////////////////////
class AnalogSensorCO2: public Capteur {

public:
  //constructeur
  AnalogSensorCO2 (float a, int d, float v);
  // thread representant le capteur et permettant de fonctionner independamment de la board
  float Get_val();
  virtual void run();
};



////////////////////////////CLASSE ACTIONNEUR ///////////////////////////////////////////////
class Actionneur : public Device {
protected :
	
	int temps;
	
public :
	Actionneur();
	Actionneur (int d);
};

////////////////////////////CLASSE LED /////////////////////////////////////////////
class LED: public Actionneur {
private:
  // etat de la LED
  int state;

  
public:
    // initialisation du temps de rafraichiisement
  LED(int t);
  // thread representant l'actionneur et permettant de fonctionner independamment de la board
  virtual void run();
  
  float read_lum();
  
  void set_lum(float v);
  
  void main();
};

////////////////////////////CLASSE MOTEUR /////////////////////////////////////////////
class Moteur: public Actionneur{
protected :
	int speed;
	int position;
	
public :
	Moteur();
	virtual void run();
	int read_speed();
	int read_position();
	
};


/////////////////////////////CLASSE VENTILATEUR //////////////////////////////////////////////////
//Ici la position n'est pas pertinente,on ne regarde que la vitesse
class Ventilateur : public Moteur{
	virtual void run();
	Ventilateur();
	void Write_speed(int sp);
	void main();
};


/////////////////////////////CLASSE CHAUFFAGE //////////////////////////////////////////////////
//Ici la position n'est pas pertinente,on ne regarde que la vitesse
class Chauffage : public Moteur{
	virtual void run();
	Chauffage();
	void Write_speed(int sp);
	void main();
};

/////////////////////////////CLASSE ARROSAGE //////////////////////////////////////////////////
//Ici la vitesse n'est pas pertinente,on ne regarde que la position
class Arrosage : public Moteur{
	virtual void run();
	Arrosage();
	void Write_pos(int sp);
	void main();
};


/////////////////////////////CLASSE OUVERTURE FENETRE //////////////////////////////////////////////////
//Ici la vitesse n'est pas pertinente,on ne regarde que la position
class Moteur_Fenetre : public Moteur{
	virtual void run();
	Moteur_Fenetre();
	void Write_pos(int sp);
	void main();
};



////////////////////////////EXEMPLES D'ACTUATORS /////////////////////////////////////////////
// exemple d'actionneur digital : une led, ne pas oublier d'heriter de Device
class DigitalActuatorLED: public Device {
private:
  // etat de la LED
  int state;
  // temps entre 2 affichage de l etat de la led
  int temps;
  
public:
    // initialisation du temps de rafraichiisement
  DigitalActuatorLED(int t);
  // thread representant l'actionneur et permettant de fonctionner independamment de la board
  virtual void run();
};

//LED intelligente (fille de LED ?)
class IntelligentDigitalActuatorLED: public Device{
private:
  // etat de la LED
  int state;
  // temps entre 2 affichage de l etat de la led
  int temps;
  
public:
    // initialisation du temps de rafraichiisement
  IntelligentDigitalActuatorLED(int t);
  // thread representant l'actionneur et permettant de fonctionner independamment de la board
  virtual void run();
	
};


// exemple d'actionneur sur le bus I2C permettant d'echanger des tableaux de caracteres : un ecran, ne pas oublier d'heriter de Device
class I2CActuatorScreen : public Device{
protected:
    // memorise l'affichage de l'ecran
  char buf[I2C_BUFFER_SIZE];
  
public:
  // constructeur
  I2CActuatorScreen ();
  // thread representant le capteur et permettant de fonctionner independamment de la board
  virtual void run();
};

//Bouton exterieur
class ExternalDigitalSensorButton: public Device {
	
public :
	ExternalDigitalSensorButton();
	
	int DetectButton();
	
	void run();
	
};


#endif
