#include "board.h"

Board::Board(const int score[][BOARD_SIZE]) : curPlayer{X}, id {0} {
    for (int i = 0; i < BOARD_SIZE; ++i) {
        cells[i] = new Cell[BOARD_SIZE];
        for (int j = 0; j < BOARD_SIZE; ++j){
                this->score[i][j] = score[i][j];       
        }
    }
}

        // Return true if all cells are not EMPTY.
bool Board::isFull() const {
    for (int i = 0; i < BOARD_SIZE; ++i) { 
        for (int j = 0; j < BOARD_SIZE; ++j) {
                return (this->cells[i][j] == EMPTY) ? false : true;
        }
    }
}

        // Return true if the game has finished (a match is found or board is full).
bool Board::isFinished() const {
    if (isFull()) return true;
    else 
    {
        for (int i = 0; i < BOARD_SIZE; ++i){ // first cell in row
                Cell currentCell = cells[i][0];
                if (currentCell == EMPTY) { continue; }
                int done = 0;
                for (int j = 1; j < BOARD_SIZE; ++j) { // check column to the right
                        if (cells[i][j] != currentCell) {
                                done = 0;
                                continue;
                        }
                        else {
                                done++;
                        }
                        if (j == BOARD_SIZE-1 && done == BOARD_SIZE-1) {
                                return true;
                        } 
                }
                currentCell = cells[0][i];
                for (int j = 1; j < BOARD_SIZE; ++j) { // check column to the right
                        if (cells[j][i] != currentCell) {
                                done = 0;
                                continue;
                        }
                        else {
                                done++;
                        }
                        if (j == BOARD_SIZE-1 && done == BOARD_SIZE-1) {
                                return true;
                        } 
                }
                currentCell = cells[0][0];
                for (int j = 1; j < BOARD_SIZE; ++j) {
                        if (cells[j][j] != currentCell) {
                                done = 0;
                                continue;
                        }
                        else {
                                done++;
                        }
                        if (j == BOARD_SIZE-1 && done == BOARD_SIZE-1) {
                                return true;
                        }
                }
                currentCell = cells[0][BOARD_SIZE-1];
                for (int j = BOARD_SIZE-2; j >= 0; --j) {
                        if (cells[j][BOARD_SIZE-j-1] != currentCell) {
                                done = 0;
                                continue;
                        }
                        else {
                                done++;
                        }
                        if (j == 0 && done == BOARD_SIZE-1) {
                                return true;
                        }
                }             
        }
        return false;  
    }
}

        // Calculate the board's current score.
int Board::getBoardScore() const {
        Cell Winner = 0; //todo make the cell and set the winner to this to know who won and then set if to see return WHAT
        if(isFinished()) {
                for (int i = 0; i < BOARD_SIZE; ++i){ // first cell in row
                        Cell currentCell = cells[i][0];
                        if (currentCell == EMPTY) { continue; }
                        int done = 0;
                        for (int j = 1; j < BOARD_SIZE; ++j) { // check column to the right
                                if (cells[i][j] != currentCell) {
                                        done = 0;
                                        continue;
                                }
                                else {
                                        done++;
                                }
                                if (j == BOARD_SIZE-1 && done == BOARD_SIZE-1) {
                                        Winner = currentCell;
                                } 
                        }
                        currentCell = cells[0][i];
                        for (int j = 1; j < BOARD_SIZE; ++j) { // check column to the right
                                if (cells[j][i] != currentCell) {
                                        done = 0;
                                        continue;
                                }
                                else {
                                        done++;
                                }
                                if (j == BOARD_SIZE-1 && done == BOARD_SIZE-1) {
                                        Winner = currentCell;
                                } 
                        }
                        currentCell = cells[0][0];
                        for (int j = 1; j < BOARD_SIZE; ++j) {
                                if (cells[j][j] != currentCell) {
                                        done = 0;
                                        continue;
                                }
                                else {
                                        done++;
                                }
                                if (j == BOARD_SIZE-1 && done == BOARD_SIZE-1) {
                                        Winner = currentCell;
                                }
                        }
                        currentCell = cells[0][BOARD_SIZE-1];
                        for (int j = BOARD_SIZE-2; j >= 0; --j) {
                                if (cells[j][BOARD_SIZE-j-1] != currentCell) {
                                        done = 0;
                                        continue;
                                }
                                else {
                                        done++;
                                }
                                if (j == 0 && done == BOARD_SIZE-1) {
                                        Winner = currentCell;
                                }
                        }            
                }
                if (Winner == X)
                        return WIN_SCORE;
                else if (Winner == O)
                        return -WIN_SCORE;              
        }
        int boardScore = 0;
        for (int i = 0; i < BOARD_SIZE; ++i) { 
                for (int j = 0; j < BOARD_SIZE; ++j) {
                        if (this->cells[i][j] == X){
                                int w = getCellWeight(cells[i][j]);
                                boardScore += w * X;
                        }
                        else if (this->cells[i][j] == O){
                                int w = getCellWeight(cells[i][j]);
                                boardScore += w * O;
                        }
                }
        }
        return boardScore;

}

        // Play the next move at coords. If successful, update the data members and return true. Otherwise return false.
bool Board::play(const BoardCoordinate& coords) {
        Cell curPlayer = this->curPlayer;
        if (!coords.isValid() || this->cells[coords.row][coords.col] != EMPTY) {
            return false;
        }
        cells[coords.row][coords.col] = curPlayer;
        
        (this->curPlayer == X) ? this->curPlayer = O : this->curPlayer = X;
        
        id = 0;
        for (int i = 0; i < BOARD_SIZE; ++i) {
                for (int j = 0; j < BOARD_SIZE; ++j) {
                        int cellValue = 0;
                        if (cells[i][j] == X) ++cellValue;
                        else if (cells[i][j] == O) cellValue+=2;
                        int power = pow(3,(i * BOARD_SIZE) + j);
                        id += cellValue * power;
                }
        }
    return true;
}