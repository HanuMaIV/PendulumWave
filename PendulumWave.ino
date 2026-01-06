/*
 *  PendulumWave.ino
 *
 *  Created: 11/27/2025 
 *  Author: Brendan Miranda
 */ 

// setup midi libary to be utilized / controlled by ultrasonic sensors.
#include "MIDIUSB.h"

// First parameter is the event type (0x09 = note on, 0x08 = note off).
// Second parameter is note-on/note-off, combined with the channel.
// Channel can be anything between 0-15. Typically reported to the user as 1-16.
// Third parameter is the note number (48 = middle C).
// Fourth parameter is the velocity (64 = normal, 127 = fastest).

// function for sending midi note
void noteOn(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOn = {0x09, 0x90 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOn);
}

// function for turning off midi note
void noteOff(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOff = {0x08, 0x80 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOff);
}
// end of midi library setup

/* To be used in loop to turn on and off a midi note per conditional statement.
  Accepts arguements of channel, pitch and velocity. MidiUSB.flush guarantees MIDI delivery. */
void attackDecay(int x, int y, int z){
  noteOn(x, y, z);   // Channel, note, velocity
  MidiUSB.flush();
  noteOff(x, y, z);  // Channel, note, velocity
  MidiUSB.flush();
}

// setup constant to map arduino pin numbers to pin names. This can change depending on how you setup the pins.
const int sensorOneTrigPin = 9;
const int sensorOneEchoPin = 10;
const int sensorTwoTrigPin = 11;
const int sensorTwoEchoPin = 12;
const int sensorThreeTrigPin = 6;
const int sensorThreeEchoPin = 7;

// boolean values that are used to determined if an object has left the sensor area before retriggering sound.
bool repeatToneOne = false;
bool repeatToneTwo = false;
bool repeatToneThree = false;

// constants used by applications to be maps to ultasonic sensor duration calculations
float durationOne, durationTwo, durationThree;
float distanceOne, distanceTwo, distanceThree;

// setup pins for app
void setup() {
  pinMode(sensorOneTrigPin, OUTPUT);
  pinMode(sensorOneEchoPin, INPUT);
  pinMode(sensorTwoTrigPin, OUTPUT);
  pinMode(sensorTwoEchoPin, INPUT);
  pinMode(sensorThreeTrigPin, OUTPUT);
  pinMode(sensorThreeEchoPin, INPUT);
  Serial.begin(115200);
  // Serial.begin(9600); // old serial
}

// main loop 
void loop() {

  // sensor one
  digitalWrite(sensorOneTrigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(sensorOneTrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(sensorOneTrigPin, LOW);

  durationOne = pulseIn(sensorOneEchoPin, HIGH); //receive duration from sensor
  distanceOne = (durationOne * 0.0341) / 2 * 0.393701; // calculation distance based on measured duration and speed of sound (divided by 2 because of 2 trips)

  if (distanceOne <= 12 && repeatToneOne == false) {
    attackDecay(2,48,30); // midi event is triggered
    repeatToneOne = true; // repeat tone set to true (this will only happen if an object has moved out of distance. this prevents retriggers by an object that remains in the sensor path)
  } else if (distanceOne > 12) {
    repeatToneOne = false; // object has moved out of sensor range and sets up repeat tone value to false and sensor one will be ready to trigger again.
  }

  // sensor two
  
  
  digitalWrite(sensorTwoTrigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(sensorTwoTrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(sensorTwoTrigPin, LOW);

  durationTwo = pulseIn(sensorTwoEchoPin, HIGH);
  distanceTwo = (durationTwo * 0.0341) / 2 * 0.393701;

  if (distanceTwo <= 12 && repeatToneTwo == false) {
    attackDecay(0, 60, 64);
    repeatToneTwo = true;
  } else if (distanceTwo > 12) {
    repeatToneTwo = false;
  }

  // sensor three
  digitalWrite(sensorThreeTrigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(sensorThreeTrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(sensorThreeTrigPin, LOW);

  durationThree = pulseIn(sensorThreeEchoPin, HIGH);
  distanceThree = (durationThree * 0.0341) / 2 * 0.393701;

  if (distanceThree <= 12 && repeatToneThree == false) {
    attackDecay(0, 72, 64);
    repeatToneThree = true;

  } else if (distanceThree > 12) {
    repeatToneThree =false;
  }

  delay(50);
  
}
