// ============================================================
//  De kluis: Startcode voor deelnemers
//  Arduino Uno R3
// ============================================================

#include <LiquidCrystal.h>

// --- Aangesloten pinnen ---
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

#define POT_PIN       A0   // Potentiometer (het kluisslot)
#define BTN_BEVESTIG  6    // Knop: bevestig jouw keuze
#define BTN_RESET     7    // Knop: reset het spel
const int LED_PINS[] = {10, 9, 8};  // 3 LED's

// --- Status variabelen ---
const int CODE_LENGTE = 3;
int GEHEIME_CODE[CODE_LENGTE];  // wordt random gegenereerd bij opstart

int  huidigCijfer = 0;     // Welk cijfer van de code geven we in?
bool kluisGeopend = false; // Is de kluis al gekraakt?
int  vorigeWaarde = -1;    // Onthoudt vorige potentiometerwaarde (voorkomt flikkering)


  // --------------------------------------------------------
  //  UITBREIDINGEN: voeg hier nieuwe globale variabelen 
  //  toe als het nodig is
  // --------------------------------------------------------

// ============================================================
// setup() wordt één keer uitgevoerd bij opstart
// ============================================================
void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  pinMode(BTN_BEVESTIG, INPUT_PULLUP);
  pinMode(BTN_RESET,    INPUT_PULLUP);
  pinMode(LED_PINS[0], OUTPUT);
  pinMode(LED_PINS[1], OUTPUT);
  pinMode(LED_PINS[2], OUTPUT);
  randomCode();   // genereer een willekeurige geheime code
  beginScherm();  // toon het startscherm
}

// ============================================================
// loop() wordt eindeloos herhaald, dit is het hoofdprogramma
// ============================================================
void loop() {

  // ----------------------------------------------------------
  // TODO 2: Resetknop uitlezen
  //
  // Vervang 'false' door de juiste voorwaarde.
  // De knop is verbonden met pin BTN_RESET.
  // Gebruik: digitalRead(...)
  // Tip: Een ingedrukte knop geeft LOW terug.
  // Tip: Een gelijkheid check je met '=='
  // ----------------------------------------------------------
  if (false) {          //TODO 2: vervang 'false'
    delay(200);
    btnReset();
    return;
  }

  if (kluisGeopend) return;

  // ----------------------------------------------------------
  // TODO 1: Potentiometer uitlezen
  //
  // Stap 1: Lees de ruwe waarde van de potentiometer.
  //         Dit kan m.b.v. analogRead(POT_PIN);
  //         Upload en draai aan de knop, wat zie je op het LCD?
  //
  // Stap 2: De ruwe waarde heeft een bereik van 0–1023, maar wij willen 0–99.
  //         Pas aan naar:
  //         int waarde = map(analogRead(POT_PIN), 0, 1023, 0, 99);
  //         Upload opnieuw, wat verandert er?
  // ----------------------------------------------------------
  int waarde = 0;   //TODO 1: vervang 0 met correcte waarde

  // ----------------------------------------------------------
  // TODO 3: Afstand berekenen
  //
  // Hoe ver zit de ingegeven waarde van het juiste cijfer?
  // Het juiste cijfer op deze positie is: GEHEIME_CODE[huidigCijfer]
  // Tip: Gebruik de functie abs() voor de absolute waarde.
  //   abs(5 - 8)  geeft  3
  //   abs(8 - 5)  geeft  3
  //
  // ----------------------------------------------------------
  int afstand = 0;      //TODO 3: vervang 0 met de correct berekende afstand

  // Toon de huidige waarde op het LCD (enkel bij wijziging)
  if (waarde != vorigeWaarde) {
    lcd.setCursor(0, 1);
    if (waarde < 10) lcd.print(" ");  // uitlijning
    lcd.print(waarde);
    lcd.print("  ");

    // --------------------------------------------------------
    // TODO 4: Hint tonen
    //
    // Er is al een functie getHint(afstand) voorzien (zie onder).
    // Roep ze aan en druk het resultaat af op het LCD:
    //   lcd.print( ... );
    // --------------------------------------------------------
                        //TODO 4: voeg hier lcd.print(...) toe

    lcd.print("        ");  // wis de rest van de regel
    vorigeWaarde = waarde;
  }

  btnBevestig(afstand);
}

// ============================================================
// HULPFUNCTIES: zorgt voor extra structuur en overzicht
// ============================================================

// Geeft een hint op basis van hoe ver je van het juiste cijfer zit
const char* getHint(int afstand) {
  if (afstand <= 3)  return "HEET!    ";
  if (afstand <= 10) return "WARM     ";
  if (afstand <= 20) return "LAUW     ";
  return             "KOUD     ";
}

