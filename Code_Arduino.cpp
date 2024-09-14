
const int sensMoteurDroit = 4;
const int vitesseMoteurDroit = 5;
const int sensMoteurGauche = 7;
const int vitesseMoteurGauche = 6;
const int detecteurLigneDroit = 10;
const int detecteurLigneGauche = 9;
const int detecteurObstacleUltrason = 12;


void setup() {
  // Initialisation des broches moteurs en sortie
  pinMode(sensMoteurDroit, OUTPUT);
  pinMode(vitesseMoteurDroit, OUTPUT);
  pinMode(sensMoteurGauche, OUTPUT);
  pinMode(vitesseMoteurGauche, OUTPUT);
  
  // Initialisation des broches détecteurs en entrée
  pinMode(detecteurLigneDroit, INPUT);
  pinMode(detecteurLigneGauche, INPUT);
  pinMode(detecteurObstacleUltrason, INPUT);
}

// Fonction pour faire avancer le robot
void avant(int vitesse) {
  digitalWrite(sensMoteurDroit, HIGH);
  digitalWrite(sensMoteurGauche, LOW);
  analogWrite(vitesseMoteurDroit, vitesse);
  analogWrite(vitesseMoteurGauche, vitesse);
}

// Fonction pour faire reculer le robot
void droite(int vitesse) {
  digitalWrite(sensMoteurDroit, LOW);
  digitalWrite(sensMoteurGauche, LOW);
  analogWrite(vitesseMoteurDroit, vitesse);
  analogWrite(vitesseMoteurGauche, vitesse);
}

// Fonction pour tourner à droite
void arriere(int vitesse) {
  digitalWrite(sensMoteurDroit, LOW);
  digitalWrite(sensMoteurGauche, HIGH);
  analogWrite(vitesseMoteurDroit, vitesse);
  analogWrite(vitesseMoteurGauche, vitesse);
}

// Fonction pour tourner à gauche
void gauche(int vitesse) {
  digitalWrite(sensMoteurDroit, HIGH);
  digitalWrite(sensMoteurGauche, HIGH);
  analogWrite(vitesseMoteurDroit, vitesse);
  analogWrite(vitesseMoteurGauche, vitesse);
}

long distance() {
  pinMode(detecteurObstacleUltrason, OUTPUT);
  digitalWrite(detecteurObstacleUltrason, LOW);
  delayMicroseconds(2);
  digitalWrite(detecteurObstacleUltrason, HIGH);
  delayMicroseconds(10);
  digitalWrite(detecteurObstacleUltrason, LOW);
  pinMode(detecteurObstacleUltrason, INPUT);
  return pulseIn(detecteurObstacleUltrason, HIGH);
}

bool obstacleDetecte() {
  long duration = distance();
  long distanceCm = duration / 58.2;
  if (distanceCm > 0 && distanceCm < 30) {
    return true;
  }
  return false;
}

void arreter() {
  analogWrite(vitesseMoteurDroit, 0);
  analogWrite(vitesseMoteurGauche, 0);
}


void revenirSurLigne(int vitesse) {
  // Tourner légèrement à gauche et à droite pour retrouver la ligne
  while (digitalRead(detecteurLigneDroit) == HIGH && digitalRead(detecteurLigneGauche) == HIGH) {
    gauche(vitesse/2);
    delay(130);
    

    droite(vitesse/2);
    delay(130);
    
  }
}

// Fonction pour suivre une ligne
void suivreLigne(int vitesse) {
  int ligneDroite = digitalRead(detecteurLigneDroit);
  int ligneGauche = digitalRead(detecteurLigneGauche);
  
  if (ligneDroite == HIGH && ligneGauche == HIGH) {
    // Revenir sur la ligne si les deux détecteurs voient du noir
    revenirSurLigne(vitesse);
  } else if (ligneDroite == LOW && ligneGauche == HIGH) {
    // Tourner légèrement à gauche si le détecteur droit voit du blanc
    droite(vitesse);
  } else if (ligneDroite == HIGH && ligneGauche == LOW) {
    // Tourner légèrement à droite si le détecteur gauche voit du blanc
    gauche(vitesse );
  } else {
    // Avancer si les deux détecteurs voient du blanc
    avant(vitesse);
  }
}

  

void loop() {
  
 
  suivreLigne(180);

  


}
