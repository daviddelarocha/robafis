// controls.h

#ifndef CONTROLS_H
#define CONTROLS_H

//------------------------------------------------------------PACKAGES-------------------------------------------------------------------------------

#include "MeColorSensor.h"
#include <Arduino.h>
#include <Wire.h>
#include <SoftwareSerial.h>
#include <MeMegaPi.h>
#include "LinkedList.h"

//------------------------------------------------------------INITIALISATION-------------------------------------------------------------------------------

// Déclaratiion des ports
MeLineFollower lineFinder(PORT_8);
MeUltrasonicSensor ultraSensor(PORT_7);  //Capt dist
MeMegaPiDCMotor motorP(PORT1A); // Pince
MeMegaPiDCMotor motorG(PORT1B); // Roue droite en regardant devant le robot
MeMegaPiDCMotor motorD(PORT3B); // roue gauche
MeColorSensor colorsensor_8(PORT_6);
int sensorState = lineFinder.readSensors(); // Declarer le capteur de ligne

//---------------------------------------------------------------DECLARATION_VARIABLES------------------------------------------------------------------------------

int debut=0 ; int fin=0; // TEMPO


// Variables couleurs
uint8_t couleur=BLACK; // Couleur retournée par le capteur //  couleur = colorsensor0.ColorIdentify();// BLANC=WHITE ... NOIR=BLUE=7 POUR LUI......ROUGE=RED...VERT=GREEN=5 YELLOW=4
uint8_t NR=0 ;  uint8_t NV=0; //Compteurs de nb de fois que l'on croise une couleur  

//Detect OBST
int DETECT=0 ; int OK_ARRIMAGE=0;

//------------------------------------------------------------------------------------------------

void STOP()   
{
 motorG.run(0); motorD.run(0);  // S1 et S2 = capteurs de presence ligne S1 a gauche
}

//-------------------------------------------------------------------


void tout_droit_manuel()
{
  motorG.run(40 *(255/100)); motorD.run(-47 *(255/100)); 
}

//------------------------------------------------------------------------------------------------

void AVANCE_PTPEU()
{
  tout_droit_manuel();
  delay(1000);
}

//-------------------------------------------------------------------

void virage_gauche_manuel()
{
  motorG.run(55 *(255/100)); motorD.run((55 *(255/100)));
}

//-------------------------------------------------------------------

void virage_droit_manuel()
{
  motorG.run(-55 *(255/100)); motorD.run(-55 * (255/100));
}

//-------------------------------------------------------------------

void arriere_manuel()
{
  motorG.run(-50 *(255/100)); motorD.run(57 *(255/100));
}

//-------------------------------------------------------------------

void fermer_pince_manuel()
{
   motorP.run(-255); delay(3 * 1000);  motorP.run(-0);
}

//-------------------------------------------------------------------

void ouvrir_pince_manuel()
{
  motorP.run(180); delay(2 * 1000); motorP.run(-0);
}

void ChercheLigne (){ // Cherche la ligne 
  while(sensorState == S1_OUT_S2_OUT ){
    motorG.run(60); motorD.run(60); delay(2000);
    if  (sensorState == S1_OUT_S2_OUT ){
      motorG.run(0); motorD.run(0); delay(1000);
      motorG.run(-60); motorD.run(-60); delay(2000);
    }
  }
}

//-------------------------------------------------------------------

int DETECT_COULEURS()
{  // BLANC=0 // ROUGE =2 // JAUNE=4 // VERT=5 // BLEU=7 // NOIR=9
// Couleur retournée par le capteur //  couleur = colorsensor0.ColorIdentify();// BLANC=WHITE ... NOIR=BLUE POUR LUI......ROUGE=RED...VERT=GREEN
  
  couleur = colorsensor_8.ColorIdentify();
  // Serial.print("\t");Serial.print("\r\n");  //INIT DES RETOURS CAPTEURS
  // switch (couleur){
  //   case 0 : Serial.print("BLANC"); break;
  //   case 2 : Serial.print("ROUGE"); break;
  //   case 4 : Serial.print("JAUNE"); break;
  //   case 5 : Serial.print("VERT"); break;
  //   case 7 : Serial.print("BLEU = NOIR"); break;
  //   case 9 : Serial.print("NOIR"); break;
  // }
  
  return couleur;
}

//-------------------------------------------------------------------
void obstacle ()
{
  while (ultraSensor.distanceCm() < 5)
  {
      STOP();
  }
}

