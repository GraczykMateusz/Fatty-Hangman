#ifndef HANGMAN_H
#define HANGMAN_H

#include <vector>

#include "Game.h"

class Hangman : public Game {
  private:
  static boost::property_tree::ptree pt;
  
  std::string id;
  std::string category;
  std::string answer;
  
  std::vector<char> answerVec;
  
  void randQuest();

  public:
    Hangman();
    bool startGame() override;
};
#endif /*HANGMAN_H*/
