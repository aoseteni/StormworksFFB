#pragma once

#include <Windows.h>
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <msclr/marshal_cppstd.h>


namespace StormworksFFB {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// FFBMonitorForm の概要
	/// </summary>
	public ref class FFBMonitorForm : public System::Windows::Forms::Form
	{
	public:
		FFBMonitorForm(void)
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
		~FFBMonitorForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::ProgressBar^  Bar_MovementForceMinus;
	private: System::Windows::Forms::ProgressBar^  Bar_MovementForcePlus;
	protected:


	private: System::Windows::Forms::Label^  Text_Movement_Force;
	private: System::Windows::Forms::ProgressBar^  Bar_TotalFrictionMinus;
	private: System::Windows::Forms::ProgressBar^  Bar_TotalFrictionPlus;

	protected:

	protected:




	private: System::Windows::Forms::Label^  Text_Total_Friction;
	private: System::Windows::Forms::ProgressBar^  Bar_CenterFrictionMinus;
	private: System::Windows::Forms::ProgressBar^  Bar_CenterFrictionPlus;



	private: System::Windows::Forms::Label^  Text_Center_Friction;
	private: System::Windows::Forms::ProgressBar^  Bar_StaticFrictionMinus;
	private: System::Windows::Forms::ProgressBar^  Bar_StaticFrictionPlus;



	private: System::Windows::Forms::Label^  Text_Static_Friction;

	private: System::Windows::Forms::CheckBox^  CheckBox_TopMost;
	private: System::Windows::Forms::Label^  Value_Movement_Force;
	private: System::Windows::Forms::Label^  Value_Total_Friction;


	private: System::Windows::Forms::Label^  Constant_Force_Line;
	private: System::Windows::Forms::Label^  Value_Center_Friction;
	private: System::Windows::Forms::Label^  Value_Static_Friction;



	private: System::Windows::Forms::Label^  Friction_Line;


	private: System::Windows::Forms::Timer^  TickTimer;
	private: System::Windows::Forms::CheckBox^  CheckBox_Scaling;
	private: System::Windows::Forms::ToolTip^  toolTip1;

	private: System::Windows::Forms::Label^  Value_Total_Direction_Force;

	private: System::Windows::Forms::ProgressBar^  Bar_TotalDirectionForceMinus;
	private: System::Windows::Forms::ProgressBar^  Bar_TotalDirectionForcePlus;


	private: System::Windows::Forms::Label^  Text_Total_Direction_Force;



	private: System::Windows::Forms::Label^  Value_Rotate_Force;
	private: System::Windows::Forms::ProgressBar^  Bar_RotateForceMinus;
	private: System::Windows::Forms::ProgressBar^  Bar_RotateForcePlus;
	private: System::Windows::Forms::Label^  Text_Rotate_Force;
	private: System::Windows::Forms::Label^  Value_Grip_Friction;
	private: System::Windows::Forms::ProgressBar^  Bar_GripFrictionMinus;
	private: System::Windows::Forms::ProgressBar^  Bar_GripFrictionPlus;



	private: System::Windows::Forms::Button^  Button_Constant_Force_Details;
	private: System::Windows::Forms::Button^  Button_Friction_Details;

	private: System::Windows::Forms::Label^  Value_Input_Axis;
	private: System::Windows::Forms::ProgressBar^  Bar_InputAxisMinus;
	private: System::Windows::Forms::ProgressBar^  Bar_InputAxisPlus;



	private: System::Windows::Forms::Label^  Text_Input_Axis;
	private: System::Windows::Forms::Label^  Input_Axis_Line;
	private: System::Windows::Forms::Label^  Text_Grip_Friction;


	private:
		std::string *Input_Axis_Name = nullptr;
		LONG *Input_Axis = nullptr;
		LONG *Total_Direction_Force = nullptr;
		LONG *Movement_Force = nullptr;
		LONG *Rotate_Force = nullptr;
		LONG *Total_Friction = nullptr;
		LONG *Grip_Friction = nullptr;
		LONG *Center_Friction = nullptr;
		LONG *Static_Friction = nullptr;
		LONG *MaxForce = nullptr;
				
	public: System::Void SetData(
		std::string *FFBMonitor_Input_Axis_Name_,
		LONG *FFBMonitor_Input_Axis_, 
		LONG *FFBMonitor_Total_Direction_Force_,
		LONG *FFBMonitor_Movement_Force_,
		LONG *FFBMonitor_Rotate_Force_,
		LONG *FFBMonitor_Total_Friction_,
		LONG *FFBMonitor_Grip_Friction_,
		LONG *FFBMonitor_Center_Friction_,
		LONG *FFBMonitor_Static_Friction_,
		LONG *FFBMonitor_MaxForce_
	) {
		Input_Axis_Name = FFBMonitor_Input_Axis_Name_;
		Input_Axis = FFBMonitor_Input_Axis_;
		Total_Direction_Force = FFBMonitor_Total_Direction_Force_;
		Movement_Force = FFBMonitor_Movement_Force_;
		Rotate_Force = FFBMonitor_Rotate_Force_;
		Total_Friction = FFBMonitor_Total_Friction_;
		Grip_Friction = FFBMonitor_Grip_Friction_;
		Center_Friction = FFBMonitor_Center_Friction_;
		Static_Friction = FFBMonitor_Static_Friction_;
		MaxForce = FFBMonitor_MaxForce_;
	}
	private: System::ComponentModel::IContainer^  components;
	public:

	private:
		/// <summary>
		/// 必要なデザイナー変数です。
		/// </summary>
		bool constantForceDetails = false;
		bool frictionForceDetails = false;


#pragma region Windows Form Designer generated code
		/// <summary>
		/// デザイナー サポートに必要なメソッドです。このメソッドの内容を
		/// コード エディターで変更しないでください。
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(FFBMonitorForm::typeid));
			this->Bar_MovementForceMinus = (gcnew System::Windows::Forms::ProgressBar());
			this->Bar_MovementForcePlus = (gcnew System::Windows::Forms::ProgressBar());
			this->Text_Movement_Force = (gcnew System::Windows::Forms::Label());
			this->Bar_TotalFrictionMinus = (gcnew System::Windows::Forms::ProgressBar());
			this->Bar_TotalFrictionPlus = (gcnew System::Windows::Forms::ProgressBar());
			this->Text_Total_Friction = (gcnew System::Windows::Forms::Label());
			this->Bar_CenterFrictionMinus = (gcnew System::Windows::Forms::ProgressBar());
			this->Bar_CenterFrictionPlus = (gcnew System::Windows::Forms::ProgressBar());
			this->Text_Center_Friction = (gcnew System::Windows::Forms::Label());
			this->Bar_StaticFrictionMinus = (gcnew System::Windows::Forms::ProgressBar());
			this->Bar_StaticFrictionPlus = (gcnew System::Windows::Forms::ProgressBar());
			this->Text_Static_Friction = (gcnew System::Windows::Forms::Label());
			this->CheckBox_TopMost = (gcnew System::Windows::Forms::CheckBox());
			this->Value_Movement_Force = (gcnew System::Windows::Forms::Label());
			this->Value_Total_Friction = (gcnew System::Windows::Forms::Label());
			this->Constant_Force_Line = (gcnew System::Windows::Forms::Label());
			this->Value_Center_Friction = (gcnew System::Windows::Forms::Label());
			this->Value_Static_Friction = (gcnew System::Windows::Forms::Label());
			this->Friction_Line = (gcnew System::Windows::Forms::Label());
			this->TickTimer = (gcnew System::Windows::Forms::Timer(this->components));
			this->CheckBox_Scaling = (gcnew System::Windows::Forms::CheckBox());
			this->toolTip1 = (gcnew System::Windows::Forms::ToolTip(this->components));
			this->Value_Total_Direction_Force = (gcnew System::Windows::Forms::Label());
			this->Text_Total_Direction_Force = (gcnew System::Windows::Forms::Label());
			this->Value_Rotate_Force = (gcnew System::Windows::Forms::Label());
			this->Text_Rotate_Force = (gcnew System::Windows::Forms::Label());
			this->Value_Grip_Friction = (gcnew System::Windows::Forms::Label());
			this->Text_Grip_Friction = (gcnew System::Windows::Forms::Label());
			this->Value_Input_Axis = (gcnew System::Windows::Forms::Label());
			this->Text_Input_Axis = (gcnew System::Windows::Forms::Label());
			this->Bar_TotalDirectionForceMinus = (gcnew System::Windows::Forms::ProgressBar());
			this->Bar_TotalDirectionForcePlus = (gcnew System::Windows::Forms::ProgressBar());
			this->Bar_RotateForceMinus = (gcnew System::Windows::Forms::ProgressBar());
			this->Bar_RotateForcePlus = (gcnew System::Windows::Forms::ProgressBar());
			this->Bar_GripFrictionMinus = (gcnew System::Windows::Forms::ProgressBar());
			this->Bar_GripFrictionPlus = (gcnew System::Windows::Forms::ProgressBar());
			this->Button_Constant_Force_Details = (gcnew System::Windows::Forms::Button());
			this->Button_Friction_Details = (gcnew System::Windows::Forms::Button());
			this->Bar_InputAxisMinus = (gcnew System::Windows::Forms::ProgressBar());
			this->Bar_InputAxisPlus = (gcnew System::Windows::Forms::ProgressBar());
			this->Input_Axis_Line = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// Bar_MovementForceMinus
			// 
			this->Bar_MovementForceMinus->Location = System::Drawing::Point(12, 135);
			this->Bar_MovementForceMinus->Maximum = 10000;
			this->Bar_MovementForceMinus->Name = L"Bar_MovementForceMinus";
			this->Bar_MovementForceMinus->RightToLeft = System::Windows::Forms::RightToLeft::Yes;
			this->Bar_MovementForceMinus->RightToLeftLayout = true;
			this->Bar_MovementForceMinus->Size = System::Drawing::Size(158, 10);
			this->Bar_MovementForceMinus->Step = 10000;
			this->Bar_MovementForceMinus->TabIndex = 26;
			// 
			// Bar_MovementForcePlus
			// 
			this->Bar_MovementForcePlus->Location = System::Drawing::Point(170, 135);
			this->Bar_MovementForcePlus->Maximum = 10000;
			this->Bar_MovementForcePlus->Name = L"Bar_MovementForcePlus";
			this->Bar_MovementForcePlus->Size = System::Drawing::Size(158, 10);
			this->Bar_MovementForcePlus->Step = 10000;
			this->Bar_MovementForcePlus->TabIndex = 25;
			// 
			// Text_Movement_Force
			// 
			this->Text_Movement_Force->AutoSize = true;
			this->Text_Movement_Force->Font = (gcnew System::Drawing::Font(L"Arial", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Text_Movement_Force->Location = System::Drawing::Point(12, 110);
			this->Text_Movement_Force->Name = L"Text_Movement_Force";
			this->Text_Movement_Force->Size = System::Drawing::Size(125, 18);
			this->Text_Movement_Force->TabIndex = 24;
			this->Text_Movement_Force->Text = L"Movement Force";
			this->toolTip1->SetToolTip(this->Text_Movement_Force, L"車体進行方向への力の強さを表します");
			// 
			// Bar_TotalFrictionMinus
			// 
			this->Bar_TotalFrictionMinus->Location = System::Drawing::Point(12, 243);
			this->Bar_TotalFrictionMinus->Maximum = 10000;
			this->Bar_TotalFrictionMinus->Name = L"Bar_TotalFrictionMinus";
			this->Bar_TotalFrictionMinus->RightToLeft = System::Windows::Forms::RightToLeft::Yes;
			this->Bar_TotalFrictionMinus->RightToLeftLayout = true;
			this->Bar_TotalFrictionMinus->Size = System::Drawing::Size(158, 10);
			this->Bar_TotalFrictionMinus->Step = 10000;
			this->Bar_TotalFrictionMinus->TabIndex = 29;
			// 
			// Bar_TotalFrictionPlus
			// 
			this->Bar_TotalFrictionPlus->Location = System::Drawing::Point(170, 243);
			this->Bar_TotalFrictionPlus->Maximum = 10000;
			this->Bar_TotalFrictionPlus->Name = L"Bar_TotalFrictionPlus";
			this->Bar_TotalFrictionPlus->Size = System::Drawing::Size(158, 10);
			this->Bar_TotalFrictionPlus->Step = 10000;
			this->Bar_TotalFrictionPlus->TabIndex = 28;
			// 
			// Text_Total_Friction
			// 
			this->Text_Total_Friction->AutoSize = true;
			this->Text_Total_Friction->Font = (gcnew System::Drawing::Font(L"Arial", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Text_Total_Friction->Location = System::Drawing::Point(12, 218);
			this->Text_Total_Friction->Name = L"Text_Total_Friction";
			this->Text_Total_Friction->Size = System::Drawing::Size(96, 18);
			this->Text_Total_Friction->TabIndex = 27;
			this->Text_Total_Friction->Text = L"Total Friction";
			this->toolTip1->SetToolTip(this->Text_Total_Friction, L"現在出力されているフリクションフォースを表します");
			// 
			// Bar_CenterFrictionMinus
			// 
			this->Bar_CenterFrictionMinus->Location = System::Drawing::Point(12, 335);
			this->Bar_CenterFrictionMinus->Maximum = 10000;
			this->Bar_CenterFrictionMinus->Name = L"Bar_CenterFrictionMinus";
			this->Bar_CenterFrictionMinus->RightToLeft = System::Windows::Forms::RightToLeft::Yes;
			this->Bar_CenterFrictionMinus->RightToLeftLayout = true;
			this->Bar_CenterFrictionMinus->Size = System::Drawing::Size(158, 10);
			this->Bar_CenterFrictionMinus->Step = 10000;
			this->Bar_CenterFrictionMinus->TabIndex = 32;
			// 
			// Bar_CenterFrictionPlus
			// 
			this->Bar_CenterFrictionPlus->Location = System::Drawing::Point(170, 335);
			this->Bar_CenterFrictionPlus->Maximum = 10000;
			this->Bar_CenterFrictionPlus->Name = L"Bar_CenterFrictionPlus";
			this->Bar_CenterFrictionPlus->Size = System::Drawing::Size(158, 10);
			this->Bar_CenterFrictionPlus->Step = 10000;
			this->Bar_CenterFrictionPlus->TabIndex = 31;
			// 
			// Text_Center_Friction
			// 
			this->Text_Center_Friction->AutoSize = true;
			this->Text_Center_Friction->Font = (gcnew System::Drawing::Font(L"Arial", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Text_Center_Friction->Location = System::Drawing::Point(12, 310);
			this->Text_Center_Friction->Name = L"Text_Center_Friction";
			this->Text_Center_Friction->Size = System::Drawing::Size(111, 18);
			this->Text_Center_Friction->TabIndex = 30;
			this->Text_Center_Friction->Text = L"Center Friction";
			this->toolTip1->SetToolTip(this->Text_Center_Friction, L"センター付近の摩擦の強さを表します");
			// 
			// Bar_StaticFrictionMinus
			// 
			this->Bar_StaticFrictionMinus->Location = System::Drawing::Point(12, 381);
			this->Bar_StaticFrictionMinus->Maximum = 10000;
			this->Bar_StaticFrictionMinus->Name = L"Bar_StaticFrictionMinus";
			this->Bar_StaticFrictionMinus->RightToLeft = System::Windows::Forms::RightToLeft::Yes;
			this->Bar_StaticFrictionMinus->RightToLeftLayout = true;
			this->Bar_StaticFrictionMinus->Size = System::Drawing::Size(158, 10);
			this->Bar_StaticFrictionMinus->Step = 10000;
			this->Bar_StaticFrictionMinus->TabIndex = 35;
			// 
			// Bar_StaticFrictionPlus
			// 
			this->Bar_StaticFrictionPlus->Location = System::Drawing::Point(170, 381);
			this->Bar_StaticFrictionPlus->Maximum = 10000;
			this->Bar_StaticFrictionPlus->Name = L"Bar_StaticFrictionPlus";
			this->Bar_StaticFrictionPlus->Size = System::Drawing::Size(158, 10);
			this->Bar_StaticFrictionPlus->Step = 10000;
			this->Bar_StaticFrictionPlus->TabIndex = 34;
			// 
			// Text_Static_Friction
			// 
			this->Text_Static_Friction->AutoSize = true;
			this->Text_Static_Friction->Font = (gcnew System::Drawing::Font(L"Arial", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Text_Static_Friction->Location = System::Drawing::Point(12, 356);
			this->Text_Static_Friction->Name = L"Text_Static_Friction";
			this->Text_Static_Friction->Size = System::Drawing::Size(104, 18);
			this->Text_Static_Friction->TabIndex = 33;
			this->Text_Static_Friction->Text = L"Static Friction";
			this->toolTip1->SetToolTip(this->Text_Static_Friction, L"静止時の摩擦の強さを表します");
			// 
			// CheckBox_TopMost
			// 
			this->CheckBox_TopMost->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->CheckBox_TopMost->AutoSize = true;
			this->CheckBox_TopMost->Font = (gcnew System::Drawing::Font(L"BIZ UDPゴシック", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(128)));
			this->CheckBox_TopMost->Location = System::Drawing::Point(223, 413);
			this->CheckBox_TopMost->Name = L"CheckBox_TopMost";
			this->CheckBox_TopMost->Size = System::Drawing::Size(108, 16);
			this->CheckBox_TopMost->TabIndex = 36;
			this->CheckBox_TopMost->Text = L"常に前面に表示";
			this->CheckBox_TopMost->UseVisualStyleBackColor = true;
			this->CheckBox_TopMost->CheckedChanged += gcnew System::EventHandler(this, &FFBMonitorForm::CheckBox_TopMost_CheckedChanged);
			// 
			// Value_Movement_Force
			// 
			this->Value_Movement_Force->Anchor = System::Windows::Forms::AnchorStyles::Top;
			this->Value_Movement_Force->Font = (gcnew System::Drawing::Font(L"Arial", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Value_Movement_Force->Location = System::Drawing::Point(142, 110);
			this->Value_Movement_Force->Name = L"Value_Movement_Force";
			this->Value_Movement_Force->Size = System::Drawing::Size(58, 18);
			this->Value_Movement_Force->TabIndex = 37;
			this->Value_Movement_Force->Text = L"-10000";
			this->Value_Movement_Force->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			this->toolTip1->SetToolTip(this->Value_Movement_Force, L"車体進行方向への力の強さを表します");
			// 
			// Value_Total_Friction
			// 
			this->Value_Total_Friction->Anchor = System::Windows::Forms::AnchorStyles::Top;
			this->Value_Total_Friction->Font = (gcnew System::Drawing::Font(L"Arial", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Value_Total_Friction->Location = System::Drawing::Point(142, 218);
			this->Value_Total_Friction->Name = L"Value_Total_Friction";
			this->Value_Total_Friction->Size = System::Drawing::Size(58, 18);
			this->Value_Total_Friction->TabIndex = 38;
			this->Value_Total_Friction->Text = L"-10000";
			this->Value_Total_Friction->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			this->toolTip1->SetToolTip(this->Value_Total_Friction, L"現在出力されているダンパーフォースを表します");
			// 
			// Constant_Force_Line
			// 
			this->Constant_Force_Line->AutoSize = true;
			this->Constant_Force_Line->Font = (gcnew System::Drawing::Font(L"Arial", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Constant_Force_Line->ForeColor = System::Drawing::SystemColors::ActiveBorder;
			this->Constant_Force_Line->Location = System::Drawing::Point(9, 188);
			this->Constant_Force_Line->Name = L"Constant_Force_Line";
			this->Constant_Force_Line->Size = System::Drawing::Size(323, 18);
			this->Constant_Force_Line->TabIndex = 39;
			this->Constant_Force_Line->Text = L"___________________________________";
			// 
			// Value_Center_Friction
			// 
			this->Value_Center_Friction->Anchor = System::Windows::Forms::AnchorStyles::Top;
			this->Value_Center_Friction->Font = (gcnew System::Drawing::Font(L"Arial", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Value_Center_Friction->Location = System::Drawing::Point(142, 310);
			this->Value_Center_Friction->Name = L"Value_Center_Friction";
			this->Value_Center_Friction->Size = System::Drawing::Size(58, 18);
			this->Value_Center_Friction->TabIndex = 40;
			this->Value_Center_Friction->Text = L"-10000";
			this->Value_Center_Friction->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			this->toolTip1->SetToolTip(this->Value_Center_Friction, L"センター付近の振れを抑えるダンパーフォースの強さを表します");
			// 
			// Value_Static_Friction
			// 
			this->Value_Static_Friction->Anchor = System::Windows::Forms::AnchorStyles::Top;
			this->Value_Static_Friction->Font = (gcnew System::Drawing::Font(L"Arial", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Value_Static_Friction->Location = System::Drawing::Point(142, 356);
			this->Value_Static_Friction->Name = L"Value_Static_Friction";
			this->Value_Static_Friction->Size = System::Drawing::Size(58, 18);
			this->Value_Static_Friction->TabIndex = 41;
			this->Value_Static_Friction->Text = L"-10000";
			this->Value_Static_Friction->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			this->toolTip1->SetToolTip(this->Value_Static_Friction, L"静止時の抵抗の強さを表します");
			// 
			// Friction_Line
			// 
			this->Friction_Line->AutoSize = true;
			this->Friction_Line->Font = (gcnew System::Drawing::Font(L"Arial", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Friction_Line->ForeColor = System::Drawing::SystemColors::ActiveBorder;
			this->Friction_Line->Location = System::Drawing::Point(9, 385);
			this->Friction_Line->Name = L"Friction_Line";
			this->Friction_Line->Size = System::Drawing::Size(323, 18);
			this->Friction_Line->TabIndex = 42;
			this->Friction_Line->Text = L"___________________________________";
			// 
			// TickTimer
			// 
			this->TickTimer->Enabled = true;
			this->TickTimer->Interval = 16;
			this->TickTimer->Tick += gcnew System::EventHandler(this, &FFBMonitorForm::TickTimer_Tick);
			// 
			// CheckBox_Scaling
			// 
			this->CheckBox_Scaling->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->CheckBox_Scaling->AutoSize = true;
			this->CheckBox_Scaling->Font = (gcnew System::Drawing::Font(L"BIZ UDPゴシック", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(128)));
			this->CheckBox_Scaling->Location = System::Drawing::Point(12, 413);
			this->CheckBox_Scaling->Name = L"CheckBox_Scaling";
			this->CheckBox_Scaling->Size = System::Drawing::Size(167, 16);
			this->CheckBox_Scaling->TabIndex = 43;
			this->CheckBox_Scaling->Text = L"MaxForceでスケーリング";
			this->toolTip1->SetToolTip(this->CheckBox_Scaling, L"各ゲージの最大値を\"MaxForce\"に設定します");
			this->CheckBox_Scaling->UseVisualStyleBackColor = true;
			// 
			// toolTip1
			// 
			this->toolTip1->AutomaticDelay = 0;
			// 
			// Value_Total_Direction_Force
			// 
			this->Value_Total_Direction_Force->Anchor = System::Windows::Forms::AnchorStyles::Top;
			this->Value_Total_Direction_Force->Font = (gcnew System::Drawing::Font(L"Arial", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Value_Total_Direction_Force->Location = System::Drawing::Point(142, 64);
			this->Value_Total_Direction_Force->Name = L"Value_Total_Direction_Force";
			this->Value_Total_Direction_Force->Size = System::Drawing::Size(58, 18);
			this->Value_Total_Direction_Force->TabIndex = 47;
			this->Value_Total_Direction_Force->Text = L"-10000";
			this->Value_Total_Direction_Force->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			this->toolTip1->SetToolTip(this->Value_Total_Direction_Force, L"現在出力されているコンスタントフォースを表します");
			// 
			// Text_Total_Direction_Force
			// 
			this->Text_Total_Direction_Force->AutoSize = true;
			this->Text_Total_Direction_Force->Font = (gcnew System::Drawing::Font(L"Arial", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Text_Total_Direction_Force->Location = System::Drawing::Point(12, 64);
			this->Text_Total_Direction_Force->Name = L"Text_Total_Direction_Force";
			this->Text_Total_Direction_Force->Size = System::Drawing::Size(113, 18);
			this->Text_Total_Direction_Force->TabIndex = 44;
			this->Text_Total_Direction_Force->Text = L"Total Dir. Force";
			this->toolTip1->SetToolTip(this->Text_Total_Direction_Force, L"現在出力されているコンスタントフォースを表します");
			// 
			// Value_Rotate_Force
			// 
			this->Value_Rotate_Force->Anchor = System::Windows::Forms::AnchorStyles::Top;
			this->Value_Rotate_Force->Font = (gcnew System::Drawing::Font(L"Arial", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Value_Rotate_Force->Location = System::Drawing::Point(142, 156);
			this->Value_Rotate_Force->Name = L"Value_Rotate_Force";
			this->Value_Rotate_Force->Size = System::Drawing::Size(58, 18);
			this->Value_Rotate_Force->TabIndex = 51;
			this->Value_Rotate_Force->Text = L"-10000";
			this->Value_Rotate_Force->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			this->toolTip1->SetToolTip(this->Value_Rotate_Force, L"車体回転時の力の強さを表します");
			// 
			// Text_Rotate_Force
			// 
			this->Text_Rotate_Force->AutoSize = true;
			this->Text_Rotate_Force->Font = (gcnew System::Drawing::Font(L"Arial", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Text_Rotate_Force->Location = System::Drawing::Point(12, 156);
			this->Text_Rotate_Force->Name = L"Text_Rotate_Force";
			this->Text_Rotate_Force->Size = System::Drawing::Size(99, 18);
			this->Text_Rotate_Force->TabIndex = 48;
			this->Text_Rotate_Force->Text = L"Rotate Force";
			this->toolTip1->SetToolTip(this->Text_Rotate_Force, L"車体回転時の力の強さを表します");
			// 
			// Value_Grip_Friction
			// 
			this->Value_Grip_Friction->Anchor = System::Windows::Forms::AnchorStyles::Top;
			this->Value_Grip_Friction->Font = (gcnew System::Drawing::Font(L"Arial", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Value_Grip_Friction->Location = System::Drawing::Point(141, 264);
			this->Value_Grip_Friction->Name = L"Value_Grip_Friction";
			this->Value_Grip_Friction->Size = System::Drawing::Size(58, 18);
			this->Value_Grip_Friction->TabIndex = 55;
			this->Value_Grip_Friction->Text = L"-10000";
			this->Value_Grip_Friction->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			this->toolTip1->SetToolTip(this->Value_Grip_Friction, L"タイヤ接地時の抵抗の強さを表します");
			// 
			// Text_Grip_Friction
			// 
			this->Text_Grip_Friction->AutoSize = true;
			this->Text_Grip_Friction->Font = (gcnew System::Drawing::Font(L"Arial", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Text_Grip_Friction->Location = System::Drawing::Point(12, 264);
			this->Text_Grip_Friction->Name = L"Text_Grip_Friction";
			this->Text_Grip_Friction->Size = System::Drawing::Size(94, 18);
			this->Text_Grip_Friction->TabIndex = 52;
			this->Text_Grip_Friction->Text = L"Grip Friction";
			this->toolTip1->SetToolTip(this->Text_Grip_Friction, L"タイヤ接地時の摩擦の強さを表します");
			// 
			// Value_Input_Axis
			// 
			this->Value_Input_Axis->Anchor = System::Windows::Forms::AnchorStyles::Top;
			this->Value_Input_Axis->Font = (gcnew System::Drawing::Font(L"Arial", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Value_Input_Axis->Location = System::Drawing::Point(142, 8);
			this->Value_Input_Axis->Name = L"Value_Input_Axis";
			this->Value_Input_Axis->Size = System::Drawing::Size(58, 18);
			this->Value_Input_Axis->TabIndex = 61;
			this->Value_Input_Axis->Text = L"-10000";
			this->Value_Input_Axis->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			this->toolTip1->SetToolTip(this->Value_Input_Axis, L"FFBの対象となる軸の入力値を表します");
			// 
			// Text_Input_Axis
			// 
			this->Text_Input_Axis->AutoSize = true;
			this->Text_Input_Axis->Font = (gcnew System::Drawing::Font(L"Arial", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Text_Input_Axis->Location = System::Drawing::Point(12, 8);
			this->Text_Input_Axis->Name = L"Text_Input_Axis";
			this->Text_Input_Axis->Size = System::Drawing::Size(58, 18);
			this->Text_Input_Axis->TabIndex = 58;
			this->Text_Input_Axis->Text = L"Input lX";
			this->toolTip1->SetToolTip(this->Text_Input_Axis, L"FFBを出力する軸を表します");
			// 
			// Bar_TotalDirectionForceMinus
			// 
			this->Bar_TotalDirectionForceMinus->Location = System::Drawing::Point(12, 89);
			this->Bar_TotalDirectionForceMinus->Maximum = 10000;
			this->Bar_TotalDirectionForceMinus->Name = L"Bar_TotalDirectionForceMinus";
			this->Bar_TotalDirectionForceMinus->RightToLeft = System::Windows::Forms::RightToLeft::Yes;
			this->Bar_TotalDirectionForceMinus->RightToLeftLayout = true;
			this->Bar_TotalDirectionForceMinus->Size = System::Drawing::Size(158, 10);
			this->Bar_TotalDirectionForceMinus->Step = 10000;
			this->Bar_TotalDirectionForceMinus->TabIndex = 46;
			// 
			// Bar_TotalDirectionForcePlus
			// 
			this->Bar_TotalDirectionForcePlus->Location = System::Drawing::Point(170, 89);
			this->Bar_TotalDirectionForcePlus->Maximum = 10000;
			this->Bar_TotalDirectionForcePlus->Name = L"Bar_TotalDirectionForcePlus";
			this->Bar_TotalDirectionForcePlus->Size = System::Drawing::Size(158, 10);
			this->Bar_TotalDirectionForcePlus->Step = 10000;
			this->Bar_TotalDirectionForcePlus->TabIndex = 45;
			// 
			// Bar_RotateForceMinus
			// 
			this->Bar_RotateForceMinus->Location = System::Drawing::Point(12, 181);
			this->Bar_RotateForceMinus->Maximum = 10000;
			this->Bar_RotateForceMinus->Name = L"Bar_RotateForceMinus";
			this->Bar_RotateForceMinus->RightToLeft = System::Windows::Forms::RightToLeft::Yes;
			this->Bar_RotateForceMinus->RightToLeftLayout = true;
			this->Bar_RotateForceMinus->Size = System::Drawing::Size(158, 10);
			this->Bar_RotateForceMinus->Step = 10000;
			this->Bar_RotateForceMinus->TabIndex = 50;
			// 
			// Bar_RotateForcePlus
			// 
			this->Bar_RotateForcePlus->Location = System::Drawing::Point(170, 181);
			this->Bar_RotateForcePlus->Maximum = 10000;
			this->Bar_RotateForcePlus->Name = L"Bar_RotateForcePlus";
			this->Bar_RotateForcePlus->Size = System::Drawing::Size(158, 10);
			this->Bar_RotateForcePlus->Step = 10000;
			this->Bar_RotateForcePlus->TabIndex = 49;
			// 
			// Bar_GripFrictionMinus
			// 
			this->Bar_GripFrictionMinus->Location = System::Drawing::Point(12, 289);
			this->Bar_GripFrictionMinus->Maximum = 10000;
			this->Bar_GripFrictionMinus->Name = L"Bar_GripFrictionMinus";
			this->Bar_GripFrictionMinus->RightToLeft = System::Windows::Forms::RightToLeft::Yes;
			this->Bar_GripFrictionMinus->RightToLeftLayout = true;
			this->Bar_GripFrictionMinus->Size = System::Drawing::Size(158, 10);
			this->Bar_GripFrictionMinus->Step = 10000;
			this->Bar_GripFrictionMinus->TabIndex = 54;
			// 
			// Bar_GripFrictionPlus
			// 
			this->Bar_GripFrictionPlus->Location = System::Drawing::Point(170, 289);
			this->Bar_GripFrictionPlus->Maximum = 10000;
			this->Bar_GripFrictionPlus->Name = L"Bar_GripFrictionPlus";
			this->Bar_GripFrictionPlus->Size = System::Drawing::Size(158, 10);
			this->Bar_GripFrictionPlus->Step = 10000;
			this->Bar_GripFrictionPlus->TabIndex = 53;
			// 
			// Button_Constant_Force_Details
			// 
			this->Button_Constant_Force_Details->Font = (gcnew System::Drawing::Font(L"BIZ UDPゴシック", 9, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(128)));
			this->Button_Constant_Force_Details->Location = System::Drawing::Point(259, 61);
			this->Button_Constant_Force_Details->Name = L"Button_Constant_Force_Details";
			this->Button_Constant_Force_Details->Size = System::Drawing::Size(70, 23);
			this->Button_Constant_Force_Details->TabIndex = 56;
			this->Button_Constant_Force_Details->Text = L"簡易表示";
			this->Button_Constant_Force_Details->UseVisualStyleBackColor = true;
			this->Button_Constant_Force_Details->Click += gcnew System::EventHandler(this, &FFBMonitorForm::Button_Constant_Force_Details_Click);
			// 
			// Button_Friction_Details
			// 
			this->Button_Friction_Details->Font = (gcnew System::Drawing::Font(L"BIZ UDPゴシック", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(128)));
			this->Button_Friction_Details->Location = System::Drawing::Point(259, 215);
			this->Button_Friction_Details->Name = L"Button_Friction_Details";
			this->Button_Friction_Details->Size = System::Drawing::Size(70, 23);
			this->Button_Friction_Details->TabIndex = 57;
			this->Button_Friction_Details->Text = L"詳細表示";
			this->Button_Friction_Details->UseVisualStyleBackColor = true;
			this->Button_Friction_Details->Click += gcnew System::EventHandler(this, &FFBMonitorForm::Button_Friction_Details_Click);
			// 
			// Bar_InputAxisMinus
			// 
			this->Bar_InputAxisMinus->Location = System::Drawing::Point(12, 33);
			this->Bar_InputAxisMinus->Maximum = 10000;
			this->Bar_InputAxisMinus->Name = L"Bar_InputAxisMinus";
			this->Bar_InputAxisMinus->RightToLeft = System::Windows::Forms::RightToLeft::Yes;
			this->Bar_InputAxisMinus->RightToLeftLayout = true;
			this->Bar_InputAxisMinus->Size = System::Drawing::Size(158, 10);
			this->Bar_InputAxisMinus->Step = 10000;
			this->Bar_InputAxisMinus->TabIndex = 60;
			// 
			// Bar_InputAxisPlus
			// 
			this->Bar_InputAxisPlus->Location = System::Drawing::Point(170, 33);
			this->Bar_InputAxisPlus->Maximum = 10000;
			this->Bar_InputAxisPlus->Name = L"Bar_InputAxisPlus";
			this->Bar_InputAxisPlus->Size = System::Drawing::Size(158, 10);
			this->Bar_InputAxisPlus->Step = 10000;
			this->Bar_InputAxisPlus->TabIndex = 59;
			// 
			// Input_Axis_Line
			// 
			this->Input_Axis_Line->AutoSize = true;
			this->Input_Axis_Line->Font = (gcnew System::Drawing::Font(L"Arial", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Input_Axis_Line->ForeColor = System::Drawing::SystemColors::ActiveBorder;
			this->Input_Axis_Line->Location = System::Drawing::Point(9, 37);
			this->Input_Axis_Line->Name = L"Input_Axis_Line";
			this->Input_Axis_Line->Size = System::Drawing::Size(323, 18);
			this->Input_Axis_Line->TabIndex = 62;
			this->Input_Axis_Line->Text = L"___________________________________";
			// 
			// FFBMonitorForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::Window;
			this->ClientSize = System::Drawing::Size(341, 437);
			this->Controls->Add(this->Value_Input_Axis);
			this->Controls->Add(this->Bar_InputAxisMinus);
			this->Controls->Add(this->Bar_InputAxisPlus);
			this->Controls->Add(this->Text_Input_Axis);
			this->Controls->Add(this->Input_Axis_Line);
			this->Controls->Add(this->Button_Friction_Details);
			this->Controls->Add(this->Button_Constant_Force_Details);
			this->Controls->Add(this->Value_Grip_Friction);
			this->Controls->Add(this->Bar_GripFrictionMinus);
			this->Controls->Add(this->Bar_GripFrictionPlus);
			this->Controls->Add(this->Text_Grip_Friction);
			this->Controls->Add(this->Value_Rotate_Force);
			this->Controls->Add(this->Bar_RotateForceMinus);
			this->Controls->Add(this->Bar_RotateForcePlus);
			this->Controls->Add(this->Text_Rotate_Force);
			this->Controls->Add(this->Value_Total_Direction_Force);
			this->Controls->Add(this->Bar_TotalDirectionForceMinus);
			this->Controls->Add(this->Bar_TotalDirectionForcePlus);
			this->Controls->Add(this->Text_Total_Direction_Force);
			this->Controls->Add(this->CheckBox_Scaling);
			this->Controls->Add(this->Value_Static_Friction);
			this->Controls->Add(this->Value_Center_Friction);
			this->Controls->Add(this->Value_Total_Friction);
			this->Controls->Add(this->Value_Movement_Force);
			this->Controls->Add(this->CheckBox_TopMost);
			this->Controls->Add(this->Bar_StaticFrictionMinus);
			this->Controls->Add(this->Bar_StaticFrictionPlus);
			this->Controls->Add(this->Text_Static_Friction);
			this->Controls->Add(this->Bar_CenterFrictionMinus);
			this->Controls->Add(this->Bar_CenterFrictionPlus);
			this->Controls->Add(this->Text_Center_Friction);
			this->Controls->Add(this->Bar_TotalFrictionMinus);
			this->Controls->Add(this->Bar_TotalFrictionPlus);
			this->Controls->Add(this->Text_Total_Friction);
			this->Controls->Add(this->Bar_MovementForceMinus);
			this->Controls->Add(this->Bar_MovementForcePlus);
			this->Controls->Add(this->Text_Movement_Force);
			this->Controls->Add(this->Constant_Force_Line);
			this->Controls->Add(this->Friction_Line);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MaximizeBox = false;
			this->MaximumSize = System::Drawing::Size(357, 1000);
			this->MinimumSize = System::Drawing::Size(357, 39);
			this->Name = L"FFBMonitorForm";
			this->Text = L"FFBMonitor";
			this->Load += gcnew System::EventHandler(this, &FFBMonitorForm::FFBMonitorForm_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private: System::Void FFBMonitorForm_Load(System::Object^  sender, System::EventArgs^  e) {
		SetDetails(constantForceDetails, frictionForceDetails);
	}

	private: System::Void CheckBox_TopMost_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
		TopMost = CheckBox_TopMost->CheckState == CheckState::Checked;
	}

	private: System::Void TickTimer_Tick(System::Object^  sender, System::EventArgs^  e) {
		//スケーリング
		if (CheckBox_Scaling->Checked) {
			if (!MaxForce) {
				System::String^ message = "MaxForceパラメーターを取得できませんでした";
				System::String^ title = "MaxForceでスケーリング";
				System::Windows::Forms::MessageBox::Show(message, title, MessageBoxButtons::OK, MessageBoxIcon::Warning);
				CheckBox_Scaling->Checked = false;
			}
			else {
				LONG max_ = *MaxForce;
				Bar_TotalDirectionForcePlus->Maximum = max_;
				Bar_TotalDirectionForceMinus->Maximum = max_;
				Bar_RotateForcePlus->Maximum = max_;
				Bar_RotateForceMinus->Maximum = max_;
				Bar_MovementForcePlus->Maximum = max_;
				Bar_MovementForceMinus->Maximum = max_;
				Bar_TotalFrictionPlus->Maximum = max_;
				Bar_TotalFrictionMinus->Maximum = max_;
				Bar_GripFrictionPlus->Maximum = max_;
				Bar_GripFrictionMinus->Maximum = max_;
				Bar_CenterFrictionPlus->Maximum = max_;
				Bar_CenterFrictionMinus->Maximum = max_;
				Bar_StaticFrictionPlus->Maximum = max_;
				Bar_StaticFrictionMinus->Maximum = max_;
			}
		}
		else {
			LONG max_ = 10000;
			Bar_TotalDirectionForcePlus->Maximum = max_;
			Bar_TotalDirectionForceMinus->Maximum = max_;
			Bar_RotateForcePlus->Maximum = max_;
			Bar_RotateForceMinus->Maximum = max_;
			Bar_MovementForcePlus->Maximum = max_;
			Bar_MovementForceMinus->Maximum = max_;
			Bar_TotalFrictionPlus->Maximum = max_;
			Bar_TotalFrictionMinus->Maximum = max_;
			Bar_GripFrictionPlus->Maximum = max_;
			Bar_GripFrictionMinus->Maximum = max_;
			Bar_CenterFrictionPlus->Maximum = max_;
			Bar_CenterFrictionMinus->Maximum = max_;
			Bar_StaticFrictionPlus->Maximum = max_;
			Bar_StaticFrictionMinus->Maximum = max_;
		}

		//軸表記の更新
		if (Input_Axis_Name) {
			Text_Input_Axis->Text = "Input " + msclr::interop::marshal_as<System::String^>(*Input_Axis_Name);
		}

		if (Input_Axis){
			ProgressBar_SpringGauge(Bar_InputAxisMinus, Bar_InputAxisPlus, Value_Input_Axis, *Input_Axis);
		}

		if (Total_Direction_Force) {
			ProgressBar_SpringGauge(Bar_TotalDirectionForceMinus, Bar_TotalDirectionForcePlus, Value_Total_Direction_Force, *Total_Direction_Force);
		}

		if (Movement_Force) {
			ProgressBar_SpringGauge(Bar_MovementForceMinus, Bar_MovementForcePlus, Value_Movement_Force, *Movement_Force);
		}

		if (Rotate_Force) {
			ProgressBar_SpringGauge(Bar_RotateForceMinus, Bar_RotateForcePlus, Value_Rotate_Force, *Rotate_Force);
		}

		if (Total_Friction) {
			ProgressBar_FrictionGauge(Bar_TotalFrictionMinus, Bar_TotalFrictionPlus, Value_Total_Friction, *Total_Friction);
		}

		if (Grip_Friction) {
			ProgressBar_FrictionGauge(Bar_GripFrictionMinus, Bar_GripFrictionPlus, Value_Grip_Friction, *Grip_Friction);
		}
			 
		if (Center_Friction) {
			ProgressBar_FrictionGauge(Bar_CenterFrictionMinus, Bar_CenterFrictionPlus, Value_Center_Friction, *Center_Friction);
		}

		if (Static_Friction) {
			ProgressBar_FrictionGauge(Bar_StaticFrictionMinus, Bar_StaticFrictionPlus, Value_Static_Friction, *Static_Friction);
		}
	}

	private: System::Void SetLocation_Input_Axis(Point location) {
		Text_Input_Axis->Location = Point(location.X, location.Y + 3);
		Value_Input_Axis->Location = Point(location.X + 130, location.Y + 3);
		Bar_InputAxisMinus->Location = Point(location.X, location.Y + 28);
		Bar_InputAxisPlus->Location = Point(location.X + 158, location.Y + 28);
	}

	private: System::Void SetVisible_Input_Axis(bool visible) {
		Text_Input_Axis->Visible = visible;
		Value_Input_Axis->Visible = visible;
		Bar_InputAxisMinus->Visible = visible;
		Bar_InputAxisPlus->Visible = visible;
	}

	private: System::Void SetLocation_Input_Axis_Line(Point location) {
		Input_Axis_Line->Location = location;
	}

	private: System::Void SetLocation_Total_Direction_Force(Point location) {
		Text_Total_Direction_Force->Location = Point(location.X, location.Y + 3);
		Value_Total_Direction_Force->Location = Point(location.X + 130, location.Y + 3);
		Button_Constant_Force_Details->Location = Point(location.X + 247, location.Y);
		Bar_TotalDirectionForceMinus->Location = Point(location.X, location.Y + 28);
		Bar_TotalDirectionForcePlus->Location = Point(location.X + 158, location.Y + 28);
	}

	private: System::Void SetVisible_Total_Direction_Force(bool visible) {
		Text_Total_Direction_Force->Visible = visible;
		Value_Total_Direction_Force->Visible = visible;
		Button_Constant_Force_Details->Visible = visible;
		Bar_TotalDirectionForceMinus->Visible = visible;
		Bar_TotalDirectionForcePlus->Visible = visible;
	}

	private: System::Void SetLocation_Movement_Force(Point location) {
		Text_Movement_Force->Location = Point(location.X, location.Y + 3);
		Value_Movement_Force->Location = Point(location.X + 130, location.Y + 3);
		Bar_MovementForceMinus->Location = Point(location.X, location.Y + 28);
		Bar_MovementForcePlus->Location = Point(location.X + 158, location.Y + 28);
	}

	private: System::Void SetVisible_Movement_Force(bool visible) {
		Text_Movement_Force->Visible = visible;
		Value_Movement_Force->Visible = visible;
		Bar_MovementForceMinus->Visible = visible;
		Bar_MovementForcePlus->Visible = visible;
	}

	private: System::Void SetLocation_Rotate_Force(Point location) {
		Text_Rotate_Force->Location = Point(location.X, location.Y + 3);
		Value_Rotate_Force->Location = Point(location.X + 130, location.Y + 3);
		Bar_RotateForceMinus->Location = Point(location.X, location.Y + 28);
		Bar_RotateForcePlus->Location = Point(location.X + 158, location.Y + 28);
	}

	private: System::Void SetVisible_Rotate_Force(bool visible) {
		Text_Rotate_Force->Visible = visible;
		Value_Rotate_Force->Visible = visible;
		Bar_RotateForceMinus->Visible = visible;
		Bar_RotateForcePlus->Visible = visible;
	}

	private: System::Void SetLocation_Constant_Force_Line(Point location) {
		Constant_Force_Line->Location = location;
	}

	private: System::Void SetLocation_Total_Friction(Point location) {
		Text_Total_Friction->Location = Point(location.X, location.Y + 3);
		Value_Total_Friction->Location = Point(location.X + 130, location.Y + 3);
		Button_Friction_Details->Location = Point(location.X + 247, location.Y);;
		Bar_TotalFrictionMinus->Location = Point(location.X, location.Y + 28);
		Bar_TotalFrictionPlus->Location = Point(location.X + 158, location.Y + 28);
	}

	private: System::Void SetVisible_Total_Friction(bool visible) {
		Text_Total_Friction->Visible = visible;
		Value_Total_Friction->Visible = visible;
		Button_Friction_Details->Visible = visible;
		Bar_TotalFrictionMinus->Visible = visible;
		Bar_TotalFrictionPlus->Visible = visible;
	}

	private: System::Void SetLocation_Grip_Friction(Point location) {
		Text_Grip_Friction->Location = Point(location.X, location.Y + 3);
		Value_Grip_Friction->Location = Point(location.X + 130, location.Y + 3);
		Bar_GripFrictionMinus->Location = Point(location.X, location.Y + 28);
		Bar_GripFrictionPlus->Location = Point(location.X + 158, location.Y + 28);
	}

	private: System::Void SetVisible_Grip_Friction(bool visible) {
		Text_Grip_Friction->Visible = visible;
		Value_Grip_Friction->Visible = visible;
		Bar_GripFrictionMinus->Visible = visible;
		Bar_GripFrictionPlus->Visible = visible;
	}

	private: System::Void SetLocation_Center_Friction(Point location) {
		Text_Center_Friction->Location = Point(location.X, location.Y + 3);
		Value_Center_Friction->Location = Point(location.X + 130, location.Y + 3);
		Bar_CenterFrictionMinus->Location = Point(location.X, location.Y + 28);
		Bar_CenterFrictionPlus->Location = Point(location.X + 158, location.Y + 28);
	}

	private: System::Void SetVisible_Center_Friction(bool visible) {
		Text_Center_Friction->Visible = visible;
		Value_Center_Friction->Visible = visible;
		Bar_CenterFrictionMinus->Visible = visible;
		Bar_CenterFrictionPlus->Visible = visible;
	}

	private: System::Void SetLocation_Static_Friction(Point location) {
		Text_Static_Friction->Location = Point(location.X, location.Y + 3);
		Value_Static_Friction->Location = Point(location.X + 130, location.Y + 3);
		Bar_StaticFrictionMinus->Location = Point(location.X, location.Y + 28);
		Bar_StaticFrictionPlus->Location = Point(location.X + 158, location.Y + 28);
	}

	private: System::Void SetVisible_Static_Friction(bool visible) {
		Text_Static_Friction->Visible = visible;
		Value_Static_Friction->Visible = visible;
		Bar_StaticFrictionMinus->Visible = visible;
		Bar_StaticFrictionPlus->Visible = visible;
	}

	private: System::Void SetLocation_Friction_Line(Point location) {
		Friction_Line->Location = location;
	}

	private: System::Void Button_Constant_Force_Details_Click(System::Object^  sender, System::EventArgs^  e) {
		constantForceDetails = !constantForceDetails;
		SetDetails(constantForceDetails, frictionForceDetails);
	}

	private: System::Void Button_Friction_Details_Click(System::Object^  sender, System::EventArgs^  e) {
		frictionForceDetails = !frictionForceDetails;
		SetDetails(constantForceDetails, frictionForceDetails);
	}

	private: System::Void SetDetails(bool constantForceDetails, bool frictionForceDetails) {
		Button_Constant_Force_Details->Text = (constantForceDetails) ? "詳細表示" : "簡易表示";
		Button_Friction_Details->Text = (frictionForceDetails) ? "詳細表示" : "簡易表示";

		int pos_y = 5;
		//InputAxis
		SetLocation_Input_Axis(Point(12, pos_y));
		SetVisible_Input_Axis(true);
		pos_y += 32;
		SetLocation_Input_Axis_Line(Point(9, pos_y));

		//ConstantForce
		pos_y += 27;
		SetLocation_Total_Direction_Force(Point(12, pos_y));
		SetVisible_Total_Direction_Force(true);
		if (constantForceDetails) {
			pos_y += 46;
			SetLocation_Movement_Force(Point(12, pos_y));
			SetVisible_Movement_Force(true);
			pos_y += 46;
			SetLocation_Rotate_Force(Point(12, pos_y));
			SetVisible_Rotate_Force(true);
		}
		else {
			SetVisible_Movement_Force(false);
			SetVisible_Rotate_Force(false);
		}
		pos_y += 32;
		SetLocation_Constant_Force_Line(Point(9, pos_y));

		//FrictionForce
		pos_y += 27;
		SetLocation_Total_Friction(Point(12, pos_y));
		if (frictionForceDetails) {
			pos_y += 46;
			SetLocation_Grip_Friction(Point(12, pos_y));
			SetVisible_Grip_Friction(true);
			pos_y += 46;
			SetLocation_Static_Friction(Point(12, pos_y));
			SetVisible_Static_Friction(true);
			pos_y += 46;
			SetLocation_Center_Friction(Point(12, pos_y));
			SetVisible_Center_Friction(true);
			
		}
		else {
			SetVisible_Grip_Friction(false);
			SetVisible_Static_Friction(false);
			SetVisible_Center_Friction(false);
		}
		pos_y += 32;
		SetLocation_Friction_Line(Point(9, pos_y));

		pos_y += 90;
		this->Size = System::Drawing::Size(this->Size.Width, pos_y);
	}

	private: System::Void ProgressBar_SpringGauge(ProgressBar^ progressbarMinus, ProgressBar^ progressbarPlus, Label^ value_text, LONG input_) {
		LONG input = min(max(input_, -progressbarMinus->Maximum), progressbarPlus->Maximum);
		progressbarPlus->Maximum += 1;
		progressbarPlus->Value = progressbarPlus->Maximum;
		progressbarPlus->Value = max(input, 0);
		progressbarPlus->Maximum -= 1;
		progressbarMinus->Maximum += 1;
		progressbarMinus->Value = progressbarMinus->Maximum;
		progressbarMinus->Value = max(-input, 0);
		progressbarMinus->Maximum -= 1;

		value_text->Text = input.ToString();
	}

	private: System::Void ProgressBar_FrictionGauge(ProgressBar^ progressbarMinus, ProgressBar^ progressbarPlus, Label^ value_text, LONG input_) {
		LONG input = min(input_, progressbarPlus->Maximum);
		progressbarPlus->Maximum += 1;
		progressbarPlus->Value = progressbarPlus->Maximum;
		progressbarPlus->Value = max(input, 0);
		progressbarPlus->Maximum -= 1;
		progressbarMinus->Maximum += 1;
		progressbarMinus->Value = progressbarMinus->Maximum;
		progressbarMinus->Value = max(input, 0);
		progressbarMinus->Maximum -= 1;

		value_text->Text = input.ToString();
	}

	//private: System::Void CheckBox_Scaling_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
	//	Bar_SpringPlus->Maximum = 10000;
	//	Bar_SpringMinus->Maximum = 10000;
	//	Bar_TotalDumperPlus->Maximum = 10000;
	//	Bar_TotalDumperMinus->Maximum = 10000;
	//
	//	if (CheckBox_Scaling->Checked) {
	//		if (!FFBMonitor_MaxForce) {
	//			System::String^ message = "MaxForceパラメーターを取得できませんでした";
	//			System::String^ title = "MaxForceでスケーリング";
	//			System::Windows::Forms::MessageBox::Show(message, title, MessageBoxButtons::OK, MessageBoxIcon::Warning);
	//			CheckBox_Scaling->Checked = false;
	//		}
	//		else {
	//			Bar_SpringPlus->Maximum = *FFBMonitor_MaxForce;
	//			Bar_SpringMinus->Maximum = *FFBMonitor_MaxForce;
	//			Bar_TotalDumperPlus->Maximum = *FFBMonitor_MaxForce;
	//			Bar_TotalDumperMinus->Maximum = *FFBMonitor_MaxForce;
	//		}
	//	}
	//}
};
}
