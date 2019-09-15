#include <MIDI.h>
#include <Adafruit_NeoPixel.h>
#define LED 13
#ifdef __AVR__
#include <avr/power.h>
#endif

#define BRIGHTNESS 5
#define PIN 6


MIDI_CREATE_DEFAULT_INSTANCE();



Adafruit_NeoPixel strip = Adafruit_NeoPixel(144, PIN, NEO_GRB + NEO_KHZ800);
int lastNote = 0;

int noteOrder[] = {50, 10, 23, 74};
int currentNote = 0;

//int noteOrder2[][5] = {{85, 86, 76, 0}, //SONG - FUR ELISE,led 1, led2, note number, 0 for no double note, 1 for double note
//  {83, 84, 75, 0},
//  {85, 86, 76, 0},
//  {83, 84, 75, 0},
//  {85, 86, 76, 0},
//  {75, 76, 71, 0},
//  {81, 82, 74, 0},
//  {77, 78, 72, 0},
//  {71, 72, 69, 1}, //
//  {24, 25, 45, 0, 1},
//  {38, 39, 52, 0, 1},
//  {48, 49, 57, 0, 1},
//  {54, 55, 60, 0},
//  {62, 63, 64, 0},
//  {71, 72, 69, 0},
//  {75, 76, 71, 1}, //
//  {14, 15, 40, 0, 1},
//  {38, 39, 52, 0, 1},
//  {46, 47, 56, 0, 1},
//  {62, 63, 64, 0},
//  {70, 71, 68, 0},
//  {75, 76, 71, 0},
//  {77, 78, 72, 1}, //
//  {24, 25, 45, 0, 1},
//  {38, 39, 52, 0, 1},
//  {48, 49, 57, 0, 1},
//  {62, 63, 64, 0},
//  {85, 86, 76, 0}, //
//  {83, 84, 75, 0},
//  {85, 86, 76, 0},
//  {83, 84, 75, 0},
//  {85, 86, 76, 0},
//  {75, 76, 71, 0},
//  {81, 82, 74, 0},
//  {77, 78, 72, 0},
//  {71, 72, 69, 1}, //
//  {24, 25, 45, 0, 1},
//  {38, 39, 52, 0, 1},
//  {48, 49, 57, 0, 1},
//  {54, 55, 60, 0},
//  {62, 63, 64, 0},
//  {71, 72, 69, 0},
//  {75, 76, 71, 1},
//  {14, 15, 40, 0, 1},
//  {38, 39, 52, 0, 1},
//  {46, 47, 56, 0, 1},
//  {62, 63, 64, 0},
//  {77, 78, 72, 0},
//  {75, 76, 71, 0},
//  {71, 72, 69, 1},
//  {24, 25, 45, 0, 1},
//  {38, 39, 52, 0, 1},
//  {48, 49, 57, 0, 1}
//};
int noteOrder2[][5] = {{46, 47, 56, 1}, //SONG - MOONLIGHT SONATA,led 1, led2, note number, 0 for no double note, 1 for double note
    {32, 33, 49, 0, 1},
    {56, 57, 61, 0},
    {62, 63, 64, 0},
    {46, 47, 56, 0},//
    {56, 57, 61, 0},
    {62, 63, 64, 0},
    {46, 47, 56, 0},//
    {56, 57, 61, 0},
    {62, 63, 64, 0},
    {46, 47, 56, 0},//
    {56, 57, 61, 0},
    {62, 63, 64, 0},
    {46, 47, 56, 1},
    {28, 29, 47, 0,1},
    {56, 57, 61, 0},
    {62, 63, 64, 0},
    {46, 47, 56, 0},//
    {56, 57, 61, 0},
    {62, 63, 64, 0},
    {46, 47, 56, 0},//
    {56, 57, 61, 0},
    {62, 63, 64, 0},
    {46, 47, 56, 0},//
    {56, 57, 61, 0},
    {62, 63, 64, 0},
    {48, 49, 57, 1},
    {24, 25, 45, 0,1},
    {56, 57, 61, 0},
    {62, 63, 64, 0},
    {48, 49, 57, 0},
    {56, 57, 61, 0},
    {62, 63, 64, 0},
    {48, 49, 57, 1},
    {18, 19, 42, 0,1},
    {58, 59, 62, 0},
    {66, 67, 66, 0},
    {48, 49, 57, 0},
    {58, 59, 62, 0},
    {66, 67, 66, 0},
    {46, 47, 56, 1},
    {22, 23, 44, 0,1},
    {54, 55, 60, 0},
    {66, 67, 66, 0},
    {46, 47, 56, 0},
    {56, 57, 61, 0},
    {62, 63, 64, 0},
    {46, 47, 56, 1},
    {22, 23, 44, 0,1},
    {56, 57, 61, 0},
    {60, 61, 63, 0},
    {42, 43, 54, 0},
    {54, 55, 60, 0},
    {60, 61, 63, 0},
    {38, 39, 52, 1},
    {32, 33, 49, 0,1},
    {46, 47, 56, 0},
    {56, 57, 61, 0},
    {46, 47, 56, 0},
    {56, 57, 61, 0},
    {62, 63, 64, 0}
  };


