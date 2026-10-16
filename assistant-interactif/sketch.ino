#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <ESP32Servo.h>

// ====== BROCHES (modifie ici si besoin) ======
const int PIN_LED_ROUGE = 14;
const int PIN_LED_VERTE = 13;
const int PIN_LED_JAUNE = 15;
const int PIN_BUZZER    = 16;
const int PIN_BOUTON    = 40;
const int PIN_SERVO     = 35;
const int PIN_SDA       = 8;
const int PIN_SCL       = 7;

LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo servo;

bool buzzerActif = false;
bool boutonPrecedent = HIGH;

// Affiche 2 lignes sur le LCD
void afficher(String ligne1, String ligne2 = "") {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(ligne1);
  lcd.setCursor(0, 1);
  lcd.print(ligne2);
}

// Allume ou éteint une LED et confirme
void commandeLed(int pin, String nom, bool etat) {
  digitalWrite(pin, etat ? HIGH : LOW);
  String msg = "LED " + nom + (etat ? " ON" : " OFF");
  Serial.println(msg);
  afficher("LED " + nom, etat ? "allumee" : "eteinte");
}

// Fait sonner ou arrête le buzzer
void commandeBuzzer(bool etat) {
  buzzerActif = etat;
  if (etat) tone(PIN_BUZZER, 1000);
  else noTone(PIN_BUZZER);
  Serial.println(etat ? "Buzzer ON" : "Buzzer OFF");
  afficher("Buzzer", etat ? "actif" : "arrete");
}

// Positionne le servo
void commandeServo(int angle) {
  servo.write(angle);
  Serial.println("Servo a " + String(angle) + " degres");
  afficher("Servo", String(angle) + " degres");
}

// Éteint tout (utilisé par le bouton)
void toutEteindre() {
  digitalWrite(PIN_LED_ROUGE, LOW);
  digitalWrite(PIN_LED_VERTE, LOW);
  digitalWrite(PIN_LED_JAUNE, LOW);
  buzzerActif = false;
  noTone(PIN_BUZZER);
  Serial.println("Bouton: tout est eteint");
  afficher("Bouton appuye", "Tout eteint");
}

void traiterCommande(String cmd) {
  cmd.trim();
  cmd.toLowerCase();
  if (cmd.length() == 0) return;

  if      (cmd == "rouge on")   commandeLed(PIN_LED_ROUGE, "rouge", true);
  else if (cmd == "rouge off")  commandeLed(PIN_LED_ROUGE, "rouge", false);
  else if (cmd == "verte on")   commandeLed(PIN_LED_VERTE, "verte", true);
  else if (cmd == "verte off")  commandeLed(PIN_LED_VERTE, "verte", false);
  else if (cmd == "jaune on")   commandeLed(PIN_LED_JAUNE, "jaune", true);
  else if (cmd == "jaune off")  commandeLed(PIN_LED_JAUNE, "jaune", false);
  else if (cmd == "servo 0")    commandeServo(0);
  else if (cmd == "servo 90")   commandeServo(90);
  else if (cmd == "servo 180")  commandeServo(180);
  else if (cmd == "buzzer on")  commandeBuzzer(true);
  else if (cmd == "buzzer off") commandeBuzzer(false);
  else if (cmd == "tout off")   toutEteindre();
  else {
    Serial.println("Commande inconnue: " + cmd);
    afficher("Commande", "inconnue");
  }
}

void setup() {
  Serial.begin(115200);

  pinMode(PIN_LED_ROUGE, OUTPUT);
  pinMode(PIN_LED_VERTE, OUTPUT);
  pinMode(PIN_LED_JAUNE, OUTPUT);
  pinMode(PIN_BUZZER, OUTPUT);
  pinMode(PIN_BOUTON, INPUT_PULLUP);

  servo.attach(PIN_SERVO);
  servo.write(90);

  Wire.begin(PIN_SDA, PIN_SCL);
  lcd.init();
  lcd.backlight();
  afficher("Assistant pret", "Tapez commande");

  Serial.println("Assistant pret. Commandes:");
  Serial.println("  rouge on/off, verte on/off, jaune on/off");
  Serial.println("  servo 0 / servo 90 / servo 180");
  Serial.println("  buzzer on / buzzer off");
}

void loop() {
  if (Serial.available()) {
    String cmd = Serial.readStringUntil('\n');
    traiterCommande(cmd);
  }

  // Bouton: éteint les LED et arrête le buzzer
  bool etatBouton = digitalRead(PIN_BOUTON);
  if (boutonPrecedent == HIGH && etatBouton == LOW) {
    toutEteindre();
  }
  boutonPrecedent = etatBouton;
}

