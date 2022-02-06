/**
 * An event based button wrapper for 
 * Thomas Fredericks' Bounce2 library
 * https://github.com/thomasfredericks/Bounce2
 * and inspired by Lennart Hennigs Button2
 * https://github.com/LennartHennigs/Button2
 * 
 * Written for Teensy but tested on Arduino Uno and others.
 * 
 * 
 */

#ifndef EventButton_h
#define EventButton_h

#include "Arduino.h"

#ifndef Bounce2_h
  #include <Bounce2.h>
#endif

#if defined(ARDUINO_ARCH_ESP32) || defined(ESP8266) || defined(CORE_TEENSY)
  #include <functional>
#endif

class EventButton {

  protected:

    #if defined(ARDUINO_ARCH_ESP32) || defined(ESP8266) || defined(CORE_TEENSY)
      typedef std::function<void(EventButton &btn)> ButtonCallback;
    #else
      typedef void (*ButtonCallback)(EventButton &);
    #endif

  public:

    /**
     * Construct a button
     */
    EventButton(byte switchPin);


    /**
     * Read and update the state of the button.
     * Call from loop() for each defined EventButton
     */
    void update();
    
    /** ***************************************************
     * Set button callback handlers
     */

    /**
     * Fires when button state changes
     */
    void setChangedHandler(ButtonCallback f);
    
    /**
     * Fires after button is pressed down
     */
    void setPressedHandler(ButtonCallback f);
    
    /**
     * Fires after button is released but before click or long pressed handlers.
     */
    void setReleasedHandler(ButtonCallback f);
    
    /**
     * Fires after button is clicked (when pressed duration
     * is less than setLongClickDuration() (default 750ms)
     * Note: the number of multi clicks can be read from
     * EventButton.clickCount() in the callback so you are not 
     * limited to double or triple clicks - any number can be actioned.
     * If double or triple click callbacks are set, this will not be
     * fired for those events.
     */
    void setClickHandler(ButtonCallback f);
    
    /**
     * Fires after button is double clicked
     * Determined by setMultiClickInterval() (default 250ms)
     * Syntactic sugar for click handler + clickCount == 2
     */
    void setDoubleClickHandler(ButtonCallback f);
    
    /**
     * Fires when button is triple clicked
     * Syntactic sugar for click handler + clickCount == 3
     */
    void setTripleClickHandler(ButtonCallback f);

    /**
     * Fires after button is long clicked (when pressed duration
     * is greater than setLongClickDuration(ms) (default 750ms)
     * See also long press handler
     */
    void setLongClickHandler(ButtonCallback f);
    
    /**
     * Fired *while* button is long pressed. By default, this fires
     * once but can fire every setLongClickDuration by passing 'true'
     * as a second argument or via setLongPressRepeat(bool).
     * Use longPressCount() in callback to read the number of times fired
     */
    void setLongPressHandler(ButtonCallback f, bool repeat=false);
    
    
    /** ***************************************
     * Fired after the button has been idle for 
     * setIdleTimeout(ms) (default 10 seconds)
     */
    void setIdleHandler(ButtonCallback f);    

    
    /** ***************************************
     *  button setup
     */

    /**
     * Default is set in the Bounce2 library (currently 10ms)
     */
    void setDebounceInterval(unsigned int intervalMs);

    /**
     * Set the interval in ms between double, triple or
     * multi clicks
     */
    void setMultiClickInterval(unsigned int intervalMs);

    /**
     * Set the ms that defines a lonf click. Long pressed callback
     * will be fired at this interval if repeat is set to true via the
     * setLongPressHandler()
     */
    void setLongClickDuration(unsigned int longDurationMs);

    /**
     * Choose whether to repeat the long press callback
     * (default is 'false')
     */
    void setLongPressRepeat(bool repeat=false);
    
    /**
     * Set the idle timeout in ms (default 10000) 
     */
    void setIdleTimeout(unsigned int timeoutMs);

    /**
     * Set the button identifier (not unique, defaults to 0)
     * Useful when multiple buttons call the same handler.
     */
    void setUserId(unsigned int id);

    /**
     * Set the user state. Slight function creep but useful.
     * For use by implementor, ignored by library
     * eg ON, OFF, INACTIVE etc
     */
    void setUserState(unsigned int s);

    
    /** ***************************************
     *  button state
     */
     
    /**
     * Directly get the current button state from Bounce2
     */
    bool buttonState();

    /**
     * Directly get the duration of the button current state from Bounce2
     */
    unsigned long currentDuration();

    /**
     * Directly get the duration of the button previous state from Bounce2
     */
    unsigned long previousDuration();

    /**
     * The number of multi-clicks that have been fired in the clicked event
     */
    unsigned char clickCount();

    
    /**
     * The number of times the long press handler has  been fired in the 
     * button pressed event
     */
    uint8_t longPressCount();
    
    /** ***************************************
     * Returns the number of ms since any event was fired for this button
     */
    unsigned long msSinceLastEvent();

    /**
     * Get the button identifier (not unique, defaults to 0)
     */
    unsigned int userId();

    /**
     * Get the user state.
     */
    unsigned int userState();

    /**
     * Returns true if enabled
     */
    bool enabled();

    /**
     * Set enabled to true of false
     * This will enable/disable all event callbacks.
     */
    void enable(bool e=true);


  protected:

    /**
     * Empty constructor only available to subclasses
     */
    EventButton();

    ButtonCallback changed_cb = NULL;
    ButtonCallback pressed_cb = NULL;
    ButtonCallback released_cb = NULL;
    ButtonCallback click_cb = NULL;
    ButtonCallback long_click_cb = NULL;
    ButtonCallback double_click_cb = NULL;
    ButtonCallback triple_click_cb = NULL;
    ButtonCallback long_press_cb = NULL;
    ButtonCallback idle_cb = NULL;

    /**
     * Hooks that subclasses can overide
     * to change/add to the update() behaviour
     */
    virtual void onPress();
    virtual void onRelease();
    virtual void onUpdate();
    bool longPressEnabled = true;

    boolean haveButton = true;
    bool _enabled = true;
    bool idleFlagged = false;
    unsigned long lastEventMs = millis();
    unsigned char _buttonState = HIGH;
    unsigned char prevClickCount = 0;
    unsigned char clickCounter = 0;
    bool clickFired = true;

  private:
    Bounce* bounce;
    unsigned int multiClickInterval = 250;
    unsigned int longClickDuration = 750;
    unsigned int longPressCounter = 0;
    unsigned long idleTimeout = 10000;
    bool previousState = LOW;
    bool repeatLongPress = false;

    unsigned int _userId = 0;
    unsigned int _userState = 0;



};

#endif


