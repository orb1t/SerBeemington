#import "application.h"
#import "mpu9250.h"
#import "dotstar.h"
#import "state.h"
#import "entity.h"
#import "subject.h"
#import "event.h"

#define DOTSTAR_GRB (1 | (0 << 2) | (2 << 4))
#define NUM_EVENTS 10

//In which we combine Lights + Motion + Games
class Frisbeem: public Subject, public Entity
{
public:
  Frisbeem(): _mpu(), _strip(54){};//Constructor
  ~Frisbeem() {}; //Destructor

  //Physical parameters
  float momentOfInertial = 0.008748;

  //States
  StateSwitch _powerState;
  StateSwitch _motionState;
  StateSwitch _lightMode;
  StateSwitch _gameMode;

  //Hardware
  MPU_9250 _mpu;
  Adafruit_DotStar _strip;

  //Connection
  TCPClient _client;

  //Events
  Event *_events[ NUM_EVENTS ];
  Event newEvent = Event(0);
  uint8_t _currentEventIndex = 0;
  int _eventCount;

  //Counting variables
  uint8_t whl;

  //Important Entity Functions
  void initlaize();
  void update();

  //Color Functions
  void rainbow( uint8_t wait );
  void colorAll(uint32_t c, uint8_t wait);
  void colorWipe(uint32_t c, uint8_t wait);
  void blue();
  uint32_t wheel( byte WheelPos );

  //Event Functions
  Event genNextEvent();
  Event *getCurrentEvent();
  void setCurrentEvent( Event *event );
  void processEvents();
};