void SUIVI_LIGNES()   // PROGRAMME BOUCLE SUIVI LIGNE    // SENS =1 = avant // SENS =0 = AR
{
  if (ultraSensor.distanceCm() > 4 && DETECT_COULEURS() != 4 && DETECT_COULEURS() != 5){
    sensorState = lineFinder.readSensors();
      switch(sensorState)
    {
      // case S1_IN_S2_IN:   motorG.run(42 *(255/100)); motorD.run(-49 *(255/100)); break; // S1 et S2 = capteurs de presence ligne S1 a gauche
      // case S1_OUT_S2_IN:  motorG.run(+25 *(255/100)); motorD.run(-50*(255/100)); break;  // tourne a droite
      // case S1_IN_S2_OUT:  motorG.run(55 *(255/100)); motorD.run(-(30 *(255/100))); break; // tourne a gauche 
      // case S1_OUT_S2_OUT: motorG.run(-45 *(255/100)); motorD.run(45 *(255/100)); break; // recule
      case S1_IN_S2_IN:   motorG.run(40 *(255/100)); motorD.run(-47 *(255/100)); break; // S1 et S2 = capteurs de presence ligne S1 a gauche
      case S1_OUT_S2_IN:  motorG.run(+25 *(255/100)); motorD.run(-60*(255/100)); break;  // tourne a droite
      case S1_IN_S2_OUT:  motorG.run(65 *(255/100)); motorD.run(-(30 *(255/100))); break; // tourne a gauche 
      case S1_OUT_S2_OUT: motorG.run(-45 *(255/100)); motorD.run(45 *(255/100)); break; // recule
      default: break;
    }
    // DETECT_COULEURS();// Detecter la couleur
  }
  else{  STOP();  }
}

void SUIVI_LIGNES_SLOW()   // PROGRAMME BOUCLE SUIVI LIGNE    // SENS =1 = avant // SENS =0 = AR
{
  if (ultraSensor.distanceCm() > 1 && DETECT_COULEURS() != 4 && DETECT_COULEURS() != 5){
    sensorState = lineFinder.readSensors();
      switch(sensorState)
    {
      case S1_IN_S2_IN:   motorG.run(40 *(255/100)); motorD.run(-47 *(255/100)); break; // S1 et S2 = capteurs de presence ligne S1 a gauche
      case S1_OUT_S2_IN:  motorG.run(+20 *(255/100)); motorD.run(-40*(255/100)); break;  // tourne a droite
      case S1_IN_S2_OUT:  motorG.run(45 *(255/100)); motorD.run(-(20 *(255/100))); break; // tourne a gauche 
      case S1_OUT_S2_OUT: motorG.run(-30 *(255/100)); motorD.run(37 *(255/100)); break; // recule
      default: break;
    }
    // DETECT_COULEURS();// Detecter la couleur
  }
  else{  STOP();  }
}


//---------------------------------------------------------------------------------------------------------------------------

void pass_intersection(int stop_counter, int end_delay)
{
  LinkedList<int> color_hist = LinkedList<int>();
  int color;
  int counter_color = 0;
  int stop_color = 9; // NOIR
  int skip_color = 0; // BLANC
  int ignore_color = 7; // BLEU
  // pass lines
  do
  {
    sensorState = lineFinder.readSensors();
    switch(sensorState)
    {
      case S1_IN_S2_IN:   motorG.run(38 *(255/100)); motorD.run(-45 *(255/100)); break; // S1 et S2 = capteurs de presence ligne S1 a gauche
      case S1_OUT_S2_IN:  motorG.run(+25 *(255/100)); motorD.run(-50*(255/100)); break;  // tourne a droite
      case S1_IN_S2_OUT:  motorG.run(45 *(255/100)); motorD.run(-(30 *(255/100))); break; // tourne a gauche
      // case S1_IN_S2_IN:   motorG.run(40 *(255/100)); motorD.run(-47 *(255/100)); break; // S1 et S2 = capteurs de presence ligne S1 a gauche
      // case S1_OUT_S2_IN:  motorG.run(+25 *(255/100)); motorD.run(-60*(255/100)); break;  // tourne a droite
      // case S1_IN_S2_OUT:  motorG.run(65 *(255/100)); motorD.run(-(25 *(255/100))); break; // tourne a gauche 
      default: break;
    }
    color = DETECT_COULEURS();
    if(color != skip_color)
    {
      if(color_hist.getLength() == 0)
      {
        color_hist.Append(color);
        if(color == stop_color)
          counter_color++;
      } else
      {
        if(color_hist.getCurrent() != color)
        {
          if(
            (color == stop_color && color_hist.getCurrent() != ignore_color) ||
            (color == ignore_color && color_hist.getCurrent() != stop_color)
          )
          {
            // color_hist.Append(color);
            counter_color++;
          }
          else if(color != stop_color && color != ignore_color)
          {
            color_hist.Append(color);
          }
          color_hist.moveToEnd();
        }
        Serial.println(counter_color);
      }
    }
  } while(counter_color < stop_counter && color_hist.getLength() < (stop_counter * 2) - 1);
  // motorG.run(40 *(255/100)); motorD.run(-47 *(255/100));
  delay(end_delay);
}

