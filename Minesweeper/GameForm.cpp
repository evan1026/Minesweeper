#include "GameForm.h"
#include "DifficultySelecter.h"
#include "Game.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThread]
void Main(array<String^>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	Minesweeper::GameForm form;
	form.startStuff();
	Application::Run(%form);

}

void Minesweeper::GameForm::startStuff() {

	this->Hide();

	Minesweeper::DifficultySelecter selecter;
	selecter.ShowDialog();

	game = gcnew Game(Minesweeper::gamemode);

	for (int i = 0; i < game->size; ++i){
		for (int j = 0; j < game->size; ++j) {
			this->Controls->Add(game->buttons[i, j]);
			game->buttons[i, j]->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &GameForm::handleButtonClick);
		}
	}
}

System::Void Minesweeper::GameForm::handleButtonClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
	System::Windows::Forms::Button^ origin = (System::Windows::Forms::Button^) sender;
	System::String^ iString = origin->Name->Substring(0, origin->Name->IndexOf(","));
	System::String^ jString = origin->Name->Substring(origin->Name->IndexOf(",") + 1);

	int i = int::Parse(iString);
	int j = int::Parse(jString);

	if (e->Button == System::Windows::Forms::MouseButtons::Left) {
		if (game->dig(i, j, true)) this->Close();
	} else if(e->Button == System::Windows::Forms::MouseButtons::Right) {
		if (game->flag(i, j)) this->Close();
	}
}