#include "automatic_traject.h"
#include "controls.h"
#include <Arduino.h>
#include <SoftwareSerial.h>
#include <MeSerial.h>
// #include <MeMegaPi.h>

// Singletons
LinkedList<Action> ACTION_PILE = LinkedList<Action>();
Graph AIRPORT_GRAPH = init_airport_graph();

unsigned char read[128] = {0}; //reçoit data

int counter=0; //0=accueil 1=manuel 2=automatique
int i, count =0; //pour parcourir data, pour remplir data
int data=-1;
int read_var = -1;
Node depart = "";
Node arrivee = "";
bool launched = false;

void setup() {
  Serial.begin(9600);
  colorsensor_8.SensorInit();
  colorsensor_8.TurnOnLight();
  // AIRPORT_GRAPH.print();

  Serial3.begin(115200);
  // bluetooth.begin(115200);    //essayer à 115200 si jamais ça ne marche pas (default)
  Serial.println("Bluetooth Start!");
  do
  {
    read_var = appel_bluetooth();
  }
  while(read_var < 0);
  launched = false;
}

int appel_bluetooth() //lecture message
{
  obstacle();
   if (Serial3.available())//si bluetooth libre
  {
    // Serial.println("disponible");

    while((data = Serial3.read()) != (int)-1) //tant que non vide 
    {
      read[count] = data - 48;//traduction ASCII
      Serial.println("Data : ");
      Serial.println(read[count]);
      if((read[count] > -1) && (read[count] < 12))//verif si info logique
      {
        //Serial.println("Reçu");
        // count++; //on pourrait faire un historique
        delay(1);
        return read[count];
      }
      else      {
        //Serial3.write(0);
        Serial.println("Pas de sens");
      }
    }
     Serial.println(read[count]);
  }
  return -1;
}

void loop() {
  switch(counter)
  {
    case 0: //------accueil ------------
      Serial.println("Accueil");
      read_var = -1;
      do
      {
        read_var = appel_bluetooth();
      }
      while(read_var < 0);
      switch (read_var)
      {
        case 1:
          counter = 1; //go mode manuel
          Serial.println("Manuel");
          break;
        case 2:
          counter = 2; //go mode automatique
          break;
      }
    break;
    case 1: //--------mode manuel --------------
      read_var = -1;
      do
      {
        read_var = appel_bluetooth();
      }
      while(read_var < 0);
      switch(read[count]) //attention, si erreur dans appel_bluetooth(), prendra le dernier nombre entré
      {
        case 1 : //tout droit 
          tout_droit_manuel();
        break;
        case 2 : //droite
          virage_droit_manuel();
        break;
        case 3 : //arrière
          arriere_manuel();
        break;
        case 4 : //gauche
          virage_gauche_manuel();
        break;
        case 5 : //stop
          STOP();
        break;
        case 6 : //ouvrir pince
          ouvrir_pince_manuel();
        break;
        case 7 : //fermer pince
          fermer_pince_manuel();
        break;
        case 0 : //retour accueil
          counter =0;
        break;
      }
    break;

    case 2: //---------mode auto ----------
      read_var = -1;
      Serial.println(launched);
      do
      {
        if(launched)
        {
          ACTION_PILE = exec_auto(ACTION_PILE);
        }
        read_var = appel_bluetooth();
      }
      while(read_var < 0);
      switch(read[count]) //attention, si erreur dans appel_bluetooth(), prendra le dernier nombre entré
      {
        case 0: //retour accueil
          counter = 0;
          ACTION_PILE.Clear();
          launched = false;
        break;
        case 1: //clear
          depart = "";
          arrivee = "";
          ACTION_PILE.Clear();
          launched = false;
        break;
        case 2: //launch
          if(depart!="" && arrivee!="")
          {
              ACTION_PILE = add_auto_path("P0", (Node)depart, AIRPORT_GRAPH, ACTION_PILE);
              ACTION_PILE = add_auto_path((Node)depart, (Node)depart+"p", AIRPORT_GRAPH, ACTION_PILE);
              ACTION_PILE = add_auto_path((Node)depart+"p", (Node)arrivee, AIRPORT_GRAPH, ACTION_PILE);
              ACTION_PILE = add_auto_path((Node)arrivee, "P0", AIRPORT_GRAPH, ACTION_PILE);
              launched = true;
              tout_droit_manuel();
              delay(1000);
              // Serial.println("cas 1");
          }
          else if(arrivee!="" && depart=="")
          {
            ACTION_PILE = add_auto_path((Node)arrivee, "P0", AIRPORT_GRAPH, ACTION_PILE);
            launched = true;
            // Serial.println("cas 2");
          }
          else if (depart!="" && arrivee=="")
          {
            ACTION_PILE = add_auto_path("P0", (Node)depart, AIRPORT_GRAPH, ACTION_PILE);
            ACTION_PILE = add_auto_path((Node)depart, (Node)depart+"p", AIRPORT_GRAPH, ACTION_PILE);
            tout_droit_manuel();
            delay(1000);
            launched = true;
            // Serial.println("cas 3");
          }
          else
          {
            // launched = true;
            Serial.println("Missing info");
          }
        break;
        case 3:
          STOP();
          // ACTION_PILE.Clear();
          launched = false;
        break;
        case 4: //N6
          depart = "N6";
        break;
        case 5: //N8
          depart = "N8";
        break;
        case 6: //M8
          depart = "N8";
        break;
        case 7: //M10
          depart = "M10";
        break;
        case 8: //M11
          depart="M11";
        break;
        case 9: //P1
          arrivee = "P1";
        break;
        case 10: //P2
          arrivee = "P2";
        break;
        case 11: //P3
          arrivee = "P3";
        break;
        case 12: //mode manuel
          counter = 1;
        break;
      }
    break;
  }
}