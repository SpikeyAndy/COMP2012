#include "swiss.h"
#include "match.h"
#include "player.h"

Swiss::Swiss(const int numRounds, const PlayerList& list)
{
    // std::cout << "Constuctor: Start Swiss" << std::endl;
    this->curRound = 0;
    this->numRounds = numRounds;
    this->list = list;
    this->list.sort();
    // std::cout << "Constuctor: End Swiss" << std::endl;
}

Swiss::~Swiss(){}


void Swiss::play(){
    // std::cout << "Play: Start" << std::endl;
    for (this->curRound = 1; this->curRound <= this->numRounds; this->curRound++)
    {
        int maxScore = 2 * curRound - 1;
        PlayerList* array = new PlayerList[maxScore]; //new an array of PlayerList
        for (int i = 0; i < maxScore; i++)
        {
            PlayerList*hi = new PlayerList();
            array[i] = *hi;
        }
        for (int j = 0; j < this->list.getNumPlayers(); j++)
        {
            
            Player* player = this->list.getPlayer(j);
            int score = player->getScore();
            
            // std::cout << array[score].getNumPlayers() << std::endl;
            
            array[score].addPlayer(player); 
        }

        for (int scores = maxScore - 1; scores >= 0; scores--)
        {
            PlayerList currentList = array[scores];

            if (array[scores].getNumPlayers() == 0) {
                continue;
            }

            else if (array[scores].getNumPlayers() > 1) {
                array[scores].sort();
            }

            int number = array[scores].getNumPlayers();
            // std::cout << number<< std::endl;
            int midIndex = number/2;

            if (number % 2 == 1) //if odd number
            {
                Player* last = array[scores].getPlayer(number-1);
                int nextScore = scores - 1;
                
                if (nextScore < 0) //score = 0
                {
                    last->addScore(2);
                    PlayerList *temp = array[scores].splice(0, number - 1);
                    array[scores] = *temp;                   
                    
                    }
                else
                {
                    array[scores] = *array[scores].splice(0, number - 1);
                    array[nextScore].addPlayer(last);
                }
            }
            for (int c = 0; c < midIndex; c++)
            {   
                
                Player* player1 = array[scores].getPlayer(c);
                Player* player2 = array[scores].getPlayer(midIndex+c);
                Match match(player1, player2);
                match.play();
            }
            array[scores].sort();  
            
        }  
        delete [] array;
        this->list.sort();
        printLeaderboard();  
    }
    // std::cout << "Play: End" << std::endl;
}

