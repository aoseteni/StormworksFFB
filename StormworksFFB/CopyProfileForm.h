#pragma once

#include <msclr/marshal_cppstd.h>

#include "ProfileSave.h"
#include "CreateProfileForm.h"

namespace StormworksFFB {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// CopyProfileForm の概要
	/// </summary>
	public ref class CopyProfileForm : public System::Windows::Forms::Form
	{
	public:
		CopyProfileForm(void)
		{
			InitializeComponent();
			//
			//TODO: ここにコンストラクター コードを追加します
			//
		}

	protected:
		/// <summary>
		/// 使用中のリソースをすべてクリーンアップします。
		/// </summary>
		~CopyProfileForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::ComboBox^  ProfileList;
	protected:
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  BaseProfileName;

	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Button^  CopyButton;


	protected:

		Profile* baseProfile = nullptr;
		std::string* dsestinationName = nullptr;

	public:
	void SetData(ComboBox^ list, Profile& baseProfile_, std::string* dsestinationName_) {
		ProfileList->Items->Clear();
		//Default以外をコピー
		for (int i = 1; i < list->Items->Count; ++i) {
			if (i == list->SelectedIndex) { continue; }
			ProfileList->Items->Add(list->Items[i]->ToString());
		}

		BaseProfileName->Text = list->SelectedItem->ToString();

		baseProfile = &baseProfile_;
		dsestinationName = dsestinationName_;
	}

	private:
		/// <summary>
		/// 必要なデザイナー変数です。
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// デザイナー サポートに必要なメソッドです。このメソッドの内容を
		/// コード エディターで変更しないでください。
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(CopyProfileForm::typeid));
			this->ProfileList = (gcnew System::Windows::Forms::ComboBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->BaseProfileName = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->CopyButton = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// ProfileList
			// 
			this->ProfileList->DropDownHeight = 200;
			this->ProfileList->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->ProfileList->DropDownWidth = 200;
			this->ProfileList->Font = (gcnew System::Drawing::Font(L"Arial", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->ProfileList->IntegralHeight = false;
			this->ProfileList->ItemHeight = 16;
			this->ProfileList->Items->AddRange(gcnew cli::array< System::Object^  >(1) { L"fga" });
			this->ProfileList->Location = System::Drawing::Point(87, 31);
			this->ProfileList->Name = L"ProfileList";
			this->ProfileList->Size = System::Drawing::Size(147, 24);
			this->ProfileList->TabIndex = 25;
			// 
			// label1
			// 
			this->label1->Font = (gcnew System::Drawing::Font(L"BIZ UDPゴシック", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(128)));
			this->label1->Location = System::Drawing::Point(11, 11);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(68, 14);
			this->label1->TabIndex = 0;
			this->label1->Text = L"コピー元";
			// 
			// BaseProfileName
			// 
			this->BaseProfileName->BackColor = System::Drawing::SystemColors::Window;
			this->BaseProfileName->Font = (gcnew System::Drawing::Font(L"BIZ UDPゴシック", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(128)));
			this->BaseProfileName->Location = System::Drawing::Point(86, 11);
			this->BaseProfileName->Name = L"BaseProfileName";
			this->BaseProfileName->Size = System::Drawing::Size(183, 14);
			this->BaseProfileName->TabIndex = 0;
			this->BaseProfileName->Text = L"ProfileName";
			// 
			// label3
			// 
			this->label3->Font = (gcnew System::Drawing::Font(L"BIZ UDPゴシック", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(128)));
			this->label3->Location = System::Drawing::Point(11, 35);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(68, 14);
			this->label3->TabIndex = 26;
			this->label3->Text = L"コピー先";
			// 
			// CopyButton
			// 
			this->CopyButton->Font = (gcnew System::Drawing::Font(L"BIZ UDPゴシック", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(128)));
			this->CopyButton->Location = System::Drawing::Point(257, 31);
			this->CopyButton->Name = L"CopyButton";
			this->CopyButton->Size = System::Drawing::Size(75, 23);
			this->CopyButton->TabIndex = 27;
			this->CopyButton->Text = L"コピー";
			this->CopyButton->UseVisualStyleBackColor = true;
			this->CopyButton->Click += gcnew System::EventHandler(this, &CopyProfileForm::CopyButton_Click);
			// 
			// CopyProfileForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::Window;
			this->ClientSize = System::Drawing::Size(341, 61);
			this->Controls->Add(this->CopyButton);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->BaseProfileName);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->ProfileList);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MaximizeBox = false;
			this->MaximumSize = System::Drawing::Size(357, 100);
			this->MinimumSize = System::Drawing::Size(357, 100);
			this->Name = L"CopyProfileForm";
			this->Text = L"CopyProfile";
			this->Load += gcnew System::EventHandler(this, &CopyProfileForm::CopyProfileForm_Load);
			this->ResumeLayout(false);

		}
#pragma endregion
		private: System::Void CopyProfileForm_Load(System::Object^  sender, System::EventArgs^  e) {
			if (!baseProfile) {
				// メッセージボックスを表示する
				System::String^ message = "コピー元のプロファイルを受け取れませんでした。";
				System::String^ title = "エラー";
				System::Windows::Forms::DialogResult dialogResult =
					System::Windows::Forms::MessageBox::Show(message, title, MessageBoxButtons::OKCancel, MessageBoxIcon::Warning);

				//フォームを閉じる
				this->Close();
			}
		}

