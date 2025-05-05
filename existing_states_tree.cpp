
#include "existing_states_tree.h"

ExistingStatesTree::ExistingStatesTree()
{
	root = new Node(10000);
}

Node::Node(uint16_t number)
	: number(number), current_moves(0) {
}

bool ExistingStatesTree::is_added(State* currentState) {
	Node* currentNode = root;

	for (int i = 0; i < field_size; i++) {
		for (int j = 0; j < field_size; j++) {
			uint8_t number = currentState->tilesMatrix[i][j];
			bool haveNode = false;

			for (Node* child : currentNode->next_number) {
				if (child->number == number) {
					haveNode = true;
					currentNode = child;
					break;
				}
			}

			if (!haveNode) {
				Node* newNode = new Node(number);
				currentNode->next_number.push_back(newNode);
				currentNode = newNode;
			}
		}
	}
	if (currentNode->current_moves == 0 || currentState->current_moves < currentNode->current_moves) {
		currentNode->current_moves = currentState->current_moves;
		return true;
	}
	return false;
}