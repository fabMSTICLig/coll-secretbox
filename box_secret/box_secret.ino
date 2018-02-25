/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep
*/


unsigned int mot_passe[6] = {600,300,300,600,600};
unsigned long temps_courant = millis();
unsigned long dernier_temps = millis();
unsigned int seuil = 10;
unsigned int indexpass = 0;
boolean tap = false;

#include <Servo.h>

Servo myservo1;
Servo myservo2;

#define CLOSEPOS1 165
#define CLOSEPOS2 162
#define OPENPOS1 (CLOSEPOS1-90)
#define OPENPOS2 (CLOSEPOS2-90)

void setup() {
  myservo1.attach(D1);
  myservo2.attach(D2);
  indexpass = 0;
  Serial.begin(9600);
        myservo1.write(CLOSEPOS1);   //Fermer 
        myservo2.write(CLOSEPOS2);   //Fermer
}


bool test_interval(unsigned int tolerance, unsigned int indexpass, unsigned int difference_temps) {
  Serial.print("indexpass:");
  Serial.print(indexpass);
  Serial.print("  tab:");
  Serial.print(mot_passe[indexpass]);
  Serial.print("  diff:");
  Serial.println(difference_temps);
 if(mot_passe[indexpass] + tolerance > difference_temps)
 {
    Serial.println("debug A");
    if( mot_passe[indexpass] - tolerance < difference_temps )
    {
      Serial.println("debug B");
      return true;
    }
 }
  return false;
}

void reinitialise(){
  indexpass = 0;
}

void loop() {
  unsigned int piezo_valeur = analogRead(A0);
  //Serial.println(piezo_valeur);
  if(piezo_valeur > seuil && tap == false){
    //Serial.println("ici");
    tap = true;
    dernier_temps = temps_courant;
    temps_courant = millis();

    unsigned long difference = temps_courant - dernier_temps;
    //Serial.println(difference);
    if (test_interval(150,indexpass,difference)==true){
      //ici les delais sont bon 
      Serial.println(difference);
      indexpass = indexpass + 1;
      if (indexpass == 5) {
        //Gagné, on ouvre la boite 
        Serial.println("WIN");  
        indexpass = 0;
        myservo1.write(OPENPOS1); //ouvrir
        myservo2.write(OPENPOS2); //ouvrir
        
        delay(15000); //10 sec
        myservo1.write(CLOSEPOS1);   //Fermer 
        myservo2.write(CLOSEPOS2);   //Fermer
      }
    } else {
      //Ici le  delais sont mauvais, l'utilisateur ne tappe pas le bon rythme
      reinitialise();
      Serial.println("LOOSE");
      
    }
    delay(200);
    tap = false;
  } else {
   
  }
}



