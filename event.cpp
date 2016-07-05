#include "event.h"
#include "3dmath.h"

void Event::visit(State *s) { s -> handleInput(*this); }; //State
void Event::visit(Subject *sj) { sj -> notify(*this); }; //Subject
void Event::visit(Observer *o) { o -> onNotify(*this); }; //Observer
void Event::visit(StateSwitch *s){ s -> handleInput(*this); }; //State

MotionEvent::MotionEvent( VectorFloat &Gin, VectorFloat &Ain, VectorFloat &Vin, VectorFloat &Xin )
{
G = Gin;
A = Ain;
V = Vin;
X = Xin;
};

void MotionEvent::visit(State *s) { s -> handleInput(*this); }; //State
void MotionEvent::visit(Subject *sj) { sj -> notify(*this); }; //Subject
void MotionEvent::visit(Observer *o) { o -> onNotify(*this); }; //Observer
void MotionEvent::visit(StateSwitch *s){ s -> handleInput(*this); }; //State

void COMEvent::visit(State *s) { s -> handleInput(*this); }; //State
void COMEvent::visit(Subject *sj) { sj -> notify(*this); }; //Subject
void COMEvent::visit(Observer *o) { o -> onNotify(*this); }; //Observer
void COMEvent::visit(StateSwitch *s){ s -> handleInput(*this); }; //State
