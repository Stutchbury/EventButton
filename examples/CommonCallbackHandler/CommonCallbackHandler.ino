/**
 * An example of using a common callback for an event in the  EventButton library
 * Can be used for multi-function buttons (ie button actions are changed at runtime).
 * 
 * Note: I am using an array to store the button instances but this is 
 * not required.
 * 
 */
#include <EventButton.h>

/**
 * Instantiate multiple EventButtons
 */
EventButton buttonRow[5] = { EventButton(28), EventButton(27), EventButton(26), EventButton(25), EventButton(24) };


/**
 * A common function to handle the 'clicked' event of all buttons.
 */
void onButtonRowClicked(EventButton& eb) {
  Serial.print("button ");
  Serial.print(eb.userId());
  Serial.print(" clickCount: ");
  Serial.println(eb.clickCount());
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(500);
  Serial.println("EventButton common callback handler example");

  //Loop through the array of event buttons.
  for ( uint8_t b=0; b<5; b++ ) {
    // Give each button a userId - this defaults to 0 so 
    // must be set if you want to identify a button in the callback.
    buttonRow[b].setUserId(b);
    // Set all buttons in the button row to use the same handler
    buttonRow[b].setClickHandler(onButtonRowClicked);
  }
}

void loop() {
  //Update all buttons
  for ( uint8_t b=0; b<5; b++ ) {
    buttonRow[b].update();
  }
}
