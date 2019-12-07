#include <iostream>
#include <sstream>

#include "game.h"
#include "renderer.h"
#include "mycontroller.h"
#include <fstream>
#include <condition_variable>
#include <mutex>
#include <exception>

int level = 1;
int score = 0;

std::mutex mtx;
std::condition_variable con_var;


void logHighestScore(int& score){
  int r{0};
  std::string  input;
  std::fstream oldResult;
 std::fstream result;
 while(!Mycontroller::quit){

  std::unique_lock<std::mutex> lck(mtx);
  con_var.wait(lck );

  oldResult.open("result.txt", std::ios::in);
  if(!oldResult){
    std::cerr << "file not available..failed to open a file\n" ;
    oldResult.clear();
  } else{
    try{  
      std::getline(oldResult,input);
      r = std::stoi(input);
      std::cout<<"Done reading from file\n";

      Mycontroller::highestScore = r;
    }catch(std::exception& e){
      std::cout << e.what();
    }

   oldResult.close();
  }

 
bool newScore = r < score;
std::cout << "new score is " << newScore <<std::endl;
std::cout << "r = " << r << std::endl;

std::cout << "score = " << score << std::endl;

  if(newScore){
    result.open("result.txt", std::ios::out);
    if(!result){
      std::cerr << "failed to create ..file not available\n" ;
    }
    else{
      result << score;
      std::cout<<"wrote into file\n";
    }
    result.close();
  }


  }
}

int main() {
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};

  std::thread t(logHighestScore, std::ref(score));
  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  //Controller controller;
  
  Game game(kGridWidth, kGridHeight);
  while (true){
   

    score = game.GetScore();
    std::cout <<score <<"---------\n";
    con_var.notify_all();
    std::cout << "trying to start loop in the game levels!..level= "<<level<<std::endl;;
    game.Run( renderer, kMsPerFrame, level);
     level++;
    std::cout << "finished level = " << level << std::endl;
    
    if(Mycontroller::quit)break;
  }
  
  //std::cout << "Score: " << game.GetScore() << "\n";
  //std::cout << "Size: " << game.GetSize() << "\n";
  con_var.notify_all();
  t.join();


  std::cout << "Game has terminated successfully!\n";
  return 0;
}