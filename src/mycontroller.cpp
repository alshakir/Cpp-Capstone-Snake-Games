#include "mycontroller.h"
#include <iostream>
#include "SDL.h"
#include "car.h"

// void Controller::ChangeDirection(Snake &snake, Snake::Direction input,
//                                  Snake::Direction opposite) const {
//   if (snake.direction != opposite || snake.size == 1) snake.direction = input;
//   return;
// }
bool Mycontroller::switchCars = true;

void Mycontroller::HandleInput(bool &running, Car &car1, Car &car2)  {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
        running = false;
      } else if (e.type == SDL_KEYDOWN) {
        std::cout << "Mycontroller::switchCars ="<< Mycontroller::switchCars << std::endl;
          if(Mycontroller::switchCars){
            Mycontroller::control(car1, e);
          }else{
            Mycontroller::control(car2, e);
          }
  }
}
}

void Mycontroller::control(Car &car,  SDL_Event& e){


      switch (e.key.keysym.sym) {
        case SDLK_UP:
          car.setAxis("vertical");
          car.setDirection(-1);
          break;

        case SDLK_DOWN:
          car.setAxis("vertical");
          car.setDirection(1);   
          break;

        case SDLK_LEFT:
          car.setAxis("horizontal");    
          car.setDirection(-1);
          break;

        case SDLK_RIGHT:
          car.setAxis("horizontal");
          car.setDirection(1);
        
        break;        
        
        case SDLK_RCTRL:
          Mycontroller::switchCars = !Mycontroller::switchCars;
        break;
                
        case SDLK_LCTRL:
          Mycontroller::switchCars = !Mycontroller::switchCars;
        break;
      }
    }
  
