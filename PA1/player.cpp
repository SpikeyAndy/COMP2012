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
    std::cout << "Constuctor: Player" << std::endl;
}

Player::~Player()
{
    delete [] name;
    std::cout << "Destructor: Player" << std::endl;
}

PlayerList::PlayerList()
{
    numPlayers = 0;
    players = nullptr;
}

PlayerList::PlayerList(const PlayerList& list)
{
    std::cout << "Copy constructor: Start PlayerList" << std::endl;
    numPlayers = list.numPlayers;
    players = new Player*[list.numPlayers];
    for (int i = 0; i < list.numPlayers; i++)
    {
        players[i] = list.players[i];
    }
    std::cout << "Copy Constuctor: End PlayerList" << std::endl;
}

PlayerList::~PlayerList()
{
    delete [] players;
}

void PlayerList::addPlayer(Player* const player)
{
    std::cout << "Start: AddPlayer" << std::endl;
    Player** uplayers = new Player*[this->numPlayers+1];
    
    this->numPlayers++;

    for (int i = 0; i < this->numPlayers; i++)
    {
        uplayers[i] = this->players[i];
    }
    uplayers[this->numPlayers] = player;
    delete [] this->players;
    this->players = uplayers;
    std::cout << "End: AddPlayer" << std::endl;
}

void PlayerList::sort() //bug: segmentation fault when sorting large number of players 
                        //todo: need to check!
{
    std::cout << "Start: Sort" << std::endl;
    for (int i = 0; i < this->numPlayers; i++)
    {
        for (int j = 0; j < this->numPlayers; j++)
        {
            if (this->players[i]->getELO() > this->players[j]->getELO())
            {
                Player *temp = this->players[i];
                this->players[i] = this->players[j];
                this->players[j] = temp;
            }
        }
    }
    std::cout << "End: Sort" << std::endl;
}

PlayerList* PlayerList::splice(const int startIndex, const int endIndex) const
{
    std::cout << "Splice: start" << std::endl;
    PlayerList* newlist = new PlayerList();
    newlist->numPlayers = endIndex - startIndex;
    Player** newplayer = new Player*[newlist->numPlayers];

    for (int i = startIndex; i < endIndex; i++)
    {
        newplayer[i] = this->players[i];
    }
    newlist->numPlayers--;
    newlist->players = newplayer;
    std::cout << "Splice: end" << std::endl;
    return newlist;
}
