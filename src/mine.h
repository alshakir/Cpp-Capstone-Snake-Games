#ifndef MINE_H
#define MINE_H

#include <string>

class Mine {


public:
    Mine(){};
    Mine(int x, int y): _xpos(x), _ypos(y){};
    void move(int speed, int axis, int limit);
    int newPos(int pos,int speed , int limit);
    int get_xpos(){return _xpos;}
    int get_ypos(){return _ypos;}
    void deactivate(){_active = false;}
    void set_xpos(int x);
    void set_ypos(int y);
private:
    int _xpos;
    int _ypos;
    bool _active = true;



};


#endif