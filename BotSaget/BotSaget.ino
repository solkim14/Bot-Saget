/**
 * Authors: Sol Kim and Thu Trinh
 * Version: November 2014
 * Note: some comments are for testing purposes
 */

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#include "Platform.h"
#include "SoftwareSerial.h"
#ifndef CDC_ENABLED
// Shield Jumper on SW
SoftwareSerial port(12,13);
#else
// Shield Jumper on HW (for Leonardo)
#define port Serial1
#endif
#else // Arduino 0022 - use modified NewSoftSerial
#include "WProgram.h"
#include "NewSoftSerial.h"
NewSoftSerial port(12,13);
#endif

#include "EasyVR.h"

EasyVR easyvr(port);
int count = 0;

//Groups and Commands
enum Groups
{
  GROUP_0  = 0,
  GROUP_1  = 1,
};

enum Group0 
{
  G0_BOT = 0,
};

enum Group1 
{
  G1_HELLO = 0,
  G1_TIRED = 1,
  G1_HUNGRY = 2,
  G1_HOBBY = 3,
  G1_BUTTS = 4,
  G1_NAME = 5,
  G1_SING = 6,
  G1_HAPPY = 7,
  G1_FORWARD = 8,
  G1_BACK = 9,
  G1_LEFT = 10,
  G1_RIGHT = 11,
  G1_DANCE = 12,
  G1_FOOD = 13,
  G1_IDOL = 14,
  G1_UP = 15,
  G1_HEY = 16,
  G1_INTRODUCTION = 17,
  G1_HRU = 18,
  G1_FINALS = 19,
  G1_MITZVAH = 20,
};


EasyVRBridge bridge;

int8_t group, idx;
// end easyvr

int led = 8;
int BUTTON = 2;  // feed me button

int photocellPin = 0;     // the cell and 10K pulldown are connected to a0
int photocellReading;     // the analog reading from the sensor divider
int mode = 0; // state changes, 1: tiredness, 2: hunger, 3: happiness
int hungry = 0;
int tired = 0;
int unhappy = 0;

int happiness = 30;
int hunger = 30;
//int tiredness = 30;

int time = 0;

void setup()
{
  pinMode(BUTTON, INPUT);
  pinMode(led, OUTPUT);
  Serial.begin(9600);

#ifndef CDC_ENABLED
  // bridge mode?
  if (bridge.check())
  {
    cli();
    bridge.loop(0, 1, 12, 13);
  }
  // run normally
  Serial.begin(9600);
#else
  // bridge mode
  if (bridge.check())
  {
    port.begin(9600);
    bridge.loop(port);
  }
#endif
  port.begin(9600);

  while (!easyvr.detect()) {
    delay(1000);
  }
  
  digitalWrite(led, LOW);
  easyvr.setTimeout(5);
  easyvr.setLanguage(0);

  group = EasyVR::TRIGGER; //<-- start group (customize)
}

void action();