		private: System::Void CopyButton_Click(System::Object^  sender, System::EventArgs^  e) {
			//何も選択されていない場合
			if (ProfileList->SelectedIndex == -1) {
				// メッセージボックスを表示する
				System::String^ message = "コピー先のプロファイルを選択してください";
				System::String^ title = "プロファイルのコピーエラー";
				System::Windows::Forms::DialogResult dialogResult =
					System::Windows::Forms::MessageBox::Show(message, title, MessageBoxButtons::OK, MessageBoxIcon::Warning);
			} 
			else if (baseProfile) {
				//新規作成が選択されている
				if (ProfileList->SelectedIndex == ProfileList->Items->Count - 1) {
					//新規作成してコピーする
					CreateProfileForm form;
					std::string createProfileName = "";
					form.SetData(baseProfile, &createProfileName);
					form.StartPosition = FormStartPosition::CenterParent;//親の中心に表示させる
					form.ShowDialog(this);
					if (createProfileName != "") {
						//作成した名前を返す
						*dsestinationName = createProfileName;
						//フォームを閉じる
						this->Close();
					}
				}
				else {//ユーザープロファイルが選択されている
					// メッセージボックスを表示する
					System::String^ message = "プロファイル 「" + BaseProfileName->Text + "」 の設定を\nプロファイル 「" + ProfileList->SelectedItem->ToString() + "」 にコピーします。よろしいですか？\n※この操作は元に戻せません。";
					System::String^ title = "プロファイルのコピー";
					System::Windows::Forms::DialogResult dialogResult =
						System::Windows::Forms::MessageBox::Show(message, title, MessageBoxButtons::OKCancel, MessageBoxIcon::Warning);

					if (dialogResult == System::Windows::Forms::DialogResult::OK) {
						std::string dsestinationName_ = msclr::interop::marshal_as<std::string>(ProfileList->SelectedItem->ToString());

						//受け取った設定をコピー先の名前で保存(コピーする)
						SaveProfile(*baseProfile, dsestinationName_);

						//作成した名前を返す
						*dsestinationName = dsestinationName_;

						//フォームを閉じる
						this->Close();
					}
				}
			}
			else {
				// メッセージボックスを表示する
				System::String^ message = "予期せぬエラーが発生しました。";
				System::String^ title = "エラー";
				System::Windows::Forms::DialogResult dialogResult =
					System::Windows::Forms::MessageBox::Show(message, title, MessageBoxButtons::OK, MessageBoxIcon::Warning);

				//フォームを閉じる
				this->Close();
			}
		}
};
}
