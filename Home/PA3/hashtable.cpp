#include "hashtable.h"

BoardOptimalMove BoardHashTable::getHashedMove(const unsigned long long id, const int depth) {
    int index = id % TABLE_SIZE;
    BoardHashNode* curNode = table[index];
    while (curNode != nullptr) {
        if (curNode->id == id && curNode->depth >= depth) {
            return curNode->optimalMove;
        }
        curNode = curNode->next;
    }
    return BoardOptimalMove();
}


// Update the table with the optimal move for the given id and depth.

// If id does not exist, create a new linked list node at (id % TABLE_SIZE).

// Else, if stored depth is lower, update the optimal move with the parameter. Otherwise, do nothing.

void BoardHashTable::updateTable(const unsigned long long id, const int depth, const BoardOptimalMove& optimalMove) {
    int index = id % TABLE_SIZE;
    BoardHashNode* node = table[index];
    while (node != nullptr) {
        if (node->id == id && node->depth == depth) {
            if (optimalMove.score != ILLEGAL && node->id <= id) {
                node->optimalMove = optimalMove;
            }
            return;
        }
        node = node->next;
    }
    if (node == nullptr) {
        BoardHashNode* newNode = new BoardHashNode(id, depth, optimalMove);
        newNode->next = table[index];
        table[index] = newNode;
    }
}


// Clear all dynamic memory and reset table array to all nullptr.

void BoardHashTable::clearTable() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        BoardHashNode* current = table[i];
        while (current != nullptr) {
            BoardHashNode* next = current->next;  
            delete current;
            current = next;
        }
        table[i] = nullptr;
    }
}
