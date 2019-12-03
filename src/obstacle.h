#ifndef OBSTACLE_H
#define OBSTACLE_H


#include <string>
#include <iostream>
#include <vector>
#include "car.h"

class Obstacle {


public:
    Obstacle(int x, int y,int limit, int speed, std::string axis, std::vector<Car*> cars):_xpos(x), _ypos(y), _limit(limit), _speed(speed), _axis(axis), _cars(cars){
        std::cout <<"creating obstacle";
    };
    //copy cstr
    Obstacle(const Obstacle& src);

    //copy assignment operator
    Obstacle& operator=(const Obstacle& src);


    //move cstr
    Obstacle(Obstacle&& src);
    
    //move assignment operator
    Obstacle& operator=(Obstacle&& src);


    void move();
    int newPos(int pos);


    void deactivate(){_active = false;}
    void setDirection(int d);
    void setAxis(std::string axis);
    void adjustDelay(int d);
    int get_xpos();
    void set_xpos(int x);
    int get_ypos();
    void set_ypos(int y);

private:
    int _xpos, _ypos;
    int _delay = 25;
    bool _active = true;
    int _speed;
    int  _limit;
    std::string _axis;
    std::vector<Car*> _cars;
   

};
#endif