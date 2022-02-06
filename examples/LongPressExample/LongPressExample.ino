/**
 * Example of using the EventButton long press repeat.
 */
#include <EventButton.h>

/**
 * Instatiate an EventButton.
 */
EventButton button1(4);

/**
 * A function to handle the 'clicked' event
 * Can be called anything but requires EventButton& 
 * as its only parameter.
 * I tend to prefix with 'on' and suffix with the 
 * event type.
 */
void onButton1LongPress(EventButton& eb) {
  Serial.print("button1 longPressCount: ");
  Serial.println(eb.longPressCount());
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(500);
  Serial.println("EventButton Long Press Repeat Example");

  //Link the event(s) to your function
  button1.setLongPressHandler(onButton1LongPress, true); //Second arg means repeat the long click
}

void loop() {
  // put your main code here, to run repeatedly:
  // You must call update() for every defined EventButton.
  // This will update the state of the button and 
  // fire the appropriat events.
  button1.update();
}