void VIRAGES(int DIR)
{ // PERMET DE GERER LES VIRAGES  // DIR=1 == tt droit // DIR=2 == GAUCHE // DIR=3 == DROITE
  switch(DIR)
  { 
  //   case 1: // TOUT DROIT
  //     debut = millis(); fin=millis();  
  //     while(fin-debut < 5000){// tempo pour passer tout le virage
  //       sensorState = lineFinder.readSensors();
  //       switch(sensorState)
  //       {
  //         case S1_IN_S2_IN:   motorG.run(50 *(255/100)); motorD.run(-57 *(255/100)); break; // S1 et S2 = capteurs de presence ligne S1 a gauche
  //         case S1_OUT_S2_IN:  motorG.run(+25 *(255/100)); motorD.run(-50*(255/100)); break;  // tourne a droite
  //         case S1_IN_S2_OUT:  motorG.run(45 *(255/100)); motorD.run(-(30 *(255/100))); break; // tourne a gauche 
  //         default: break;
  //       }
  //       fin=millis(); 
  //     }
  //     // pass_intersection(4, 1800);
  //   break;

  //   case 2:  // VIRAGE A GAUCHE
  //     motorG.run(50 *(255/100)); motorD.run(-45 *(255/100)); delay(2500);// tempo pour passer tout le virage
  //     motorG.run(75 *(255/100)); motorD.run(-15 *(255/100)); delay(1200);//TOURNER
  //     motorG.run(45 *(255/100)); motorD.run(-45 *(255/100)); delay(1000);// ALLER DROIT
  //     // pass_intersection(3, 150);
  //     // // turn left
  //     // Serial.println("tourne");
  //     // motorG.run(50 *(255/100));
  //     // motorD.run(57 *(255/100));
  //     // while (DETECT_COULEURS() != 2)
  //     // {}
  //     // STOP();
  //     // // pass_intersection(1, 200);
  //     // motorG.run(40 *(255/100)); motorD.run(-47 *(255/100));
  //     // delay(1500);
  //   break;     

  //   case 3:  // VIRAGE A DROITE
  //     motorG.run(50 *(255/100)); motorD.run(-45 *(255/100)); delay(2500);// tempo pour passer tout le virage
  //     motorG.run(-75 *(255/100)); motorD.run(15 *(255/100)); delay(1200);//TOURNER
  //     motorG.run(45 *(255/100)); motorD.run(-45 *(255/100)); delay(1000);// ALLER DROIT 
  //     // pass_intersection(3, 150);
  //     // // turn left
  //     // Serial.println("tourne");
  //     // motorG.run(-50 *(255/100));
  //     // motorD.run(-57 *(255/100));
  //     // while (DETECT_COULEURS() != 5)
  //     // {}
  //     // STOP();
  //     // // pass_intersection(1, 200);
  //     // motorG.run(38 *(255/100)); motorD.run(-45 *(255/100));
  //     // delay(1500); 
  //   break;           
      
  //   default :  break;  
  case 1: // TOUT DROIT
      debut = millis(); fin=millis();  
      while(fin-debut<5000){// tempo pour passer tout le virage
        sensorState = lineFinder.readSensors();
        switch(sensorState)
        {
          case S1_IN_S2_IN:   motorG.run(50 *(255/100)); motorD.run(-57 *(255/100)); break; // S1 et S2 = capteurs de presence ligne S1 a gauche
          case S1_OUT_S2_IN:  motorG.run(+25 *(255/100)); motorD.run(-50*(255/100)); break;  // tourne a droite
          case S1_IN_S2_OUT:  motorG.run(45 *(255/100)); motorD.run(-(30 *(255/100))); break; // tourne a gauche 
          case S1_OUT_S2_OUT: motorG.run(40 *(255/100)); motorD.run(-45 *(255/100)); break; // avance
          default: break;
        }
        fin=millis(); 
      }
      if (sensorState == S1_OUT_S2_OUT ){
        ChercheLigne()   ;   
      }
      break;     


    case 2:  // VIRAGE A GAUCHE
      debut = millis(); fin=millis();  //avancer un peu 
      while(fin-debut<1250){// tempo pour passer tout le virage
        motorG.run(50 *(255/100)); motorD.run(-45 *(255/100)); //delay(1250);
        fin=millis(); 
      }
      debut = millis(); fin=millis();   //tourner a gauche
      while(fin-debut<1300){// tempo pour passer tout le virage
        motorG.run(75 *(255/100)); motorD.run(-15 *(255/100)); 
        fin=millis(); 
      }
      debut = millis(); fin=millis();   //tout droit
      while(fin-debut<1000){// tempo pour passer tout le virage
        motorG.run(45 *(255/100)); motorD.run(-45 *(255/100)); 
        fin=millis(); 
      }
    break;     

    case 3:  // VIRAGE A GAUCHE
      debut = millis(); fin=millis();  //avancer un peu 
      while(fin-debut<1250){// tempo pour passer tout le virage
        motorG.run(50 *(255/100)); motorD.run(-45 *(255/100)); 
        fin=millis(); 
      }
      debut = millis(); fin=millis();   //tourner a gauche
      while(fin-debut<1250){// tempo pour passer tout le virage
        motorG.run(15 *(255/100)); motorD.run(-90 *(255/100)); 
        fin=millis(); 
      }
      debut = millis(); fin=millis();   //tout droit
      while(fin-debut<1000){// tempo pour passer tout le virage
        motorG.run(45 *(255/100)); motorD.run(-45 *(255/100)); 
        fin=millis(); 
      }
    break;           
      
    default :  break;          
  }
  
}

