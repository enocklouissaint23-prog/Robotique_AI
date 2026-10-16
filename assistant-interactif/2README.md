# Assistant interactif - Robotique & IA

## Objectif
Simuler sur Wokwi un assistant contrôlé par des commandes
écrites dans le moniteur série : LED, servomoteur, buzzer
et confirmation sur un écran LCD.

## Composants et outils
- ESP32-S2
- Écran LCD 1602 I2C
- 3 LED (rouge, verte, jaune) + 3 résistances 220 ohms
- Servomoteur
- Buzzer
- Bouton poussoir
- Simulateur Wokwi

## Fonctionnement
Commandes tapées dans le moniteur série :
- rouge on / rouge off
- verte on / verte off
- jaune on / jaune off
- servo 0 / servo 90 / servo 180
- buzzer on / buzzer off

Chaque commande affiche une confirmation sur le LCD.
Le bouton éteint toutes les LED et arrête le buzzer.

Branchements : LED rouge GPIO 14, verte GPIO 13,
jaune GPIO 15, buzzer GPIO 16, bouton GPIO 40,
servo GPIO 35, LCD SDA GPIO 8 et SCL GPIO 7.

## Résultats
Toutes les commandes fonctionnent en simulation.
Les captures sont dans ce dossier (Images_AI.pdf).
