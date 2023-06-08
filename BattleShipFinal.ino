#include <Adafruit_CircuitPlayground.h> //circuit playground library

volatile bool leftButtonFlag = 0;
volatile bool rightButtonFlag = 0;
volatile bool switchFlag = 0;
volatile bool switchActivated = 1;
bool hitRF = 0;
bool hitRS = 0;
bool hitLF = 0;
bool hitLS = 0;

volatile int leftCount = 4;
volatile int rightCount = 5;
volatile int switchCount = 0;
int leftShipOne;
int leftShipTwo;
int rightShipOne;
int rightShipTwo;

int hitShip[2][2] = {
  {420, 100}, {316, 300}
};

int ending[7][2] = { // duh duh duh duh duh duh!
  {493, 650}, 
  {415, 125}, 
  {493, 125}, 
  {440, 250}, 
  {369, 250}, 
  {440, 250},
  {493, 1000}
};




void setup() {
  CircuitPlayground.begin();
  Serial.begin(9600);

  pinMode(4, INPUT_PULLDOWN);
  pinMode(5, INPUT_PULLDOWN);
  pinMode(7, INPUT_PULLUP);
  
  attachInterrupt(4, leftMove, FALLING);
  attachInterrupt(5, rightMove, FALLING);
  attachInterrupt(7, switchMove, CHANGE);
}

void loop() {
  
  if (switchFlag) {
    
    switchCount++;
    
    if (switchCount == 1) {
      
      leftShipOne = leftCount;
      Serial.println(leftShipOne);
      CircuitPlayground.clearPixels();
      CircuitPlayground.setPixelColor(5, 0, 0, 255);
      
    } else if (switchCount == 2) {
      
      rightShipOne = rightCount;
      Serial.println(rightShipOne);
      CircuitPlayground.clearPixels();
      CircuitPlayground.setPixelColor(4, 0, 0, 255);   


    } else if (switchCount == 3) {

      leftShipTwo = leftCount;
      Serial.println(leftShipTwo);    
      CircuitPlayground.clearPixels();
      CircuitPlayground.setPixelColor(5, 0, 0, 255);
      
    } else if (switchCount == 4) {

      rightShipTwo = rightCount; 
      Serial.println(rightShipTwo);  
      CircuitPlayground.clearPixels();
      CircuitPlayground.setPixelColor(5, 0, 0, 255);  

    } else if (switchCount > 4 && switchCount % 2 != 0) {

      if (rightShipOne == rightCount && !hitRF) {

        CircuitPlayground.setPixelColor(5, 255, 0, 0); 
        CircuitPlayground.setPixelColor(6, 255, 0, 0);
        CircuitPlayground.setPixelColor(7, 255, 0, 0); 
        CircuitPlayground.setPixelColor(8, 255, 0, 0);
        CircuitPlayground.setPixelColor(9, 255, 0, 0);

        for (int t = 0; t < 2; t++) {
          CircuitPlayground.playTone(hitShip[t][0], hitShip[t][1]);
        }

        hitRF = 1;

      } else if (rightShipTwo == rightCount && !hitRS) {

        CircuitPlayground.setPixelColor(5, 255, 0, 0); 
        CircuitPlayground.setPixelColor(6, 255, 0, 0);
        CircuitPlayground.setPixelColor(7, 255, 0, 0); 
        CircuitPlayground.setPixelColor(8, 255, 0, 0);
        CircuitPlayground.setPixelColor(9, 255, 0, 0);

        for (int t = 0; t < 2; t++) {
          CircuitPlayground.playTone(hitShip[t][0], hitShip[t][1]);
        }

        hitRS = 1;

      }

      CircuitPlayground.setPixelColor(4, 0, 0, 255);

    } else if (switchCount > 4 && switchCount % 2 == 0) {
      
      if (leftShipOne == leftCount && !hitLF) {

        CircuitPlayground.setPixelColor(0, 255, 0, 0); 
        CircuitPlayground.setPixelColor(1, 255, 0, 0);
        CircuitPlayground.setPixelColor(2, 255, 0, 0); 
        CircuitPlayground.setPixelColor(3, 255, 0, 0);
        CircuitPlayground.setPixelColor(4, 255, 0, 0); 

        for (int t = 0; t < 2; t++) {
          CircuitPlayground.playTone(hitShip[t][0], hitShip[t][1]);
        }

        hitLF = 1;
         
      } else if (leftShipTwo == leftCount && !hitLS) {

        CircuitPlayground.setPixelColor(0, 255, 0, 0); 
        CircuitPlayground.setPixelColor(1, 255, 0, 0);
        CircuitPlayground.setPixelColor(2, 255, 0, 0); 
        CircuitPlayground.setPixelColor(3, 255, 0, 0);
        CircuitPlayground.setPixelColor(4, 255, 0, 0);

        for (int t = 0; t < 2; t++) {
          CircuitPlayground.playTone(hitShip[t][0], hitShip[t][1]);
        }

        hitLS = 1;

      }

      CircuitPlayground.setPixelColor(5, 0, 0, 255);

    } else {}

    switchFlag = 0;
    switchActivated = 0;
    leftCount = 4;
    rightCount = 5;

  }

  //Code to move pixel colors based on player input
  if (switchCount == 0 || switchCount == 2) {
    if (leftButtonFlag) {
      leftCount--;
      if (leftCount < 0) {
        leftCount = 4;
      }
      CircuitPlayground.clearPixels();
      CircuitPlayground.setPixelColor(leftCount, 0, 0, 255);
      leftButtonFlag = 0;
      switchActivated = 1;
    }
  } else if (switchCount == 1 || switchCount == 3) {

    if (rightButtonFlag) {
      rightCount++;
      if (rightCount > 9) {
        rightCount = 5;
      }
      CircuitPlayground.clearPixels();
      CircuitPlayground.setPixelColor(rightCount, 0, 0, 255);
      rightButtonFlag = 0;
      switchActivated = 1;
    }

  } else if (switchCount > 3 && (switchCount % 2 == 0)) {
  
    if (leftButtonFlag) {
      rightCount++;
      if (rightCount > 9) {
        rightCount = 5;
      }
      CircuitPlayground.clearPixels();
      CircuitPlayground.setPixelColor(rightCount, 0, 0, 255);
      leftButtonFlag = 0;
      switchActivated = 1;
    } 
    
  } else if (switchCount > 3 && (switchCount % 2 != 0)) {
  
    if (rightButtonFlag) {
      leftCount--;
      if (leftCount < 0) {
        leftCount = 4;
      }
      CircuitPlayground.clearPixels();
      CircuitPlayground.setPixelColor(leftCount, 0, 0, 255);
      rightButtonFlag = 0;
      switchActivated = 1;
    }
    
  } 

  if ((hitRF && hitRS) || (hitLF && hitLS)) {
    Serial.println("Game Over Loserrrr");
    for(int x = 0; x < 10; x++) {
      CircuitPlayground.setPixelColor(x, 255, 0, 0);
    }
    for (int y = 0; y < 7; y++ ) {
      CircuitPlayground.playTone(ending[y][0], ending[y][1]);
    }
    delay(5000);
    exit(1);
  }

}

void leftMove() {
  leftButtonFlag = 1;
}
void rightMove() {
  rightButtonFlag = 1;
}
void switchMove() {
  if (switchActivated) {
    switchFlag = 1;
  }
}