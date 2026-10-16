#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// ====== BROCHES ======
const int PIN_POT       = 1;
const int PIN_LED_VERTE = 13;
const int PIN_LED_JAUNE = 15;
const int PIN_LED_ROUGE = 14;
const int PIN_BUZZER    = 16;
const int PIN_HOLD      = 40;
const int PIN_SDA       = 8;
const int PIN_SCL       = 7;

// ====== PARAMETRES ======
const float VREF = 3.3;
const int ADC_MAX = 4095;
const float SEUIL_BAS  = 1.1;   // en dessous : vert
const float SEUIL_HAUT = 2.2;   // au dessus : rouge + buzzer

LiquidCrystal_I2C lcd(0x27, 16, 2);

bool hold = false;
float tensionFigee = 0;
bool boutonPrecedent = HIGH;

void setup() {
  Serial.begin(115200);
  analogReadResolution(12);

  pinMode(PIN_LED_VERTE, OUTPUT);
  pinMode(PIN_LED_JAUNE, OUTPUT);
  pinMode(PIN_LED_ROUGE, OUTPUT);
  pinMode(PIN_BUZZER, OUTPUT);
  pinMode(PIN_HOLD, INPUT_PULLUP);

  Wire.begin(PIN_SDA, PIN_SCL);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Voltmetre HOLD");
  delay(1000);
  lcd.clear();
}

void loop() {
  // Gestion du bouton HOLD (appui = change l'état)
  bool etatBouton = digitalRead(PIN_HOLD);
  if (boutonPrecedent == HIGH && etatBouton == LOW) {
    hold = !hold;
    if (hold) {
      int valeur = analogRead(PIN_POT);
      tensionFigee = valeur * VREF / ADC_MAX;
    }
    delay(50);  // anti-rebond
  }
  boutonPrecedent = etatBouton;

  // Mesure (ou valeur figée)
  float tension;
  if (hold) {
    tension = tensionFigee;
  } else {
    int valeur = analogRead(PIN_POT);
    tension = valeur * VREF / ADC_MAX;
  }

  // LED selon le niveau
  digitalWrite(PIN_LED_VERTE, tension < SEUIL_BAS);
  digitalWrite(PIN_LED_JAUNE, tension >= SEUIL_BAS && tension <= SEUIL_HAUT);
  digitalWrite(PIN_LED_ROUGE, tension > SEUIL_HAUT);

  // Buzzer si tension trop haute
  if (tension > SEUIL_HAUT) tone(PIN_BUZZER, 1000);
  else noTone(PIN_BUZZER);

  // Affichage LCD
  lcd.setCursor(0, 0);
  lcd.print("Tension:        ");
  lcd.setCursor(0, 1);
  lcd.print(tension, 2);
  lcd.print(" V ");
  lcd.print(hold ? "HOLD  " : "      ");

  Serial.print(tension, 2);
  Serial.println(hold ? " V (HOLD)" : " V");

  delay(100);
}
