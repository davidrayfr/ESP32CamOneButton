// Library One Button
// test avec ESP-32 CAM
// Bouton sur GPIO 12
// Allumage diode blanche
// Check 1 clic -> On allume la Led Blanche
// Check 2 clic
// Check Long Clic

#include <Arduino.h>
#include "OneButton.h"

#define RED_LED_PIN 33 // LED rouge: GPIO 33
#define WHITE_LED_PIN 4 // LED blanche: GPIO 4 - ESP32 CAM
#define BUTTON_PIN 12 // Bouton Branché sur GPIO 12
#define TIME_LONG_CLICK 1000 // Detection Tps Mini long clic

// Setup a new OneButton on pin PIN_INPUT
// The 2. parameter activeLOW is true, because external wiring sets the button to LOW when pressed.
OneButton button(BUTTON_PIN, true,true);

// current LED state, staring with LOW (0)
int whiteLedState = LOW;
int redLedState = LOW;
unsigned long pressStartTime;

void doubleClick()
{
Serial.println("Double Click");

}

void simpleClick()
{
Serial.println("Simple Click");

}

void longClick()
{
Serial.println("Long Click");

}

// this function will be called when the button was held down for 1 second or more.
void pressStart() {
  Serial.println("pressStart()");
  pressStartTime = millis() - 1000; // as set in setPressTicks()
} // pressStart()


// this function will be called when the button was released after a long hold.
void pressStop() {
  Serial.print("pressStop(");
  Serial.print(millis() - pressStartTime);
  Serial.println(") detected.");
} // pressStop()

void setup()
{
    Serial.begin(115200);
    Serial.println("One Button Example with ESP-32 Cam");

    // enable the standard led on pin 13.
    pinMode(WHITE_LED_PIN, OUTPUT); // sets the digital pin as output
    pinMode(RED_LED_PIN, OUTPUT); // sets the digital pin as output

    // Initiate Led
    digitalWrite(WHITE_LED_PIN, whiteLedState);
    digitalWrite(RED_LED_PIN, redLedState);

    // link the doubleclick function to be called on a doubleclick event.
    button.attachDoubleClick(doubleClick);
    button.attachClick(simpleClick);
    button.setPressTicks(1000); // that is the time when LongPressStart is called
    button.attachLongPressStart(pressStart);
    button.attachLongPressStop(pressStop);
}



void loop()
{
 
    button.tick();
    
    delay(10);
}