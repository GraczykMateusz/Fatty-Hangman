#ifndef HANGMAN_H
#define HANGMAN_H

#include "Game.h"

class Hangman : public Game {
  private:
  static boost::property_tree::ptree pt;
  
  std::string id;
  std::string question;
  std::string answer;
  
  public:
    Hangman();
    bool startGame() override;
};
#endif /*HANGMAN_H*/
