#pragma once

#include "header.h"
#include "vector"
#include "State.h"

struct Node {
	Node(uint8_t number);
	uint8_t number;
	uint16_t current_moves; // 0 if it is not on the 16 level
	std::vector<Node*> nextNumber;
};

class ExistingStatesTree {
public:
	ExistingStatesTree();
	~ExistingStatesTree();

	Node* root;

	bool isAdded(State* currentState);
	void deleteSubtree(Node* node);
};
