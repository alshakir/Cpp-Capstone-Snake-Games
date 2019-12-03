#include "game.h"
#include <iostream>
#include "SDL.h"
#include "mine.h"
#include <thread>
#include "car.h"
#include "mycontroller.h"
#include "randomizer.h"
#include "obstacle.h"
#include <string>


Game::Game(std::size_t grid_width, std::size_t grid_height)
    : engine(dev()),
      random_w(0, static_cast<int>(grid_width)),
      random_h(0, static_cast<int>(grid_height)) {
  PlaceFood();
}

void Game::Run( Renderer &renderer,
               std::size_t target_frame_duration, int level) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;


      Car car1 {635, 630, 640,-1, "horizontal"};
      Car car2 {630, 635, 640, -1, "vertical"};

      std::vector<std::thread> cars ;
      cars.emplace_back(std::thread(&Car::move, &car1));
      cars.emplace_back(std::thread(&Car::move, &car2));

      std::vector<Car*> carObjects {&car1, &car2};




std::vector<Obstacle> obstacles;

for( int i = 0 ; i < level * 3; i++){
  int x = Randomizer::genRand(1,600);
  int y = Randomizer::genRand(1,600);
  int d = Randomizer::genRand(1,2);
  std::string direction = "vertical";

  if(d==1){
    direction = "horizontal";
  }
  Obstacle obstacle {x,y, 600,1,direction,carObjects};
  obstacles.emplace_back(std::move(obstacle));

}
  // Mine mine1{50,70};
  // Mine mine2{150,70};  
  // Mine mine3{500,170};

  std::vector<Obstacle*> obstaclesPtr;
//for( Obstacle& o : obstacles){
   for( int i = 0 ; i < level * 3; i++){
    obstaclesPtr.emplace_back(&obstacles[i]);
}
std::vector<std::thread> obstacleThreads;
//for( Obstacle& o : obstacles){
   for( int i = 0 ; i < level * 3; i++){
    obstacleThreads.emplace_back(std::thread(&Obstacle::move,obstaclesPtr[i]));
}




    
  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    //controller.HandleInput(running, snake);
    Mycontroller::HandleInput(running,car1,car2);

    Update();

    //update
    if(car1.isActive()==false && car2.isActive() ==false){
       if(car1.get_success()==true && car2.get_success() ==true){
          running = false;
          for(auto& o : obstacles){
            o.deactivate();
          }
      }else{

      car1.set_xpos(600);
      car1.set_ypos(600);
      car2.set_xpos(600);
      car2.set_ypos(600);
      car1.set_active(true);
      car2.set_active(true);

        for(auto& c : cars){
           c.join();
        }
       
       cars.pop_back();
       cars.pop_back();
       
      cars.emplace_back(std::thread(&Car::move, &car1));
      cars.emplace_back(std::thread(&Car::move, &car2));
      }

    }

    
    renderer.Render( obstaclesPtr, carObjects);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }

// for( auto& ob : obstaclesPtr){
//   std::cout << ob;
//   delete ob;
  
// }
 
//  for (auto& c : carObjects){
//    delete c;
//  } 

// make sure that all threads will stop and join
    for(auto& o : obstacles){
      o.deactivate();
    }
  
  car1.deactivate();
  car2.deactivate();

for( auto& t : cars){
  t.join();
}

for(auto& t : obstacleThreads){
  t.join();
}
}

void Game::PlaceFood() {
  // int x, y;
  // while (true) {
  //   x = random_w(engine);
  //   y = random_h(engine);

  //   // Check that the location is not occupied by a snake item before placing
  //   // food.
  //   if (!snake.SnakeCell(x, y)) {
  //     food.x = x;
  //     food.y = y;
  //     return;
  //   }
  // }
}

void Game::Update() {
  // if (!snake.alive) return;

  // snake.Update();

  // int new_x = static_cast<int>(snake.head_x);
  // int new_y = static_cast<int>(snake.head_y);

  // // Check if there's food over here
  // if (food.x == new_x && food.y == new_y) {
  //   score++;
  //   PlaceFood();
  //   // Grow snake and increase speed.
  //   snake.GrowBody();
  //   snake.speed += 0.02;
  // }

  //mine.move(1,2,600);
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return 1; }