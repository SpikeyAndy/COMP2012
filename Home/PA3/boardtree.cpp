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
    root = nullptr;
}

// Implement getSubTree function
BoardTree* BoardTree::getSubTree(const BoardCoordinate& coords) {
    if (!coords.isValid() || root == nullptr) {
        return nullptr;
    }
    int row = coords.row;
    int col = coords.col;
    BoardTree* subTree = &root->subTree[row][col];
    if (subTree->root != nullptr) {
        return subTree;
    }
    Board copyBoard = root->board;
    if (copyBoard.play(coords)) { //! 'this' argument to member function 'play' has type 'const Board', but function is not marked const
        return subTree;
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
        BoardCoordinate coord = BoardCoordinate(1,1);
        return BoardOptimalMove(root->board.getBoardScore(), coord);
    }
    int estimatedScore = (root->board.getCurPlayer() == X) ? INT_MIN : INT_MAX;
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
            if ((root->board.getCurPlayer() == X && childMove.score > estimatedScore) // if the current player is X and score is bigger than the Estmated, then that will be the chosen
                || (root->board.getCurPlayer() == O && childMove.score < estimatedScore)) {
                estimatedScore = childMove.score;
                bestMove = BoardOptimalMove(estimatedScore, coord);
            }
        }
    }
    return bestMove;
}

// Implement getOptimalMoveAlphaBeta function
BoardOptimalMove BoardTree::getOptimalMoveAlphaBeta(const unsigned int depth, int alpha, int beta) {
    // TODO: Implement getOptimalMoveAlphaBeta function
        if (root == nullptr) {
            return BoardOptimalMove();
        }
        if (depth == 0 || root->board.isFinished()) {
            BoardCoordinate coord = BoardCoordinate(0,0);
            return BoardOptimalMove(root->board.getBoardScore(), coord);
        }
        int estimatedScore = (root->board.getCurPlayer() == X) ? INT_MIN : INT_MAX;
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
                if ((root->board.getCurPlayer() == X && childMove.score > estimatedScore) // if the current player is X and score is bigger than the Estmated, then that will be the chosen
                    || (root->board.getCurPlayer() == O && childMove.score < estimatedScore)) {
                    estimatedScore = childMove.score;
                    bestMove = BoardOptimalMove(estimatedScore, coord);
                }
            }
        }
    return bestMove;
}
