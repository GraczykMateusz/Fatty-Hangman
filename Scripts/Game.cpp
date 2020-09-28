#include <iostream>
#include <fstream>
#include <boost/property_tree/json_parser.hpp>

#include "Game.h"

/*----------MENU-DISPLAY-----------*/

void Game::showMenu() const {
  std::cout << " _________________ \n"
            << "|                 |\n"
            << "| *FATTY HANGMAN* |\n"
            << "|_________________|\n\n"

            << "1.Start\n"
            << "2.Add question\n"
            << "3.Display all questions\n"
            << "4.Delete question\n"
            << "5.Delete all questions\n"
            << "6.Quit\n\n";
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

}

void Game::displayAllQuest() { 
  try {
    std::ifstream questionsFile(questionsPath);
    boost::property_tree::read_json(questionsFile, pt);
    
    for(auto& arr_element: pt) {
      std::cout << arr_element.first << "\n";

      for(auto& property: arr_element.second) {
          std::cout << property.first
                    << " = "
                    << property.second.get_value < std::string > () << "\n";
      }
      std::cout << "=========================================================\n";
    }
  } catch(const std::exception& e) {
    std::cout << "Make sure the location of the questions file is there:\n"
              << questionsPath
              << "\n" << e.what();
  }
  back();
}

void Game::delQuest() {
  std::cout << "Which question should we delete?\n"
            << "Question number: ";

  std::string questNum;
  std::cin >> questNum;
}

void Game::delAllQuest() {
  std::ofstream questionsFile(questionsPath);
  boost::property_tree::write_json(questionsFile, pt);

  pt.erase("Question 1");

}

/*----QUESTIONS-MANAGEMENT-END----*/
