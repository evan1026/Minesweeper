#include "Game.h"

Game::Game(Minesweeper::Mode gamemode) {

	System::Random rand;

	if (gamemode == Minesweeper::Mode::EASY) {
		size = 8;
		numBombs = 9;
	} else if (gamemode == Minesweeper::Mode::MEDIUM) {
		size = 14;
		numBombs = 15;
	} else {
		size = 20;
		numBombs = 21;
	}

	gameboard = gcnew array<int, 2>(size, size);
	userboard = gcnew array<UserboardCell, 2>(size, size);
	buttons = gcnew array<System::Windows::Forms::Button^, 2>(size, size);

	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			gameboard[i, j] = 0;
			userboard[i, j] = UserboardCell::BLANK;
			buttons[i, j] = gcnew System::Windows::Forms::Button();
			buttons[i, j]->Location = System::Drawing::Point(BUTTON_SIZE * i, BUTTON_SIZE * j);
			buttons[i, j]->Size = System::Drawing::Size(BUTTON_SIZE, BUTTON_SIZE);
			buttons[i, j]->TabIndex = i * size + j;
			buttons[i, j]->Text = L"";
			buttons[i, j]->UseVisualStyleBackColor = true;
			buttons[i, j]->Margin = System::Windows::Forms::Padding(0);
			buttons[i, j]->Name = L"" + i + L"," + j;
			buttons[i, j]->BackColor = System::Drawing::SystemColors::Highlight;
		}
	}

	for (int i = 0; i < numBombs; ++i) {
		while (true) {
			int x = rand.Next(size);
			int y = rand.Next(size);

			if (gameboard[x, y] == 0) {
				gameboard[x, y] = -1;
				break;
			}
		}
	}

	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			if (gameboard[i, j] != -1) {
				if (i > 0) {
					if (                gameboard[i - 1, j]     == -1) gameboard[i, j] += 1;
					if (j > 0        && gameboard[i - 1, j - 1] == -1) gameboard[i, j] += 1;
					if (j < size - 1 && gameboard[i - 1, j + 1] == -1) gameboard[i, j] += 1;
				}
				if (i < size - 1) {
					if (                gameboard[i + 1, j]     == -1) gameboard[i, j] += 1;
					if (j > 0        && gameboard[i + 1, j - 1] == -1) gameboard[i, j] += 1;
					if (j < size - 1 && gameboard[i + 1, j + 1] == -1) gameboard[i, j] += 1;
				}
				if (j > 0        && gameboard[i, j - 1] == -1) gameboard[i, j] += 1;
				if (j < size - 1 && gameboard[i, j + 1] == -1) gameboard[i, j] += 1;
			}
		}
	}

	updateButtons();
}

void Game::updateButtons() {
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			if (userboard[i, j] == UserboardCell::BLANK) {
				buttons[i, j]->Text = L"";
				buttons[i, j]->BackColor = System::Drawing::SystemColors::Highlight;
			} else if (userboard[i, j] == UserboardCell::FLAGGED) {
				buttons[i, j]->Text = L"";
				buttons[i, j]->BackColor = System::Drawing::Color::Red;
			} else {
				buttons[i, j]->Text = L"" + gameboard[i, j];
				buttons[i, j]->BackColor = System::Drawing::SystemColors::Control;
				buttons[i, j]->Enabled = false;
			}
		}
	}
}

bool Game::dig(int i, int j, bool tryFlagged) {
	if (i >= size || i < 0) return false;
	if (j >= size || j < 0) return false;

	if (userboard[i, j] == UserboardCell::SHOWN) return false;

	if (userboard[i, j] == UserboardCell::FLAGGED) {
		if (!tryFlagged) return false;
		System::Windows::Forms::DialogResult^ result = System::Windows::Forms::MessageBox::Show(L"Are you sure?", "", System::Windows::Forms::MessageBoxButtons::YesNo);
		if (result->Equals(System::Windows::Forms::DialogResult::No)) return false;
	}

	if (gameboard[i, j] == -1) {
		System::Windows::Forms::MessageBox::Show("YOU LOSE!");
		return true;
	}

	userboard[i, j] = UserboardCell::SHOWN;

	if (gameboard[i, j] == 0) {
		dig(i,     j + 1, false);
		dig(i,     j - 1, false);
		dig(i + 1, j + 1, false);
		dig(i + 1, j,     false);
		dig(i + 1, j - 1, false);
		dig(i - 1, j + 1, false);
		dig(i - 1, j,     false);
		dig(i - 1, j - 1, false);
	}

	updateButtons();

	return checkWin();
}

bool Game::flag(int i, int j) {
	if (userboard[i, j] == UserboardCell::SHOWN) return false;

	if (userboard[i, j] == UserboardCell::BLANK) {
		userboard[i, j] = UserboardCell::FLAGGED;
		numFlags += 1;
	} else if (userboard[i, j] == UserboardCell::FLAGGED) {
		userboard[i, j] = UserboardCell::BLANK;
		numFlags += 1;
	}

	updateButtons();

	return checkWin();
}

bool Game::checkWin() {
	if (numFlags != numBombs) return false;

	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			if (userboard[i, j] == UserboardCell::BLANK) return false;
		}
	}

	System::Windows::Forms::MessageBox::Show("YOU WIN");
	return true;
}