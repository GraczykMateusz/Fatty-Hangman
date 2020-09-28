#ifndef GAME_H
#define GAME_H

#include <string>

#include <boost/property_tree/ptree.hpp>

class Game {
  private:
    const std::string questionsPath = "../QuestionsDir/Questions.json";
    boost::property_tree::ptree pt;

  public:
    Game() = default;
    virtual ~Game() = default;
    
    virtual void showMenu() const;

    virtual void startGame() const = 0;
    virtual void addQuest();
    virtual void displayAllQuest();
    virtual void delQuest();
    virtual void delAllQuest();

    virtual unsigned int input() const;
    virtual void back() const;
};
#endif /*GAME_H*/
