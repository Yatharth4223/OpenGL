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
		static double specularColorR = 0;
		static double specularColorG = 0;
		static double specularColorB = 0;
		
		static bool isTransforming = false;
		static bool isTranslating = false;
		static bool isRotating = false;
		static bool isScaling = false;
		static bool resetTransform = false;

		static bool isWaterScene= false;
		static bool isBlueTint = false;
		static bool isWireFrameRender = false;
		static double frequency = 0;
		static double amplitude = 0;

		static bool isSpaceScene = false;

	public:
		ToolWindow(void)
		{
			InitializeComponent();
			SpecularStrengthReading->Text = SpecularStrengthTrackBar->Value.ToString();
			SpecularColorR->Text = SpecularRtrackBar->Value.ToString();
			SpecularColorG->Text = SpecularGTrackBar->Value.ToString();
			SpecularColorB->Text = SpecularColorBTrackBar->Value.ToString();

			frequencytextBox->Text = frequencyTrackBar->Value.ToString();
			amplitudeTextBox->Text = amplitudeTrackBar->Value.ToString();
		}

	private: System::Windows::Forms::CheckBox^ TranslateCheckBox;
	private: System::Windows::Forms::CheckBox^ RotateCheckBox;
	private: System::Windows::Forms::CheckBox^ ScaleCheckBox;
	private: System::Windows::Forms::RadioButton^ SpaceSceneRadioButton;
	private: System::Windows::Forms::TrackBar^ frequencyTrackBar;

	private: System::Windows::Forms::TextBox^ frequencytextBox;

	private: System::Windows::Forms::TextBox^ textBox4;
	private: System::Windows::Forms::TextBox^ textBox8;
	private: System::Windows::Forms::TrackBar^ amplitudeTrackBar;

	private: System::Windows::Forms::CheckBox^ TinBluecheckBox;
	private: System::Windows::Forms::CheckBox^ WireFramecheckBox;
	private: System::Windows::Forms::TextBox^ amplitudeTextBox;






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
	private: System::Windows::Forms::RadioButton^ TransformRadioButton;
	private: System::Windows::Forms::Button^ ResetTransformButton;
	private: System::Windows::Forms::RadioButton^ WaterSceneButton;


	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

		private: System::Void ResetButton_Click(System::Object^ sender, System::EventArgs^ e) 
		{
			resetLightPosition = true;
		}


		private: System::Void SpecularStrengthTrackBar_Scroll(System::Object^ sender, System::EventArgs^ e) {
			SpecularStrengthReading->Text = SpecularStrengthTrackBar->Value.ToString();
			specularStrength = SpecularStrengthTrackBar->Value;
		}
		private: System::Void SpecularRtrackBar_Scroll(System::Object^ sender, System::EventArgs^ e) {
			SpecularColorR->Text = SpecularRtrackBar->Value.ToString();
			specularColorR = (double) SpecularRtrackBar->Value /100;

		}
		private: System::Void SpecularGTrackBar_Scroll(System::Object^ sender, System::EventArgs^ e) {
			SpecularColorG->Text = SpecularGTrackBar->Value.ToString();
			specularColorG = SpecularGTrackBar->Value;

		}
		private: System::Void SpecularColorBTrackBar_Scroll(System::Object^ sender, System::EventArgs^ e) {
			SpecularColorB->Text = SpecularColorBTrackBar->Value.ToString();
			specularColorB = SpecularColorBTrackBar->Value;
		}

		private: System::Void MoveLightRadioButton_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
			isMovingLight = MoveLightRadioButton->Checked;
		}

		//private: System::Void ResetTeapotPositionButton_Click(System::Object^ sender, System::EventArgs^ e) {
		//	resetTransform = true;
		//}

		//private: System::Void MoveCubesToSphereButton_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		//	isMovingLight = false;
		//	isTransforming = false;
		//}

		private: System::Void TransformRadioButton_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
			isTransforming = TransformRadioButton->Checked;
	    }
		private: System::Void ResetTransformButton_Click(System::Object^ sender, System::EventArgs^ e) {
			isTransforming = true;
		}

		private: System::Void TranslateButton_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
			isTranslating = TranslateCheckBox->Checked;
		}

		private: System::Void RotateButton_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
			isRotating = RotateCheckBox->Checked;
		}

		private: System::Void ScaleButton_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
			isScaling = ScaleCheckBox->Checked;
		}

		private: System::Void frequencyTrackBar_Scroll(System::Object^ sender, System::EventArgs^ e) {
			frequencytextBox->Text = frequencyTrackBar->Value.ToString();
			frequency = frequencyTrackBar->Value;
	    }

		private: System::Void amplitudeTrackBar_scroll(System::Object^ sender, System::EventArgs^ e) {
			amplitudeTextBox->Text = amplitudeTrackBar->Value.ToString();
			amplitude = amplitudeTrackBar->Value;
	    }

		private: System::Void WireFramecheckBox_checkedChanged(System::Object^ sender, System::EventArgs^ e) {
			isWireFrameRender = WireFramecheckBox->Checked;
		}

		private: System::Void TintBlueButton_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
			isBlueTint = true;
		}

		private: System::Void WaterSceneButton_checkedChanged(System::Object^ sender, System::EventArgs^ e) {
			isWaterScene = WaterSceneButton->Checked;
		}
		private: System::Void SpaceSceneRadioButton_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
			isSpaceScene = SpaceSceneRadioButton->Checked;
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
			this->TransformRadioButton = (gcnew System::Windows::Forms::RadioButton());
			this->ResetTransformButton = (gcnew System::Windows::Forms::Button());
			this->WaterSceneButton = (gcnew System::Windows::Forms::RadioButton());
			this->TranslateCheckBox = (gcnew System::Windows::Forms::CheckBox());
			this->RotateCheckBox = (gcnew System::Windows::Forms::CheckBox());
			this->ScaleCheckBox = (gcnew System::Windows::Forms::CheckBox());
			this->SpaceSceneRadioButton = (gcnew System::Windows::Forms::RadioButton());
			this->frequencyTrackBar = (gcnew System::Windows::Forms::TrackBar());
			this->frequencytextBox = (gcnew System::Windows::Forms::TextBox());
			this->textBox4 = (gcnew System::Windows::Forms::TextBox());
			this->textBox8 = (gcnew System::Windows::Forms::TextBox());
			this->amplitudeTrackBar = (gcnew System::Windows::Forms::TrackBar());
			this->TinBluecheckBox = (gcnew System::Windows::Forms::CheckBox());
			this->WireFramecheckBox = (gcnew System::Windows::Forms::CheckBox());
			this->amplitudeTextBox = (gcnew System::Windows::Forms::TextBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->SpecularStrengthTrackBar))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->SpecularRtrackBar))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->SpecularGTrackBar))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->SpecularColorBTrackBar))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->frequencyTrackBar))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->amplitudeTrackBar))->BeginInit();
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
			// TransformRadioButton
			// 
			this->TransformRadioButton->AccessibleName = L"TransformRadioButton";
			this->TransformRadioButton->AutoSize = true;
			this->TransformRadioButton->Location = System::Drawing::Point(12, 342);
			this->TransformRadioButton->Name = L"TransformRadioButton";
			this->TransformRadioButton->Size = System::Drawing::Size(89, 20);
			this->TransformRadioButton->TabIndex = 15;
			this->TransformRadioButton->Text = L"Transform";
			this->TransformRadioButton->UseVisualStyleBackColor = true;
			this->TransformRadioButton->CheckedChanged += gcnew System::EventHandler(this, &ToolWindow::TransformRadioButton_CheckedChanged);
			// 
			// ResetTransformButton
			// 
			this->ResetTransformButton->AccessibleName = L"ResetPositionButton";
			this->ResetTransformButton->Location = System::Drawing::Point(31, 368);
			this->ResetTransformButton->Name = L"ResetTransformButton";
			this->ResetTransformButton->Size = System::Drawing::Size(154, 23);
			this->ResetTransformButton->TabIndex = 16;
			this->ResetTransformButton->Text = L"Reset Transform";
			this->ResetTransformButton->UseVisualStyleBackColor = true;
			this->ResetTransformButton->Click += gcnew System::EventHandler(this, &ToolWindow::ResetTransformButton_Click);
			// 
			// WaterSceneButton
			// 
			this->WaterSceneButton->AutoSize = true;
			this->WaterSceneButton->Location = System::Drawing::Point(1, 497);
			this->WaterSceneButton->Name = L"WaterSceneButton";
			this->WaterSceneButton->Size = System::Drawing::Size(106, 20);
			this->WaterSceneButton->TabIndex = 17;
			this->WaterSceneButton->Text = L"Water Scene";
			this->WaterSceneButton->UseVisualStyleBackColor = true;
			this->WaterSceneButton->CheckedChanged += gcnew System::EventHandler(this, &ToolWindow::WaterSceneButton_checkedChanged);
			// 
			// TranslateCheckBox
			// 
			this->TranslateCheckBox->AutoSize = true;
			this->TranslateCheckBox->Location = System::Drawing::Point(31, 398);
			this->TranslateCheckBox->Name = L"TranslateCheckBox";
			this->TranslateCheckBox->Size = System::Drawing::Size(86, 20);
			this->TranslateCheckBox->TabIndex = 20;
			this->TranslateCheckBox->Text = L"Translate";
			this->TranslateCheckBox->UseVisualStyleBackColor = true;
			this->TranslateCheckBox->CheckedChanged += gcnew System::EventHandler(this, &ToolWindow::TranslateButton_CheckedChanged);
			// 
			// RotateCheckBox
			// 
			this->RotateCheckBox->AutoSize = true;
			this->RotateCheckBox->Location = System::Drawing::Point(31, 424);
			this->RotateCheckBox->Name = L"RotateCheckBox";
			this->RotateCheckBox->Size = System::Drawing::Size(69, 20);
			this->RotateCheckBox->TabIndex = 21;
			this->RotateCheckBox->Text = L"Rotate";
			this->RotateCheckBox->UseVisualStyleBackColor = true;
			this->RotateCheckBox->CheckedChanged += gcnew System::EventHandler(this, &ToolWindow::RotateButton_CheckedChanged);
			// 
			// ScaleCheckBox
			// 
			this->ScaleCheckBox->AutoSize = true;
			this->ScaleCheckBox->Location = System::Drawing::Point(31, 450);
			this->ScaleCheckBox->Name = L"ScaleCheckBox";
			this->ScaleCheckBox->Size = System::Drawing::Size(64, 20);
			this->ScaleCheckBox->TabIndex = 22;
			this->ScaleCheckBox->Text = L"Scale";
			this->ScaleCheckBox->UseVisualStyleBackColor = true;
			this->ScaleCheckBox->CheckedChanged += gcnew System::EventHandler(this, &ToolWindow::ScaleButton_CheckedChanged);
			// 
			// SpaceSceneRadioButton
			// 
			this->SpaceSceneRadioButton->AutoSize = true;
			this->SpaceSceneRadioButton->Location = System::Drawing::Point(2, 671);
			this->SpaceSceneRadioButton->Name = L"SpaceSceneRadioButton";
			this->SpaceSceneRadioButton->Size = System::Drawing::Size(110, 20);
			this->SpaceSceneRadioButton->TabIndex = 23;
			this->SpaceSceneRadioButton->Text = L"Space Scene";
			this->SpaceSceneRadioButton->UseVisualStyleBackColor = true;
			this->SpaceSceneRadioButton->CheckedChanged += gcnew System::EventHandler(this, &ToolWindow::SpaceSceneRadioButton_CheckedChanged);
			// 
			// frequencyTrackBar
			// 
			this->frequencyTrackBar->Location = System::Drawing::Point(191, 524);
			this->frequencyTrackBar->Maximum = 128;
			this->frequencyTrackBar->Minimum = 1;
			this->frequencyTrackBar->Name = L"frequencyTrackBar";
			this->frequencyTrackBar->Size = System::Drawing::Size(326, 56);
			this->frequencyTrackBar->TabIndex = 24;
			this->frequencyTrackBar->Value = 4;
			this->frequencyTrackBar->Scroll += gcnew System::EventHandler(this, &ToolWindow::frequencyTrackBar_Scroll);
			// 
			// frequencytextBox
			// 
			this->frequencytextBox->AccessibleName = L"";
			this->frequencytextBox->Location = System::Drawing::Point(523, 524);
			this->frequencytextBox->Name = L"frequencytextBox";
			this->frequencytextBox->Size = System::Drawing::Size(47, 22);
			this->frequencytextBox->TabIndex = 25;
			// 
			// textBox4
			// 
			this->textBox4->Location = System::Drawing::Point(31, 524);
			this->textBox4->Name = L"textBox4";
			this->textBox4->Size = System::Drawing::Size(76, 22);
			this->textBox4->TabIndex = 26;
			this->textBox4->Text = L"Frequency";
			// 
			// textBox8
			// 
			this->textBox8->Location = System::Drawing::Point(31, 579);
			this->textBox8->Name = L"textBox8";
			this->textBox8->Size = System::Drawing::Size(76, 22);
			this->textBox8->TabIndex = 27;
			this->textBox8->Text = L"Amplitude";
			// 
			// amplitudeTrackBar
			// 
			this->amplitudeTrackBar->Location = System::Drawing::Point(191, 571);
			this->amplitudeTrackBar->Maximum = 128;
			this->amplitudeTrackBar->Minimum = 1;
			this->amplitudeTrackBar->Name = L"amplitudeTrackBar";
			this->amplitudeTrackBar->Size = System::Drawing::Size(326, 56);
			this->amplitudeTrackBar->TabIndex = 28;
			this->amplitudeTrackBar->Value = 4;
			this->amplitudeTrackBar->Scroll += gcnew System::EventHandler(this, &ToolWindow::amplitudeTrackBar_scroll);
			// 
			// TinBluecheckBox
			// 
			this->TinBluecheckBox->AutoSize = true;
			this->TinBluecheckBox->Location = System::Drawing::Point(31, 645);
			this->TinBluecheckBox->Name = L"TinBluecheckBox";
			this->TinBluecheckBox->Size = System::Drawing::Size(81, 20);
			this->TinBluecheckBox->TabIndex = 29;
			this->TinBluecheckBox->Text = L"Tint Blue";
			this->TinBluecheckBox->UseVisualStyleBackColor = true;
			this->TinBluecheckBox->CheckedChanged += gcnew System::EventHandler(this, &ToolWindow::TintBlueButton_CheckedChanged);
			// 
			// WireFramecheckBox
			// 
			this->WireFramecheckBox->AutoSize = true;
			this->WireFramecheckBox->Location = System::Drawing::Point(31, 619);
			this->WireFramecheckBox->Name = L"WireFramecheckBox";
			this->WireFramecheckBox->Size = System::Drawing::Size(144, 20);
			this->WireFramecheckBox->TabIndex = 30;
			this->WireFramecheckBox->Text = L"WireFrame Render";
			this->WireFramecheckBox->UseVisualStyleBackColor = true;
			this->WireFramecheckBox->CheckedChanged += gcnew System::EventHandler(this, &ToolWindow::WireFramecheckBox_checkedChanged);
			// 
			// amplitudeTextBox
			// 
			this->amplitudeTextBox->AccessibleName = L"SpecularB";
			this->amplitudeTextBox->Location = System::Drawing::Point(523, 579);
			this->amplitudeTextBox->Name = L"amplitudeTextBox";
			this->amplitudeTextBox->Size = System::Drawing::Size(47, 22);
			this->amplitudeTextBox->TabIndex = 31;
			// 
			// ToolWindow
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(582, 700);
			this->Controls->Add(this->amplitudeTextBox);
			this->Controls->Add(this->WireFramecheckBox);
			this->Controls->Add(this->TinBluecheckBox);
			this->Controls->Add(this->amplitudeTrackBar);
			this->Controls->Add(this->textBox8);
			this->Controls->Add(this->textBox4);
			this->Controls->Add(this->frequencytextBox);
			this->Controls->Add(this->frequencyTrackBar);
			this->Controls->Add(this->SpaceSceneRadioButton);
			this->Controls->Add(this->ScaleCheckBox);
			this->Controls->Add(this->RotateCheckBox);
			this->Controls->Add(this->TranslateCheckBox);
			this->Controls->Add(this->WaterSceneButton);
			this->Controls->Add(this->ResetTransformButton);
			this->Controls->Add(this->TransformRadioButton);
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
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->frequencyTrackBar))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->amplitudeTrackBar))->EndInit();
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