// Toont "Cijfer X van 3" op het scherm
void beginScherm() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Cijfer ");
  lcd.print(huidigCijfer + 1);
  lcd.print(" van ");
  lcd.print(CODE_LENGTE);
  vorigeWaarde = -1;
}

// Wordt opgeroepen als de kluis volledig gekraakt is
void kluisOpen() {
  kluisGeopend = true;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("** KLUIS OPEN **");
  lcd.setCursor(0, 1);
  lcd.print(" Gefeliciteerd! ");

  // --------------------------------------------------------
  //  UITBREIDING A: voeg hier een           
  //  LED-animatie toe als visuele beloning! 
  // --------------------------------------------------------

  
  // --------------------------------------------------------
  //  UITBREIDING D: Toon hier de verstreken tijd
  // --------------------------------------------------------
}

// Wordt opgeroepen bij een fout cijfer
void foutMelding(int afstand) {
  // Alle LED's animatie:
  for (int j = 0; j < CODE_LENGTE; j++){
    digitalWrite(LED_PINS[j], HIGH);
  }
  delay(300);
  for (int j = 0; j < CODE_LENGTE; j++){
    digitalWrite(LED_PINS[j], LOW);
  }
  delay(300);
  for (int j = 0; j < CODE_LENGTE; j++){
    digitalWrite(LED_PINS[j], HIGH);
  }

  lcd.setCursor(0, 0);
  lcd.print("FOUT!  ");
  lcd.print(getHint(afstand));
  lcd.setCursor(0, 1);
  lcd.print("Probeer opnieuw!");

  delay(1500);

  // Herstel: zet enkel de al-correcte LED's terug aan
  for (int j = 0; j < CODE_LENGTE; j++){
    digitalWrite(LED_PINS[j], LOW);
  }
  for (int j = 0; j < huidigCijfer; j++){
    digitalWrite(LED_PINS[j], HIGH);
  }
  beginScherm();
}

// Verwerkt de bevestigknop
void btnBevestig(int afstand) {
  if (digitalRead(BTN_BEVESTIG) == LOW) {
    delay(200);

    // --------------------------------------------------------
    // TODO 5: bevestiglogica
    //
    // Controleer of het ingegeven cijfer correct is.
    //
    // Tip: gebruik volgende structuur om je op weg te helpen
    // Als CORRECT (afstand == 0):
    //   1. Zet de LED van het huidige cijfer aan:
    //        LED's hebben een digitaal signaal nodig die hoog is om aan te gaan
    //        De drie LED's zijn opgeslagen in de array ‘LED_PINS’. Een array werkt als een genummerde lijst: 
    //        ‘LED_PINS[0]’ is de eerste LED, ‘LED_PINS[1]’ de tweede, enzovoort. Welke index heb je hier nodig?
    //   2. Verhoog huidigCijfer met 1
    //   3. Zijn nu ALLE cijfers correct? 
    //        -> kluisOpen()
    //      Nog niet alle correct?
    //        -> vorigeWaarde = -1;
    //           beginScherm();
    // Als FOUT:
    //   -> foutMelding(afstand)
    //     (Al correcte LED's blijven aan, geen volledige reset!)
    // --------------------------------------------------------

                        //TODO 5: schrijf hier jouw if/else logica




  
    // --------------------------------------------------------
    //  UITBREIDING B: verhoog pogingen bij een fout en    
    //    reset naar 0 bij een correct cijfer.               
    //    Blokkeer invoer na 5 foute pogingen.                
    // --------------------------------------------------------
    delay(200);
  }
}

// Genereert een willekeurige code en print ze naar de Seriële Monitor
void randomCode() {
  randomSeed(analogRead(A1));  // A1 onverbonden = elektrische ruis als seed
  for (int i = 0; i < CODE_LENGTE; i++) {
    GEHEIME_CODE[i] = random(0, 100);
  }
  // Bekijk de code via: Extra -> Seriële Monitor (Ctrl+Shift+M)
  for (int i = 0; i < CODE_LENGTE; i++) {
    Serial.print(GEHEIME_CODE[i]);
    Serial.print(" ");
  }
  Serial.println();
}

// Reset het spel volledig naar de begintoestand
void btnReset() {
  huidigCijfer = 0;
  kluisGeopend = false;
  for (int i = 0; i < CODE_LENGTE; i++) {
    digitalWrite(LED_PINS[i], LOW);
  }
  randomCode();
  beginScherm();
}