bool notePressed;
uint32_t green = strip.Color(0, 255, 0); //Colour declarations
uint32_t red = strip.Color(255, 0, 0);
uint32_t blue = strip.Color(0, 0, 255);
uint32_t purple = strip.Color(255, 0, 255);
uint32_t orange = strip.Color(255, 69, 0);
uint32_t color;
int keysPressed = 0;
bool doubleNote;
int doubleNotes;

void setup() {
  Serial.begin(9600);
  pinMode (LED, OUTPUT);
  MIDI.begin(MIDI_CHANNEL_OMNI);
  MIDI.setHandleNoteOn(KeyOn);
  MIDI.setHandleNoteOff(KeyOff);
  strip.setBrightness(BRIGHTNESS);
  strip.begin();
  
  showNextNote();

  strip.show();

  //MIDI.setHandleNoteOff(KeyOff);
}
void loop() {



  //STRIPTEST//
  //  for (int i = 0; i<60; i++){
  //    strip.setPixelColor(i,strip.Color(255,0,0));
  //    strip.show();
  //    delay(500);
  //    strip.setPixelColor(i,0);
  //    strip.show();
  //  }

  //showNextNote();


  MIDI.read();//Constantly reads the midi signal coming from the piano

  //showNextNote();



}
void KeyOn(byte inChannel, byte inNote, byte inVelocity) {//What happens when a key is pressed on the piano
  keysPressed++;
  color = red;
//  if (inNote == 21 && inVelocity != 144) {
//    FurElise();
//  }
//  if (inNote == 23 && inVelocity != 144) {
//    MoonLight();
//  }

  if (noteOrder2[currentNote][2] == inNote && noteOrder2[currentNote][3] == 1) {
    strip.setPixelColor(noteOrder2[currentNote][0], orange);
    strip.setPixelColor(noteOrder2[currentNote][1], orange);
    strip.show();
    doubleNotes++;
    inNote = 0;
  }
  if (noteOrder2[currentNote + 1][2] == inNote && noteOrder2[currentNote][3] == 1) {
    strip.setPixelColor(noteOrder2[currentNote + 1][0], orange);
    strip.setPixelColor(noteOrder2[currentNote + 1][1], orange);
    strip.show();
    doubleNotes++;
    inNote = 0;
  }
  if (doubleNotes == 2) { //Only passed when the double note is successful
    currentNote += 2;
    showNextNote();
    doubleNotes = 0;
  }
  if (inNote == noteOrder2[currentNote][2]) {
    doubleNotes = 0;
    strip.setPixelColor(noteOrder2[currentNote][0], 0);
    strip.setPixelColor(noteOrder2[currentNote][1], 0);
    strip.show();
    currentNote++;
    showNextNote();
    inNote = 0;
  }


  strip.setPixelColor(noteToStripIndex(inNote), color);
  strip.setPixelColor(noteToStripIndex(inNote) + 1, color);
  strip.show();








}
void KeyOff(byte inChannel, byte inNote, byte inVelocity) {//What happens whenever a key is released on the piano
  //inNote is the note being pressed
  doubleNotes = 0;
  keysPressed--;

  color = red;

  //strip.setBrightness(10);

  strip.setPixelColor(noteToStripIndex(inNote), 0);
  strip.setPixelColor(noteToStripIndex(inNote) + 1, 0);
  strip.show();



  showNextNote();

}

