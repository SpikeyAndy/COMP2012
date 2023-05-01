#include "boardtree.h"

// Implement the constructor
BoardTree::BoardTree(const Board& board) {
    // TODO: Implement constructor
        root = new BoardNode(board);
}



// Implement the destructor
BoardTree::~BoardTree() {
    // TODO: Implement destructor
    delete root;
}

// Implement getSubTree function
BoardTree* BoardTree::getSubTree(const BoardCoordinate& coords) {
    // TODO: Implement getSubTree function
    if (root == nullptr)
    {
        return nullptr;
    }
    int row = coords.row;
    int col = coords.col;
    if (root->subTree[row][col] != nullptr) {
        return root->subTree[row][col];
    }
    Board newBoard = root->play(coords);
    if (newBoard.isValid()) {
        root->subTree[row][col] = new BoardTree(newBoard);
        return root->subTree[row][col];
    }
    return nullptr;
}

// Implement getOptimalMove function
BoardOptimalMove BoardTree::getOptimalMove(const unsigned int depth) {
        // TODO: Implement getOptimalMove function
        if (root == nullptr) {
            return BoardOptimalMove();
        }
        if (depth == 0 || root->board.isFinished()) {
            return BoardOptimalMove(this->score, this->coords);
        }
        int estimatedScore = (root->board.CurPlayer == X) ? INT_MIN : INT_MAX;
        BoardOptimalMove bestMove;
        for (int row = 0; row < BOARD_SIZE; row++) {
            for (int col = 0; col < BOARD_SIZE; col++) {
                BoardCoordinate coord(row, col);
                BoardTree* childTree = getSubTree(coord);       
                // If the child tree corresponds to an invalid move/board, simply skip to the next subtree
                if (childTree == nullptr) {
                    continue;
                }       
                BoardOptimalMove childMove = childTree->getOptimalMove(depth - 1);      
                if (childMove.score == ILLEGAL) {
                    continue;
                }       
                if ((root->board.curPlayer == X && childMove.score > estimatedScore) // if the current player is X and score is bigger than the Estmated, then that will be the chosen
                    || (root->board.curPlayer == O && childMove.score < estimatedScore)) {
                    estimatedScore = childMove.score;
                    bestMove = BoardOptimalMove(estimatedScore, this->board.coords);
                }
            }
        }
    return bestMove;
}

// Implement getOptimalMoveAlphaBeta function
BoardOptimalMove BoardTree::getOptimalMoveAlphaBeta(const unsigned int depth, int alpha, int beta) {
    // TODO: Implement getOptimalMoveAlphaBeta function
    
}
