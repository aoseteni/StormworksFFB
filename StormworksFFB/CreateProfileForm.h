#pragma once

#include "ProfileSave.h"

#include <msclr/marshal_cppstd.h>

namespace StormworksFFB {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// CreateProfileForm �̊T�v
	/// </summary>
	public ref class CreateProfileForm : public System::Windows::Forms::Form
	{
	public:
		CreateProfileForm(void)
		{
			InitializeComponent();
			//
			//TODO: �����ɃR���X�g���N�^�[ �R�[�h��ǉ����܂�
			//
		}

	protected:
		/// <summary>
		/// �g�p���̃��\�[�X�����ׂăN���[���A�b�v���܂��B
		/// </summary>
		~CreateProfileForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TextBox^  ProfileNameBox;
	protected:

	private: System::Windows::Forms::Button^  CreateButton;

	protected:

	private: 
		std::string* createFilename;
		Profile* saveProfile;
	private: System::Windows::Forms::Label^  label1;

	public:
		void SetData(Profile* saveProfile_, std::string* createFilename_) {
			saveProfile = saveProfile_;
			createFilename = createFilename_;
		}

	private:
		/// <summary>
		/// �K�v�ȃf�U�C�i�[�ϐ��ł��B
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// �f�U�C�i�[ �T�|�[�g�ɕK�v�ȃ��\�b�h�ł��B���̃��\�b�h�̓��e��
		/// �R�[�h �G�f�B�^�[�ŕύX���Ȃ��ł��������B
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(CreateProfileForm::typeid));
			this->ProfileNameBox = (gcnew System::Windows::Forms::TextBox());
			this->CreateButton = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// ProfileNameBox
			// 
			this->ProfileNameBox->Font = (gcnew System::Drawing::Font(L"Arial", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->ProfileNameBox->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->ProfileNameBox->Location = System::Drawing::Point(105, 11);
			this->ProfileNameBox->Name = L"ProfileNameBox";
			this->ProfileNameBox->Size = System::Drawing::Size(137, 22);
			this->ProfileNameBox->TabIndex = 0;
			// 
			// CreateButton
			// 
			this->CreateButton->BackColor = System::Drawing::SystemColors::Control;
			this->CreateButton->Font = (gcnew System::Drawing::Font(L"BIZ UDP�S�V�b�N", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(128)));
			this->CreateButton->Location = System::Drawing::Point(250, 11);
			this->CreateButton->Name = L"CreateButton";
			this->CreateButton->Size = System::Drawing::Size(75, 23);
			this->CreateButton->TabIndex = 1;
			this->CreateButton->Text = L"�V�K�쐬";
			this->CreateButton->UseVisualStyleBackColor = false;
			this->CreateButton->Click += gcnew System::EventHandler(this, &CreateProfileForm::CreateButton_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"BIZ UDP�S�V�b�N", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(128)));
			this->label1->Location = System::Drawing::Point(8, 16);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(91, 13);
			this->label1->TabIndex = 2;
			this->label1->Text = L"�v���t�@�C����";
			// 
			// CreateProfileForm
			// 
			this->AcceptButton = this->CreateButton;
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::Window;
			this->ClientSize = System::Drawing::Size(341, 45);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->CreateButton);
			this->Controls->Add(this->ProfileNameBox);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->KeyPreview = true;
			this->MaximizeBox = false;
			this->MaximumSize = System::Drawing::Size(357, 84);
			this->MinimumSize = System::Drawing::Size(357, 84);
			this->Name = L"CreateProfileForm";
			this->Text = L"CreateProfile";
			this->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &CreateProfileForm::CreateProfileForm_KeyPress);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void CreateButton_Click(System::Object^  sender, System::EventArgs^  e) {
		std::string filename = msclr::interop::marshal_as<std::string>(ProfileNameBox->Text);

		if (FindProfile(filename)) {
			// ���b�Z�[�W�{�b�N�X��\������
			System::String^ message = "�v���t�@�C�� " + ProfileNameBox->Text + " �͊��ɑ��݂���ׁA�쐬�ł��܂���B";
			System::String^ title = "�v���t�@�C���̍쐬�G���[";
			System::Windows::Forms::MessageBox::Show(message, title, MessageBoxButtons::OK, MessageBoxIcon::Warning);
		}
		else if (filename == "" || filename == "Default" || filename == "�{�V�K�쐬") {//�g�p�ł��Ȃ����O
			// ���b�Z�[�W�{�b�N�X��\������
			System::String^ message = "�g�p�ł��Ȃ��v���t�@�C�����ł��B";
			System::String^ title = "�v���t�@�C���̍쐬�G���[";
			System::Windows::Forms::MessageBox::Show(message, title, MessageBoxButtons::OK, MessageBoxIcon::Warning);
		}
		else if(saveProfile){
			if (SaveProfile(*saveProfile, filename)) {//�v���t�@�C���쐬
				if (createFilename) {
					*createFilename = filename;
				}
				this->Close();
			}
		}
		else {
			//�v���t�@�C���̍쐬���s
			// ���b�Z�[�W�{�b�N�X��\������
			System::String^ message = "�v���t�@�C���̍쐬�Ɏ��s���܂����B\n�����ȕ������܂܂�Ă���\��������܂��B";
			System::String^ title = "�v���t�@�C���̍쐬�G���[";
			System::Windows::Forms::MessageBox::Show(message, title, MessageBoxButtons::OK, MessageBoxIcon::Warning);
		}
	}

	private: System::Void CreateProfileForm_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
		//�g�p�ł��Ȃ�����
		if (e->KeyChar == '\\' ||
			e->KeyChar == '/' ||
			e->KeyChar == ':' ||
			e->KeyChar == '*' ||
			e->KeyChar == ':' ||
			e->KeyChar == '?' ||
			e->KeyChar == '\"' ||
			e->KeyChar == ':' ||
			e->KeyChar == '<' ||
			e->KeyChar == '>' ||
			e->KeyChar == '|')
		{
			System::Media::SystemSounds::Beep->Play();
			e->Handled = true;
			return;
		}

		//Esc�L�[�������ꂽ��t�H�[�������
		if (e->KeyChar == (char)Keys::Escape) {
			//�r�[�v�����Ȃ�Ȃ��悤�ɂ���
			e->Handled = true;
			//�t�H�[�������
			this->Close();
		}
	}
};
}
