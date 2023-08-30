#include <NewPing.h>

// Pines
#define A1A 9 // Mot. derecho avance
#define A1B 8// Mot. derecho retroceso
#define B1A 11 // Mot. izquierdo avance
#define B1B 10 // Mot. izquierdo retroceso

#define trig_frente 2
#define echo_frente 3

#define trig_derecho 5
#define echo_derecho 4

#define trig_izquierdo 7
#define echo_izquierdo 6

int pared_avistada=6;

// Variables 
float dist_derecho, dist_derecho2, dist_izquierdo, dist_izquierdo2, dist_frente, dist_frente2;
float final_derecho, final_izquierdo, final_frente;

// Declaración de sensores
NewPing sens_frente(trig_frente, echo_frente, 100);
NewPing sens_derecho(trig_derecho, echo_derecho, 100);
NewPing sens_izquierdo(trig_izquierdo, echo_izquierdo, 100);

void setup(){

  // L9110s
  pinMode(A1A, OUTPUT); //Rueda der. Retroceso
  pinMode(A1B, OUTPUT); //Rueda der. Avance
  pinMode(B1A, OUTPUT); //Rueda izq. Avance
  pinMode(B1B, OUTPUT); //Rueda izq. Retroceso
  
  // Sensor ultrasonido
  pinMode(trig_frente, OUTPUT);
  pinMode(echo_frente, INPUT);
  
  pinMode(trig_derecho, OUTPUT);
  pinMode(echo_derecho, INPUT);

  pinMode(trig_izquierdo, OUTPUT);
  pinMode(echo_izquierdo, INPUT);

  Serial.begin(9600);
}

void loop(){
  
  // Sensor ultrasonico
  sensores();

  // Algoritmos de giro/avance
 
  if(dist_frente >= pared_avistada){
    avance();
    
    if(dist_derecho > pared_avistada){
    stop();
    delay(50);
    derecho();
    delay(300);
    avance();
    }
  }

  if(dist_frente <= pared_avistada){
    if(dist_derecho < pared_avistada){
    izquierda();      
    }
    if(dist_derecho > pared_avistada){
    derecho();
    }
  } 
}

void avance(){
  digitalWrite(A1A, LOW);
  digitalWrite(A1B, HIGH);
  digitalWrite(B1A, HIGH);
  digitalWrite(B1B, LOW);
}

void derecho(){
  digitalWrite(A1A, HIGH);
  digitalWrite(A1B, LOW);
  digitalWrite(B1A, HIGH);
  digitalWrite(B1B, LOW);
}

void izquierda(){
  digitalWrite(A1A, LOW);
  digitalWrite(A1B, HIGH);
  digitalWrite(B1A, LOW);
  digitalWrite(B1B, HIGH);
}

void stop(){
  digitalWrite(A1A, LOW);
  digitalWrite(A1B, LOW);
  digitalWrite(B1A, LOW);
  digitalWrite(B1B, LOW);
}

void sensores(){

  dist_frente=sens_frente.ping_cm();
  dist_derecho=sens_derecho.ping_cm(); 
  dist_izquierdo=sens_izquierdo.ping_cm();


  final_frente=(dist_frente+dist_frente2)/2;
  final_derecho=(dist_derecho+dist_derecho2)/2;
  final_izquierdo=(dist_izquierdo+dist_izquierdo2)/2;

  dist_frente2=dist_frente;
  dist_derecho2=dist_derecho;
  dist_izquierdo2=dist_izquierdo;
}