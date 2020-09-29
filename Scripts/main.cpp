#include <iostream>
#include <memory>

#include "Game.h"
#include "Hangman.h"

int main() {
  std::unique_ptr<Game> hangmanGame(new Hangman());

  do {
    system("clear");
    hangmanGame->showMenu();

    switch(hangmanGame->input()) {
      case 1:
        system("clear");
        hangmanGame->startGame();
        break;
      case 2:
        system("clear");
        hangmanGame->addQuest();
        break;
      case 3:
        system("clear");
        hangmanGame->displayAllQuest();
        break;
      case 4:
        system("clear");
        hangmanGame->delQuest();
        break;
      case 5:
        system("clear");
        hangmanGame->delAllQuest();
        break;
      case 6:
        return 0;
        break;
      default:
        system("clear");
    }
  } while(true);
}