#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"


int level = 1;
int score = 0;


int main() {
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};


  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  //Controller controller;
  Game game(kGridWidth, kGridHeight);
  for (int level = 1; level <= 4; level++){
    std::cout << "trying to start loop in the game levels!..level= "<<level<<std::endl;;
    game.Run( renderer, kMsPerFrame, level);
    std::cout << "finished level = " << level;
  }
  std::cout << "Game has terminated successfully!\n";
  //std::cout << "Score: " << game.GetScore() << "\n";
  //std::cout << "Size: " << game.GetSize() << "\n";
  return 0;
}