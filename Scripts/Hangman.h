#ifndef HANGMAN_H
#define HANGMAN_H

#include "Game.h"

class Hangman : public Game {
  public:
    void startGame() const override;
};

#endif /*HANGMAN_H*/
