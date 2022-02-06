/**
 * A basic example of using the EventButton library.
 */
#include <EventButton.h>

/**
 * Instatiate an EventButton.
 * EventButton(byte switchPin);
 */
EventButton button1(4);


/**
 * A function to handle the 'clicked' event
 * Can be called anything but requires EventButton& 
 * as its only parameter.
 * I tend to prefix with 'on' and suffix with the 
 * event type.
 */
void onbutton1Clicked(EventButton& eb) {
  Serial.print("button1 clickCount: ");
  Serial.println(eb.clickCount());
}

/**
 * A function to handle the 'released' event
 * Can be called anything but requires EventButton& 
 * as its only parameter.
 */
void onbutton1Released(EventButton& eb) {
  Serial.print("button1 released: ");
  Serial.println(eb.clickCount());
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(500);
  Serial.println("EventButton Basic Example");

  //Link the event(s) to your function
  button1.setClickHandler(onbutton1Clicked);
  button1.setReleasedHandler(onbutton1Released);
}

void loop() {
  // put your main code here, to run repeatedly:
  // You must call update() for every defined EventButton.
  // This will update the state of the button and 
  // fire the appropriat events.
  button1.update();
}
