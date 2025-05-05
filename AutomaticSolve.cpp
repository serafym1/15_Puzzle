
#include "AutomaticSolve.h"
#include "puzzle.h"
#include "qpropertyanimation.h"
#include <windows.h>

AutomaticSolve::AutomaticSolve(puzzle* parent, Tile** sourceArray)
	: parentW(parent)
{
	std::cout << "Starting program" << std::endl;
	for (int i = 0; i < field_size; i++) {
		for (int j = 0; j < field_size; j++) {
			int number = i * field_size + j + 1;
			if (number == field_size * field_size) {
				correctPos[0] = POS(field_size - 1, field_size - 1);
			}
			else {
				correctPos[number] = POS(j, i);
			}
			sourceArray[i*4+j]->setDisabled(true);
		}
	}
	
	State* state = new State(sourceArray, correctPos);
	states_queue.push(state);
	automatic_solve();
	
	parentW->menu->moves_num = swapOrder.size();
	parentW->menu->moves_counter->setText("Moves left:\n" + QString::number(swapOrder.size()) + "/" + QString::number(parentW->menu->moves_num));
	parentW->menu->moves_counter->update();
	Tile* moveTile;
	do {
		moveTile = parentW->field->tilesArray[swapOrder.top()];
		swapOrder.pop();
		QPropertyAnimation* anim = new QPropertyAnimation(moveTile, "pos", parentW);
		anim->setDuration(600);
		anim->setStartValue(moveTile->pos());
		anim->setEndValue(parentW->field->tile0->pos());
		anim->setEasingCurve(QEasingCurve::InOutCubic);
		parentW->field->tile0->move(moveTile->pos());

		QEventLoop loop;
		QObject::connect(anim, &QPropertyAnimation::finished, &loop, &QEventLoop::quit);
		anim->start();
		loop.exec();
		std::swap(parentW->field->tile0->index, moveTile->index);

		parentW->menu->moves_counter->setText("Moves left:\n" + QString::number(swapOrder.size()) + "/" + QString::number(parentW->menu->moves_num));
		parentW->menu->moves_counter->update();
		
	} while (!swapOrder.empty());
		
	parentW->showResult();
}

void AutomaticSolve::automatic_solve()
{
	do {
		State* currentState = states_queue.top(); 
		states_queue.pop();
		
		std::cout << "Heu: " << currentState->prognised_heuristic
			<< " Moves: " << currentState->current_moves << std::endl;

		parentW->menu->moves_counter->setText("Solving...");
		parentW->menu->moves_counter->update();
		parentW->menu->moves_counter->repaint();

		for (ZeroMovesDir dir : {UP, DOWN, LEFT, RIGHT}) {
			if (currentState->can_move(dir)) {
				State* newState = new State(currentState, correctPos, dir);
				if (!existing_states.is_added(newState)) {
					delete newState;
				}
				else {
					states_queue.push(newState);
				}
			}

		}
	} while (states_queue.top()->prognised_heuristic != 0);
	for (int i = 0; i < field_size; i++) {
		for (int j = 0; j < field_size; j++) {
			std::cout << int(states_queue.top()->tilesMatrix[i][j]) << "\t";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl << "\tMoves:\t" << int(states_queue.top()->current_moves) << std::endl << std::endl;

	State* thisState = states_queue.top();
	do {

		int swapped_tile = thisState->parent_state->tilesMatrix[thisState->zero_pos.y][thisState->zero_pos.x];
		swapOrder.push(swapped_tile - 1);
		thisState = thisState->parent_state;
	} while (thisState->parent_state != nullptr);
	delete thisState;

	while (!states_queue.empty()) {
		State* thisState = states_queue.top();
		states_queue.pop();
		delete thisState;
	}
}

//bool AutomaticSolve::check_unique_and_add(State* current)
//{
//	for (State* existing : existing_states) {
//		if (current->is_same(existing)) {
//			if (current->current_moves < existing->current_moves) {
//				*existing = *current;
//				states_queue.push(current);
//				return true;
//			}
//			return false;
//		}
//
//	}
//	existing_states.push_back(current);
//	states_queue.push(current);
//
//	return true;
//}

AutomaticSolve::~AutomaticSolve()
{
	
}