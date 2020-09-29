#include <iostream>
#include <fstream>
#include <boost/property_tree/json_parser.hpp>

#include "Game.h"

Game::Game() {
  auto loadJson = [&]() mutable {
    boost::property_tree::read_json(questionsPath, pt);
  };
}

/*----------MENU-DISPLAY-----------*/

void Game::showMenu() const {
  std::cout << " _________________ \n"
            << "|                 |\n"
            << "| *FATTY HANGMAN* |\n"
            << "|_________________|\n\n"

            << "1.Start\n"
            << "2.Add a question\n"
            << "3.Display a question\n"
            << "4.Display all questions\n"
            << "5.Delete a question\n"
            << "6.Delete all questions\n"
            << "7.Quit\n\n";
}

/*---------MENU-DISPLAY-END-------*/

/*---------MENU-MOVEMENT----------*/
unsigned int Game::input() const {
  unsigned int input;

  std::cout << "Select: ";
  std::cin >> input;
  
  return input;
} 
void Game::back() const {
  std::cout << "\n0.Back\n";
  while(input()){}
} 
/*--------MENU-MOVEMENT-END-------*/

/*------QUESTIONS-MANAGEMENT------*/

void Game::addQuest() {
  boost::property_tree::read_json(questionsPath, pt);

  pt.push_back(boost::property_tree::ptree::value_type("pi", boost::property_tree::ptree("3.14159")));

  boost::property_tree::write_json(questionsPath, pt);
}

void Game::displayQuest() {

}

void Game::displayAllQuest() { 
  try {
    boost::property_tree::read_json(questionsPath, pt);
    
    for(auto& arr_element: pt) {
      std::cout << arr_element.first << "\n";

      for(auto& property: arr_element.second) {
          std::cout << property.first
                    << " = "
                    << property.second.get_value < std::string > () << "\n";
      }
      std::cout << "=================================\n";
    }
  } catch(const std::exception& e) {
    std::cout << "Make sure the location of the questions file is there:\n"
              << questionsPath
              << "\n";
  }
  back();
}

void Game::delQuest() {
  std::cout << "Which question should we delete?\n"
            << "Question number: ";

  std::string questNum;
  std::cin >> questNum;

  std::string questKey = "Question" + questNum;

  try {
    boost::property_tree::read_json(questionsPath, pt);

    pt.erase(questKey);

    boost::property_tree::write_json(questionsPath, pt);

    std::cout << "Successfully removed!\n";

    back();

  } catch(const std::exception& e) {
    std::cout << "Make sure the location of the questions file is there:\n"
              << questionsPath
              << "\n";
  }
}

void Game::delAllQuest() {
  boost::property_tree::read_json(questionsPath, pt);

  pt.clear();

  boost::property_tree::write_json(questionsPath, pt);
}

/*----QUESTIONS-MANAGEMENT-END----*/
