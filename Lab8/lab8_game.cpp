// Nicholas A Moore
// CSIII
// Lab 8
// Part II
// 03/12/2023

#include "games.hpp"

int main() {
	srand(time(nullptr));

	Game* gp = nullptr;
	gp = new Dice;
	gp->playGame();
	delete gp;
}