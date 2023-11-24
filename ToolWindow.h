#pragma once

namespace InitOpenGL {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for ToolWindow
	/// </summary>
	/// 
	

	public ref class ToolWindow : public System::Windows::Forms::Form
	{
	public : 
		static bool isMovingLight = true;
		static bool resetLightPosition = false;
		static int specularStrength = 0;
		static int specularColorR = 0;
		static int specularColorG = 0;
		static int specularColorB = 0;
		static bool isColoringByPosition = false;
		static bool resetTeapotPosition = false;
		static bool isMovingCubesToSpheres = false;


		ToolWindow(void)
		{
			InitializeComponent();

		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~ToolWindow()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::RadioButton^ MoveLightRadioButton;
	protected:

	private: System::Windows::Forms::Button^ ResetButton;
	protected:

	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::TrackBar^ SpecularStrengthTrackBar;

	private: System::Windows::Forms::TextBox^ SpecularStrengthReading;


	private: System::Windows::Forms::TextBox^ textBox3;
	private: System::Windows::Forms::TrackBar^ SpecularRtrackBar;
	private: System::Windows::Forms::TextBox^ SpecularColorR;



	private: System::Windows::Forms::TextBox^ textBox5;
	private: System::Windows::Forms::TextBox^ textBox6;
	private: System::Windows::Forms::TextBox^ textBox7;
	private: System::Windows::Forms::TrackBar^ SpecularGTrackBar;
	private: System::Windows::Forms::TrackBar^ SpecularColorBTrackBar;


	private: System::Windows::Forms::TextBox^ SpecularColorG;
	private: System::Windows::Forms::TextBox^ SpecularColorB;
	private: System::Windows::Forms::RadioButton^ ColorByPostionRadioButton;



	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::RadioButton^ radioButton3;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

		private: System::Void ResetButton_Click(System::Object^ sender, System::EventArgs^ e) 
		{
			resetLightPosition = true;
		}

		private: System::Void MoveLightRadioButton_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
			isMovingLight = true;
			isColoringByPosition = false;
			isMovingCubesToSpheres = false;
		}
		private: System::Void SpecularStrengthTrackBar_Scroll(System::Object^ sender, System::EventArgs^ e) {
			SpecularStrengthReading->Text = SpecularStrengthTrackBar->Value.ToString();
			specularStrength = SpecularStrengthTrackBar->Value;
		}
		private: System::Void SpecularRtrackBar_Scroll(System::Object^ sender, System::EventArgs^ e) {
			SpecularColorR->Text = SpecularRtrackBar->Value.ToString();
			specularColorR = SpecularRtrackBar->Value;

		}
		private: System::Void SpecularGTrackBar_Scroll(System::Object^ sender, System::EventArgs^ e) {
			SpecularColorG->Text = SpecularGTrackBar->Value.ToString();
			specularColorG = SpecularGTrackBar->Value;

		}
		private: System::Void SpecularColorBTrackBar_Scroll(System::Object^ sender, System::EventArgs^ e) {
			SpecularColorB->Text = SpecularColorBTrackBar->Value.ToString();
			specularColorB = SpecularColorBTrackBar->Value;
		}


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->MoveLightRadioButton = (gcnew System::Windows::Forms::RadioButton());
			this->ResetButton = (gcnew System::Windows::Forms::Button());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->SpecularStrengthTrackBar = (gcnew System::Windows::Forms::TrackBar());
			this->SpecularStrengthReading = (gcnew System::Windows::Forms::TextBox());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->SpecularRtrackBar = (gcnew System::Windows::Forms::TrackBar());
			this->SpecularColorR = (gcnew System::Windows::Forms::TextBox());
			this->textBox5 = (gcnew System::Windows::Forms::TextBox());
			this->textBox6 = (gcnew System::Windows::Forms::TextBox());
			this->textBox7 = (gcnew System::Windows::Forms::TextBox());
			this->SpecularGTrackBar = (gcnew System::Windows::Forms::TrackBar());
			this->SpecularColorBTrackBar = (gcnew System::Windows::Forms::TrackBar());
			this->SpecularColorG = (gcnew System::Windows::Forms::TextBox());
			this->SpecularColorB = (gcnew System::Windows::Forms::TextBox());
			this->ColorByPostionRadioButton = (gcnew System::Windows::Forms::RadioButton());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->radioButton3 = (gcnew System::Windows::Forms::RadioButton());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->SpecularStrengthTrackBar))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->SpecularRtrackBar))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->SpecularGTrackBar))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->SpecularColorBTrackBar))->BeginInit();
			this->SuspendLayout();
			// 
			// MoveLightRadioButton
			// 
			this->MoveLightRadioButton->AccessibleName = L"MoveLightRadioButton";
			this->MoveLightRadioButton->AutoSize = true;
			this->MoveLightRadioButton->Location = System::Drawing::Point(12, 12);
			this->MoveLightRadioButton->Name = L"MoveLightRadioButton";
			this->MoveLightRadioButton->Size = System::Drawing::Size(93, 20);
			this->MoveLightRadioButton->TabIndex = 0;
			this->MoveLightRadioButton->TabStop = true;
			this->MoveLightRadioButton->Text = L"Move Light";
			this->MoveLightRadioButton->UseVisualStyleBackColor = true;
			this->MoveLightRadioButton->CheckedChanged += gcnew System::EventHandler(this, &ToolWindow::MoveLightRadioButton_CheckedChanged);
			// 
			// ResetButton
			// 
			this->ResetButton->AccessibleName = L"";
			this->ResetButton->Location = System::Drawing::Point(31, 38);
			this->ResetButton->Name = L"ResetButton";
			this->ResetButton->Size = System::Drawing::Size(141, 23);
			this->ResetButton->TabIndex = 1;
			this->ResetButton->Text = L"Reset Light Position";
			this->ResetButton->UseVisualStyleBackColor = true;
			this->ResetButton->Click += gcnew System::EventHandler(this, &ToolWindow::ResetButton_Click);
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(31, 86);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(119, 22);
			this->textBox1->TabIndex = 2;
			this->textBox1->Text = L"Specular Strength";
			this->textBox1->TextChanged += gcnew System::EventHandler(this, &ToolWindow::textBox1_TextChanged);
			// 
			// SpecularStrengthTrackBar
			// 
			this->SpecularStrengthTrackBar->Location = System::Drawing::Point(191, 86);
			this->SpecularStrengthTrackBar->Maximum = 128;
			this->SpecularStrengthTrackBar->Minimum = 1;
			this->SpecularStrengthTrackBar->Name = L"SpecularStrengthTrackBar";
			this->SpecularStrengthTrackBar->Size = System::Drawing::Size(326, 56);
			this->SpecularStrengthTrackBar->TabIndex = 3;
			this->SpecularStrengthTrackBar->Value = 4;
			this->SpecularStrengthTrackBar->Scroll += gcnew System::EventHandler(this, &ToolWindow::SpecularStrengthTrackBar_Scroll);
			// 
			// SpecularStrengthReading
			// 
			this->SpecularStrengthReading->AccessibleName = L"SpecularStrengthReading";
			this->SpecularStrengthReading->Location = System::Drawing::Point(523, 86);
			this->SpecularStrengthReading->Name = L"SpecularStrengthReading";
			this->SpecularStrengthReading->Size = System::Drawing::Size(47, 22);
			this->SpecularStrengthReading->TabIndex = 4;
			this->SpecularStrengthReading->TextChanged += gcnew System::EventHandler(this, &ToolWindow::textBox2_TextChanged);
			// 
			// textBox3
			// 
			this->textBox3->Location = System::Drawing::Point(31, 164);
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(111, 22);
			this->textBox3->TabIndex = 5;
			this->textBox3->Text = L"Specular Color";
			this->textBox3->TextChanged += gcnew System::EventHandler(this, &ToolWindow::textBox3_TextChanged);
			// 
			// SpecularRtrackBar
			// 
			this->SpecularRtrackBar->Location = System::Drawing::Point(191, 164);
			this->SpecularRtrackBar->Maximum = 300;
			this->SpecularRtrackBar->Minimum = 1;
			this->SpecularRtrackBar->Name = L"SpecularRtrackBar";
			this->SpecularRtrackBar->Size = System::Drawing::Size(326, 56);
			this->SpecularRtrackBar->TabIndex = 6;
			this->SpecularRtrackBar->Value = 100;
			this->SpecularRtrackBar->Scroll += gcnew System::EventHandler(this, &ToolWindow::SpecularRtrackBar_Scroll);
			// 
			// SpecularColorR
			// 
			this->SpecularColorR->AccessibleName = L"";
			this->SpecularColorR->Location = System::Drawing::Point(523, 169);
			this->SpecularColorR->Name = L"SpecularColorR";
			this->SpecularColorR->Size = System::Drawing::Size(47, 22);
			this->SpecularColorR->TabIndex = 7;
			// 
			// textBox5
			// 
			this->textBox5->Location = System::Drawing::Point(156, 169);
			this->textBox5->Name = L"textBox5";
			this->textBox5->Size = System::Drawing::Size(29, 22);
			this->textBox5->TabIndex = 8;
			this->textBox5->Text = L"R";
			// 
			// textBox6
			// 
			this->textBox6->Location = System::Drawing::Point(156, 226);
			this->textBox6->Name = L"textBox6";
			this->textBox6->Size = System::Drawing::Size(29, 22);
			this->textBox6->TabIndex = 9;
			this->textBox6->Text = L"G";
			// 
			// textBox7
			// 
			this->textBox7->Location = System::Drawing::Point(156, 288);
			this->textBox7->Name = L"textBox7";
			this->textBox7->Size = System::Drawing::Size(29, 22);
			this->textBox7->TabIndex = 10;
			this->textBox7->Text = L"B";
			// 
			// SpecularGTrackBar
			// 
			this->SpecularGTrackBar->Location = System::Drawing::Point(191, 226);
			this->SpecularGTrackBar->Maximum = 300;
			this->SpecularGTrackBar->Minimum = 1;
			this->SpecularGTrackBar->Name = L"SpecularGTrackBar";
			this->SpecularGTrackBar->Size = System::Drawing::Size(326, 56);
			this->SpecularGTrackBar->TabIndex = 11;
			this->SpecularGTrackBar->Value = 100;
			this->SpecularGTrackBar->Scroll += gcnew System::EventHandler(this, &ToolWindow::SpecularGTrackBar_Scroll);
			// 
			// SpecularColorBTrackBar
			// 
			this->SpecularColorBTrackBar->Location = System::Drawing::Point(191, 288);
			this->SpecularColorBTrackBar->Maximum = 300;
			this->SpecularColorBTrackBar->Minimum = 1;
			this->SpecularColorBTrackBar->Name = L"SpecularColorBTrackBar";
			this->SpecularColorBTrackBar->Size = System::Drawing::Size(326, 56);
			this->SpecularColorBTrackBar->TabIndex = 12;
			this->SpecularColorBTrackBar->Value = 100;
			this->SpecularColorBTrackBar->Scroll += gcnew System::EventHandler(this, &ToolWindow::SpecularColorBTrackBar_Scroll);
			// 
			// SpecularColorG
			// 
			this->SpecularColorG->AccessibleName = L"SpecularG";
			this->SpecularColorG->Location = System::Drawing::Point(523, 226);
			this->SpecularColorG->Name = L"SpecularColorG";
			this->SpecularColorG->Size = System::Drawing::Size(47, 22);
			this->SpecularColorG->TabIndex = 13;
			// 
			// SpecularColorB
			// 
			this->SpecularColorB->AccessibleName = L"SpecularB";
			this->SpecularColorB->Location = System::Drawing::Point(523, 288);
			this->SpecularColorB->Name = L"SpecularColorB";
			this->SpecularColorB->Size = System::Drawing::Size(47, 22);
			this->SpecularColorB->TabIndex = 14;
			// 
			// ColorByPostionRadioButton
			// 
			this->ColorByPostionRadioButton->AccessibleName = L"ColorPositionRadioButton";
			this->ColorByPostionRadioButton->AutoSize = true;
			this->ColorByPostionRadioButton->Location = System::Drawing::Point(12, 342);
			this->ColorByPostionRadioButton->Name = L"ColorByPostionRadioButton";
			this->ColorByPostionRadioButton->Size = System::Drawing::Size(130, 20);
			this->ColorByPostionRadioButton->TabIndex = 15;
			this->ColorByPostionRadioButton->TabStop = true;
			this->ColorByPostionRadioButton->Text = L"Color By Position";
			this->ColorByPostionRadioButton->UseVisualStyleBackColor = true;
			// 
			// button2
			// 
			this->button2->AccessibleName = L"ResetTeapotPositionButton";
			this->button2->Location = System::Drawing::Point(31, 368);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(154, 23);
			this->button2->TabIndex = 16;
			this->button2->Text = L"Reset Teapot Position";
			this->button2->UseVisualStyleBackColor = true;
			// 
			// radioButton3
			// 
			this->radioButton3->AutoSize = true;
			this->radioButton3->Location = System::Drawing::Point(12, 416);
			this->radioButton3->Name = L"radioButton3";
			this->radioButton3->Size = System::Drawing::Size(171, 20);
			this->radioButton3->TabIndex = 17;
			this->radioButton3->TabStop = true;
			this->radioButton3->Text = L"Move Cubes To Sphere";
			this->radioButton3->UseVisualStyleBackColor = true;
			// 
			// ToolWindow
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(582, 553);
			this->Controls->Add(this->radioButton3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->ColorByPostionRadioButton);
			this->Controls->Add(this->SpecularColorB);
			this->Controls->Add(this->SpecularColorG);
			this->Controls->Add(this->SpecularColorBTrackBar);
			this->Controls->Add(this->SpecularGTrackBar);
			this->Controls->Add(this->textBox7);
			this->Controls->Add(this->textBox6);
			this->Controls->Add(this->textBox5);
			this->Controls->Add(this->SpecularColorR);
			this->Controls->Add(this->SpecularRtrackBar);
			this->Controls->Add(this->textBox3);
			this->Controls->Add(this->SpecularStrengthReading);
			this->Controls->Add(this->SpecularStrengthTrackBar);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->ResetButton);
			this->Controls->Add(this->MoveLightRadioButton);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
			this->Name = L"ToolWindow";
			this->Text = L"ToolWindow";
			this->TopMost = true;
			this->Load += gcnew System::EventHandler(this, &ToolWindow::ToolWindow_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->SpecularStrengthTrackBar))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->SpecularRtrackBar))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->SpecularGTrackBar))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->SpecularColorBTrackBar))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void ToolWindow_Load(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void radioButton1_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {

	}
	private: System::Void textBox1_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void textBox2_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	}
private: System::Void textBox3_TextChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void trackBar1_Scroll(System::Object^ sender, System::EventArgs^ e) {
}





};
}
