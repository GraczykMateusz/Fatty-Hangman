#include <iostream>
#include <random>
#include <vector>
#include <boost/algorithm/string.hpp>
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
      throw "Cannot start! Empty questions file!\n";
  } catch(const char* err) {
    std::cout << err;
    back();
    return false;
  }
  
  int questIterNum;
  auto randQuest = [&questIterNum]() {
    std::random_device rd;
    std::mt19937 gen(rd());

    int i = pt.size();
    std::uniform_int_distribution<> disIterNum(0, --i);

    questIterNum = disIterNum(gen);
  };
  randQuest();
  
  boost::property_tree::ptree::iterator it = pt.begin();

  //set correct category
  for(int i = 0; i < questIterNum; ++i) 
    ++it;

  id = it->first;

  auto it2 = it->second.begin();
  
  category = it2->second.get_value < std::string > ();

  auto it3 = it2;

  ++it3;

  answer = it3->second.get_value < std::string > ();
  
  std::vector<char> answerVec;

  for(int i = 0; i < answer.length(); ++i) {
    if(answer[i] == ' ') {
      answerVec.push_back(answer[i]);
    } else {
      answerVec.push_back('+');
    }
  }  
  std::cout << "Characters used: "
            << "\n";

  std::string inputAnswer;
  int mistake = -1;
  bool gameOver = false;
  do {
      system("clear");
      ++mistake;
      //id
      std::cout << "Id = "
            << id
            << "\n";
      //category
      std::cout << it2->first
            << " = "
            << category 
            << "\n\n";
      //answer
      std::cout << "Answer:\n";
      //+++ +++ +++
      for(auto& character : answerVec)
        std::cout << character;

      std::cout << "\n";
      //hangman disp
      switch(mistake) {
        case 0:
          std::cout << " _________________ \n"
                    << "|                 |\n"
                    << "|                 |\n"
                    << "|      LET'S      |\n"
                    << "|      START      |\n"
                    << "|       ...       |\n"
                    << "|                 |\n"
                    << "|_________________|\n\n";
          break;
        case 1:
          std::cout << " _________________ \n"
                    << "|                 |\n"
                    << "|                 |\n"
                    << "|                 |\n"
                    << "|                 |\n"
                    << "|                 |\n"
                    << "|                 |\n"
                    << "|___/___\\_________|\n\n";
          break;
        case 2:
          std::cout << " _________________ \n"
                    << "|                 |\n"
                    << "|                 |\n"
                    << "|                 |\n"
                    << "|                 |\n"
                    << "|                 |\n"
                    << "|    / \\          |\n"
                    << "|___/___\\_________|\n\n";
          break;
        case 3:
          std::cout << " _________________ \n"
                    << "|                 |\n"
                    << "|                 |\n"
                    << "|                 |\n"
                    << "|                 |\n"
                    << "|     |           |\n"
                    << "|    / \\          |\n"
                    << "|___/___\\_________|\n\n";
          break;
        case 4:
          std::cout << " _________________ \n"
                    << "|                 |\n"
                    << "|                 |\n"
                    << "|                 |\n"
                    << "|     |           |\n"
                    << "|     |           |\n"
                    << "|    / \\          |\n"
                    << "|___/___\\_________|\n\n";
          break;
        case 5:
          std::cout << " _________________ \n"
                    << "|                 |\n"
                    << "|                 |\n"
                    << "|     |           |\n"
                    << "|     |           |\n"
                    << "|     |           |\n"
                    << "|    / \\          |\n"
                    << "|___/___\\_________|\n\n";
          break;
        case 6:
          std::cout << " _________________ \n"
                    << "|                 |\n"
                    << "|      _____      |\n"
                    << "|     |           |\n"
                    << "|     |           |\n"
                    << "|     |           |\n"
                    << "|    / \\          |\n"
                    << "|___/___\\_________|\n\n";
          break;
        case 7:
          std::cout << " _________________ \n"
                    << "|                 |\n"
                    << "|      _____      |\n"
                    << "|     |     |     |\n"
                    << "|     |           |\n"
                    << "|     |           |\n"
                    << "|    / \\          |\n"
                    << "|___/___\\_________|\n\n";
          break;
        case 8:
          std::cout << " _________________ \n"
                    << "|                 |\n"
                    << "|      _____      |\n"
                    << "|     |     |     |\n"
                    << "|     |     O     |\n"
                    << "|     |           |\n"
                    << "|    / \\          |\n"
                    << "|___/___\\_________|\n\n";
          break;
        case 9:
          std::cout << " _________________ \n"
                    << "|                 |\n"
                    << "|      _____      |\n"
                    << "|     |     |     |\n"
                    << "|     |     O     |\n"
                    << "|     |    ( )    |\n"
                    << "|    / \\          |\n"
                    << "|___/___\\_________|\n\n";
          break;
        case 10:
          std::cout << " _________________ \n"
                    << "|                 |\n"
                    << "|      _____      |\n"
                    << "|     |     |     |\n"
                    << "|     |    \\O/    |\n"
                    << "|     |    ( )    |\n"
                    << "|    / \\          |\n"
                    << "|___/___\\_________|\n\n";
          break;
        case 11:
          std::cout << " _________________ \n"
                    << "|     *LOSER*     |\n"
                    << "|      _____      |\n"
                    << "|     |     |     |\n"
                    << "|     |    \\O/    |\n"
                    << "|     |    ( )    |\n"
                    << "|    / \\   /'\\    |\n"
                    << "|___/___\\_________|\n\n";
          gameOver = true;
          break;
      }
      //char used

      if(gameOver != true) {
        std::cout << "\nWrite letter or full answer: ";
        std::getline(std::cin, inputAnswer);
        std::transform(inputAnswer.begin(), inputAnswer.end(), inputAnswer.begin(), ::toupper);
      } else {
        std::cout << "\nYOU LOSE!";
        back();
        return false;
      }
  } while(inputAnswer != answer && inputAnswer.length() != 1 && gameOver != true);
  
  std::cout << "\nCONGRATULATIONS YOU WON!";
  back();
  return true;
}
