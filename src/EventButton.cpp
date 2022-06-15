#include "EventButton.h"


EventButton::EventButton(byte switchPin)
  : bounce(new Bounce()) {
  pinMode(switchPin, INPUT_PULLUP); //Set pullup first
  // Top tip From PJRC's Encoder - without this delay the
  // long-press doesn't fire on first press.
  // allow time for a passive R-C filter to charge
  // through the pullup resistors, before reading
  // the initial state
  delayMicroseconds(2000); //Delay
  bounce->attach(switchPin, INPUT_PULLUP); //then attach button
}

EventButton::EventButton() {
  haveButton = false;
}

void EventButton::onPress() {
  longPressEnabled = true;
  if (pressed_cb != NULL) pressed_cb(*this);
}

void EventButton::onRelease() {
  if (previousState == HIGH) {
    clickFired = false;
    clickCounter++;
    prevClickCount = clickCounter;
  }
  if (released_cb != NULL) released_cb(*this);
}

/**
 * An empty update hook that can be overriden by subclasses
 */
void EventButton::onUpdate() {}


void EventButton::update() {
  if (_enabled) {
    //button update (fires pressed/released callbacks)
    if (haveButton && bounce->update()) {
      lastEventMs = millis();
      idleFlagged = false;
      if (changed_cb != NULL) changed_cb(*this);
      _buttonState = bounce->read();
      if (bounce->fell()) {
        previousState = HIGH;
        onPress();
      }
      else if (bounce->rose()) {
        onRelease();
        previousState = LOW;
      }
    }
    //Allow subclasses to hook into the update() process
    onUpdate();
    //fire long press callbacks
    if (haveButton && longPressEnabled && LOW == bounce->read()) {
      if (bounce->currentDuration() > (longClickDuration * (longPressCounter + 1))) {
        lastEventMs = millis();
        if ((repeatLongPress || longPressCounter == 0) && long_press_cb != NULL) {
          long_press_cb(*this);
        }
        longPressCounter++;
      }
    }
    //fire button click callbacks
    if (haveButton && !clickFired && _buttonState == HIGH && bounce->currentDuration() > multiClickInterval) {
      clickFired = true;
      if (bounce->previousDuration() > longClickDuration) {
        clickCounter = 0;
        prevClickCount = 1;
        longPressCounter = 0;
        if (long_click_cb != NULL) long_click_cb(*this);
      }
      else {
        if (clickCounter == 3 && triple_click_cb != NULL) {
          triple_click_cb(*this);
        }
        else if (clickCounter == 2 && double_click_cb != NULL) {
          double_click_cb(*this);
        }
        else {
          if (click_cb != NULL) click_cb(*this);
        }
        clickCounter = 0;
      }
    }
    //fire idle timeout callback
    if (!idleFlagged && idle_cb != NULL && msSinceLastEvent() > idleTimeout) {
      idleFlagged = true;
      idle_cb(*this);
    }
  }
}

void EventButton::setChangedHandler(ButtonCallback f) { changed_cb = f; }

void EventButton::setPressedHandler(ButtonCallback f) { pressed_cb = f; }

void EventButton::setReleasedHandler(ButtonCallback f) { released_cb = f; }

void EventButton::setClickHandler(ButtonCallback f) { click_cb = f; }

void EventButton::setLongClickHandler(ButtonCallback f) { long_click_cb = f; }

void EventButton::setDoubleClickHandler(ButtonCallback f) { double_click_cb = f; }

void EventButton::setTripleClickHandler(ButtonCallback f) { triple_click_cb = f; }

void EventButton::setLongPressHandler(ButtonCallback f, bool repeat /*=false*/) {
  long_press_cb = f;
  repeatLongPress = repeat;
}

void EventButton::setIdleHandler(ButtonCallback f) { idle_cb = f; }

void EventButton::setDebounceInterval(unsigned int intervalMs) { bounce->interval(intervalMs); }

void EventButton::setMultiClickInterval(unsigned int intervalMs) { multiClickInterval = intervalMs; }

void EventButton::setLongClickDuration(unsigned int longDurationMs) { longClickDuration = longDurationMs; }

void EventButton::setLongPressRepeat(bool repeat /*=false*/) { repeatLongPress = repeat; }

void EventButton::setIdleTimeout(unsigned int timeoutMs) { idleTimeout = timeoutMs; }

void EventButton::setUserId(unsigned int identifier) { _userId = identifier; }

void EventButton::setUserState(unsigned int s) { _userState = s; }

bool EventButton::buttonState() { return bounce->read(); }

unsigned char EventButton::clickCount() { return prevClickCount; }

unsigned long EventButton::currentDuration() { return bounce->currentDuration(); }

unsigned long EventButton::previousDuration() { return bounce->previousDuration(); }

uint8_t EventButton::longPressCount() { return longPressCounter + 1; }

unsigned long EventButton::msSinceLastEvent() { return millis() - lastEventMs; }

unsigned int EventButton::userId() { return _userId; }

unsigned int EventButton::userState() { return _userState; }

bool EventButton::isPressed() { return buttonState() == LOW; }

bool EventButton::enabled() { return _enabled; }

void EventButton::enable(bool e) {
  _enabled = e;
}


