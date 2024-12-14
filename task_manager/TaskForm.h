#pragma once
#include "LinkedList.h"
#include <msclr/marshal_cppstd.h> // For string conversion

namespace task_manager {

	using namespace System;
	using namespace System::Windows::Forms;
	using namespace System::Drawing;

	public ref class TaskForm : public Form {
	private:
		LinkedList* taskList; // LinkedList instance
		Panel^ scrollablePanel; // Panel for tasks
		TextBox^ txtTitle;
		TextBox^ txtDescription;

	public:
		TaskForm(void) {
			InitializeComponent();
			taskList = new LinkedList(); // Initialize linked list
		}

	protected:
		~TaskForm() {
			if (components) { delete components; }
			delete taskList;
		}

	private: 
		// Form components
		Button^ btnSubmit;
		Button^ btnDisplay;
		Label^ lblTitle;
		Label^ lblDescription;

		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void) {
			this->Text = L"Task Manager";
			this->Size = System::Drawing::Size(600, 500);
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;

			// Title label
			lblTitle = gcnew Label();
			lblTitle->Text = "Title:";
			lblTitle->Location = Point(20, 20);
			this->Controls->Add(lblTitle);

			// Title TextBox
			txtTitle = gcnew TextBox();
			txtTitle->Location = Point(80, 20);
			txtTitle->Size = Drawing::Size(200, 20);
			txtTitle->TextAlign = HorizontalAlignment::Center; // Center the text
			this->Controls->Add(txtTitle);

			// Description label
			lblDescription = gcnew Label();
			lblDescription->Text = "Description:";
			lblDescription->Location = Point(20, 60);
			this->Controls->Add(lblDescription);

			// Description TextBox
			txtDescription = gcnew TextBox();
			txtDescription->Location = Point(120, 60);
			txtDescription->Size = Drawing::Size(200, 20);
			this->Controls->Add(txtDescription);

			// Submit button
			btnSubmit = gcnew Button();
			btnSubmit->Text = "Submit";
			btnSubmit->Location = Point(20, 100);
			btnSubmit->Click += gcnew EventHandler(this, &TaskForm::btnSubmit_Click);
			this->Controls->Add(btnSubmit);

			// Display button
			btnDisplay = gcnew Button();
			btnDisplay->Text = "Display Tasks";
			btnDisplay->Location = Point(120, 100);
			btnDisplay->Click += gcnew EventHandler(this, &TaskForm::btnDisplay_Click);
			this->Controls->Add(btnDisplay);

			// Scrollable Panel for tasks
			scrollablePanel = gcnew Panel();
			scrollablePanel->Location = Point(20, 150);
			scrollablePanel->Size = Drawing::Size(500, 300);
			scrollablePanel->AutoScroll = true;
			scrollablePanel->BorderStyle = BorderStyle::FixedSingle;
			this->Controls->Add(scrollablePanel);
		}
#pragma endregion

		// Submit button event handler
		void btnSubmit_Click(Object^ sender, EventArgs^ e) {
			if (txtTitle->Text == "" || txtDescription->Text == "") {
				MessageBox::Show("Please enter both title and description.", "Error");
				return;
			}

			// Convert to TASK struct and append to LinkedList
			Task newTask;
			std::string title = msclr::interop::marshal_as<std::string>(txtTitle->Text);
			std::string description = msclr::interop::marshal_as<std::string>(txtDescription->Text);
			strcpy_s(newTask.title, sizeof(newTask.title), title.c_str());
			strcpy_s(newTask.description, sizeof(newTask.description), description.c_str());

			taskList->appendNodeBack(newTask);
			MessageBox::Show("Task added successfully!", "Success");

			// Clear inputs
			txtTitle->Text = "";
			txtDescription->Text = "";
		}

		// Display button event handler
		void btnDisplay_Click(Object^ sender, EventArgs^ e) {
			scrollablePanel->Controls->Clear(); // Clear previous tasks

			// Traverse the LinkedList and display tasks
			int yOffset = 10;
			Node* current = taskList->front;
			while (current != NULL) {
				Label^ title = gcnew Label();
				std::string titleText = "TITLE:: " + std::string(current->data.title);
				title->Text = gcnew String(titleText.c_str());
				title->Location = Point(10, yOffset);
				title->AutoSize = true;
				scrollablePanel->Controls->Add(title);
				
				yOffset += 20; // Add spacing

				Label^ description = gcnew Label();
				std::string descriptionText = "DESCRIPTION: " + std::string(current->data.description);
				description->Text = gcnew String(descriptionText.c_str());
				description->Location = Point(10, yOffset);
				description->AutoSize = true;
				scrollablePanel->Controls->Add(description);

				yOffset += 50; // Add spacing
				current = current->next;
			}
		}
	};
}
