#pragma once

#include "header.h"
#include "vector"
#include "State.h"

struct Node {
	Node(uint16_t number);
	uint8_t number;
	uint16_t current_moves; // 0 if it is not on the 16 level
	std::vector<Node*> next_number;
};

class ExistingStatesTree {
public:
	Node* root;
	ExistingStatesTree();
	bool is_added(State* currentState);
};