void loop()
{ 
  digitalWrite(led, HIGH);
  Serial.println(group);
  easyvr.recognizeCommand(group);

  do
  {
    time++;

    // can do some processing while waiting for a spoken command
    if (digitalRead(BUTTON) == HIGH) {
      hunger += 10; 
      Serial.println('E');
      delay(1000);
    }

    // light sensor measures tiredness
    photocellReading = analogRead(photocellPin);
    if (photocellReading <= 300 && mode != 1) {
      Serial.println('H');
      mode = 1;
      tired = 1;
      delay(3000);
    }  else if (photocellReading > 300 && mode == 1 && tired == 1) {
      Serial.println('I');
      mode = 0; 
      delay(3000);
    }
    
    // hunger mode trumps all
    if ((mode == 0 || mode == 3) && hunger <= 20) {
      Serial.println('K');
      mode = 2;
    } else if (mode == 2 && hunger > 20) {
      mode = 0; 
    }
    
    // happiness is next
    if (mode == 0 && happiness <= 20) {
      Serial.println('P');
      mode = 3;
    } else if (mode == 3 && happiness > 20) {
      mode = 0; 
      happiness += 10;
    }
    
    // every so often, decrement happiness and hunger
    if (time % 100000 == 0) {
      if (mode == 0 || mode == 3) happiness--;
      if (mode == 0 || mode == 2) hunger--;
    }

    if (happiness < 20) {
      Serial.println('P');
      delay(3000);
    }
  }
  while (!easyvr.hasFinished());

  digitalWrite(led, LOW);
  
  idx = easyvr.getWord();
  if (idx >= 0)
  {
    // built-in trigger (ROBOT)
    return;
  }
  idx = easyvr.getCommand();
  if (idx >= 0)
  {
    // print debug message
    uint8_t train = 0;
    char name[32];
    Serial.print(idx);
    if (easyvr.dumpCommand(group, idx, name, train))
    {

    }
    else
      easyvr.playSound(0, EasyVR::VOL_FULL);
    ``// perform some action
    action();
  }
  else // errors or timeout
  {
    int16_t err = easyvr.getError();
    if (err >= 0)
    {
      count++;
    }

    if (count == 3)     //if 3 errors are sent do something
    {
      group = GROUP_0;
      switch (idx) {
      case G0_BOT:
        group = GROUP_1;
      }
      count = 0;
    }
  }
}

void action()
{
  switch (group)
  {
  case GROUP_0:
    switch (idx)
    {
    case G0_BOT:
      // group = GROUP_X; <-- or jump to another group X for composite commands
      group = GROUP_1;
      happiness += 10;
      break;
    }
    break;
  case GROUP_1:
    switch (idx)
    {
    case G1_HELLO:
      group = GROUP_0;
      Serial.println('R');
      delay(0);
      break;
    case G1_TIRED:
      group = GROUP_0;
      // if not tired N
      if (tired) Serial.println('M');
      else Serial.println('N');
      delay(0);
      break;
    case G1_HUNGRY:
      group = GROUP_0;
      // if not hungry L
      if (hungry == 0) {  // stuffed
        Serial.println('L');
      } else {
        Serial.println('K');
      }
      delay(0);
      break;
    case G1_HOBBY:
      group = GROUP_0;
      Serial.println('J');
      delay(0);
      break;
    case G1_BUTTS:
      group = GROUP_0;
      Serial.println('F');
      delay(0);
      break;
    case G1_NAME:
      group = GROUP_0;
      Serial.println('G');
      delay(0);
      break;
    case G1_SING:
      group = GROUP_0;
      Serial.println('!');
      delay(0);
      break;
    case G1_HAPPY:
      group = GROUP_0;
      Serial.println('O');
      delay(0);
      break;
    case G1_FORWARD:
      group = GROUP_0;
      Serial.println('A');
      delay(0);
      break;
    case G1_BACK:
      group = GROUP_0;
      Serial.println('B');
      delay(0);
      break;
    case G1_LEFT:
      group = GROUP_0;
      Serial.println('C');
      delay(0);
      break;
    case G1_RIGHT:
      group = GROUP_0;
      Serial.println('D');
      delay(0);
      break;
    case G1_DANCE:
      group = GROUP_0;
      Serial.println('Q');
      delay(0);
      break;
    case G1_FOOD:
      group = GROUP_0;
      Serial.println('S');
      delay(0);
      break;
    case G1_IDOL:
      group = GROUP_0;
      Serial.println('U');
      delay(0);
      break;
    case G1_UP:
      group = GROUP_0;
      Serial.println('T');
      delay(0);
      break;
    case G1_HEY:
      group = GROUP_0;
      Serial.println('V');
      delay(0);
      break;
    case G1_INTRODUCTION:
      group = GROUP_0;
      Serial.println('W');
      delay(0);
      break;
    case G1_HRU:
      group = GROUP_0;
      Serial.println('X');
      delay(0);
      break;
    case G1_FINALS:
      group = GROUP_0;
      Serial.println('Y');
      delay(0);
      break;
    case G1_MITZVAH:
      group = GROUP_0;
      Serial.println('Z');
      delay(0);
      break;
    }
    break;
  }
}
