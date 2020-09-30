#include <iostream>
#include <random>
#include <boost/property_tree/json_parser.hpp>
#include <boost/uuid/uuid_generators.hpp>

#include "Hangman.h"
#include "Game.h"

boost::property_tree::ptree Hangman::pt;

Hangman::Hangman() {
  try {
    this->pt = Game::getPt();
    boost::property_tree::read_json(Game::getQuestionsPath(), pt);
  } catch(const std::exception& e) {
    std::cout << "Make sure the location of the questions file is there:\n"
              << Game::getQuestionsPath
              << "\n";
  }
}

bool Hangman::startGame() {
  try {
    boost::property_tree::read_json(Game::getQuestionsPath(), pt);
  } catch(const std::exception& e) {
    std::cout << "Make sure the location of the questions file is there:\n"
              << Game::getQuestionsPath
              << "\n";
    back();
    return false;
  }
  try {
    if(pt.empty())
      throw "Cannot start! Empty questions file!";
  } catch(const char* err) {
    std::cout << err;
    back();
    return false;
  }

  std::random_device rd;
	std::mt19937 gen(rd());

  int i = pt.size();
  std::uniform_int_distribution<> disIterNum(0, --i);

  int questIterNum = disIterNum(gen);

  boost::property_tree::ptree::iterator it = pt.begin();

  for(int i = 0; i < questIterNum; ++i) 
    ++it;

  std::cout << "Id = " << it->first << "\n";
  for(auto& i : it->second)
    std::cout << i.first
              << " = "
              << i.second.get_value < std::string > () << "\n";

  back();
  return true;
}
