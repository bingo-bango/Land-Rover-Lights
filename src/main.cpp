#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

// RGBW parameters and setup
#define LED_PIN   2
#define LED_COUNT 2
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_RGBW + NEO_KHZ800);

const int headPin = 0;       // headlights output
const int tailPin = 10;       // tails output
const int hornPin = 4;       // horn output
const int indrPin = 2;       // rh flashers
const int indlPin = 3;       // lh flashers
const int tButPin = 7;       // toggle main lights button
const int rButPin = 8;       // rh flasher button
const int lButPin = 12;      // lh flasher button
const int hButPin = 13;      // Horn / Siren button

int hlstate = 0;  // headlight state
int tlstate = 0;  // tail light state
int hrstate = 0;  // horn state
int frstate = 0;  // rh flasher state
int flstate = 0;  // lh flasher state

int togg_tBut = 0;

int dipped = 63;     // dipped brightness (0-254)
int highbm = 254;    // brights brightness (0-254)

float sinVal;
int toneVal;

void setup() {
  // RGBW setup
  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(255); // Set BRIGHTNESS to about 1/5 (max = 255)

  // DEBUG
  strip.setPixelColor(0, strip.Color(0, 0, 0, dipped));
  strip.setPixelColor(1, strip.Color(0, 0, 0, dipped));
  strip.show();
  analogWrite(tailPin, 255);
  delay(100);
  strip.setPixelColor(0, strip.Color(0, 0, 0, 0));
  strip.setPixelColor(1, strip.Color(0, 0, 0, 0));
  strip.show();
  analogWrite(tailPin, 0);
  Serial.begin(9600);
  // END DEBUG
    
  // set the output pins:
  pinMode(hornPin, OUTPUT);
  pinMode(tailPin, OUTPUT);

  // set the inputs:
  pinMode(tButPin, INPUT);
  pinMode(rButPin, INPUT);
  pinMode(lButPin, INPUT);
  pinMode(hButPin, INPUT);
}

void loop() {

  // Check button states
  int read_tBut = digitalRead(tButPin);
  int read_rBut = digitalRead(rButPin);
  int read_lBut = digitalRead(lButPin);
  int read_hBut = digitalRead(hButPin);

  //

  if (read_tBut == 0) {
    hlstate = hlstate +1;
    togg_tBut = 1;
  } else {
    togg_tBut = 0;
  }



  Serial.println(hlstate);
    
    


  // Set Headlights and tail lights
  switch (hlstate) {
    case 0:   // lights off
      strip.setPixelColor(0, strip.Color(0, 0, 0, 0));
      strip.setPixelColor(1, strip.Color(0, 0, 0, 0));
      strip.show();
      analogWrite(tailPin, 0);
      break;
    case 1:   // fade to dipped
        for (int i = 0; i <= dipped; i++) {
          strip.setPixelColor(0, strip.Color(0, 0, 0, i));
          strip.setPixelColor(1, strip.Color(0, 0, 0, i));
          strip.show();
          analogWrite(tailPin, (4 *i) );
          delay(1);
          }
         hlstate = 2;
         break;
    case 2: // keep on dipped
        strip.setPixelColor(0, strip.Color(0, 0, 0, dipped));
        strip.setPixelColor(1, strip.Color(0, 0, 0, dipped));
        strip.show();
        analogWrite(tailPin, 255);
        break;
    case 3: // fade to high
      for (int i = dipped; i <= 255; i++) {
        strip.setPixelColor(0, strip.Color(0, 0, 0, i));
        strip.setPixelColor(1, strip.Color(0, 0, 0, i));
        strip.show();
        delay(1);
        }
        hlstate = 4;
        break;
    case 4: // keep on high
        strip.setPixelColor(0, strip.Color(0, 0, 0, 255));
        strip.setPixelColor(1, strip.Color(0, 0, 0, 255));
        strip.show();
        break;
    case 5: // fade from high to off
      for (int i = 255; i >= 0; i--) {
        strip.setPixelColor(0, strip.Color(0, 0, 0, i));
        strip.setPixelColor(1, strip.Color(0, 0, 0, i));
        strip.show();
        analogWrite(tailPin, i);
        delay(1);
        }
      hlstate = 0;
      break;
      
}


//  strip.clear();
//  strip.setPixelColor(0, strip.Color(0, 0, 255, 0));
//  strip.setPixelColor(1, strip.Color(0, 0, 0, 255));
//  strip.show();
//  delay(100);
//  strip.clear();
//  strip.setPixelColor(0, strip.Color(0, 0, 0, 255));
//  strip.setPixelColor(1, strip.Color(0, 0, 255, 0));
//  strip.show();
//  delay(100);
//  //fadeIn();


  // car alarm

  
//  for (int x=0; x<180; x++) {
//    // convert degrees to radians then obtain sin value
//    sinVal = (sin(x*(3.1412/180)));
//    // generate a frequency from the sin value
//    toneVal = 2000+(int(sinVal*1000));
//    tone(hornPin, toneVal);
//    delay(2);
//  }

  // horn beep
//  tone(hornPin, 800, 100);
//  delay(200);
  
  
  // alarm lock
//  tone(hornPin, 800, 100);
//  delay(200);
//  tone(hornPin, 800, 100);
//  delay(5000);
  

  // alarm unlock
//  tone(hornPin, 800, 500);
//  delay(50000);

  

  // car alarm (consider making pseudo-sin wave)
//  tone(hornPin, 1000, 100);
//  delay(100);
//  noTone();
//  tone(hornPin, 400, 100);
//  delay(100);

  // low power mode


  // DEBUG: find out ADC values by blipping LED

  // Read ADC
  // buttVal = analogRead(4);

//  if (buttVal > 0 && buttVal < 1024) {
//      sectorNumber = 0;
//     
//    }
  


  
}

void fadeIn() {
  int delayTime = 1;
  for (int a=0; a<255; a++) {
    strip.clear();
    strip.setPixelColor(0, strip.Color(0, 0, 0, a));
    strip.setPixelColor(1, strip.Color(0, 0, 0, a));
    strip.show();
    delay(5);
  }
}

void flasher(int delayTime, int cycles, int pix, int r, int g, int b, int w) {
  strip.clear();
  
  for(int a=0; a<cycles; a++) {
    strip.setPixelColor(pix, strip.Color(r, g, b, w));
    strip.show();
    delay(delayTime);
    strip.setPixelColor(pix, strip.Color(0, 0, 0, 0));
    strip.show();
    delay(delayTime);
  }
  
}

/*  NOTES
 *   Low power: https://homecircuits.eu/blog/low-power-picopower-attiny13a/
 *   Check microtone lib for the horn
 */
