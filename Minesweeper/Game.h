#pragma once
#include "MinesweeperGlobals.h"

#define BUTTON_SIZE 30

enum UserboardCell {
	BLANK,
	FLAGGED,
	SHOWN
};

public ref struct Game {

	int numBombs;
	int numFlags;
	int size;

	array<int, 2>^ gameboard;
	array<UserboardCell, 2>^ userboard;
	array<System::Windows::Forms::Button^, 2>^ buttons;

	Game(Minesweeper::Mode gamemode);
	Game() {}

	void updateButtons();
	bool dig(int i, int j, bool tryFlagged);
	bool flag(int i, int j);
	bool checkWin();
};