void lightUpEachLight(uint32_t c, uint8_t wait) {
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

void showNextNote() {
  uint32_t color = green;
  if (noteOrder2[currentNote][4] == 1)
  {
    color = blue;
  }
  clearStrip();
  strip.show();
  if (noteOrder2[currentNote][3] != 0) {
    doubleNote = true;

    strip.setPixelColor(noteOrder2[currentNote][0], color);
    strip.setPixelColor(noteOrder2[currentNote][1], color);
    color = blue;
    strip.setPixelColor(noteOrder2[currentNote + 1][0], color);
    strip.setPixelColor(noteOrder2[currentNote + 1][1], color);
    strip.show();
  }
  else {
    strip.setPixelColor(noteOrder2[currentNote][0], color);
    strip.setPixelColor(noteOrder2[currentNote][1], color);
    strip.show();
  }
  doubleNote = false;
  color = green;
}
void clearStrip()
{
  for (int i = 0; i < 144; i++) {
    strip.setPixelColor(i, 0);

  }
  strip.show();
}
int noteToStripIndex(byte inNote) {
  byte index;

  index = (inNote - 33) * 2;
  if (inNote >= 69) {
    index--;
    return index;
  }
  return index;
}
//void FurElise() {
//
//  int noteOrder2[][5] = {{85, 86, 76, 0}, //SONG - FUR ELISE,led 1, led2, note number, 0 for no double note, 1 for double note
//    {83, 84, 75, 0},
//    {85, 86, 76, 0},
//    {83, 84, 75, 0},
//    {85, 86, 76, 0},
//    {75, 76, 71, 0},
//    {81, 82, 74, 0},
//    {77, 78, 72, 0},
//    {71, 72, 69, 1}, //
//    {24, 25, 45, 0, 1},
//    {38, 39, 52, 0, 1},
//    {48, 49, 57, 0, 1},
//    {54, 55, 60, 0},
//    {62, 63, 64, 0},
//    {71, 72, 69, 0},
//    {75, 76, 71, 1}, //
//    {14, 15, 40, 0, 1},
//    {38, 39, 52, 0, 1},
//    {46, 47, 56, 0, 1},
//    {62, 63, 64, 0},
//    {70, 71, 68, 0},
//    {75, 76, 71, 0},
//    {77, 78, 72, 1}, //
//    {24, 25, 45, 0, 1},
//    {38, 39, 52, 0, 1},
//    {48, 49, 57, 0, 1},
//    {62, 63, 64, 0},
//    {85, 86, 76, 0}, //
//    {83, 84, 75, 0},
//    {85, 86, 76, 0},
//    {83, 84, 75, 0},
//    {85, 86, 76, 0},
//    {75, 76, 71, 0},
//    {81, 82, 74, 0},
//    {77, 78, 72, 0},
//    {71, 72, 69, 1}, //
//    {24, 25, 45, 0, 1},
//    {38, 39, 52, 0, 1},
//    {48, 49, 57, 0, 1},
//    {54, 55, 60, 0},
//    {62, 63, 64, 0},
//    {71, 72, 69, 0},
//    {75, 76, 71, 1},
//    {14, 15, 40, 0, 1},
//    {38, 39, 52, 0, 1},
//    {46, 47, 56, 0, 1},
//    {62, 63, 64, 0},
//    {77, 78, 72, 0},
//    {75, 76, 71, 0},
//    {71, 72, 69, 1},
//    {24, 25, 45, 0, 1},
//    {38, 39, 52, 0, 1},
//    {48, 49, 57, 0, 1}
//  };
//
//  //if (inNote == 22)
//  currentNote = 0;
//}
//void MoonLight() {
//  int noteOrder2[][5] = {{56, 46, 47, 1}, //SONG - MOONLIGHT SONATA,led 1, led2, note number, 0 for no double note, 1 for double note
//    {49, 32, 33, 0, 1},
//    {61, 56, 57, 0},
//    {64, 62, 63, 0},
//    {56, 46, 47, 1},
//    {61, 56, 57, 0},
//    {64, 62, 63, 0}
//
//  };
//  currentNote = 0;
//}
