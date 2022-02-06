/**
 * A basic example of enabling or disabling an EventButton.
 */
#include <EventButton.h>

/**
 * Instantiate an EventButton.
 */
EventButton button1(2);


/** 
 * Instantiate the button to enable or disable the button above
 */
EventButton button2(4);


/**
 * Functions to handle the 'clicked' events for each button
 * Can be called anything but requires EventButton& 
 * as its only parameter.
 * I tend to prefix with 'on' and suffix with the 
 * event type.
 */

void onbutton1Clicked(EventButton& eb) {
  Serial.print("button1 clickCount: ");
  Serial.println(eb.clickCount());
}
 
void onbutton2Clicked(EventButton& eb) {
  Serial.print("button2 clickCount: ");
  Serial.println(eb.clickCount());
  //Toggle enable for button1
  //Note: this is not the EventButton 'eb' passed to the function.
  button1.enabled() ? button1.enable(false) : button1.enable();
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(500);
  Serial.println("EventButton Enable/Disable Example");

  //Link the event(s) to your function
  button1.setClickHandler(onbutton1Clicked);
  button2.setClickHandler(onbutton2Clicked);
}

void loop() {
  // put your main code here, to run repeatedly:
  // You must call update() for every defined EventButton.
  // This will update the state of the button and 
  // fire the appropriate events.
  button1.update();
  button2.update();
}
