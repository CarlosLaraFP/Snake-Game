#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"

int main(int argc, char* argv[]) 
{
  constexpr std::size_t kFramesPerSecond {60};
  constexpr std::size_t kMsPerFrame {1000 / kFramesPerSecond};
  // pixels
  constexpr std::size_t kScreenWidth {640};
  constexpr std::size_t kScreenHeight {640};
  // game surface/motion area
  constexpr std::size_t kGridWidth {32};
  constexpr std::size_t kGridHeight {32};

  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;
  Game game(kGridWidth, kGridHeight);

  game.Run(controller, renderer, kMsPerFrame);

  std::cout << "Game has terminated successfully!" << std::endl;
  std::cout << "Score: " << game.GetScore() << std::endl;
  std::cout << "Highscore: " << game.GetHighScore() << std::endl;
  std::cout << "Snake Size: " << game.GetSnakeSize() << std::endl;

  return 0;
}