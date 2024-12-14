#include "SignIn.h"

using namespace System;
using namespace System::Windows::Forms;
[STAThread]
void main (array<String^>^ args) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	task_manager::SignIn form;
	Application::Run(%form);
}