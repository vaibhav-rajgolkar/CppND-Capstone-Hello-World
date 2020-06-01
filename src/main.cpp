#include <iostream>
#include "constants.h"
#include "audio.h"
#include "renderer.h"
#include "controller.h"
#include "game.h"


int main() {

   Renderer renderer;
   Audio audio;
   Controller controller(&audio);
   Game game(&audio);
   game.Run(controller, renderer, Constant::kMsPerFrame);
   std::cout << "Game has terminated successfully!\n";
   std::cout << "Score: " << game.GetScore() << "\n";
   std::cout << "High Score: " << game.GetHighScore() << "\n";

    return 0;
}