//--------------------------------------------------------------------------------------------------

void Arrimage() {
  Serial.println("On commence");
  // DETECT_COULEURS() ; 
  // while (couleur != 5 && couleur != 4   ) {SUIVI_LIGNES()  ;}
  // STOP();
  // motorP.run(-120); delay(3 * 1000);  motorP.run(-0);// serer pince
  // //att
  // STOP();
  // delay(100);
  // while (ultraSensor.distanceCm() > 30)   {STOP(); delay(100)  ; Serial.print(ultraSensor.distanceCm()) ; } // detect avion
  // //Reculer
  // motorG.run(-40 *(255/100));
  // motorD.run(45 *(255/100));
  // delay(1400);
  // //att
  // STOP();
  // delay(100);
  //Demi tour
  // debut = millis(); fin = millis();
  // while(fin-debut < 2900) { motorG.run(60 *(255/100)); motorD.run(70 *(255/100));  fin = millis();  } // debut demis tour (2500)
  // STOP(); delay(1000);
  // debut = millis(); fin = millis(); while(fin-debut<1200){SUIVI_LIGNES();fin = millis();} STOP(); delay(1000); //reprendre ligne
  LinkedList<int> color_hist = LinkedList<int>();
  int color;
  int counter_color = 0;
  int stop_counter = 3;
  int stop_color = 9; // NOIR
  int skip_color = 0; // BLANC
  int ignore_color = 7; // BLEU
  motorG.run(40 *(255/100)); motorD.run(50 *(255/100));
  do
  {
    color = DETECT_COULEURS();
    // Serial.println(color);
    if(color_hist.getLength() == 0)
    {
      color_hist.Append(color);
      if(color == stop_color)
        counter_color++;
    } else
    {
      if(color_hist.getCurrent() != color)
      {
        if(color == stop_color && color_hist.getCurrent() != ignore_color)
          counter_color++;
        else if(color == ignore_color && color_hist.getCurrent() != stop_color)
          counter_color++;
        
        color_hist.Append(color);
        color_hist.moveToEnd();
      }
      Serial.println(counter_color);
    }
  } while(counter_color < stop_counter && color_hist.getLength() < ((stop_counter * 2)));
  //att
  STOP();
  delay(100);
  // 
  // motorG.run(30 *(255/100));
  // motorD.run(-37 *(255/100));
  // delay(800);
  // align
  // while(true)
  // {
  //   Serial.println("Align");
  //   sensorState = lineFinder.readSensors();
  //   if(sensorState == S1_IN_S2_IN)
  //     break;
  //   else if(sensorState == S1_OUT_S2_IN)
  //   {
  //     motorG.run(+25 *(255/100));
  //     motorD.run(-50*(255/100));
  //   }// tourne a droite
  //   else if(sensorState == S1_IN_S2_OUT)
  //   {
  //     motorG.run(45 *(255/100));
  //     motorD.run(-(30 *(255/100)));// tourne a gauche 
  //   }
  // }
  SUIVI_LIGNES();
  delay(1000);
  // ouvrir  pince
  motorP.run(180);
  delay(2 * 1000);
  motorP.run(-0);
  //Reculer vers avion
  motorG.run(-30 *(255/100));
  motorD.run(37 *(255/100));
  delay(1000);
  //att
  STOP();
  delay(1000);  
  motorP.run(-255); delay(3 * 1000);  motorP.run(-0);// serer pince

  STOP();
  delay(500);
}

