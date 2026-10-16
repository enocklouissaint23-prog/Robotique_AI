#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// ====== BROCHES ======
const int PIN_POT = 1;   
const int PIN_SDA = 8;
const int PIN_SCL = 7;

const float VREF = 3.3;       
const int ADC_MAX = 4095;     

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(115200);
  analogReadResolution(12);

  Wire.begin(PIN_SDA, PIN_SCL);
  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("Voltmetre");
  delay(1000);
  lcd.clear();
}

void loop() {
  int valeur = analogRead(PIN_POT);             
  float tension = valeur * VREF / ADC_MAX;       

  lcd.setCursor(0, 0);
  lcd.print("Tension:        ");
  lcd.setCursor(0, 1);
  lcd.print(tension, 2);
  lcd.print(" V   ");

  Serial.print("ADC: ");
  Serial.print(valeur);
  Serial.print("  Tension: ");
  Serial.print(tension, 2);
  Serial.println(" V");

  delay(200);
}

