#include "swiss.h"
#include "match.h"
#include "player.h"

Swiss::Swiss(const int numRounds, const PlayerList& list)
{
    std::cout << "Constuctor: Start Swiss" << std::endl;
    this->curRound = 0;
    this->numRounds = numRounds;
    this->list = list;
    this->list.sort();
    std::cout << "Constuctor: End Swiss" << std::endl;
}

Swiss::~Swiss(){}


void Swiss::play(){
    std::cout << "Play: Start" << std::endl;
    for (this->curRound = 1; this->curRound <= this->numRounds; this->curRound++)
    {
        int maxScore = 2 * curRound - 1;
        PlayerList* array = new PlayerList[maxScore]; //new an array of PlayerList
        
        for (int j = 0; j < this->list.getNumPlayers(); j++)
        {
            Player* player = this->list.getPlayer(j);
            int score = player->getScore();
            
            array[score].addPlayer(player); 
        }

        for (int scores = maxScore; scores >= 0; scores--)
        {
            PlayerList& currentList = array[scores];

            if (currentList.getNumPlayers() == 0) {
                continue;
            }

            currentList.sort();

            int number = currentList.getNumPlayers();
            int midIndex = number/2;
            if (number % 2 == 1) //if odd number
            {
                Player* last = currentList.getPlayer(number-1);
                int nextScore = scores - 1;
                
                if (nextScore < 0)
                {
                    last->addScore(2);
                }
                else
                {
                    currentList.splice(0, number - 1);
                    array[nextScore].addPlayer(last);
                }
            }
            for (int c = 0; c < number/2; c++)
            {   
                if (midIndex+c <= number)
                {
                    Player* player1 = currentList.getPlayer(c);
                    Player* player2 = currentList.getPlayer(midIndex+c);
                    Match match(player1, player2);
                    match.play();
                }
            }
            this->list.sort();   
        }  
        printLeaderboard();  
        delete[] array;   
    }
    std::cout << "Play: End" << std::endl;
}

