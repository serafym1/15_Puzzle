
#include "ExistingStatesTree.h"

ExistingStatesTree::ExistingStatesTree()
{
	root = new Node(10000);
}

Node::Node(uint8_t number)
	: number(number), current_moves(0) {
}

bool ExistingStatesTree::isAdded(State* currentState) {
	Node* currentNode = root;

	for (int i = 0; i < FIELD_SIZE; i++) {
		for (int j = 0; j < FIELD_SIZE; j++) {
			uint8_t number = currentState->tilesMatrix[i][j];
			bool haveNode = false;

			for (Node* child : currentNode->nextNumber) {
				if (child->number == number) {
					haveNode = true;
					currentNode = child;
					break;
				}
			}

			if (!haveNode) {
				Node* newNode = new Node(number);
				currentNode->nextNumber.push_back(newNode);
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

ExistingStatesTree::~ExistingStatesTree() {
	deleteSubtree(root);
}

void ExistingStatesTree::deleteSubtree(Node* node) {
	if (!node) return;
	for (Node* child : node->nextNumber) {
		deleteSubtree(child);
	}
	delete node;
}