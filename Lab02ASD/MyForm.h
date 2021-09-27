#pragma once
#include <cmath>
#define DECA pow(10, 2)
namespace Lab02ASD {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TextBox^ inputTB;
	private: System::Windows::Forms::TextBox^ nextInputTB;
	private: System::Windows::Forms::RichTextBox^ sortStagesRTB;

	protected:

	protected:


	private: System::Windows::Forms::TextBox^ resultTB;

	private: System::Windows::Forms::Button^ invokeButton;

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
			this->inputTB = (gcnew System::Windows::Forms::TextBox());
			this->nextInputTB = (gcnew System::Windows::Forms::TextBox());
			this->sortStagesRTB = (gcnew System::Windows::Forms::RichTextBox());
			this->resultTB = (gcnew System::Windows::Forms::TextBox());
			this->invokeButton = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// inputTB
			// 
			this->inputTB->Location = System::Drawing::Point(39, 32);
			this->inputTB->Name = L"inputTB";
			this->inputTB->Size = System::Drawing::Size(493, 22);
			this->inputTB->TabIndex = 0;
			// 
			// nextInputTB
			// 
			this->nextInputTB->Location = System::Drawing::Point(39, 103);
			this->nextInputTB->Name = L"nextInputTB";
			this->nextInputTB->Size = System::Drawing::Size(493, 22);
			this->nextInputTB->TabIndex = 1;
			// 
			// sortStagesRTB
			// 
			this->sortStagesRTB->Location = System::Drawing::Point(39, 136);
			this->sortStagesRTB->Name = L"sortStagesRTB";
			this->sortStagesRTB->Size = System::Drawing::Size(493, 275);
			this->sortStagesRTB->TabIndex = 2;
			this->sortStagesRTB->Text = L"";
			this->sortStagesRTB->TextChanged += gcnew System::EventHandler(this, &MyForm::sortStagesRTB_TextChanged);
			// 
			// resultTB
			// 
			this->resultTB->Location = System::Drawing::Point(28, 432);
			this->resultTB->Name = L"resultTB";
			this->resultTB->Size = System::Drawing::Size(504, 22);
			this->resultTB->TabIndex = 3;
			this->resultTB->TextChanged += gcnew System::EventHandler(this, &MyForm::resultTB_TextChanged);
			// 
			// invokeButton
			// 
			this->invokeButton->Location = System::Drawing::Point(216, 60);
			this->invokeButton->Name = L"invokeButton";
			this->invokeButton->Size = System::Drawing::Size(146, 37);
			this->invokeButton->TabIndex = 4;
			this->invokeButton->Text = L"Invoke";
			this->invokeButton->UseVisualStyleBackColor = true;
			this->invokeButton->Click += gcnew System::EventHandler(this, &MyForm::invokeButton_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(624, 501);
			this->Controls->Add(this->invokeButton);
			this->Controls->Add(this->resultTB);
			this->Controls->Add(this->sortStagesRTB);
			this->Controls->Add(this->nextInputTB);
			this->Controls->Add(this->inputTB);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
		double* arr;
		int n_size;
		void selectionSort() {
			double min;
			int index;
			for (int i = 0; i < n_size-1; i++) {
				index = i;
				sortStagesRTB->Text += "Iteration: " + i.ToString() +"\n";
				min = arr[i];
				for (int j = i+1; j < n_size; j++) {
					
					if (arr[j] < min) {
						min = arr[j];
						index = j;
					}
				}
				double tmp = arr[i];
				arr[i] = min;
				arr[index] = tmp;
				for (int l = 0; l < n_size; l++) {
					sortStagesRTB->Text += arr[l].ToString() + " ";
				}
				sortStagesRTB->Text += "\n";
			}
		}
	private: System::Void invokeButton_Click(System::Object^ sender, System::EventArgs^ e) {
		n_size = inputTB->Text->Split(' ')->Length;
		arr = new double[n_size];

		for (int i = 0; i < n_size; i++) {
			arr[i] = Convert::ToDouble(inputTB->Text->Split(' ')[i]);
			if ((i + 1) % 2 == 0) {
				arr[i] = (int)(sqrt(fabs(arr[i] - 10)) * DECA) / DECA;
			}
			nextInputTB->Text += arr[i].ToString() + " ";
			
		}
		selectionSort();
		for (int i = 0; i < n_size; i++) {
			resultTB->Text += arr[i].ToString() + " ";
		}
	}
	private: System::Void resultTB_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	}
private: System::Void sortStagesRTB_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	}
private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {
	OpenFileDialog^ file = gcnew OpenFileDialog();
	file->Filter = "txt files (*.txt)|*.txt";
	if (file->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
		String^ filePath = file->FileName;
		String^ lines = IO::File::ReadAllText(filePath);
		inputTB->Text = lines;
	}
}
};
}
