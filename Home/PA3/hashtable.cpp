#include "hashtable.h"

BoardOptimalMove BoardHashTable::getHashedMove(const unsigned long long id, const int depth) {
	int index = id % TABLE_SIZE;
	while (table[index] != nullptr) {
		if (table[index]->id == id) {
			return table[index]->optimalMove;
		}
		table[index] = table[index]->next;
	}
	return BoardOptimalMove();
	
}


// Update the table with the optimal move for the given id and depth.

// If id does not exist, create a new linked list node at (id % TABLE_SIZE).

// Else, if stored depth is lower, update the optimal move with the parameter. Otherwise, do nothing.

void BoardHashTable::updateTable(const unsigned long long id, const int depth, const BoardOptimalMove& optimalMove) {
	int index = id % TABLE_SIZE;
	while (table[index] != nullptr) {
		if (table[index]->id == id && table[index]->depth == depth) {
			table[index]->optimalMove = optimalMove;
		}
		table[index] = table[index]->next;
	}
	table[index] = new BoardHashNode(id, depth, optimalMove);
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
