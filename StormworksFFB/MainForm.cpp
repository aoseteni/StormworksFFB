#include "MainForm.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace StormworksFFB;

[STAThreadAttribute]
int main() {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	MainForm ^mainForm = gcnew MainForm();

	Application::Run(mainForm);

	return 0;
}