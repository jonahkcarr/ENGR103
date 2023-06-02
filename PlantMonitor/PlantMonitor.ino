#include <Adafruit_CircuitPlayground.h> //circuit playground library
#include <AsyncDelay.h> // async delay library

int temp;
int light;
int capacitance;
int sound;

volatile int count = 0;
volatile int countRemainder2;
volatile int countRemainder4;

volatile bool switchFlag = 0; // use for interupt
volatile bool switchState = 0;

AsyncDelay delay_1s;

volatile int soundToPixel;
volatile int tempToPixel;

void setup() {
  CircuitPlayground.begin(); // begin cicruit playground functions
  Serial.begin(9600); //begin serial output
  while(!Serial); // holds program till monitor opens

  pinMode(7, INPUT_PULLUP);
  attachInterrupt(7, soundOff, CHANGE);

  Serial.println("Starting Light Readings:");

  delay_1s.start(1000, AsyncDelay::MILLIS); //begins counting
}

void loop() {
  
  if (delay_1s.isExpired()) {
    
    temp = CircuitPlayground.temperatureF();
    light = CircuitPlayground.lightSensor();
    capacitance = CircuitPlayground.readCap(A1);
    sound = CircuitPlayground.mic.soundPressureLevel(20);
    
    count++;
    countRemainder2 = (count/4) % 2;
    countRemainder4 = count % 4;
    
    Serial.println(light); 

    if (sound > 90) {
      sound = 90;
    } else if (sound < 40) {
      sound = 40;
    } else{}

    if (temp > 110) {
      temp = 110;
    } else if (temp < 60) {
      temp = 60;      
    } else{}

    if (switchFlag) {
      delay(5);
      switchState = digitalRead(7);
      switchFlag = 0;
    }

    if (capacitance > 1000) {
      if (countRemainder2 == 0 && countRemainder4 == 0) {
        CircuitPlayground.clearPixels();
        soundToPixel = map(sound, 40, 90, 0, 9);  
        for (int x = 0; x <= soundToPixel; x++) {
          CircuitPlayground.setPixelColor(x, 0, 0, 255);
        }
      } else if (countRemainder2 != 0 && countRemainder4 == 0) {
        CircuitPlayground.clearPixels();
        tempToPixel = map(temp, 60, 110, 0, 9);
        for (int i = 0; i <= tempToPixel; i++) {
          CircuitPlayground.setPixelColor(i, 255, 0, 0);
        }
      } else {}
    } else {
      if (!switchState) {
        CircuitPlayground.clearPixels();
        CircuitPlayground.playTone(416, 100);
        delay(100);
        for (int y = 0; y < 10; y++) {
          CircuitPlayground.setPixelColor(y, 0, 255, 0);
        }   
        CircuitPlayground.playTone(486, 100);
      } else {
        CircuitPlayground.clearPixels();
        delay(100);
        for (int y = 0; y < 10; y++) {
          CircuitPlayground.setPixelColor(y, 0, 255, 0);
        }
      }
    }
    delay_1s.repeat();
  }
}

void soundOff() {
  switchFlag = 1;
}

