#pragma once
#include "MinesweeperGlobals.h"

namespace Minesweeper {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	Mode gamemode;

	/// <summary>
	/// Summary for DifficultySelecter
	/// </summary>
	public ref class DifficultySelecter : public System::Windows::Forms::Form
	{
	public:
		DifficultySelecter()
		{
			InitializeComponent();
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~DifficultySelecter()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  EasyButton;
	protected:
	private: System::Windows::Forms::Button^  MediumButton;
	private: System::Windows::Forms::Button^  HardButton;


	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->EasyButton = (gcnew System::Windows::Forms::Button());
			this->MediumButton = (gcnew System::Windows::Forms::Button());
			this->HardButton = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// EasyButton
			// 
			this->EasyButton->Location = System::Drawing::Point(12, 12);
			this->EasyButton->Name = L"EasyButton";
			this->EasyButton->Size = System::Drawing::Size(106, 66);
			this->EasyButton->TabIndex = 0;
			this->EasyButton->Text = L"Easy\r\n(8x8 - 9 bombs)";
			this->EasyButton->UseVisualStyleBackColor = true;
			this->EasyButton->Click += gcnew System::EventHandler(this, &DifficultySelecter::EasyButton_Click);
			// 
			// MediumButton
			// 
			this->MediumButton->Location = System::Drawing::Point(124, 12);
			this->MediumButton->Name = L"MediumButton";
			this->MediumButton->Size = System::Drawing::Size(106, 66);
			this->MediumButton->TabIndex = 1;
			this->MediumButton->Text = L"Medium\r\n(14x14 - 15 bombs)";
			this->MediumButton->UseVisualStyleBackColor = true;
			this->MediumButton->Click += gcnew System::EventHandler(this, &DifficultySelecter::MediumButton_Click);
			// 
			// HardButton
			// 
			this->HardButton->Location = System::Drawing::Point(236, 12);
			this->HardButton->Name = L"HardButton";
			this->HardButton->Size = System::Drawing::Size(106, 66);
			this->HardButton->TabIndex = 2;
			this->HardButton->Text = L"Hard\r\n(20x20 - 21 bombs)";
			this->HardButton->UseVisualStyleBackColor = true;
			this->HardButton->Click += gcnew System::EventHandler(this, &DifficultySelecter::HardButton_Click);
			// 
			// DifficultySelecter
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(354, 90);
			this->Controls->Add(this->HardButton);
			this->Controls->Add(this->MediumButton);
			this->Controls->Add(this->EasyButton);
			this->Name = L"DifficultySelecter";
			this->Text = L"Please Select a Difficulty";
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void EasyButton_Click(System::Object^  sender, System::EventArgs^  e) {
		Minesweeper::gamemode = Minesweeper::Mode::EASY;
		this->Close();
	}
	private: System::Void MediumButton_Click(System::Object^  sender, System::EventArgs^  e) {
		Minesweeper::gamemode = Minesweeper::Mode::MEDIUM;
		this->Close();
	}
	private: System::Void HardButton_Click(System::Object^  sender, System::EventArgs^  e) {
		Minesweeper::gamemode = Minesweeper::Mode::HARD;
		this->Close();
	}
	};
}
