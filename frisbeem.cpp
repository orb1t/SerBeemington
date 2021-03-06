#include "frisbeem.h"
#include "games.h"

void Frisbeem::initlaize(){
  //Initalize communication
  _com.initialize();
  _com.log("Communication Started...");
  _com.log("Go For Initlaize");
  //Update MPU
  _com.log("Go For Brains");
  _mpu.initialize();
  //Update Strip
  _com.log("Go For Lights");
  _lights.initlaize();

  _com.log("Listening To Game");
  Firework *_currentGame = new Firework();
  addObserver( _currentGame );

  //Serial.println("Motion State Creation");
  _com.log("Go For Loop");
}

void Frisbeem::update(){
  //Open COM to end client if conditions are correct
  _com.open();
  //Tick The Log So It Can Output Periodically
  _com.tick();

  _com.log("Beeming Into Space...");
  //Update COM layer
  _com.update();

  //Handle Other Stuff
  _com.log("Updating...");
  //Update MPU
  start = micros();
  //Physics Update Inner Loop
  while ( micros() - start < renderInterval) {
    _com.log("Updating MPU");
    _mpu.update();
    updateThetaOffset();
    processMotion();
    //Send telemetry here... idk?
    _com.send_telemetry();
  }
  //Initialize Lights
  _com.log("Puttin On The High Beems!");
  _lights.update(0);

  //Close COM to end client
  _com.close();
}

void Frisbeem::updateThetaOffset()
{
  thisTime = micros();

  //Integrate For Theta
  if ( abs(_mpu.G.z) > 0.1){
    thetaOffset -= _mpu.G.z * (thisTime - lastTime) / 1000000;
  }
  //Catch & Adjust For Theta Over Limit
  if (thetaOffset > 360){
    thetaOffset -= 360;
  }
  else if (thetaOffset < 0){
    thetaOffset += 360;
  }

  lightOffset = thetaOffset / degPerPixel;

  //Preserve Time Calculations
  lastTime = thisTime;
}

void Frisbeem::processMotion()
{ //Generate A New Event & Add to circular buffer after deleting current item
  //Serial.print("Getting New Event #");Serial.println(_eventCount);
  currentMotionEvent = genNextEvent();
  currentMotionEvent.visit( &_motionState );//StateSwitchCall
  currentMotionEvent.visit( this );//Subject Call notify()

}

MotionEvent Frisbeem::genNextEvent()
{ //For Now Look At Omegea (w)
  return MotionEvent( _mpu.G, _mpu.A, _mpu.V, _mpu.X );
}
