#ifndef HANGMAN_H
#define HANGMAN_H

#include "Game.h"

class Hangman : public Game {
  static boost::property_tree::ptree pt;
  public:
    Hangman();
    bool startGame() override;
};
#endif /*HANGMAN_H*/
