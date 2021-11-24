#pragma once
#include "../mp2-lab3-stack/TCalculator.h"
#include <msclr\marshal_cppstd.h>

namespace mp2lab3stackform {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// —водка дл€ MyForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
		{
			InitializeComponent();
			SetupTransparency();
		}

	protected:
		/// <summary>
		/// ќсвободить все используемые ресурсы.
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::PictureBox^ pictureBox1;
	private: System::Windows::Forms::TextBox^ textBoxExpr;

	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ labelResult;

	private: System::Windows::Forms::Button^ buttonCalc;

	protected:

	private:
		/// <summary>
		/// ќб€зательна€ переменна€ конструктора.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// “ребуемый метод дл€ поддержки конструктора Ч не измен€йте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MainForm::typeid));
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->textBoxExpr = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->labelResult = (gcnew System::Windows::Forms::Label());
			this->buttonCalc = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->SuspendLayout();
			// 
			// pictureBox1
			// 
			this->pictureBox1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pictureBox1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox1.Image")));
			this->pictureBox1->Location = System::Drawing::Point(0, 0);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(451, 239);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::CenterImage;
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			// 
			// textBoxExpr
			// 
			this->textBoxExpr->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(97)), static_cast<System::Int32>(static_cast<System::Byte>(55)),
				static_cast<System::Int32>(static_cast<System::Byte>(182)));
			this->textBoxExpr->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18.15652F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBoxExpr->ForeColor = System::Drawing::Color::White;
			this->textBoxExpr->Location = System::Drawing::Point(12, 67);
			this->textBoxExpr->Name = L"textBoxExpr";
			this->textBoxExpr->Size = System::Drawing::Size(427, 40);
			this->textBoxExpr->TabIndex = 1;
			this->textBoxExpr->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->textBoxExpr->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MainForm::txInput_KeyDown);
			this->textBoxExpr->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MainForm::txInput_KeyPress);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->BackColor = System::Drawing::Color::Transparent;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.27826F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label1->ForeColor = System::Drawing::Color::White;
			this->label1->Location = System::Drawing::Point(7, 30);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(268, 30);
			this->label1->TabIndex = 2;
			this->label1->Text = L"Enter your expression:";
			// 
			// labelResult
			// 
			this->labelResult->BackColor = System::Drawing::Color::Transparent;
			this->labelResult->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20.03478F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->labelResult->ForeColor = System::Drawing::Color::White;
			this->labelResult->Location = System::Drawing::Point(152, 123);
			this->labelResult->Name = L"labelResult";
			this->labelResult->Size = System::Drawing::Size(287, 40);
			this->labelResult->TabIndex = 3;
			this->labelResult->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// buttonCalc
			// 
			this->buttonCalc->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(97)), static_cast<System::Int32>(static_cast<System::Byte>(55)),
				static_cast<System::Int32>(static_cast<System::Byte>(182)));
			this->buttonCalc->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->buttonCalc->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18.15652F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->buttonCalc->ForeColor = System::Drawing::Color::White;
			this->buttonCalc->Location = System::Drawing::Point(12, 123);
			this->buttonCalc->Name = L"buttonCalc";
			this->buttonCalc->Size = System::Drawing::Size(134, 40);
			this->buttonCalc->TabIndex = 4;
			this->buttonCalc->Text = L"=";
			this->buttonCalc->UseVisualStyleBackColor = false;
			this->buttonCalc->Click += gcnew System::EventHandler(this, &MainForm::buttonCalc_Click);
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(451, 239);
			this->Controls->Add(this->buttonCalc);
			this->Controls->Add(this->labelResult);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->textBoxExpr);
			this->Controls->Add(this->pictureBox1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MaximizeBox = false;
			this->Name = L"MainForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Calculator";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

		private: System::Void txInput_KeyPress(Object^ sender, KeyPressEventArgs^ e)
		{
			if (!Char::IsControl(e->KeyChar) && !Char::IsDigit(e->KeyChar) 
				&& e->KeyChar != '.' && e->KeyChar != '(' && e->KeyChar != ')'
				&& e->KeyChar != '+' && e->KeyChar != '-' && e->KeyChar != '*' && e->KeyChar != '/'
				&& e->KeyChar != ' ')
			{
				e->Handled = true;
			}
			if (e->KeyChar == 127) e->Handled = true;
		}

		private: System::Void txInput_KeyDown(Object^ sender, KeyEventArgs^ e)
		{
			if (e->KeyCode == Keys::Enter)
			{
				buttonCalc_Click(sender, e);
			}
		}

		private: System::Void buttonCalc_Click(Object^ sender, EventArgs^ e)
		{
			std::string infix = msclr::interop::marshal_as<std::string>(textBoxExpr->Text);

			if (String::IsNullOrEmpty((textBoxExpr->Text)->Trim()))
			{
				labelResult->Text = "";
				return;
			}

			TCalculator calc;
			calc.SetExpr(infix);

			if (!calc.CheckExpr())
			{
				labelResult->Text = "Incorrect";
				return;
			}

			try
			{
				double result = calc.Calc();
				labelResult->Text = Convert::ToString(result);
			}
			catch (...)
			{
				labelResult->Text = "Incorrect";
			}
		}

		void SetupTransparency()
		{
			label1->Parent = pictureBox1;
			labelResult->Parent = pictureBox1;
		}
	};
}