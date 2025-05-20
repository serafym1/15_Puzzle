
#include "AutomaticSolve.h"
#include "puzzle.h"
#include "qpropertyanimation.h"
#include <windows.h>

AutomaticSolve::AutomaticSolve(Puzzle* parent, Tile** sourceArray)
	: puzzle(parent)
{
	std::cout << "Starting program" << std::endl;
	for (int i = 0; i < FIELD_SIZE; i++) {
		for (int j = 0; j < FIELD_SIZE; j++) {
			int number = i * FIELD_SIZE + j + 1;
			if (number == FIELD_SIZE * FIELD_SIZE) {
				correctPos[0] = POS(FIELD_SIZE - 1, FIELD_SIZE - 1);
			}
			else {
				correctPos[number] = POS(j, i);
			}
			sourceArray[i*4+j]->setDisabled(true);
		}
	}
	
	State* state = new State(sourceArray, correctPos);
	if (state->heuristic == 0) {
		puzzle->showResult("So, why?", "The puzzle is already solved!!!");
	}
	statesQueue.push(state);
	automaticSolve();
	
	puzzle->movesCounter->moves_num = swapOrder.size();
	puzzle->movesCounter->updateMovesCounter("Moves left:\n" + QString::number(swapOrder.size()) + "/" + QString::number(puzzle->movesCounter->moves_num));
	Tile* moveTile;
	do {
		moveTile = puzzle->field->tilesArray[swapOrder.top()];
		swapOrder.pop();
		QPropertyAnimation* anim = new QPropertyAnimation(moveTile, "pos", puzzle);
		QObject::connect(anim, &QPropertyAnimation::finished, anim, &QObject::deleteLater);
		anim->setDuration(600);
		anim->setStartValue(moveTile->pos());
		anim->setEndValue(puzzle->field->tile0->pos());
		anim->setEasingCurve(QEasingCurve::InOutCubic);
		puzzle->field->tile0->move(moveTile->pos());

		QEventLoop loop;
		QObject::connect(anim, &QPropertyAnimation::finished, &loop, &QEventLoop::quit);
		anim->start();
		loop.exec();
		std::swap(puzzle->field->tile0->index, moveTile->index);

		puzzle->movesCounter->updateMovesCounter("Moves left:\n" + QString::number(swapOrder.size()) + "/" + QString::number(puzzle->movesCounter->moves_num));
		
	} while (!swapOrder.empty());
		
	puzzle->showResult("Info", "The puzzle was solved in " + QString::number(puzzle->movesCounter->moves_num) + " moves.");
}

void AutomaticSolve::automaticSolve()
{
	puzzle->movesCounter->updateMovesCounter("Solving...");
	do {
		State* currentState = statesQueue.top(); 
		statesQueue.pop();
		
		std::cout << "H " << currentState->heuristic
			<< " M " << currentState->current_moves << std::endl;

		for (ZeroMovesDir dir : {UP, DOWN, LEFT, RIGHT}) {
			if (currentState->canMove(dir)) {
				State* newState = new State(currentState, correctPos, dir);
				if (!existingStates.isAdded(newState)) {
					delete newState;
				}
				else {
					statesQueue.push(newState);
				}
			}
		}
	} while (statesQueue.top()->heuristic != 0);
	
	for (int i = 0; i < FIELD_SIZE; i++) {
		for (int j = 0; j < FIELD_SIZE; j++) {
			std::cout << int(statesQueue.top()->tilesMatrix[i][j]) << "\t";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl << "\tMoves:\t" << int(statesQueue.top()->current_moves) << std::endl << std::endl;

	State* thisState = statesQueue.top();
	do {

		int swapped_tile = thisState->parent_state->tilesMatrix[thisState->zero_pos.y][thisState->zero_pos.x];
		swapOrder.push(swapped_tile - 1);
		thisState = thisState->parent_state;
	} while (thisState->parent_state != nullptr);
	delete thisState;

	while (!statesQueue.empty()) {
		State* thisState = statesQueue.top();
		statesQueue.pop();
		delete thisState;
	}
}

AutomaticSolve::~AutomaticSolve()
{
	
}