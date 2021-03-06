#import "lights.h"
#import "globals.h"
#import "state.h"

void Lights::initlaize()
{
  _strip.begin();
  //Loading Effect :)
  off();
  _strip.show();
  colorWipe( wheel( 255 ),20);
  _strip.show();
  delay(100);
}

void Lights::update(uint8_t wait)
{
  if (frisbeem._motionState.stateNow()->_motionData -> sleepModeActivated || !_on){
    off();
    refresh();
    delay(250);
  }
  else{ //Do Da Lights
    frisbeem._com.log("State Now");
    frisbeem._com.log( frisbeem._motionState.stateNow() -> type() );
    if ( frisbeem._motionState.currentState == MotionSwitch::REST){
        frisbeem._com.log("Case Rest");
        blue();
    }
    else if ( frisbeem._motionState.currentState == MotionSwitch::SPIN){
        frisbeem._com.log("Case Spin");
        green();
    }
    else if ( frisbeem._motionState.currentState == MotionSwitch::MOTION) {
        frisbeem._com.log("Case Motion");
        orange();
    }
    else {
        frisbeem._com.log("Default");
        red();
    }
    refresh();
  }
}

void Lights::refresh(){
  ATOMIC_BLOCK() {
   // We block so that the light timing doesn't get messed up... ya know...
   //technically speaking
   _strip.show();
  }
}

// Cool and useful color functions
void Lights::rainbow(uint8_t offset) {
  uint16_t i;
  int current;
  int numPixels = _strip.numPixels();
  if (whl > 255){
    whl = 0;
  }
  for(i=0; i< numPixels; i++) {
      current = i - offset;
      if (current < 0){ //Normal Assignment
        current = numPixels + current;
      }
    _strip.setPixelColor(current, wheel((i+whl)));
    if ( i == 0 ){
      _strip.setPixelColor(current, _strip.Color(255,0,0));
    }
  }
  whl++;
}

void Lights::quarters(uint32_t c,uint32_t c2, uint8_t offset)
{ //Split Lights by 4 and color a quarter
  uint16_t i;
  int numPixels = _strip.numPixels();
  int quarterNumber = numPixels / 4;
  int remdr = numPixels % 4;
  int current;

  for (i=0; i<numPixels; i++){
    current = i - offset;
    if (current < 0){ //Normal Assignment
      current = numPixels + current;
    }
    if ( i < numPixels / 4){
      _strip.setPixelColor(current, c);
    }
    else if ( i < numPixels * 1 / 2){
      _strip.setPixelColor(current, _strip.Color(0,0,0));
    }
    else if ( (i-1) < numPixels * 3 / 4){
      _strip.setPixelColor(current, c2);
    }
    else{
      _strip.setPixelColor(current, _strip.Color(0,0,0));
    }
  }
}

// Set all pixels in the strip to a solid color, then wait (ms)
void Lights::colorAll(uint32_t c) {
  uint16_t i;

  for(i=0; i<_strip.numPixels(); i++) {
    _strip.setPixelColor(i, c);
  }
}

// Fill the dots one after the other with a color, wait (ms) after each one
void Lights::colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<_strip.numPixels(); i++) {
    _strip.setPixelColor(i, c);
    delay(wait);
    _strip.show();
  }
}



// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Lights::wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return _strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return _strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return _strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

void Lights::orange() {
  uint16_t i, j;

  for(i=0; i<_strip.numPixels(); i++) {
      _strip.setPixelColor(i, wheel(200));
  }
}

void Lights::blue() {
  uint16_t i, j;

  for(i=0; i<_strip.numPixels(); i++) {
      _strip.setPixelColor(i, wheel(255));
  }
}

void Lights::green() {
  uint16_t i, j;

  for(i=0; i<_strip.numPixels(); i++) {
      _strip.setPixelColor(i, wheel(60));
  }
}

void Lights::red() {
  uint16_t i, j;

  for(i=0; i<_strip.numPixels(); i++) {
      _strip.setPixelColor(i, wheel(180));
  }
}
void Lights::off() {
  uint16_t i, j;

  for(i=0; i<_strip.numPixels(); i++) {
      _strip.setPixelColor(i, _strip.Color(0,0,0));
  }
}
