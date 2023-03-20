#include "player.h"
#include "match.h"
#include "swiss.h"
#include <cstring>
#include <iostream>


//TODO: TASK 1: Constructor and Destructor for player object
Player::Player(const char* const name, const int elo)
{
    char* newName = new char [strlen(name) + 1];
    std::strcpy(newName, name);
    this->name = newName;
    this->elo = elo;
    this->score = 0;
    // std::cout << "Constuctor: Player" << std::endl;
}

Player::~Player()
{
    // std::cout << "deleting: Player: " << name << std::endl;
    delete [] name;
    // std::cout << "deleted" << std::endl;
}

PlayerList::PlayerList()
{
    this->numPlayers = 0;
    this->players = nullptr;
}

PlayerList::PlayerList(const PlayerList& list)
{
    // std::cout << "Copy constructor: Start PlayerList" << std::endl;
    this->numPlayers = list.numPlayers;
    this->players = new Player*[list.numPlayers];
    for (int i = 0; i < list.numPlayers; i++)
    {
        this->players[i] = list.players[i];
    }
    // std::cout << "Copy Constuctor: End PlayerList" << std::endl;
}

PlayerList::~PlayerList()
{
    delete [] players;
    // if (!players)
    // {
    //     std::cout << "deleteing PlayerList:" << players << std::endl;
    //     delete [] players;
    // }
    // 
     std::cout << "deleted " << std::endl;
}

void PlayerList::addPlayer(Player* const player)
{
    //player->print();
    // std::cout << "Start: AddPlayer with numPlayers = " << this->numPlayers << std::endl;
    int realNo = this->numPlayers + 1;

    Player** temp = new Player*[realNo];
    
    this->numPlayers = realNo;

    for (int i = 0; i < realNo - 1; i++)
    {
        temp[i] = this->players[i];
    }
    temp[realNo-1] = player;

    delete [] this->players;
    this->players = temp;
    // std::cout << "End: AddPlayer with numPlayers = " << this->numPlayers << std::endl;
}

void PlayerList::sort()                      
{
    // std::cout << "Start: Sort with numPlayers = " << this->numPlayers << std::endl;
    
    for (int i = 0; i < this->numPlayers - 1; i++)
    {
        for (int j = i+1; j < this->numPlayers; j++)
        {
            if (this->players[j]->getScore() > this->players[i]->getScore())
            {
                Player *temp = this->players[i];
                this->players[i] = this->players[j];
                this->players[j] = temp;
            }
            else if (this->players[j]->getScore() == this->players[i]->getScore() && this->players[j]->getELO() > this->players[i]->getELO())
            {
                Player *temp = this->players[i];
                this->players[i] = this->players[j];
                this->players[j] = temp;
            }
        }
    }

    
    // std::cout << "End: Sort with numPlayers = " << this->numPlayers << std::endl;
}

PlayerList* PlayerList::splice(const int startIndex, const int endIndex) const
{
    // std::cout << "Splice: starting with " << this->getNumPlayers() << std::endl;
    int newNum = endIndex - startIndex;

    PlayerList* newlist = new PlayerList();
    
    // std::cout << "splice out "; this->players[endIndex]->print(); std::cout << std::endl;

    newlist->numPlayers = newNum;
    
    newlist->players = new Player*[newlist->numPlayers];

    for (int i = startIndex; i < endIndex; i++)
    {
        newlist->players[i - startIndex] = this->players[i];
    }
    newlist->sort();
    

    // std::cout << "Splice: end with numPlayers = " << newlist->numPlayers << std::endl;
    return newlist;
}
