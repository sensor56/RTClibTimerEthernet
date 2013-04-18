RTClibTimerEthernet
===================

Ma librairie RTClibTimerEthernet est une surcouche à la librairie « temps-réel » RTCLib et permet d'implémenter facilement des objets « timers temps-réel » (ou « timers RTC ») pour une utilisation via réseau Ethernet (pour la réception des informations des timers RTC).

Chaque objet timer RTC dispose des paramètres suivants : 
* boolean etat;  // variable d'état du timer - true/false actif/inactif
* long interval; // variable intervalle entre 2 événements en secondes 
* long maxCompt; // variable nombre événements max - comptage sans fin si =0
* long compt; // variable nombre événements survenus depuis début comptage
* long debut; // variable unixtime de debut
* long last; // variable unixtime dernier événement

Chaque objet timer dispose des fonctions suivantes : 
* void start(long intervalIn, long maxComptIn); // initialisation timer avec limite 
* void start(long intervalIn); // initialisation timer sans fin 
* void start(); //----- démarre timer sans modifier les paramètres actuels --- 
  
* void stop();//----- stoppe le timer sans modifier les paramètres actuels --- 

* void status(EthernetClient clientIn); //---- affiche infos sur l'état du timer vers client Ethernet
	
* void service(long unixtimeIn, void (*userFunc)(int), int indexIn) ; // routine de gestion du timer, à placer dans loop 


Le principe d'utilisation consistera : 
* à lancer le timer avec les paramètres voulus à l'aide de la fonction start(),
* à appeler la fonction service() du timer au sein de la fonction loop(). Cette fonction service() assure la gestion interne du timer RTC. Noter que la fonction service reçoit en paramètre une fonction qui sera appelée lorsque l'événement timer surviendra ce qui permet de personnaliser à loisir les actions à effectuer. La fonction appelée recevra en paramètre l'index du timer utilisé, ce qui permettra de personnaliser l'action à effectuer par timer. Au final, souplesse maximale. 
* à afficher l'état des paramètres du timer RTC à tout moment avec la fonction status()
* à stopper le timer au besoin avec la fonction stop() 


Cette librairie est utilisée notamment dans mon projet "The Open Datalogger Project" : https://github.com/sensor56/TheOpenDataloggerProject
