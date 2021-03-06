#define PIN_HUMIDITE 10
#define PIN_TEMPERATURE 9
#define PIN_LUMIERE 11
#define PIN_CO2 12
#define PIN_CHAUFFAGE 5
#define PIN_VENTILATEUR 6
#define PIN_FENETRE 4
#define PIN_ARROSAGE 8
#define PIN_LAMPE 7

#include <unistd.h>
#include "core_simulation.h"
#include "mydevices.h"
#include "environnement.h"


// la fonction d'initialisation d'arduino
void Board::setup(){
  // on configure la vitesse de la liaison
  Serial.begin(9600);
// on fixe les pin en entree et en sortie en fonction des capteurs/actionneurs mis sur la carte
  pinMode(PIN_TEMPERATURE,INPUT);
  pinMode(PIN_HUMIDITE,INPUT);
  pinMode(PIN_LUMIERE,INPUT);
  pinMode(PIN_CO2,INPUT);

  pinMode(PIN_FENETRE,OUTPUT);
  pinMode(PIN_CHAUFFAGE,OUTPUT);
  pinMode(PIN_VENTILATEUR,OUTPUT);
  pinMode(PIN_LAMPE,OUTPUT);
  pinMode(PIN_ARROSAGE,OUTPUT);
  
  //initialiser les actionneurs a 0, sinon ils font n'importe quoi :(
  analogWrite(PIN_FENETRE, 0);
  analogWrite(PIN_CHAUFFAGE, 0); 
  analogWrite(PIN_VENTILATEUR, 0);
  digitalWrite(PIN_LAMPE, 0);
  digitalWrite(PIN_ARROSAGE, 0);

}

// la boucle de controle arduino
void Board::loop(){
	Plante *cactus=new Plante;
	bool Vivant;
	char buf[1000];
	int val_t, val_h, val_l, val_c;


 for(int i=0;i<100;i++){ 
	 
	 //initialisation
	 bool *MemoireLampe=new bool ;
	 *MemoireLampe= false;
	  int *CommandTab=new int[5];
	  int *TauxHum = new int;
	  int *TauxTemp = new int;
	  *TauxHum=0;
	  *TauxTemp=0;
	  for (int j=0;j<5;j++){
		  CommandTab[j]=0;
	  }

	  //recuperation valeurs capteurs
	  val_t=analogRead(PIN_TEMPERATURE);
	  val_h=analogRead(PIN_HUMIDITE);
	  val_l=analogRead(PIN_LUMIERE);
	  val_c=analogRead(PIN_CO2);

	  //Affichage valeurs environnement
	  
	  cout<<endl;
      sprintf(buf," Temperature : %d °C \n           Humidite : %d pour 100 \n           Luminosite : %d kilolux \n           CO2 : %d pour 1 0000",val_t, val_h,val_l, val_c);
      bus.write(1,buf,1000);

	      
	  //HappySeed :: main
      Vivant = HappySeed ::main(val_t, val_h, val_l, val_c, TauxHum, TauxTemp, cactus,CommandTab, MemoireLampe);
      if (!(Vivant)){
    	cout <<"Adieu la plante, vous n'avez pas la main verte !"<<endl;
    	exit(-1);
      }
      else {

    	//il y a toujours le meme nombre d'actions, une par actionneur. L'action peut etre d'eteindre l'actionneur
    	//ou de l'allumer ("le laisser tel qu'il est" = un de ces deux cas). Il reste alors a transmettre la valeur a ecrire
    	// Pour cela, on utilise le tableau suivant :
    	
        /*
         * CommandTab : tableau d'entiers de la meme taille que le nb de capteurs.
         * CommandTab[0] -> fenetre. 			Valeurs : entre 0 et 50
         * CommandTab[1] -> chauffage			Valeurs : entre 0 et 10
         * CommandTab[2] -> ventilateur			Valeurs : entre 0 et 10
         * CommandTab[3] ->	lampe				Valeurs : 0 ou 1
         * CommandTab[4] ->	arrosage			Valeurs : 0 ou 1
         * */

    	  cout <<"Tableau actionneur :";	//apercu rapide du contenu des consignes
    	  for (int i=0;i<5;i++){
    		  cout<<CommandTab[i]<<" ";
    	  }
		cout<<endl;
		cout <<endl;
		analogWrite(PIN_FENETRE, CommandTab[0]); 		
		analogWrite(PIN_CHAUFFAGE, CommandTab[1]);		
		analogWrite(PIN_VENTILATEUR, CommandTab[2]); 	
		analogWrite(PIN_LAMPE, CommandTab[3]); 			
		digitalWrite(PIN_ARROSAGE, CommandTab[4]);		
	
		delete CommandTab;
		delete TauxHum ;
		delete TauxTemp ;
		sleep(3);
	
	  }
  }

}


