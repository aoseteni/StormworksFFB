#pragma once

#include <Windows.h>

namespace StormworksFFB {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// TyreMonitorForm の概要
	/// </summary>
	public ref class TyreMonitorForm : public System::Windows::Forms::Form
	{
	public:
		TyreMonitorForm(void)
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
		~TyreMonitorForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::PictureBox^  TyreImageHolder;
	protected:

	private: System::ComponentModel::IContainer^  components;
	private: System::Windows::Forms::Timer^  TickTimer;

	protected:

	private:
		/// <summary>
		/// 必要なデザイナー変数です。
		/// </summary>

		float *leftTyreAngle = nullptr;//単位:rad
	private: System::Windows::Forms::Label^  Text_LeftTyreAngle_Deg;
	private: System::Windows::Forms::Label^  Text_RightTyreAngle_Deg;
	private: System::Windows::Forms::Label^  Text_LeftTyreAngle_Rad;


	private: System::Windows::Forms::Label^  Text_RightTyreAngle_Rad;
	private: System::Windows::Forms::CheckBox^  CheckBox_TopMost;
	private: System::Windows::Forms::Label^  Dumper_Line;



			 float *rightTyreAngle = nullptr;//単位:rad

	public: System::Void SetData(
		float *leftTyreAngle_,
		float *rightTyreAngle_
	) {
		leftTyreAngle = leftTyreAngle_;
		rightTyreAngle = rightTyreAngle_;
	}
			 


#pragma region Windows Form Designer generated code
		/// <summary>
		/// デザイナー サポートに必要なメソッドです。このメソッドの内容を
		/// コード エディターで変更しないでください。
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(TyreMonitorForm::typeid));
			this->TyreImageHolder = (gcnew System::Windows::Forms::PictureBox());
			this->TickTimer = (gcnew System::Windows::Forms::Timer(this->components));
			this->Text_LeftTyreAngle_Deg = (gcnew System::Windows::Forms::Label());
			this->Text_RightTyreAngle_Deg = (gcnew System::Windows::Forms::Label());
			this->Text_LeftTyreAngle_Rad = (gcnew System::Windows::Forms::Label());
			this->Text_RightTyreAngle_Rad = (gcnew System::Windows::Forms::Label());
			this->CheckBox_TopMost = (gcnew System::Windows::Forms::CheckBox());
			this->Dumper_Line = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->TyreImageHolder))->BeginInit();
			this->SuspendLayout();
			// 
			// TyreImageHolder
			// 
			this->TyreImageHolder->Enabled = false;
			this->TyreImageHolder->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"TyreImageHolder.Image")));
			this->TyreImageHolder->Location = System::Drawing::Point(25, 84);
			this->TyreImageHolder->Name = L"TyreImageHolder";
			this->TyreImageHolder->Size = System::Drawing::Size(100, 220);
			this->TyreImageHolder->TabIndex = 0;
			this->TyreImageHolder->TabStop = false;
			this->TyreImageHolder->Visible = false;
			// 
			// TickTimer
			// 
			this->TickTimer->Enabled = true;
			this->TickTimer->Interval = 16;
			this->TickTimer->Tick += gcnew System::EventHandler(this, &TyreMonitorForm::TickTimer_Tick);
			// 
			// Text_LeftTyreAngle_Deg
			// 
			this->Text_LeftTyreAngle_Deg->Anchor = System::Windows::Forms::AnchorStyles::Top;
			this->Text_LeftTyreAngle_Deg->Font = (gcnew System::Drawing::Font(L"Arial", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Text_LeftTyreAngle_Deg->Location = System::Drawing::Point(31, 9);
			this->Text_LeftTyreAngle_Deg->Name = L"Text_LeftTyreAngle_Deg";
			this->Text_LeftTyreAngle_Deg->Size = System::Drawing::Size(100, 18);
			this->Text_LeftTyreAngle_Deg->TabIndex = 1;
			this->Text_LeftTyreAngle_Deg->Tag = L"1.000";
			this->Text_LeftTyreAngle_Deg->Text = L"deg";
			this->Text_LeftTyreAngle_Deg->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			// 
			// Text_RightTyreAngle_Deg
			// 
			this->Text_RightTyreAngle_Deg->Anchor = System::Windows::Forms::AnchorStyles::Top;
			this->Text_RightTyreAngle_Deg->Font = (gcnew System::Drawing::Font(L"Arial", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Text_RightTyreAngle_Deg->Location = System::Drawing::Point(212, 9);
			this->Text_RightTyreAngle_Deg->Name = L"Text_RightTyreAngle_Deg";
			this->Text_RightTyreAngle_Deg->Size = System::Drawing::Size(100, 18);
			this->Text_RightTyreAngle_Deg->TabIndex = 2;
			this->Text_RightTyreAngle_Deg->Tag = L"1.000";
			this->Text_RightTyreAngle_Deg->Text = L"deg";
			this->Text_RightTyreAngle_Deg->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			// 
			// Text_LeftTyreAngle_Rad
			// 
			this->Text_LeftTyreAngle_Rad->Anchor = System::Windows::Forms::AnchorStyles::Top;
			this->Text_LeftTyreAngle_Rad->Font = (gcnew System::Drawing::Font(L"Arial", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Text_LeftTyreAngle_Rad->Location = System::Drawing::Point(31, 27);
			this->Text_LeftTyreAngle_Rad->Name = L"Text_LeftTyreAngle_Rad";
			this->Text_LeftTyreAngle_Rad->Size = System::Drawing::Size(100, 18);
			this->Text_LeftTyreAngle_Rad->TabIndex = 3;
			this->Text_LeftTyreAngle_Rad->Tag = L"1.000";
			this->Text_LeftTyreAngle_Rad->Text = L"rad";
			this->Text_LeftTyreAngle_Rad->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			// 
			// Text_RightTyreAngle_Rad
			// 
			this->Text_RightTyreAngle_Rad->Anchor = System::Windows::Forms::AnchorStyles::Top;
			this->Text_RightTyreAngle_Rad->Font = (gcnew System::Drawing::Font(L"Arial", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Text_RightTyreAngle_Rad->Location = System::Drawing::Point(212, 27);
			this->Text_RightTyreAngle_Rad->Name = L"Text_RightTyreAngle_Rad";
			this->Text_RightTyreAngle_Rad->Size = System::Drawing::Size(100, 18);
			this->Text_RightTyreAngle_Rad->TabIndex = 4;
			this->Text_RightTyreAngle_Rad->Tag = L"1.000";
			this->Text_RightTyreAngle_Rad->Text = L"rad";
			this->Text_RightTyreAngle_Rad->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			// 
			// CheckBox_TopMost
			// 
			this->CheckBox_TopMost->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->CheckBox_TopMost->AutoSize = true;
			this->CheckBox_TopMost->Font = (gcnew System::Drawing::Font(L"BIZ UDPゴシック", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(128)));
			this->CheckBox_TopMost->Location = System::Drawing::Point(223, 200);
			this->CheckBox_TopMost->Name = L"CheckBox_TopMost";
			this->CheckBox_TopMost->Size = System::Drawing::Size(108, 16);
			this->CheckBox_TopMost->TabIndex = 43;
			this->CheckBox_TopMost->Text = L"常に前面に表示";
			this->CheckBox_TopMost->UseVisualStyleBackColor = true;
			this->CheckBox_TopMost->CheckedChanged += gcnew System::EventHandler(this, &TyreMonitorForm::CheckBox_TopMost_CheckedChanged);
			// 
			// Dumper_Line
			// 
			this->Dumper_Line->Anchor = System::Windows::Forms::AnchorStyles::Bottom;
			this->Dumper_Line->AutoSize = true;
			this->Dumper_Line->Font = (gcnew System::Drawing::Font(L"Arial", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Dumper_Line->ForeColor = System::Drawing::SystemColors::ActiveBorder;
			this->Dumper_Line->Location = System::Drawing::Point(9, 172);
			this->Dumper_Line->Name = L"Dumper_Line";
			this->Dumper_Line->Size = System::Drawing::Size(323, 18);
			this->Dumper_Line->TabIndex = 44;
			this->Dumper_Line->Text = L"___________________________________";
			// 
			// TyreMonitorForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::Window;
			this->ClientSize = System::Drawing::Size(341, 224);
			this->Controls->Add(this->CheckBox_TopMost);
			this->Controls->Add(this->Text_RightTyreAngle_Rad);
			this->Controls->Add(this->Text_LeftTyreAngle_Rad);
			this->Controls->Add(this->Text_RightTyreAngle_Deg);
			this->Controls->Add(this->Text_LeftTyreAngle_Deg);
			this->Controls->Add(this->TyreImageHolder);
			this->Controls->Add(this->Dumper_Line);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MaximumSize = System::Drawing::Size(357, 263);
			this->MinimumSize = System::Drawing::Size(357, 263);
			this->Name = L"TyreMonitorForm";
			this->Text = L"TyreMonitor";
			this->Load += gcnew System::EventHandler(this, &TyreMonitorForm::TyreMonitorForm_Load);
			this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &TyreMonitorForm::TyreMonitorForm_Paint);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->TyreImageHolder))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void TyreMonitorForm_Load(System::Object^  sender, System::EventArgs^  e) {
		this->SetStyle(ControlStyles::Opaque, true);
		this->SetStyle(ControlStyles::DoubleBuffer, true);
		this->SetStyle(ControlStyles::UserPaint, true);
		this->SetStyle(ControlStyles::AllPaintingInWmPaint, true);
		TopMost = false;
		CheckBox_TopMost->CheckState = CheckState::Unchecked;
	}

	private: System::Void TickTimer_Tick(System::Object^  sender, System::EventArgs^  e) {
		if (leftTyreAngle) {
			Text_LeftTyreAngle_Rad->Text = (*leftTyreAngle).ToString("0.0000 rad");
			Text_LeftTyreAngle_Deg->Text = rad2deg(*leftTyreAngle).ToString("0.000 deg");
		}
		if (rightTyreAngle) {
			Text_RightTyreAngle_Rad->Text = (*rightTyreAngle).ToString("0.0000 rad");
			Text_RightTyreAngle_Deg->Text = rad2deg(*rightTyreAngle).ToString("0.000 deg");
		}

		this->Invalidate();//Paintイベントを発生させる
	}

	private: System::Void TyreMonitorForm_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
		e->Graphics->Clear(this->BackColor);

		if (leftTyreAngle) {
			DrawImage(e, TyreImageHolder->Image, 80, 110, rad2deg(*leftTyreAngle), 0.5f);
		}

		if (rightTyreAngle) {
			DrawImage(e, TyreImageHolder->Image, 260, 110, rad2deg(*rightTyreAngle), 0.5f);
		}
	}

	private: float rad2deg(float v) {
		return (float)(v * 180 / Math::PI);
	}

	private: System::Void DrawImage(System::Windows::Forms::PaintEventArgs^  e, Image ^image, int x, int y, float rotate, float zoom)
	{
		if (!image) {
			return;
		}
		e->Graphics->ResetTransform();
		e->Graphics->ScaleTransform(zoom, zoom);
		e->Graphics->RotateTransform(rotate, System::Drawing::Drawing2D::MatrixOrder::Append);
		e->Graphics->TranslateTransform((float)x, (float)y, System::Drawing::Drawing2D::MatrixOrder::Append);
		e->Graphics->DrawImage(image, -image->Width / 2, -image->Height / 2);
	}

	private: System::Void CheckBox_TopMost_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
		TopMost = CheckBox_TopMost->CheckState == CheckState::Checked;
	}
};
}
