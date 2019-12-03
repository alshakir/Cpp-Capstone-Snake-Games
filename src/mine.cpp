#include <iostream>
#include <string>
#include "mine.h"
#include <thread>

//#include "randomizer.h"



void Mine::move(int speed , int axis, int limit){

// 1 = horizontal
// 2 = vertical
while(_active){
        std::this_thread::sleep_for(std::chrono::milliseconds(30));
        if (axis == 1){

            _xpos = newPos(_xpos,speed, limit);

            //std::cout << "Thread #: " <<std::this_thread::get_id()<<" ---    Pos ="<< _xpos<<std::endl;
        }else{
            _ypos = newPos(_ypos,speed, limit);

            //std::cout << "Thread #: " <<std::this_thread::get_id()<<" ---   Pos = " <<_ypos<<std::endl;
        }
    }
}


int Mine::newPos(int pos,int speed , int limit){
    //std::cout<<Randomizer::genRand(1,600)<<std::endl;
    if (pos + speed > limit){

        pos = 0;

    }else if(pos + speed < 0){
        
        pos = limit;

    }else{

        pos += speed;
    }
    return pos;
}

void Mine::set_xpos(int x){
    _xpos = x;
}
void Mine::set_ypos(int y){
    _ypos = y;
}