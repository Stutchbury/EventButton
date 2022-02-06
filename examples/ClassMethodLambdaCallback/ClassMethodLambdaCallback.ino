/**
 * Example using the EventButton library with a class method 
 * as a the callback function.
 * **NOTE** Only available for ESP8266/32 and Teensy
 */
#include <EventButton.h>

/**
 * Instatiate an EventButton.
 */
EventButton eb1(4);

/**
 * A noddy class for this example
 */
class Foo {

  public:
    /**
     * A class method to handle the 'clicked' event
     * Can be called anything but requires EventButton& 
     * as its only parameter.
     * 
      */
    void onEb1Clicked(EventButton& eb) {
      Serial.print("eb1 clickCount: ");
      Serial.println(eb.clickCount());
    }
    
};

/**
 * Instantiate the class
 */
Foo foo;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(500);
  Serial.println("EventButton Class Method Callback Example");

  //Link the event(s) to your class method
  //Not quite as simple as a static function
  eb1.setClickHandler([&](EventButton &btn) {
    foo.onEb1Clicked(btn);
  });

}

void loop() {
  // put your main code here, to run repeatedly:
  // You must call update() for every defined EventButton.
  // This will update the state of the button and 
  // fire the appropriate events.
  eb1.update();
}
