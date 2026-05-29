/* * COMFY & RESPONSIVE GEIGERZÄHLER (Für ESP32-S3)
 * Weniger Sound-Chaos, dafür blitzschnelle Reaktion!
 * Lautsprecher an Pin 5, Touch-Kabel an Pin 4
 */

#include <Arduino.h>

int speakerPin = 5; 
int touchPin = 4;   

class GeigerCounter
{
public:
  void loopCounter()
  {
    int touchValue = touchRead(touchPin);
    
    int threshold = 95; // NUR 5% Klick-Chance im Leerlauf -> entspanntes Knistern
    int maxPause = 30;  // Kurze maximale Pause für schnelle Touch-Abfrage

    // Sobald dein Finger das Kabel berührt (Wert > 40.000)
    if (touchValue > 40000) 
    {
      threshold = 40;   // 60% Klick-Chance -> heftiges Rattern
      maxPause = 8;     // Macht das Timing extrem aggressiv
    }

    int randomEvent = random(0, 100);

    if (randomEvent > threshold) 
    {
      click();
    }

    // Eine feste, winzige Grundpause (2ms) + ein kleiner Zufall.
    // Das hält den ESP32-S3 extrem reaktiv für deine Hand!
    delay(2 + random(0, maxPause)); 
  }

private:
  void click()
  {
    tone(speakerPin, 2200); 
    delay(2); // Knackiger, kurzer Impuls
    noTone(speakerPin);
  }
};

GeigerCounter geiger;

void setup() {
  touchAttachInterrupt(touchPin, NULL, 4000); 
  randomSeed(analogRead(0)); 
}

void loop() {
  geiger.loopCounter();
}