#include <iostream>
#include <stdlib.h>
#include <boost/property_tree/json_parser.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid_generators.hpp>

#include "Game.h"

boost::property_tree::ptree Game::pt;
const std::string Game::questionsPath = "../QuestionsDir/Questions.json";

Game::Game() {
  try {
    boost::property_tree::read_json(questionsPath, pt);
  } catch(const std::exception& e) {
    std::cout << "Game cannot starting without a questions file!\n"
              << "Make sure the location of the questions file is there:\n"
              << "../QuestionsDir/Questions.json"
              << "\n";
    exit(EXIT_FAILURE);
  }
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
  std::string input;

  std::cout << "Select: ";
  std::getline(std::cin, input);
  
  try
  {
    auto in = std::stoi(input);
    return in;
  }
  catch(const std::exception& e)
  {
    return -1;
  }
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
    std::getline(std::cin, category);

    std::cout << "Answer: ";
    std::getline(std::cin, answer);

    boost::property_tree::ptree newQuest;
    newQuest.put("Category", category);
    newQuest.put("Answer", answer);

    auto gen = boost::uuids::random_generator();
    boost::uuids::uuid id = gen();
    
    auto id_str = boost::uuids::to_string(id);
    
    pt.add_child(id_str, newQuest);

    boost::property_tree::write_json(questionsPath, pt);
  
    std::cout << "Successfully added!\n";

  } catch(const std::exception& e) {
    std::cout << "Make sure the location of the questions file is there:\n"
              << questionsPath
              << "\n";
  }
  back();
}

void Game::displayAllQuest() { 
  try {
    boost::property_tree::read_json(questionsPath, pt);
    
    if(pt.empty())
      std::cout << "The question file is empty!\n";

    for(auto& arr_element: pt) {
      std::cout << "Id = " << arr_element.first << "\n";

      for(auto& property: arr_element.second) {
          std::cout << property.first
                    << " = "
                    << property.second.get_value < std::string > () << "\n";
      }
      std::cout << "============================================\n";
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
    std::getline(std::cin, questId);
    
    auto find = pt.find(questId);

    if(find == pt.not_found()) {
      std::cout << "\nQuestion id not found!\n";
      back();
      return false;
    }

    pt.erase(questId);
    
    boost::property_tree::write_json(questionsPath, pt);
    
    std::cout << "Successfully removed!\n";
  
  } catch(const std::exception& e) {
    std::cout << "Make sure the location of the questions file is there:\n"
              << questionsPath
              << "\n";
  }
  back();
  return true;
}

bool Game::delAllQuest() {
  try {
    boost::property_tree::read_json(questionsPath, pt);    

    std::string youSure;
    do {
      std::cout << "Are you sure to delete all questions? Y/N\n"
                << "Select: ";
      std::getline(std::cin, youSure);
    } while((youSure[0] != 'Y'
          && youSure[0] != 'y'
          && youSure[0] != 'N'
          && youSure[0] != 'n')
          || youSure.length() != 1);

    if(youSure[0] == 'N' || youSure[0] == 'n')
      return false;

    pt.clear();

    boost::property_tree::write_json(questionsPath, pt);
 
    std::cout << "Successfully removed!\n";

  } catch(const std::exception& e) {
    std::cout << "Make sure the location of the questions file is there:\n"
              << questionsPath
              << "\n";
  }
  back();
  return true;
}

/*----QUESTIONS-MANAGEMENT-END----*/