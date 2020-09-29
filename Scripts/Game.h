#ifndef GAME_H
#define GAME_H

#include <string>

#include <boost/property_tree/ptree.hpp>

class Game {
  private:
    const std::string questionsPath = "../QuestionsDir/Questions.json";
    boost::property_tree::ptree pt;

  public:
    Game();
    virtual ~Game() = default;
    
    virtual void showMenu() const;

    virtual void startGame() const = 0;
    virtual void addQuest();
    virtual void displayAllQuest();
    virtual bool delQuest();
    virtual bool delAllQuest();

    virtual unsigned int input() const;
    virtual void back() const;
};
#endif /*GAME_H*/
