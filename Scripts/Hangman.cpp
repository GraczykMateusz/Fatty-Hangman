#include <iostream>
#include <boost/property_tree/json_parser.hpp>

#include "Hangman.h"
#include "Game.h"

boost::property_tree::ptree Hangman::pt;

Hangman::Hangman() {
  this->pt = Game::getPt();
  boost::property_tree::read_json(Game::getQuestionsPath(), pt);
}

void Hangman::startGame() const {
  std::cout << "GameStarting... [test]";
 
}
