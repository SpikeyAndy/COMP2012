#include "boardtree.h"


// Implement the constructor
BoardTree::BoardTree(const Board& board) {
    // Allocate memory for root node
    root = new BoardNode(board);
}


// Implement the destructor
BoardTree::~BoardTree() {
    // DONE: Implement destructor
    delete root;
    root = nullptr;
}

// Implement getSubTree function
BoardTree* BoardTree::getSubTree(const BoardCoordinate& coords) {
    int row = coords.row;
    int col = coords.col;

    BoardTree* tree = nullptr;

    if (root->subTree[row][col].root == nullptr) { 
        Board copyBoard = root->board; 
        if (copyBoard.play(coords)) { 
            root->subTree[row][col].root = new BoardNode(copyBoard);
        }
        else {
            return nullptr;
        }
    }

    tree = &root->subTree[row][col];
    return tree;
}



// Implement getOptimalMove function
BoardOptimalMove BoardTree::getOptimalMove(const unsigned int depth) { //std::cout << "getOptimalMove starting at " << depth << std::endl;
    // DONE : Implement getOptimalMove function
    if (root == nullptr) {
        // std::cout << "root is null, ILLEGAL MOVE returned -1 -1" << std::endl; //<cout>
        return BoardOptimalMove();
    }
    if (depth == 0 || root->board.isFinished()) {
        // std::cout << "BOARD finished or depth = 0" << std::endl; //<cout>
        // BoardCoordinate coord = BoardCoordinate(); //- maybe it was this that cause it to use the coordinate
        return BoardOptimalMove(root->board.getBoardScore(), BoardCoordinate{-1,-1}); //! somehow it uses this coordinate
    }
    BoardOptimalMove bestMove = BoardHashTable::getInstance().getHashedMove(root->board.getID(), depth);
    if (bestMove.score != ILLEGAL) {
        //std::cout << "bestmove HashTABLE: " << bestMove.score << std::endl;
        return bestMove;
    }

    int estimatedScore = -2147483648; // the minimum value of an int; //assume curPlayer is X
    if (root->board.getCurPlayer() == O) 
        estimatedScore = 2147483647;
    //std::cout << "DEFINE estimateScore : " << estimatedScore << std::endl;

    //BoardOptimalMove bestMove{};

    for (int row = 0; row < BOARD_SIZE; row++) { //! POTENTIAL PROBLEM: difficult to debug with recurrsion and loop calling getSubTree(coords) and getOptimalMove(depth)
        for (int col = 0; col < BOARD_SIZE; col++) {
            BoardCoordinate coord(row, col);
            
            BoardTree* childTree = getSubTree(coord);  
            if (childTree == nullptr) continue;  // handles the return nullptr: if the coords are invalid.

            // If the child tree corresponds to an invalid move/board, simply skip to the next subtree
            BoardOptimalMove childMove = childTree->getOptimalMove(depth - 1);
            if (childMove.score == ILLEGAL) {
                continue;
            }
            if ((root->board.getCurPlayer() == X && childMove.score > estimatedScore) // if the current player is X and score is bigger than the Estmated, then that will be the chosen
            || (root->board.getCurPlayer() == O && childMove.score < estimatedScore)) {
                // std::cout << "CHECK estimateScore : " << estimatedScore << std::endl;
                estimatedScore = childMove.score;
                bestMove = BoardOptimalMove(estimatedScore, coord);
            }  
        }         
    }
    //std::cout << "getOptimalMove(bestMove) end << " << bestMove.score << std::endl;
    BoardHashTable::getInstance().updateTable(root->board.getID(), depth, bestMove);
    return bestMove;
}

// Implement getOptimalMoveAlphaBeta function
BoardOptimalMove BoardTree::getOptimalMoveAlphaBeta(const unsigned int depth, int alpha, int beta) { //not implemented yet.
    // TODO: Implement getOptimalMoveAlphaBeta function
        if (root == nullptr) {
        // std::cout << "root is null, ILLEGAL MOVE returned -1 -1" << std::endl; //<cout>
        return BoardOptimalMove();
    }
    if (depth == 0 || root->board.isFinished()) {
        // std::cout << "BOARD finished or depth = 0" << std::endl; //<cout>
        // BoardCoordinate coord = BoardCoordinate(); //- maybe it was this that cause it to use the coordinate
        return BoardOptimalMove(root->board.getBoardScore(), BoardCoordinate{-1,-1}); //! somehow it uses this coordinate
    }
    BoardOptimalMove bestMove = BoardHashTable::getInstance().getHashedMove(root->board.getID(), depth);
    if (bestMove.score != ILLEGAL) {
        //std::cout << "bestmove HashTABLE: " << bestMove.score << std::endl;
        return bestMove;
    }

    int estimatedScore = -2147483648; //assume curPlayer is X
    if (root->board.getCurPlayer() == O) 
        estimatedScore = 2147483647;
    //std::cout << "DEFINE estimateScore : " << estimatedScore << std::endl;

    //BoardOptimalMove bestMove{};

    for (int row = 0; row < BOARD_SIZE; row++) { //! POTENTIAL PROBLEM: difficult to debug with recurrsion and loop calling getSubTree(coords) and getOptimalMove(depth)
        for (int col = 0; col < BOARD_SIZE; col++) {
            BoardCoordinate coord(row, col);
            
            BoardTree* childTree = getSubTree(coord);  
            if (childTree == nullptr) continue;  // handles the return nullptr: if the coords are invalid.

            // If the child tree corresponds to an invalid move/board, simply skip to the next subtree
            BoardOptimalMove childMove = childTree->getOptimalMoveAlphaBeta(depth - 1, alpha, beta);
            if (childMove.score == ILLEGAL) {
                continue;
            }
            if ((root->board.getCurPlayer() == X && childMove.score > estimatedScore) // if the current player is X and score is bigger than the Estmated, then that will be the chosen
            || (root->board.getCurPlayer() == O && childMove.score < estimatedScore)) {
                // std::cout << "CHECK estimateScore : " << estimatedScore << std::endl;
                estimatedScore = childMove.score;
                bestMove = BoardOptimalMove(estimatedScore, coord);
            }  
            if (root->board.getCurPlayer() == X) {
                if (childMove.score > beta) {
                    return bestMove; }
                alpha = fmax(childMove.score, alpha);
            }
            if (root->board.getCurPlayer() == O) {
                if (childMove.score < alpha) {
                    return bestMove; }
                beta = fmin(childMove.score, beta);
            }         
        }         
    }
    //std::cout << "getOptimalMove(bestMove) end << " << bestMove.score << std::endl;
    BoardHashTable::getInstance().updateTable(root->board.getID(), depth, bestMove);
    return bestMove;
}
    
   