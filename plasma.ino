
#include <Adafruit_NeoPixel.h>

// On définit le pin où est connecté la patte DATA du bandeau
#define LED 0
#define nbLED 18
#define COLOR 1
#define MOTOR 6
#define MAX 2
#define SHOT 4


int color1;
int color2;

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)

//Ici, le 150 correspond au nombre de led
Adafruit_NeoPixel strip = Adafruit_NeoPixel(nbLED, LED, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.show(); // Initialise toute les led à 'off'
  pinMode(COLOR, INPUT_PULLUP);
  pinMode(MOTOR, INPUT_PULLUP);
  pinMode(MAX, INPUT_PULLUP);
  pinMode(SHOT, INPUT_PULLUP);
}

void marche(int niveau)
{
  int i,j;
  for (i = 0; i < nbLED; i++)
  {
    strip.setPixelColor(i, 0, 0, 0);
  }
  if (niveau >= 0)
  {
    for (i = 0; i < niveau; i++)
    {
      strip.setPixelColor(5-i, color1, 0, color2);
      strip.setPixelColor(11-i, color1, 0, color2);
      strip.setPixelColor(17-i, color1, 0, color2);
    }
  }
  strip.show(); // on affiche
}

void arret()
{
  int i;
  for (i = 0; i < nbLED; i++)
  {
    strip.setPixelColor(i, 0, 0, 0);
  }
  strip.show(); // on affiche
}
void loop() {
  int Delay, level;
  unsigned long time1 = 0;
  unsigned long time2 = 0;
  //      for(int i = 0; i < nbLED; i++ ) { // On fait une boucle pour définir la couleur de chaque led
  //        // setPixelColor(n° de led, Rouge, Vert, Bleu)
  //        strip.setPixelColor(i, 0, 0, 255);
  //        }
  level = -1;
  if (digitalRead(MOTOR))
  {
    if (digitalRead(COLOR))
    {
      color1 = 255;
      color2 = 0;
    }
    else
    {
      color1 = 0;
      color2 = 255;
    }
    while (digitalRead(MOTOR))
    {
      if (!digitalRead(MAX))
        Delay = 300;
      else
        Delay = 600;
      if (!digitalRead(SHOT)) {
        if (millis() > time2 + 300) {
          time2 = millis();
          level = level - 2;
        }
        if (level <= -1) level = -1;
        marche(level);
      }
      if (millis() > time1 + Delay) {
        time1 = millis();
        level++;
        if (level >= nbLED/3) level = nbLED/3;
        marche(level);
      }

    }
    arret();
  }
}
