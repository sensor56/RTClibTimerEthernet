/*
 * Copyright (c) 2013 by Xavier HINAULT - support@mon-club-elec.fr
 *
 * This file is free software; you can redistribute it and/or modify
 * it under the terms of either the GNU General Public License version 3
 * or the GNU Lesser General Public License version 3, both as
 * published by the Free Software Foundation.
 */

/* Cette librairie permet d'implémenter des timers RTC - version réseau Ethernet
*/

#include "Arduino.h"
#include "Ethernet.h"
//#include "RTClib.h"
#include "RTClibTimerEthernet.h"

//#define ON 1
//#define OFF 0

  RTClibTimerEthernet::RTClibTimerEthernet(){ // constructeur par défaut
  
 
  }
  
//////////// fonctions membre de la classe //////////////

// ------ routine de gestion du timer ---- à placer dans loop --- 
void RTClibTimerEthernet::service(long unixtimeIn, void (*userFunc)(int), int indexIn) {
	
      if (this->etat==ON) { // si le timer est actif
      
        //if (timer[compt][i]==0) { // si premier passage  
        if (compt==0) { // si premier passage  
          this->debut=unixtimeIn; // mémorise début
          this->last=unixtimeIn; // initialise last
          this->compt=1; // incrémente compteur
          
          userFunc(indexIn); // appelle la fonction passée en pointeur avec l'argument voulu 
          
          //timerEvent(i); // appelle fonction voulue
          
        } // fin si premier passage 
        else { // si compt >=1 = passages suivants
          
          if (unixtimeIn-this->last>=this->interval) { // si l'intervalle du timer s'est écoulé
          
           Serial.print("\nIntervalle timer ");
           Serial.print(indexIn), 
           Serial.print (" ecoule."); 
           
           this->compt=this->compt+1; // incrémente compteur
           this->last=unixtimeIn; // RAZ last          

          userFunc(indexIn); // appelle la fonction passée en pointeur avec l'argument voulu 

          //timerEvent(i); // appelle fonction voulue
  
           if ( (maxCompt!=0) && (compt>=maxCompt) ) {
             Serial.println("\n>>>>>>>>>>>>>>>>>< Desactivation timer <<<<<<<<<<<<<<<<"); 
             this->etat=0; // stoppe le timer si nombre max atteint et si pas infini (timer[maxCompt]!=0)
           } // fin si comptMax atteint
           
          } // fin if intervalle écoulé
            
        } // fin else compt>=1
      
      } // fin si timer ON 
	
} // fin service()

//---- initialisation Timer avec intervalle et limite ------ 
void RTClibTimerEthernet::start(long intervalIn, long maxComptIn) {
    
    this->interval=intervalIn; // intervalle EN SECONDES !!
    this->maxCompt=maxComptIn; // nombre d'évènements voulus - durée = (n-1) x delai
    this->compt=0; // initialise comptage au démarrage
    this->etat=ON; // active le timer

} // fin start

//---- initialisation Timer avec intervalle et sans limite------ 
void RTClibTimerEthernet::start(long intervalIn) {
    
    this->interval=intervalIn; // intervalle EN SECONDES !!
    this->maxCompt=0; // nombre d'évènements voulus - 0 = sans fin
    this->compt=0; // initialise comptage au démarrage
    this->etat=ON; // active le timer

} // fin start

//----- démarre timer sans modifier les paramètres actuels --- 
void RTClibTimerEthernet::start() {
  
    this->etat=ON; // active le Timer sans modifier les paramètres courants

} // fin start 

//----- stoppe le timer sans modifier les paramètres actuels --- 
void RTClibTimerEthernet::stop() {
  
    this->etat=OFF; // désactive le Timer sans modifier les paramètres courants

} // fin stop timer

//---- info timer ---------
void RTClibTimerEthernet::status(EthernetClient clientIn){
 
      // affiche état Timer
      if (this->etat==1)clientIn.println("Timer actif"); else clientIn.println("Timer inactif");
      clientIn.print("intervalle="), clientIn.println(this->interval); 
      clientIn.print("limite comptage="), clientIn.println(this->maxCompt); 
      clientIn.print("comptage actuel="), clientIn.println(this->compt); 
      clientIn.print("debut="), clientIn.println(this->debut); 
      clientIn.print("dernier="), clientIn.println(this->last);     
 
} // fin info Timer 


/*
//------ fonction utile envoi entete http ---------------- 
void RTClibTimerEthernet::envoiEnteteHTTP(EthernetClient clientIn){
 
 if (clientIn) {

   //-- envoi de la réponse HTTP --- 
           clientIn.println(F("HTTP/1.1 200 OK")); // entete de la réponse : protocole HTTP 1.1 et exécution requete réussie
           clientIn.println(F("Content-Type: text/html")); // précise le type de contenu de la réponse qui suit 
           clientIn.println(F("Connnection: close")); // précise que la connexion se ferme après la réponse
           clientIn.println(); // ligne blanche 
           
           //--- envoi en copie de la réponse http sur le port série 
           Serial.println(F("La reponse HTTP suivante est envoyee au client distant :")); 
           Serial.println(F("HTTP/1.1 200 OK"));
           Serial.println(F("Content-Type: text/html"));
           Serial.println(F("Connnection: close"));

 } // fin si client
 
} // fin envoiEnteteHTTP

*/


