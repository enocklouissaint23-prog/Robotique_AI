# Voltmètre amélioré avec LED, buzzer et bouton HOLD

## Objectif
Améliorer le voltmètre en indiquant le niveau de tension
avec des LED, une alarme sonore et un bouton HOLD qui
fige la mesure.

## Composants et outils
- ESP32-S2
- Potentiomètre
- Écran LCD 1602 I2C
- 3 LED (verte, jaune, rouge) + 3 résistances 220 ohms
- Buzzer
- Bouton poussoir (HOLD)
- Simulateur Wokwi

## Fonctionnement
- Tension inférieure à 1,1 V : LED verte
- Tension entre 1,1 V et 2,2 V : LED jaune
- Tension supérieure à 2,2 V : LED rouge + buzzer
- Un appui sur le bouton HOLD fige la valeur affichée
  ("HOLD" apparaît sur le LCD), un second appui la libère.

Rôle des composants :
- Potentiomètre : simule la tension à mesurer
- Résistances : limitent le courant des LED
- Buzzer : alarme quand la tension est trop haute
- Bouton : fige la mesure (INPUT_PULLUP)

Branchements : potentiomètre sur GPIO 1, LED verte GPIO 13,
jaune GPIO 15, rouge GPIO 14, buzzer GPIO 16, bouton GPIO 40,
LCD SDA GPIO 8 et SCL GPIO 7.

## Résultats
Les LED et le buzzer réagissent aux bons seuils, et le
bouton HOLD fige correctement l'affichage.
Les captures sont dans ce dossier.
