# Voltmètre numérique avec écran LCD

## Objectif
Réaliser sur Wokwi un voltmètre numérique qui mesure une
tension et l'affiche sur un écran LCD. Un potentiomètre
simule la tension à mesurer.

## Composants et outils
- ESP32-S2
- Potentiomètre
- Écran LCD 1602 I2C
- Simulateur Wokwi

## Fonctionnement
- Le potentiomètre est un diviseur de tension : sa broche
  du milieu (GPIO 1) envoie une tension de 0 à 3,3 V.
- Le convertisseur analogique-numérique (ADC) de l'ESP32
  transforme cette tension en nombre de 0 à 4095.
- Le programme calcule : tension = valeur x 3,3 / 4095.
- Le résultat est affiché sur le LCD toutes les 200 ms.

Branchements : potentiomètre GND, 3V3 et SIG sur GPIO 1 ;
LCD SDA sur GPIO 8 et SCL sur GPIO 7.

## Résultats
La tension affichée varie de 0.00 V à 3.30 V quand on
tourne le potentiomètre.
Les captures sont dans ce dossier.
