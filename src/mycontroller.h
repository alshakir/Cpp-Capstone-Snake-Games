#ifndef MYCONTROLLER_H
#define MYCONTROLLER_H

#include "car.h"
#include "SDL.h"

class Mycontroller {
public:

    static void HandleInput(bool &running, Car &car1, Car &car2)  ;
    static void control(Car& car, SDL_Event& e);
    static bool switchCars ;
};



//bool Mycontroller::switchCars;

#endif