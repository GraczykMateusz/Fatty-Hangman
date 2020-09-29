#include <iostream>
#include <boost/property_tree/json_parser.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid_generators.hpp>

#include "Game.h"

Game::Game() {
  boost::property_tree::read_json(questionsPath, pt);
}

/*----------MENU-DISPLAY-----------*/

void Game::showMenu() const {
  std::cout << " _________________ \n"
            << "|                 |\n"
            << "| *FATTY HANGMAN* |\n"
            << "|_________________|\n\n"

            << "1.Start\n"
            << "2.Add a question\n"
            << "3.Display all questions\n"
            << "4.Delete a question\n"
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
  try {
    boost::property_tree::read_json(questionsPath, pt);

    std::string category, answer;

    std::cout << "Category: ";
    std::cin >> category;

    std::cout << "Answer: ";
    std::cin >> answer;

    boost::property_tree::ptree newQuest;
    newQuest.put("Category", category);
    newQuest.put("Answer", answer);

    auto gen = boost::uuids::random_generator();
    boost::uuids::uuid id = gen();
    
    auto id_str = boost::uuids::to_string(id);
    
    pt.add_child(id_str, newQuest);

    boost::property_tree::write_json(questionsPath, pt);
  
    back();

  } catch(const std::exception& e) {
    std::cout << "Make sure the location of the questions file is there:\n"
              << questionsPath
              << "\n";
  }
}

void Game::displayAllQuest() { 
  try {
    boost::property_tree::read_json(questionsPath, pt);
    
    if(pt.empty())
      std::cout << "The question file is empty!\n";

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

bool Game::delQuest() {
  try {
    boost::property_tree::read_json(questionsPath, pt);
    
    std::cout << "Which question should we delete?\n"
              << "Question id: ";

    std::string questId;
    std::cin >> questId;
    
    auto find = pt.find(questId);

    if(find == pt.not_found()) {
      std::cout << "\nQuestion id not found!\n";
      back();
      return false;
    }

    pt.erase(questId);
    
    boost::property_tree::write_json(questionsPath, pt);
    
    std::cout << "Successfully removed!\n";
    
    back();
    return true;
  
  } catch(const std::exception& e) {
    std::cout << "Make sure the location of the questions file is there:\n"
              << questionsPath
              << "\n";
    return false;
  }
}

bool Game::delAllQuest() {
  try {
    boost::property_tree::read_json(questionsPath, pt);    

    char youSure;
    do {
      std::cout << "Are you sure to delete all questions? Y/N\n"
                << "Select: ";
      std::cin >> youSure;
    } while(youSure != 'Y' && youSure != 'y' && youSure != 'N' && youSure != 'n');

    if(youSure == 'N' || youSure == 'n')
      return false;

    pt.clear();

    boost::property_tree::write_json(questionsPath, pt);
 
    std::cout << "Successfully removed!\n";

    back();
    return true;

  } catch(const std::exception& e) {
    std::cout << "Make sure the location of the questions file is there:\n"
              << questionsPath
              << "\n";
    return false;
  }
}

/*----QUESTIONS-MANAGEMENT-END----*/
