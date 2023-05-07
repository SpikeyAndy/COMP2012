#include "board.h"

Board::Board(const int score[][BOARD_SIZE]) : curPlayer{X}, id {0} {
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j){
                cells[i][j] = EMPTY;
                this->score[i][j] = score[i][j];       
        }
    }
}

        // Return true if all cells are not EMPTY.
bool Board::isFull() const {
    for (int i = 0; i < BOARD_SIZE; i++) { 
        for (int j = 0; j < BOARD_SIZE; j++) {
                if (this->cells[i][j] == EMPTY) {
                        return false;
                }   
        }
    }
    return true;
}

        // Return true if the game has finished (a match is found or board is full).
bool Board::isFinished() const { /////! function uses the currentCell then check the other 2 cells and see if both are also currentCell (using done int)
                        
    if (isFull()) return true;
    else 
    {
        int done = 0;
        for (int i = 0; i < BOARD_SIZE; ++i){ // first cell in row
                Cell currentCell = cells[i][0];
                if (currentCell == EMPTY) {continue;} /////! this checks if EMPTY then it will not continue to check because EMPTY definitely no one win
                done = 0;
                for (int j = 1; j < BOARD_SIZE; ++j) { // check column to the right
                        // if (currentCell == EMPTY) { continue; }
                        if (cells[i][j] == currentCell) {
                                done++;
                                // continue;
                        }
                        else {
                                done = 0;
                        }
                        if (j == BOARD_SIZE-1 && done == BOARD_SIZE-1) {
                                return true;
                        } 
                }
        }
        for (int i = 0; i < BOARD_SIZE; ++i){
                done = 0;
                Cell currentCell = cells[0][i];
                if (currentCell == EMPTY) {continue;}
                for (int j = 1; j < BOARD_SIZE; ++j) { // check column to the right
                        if (cells[j][i] == currentCell) {
                                done++;
                        }
                        else {
                                done = 0;
                        }
                        if (j == BOARD_SIZE-1 && done == BOARD_SIZE-1) {
                                return true;
                        } 
                }
        }
        for (int i = 0; i < BOARD_SIZE; ++i){
                done = 0;
                Cell currentCell = cells[0][0];
                if (currentCell == EMPTY) {continue;}
                for (int j = 1; j < BOARD_SIZE; ++j) {
                        if (cells[j][j] == currentCell) {
                                done++;
                        }
                        else {
                                done = 0;
                        }
                        if (j == BOARD_SIZE-1 && done == BOARD_SIZE-1) {
                                return true;
                        }
                }
        }
        for (int i = 0; i < BOARD_SIZE; ++i){
                done = 0;
                Cell currentCell = cells[0][BOARD_SIZE-1];
                if (currentCell == EMPTY) {continue;}
                for (int j = BOARD_SIZE-2; j >= 0; --j) {
                        if (cells[BOARD_SIZE-j-1][j] == currentCell) {
                                done++;
                        }
                        else {
                                done = 0;
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
        Cell Winner = EMPTY; //todo make the cell and set the winner to this to know who won and then set if to see return WHAT
        if(isFinished()) { /////! same as the check finished but instead of returning true, it sets Winner = currentCell
                int done = 0;
                for (int i = 0; i < BOARD_SIZE; ++i){ // first cell in row 
                        Cell currentCell = cells[i][0];
                        if (currentCell == EMPTY) {continue;}
                        done = 0;
                        for (int j = 1; j < BOARD_SIZE; ++j) { // check column to the right
                                // if (currentCell == EMPTY) { continue; }
                                if (cells[i][j] == currentCell) {
                                done++;
                                // continue;
                                }
                                else {
                                        done = 0;
                                }
                                if (j == BOARD_SIZE-1 && done == BOARD_SIZE-1) {
                                        Winner = currentCell;
                                } 
                        }
                }
                for (int i = 0; i < BOARD_SIZE; ++i){
                        done = 0;
                        Cell currentCell = cells[0][i];
                        if (currentCell == EMPTY) {continue;}
                        for (int j = 1; j < BOARD_SIZE; ++j) { // check column to the right
                                // if (currentCell == EMPTY) { continue; }
                                if (cells[j][i] == currentCell) {
                                done++;
                                // continue;
                                }
                                else {
                                        done = 0;
                                }
                                if (j == BOARD_SIZE-1 && done == BOARD_SIZE-1) {
                                        Winner = currentCell;
                                } 
                        }
                }
                for (int i = 0; i < BOARD_SIZE; ++i){
                        done = 0;
                        Cell currentCell = cells[0][0];
                        if (currentCell == EMPTY) {continue;}
                        for (int j = 1; j < BOARD_SIZE; ++j) {
                                // if (currentCell == EMPTY) { continue; }
                                if (cells[j][j] == currentCell) {
                                done++;
                                // continue;
                                }
                                else {
                                        done = 0;
                                }
                                if (j == BOARD_SIZE-1 && done == BOARD_SIZE-1) {
                                        Winner = currentCell;
                                }
                        }
                }
                for (int i = 0; i < BOARD_SIZE; ++i){
                        done = 0;
                        Cell currentCell = cells[0][BOARD_SIZE-1];
                        if (currentCell == EMPTY) {continue;}
                        for (int j = BOARD_SIZE-2; j >= 0; --j) {
                                // if (currentCell == EMPTY) { continue; }
                                if (cells[BOARD_SIZE-j-1][j] == currentCell) {
                                        done++;
                                        // continue;
                                }
                                else {
                                       done = 0;
                                }
                                if (j == 0 && done == BOARD_SIZE-1) {
                                        Winner = currentCell;
                                }
                        }            
                }               
        }
        int boardScore = 0;
        if (Winner == X){
                boardScore = WIN_SCORE;
        }    
        else if (Winner == O) {
                boardScore = -WIN_SCORE;
        }           
        else if (Winner == EMPTY) { //!this should be correctly implemented
                int xScore = 0;
                int oScore = 0;
                for (int i = 0; i < BOARD_SIZE; ++i) { 
                        for (int j = 0; j < BOARD_SIZE; ++j) {
                                if (this->cells[i][j] == X){
                                        xScore += score[i][j];
                                }
                                else if (this->cells[i][j] == O){
                                        oScore += score[i][j];
                                }  
                        }
                }
                xScore = xScore * getCellWeight(X);
                oScore = oScore * getCellWeight(O);
                boardScore = xScore - oScore;
                return boardScore;
        }
        return boardScore;
}

        // Play the next move at coords. If successful, update the data members and return true. Otherwise return false.
bool Board::play(const BoardCoordinate& coords) {
    // Check if the move is valid
    if (!coords.isValid() || cells[coords.row][coords.col] != EMPTY) {
        return false;
    }

    // Update the board and player
    cells[coords.row][coords.col] = curPlayer;
    
    // Update the board ID
    int power = pow(3, coords.row * BOARD_SIZE + coords.col);
    if (cells[coords.row][coords.col] == O){
        id += 2 * power;
    }
    else if (cells[coords.row][coords.col] == X) {
        id += 1 * power;
    }
    
    //update player
    curPlayer = (curPlayer == X) ? O : X;

    return true;
}
