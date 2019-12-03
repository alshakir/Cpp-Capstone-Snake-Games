
#include "car.h"
#include <thread>
#include <iostream>
#include <string>
#include <mutex>



    void Car::move(){
        // horizontal
        // vertical
        while(_active){
            std::this_thread::sleep_for(std::chrono::milliseconds(_delay));
            if (_axis == "horizontal"){
                int x = get_xpos();
                set_xpos( newPos(x));

                //std::cout << "Car Thread #: " <<std::this_thread::get_id()<<" ---    Pos ="<< _xpos<<std::endl;
            }else{
                int y = get_ypos();
                set_ypos(newPos(y));

                //std::cout << "Car Thread #: " <<std::this_thread::get_id()<<" ---   Pos = " <<_ypos<<std::endl;
            }
            // reached to  the correct place
            if(get_xpos()< 15 && get_ypos() <15)
                {   
                    _active = false;
                    _succeeded = true;
                }
        }
            // stopped in the correct place
              if(get_xpos()< 15 && get_ypos() <15)
                {
                    _succeeded = true;
                }
    };

    int Car::newPos(int pos){
        if (pos + _speed > _limit){

            pos = _limit-5;// to make its edge visible

        }else if(pos + _speed < 0){
            
            pos = 0;

        }else{

            pos += _speed;
        }
        return pos;

    };


    void Car::setAxis(std::string axis){

        // horizontal or vertical
        _axis = axis;
    }

    void Car::setDirection(int d){
        //+1 or -1
        _speed = d * abs(_speed);
    }

    void Car::adjustDelay(int d){
        _delay += d;
    };

    int Car::get_xpos(){
         std::lock_guard lck(mtx);
         return _xpos;
    }

    int Car::get_ypos(){
         std::lock_guard lck(mtx);
         return _ypos;
    }


    void Car::set_xpos(int x){
        std::lock_guard lck(mtx);
        _xpos = x;
    }


    void Car::set_ypos(int y){
        std::lock_guard lck(mtx);
        _ypos = y;
    }

 bool Car::get_success(){
         std::lock_guard lck(mtx);
         return _succeeded;
    }

bool Car::isActive(){
    return _active;
}
  
  void Car::set_active(bool a){
      _active = a;
  };