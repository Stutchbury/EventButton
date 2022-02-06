/**
 * This example demostrates how to create multiple buttons.
 * 
 */
#include <EventButton.h>

/**
 * Instatiate an EventButton.
 * For Arduino Uno, the hardware interrupts are pins 2 & 3
 * For Teensy, you can use any digital pin.
 */
EventButton firstButton(4);
EventButton secondButton(14);
//. . .
EventButton nthButton(15);

/**
 * A function to handle the firstButton 'clicked' event
 */
void onFirstButtonClicked(EventButton& eb) {
  Serial.print("First button clickCount: ");
  Serial.println(eb.clickCount());
}


/**
 * A function to handle the secondButton 'clicked' event
 */
void onSecondButtonClicked(EventButton& eb) {
  Serial.print("Second button clickCount: ");
  Serial.println(eb.clickCount());
}

/**
 * A function to handle the nthButton 'clicked' event
 */
void onNthButtonClicked(EventButton& eb) {
  Serial.print("Nth button clickCount: ");
  Serial.println(eb.clickCount());
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(500);
  Serial.println("EventButton multiple button example");

  //Link the event(s) to your function
  firstButton.setClickHandler(onFirstButtonClicked);
  secondButton.setClickHandler(onSecondButtonClicked);
  nthButton.setClickHandler(onNthButtonClicked);



}

void loop() {
  // put your main code here, to run repeatedly:
  // You must call update() for every defined EventButton.
  firstButton.update();
  secondButton.update();
  nthButton.update();
}
