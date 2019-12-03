#include "game.h"
#include <iostream>
#include "SDL.h"
#include "mine.h"
#include <thread>
#include "car.h"
#include "mycontroller.h"


Game::Game(std::size_t grid_width, std::size_t grid_height)
    : snake(grid_width, grid_height),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width)),
      random_h(0, static_cast<int>(grid_height)) ,
      mine(grid_width,grid_height){
  PlaceFood();
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;


  Mine mine1{50,70};
  Mine mine2{150,70};  
  Mine mine3{500,170};

  std::vector<std::thread> mines ;

  mines.emplace_back(std::thread(&Mine::move, &mine1, 1, 1, 600));
  mines.emplace_back(std::thread(&Mine::move, &mine2, 1, 2, 600));
  mines.emplace_back(std::thread(&Mine::move, &mine3, 1, 1, 600));

  std::vector<Mine*> mineObjects {&mine1, &mine2, &mine3};
  

  Car car1 {10, 300, 640,1, "horizontal"};
  Car car2 {635, 300, 640, -1, "horizontal"};

  std::vector<std::thread> cars ;
  cars.emplace_back(std::thread(&Car::move, &car1));
  cars.emplace_back(std::thread(&Car::move, &car2));


  std::vector<Car*> carObjects {&car1, &car2};

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    //controller.HandleInput(running, snake);
    Mycontroller::HandleInput(running,car1,car2);

    Update();
    renderer.Render(snake, food, mine, mineObjects, carObjects);

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

  for( auto &t : mines){
    //t.join();
  }
}

void Game::PlaceFood() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);

    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snake.SnakeCell(x, y)) {
      food.x = x;
      food.y = y;
      return;
    }
  }
}

void Game::Update() {
  if (!snake.alive) return;

  snake.Update();

  int new_x = static_cast<int>(snake.head_x);
  int new_y = static_cast<int>(snake.head_y);

  // Check if there's food over here
  if (food.x == new_x && food.y == new_y) {
    score++;
    PlaceFood();
    // Grow snake and increase speed.
    snake.GrowBody();
    snake.speed += 0.02;
  }

  //mine.move(1,2,600);
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake.size; }