void Arrimage2() {
  DETECT_COULEURS() ; 
  while (couleur != 5 && couleur != 4   ) {SUIVI_LIGNES()  ;}
  STOP();
  motorP.run(-120); delay(3 * 1000);  motorP.run(-0);// serer pince  
  while (ultraSensor.distanceCm() > 30)   {STOP(); delay(100)  ; Serial.print(ultraSensor.distanceCm()) ; } // detect avion
  motorG.run(-50 *(255/100)); motorD.run(55 *(255/100)); delay(2000); //Reculer
  motorG.run(0 *(255/100)); motorD.run(-0 *(255/100)); delay(1000); //att
  
  //Demi tour
  debut = millis(); fin = millis();
  while(fin-debut < 2550) { motorG.run(60 *(255/100)); motorD.run(70 *(255/100));  fin = millis();  } // debut demis tour (2500)
  STOP(); delay(1000);
  debut = millis(); fin = millis(); while(fin-debut<1200){SUIVI_LIGNES();fin = millis();} STOP(); delay(1000); //reprendre ligne
  motorG.run(0 *(255/100)); motorD.run(-0 *(255/100)); delay(1000); //att
  
  motorP.run(180); delay(4 * 1000);  motorP.run(-0);// ouvrir  pince
  motorG.run(-50 *(255/100)); motorD.run(57 *(255/100)); delay(3000); //Reculer vers avion
  motorG.run(0 *(255/100)); motorD.run(-0 *(255/100)); delay(1000); //att  
  motorP.run(-255); delay(5 * 1000);  motorP.run(-0);// serer pince

  STOP(); delay(100);
}

//-----------------------------------------------------------------------------------------------------------------------------

void DESARRIMAGE() {
  tout_droit_manuel();
  delay(950);
  motorP.run(180); delay(4 * 1000);  motorP.run(-0);// ouvrir  pince
  debut = millis(); fin = millis(); while(fin-debut<3000){SUIVI_LIGNES();fin = millis();} STOP(); delay(1000); //reprendre ligne
  motorP.run(-120); delay(3 * 1000);  motorP.run(-0);// serer pince 
}

//------------------------------------------------------------UTIL_FUNCTIONS-----------------------------------------------------------------

// skip functions
void do_nothing(){
  Serial.println(__FUNCTION__);
}
bool true_flag()
{
  Serial.println(__FUNCTION__);
  return true;
}

// color functions
bool DETECT_VERT()
{
  Serial.println(__FUNCTION__);
  return (DETECT_COULEURS() == 5);
return true;
}
bool DETECT_JAUNE()
{
  Serial.println(__FUNCTION__);
  return (DETECT_COULEURS() == 4 || DETECT_COULEURS() == 5);
return true;
}
bool DETECT_ROUGE()
{
  Serial.println(__FUNCTION__);
  return (DETECT_COULEURS() == 2);
return true;
}
bool DETECT_BLEU()
{
  Serial.println(__FUNCTION__);
//   return (DETECT_COULEURS() == 7);
return true;
}

// movement functions
void SUIVI_LIGNE()
{
  Serial.println(__FUNCTION__);
  SUIVI_LIGNES();
}
void VIRAGE_TTDROITE()
{
  Serial.println(__FUNCTION__);
  VIRAGES(1);
}
void VIRAGE_GAUCHE()
{
  Serial.println(__FUNCTION__);
  VIRAGES(2);
}
void VIRAGE_DROITE()
{
  Serial.println(__FUNCTION__);
  VIRAGES(3);
}
void CHANGE_DIR()
{
  Serial.println(__FUNCTION__);
  // ...
}
void STOP_R()
{
  Serial.println(__FUNCTION__);
  STOP();
}

// Plane
void TAKE_PLANE()
{
  Serial.println(__FUNCTION__);
  Arrimage2();
}

void LEAVE_PLANE()
{
  Serial.println(__FUNCTION__);
  DESARRIMAGE();
}

#endif