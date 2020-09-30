#ifndef GAME_H
#define GAME_H

#include <string>

#include <boost/property_tree/ptree.hpp>

class Game {
  private:
    static const std::string questionsPath;
    static boost::property_tree::ptree pt;

  public:
    Game();
    virtual ~Game() = default;
    
    virtual void showMenu() const;

    virtual bool startGame() = 0;
    virtual void addQuest();
    virtual void displayAllQuest();
    virtual bool delQuest();
    virtual bool delAllQuest();

    static boost::property_tree::ptree& getPt() { return pt; }
    static const std::string& getQuestionsPath() { return questionsPath; }

    virtual unsigned int input() const;
    virtual void back() const;
};
#endif /*GAME_H*/