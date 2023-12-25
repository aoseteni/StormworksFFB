#pragma once

#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>

#include <string.h>
#include <cstdlib>

#include <Windows.h>
#include <WinUser.h>

#include <msclr/marshal_cppstd.h>

#define DIRECTINPUT_VERSION     0x0800          // DirectInputのバージョン指定
#include <dinput.h>

#include "DIUtils.h"

#include "AppDataFileSave.h"
#include "ProfileSave.h"
#include "CreateProfileForm.h"
#include "CopyProfileForm.h"
#include "FFBMonitorForm.h"
#include "TyreMonitorForm.h"

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "ws2_32.lib")

#define min(a,b)            (((a) < (b)) ? (a) : (b))
#define max(a,b)            (((a) > (b)) ? (a) : (b))
#define GetHInstance() ((HINSTANCE)GetModuleHandle(0))
#define GetHWND() (reinterpret_cast<HWND>(this->Handle.ToPointer()))

//StormworksからのFFB用信号受け取り用//

// ポート番号
const int port_number = 4091;
int channel = 0;

//チャンネルの最大数
const int channel_max = 10;

// Windows Sockets仕様に関する情報を格納する構造体
WSADATA wsa_data[channel_max];

// サーバ側ソケット作成
SOCKET src_socket[channel_max];

// sockaddr_in構造体の作成とポート番号、IPタイプの入力
struct sockaddr_in src_addr[channel_max];


// クライアント側のソケット設定
SOCKET dst_socket[channel_max];
struct sockaddr_in dst_addr[channel_max];
int dst_addr_size = sizeof(dst_addr);

// 送受信に使用するバッファ
char recv_buf[channel_max][256];
char send_buf[channel_max][256];

//各FFBパラメータ
enum {
	LEFT,
	RIGHT
};

struct CarState
{
	float tireSpeed[2];//単位:km/h
	bool tireOnGround[2];//trueで接地
	float bodySpeedX[2];//単位:km/h
	float bodySpeedZ[2];//単位:km/h
	float bodyRotateY[2];//単位:1回転/sec
	float wheelbase;
	float tread;
	float ackermannAnglePer;

	void Reset() {
		for (int i = 0; i < 2; i++) {
			tireSpeed[i] = 0;
			tireOnGround[i] = false;
			bodySpeedX[i] = 0;
			bodySpeedZ[i] = 0;
		}
		wheelbase = 0;
		tread = 0;
		ackermannAnglePer = 0;
	}
};
CarState carState;

int id_max = 0;//最新の情報のid番号

const int timeoutTime = 30;//単位:tick
int timeoutTimer = 0;
float TPS = 0;
int tickCount = 0;

//StormworksからのFFB用信号受け取り用//

//DirectInput用//
BYTE byKeyState[256];		//キーボード
DIMOUSESTATE diMouseState;	//マウス
DIDEV usingDeviceDID = DID_NONE;//使用中のデバイス番号
int usingAxisIndex = 0;		//使用中の軸番号
DIJOYSTATE diJoyState;		//ゲームパッド
DIJOYSTATE preDiJoyState;	//1tick前のゲームパッド
bool initialized = false;

Profile loadProfile;//ロードしたプロファイル(ロード後変更禁止)
Profile appProfile;//設定を一時的に保存する用
AppData appData;//起動時に読み込む設定

//フォームUI用変数
int preProfileIndex = 0;
int preDeviceIndex = 0;
int preAxisIndex = 0;
bool ffbBoot = false;
int ffbBootCount = 0;

//FFBモニター用変数
std::string FFBMonitor_Input_Axis_Name = "";
LONG FFBMonitor_Input_Axis = 0;
LONG FFBMonitor_Total_Direction_Force = 0;
LONG FFBMonitor_Movement_Force = 0;
LONG FFBMonitor_Rotate_Force = 0;
LONG FFBMonitor_Total_Friction = 0;
LONG FFBMonitor_Grip_Friction = 0;
LONG FFBMonitor_Center_Friction = 0;
LONG FFBMonitor_Static_Friction = 0;
LONG FFBMonitor_MaxForce = 0;

//タイヤモニター用変数
float TyreMonitor_LeftTyreAngle = 0;//単位:rad
float TyreMonitor_RightTyreAngle = 0;//単位:rad


//デバッグ用変数
float f1 = 0;
float f2 = 0;
float f3 = 0;

namespace StormworksFFB {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// MainForm の概要
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
		{
			InitializeComponent();
			//
			//TODO: ここにコンストラクター コードを追加します
			//
		}
	private: System::Windows::Forms::Label^  Text_InputAxis;
	public:

	private: System::Windows::Forms::CheckBox^  CheckBox_AlwaysOnTop;


	public:

	public:



	private: System::Windows::Forms::Label^  Text_Device;
	private: System::Windows::Forms::Label^  DeviceName;
	private: System::Windows::Forms::TrackBar^  TrackBar_MaxForce;

	private: System::Windows::Forms::Label^  Text_MaxForce;
	private: System::Windows::Forms::TextBox^  TextBox_MaxForce;


	private: System::Windows::Forms::Label^  Text_MovementForce;
	private: System::Windows::Forms::TrackBar^  TrackBar_MovementForce;
	private: System::Windows::Forms::TextBox^  TextBox_MovementForce;
	private: System::Windows::Forms::Label^  Text_StaticFriction;
	private: System::Windows::Forms::TrackBar^  TrackBar_StaticFriction;
	private: System::Windows::Forms::TextBox^  TextBox_StaticFriction;






	private: System::Windows::Forms::ToolTip^  toolTip1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::ProgressBar^  Bar_InputAxis_Plus;


	private: System::Windows::Forms::ProgressBar^  Bar_InputAxis_Minus;


	private: System::Windows::Forms::ComboBox^  ProfileList;
	private: System::Windows::Forms::Button^  ProfileSaveButton;
	private: System::Windows::Forms::Button^  ProfileRevertChangesButton;
	private: System::Windows::Forms::Button^  ProfileDeleteButton;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Button^  ProfileCopyButton;
	private: System::Windows::Forms::Button^  ProfileReturnToDefaultButton;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Button^  FFB_OFF_Button;
	private: System::Windows::Forms::Button^  FFB_ON_Button;
	private: System::Windows::Forms::Label^  FFBState_Text;
	private: System::Windows::Forms::ProgressBar^  FFBState_Bar;
	private: System::Windows::Forms::TrackBar^  TrackBar_CenterFrictionMax;

	private: System::Windows::Forms::TextBox^  TextBox_CenterFrictionMax;

	private: System::Windows::Forms::Label^  Text_CenterFrictionMax;
	private: System::Windows::Forms::TrackBar^  TrackBar_CenterFrictionZone;
	private: System::Windows::Forms::TextBox^  TextBox_CenterFrictionZone;



	private: System::Windows::Forms::Label^  Text_CenterFrictionZone;

	private: System::Windows::Forms::TrackBar^  TrackBar_TyreDynamicFrictionCoefficient;
	private: System::Windows::Forms::TextBox^  TextBox_TyreDynamicFrictionCoefficient;
	private: System::Windows::Forms::Label^  Text_TyreDynamicFrictionCoefficient;
	private: System::Windows::Forms::Label^  Text_TyreDynamicFrictionCoefficient_Unit;

	private: System::Windows::Forms::Button^  FFBMonitorButton;
	private: System::Windows::Forms::TrackBar^  TrackBar_RotateForce;
	private: System::Windows::Forms::TextBox^  TextBox_RotateForce;
	private: System::Windows::Forms::Label^  Text_RotateForce;
	private: System::Windows::Forms::TrackBar^  TrackBar_GripFriction;

	private: System::Windows::Forms::TextBox^  TextBox_GripFriction;

	private: System::Windows::Forms::Label^  Text_GripFriction;

	private: System::Windows::Forms::Label^  Text_ForceScale;
	private: System::Windows::Forms::TrackBar^  TrackBar_ForceScale;
	private: System::Windows::Forms::TextBox^  TextBox_ForceScale;



	private: System::Windows::Forms::Label^  Text_ForceScale_Unit;




	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::NumericUpDown^  ChannelSelectBox;
	private: System::Windows::Forms::ComboBox^  DeviceList;

	private: System::Windows::Forms::ComboBox^  AxisList;
	private: System::Windows::Forms::Label^  Text_Axis;


	private: System::Windows::Forms::TextBox^  TextBox_MinForce;

	private: System::Windows::Forms::Label^  Text_MinForce;
	private: System::Windows::Forms::TrackBar^  TrackBar_MinForce;




	private: System::Windows::Forms::TextBox^  TextBox_MaxTyreAngle;



	private: System::Windows::Forms::Label^  Text_MaxTyreAngle;
	private: System::Windows::Forms::Label^  Text_MaxTyreAngle_Unit;



	private: System::Windows::Forms::Label^  Text_MaxTyreAngleDeg;

	private: System::Windows::Forms::CheckBox^  CheckBox_InvertFFB;

	private: System::Windows::Forms::TrackBar^  TrackBar_DeadZoneInside;
	private: System::Windows::Forms::TextBox^  TextBox_DeadZoneInside;




	private: System::Windows::Forms::Label^  Text_DeadZoneInside;
private: System::Windows::Forms::Label^  Text_DeadZoneInside_Unit;


	private: System::Windows::Forms::TrackBar^  TrackBar_SoftLockForce;
	private: System::Windows::Forms::TextBox^  TextBox_SoftLockForce;



	private: System::Windows::Forms::Label^  Text_SoftLockForce;
	private: System::Windows::Forms::TextBox^  TextBox_DeadZoneOutside;



	private: System::Windows::Forms::Label^  Text_DeadZoneOutside;
private: System::Windows::Forms::Label^  Text_DeadZoneOutside_Unit;


private: System::Windows::Forms::TrackBar^  TrackBar_DeadZoneOutside;
private: System::Windows::Forms::TrackBar^  TrackBar_MaxTyreAngle;
private: System::Windows::Forms::Button^  TyreTypeButton;


private: System::Windows::Forms::Label^  label5;
private: System::Windows::Forms::Button^  TyreMonitorButton;





	public:
	private: System::Windows::Forms::Button^  ResetButton;
	public:


	protected:
		/// <summary>
		/// 使用中のリソースをすべてクリーンアップします。
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  Text_Online;
	protected:

	protected:


	private: System::ComponentModel::IContainer^  components;
	protected:

	private:

	private:
		/// <summary>
		/// 必要なデザイナー変数です。
		/// </summary>
		//OnTick用タイマー
		System::Timers::Timer^ timer;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// デザイナー サポートに必要なメソッドです。このメソッドの内容を
		/// コード エディターで変更しないでください。
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(MainForm::typeid));
			this->ResetButton = (gcnew System::Windows::Forms::Button());
			this->Text_Online = (gcnew System::Windows::Forms::Label());
			this->Text_InputAxis = (gcnew System::Windows::Forms::Label());
			this->CheckBox_AlwaysOnTop = (gcnew System::Windows::Forms::CheckBox());
			this->Text_Device = (gcnew System::Windows::Forms::Label());
			this->DeviceName = (gcnew System::Windows::Forms::Label());
			this->TrackBar_MaxForce = (gcnew System::Windows::Forms::TrackBar());
			this->Text_MaxForce = (gcnew System::Windows::Forms::Label());
			this->TextBox_MaxForce = (gcnew System::Windows::Forms::TextBox());
			this->Text_MovementForce = (gcnew System::Windows::Forms::Label());
			this->TrackBar_MovementForce = (gcnew System::Windows::Forms::TrackBar());
			this->TextBox_MovementForce = (gcnew System::Windows::Forms::TextBox());
			this->Text_StaticFriction = (gcnew System::Windows::Forms::Label());
			this->TrackBar_StaticFriction = (gcnew System::Windows::Forms::TrackBar());
			this->TextBox_StaticFriction = (gcnew System::Windows::Forms::TextBox());
			this->toolTip1 = (gcnew System::Windows::Forms::ToolTip(this->components));
			this->Text_CenterFrictionMax = (gcnew System::Windows::Forms::Label());
			this->Text_CenterFrictionZone = (gcnew System::Windows::Forms::Label());
			this->Text_TyreDynamicFrictionCoefficient = (gcnew System::Windows::Forms::Label());
			this->Text_RotateForce = (gcnew System::Windows::Forms::Label());
			this->Text_GripFriction = (gcnew System::Windows::Forms::Label());
			this->Text_ForceScale = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->ChannelSelectBox = (gcnew System::Windows::Forms::NumericUpDown());
			this->DeviceList = (gcnew System::Windows::Forms::ComboBox());
			this->AxisList = (gcnew System::Windows::Forms::ComboBox());
			this->Text_MinForce = (gcnew System::Windows::Forms::Label());
			this->Text_MaxTyreAngle = (gcnew System::Windows::Forms::Label());
			this->CheckBox_InvertFFB = (gcnew System::Windows::Forms::CheckBox());
			this->Text_DeadZoneInside = (gcnew System::Windows::Forms::Label());
			this->Text_SoftLockForce = (gcnew System::Windows::Forms::Label());
			this->Text_DeadZoneOutside = (gcnew System::Windows::Forms::Label());
			this->TyreTypeButton = (gcnew System::Windows::Forms::Button());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->Text_TyreDynamicFrictionCoefficient_Unit = (gcnew System::Windows::Forms::Label());
			this->Text_ForceScale_Unit = (gcnew System::Windows::Forms::Label());
			this->Text_MaxTyreAngle_Unit = (gcnew System::Windows::Forms::Label());
			this->Text_DeadZoneInside_Unit = (gcnew System::Windows::Forms::Label());
			this->Text_DeadZoneOutside_Unit = (gcnew System::Windows::Forms::Label());
			this->Text_MaxTyreAngleDeg = (gcnew System::Windows::Forms::Label());
			this->Text_Axis = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->Bar_InputAxis_Plus = (gcnew System::Windows::Forms::ProgressBar());
			this->Bar_InputAxis_Minus = (gcnew System::Windows::Forms::ProgressBar());
			this->ProfileList = (gcnew System::Windows::Forms::ComboBox());
			this->ProfileSaveButton = (gcnew System::Windows::Forms::Button());
			this->ProfileRevertChangesButton = (gcnew System::Windows::Forms::Button());
			this->ProfileDeleteButton = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->ProfileCopyButton = (gcnew System::Windows::Forms::Button());
			this->ProfileReturnToDefaultButton = (gcnew System::Windows::Forms::Button());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->FFB_OFF_Button = (gcnew System::Windows::Forms::Button());
			this->FFB_ON_Button = (gcnew System::Windows::Forms::Button());
			this->FFBState_Text = (gcnew System::Windows::Forms::Label());
			this->FFBState_Bar = (gcnew System::Windows::Forms::ProgressBar());
			this->TrackBar_CenterFrictionMax = (gcnew System::Windows::Forms::TrackBar());
			this->TextBox_CenterFrictionMax = (gcnew System::Windows::Forms::TextBox());
			this->TrackBar_CenterFrictionZone = (gcnew System::Windows::Forms::TrackBar());
			this->TextBox_CenterFrictionZone = (gcnew System::Windows::Forms::TextBox());
			this->TrackBar_TyreDynamicFrictionCoefficient = (gcnew System::Windows::Forms::TrackBar());
			this->TextBox_TyreDynamicFrictionCoefficient = (gcnew System::Windows::Forms::TextBox());
			this->FFBMonitorButton = (gcnew System::Windows::Forms::Button());
			this->TrackBar_RotateForce = (gcnew System::Windows::Forms::TrackBar());
			this->TextBox_RotateForce = (gcnew System::Windows::Forms::TextBox());
			this->TrackBar_GripFriction = (gcnew System::Windows::Forms::TrackBar());
			this->TextBox_GripFriction = (gcnew System::Windows::Forms::TextBox());
			this->TrackBar_ForceScale = (gcnew System::Windows::Forms::TrackBar());
			this->TextBox_ForceScale = (gcnew System::Windows::Forms::TextBox());
			this->TextBox_MinForce = (gcnew System::Windows::Forms::TextBox());
			this->TrackBar_MinForce = (gcnew System::Windows::Forms::TrackBar());
			this->TextBox_MaxTyreAngle = (gcnew System::Windows::Forms::TextBox());
			this->TrackBar_DeadZoneInside = (gcnew System::Windows::Forms::TrackBar());
			this->TextBox_DeadZoneInside = (gcnew System::Windows::Forms::TextBox());
			this->TrackBar_SoftLockForce = (gcnew System::Windows::Forms::TrackBar());
			this->TextBox_SoftLockForce = (gcnew System::Windows::Forms::TextBox());
			this->TextBox_DeadZoneOutside = (gcnew System::Windows::Forms::TextBox());
			this->TrackBar_DeadZoneOutside = (gcnew System::Windows::Forms::TrackBar());
			this->TrackBar_MaxTyreAngle = (gcnew System::Windows::Forms::TrackBar());
			this->TyreMonitorButton = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->TrackBar_MaxForce))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->TrackBar_MovementForce))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->TrackBar_StaticFriction))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ChannelSelectBox))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->TrackBar_CenterFrictionMax))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->TrackBar_CenterFrictionZone))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->TrackBar_TyreDynamicFrictionCoefficient))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->TrackBar_RotateForce))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->TrackBar_GripFriction))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->TrackBar_ForceScale))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->TrackBar_MinForce))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->TrackBar_DeadZoneInside))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->TrackBar_SoftLockForce))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->TrackBar_DeadZoneOutside))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->TrackBar_MaxTyreAngle))->BeginInit();
			this->SuspendLayout();
			// 
			// ResetButton
			// 
			this->ResetButton->Font = (gcnew System::Drawing::Font(L"Arial", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->ResetButton->Location = System::Drawing::Point(10, 627);
			this->ResetButton->Name = L"ResetButton";
			this->ResetButton->Size = System::Drawing::Size(98, 23);
			this->ResetButton->TabIndex = 0;
			this->ResetButton->Text = L"Reset";
			this->toolTip1->SetToolTip(this->ResetButton, L"アプリケーションのリセットを行います\r\nデバイスの変更及びアプリケーション外でのプロファイルの変更が行われた際に使用してください");
			this->ResetButton->UseVisualStyleBackColor = true;
			this->ResetButton->Click += gcnew System::EventHandler(this, &MainForm::ResetButton_Click);
			// 
			// Text_Online
			// 
			this->Text_Online->AutoSize = true;
			this->Text_Online->Font = (gcnew System::Drawing::Font(L"Arial", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Text_Online->ForeColor = System::Drawing::SystemColors::ControlDark;
			this->Text_Online->ImageAlign = System::Drawing::ContentAlignment::BottomRight;
			this->Text_Online->Location = System::Drawing::Point(359, 107);
			this->Text_Online->Name = L"Text_Online";
			this->Text_Online->Size = System::Drawing::Size(70, 24);
			this->Text_Online->TabIndex = 1;
			this->Text_Online->Text = L"Offline";
			this->toolTip1->SetToolTip(this->Text_Online, L"選択されたチャンネルでStormworks内ビークルからのFFB用信号の受信に成功していればOnline、いなければOfflineになります");
			// 
			// Text_InputAxis
			// 
			this->Text_InputAxis->Anchor = System::Windows::Forms::AnchorStyles::Top;
			this->Text_InputAxis->Font = (gcnew System::Drawing::Font(L"Arial", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Text_InputAxis->Location = System::Drawing::Point(308, 59);
			this->Text_InputAxis->Name = L"Text_InputAxis";
			this->Text_InputAxis->Size = System::Drawing::Size(58, 18);
			this->Text_InputAxis->TabIndex = 3;
			this->Text_InputAxis->Text = L"-10000";
			this->Text_InputAxis->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			this->toolTip1->SetToolTip(this->Text_InputAxis, L"FFBの対象となる軸の入力値を表します");
			// 
			// CheckBox_AlwaysOnTop
			// 
			this->CheckBox_AlwaysOnTop->AutoSize = true;
			this->CheckBox_AlwaysOnTop->Font = (gcnew System::Drawing::Font(L"BIZ UDPゴシック", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(128)));
			this->CheckBox_AlwaysOnTop->Location = System::Drawing::Point(558, 630);
			this->CheckBox_AlwaysOnTop->Name = L"CheckBox_AlwaysOnTop";
			this->CheckBox_AlwaysOnTop->Size = System::Drawing::Size(108, 16);
			this->CheckBox_AlwaysOnTop->TabIndex = 4;
			this->CheckBox_AlwaysOnTop->Text = L"常に前面に表示";
			this->CheckBox_AlwaysOnTop->UseVisualStyleBackColor = true;
			this->CheckBox_AlwaysOnTop->CheckedChanged += gcnew System::EventHandler(this, &MainForm::CheckBox_AlwaysOnTop_CheckedChanged);
			// 
			// Text_Device
			// 
			this->Text_Device->AutoSize = true;
			this->Text_Device->Font = (gcnew System::Drawing::Font(L"Arial", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Text_Device->Location = System::Drawing::Point(13, 4);
			this->Text_Device->Name = L"Text_Device";
			this->Text_Device->Size = System::Drawing::Size(57, 18);
			this->Text_Device->TabIndex = 5;
			this->Text_Device->Text = L"Device";
			// 
			// DeviceName
			// 
			this->DeviceName->AutoSize = true;
			this->DeviceName->Font = (gcnew System::Drawing::Font(L"Nirmala UI", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->DeviceName->Location = System::Drawing::Point(12, 30);
			this->DeviceName->Name = L"DeviceName";
			this->DeviceName->Size = System::Drawing::Size(108, 21);
			this->DeviceName->TabIndex = 6;
			this->DeviceName->Text = L"DeviceName";
			// 
			// TrackBar_MaxForce
			// 
			this->TrackBar_MaxForce->LargeChange = 50;
			this->TrackBar_MaxForce->Location = System::Drawing::Point(5, 260);
			this->TrackBar_MaxForce->Maximum = 10000;
			this->TrackBar_MaxForce->Name = L"TrackBar_MaxForce";
			this->TrackBar_MaxForce->Size = System::Drawing::Size(328, 45);
			this->TrackBar_MaxForce->SmallChange = 10;
			this->TrackBar_MaxForce->TabIndex = 7;
			this->TrackBar_MaxForce->TickFrequency = 1000;
			this->TrackBar_MaxForce->Value = 2000;
			this->TrackBar_MaxForce->Scroll += gcnew System::EventHandler(this, &MainForm::TrackBar_MaxForce_Scroll);
			// 
			// Text_MaxForce
			// 
			this->Text_MaxForce->AutoSize = true;
			this->Text_MaxForce->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Text_MaxForce->Location = System::Drawing::Point(10, 243);
			this->Text_MaxForce->Name = L"Text_MaxForce";
			this->Text_MaxForce->Size = System::Drawing::Size(62, 15);
			this->Text_MaxForce->TabIndex = 8;
			this->Text_MaxForce->Text = L"Max Force";
			this->toolTip1->SetToolTip(this->Text_MaxForce, L"FFBの最大値を設定します");
			// 
			// TextBox_MaxForce
			// 
			this->TextBox_MaxForce->Font = (gcnew System::Drawing::Font(L"Arial", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->TextBox_MaxForce->ImeMode = System::Windows::Forms::ImeMode::Disable;
			this->TextBox_MaxForce->Location = System::Drawing::Point(271, 234);
			this->TextBox_MaxForce->MaxLength = 5;
			this->TextBox_MaxForce->Name = L"TextBox_MaxForce";
			this->TextBox_MaxForce->ShortcutsEnabled = false;
			this->TextBox_MaxForce->Size = System::Drawing::Size(56, 26);
			this->TextBox_MaxForce->TabIndex = 12;
			this->TextBox_MaxForce->Text = L"0";
			this->TextBox_MaxForce->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MainForm::TextBox_NumOnly_KeyPress);
			this->TextBox_MaxForce->Leave += gcnew System::EventHandler(this, &MainForm::TextBox_MaxForce_Leave);
			// 
			// Text_MovementForce
			// 
			this->Text_MovementForce->AutoSize = true;
			this->Text_MovementForce->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Text_MovementForce->Location = System::Drawing::Point(10, 300);
			this->Text_MovementForce->Name = L"Text_MovementForce";
			this->Text_MovementForce->Size = System::Drawing::Size(97, 15);
			this->Text_MovementForce->TabIndex = 13;
			this->Text_MovementForce->Text = L"Movement Force";
			this->toolTip1->SetToolTip(this->Text_MovementForce, L"車体進行方向への力の強さを設定します");
			// 
			// TrackBar_MovementForce
			// 
			this->TrackBar_MovementForce->LargeChange = 50;
			this->TrackBar_MovementForce->Location = System::Drawing::Point(5, 316);
			this->TrackBar_MovementForce->Maximum = 10000;
			this->TrackBar_MovementForce->Name = L"TrackBar_MovementForce";
			this->TrackBar_MovementForce->Size = System::Drawing::Size(328, 45);
			this->TrackBar_MovementForce->SmallChange = 10;
			this->TrackBar_MovementForce->TabIndex = 14;
			this->TrackBar_MovementForce->TickFrequency = 1000;
			this->TrackBar_MovementForce->Value = 5000;
			this->TrackBar_MovementForce->Scroll += gcnew System::EventHandler(this, &MainForm::TrackBar_MovementForce_Scroll);
			// 
			// TextBox_MovementForce
			// 
			this->TextBox_MovementForce->Font = (gcnew System::Drawing::Font(L"Arial", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->TextBox_MovementForce->ImeMode = System::Windows::Forms::ImeMode::Disable;
			this->TextBox_MovementForce->Location = System::Drawing::Point(271, 290);
			this->TextBox_MovementForce->MaxLength = 5;
			this->TextBox_MovementForce->Name = L"TextBox_MovementForce";
			this->TextBox_MovementForce->ShortcutsEnabled = false;
			this->TextBox_MovementForce->Size = System::Drawing::Size(56, 26);
			this->TextBox_MovementForce->TabIndex = 15;
			this->TextBox_MovementForce->Text = L"0";
			this->TextBox_MovementForce->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MainForm::TextBox_NumOnly_KeyPress);
			this->TextBox_MovementForce->Leave += gcnew System::EventHandler(this, &MainForm::TextBox_MovementForce_Leave);
			// 
			// Text_StaticFriction
			// 
			this->Text_StaticFriction->AutoSize = true;
			this->Text_StaticFriction->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Text_StaticFriction->Location = System::Drawing::Point(345, 357);
			this->Text_StaticFriction->Name = L"Text_StaticFriction";
			this->Text_StaticFriction->Size = System::Drawing::Size(80, 15);
			this->Text_StaticFriction->TabIndex = 16;
			this->Text_StaticFriction->Text = L"Static Friction";
			this->toolTip1->SetToolTip(this->Text_StaticFriction, L"静止時の摩擦の強さを設定します");
			// 
			// TrackBar_StaticFriction
			// 
			this->TrackBar_StaticFriction->LargeChange = 50;
			this->TrackBar_StaticFriction->Location = System::Drawing::Point(340, 373);
			this->TrackBar_StaticFriction->Maximum = 10000;
			this->TrackBar_StaticFriction->Name = L"TrackBar_StaticFriction";
			this->TrackBar_StaticFriction->Size = System::Drawing::Size(328, 45);
			this->TrackBar_StaticFriction->SmallChange = 10;
			this->TrackBar_StaticFriction->TabIndex = 17;
			this->TrackBar_StaticFriction->TickFrequency = 1000;
			this->TrackBar_StaticFriction->Value = 5000;
			this->TrackBar_StaticFriction->Scroll += gcnew System::EventHandler(this, &MainForm::TrackBar_StaticFriction_Scroll);
			// 
			// TextBox_StaticFriction
			// 
			this->TextBox_StaticFriction->AcceptsReturn = true;
			this->TextBox_StaticFriction->Font = (gcnew System::Drawing::Font(L"Arial", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->TextBox_StaticFriction->ImeMode = System::Windows::Forms::ImeMode::Disable;
			this->TextBox_StaticFriction->Location = System::Drawing::Point(603, 347);
			this->TextBox_StaticFriction->MaxLength = 5;
			this->TextBox_StaticFriction->Name = L"TextBox_StaticFriction";
			this->TextBox_StaticFriction->ShortcutsEnabled = false;
			this->TextBox_StaticFriction->Size = System::Drawing::Size(56, 26);
			this->TextBox_StaticFriction->TabIndex = 18;
			this->TextBox_StaticFriction->Text = L"0";
			this->TextBox_StaticFriction->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MainForm::TextBox_NumOnly_KeyPress);
			this->TextBox_StaticFriction->Leave += gcnew System::EventHandler(this, &MainForm::TextBox_StaticFriction_Leave);
			// 
			// toolTip1
			// 
			this->toolTip1->AutomaticDelay = 0;
			// 
			// Text_CenterFrictionMax
			// 
			this->Text_CenterFrictionMax->AutoSize = true;
			this->Text_CenterFrictionMax->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Text_CenterFrictionMax->Location = System::Drawing::Point(345, 414);
			this->Text_CenterFrictionMax->Name = L"Text_CenterFrictionMax";
			this->Text_CenterFrictionMax->Size = System::Drawing::Size(111, 15);
			this->Text_CenterFrictionMax->TabIndex = 38;
			this->Text_CenterFrictionMax->Text = L"Center Friction Max";
			this->toolTip1->SetToolTip(this->Text_CenterFrictionMax, L"センター付近の摩擦の最大強さを設定します");
			// 
			// Text_CenterFrictionZone
			// 
			this->Text_CenterFrictionZone->AutoSize = true;
			this->Text_CenterFrictionZone->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Text_CenterFrictionZone->Location = System::Drawing::Point(346, 471);
			this->Text_CenterFrictionZone->Name = L"Text_CenterFrictionZone";
			this->Text_CenterFrictionZone->Size = System::Drawing::Size(118, 15);
			this->Text_CenterFrictionZone->TabIndex = 41;
			this->Text_CenterFrictionZone->Text = L"Center Friction Zone";
			this->toolTip1->SetToolTip(this->Text_CenterFrictionZone, L"センター付近の摩擦の範囲を設定します");
			// 
			// Text_TyreDynamicFrictionCoefficient
			// 
			this->Text_TyreDynamicFrictionCoefficient->AutoSize = true;
			this->Text_TyreDynamicFrictionCoefficient->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->Text_TyreDynamicFrictionCoefficient->Location = System::Drawing::Point(345, 243);
			this->Text_TyreDynamicFrictionCoefficient->Name = L"Text_TyreDynamicFrictionCoefficient";
			this->Text_TyreDynamicFrictionCoefficient->Size = System::Drawing::Size(184, 15);
			this->Text_TyreDynamicFrictionCoefficient->TabIndex = 44;
			this->Text_TyreDynamicFrictionCoefficient->Text = L"Tyre Dynamic Friction Coefficient";
			this->toolTip1->SetToolTip(this->Text_TyreDynamicFrictionCoefficient, L"タイヤがスリップした際の摩擦係数倍率を設定します");
			// 
			// Text_RotateForce
			// 
			this->Text_RotateForce->AutoSize = true;
			this->Text_RotateForce->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Text_RotateForce->Location = System::Drawing::Point(10, 357);
			this->Text_RotateForce->Name = L"Text_RotateForce";
			this->Text_RotateForce->Size = System::Drawing::Size(77, 15);
			this->Text_RotateForce->TabIndex = 49;
			this->Text_RotateForce->Text = L"Rotate Force";
			this->toolTip1->SetToolTip(this->Text_RotateForce, L"車体回転時の力の強さを設定します");
			// 
			// Text_GripFriction
			// 
			this->Text_GripFriction->AutoSize = true;
			this->Text_GripFriction->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Text_GripFriction->Location = System::Drawing::Point(345, 300);
			this->Text_GripFriction->Name = L"Text_GripFriction";
			this->Text_GripFriction->Size = System::Drawing::Size(73, 15);
			this->Text_GripFriction->TabIndex = 52;
			this->Text_GripFriction->Text = L"Grip Friction";
			this->toolTip1->SetToolTip(this->Text_GripFriction, L"タイヤ接地時の摩擦の強さを設定します");
			// 
			// Text_ForceScale
			// 
			this->Text_ForceScale->AutoSize = true;
			this->Text_ForceScale->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Text_ForceScale->Location = System::Drawing::Point(345, 186);
			this->Text_ForceScale->Name = L"Text_ForceScale";
			this->Text_ForceScale->Size = System::Drawing::Size(72, 15);
			this->Text_ForceScale->TabIndex = 56;
			this->Text_ForceScale->Text = L"Force Scale";
			this->toolTip1->SetToolTip(this->Text_ForceScale, L"FFBの倍率を設定します");
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Font = (gcnew System::Drawing::Font(L"Arial", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label6->Location = System::Drawing::Point(251, 111);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(62, 17);
			this->label6->TabIndex = 61;
			this->label6->Text = L"Channel";
			this->toolTip1->SetToolTip(this->label6, L"チャンネルを選択します\r\n接続先のStormworks内ビークルと同じ数値を選択してください");
			// 
			// ChannelSelectBox
			// 
			this->ChannelSelectBox->BackColor = System::Drawing::SystemColors::Window;
			this->ChannelSelectBox->Font = (gcnew System::Drawing::Font(L"Arial", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0), true));
			this->ChannelSelectBox->Location = System::Drawing::Point(313, 107);
			this->ChannelSelectBox->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 10, 0, 0, 0 });
			this->ChannelSelectBox->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->ChannelSelectBox->Name = L"ChannelSelectBox";
			this->ChannelSelectBox->ReadOnly = true;
			this->ChannelSelectBox->Size = System::Drawing::Size(45, 25);
			this->ChannelSelectBox->TabIndex = 62;
			this->toolTip1->SetToolTip(this->ChannelSelectBox, L"チャンネルを選択します\r\n接続先のStormworks内ビークルと同じ数値を選択してください");
			this->ChannelSelectBox->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->ChannelSelectBox->ValueChanged += gcnew System::EventHandler(this, &MainForm::ChannelSelectBox_ValueChanged);
			// 
			// DeviceList
			// 
			this->DeviceList->DropDownHeight = 200;
			this->DeviceList->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->DeviceList->DropDownWidth = 200;
			this->DeviceList->Font = (gcnew System::Drawing::Font(L"Arial", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->DeviceList->IntegralHeight = false;
			this->DeviceList->ItemHeight = 16;
			this->DeviceList->Items->AddRange(gcnew cli::array< System::Object^  >(1) { L"DeviceName USB Controller" });
			this->DeviceList->Location = System::Drawing::Point(13, 24);
			this->DeviceList->Name = L"DeviceList";
			this->DeviceList->Size = System::Drawing::Size(647, 24);
			this->DeviceList->TabIndex = 63;
			this->toolTip1->SetToolTip(this->DeviceList, L"使用するデバイスを選択します");
			this->DeviceList->SelectedIndexChanged += gcnew System::EventHandler(this, &MainForm::DeviceList_SelectedIndexChanged);
			// 
			// AxisList
			// 
			this->AxisList->DropDownHeight = 200;
			this->AxisList->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->AxisList->DropDownWidth = 200;
			this->AxisList->Font = (gcnew System::Drawing::Font(L"Arial", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->AxisList->IntegralHeight = false;
			this->AxisList->ItemHeight = 16;
			this->AxisList->Items->AddRange(gcnew cli::array< System::Object^  >(6) { L"lX", L"lY", L"lZ", L"lRx", L"lRy", L"lRz" });
			this->AxisList->Location = System::Drawing::Point(51, 54);
			this->AxisList->Name = L"AxisList";
			this->AxisList->Size = System::Drawing::Size(44, 24);
			this->AxisList->TabIndex = 64;
			this->toolTip1->SetToolTip(this->AxisList, L"FFBを出力する軸を選択します");
			this->AxisList->SelectedIndexChanged += gcnew System::EventHandler(this, &MainForm::AxisList_SelectedIndexChanged);
			// 
			// Text_MinForce
			// 
			this->Text_MinForce->AutoSize = true;
			this->Text_MinForce->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Text_MinForce->Location = System::Drawing::Point(10, 186);
			this->Text_MinForce->Name = L"Text_MinForce";
			this->Text_MinForce->Size = System::Drawing::Size(60, 15);
			this->Text_MinForce->TabIndex = 67;
			this->Text_MinForce->Text = L"Min Force";
			this->toolTip1->SetToolTip(this->Text_MinForce, L"FFBの最小値を設定します");
			// 
			// Text_MaxTyreAngle
			// 
			this->Text_MaxTyreAngle->AutoSize = true;
			this->Text_MaxTyreAngle->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Text_MaxTyreAngle->Location = System::Drawing::Point(346, 528);
			this->Text_MaxTyreAngle->Name = L"Text_MaxTyreAngle";
			this->Text_MaxTyreAngle->Size = System::Drawing::Size(86, 15);
			this->Text_MaxTyreAngle->TabIndex = 70;
			this->Text_MaxTyreAngle->Text = L"Max Tyre Angle";
			this->toolTip1->SetToolTip(this->Text_MaxTyreAngle, L"タイヤの最大切れ角を設定します");
			// 
			// CheckBox_InvertFFB
			// 
			this->CheckBox_InvertFFB->AutoSize = true;
			this->CheckBox_InvertFFB->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->CheckBox_InvertFFB->Location = System::Drawing::Point(525, 185);
			this->CheckBox_InvertFFB->Name = L"CheckBox_InvertFFB";
			this->CheckBox_InvertFFB->Size = System::Drawing::Size(80, 19);
			this->CheckBox_InvertFFB->TabIndex = 74;
			this->CheckBox_InvertFFB->Text = L"Invert FFB";
			this->toolTip1->SetToolTip(this->CheckBox_InvertFFB, L"FFB信号を反転します");
			this->CheckBox_InvertFFB->UseVisualStyleBackColor = true;
			this->CheckBox_InvertFFB->CheckedChanged += gcnew System::EventHandler(this, &MainForm::CheckBox_InvertFFB_CheckedChanged);
			// 
			// Text_DeadZoneInside
			// 
			this->Text_DeadZoneInside->AutoSize = true;
			this->Text_DeadZoneInside->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Text_DeadZoneInside->Location = System::Drawing::Point(10, 414);
			this->Text_DeadZoneInside->Name = L"Text_DeadZoneInside";
			this->Text_DeadZoneInside->Size = System::Drawing::Size(113, 15);
			this->Text_DeadZoneInside->TabIndex = 75;
			this->Text_DeadZoneInside->Text = L"Dead Zone (inside)";
			this->toolTip1->SetToolTip(this->Text_DeadZoneInside, L"内側のデッドゾーンを設定します\r\n指定した割合以下の入力はすべて最小値として扱われます");
			// 
			// Text_SoftLockForce
			// 
			this->Text_SoftLockForce->AutoSize = true;
			this->Text_SoftLockForce->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Text_SoftLockForce->Location = System::Drawing::Point(10, 528);
			this->Text_SoftLockForce->Name = L"Text_SoftLockForce";
			this->Text_SoftLockForce->Size = System::Drawing::Size(91, 15);
			this->Text_SoftLockForce->TabIndex = 79;
			this->Text_SoftLockForce->Text = L"Soft Lock Force";
			this->toolTip1->SetToolTip(this->Text_SoftLockForce, L"ハンドルが\"Dead Zone (outside)\"に到達した際にかける力を設定します\r\nこの設定は\"Max Force\"及び\"Min Force\"の影響を受けま"
				L"せん");
			// 
			// Text_DeadZoneOutside
			// 
			this->Text_DeadZoneOutside->AutoSize = true;
			this->Text_DeadZoneOutside->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Text_DeadZoneOutside->Location = System::Drawing::Point(10, 471);
			this->Text_DeadZoneOutside->Name = L"Text_DeadZoneOutside";
			this->Text_DeadZoneOutside->Size = System::Drawing::Size(120, 15);
			this->Text_DeadZoneOutside->TabIndex = 82;
			this->Text_DeadZoneOutside->Text = L"Dead Zone (outside)";
			this->toolTip1->SetToolTip(this->Text_DeadZoneOutside, L"外側のデッドゾーンを設定します\r\n指定した割合以上の入力はすべて最大値として扱われます");
			// 
			// TyreTypeButton
			// 
			this->TyreTypeButton->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->TyreTypeButton->Location = System::Drawing::Point(467, 524);
			this->TyreTypeButton->Margin = System::Windows::Forms::Padding(0);
			this->TyreTypeButton->Name = L"TyreTypeButton";
			this->TyreTypeButton->Size = System::Drawing::Size(54, 22);
			this->TyreTypeButton->TabIndex = 87;
			this->TyreTypeButton->Text = L"Default";
			this->toolTip1->SetToolTip(this->TyreTypeButton, L"Default:");
			this->TyreTypeButton->UseVisualStyleBackColor = true;
			this->TyreTypeButton->Click += gcnew System::EventHandler(this, &MainForm::TyreTypeButton_Click);
			// 
			// label5
			// 
			this->label5->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Right));
			this->label5->AutoSize = true;
			this->label5->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label5->ImageAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->label5->Location = System::Drawing::Point(436, 528);
			this->label5->Name = L"label5";
			this->label5->RightToLeft = System::Windows::Forms::RightToLeft::No;
			this->label5->Size = System::Drawing::Size(35, 15);
			this->label5->TabIndex = 88;
			this->label5->Text = L"Type:";
			this->label5->TextAlign = System::Drawing::ContentAlignment::TopRight;
			this->toolTip1->SetToolTip(this->label5, L"タイヤを曲げる方式を選択します");
			// 
			// Text_TyreDynamicFrictionCoefficient_Unit
			// 
			this->Text_TyreDynamicFrictionCoefficient_Unit->AutoSize = true;
			this->Text_TyreDynamicFrictionCoefficient_Unit->Font = (gcnew System::Drawing::Font(L"Arial", 12, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->Text_TyreDynamicFrictionCoefficient_Unit->Location = System::Drawing::Point(642, 238);
			this->Text_TyreDynamicFrictionCoefficient_Unit->Name = L"Text_TyreDynamicFrictionCoefficient_Unit";
			this->Text_TyreDynamicFrictionCoefficient_Unit->Size = System::Drawing::Size(22, 18);
			this->Text_TyreDynamicFrictionCoefficient_Unit->TabIndex = 47;
			this->Text_TyreDynamicFrictionCoefficient_Unit->Text = L"%";
			// 
			// Text_ForceScale_Unit
			// 
			this->Text_ForceScale_Unit->AutoSize = true;
			this->Text_ForceScale_Unit->Font = (gcnew System::Drawing::Font(L"Arial", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Text_ForceScale_Unit->Location = System::Drawing::Point(642, 181);
			this->Text_ForceScale_Unit->Name = L"Text_ForceScale_Unit";
			this->Text_ForceScale_Unit->Size = System::Drawing::Size(22, 18);
			this->Text_ForceScale_Unit->TabIndex = 59;
			this->Text_ForceScale_Unit->Text = L"%";
			// 
			// Text_MaxTyreAngle_Unit
			// 
			this->Text_MaxTyreAngle_Unit->AutoSize = true;
			this->Text_MaxTyreAngle_Unit->Font = (gcnew System::Drawing::Font(L"Arial", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Text_MaxTyreAngle_Unit->Location = System::Drawing::Point(582, 526);
			this->Text_MaxTyreAngle_Unit->Name = L"Text_MaxTyreAngle_Unit";
			this->Text_MaxTyreAngle_Unit->Size = System::Drawing::Size(83, 18);
			this->Text_MaxTyreAngle_Unit->TabIndex = 72;
			this->Text_MaxTyreAngle_Unit->Text = L"x0.25 turns";
			// 
			// Text_DeadZoneInside_Unit
			// 
			this->Text_DeadZoneInside_Unit->AutoSize = true;
			this->Text_DeadZoneInside_Unit->Font = (gcnew System::Drawing::Font(L"Arial", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Text_DeadZoneInside_Unit->Location = System::Drawing::Point(310, 408);
			this->Text_DeadZoneInside_Unit->Name = L"Text_DeadZoneInside_Unit";
			this->Text_DeadZoneInside_Unit->Size = System::Drawing::Size(22, 18);
			this->Text_DeadZoneInside_Unit->TabIndex = 78;
			this->Text_DeadZoneInside_Unit->Text = L"%";
			// 
			// Text_DeadZoneOutside_Unit
			// 
			this->Text_DeadZoneOutside_Unit->AutoSize = true;
			this->Text_DeadZoneOutside_Unit->Font = (gcnew System::Drawing::Font(L"Arial", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Text_DeadZoneOutside_Unit->Location = System::Drawing::Point(310, 465);
			this->Text_DeadZoneOutside_Unit->Name = L"Text_DeadZoneOutside_Unit";
			this->Text_DeadZoneOutside_Unit->Size = System::Drawing::Size(22, 18);
			this->Text_DeadZoneOutside_Unit->TabIndex = 85;
			this->Text_DeadZoneOutside_Unit->Text = L"%";
			// 
			// Text_MaxTyreAngleDeg
			// 
			this->Text_MaxTyreAngleDeg->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Right));
			this->Text_MaxTyreAngleDeg->AutoSize = true;
			this->Text_MaxTyreAngleDeg->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Text_MaxTyreAngleDeg->ImageAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->Text_MaxTyreAngleDeg->Location = System::Drawing::Point(581, 514);
			this->Text_MaxTyreAngleDeg->Name = L"Text_MaxTyreAngleDeg";
			this->Text_MaxTyreAngleDeg->RightToLeft = System::Windows::Forms::RightToLeft::No;
			this->Text_MaxTyreAngleDeg->Size = System::Drawing::Size(77, 15);
			this->Text_MaxTyreAngleDeg->TabIndex = 73;
			this->Text_MaxTyreAngleDeg->Text = L"(59.124 deg)";
			this->Text_MaxTyreAngleDeg->TextAlign = System::Drawing::ContentAlignment::TopRight;
			this->Text_MaxTyreAngleDeg->SizeChanged += gcnew System::EventHandler(this, &MainForm::Text_MaxTyreAngleDeg_TextChanged);
			// 
			// Text_Axis
			// 
			this->Text_Axis->AutoSize = true;
			this->Text_Axis->Font = (gcnew System::Drawing::Font(L"Arial", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Text_Axis->Location = System::Drawing::Point(15, 57);
			this->Text_Axis->Name = L"Text_Axis";
			this->Text_Axis->Size = System::Drawing::Size(38, 18);
			this->Text_Axis->TabIndex = 65;
			this->Text_Axis->Text = L"Axis";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Arial", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label2->ForeColor = System::Drawing::SystemColors::ActiveBorder;
			this->label2->Location = System::Drawing::Point(9, 152);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(656, 18);
			this->label2->TabIndex = 19;
			this->label2->Text = L"________________________________________________________________________";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"Arial", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label4->ForeColor = System::Drawing::SystemColors::ActiveBorder;
			this->label4->Location = System::Drawing::Point(9, 603);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(656, 18);
			this->label4->TabIndex = 20;
			this->label4->Text = L"________________________________________________________________________";
			// 
			// Bar_InputAxis_Plus
			// 
			this->Bar_InputAxis_Plus->Location = System::Drawing::Point(336, 81);
			this->Bar_InputAxis_Plus->Maximum = 10000;
			this->Bar_InputAxis_Plus->Name = L"Bar_InputAxis_Plus";
			this->Bar_InputAxis_Plus->Size = System::Drawing::Size(323, 10);
			this->Bar_InputAxis_Plus->Step = 1;
			this->Bar_InputAxis_Plus->TabIndex = 22;
			// 
			// Bar_InputAxis_Minus
			// 
			this->Bar_InputAxis_Minus->Location = System::Drawing::Point(13, 81);
			this->Bar_InputAxis_Minus->Maximum = 10000;
			this->Bar_InputAxis_Minus->Name = L"Bar_InputAxis_Minus";
			this->Bar_InputAxis_Minus->RightToLeft = System::Windows::Forms::RightToLeft::Yes;
			this->Bar_InputAxis_Minus->RightToLeftLayout = true;
			this->Bar_InputAxis_Minus->Size = System::Drawing::Size(323, 10);
			this->Bar_InputAxis_Minus->Step = 1;
			this->Bar_InputAxis_Minus->TabIndex = 23;
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
			this->ProfileList->Location = System::Drawing::Point(12, 589);
			this->ProfileList->Name = L"ProfileList";
			this->ProfileList->Size = System::Drawing::Size(216, 24);
			this->ProfileList->TabIndex = 24;
			this->ProfileList->SelectedIndexChanged += gcnew System::EventHandler(this, &MainForm::ProfileList_SelectedIndexChanged);
			// 
			// ProfileSaveButton
			// 
			this->ProfileSaveButton->Font = (gcnew System::Drawing::Font(L"BIZ UDPゴシック", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(128)));
			this->ProfileSaveButton->Location = System::Drawing::Point(231, 588);
			this->ProfileSaveButton->Name = L"ProfileSaveButton";
			this->ProfileSaveButton->Size = System::Drawing::Size(73, 26);
			this->ProfileSaveButton->TabIndex = 25;
			this->ProfileSaveButton->Text = L"上書き保存";
			this->ProfileSaveButton->UseVisualStyleBackColor = true;
			this->ProfileSaveButton->Click += gcnew System::EventHandler(this, &MainForm::ProfileSaveButton_Click);
			// 
			// ProfileRevertChangesButton
			// 
			this->ProfileRevertChangesButton->Font = (gcnew System::Drawing::Font(L"BIZ UDPゴシック", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(128)));
			this->ProfileRevertChangesButton->Location = System::Drawing::Point(305, 588);
			this->ProfileRevertChangesButton->Name = L"ProfileRevertChangesButton";
			this->ProfileRevertChangesButton->Size = System::Drawing::Size(73, 26);
			this->ProfileRevertChangesButton->TabIndex = 26;
			this->ProfileRevertChangesButton->Text = L"変更を破棄";
			this->ProfileRevertChangesButton->UseVisualStyleBackColor = true;
			this->ProfileRevertChangesButton->Click += gcnew System::EventHandler(this, &MainForm::ProfileRevertChangesButton_Click);
			// 
			// ProfileDeleteButton
			// 
			this->ProfileDeleteButton->Font = (gcnew System::Drawing::Font(L"BIZ UDPゴシック", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(128)));
			this->ProfileDeleteButton->Location = System::Drawing::Point(379, 588);
			this->ProfileDeleteButton->Name = L"ProfileDeleteButton";
			this->ProfileDeleteButton->Size = System::Drawing::Size(73, 26);
			this->ProfileDeleteButton->TabIndex = 27;
			this->ProfileDeleteButton->Text = L"設定を削除";
			this->ProfileDeleteButton->UseVisualStyleBackColor = true;
			this->ProfileDeleteButton->Click += gcnew System::EventHandler(this, &MainForm::ProfileDeleteButton_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"BIZ UDPゴシック", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(12, 573);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(70, 12);
			this->label1->TabIndex = 28;
			this->label1->Text = L"プロファイル";
			// 
			// ProfileCopyButton
			// 
			this->ProfileCopyButton->Font = (gcnew System::Drawing::Font(L"BIZ UDPゴシック", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(128)));
			this->ProfileCopyButton->Location = System::Drawing::Point(574, 588);
			this->ProfileCopyButton->Name = L"ProfileCopyButton";
			this->ProfileCopyButton->Size = System::Drawing::Size(88, 26);
			this->ProfileCopyButton->TabIndex = 29;
			this->ProfileCopyButton->Text = L"設定のコピー";
			this->ProfileCopyButton->UseVisualStyleBackColor = true;
			this->ProfileCopyButton->Click += gcnew System::EventHandler(this, &MainForm::ProfileCopyButton_Click);
			// 
			// ProfileReturnToDefaultButton
			// 
			this->ProfileReturnToDefaultButton->Font = (gcnew System::Drawing::Font(L"BIZ UDPゴシック", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(128)));
			this->ProfileReturnToDefaultButton->Location = System::Drawing::Point(453, 588);
			this->ProfileReturnToDefaultButton->Name = L"ProfileReturnToDefaultButton";
			this->ProfileReturnToDefaultButton->Size = System::Drawing::Size(120, 26);
			this->ProfileReturnToDefaultButton->TabIndex = 31;
			this->ProfileReturnToDefaultButton->Text = L"デフォルト値に戻す";
			this->ProfileReturnToDefaultButton->UseVisualStyleBackColor = true;
			this->ProfileReturnToDefaultButton->Click += gcnew System::EventHandler(this, &MainForm::ReturnToDefaultButton_Click);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Arial", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label3->ForeColor = System::Drawing::SystemColors::ActiveBorder;
			this->label3->Location = System::Drawing::Point(9, 83);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(656, 18);
			this->label3->TabIndex = 32;
			this->label3->Text = L"________________________________________________________________________";
			// 
			// FFB_OFF_Button
			// 
			this->FFB_OFF_Button->BackColor = System::Drawing::Color::OrangeRed;
			this->FFB_OFF_Button->Font = (gcnew System::Drawing::Font(L"BIZ UDPゴシック", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(128)));
			this->FFB_OFF_Button->Location = System::Drawing::Point(93, 133);
			this->FFB_OFF_Button->Name = L"FFB_OFF_Button";
			this->FFB_OFF_Button->Size = System::Drawing::Size(160, 30);
			this->FFB_OFF_Button->TabIndex = 33;
			this->FFB_OFF_Button->Text = L"FFB OFF";
			this->FFB_OFF_Button->UseVisualStyleBackColor = false;
			this->FFB_OFF_Button->Click += gcnew System::EventHandler(this, &MainForm::FFB_OFF_Button_Click);
			// 
			// FFB_ON_Button
			// 
			this->FFB_ON_Button->BackColor = System::Drawing::Color::LawnGreen;
			this->FFB_ON_Button->Font = (gcnew System::Drawing::Font(L"BIZ UDPゴシック", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(128)));
			this->FFB_ON_Button->Location = System::Drawing::Point(255, 133);
			this->FFB_ON_Button->Name = L"FFB_ON_Button";
			this->FFB_ON_Button->Size = System::Drawing::Size(160, 30);
			this->FFB_ON_Button->TabIndex = 34;
			this->FFB_ON_Button->Text = L"FFB ON";
			this->FFB_ON_Button->UseVisualStyleBackColor = false;
			this->FFB_ON_Button->Click += gcnew System::EventHandler(this, &MainForm::FFB_ON_Button_Click);
			// 
			// FFBState_Text
			// 
			this->FFBState_Text->AutoSize = true;
			this->FFBState_Text->Font = (gcnew System::Drawing::Font(L"Arial", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->FFBState_Text->ForeColor = System::Drawing::SystemColors::ControlDark;
			this->FFBState_Text->Location = System::Drawing::Point(417, 132);
			this->FFBState_Text->Name = L"FFBState_Text";
			this->FFBState_Text->Size = System::Drawing::Size(80, 16);
			this->FFBState_Text->TabIndex = 36;
			this->FFBState_Text->Text = L"FFB Inactive";
			// 
			// FFBState_Bar
			// 
			this->FFBState_Bar->Location = System::Drawing::Point(418, 149);
			this->FFBState_Bar->Maximum = 10000;
			this->FFBState_Bar->Name = L"FFBState_Bar";
			this->FFBState_Bar->Size = System::Drawing::Size(160, 12);
			this->FFBState_Bar->Step = 1;
			this->FFBState_Bar->TabIndex = 37;
			this->FFBState_Bar->Value = 9999;
			// 
			// TrackBar_CenterFrictionMax
			// 
			this->TrackBar_CenterFrictionMax->LargeChange = 50;
			this->TrackBar_CenterFrictionMax->Location = System::Drawing::Point(340, 430);
			this->TrackBar_CenterFrictionMax->Maximum = 10000;
			this->TrackBar_CenterFrictionMax->Name = L"TrackBar_CenterFrictionMax";
			this->TrackBar_CenterFrictionMax->Size = System::Drawing::Size(328, 45);
			this->TrackBar_CenterFrictionMax->SmallChange = 10;
			this->TrackBar_CenterFrictionMax->TabIndex = 39;
			this->TrackBar_CenterFrictionMax->TickFrequency = 1000;
			this->TrackBar_CenterFrictionMax->Value = 10000;
			this->TrackBar_CenterFrictionMax->Scroll += gcnew System::EventHandler(this, &MainForm::TrackBar_CenterFrictionMax_Scroll);
			// 
			// TextBox_CenterFrictionMax
			// 
			this->TextBox_CenterFrictionMax->Font = (gcnew System::Drawing::Font(L"Arial", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->TextBox_CenterFrictionMax->ImeMode = System::Windows::Forms::ImeMode::Disable;
			this->TextBox_CenterFrictionMax->Location = System::Drawing::Point(604, 404);
			this->TextBox_CenterFrictionMax->MaxLength = 5;
			this->TextBox_CenterFrictionMax->Name = L"TextBox_CenterFrictionMax";
			this->TextBox_CenterFrictionMax->ShortcutsEnabled = false;
			this->TextBox_CenterFrictionMax->Size = System::Drawing::Size(56, 26);
			this->TextBox_CenterFrictionMax->TabIndex = 40;
			this->TextBox_CenterFrictionMax->Text = L"0";
			this->TextBox_CenterFrictionMax->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MainForm::TextBox_NumOnly_KeyPress);
			this->TextBox_CenterFrictionMax->Leave += gcnew System::EventHandler(this, &MainForm::TextBox_CenterFrictionMax_Leave);
			// 
			// TrackBar_CenterFrictionZone
			// 
			this->TrackBar_CenterFrictionZone->Cursor = System::Windows::Forms::Cursors::Default;
			this->TrackBar_CenterFrictionZone->LargeChange = 50;
			this->TrackBar_CenterFrictionZone->Location = System::Drawing::Point(340, 487);
			this->TrackBar_CenterFrictionZone->Maximum = 10000;
			this->TrackBar_CenterFrictionZone->Name = L"TrackBar_CenterFrictionZone";
			this->TrackBar_CenterFrictionZone->Size = System::Drawing::Size(328, 45);
			this->TrackBar_CenterFrictionZone->SmallChange = 10;
			this->TrackBar_CenterFrictionZone->TabIndex = 42;
			this->TrackBar_CenterFrictionZone->TickFrequency = 1000;
			this->TrackBar_CenterFrictionZone->Value = 5000;
			this->TrackBar_CenterFrictionZone->Scroll += gcnew System::EventHandler(this, &MainForm::TrackBar_CenterFrictionZone_Scroll);
			// 
			// TextBox_CenterFrictionZone
			// 
			this->TextBox_CenterFrictionZone->Font = (gcnew System::Drawing::Font(L"Arial", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->TextBox_CenterFrictionZone->ImeMode = System::Windows::Forms::ImeMode::Disable;
			this->TextBox_CenterFrictionZone->Location = System::Drawing::Point(605, 461);
			this->TextBox_CenterFrictionZone->MaxLength = 5;
			this->TextBox_CenterFrictionZone->Name = L"TextBox_CenterFrictionZone";
			this->TextBox_CenterFrictionZone->ShortcutsEnabled = false;
			this->TextBox_CenterFrictionZone->Size = System::Drawing::Size(56, 26);
			this->TextBox_CenterFrictionZone->TabIndex = 43;
			this->TextBox_CenterFrictionZone->Text = L"0";
			this->TextBox_CenterFrictionZone->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MainForm::TextBox_NumOnly_KeyPress);
			this->TextBox_CenterFrictionZone->Leave += gcnew System::EventHandler(this, &MainForm::TextBox_CenterFrictionZone_Leave);
			// 
			// TrackBar_TyreDynamicFrictionCoefficient
			// 
			this->TrackBar_TyreDynamicFrictionCoefficient->LargeChange = 10;
			this->TrackBar_TyreDynamicFrictionCoefficient->Location = System::Drawing::Point(340, 260);
			this->TrackBar_TyreDynamicFrictionCoefficient->Maximum = 100;
			this->TrackBar_TyreDynamicFrictionCoefficient->Name = L"TrackBar_TyreDynamicFrictionCoefficient";
			this->TrackBar_TyreDynamicFrictionCoefficient->Size = System::Drawing::Size(328, 45);
			this->TrackBar_TyreDynamicFrictionCoefficient->TabIndex = 45;
			this->TrackBar_TyreDynamicFrictionCoefficient->TickFrequency = 50;
			this->TrackBar_TyreDynamicFrictionCoefficient->Value = 100;
			this->TrackBar_TyreDynamicFrictionCoefficient->Scroll += gcnew System::EventHandler(this, &MainForm::TrackBar_TyreDynamicFrictionCoefficient_Scroll);
			// 
			// TextBox_TyreDynamicFrictionCoefficient
			// 
			this->TextBox_TyreDynamicFrictionCoefficient->Font = (gcnew System::Drawing::Font(L"Arial", 12, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->TextBox_TyreDynamicFrictionCoefficient->ImeMode = System::Windows::Forms::ImeMode::Disable;
			this->TextBox_TyreDynamicFrictionCoefficient->Location = System::Drawing::Point(607, 234);
			this->TextBox_TyreDynamicFrictionCoefficient->MaxLength = 3;
			this->TextBox_TyreDynamicFrictionCoefficient->Name = L"TextBox_TyreDynamicFrictionCoefficient";
			this->TextBox_TyreDynamicFrictionCoefficient->ShortcutsEnabled = false;
			this->TextBox_TyreDynamicFrictionCoefficient->Size = System::Drawing::Size(36, 26);
			this->TextBox_TyreDynamicFrictionCoefficient->TabIndex = 46;
			this->TextBox_TyreDynamicFrictionCoefficient->Text = L"100";
			this->TextBox_TyreDynamicFrictionCoefficient->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MainForm::TextBox_NumOnly_KeyPress);
			this->TextBox_TyreDynamicFrictionCoefficient->Leave += gcnew System::EventHandler(this, &MainForm::TextBox_TyreDynamicFrictionCoefficient_Leave);
			// 
			// FFBMonitorButton
			// 
			this->FFBMonitorButton->Font = (gcnew System::Drawing::Font(L"BIZ UDPゴシック", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(128)));
			this->FFBMonitorButton->Location = System::Drawing::Point(565, 55);
			this->FFBMonitorButton->Name = L"FFBMonitorButton";
			this->FFBMonitorButton->Size = System::Drawing::Size(94, 24);
			this->FFBMonitorButton->TabIndex = 48;
			this->FFBMonitorButton->Text = L"FFBモニター";
			this->FFBMonitorButton->UseVisualStyleBackColor = true;
			this->FFBMonitorButton->Click += gcnew System::EventHandler(this, &MainForm::FFBMonitorButton_Click);
			// 
			// TrackBar_RotateForce
			// 
			this->TrackBar_RotateForce->LargeChange = 50;
			this->TrackBar_RotateForce->Location = System::Drawing::Point(5, 373);
			this->TrackBar_RotateForce->Maximum = 10000;
			this->TrackBar_RotateForce->Name = L"TrackBar_RotateForce";
			this->TrackBar_RotateForce->Size = System::Drawing::Size(328, 45);
			this->TrackBar_RotateForce->SmallChange = 10;
			this->TrackBar_RotateForce->TabIndex = 50;
			this->TrackBar_RotateForce->TickFrequency = 1000;
			this->TrackBar_RotateForce->Value = 5000;
			this->TrackBar_RotateForce->Scroll += gcnew System::EventHandler(this, &MainForm::TrackBar_RotateForce_Scroll);
			// 
			// TextBox_RotateForce
			// 
			this->TextBox_RotateForce->Font = (gcnew System::Drawing::Font(L"Arial", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->TextBox_RotateForce->ImeMode = System::Windows::Forms::ImeMode::Disable;
			this->TextBox_RotateForce->Location = System::Drawing::Point(271, 347);
			this->TextBox_RotateForce->MaxLength = 5;
			this->TextBox_RotateForce->Name = L"TextBox_RotateForce";
			this->TextBox_RotateForce->ShortcutsEnabled = false;
			this->TextBox_RotateForce->Size = System::Drawing::Size(56, 26);
			this->TextBox_RotateForce->TabIndex = 51;
			this->TextBox_RotateForce->Text = L"0";
			this->TextBox_RotateForce->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MainForm::TextBox_NumOnly_KeyPress);
			this->TextBox_RotateForce->Leave += gcnew System::EventHandler(this, &MainForm::TextBox_RotateForce_Leave);
			// 
			// TrackBar_GripFriction
			// 
			this->TrackBar_GripFriction->LargeChange = 50;
			this->TrackBar_GripFriction->Location = System::Drawing::Point(340, 316);
			this->TrackBar_GripFriction->Maximum = 10000;
			this->TrackBar_GripFriction->Name = L"TrackBar_GripFriction";
			this->TrackBar_GripFriction->Size = System::Drawing::Size(328, 45);
			this->TrackBar_GripFriction->SmallChange = 10;
			this->TrackBar_GripFriction->TabIndex = 53;
			this->TrackBar_GripFriction->TickFrequency = 1000;
			this->TrackBar_GripFriction->Value = 5000;
			this->TrackBar_GripFriction->Scroll += gcnew System::EventHandler(this, &MainForm::TrackBar_GripFriction_Scroll);
			// 
			// TextBox_GripFriction
			// 
			this->TextBox_GripFriction->Font = (gcnew System::Drawing::Font(L"Arial", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->TextBox_GripFriction->ImeMode = System::Windows::Forms::ImeMode::Disable;
			this->TextBox_GripFriction->Location = System::Drawing::Point(603, 290);
			this->TextBox_GripFriction->MaxLength = 5;
			this->TextBox_GripFriction->Name = L"TextBox_GripFriction";
			this->TextBox_GripFriction->ShortcutsEnabled = false;
			this->TextBox_GripFriction->Size = System::Drawing::Size(56, 26);
			this->TextBox_GripFriction->TabIndex = 54;
			this->TextBox_GripFriction->Text = L"0";
			this->TextBox_GripFriction->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MainForm::TextBox_NumOnly_KeyPress);
			this->TextBox_GripFriction->Leave += gcnew System::EventHandler(this, &MainForm::TextBox_GripFriction_Leave);
			// 
			// TrackBar_ForceScale
			// 
			this->TrackBar_ForceScale->LargeChange = 50;
			this->TrackBar_ForceScale->Location = System::Drawing::Point(340, 203);
			this->TrackBar_ForceScale->Maximum = 300;
			this->TrackBar_ForceScale->Name = L"TrackBar_ForceScale";
			this->TrackBar_ForceScale->Size = System::Drawing::Size(328, 45);
			this->TrackBar_ForceScale->TabIndex = 55;
			this->TrackBar_ForceScale->TickFrequency = 100;
			this->TrackBar_ForceScale->Value = 100;
			this->TrackBar_ForceScale->Scroll += gcnew System::EventHandler(this, &MainForm::TrackBar_ForceScale_Scroll);
			// 
			// TextBox_ForceScale
			// 
			this->TextBox_ForceScale->Font = (gcnew System::Drawing::Font(L"Arial", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->TextBox_ForceScale->ImeMode = System::Windows::Forms::ImeMode::Disable;
			this->TextBox_ForceScale->Location = System::Drawing::Point(607, 177);
			this->TextBox_ForceScale->MaxLength = 3;
			this->TextBox_ForceScale->Name = L"TextBox_ForceScale";
			this->TextBox_ForceScale->ShortcutsEnabled = false;
			this->TextBox_ForceScale->Size = System::Drawing::Size(36, 26);
			this->TextBox_ForceScale->TabIndex = 58;
			this->TextBox_ForceScale->Text = L"300";
			this->TextBox_ForceScale->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MainForm::TextBox_NumOnly_KeyPress);
			this->TextBox_ForceScale->Leave += gcnew System::EventHandler(this, &MainForm::TextBox_ForceScale_Leave);
			// 
			// TextBox_MinForce
			// 
			this->TextBox_MinForce->Font = (gcnew System::Drawing::Font(L"Arial", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->TextBox_MinForce->ImeMode = System::Windows::Forms::ImeMode::Disable;
			this->TextBox_MinForce->Location = System::Drawing::Point(271, 177);
			this->TextBox_MinForce->MaxLength = 5;
			this->TextBox_MinForce->Name = L"TextBox_MinForce";
			this->TextBox_MinForce->ShortcutsEnabled = false;
			this->TextBox_MinForce->Size = System::Drawing::Size(56, 26);
			this->TextBox_MinForce->TabIndex = 68;
			this->TextBox_MinForce->Text = L"0";
			this->TextBox_MinForce->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MainForm::TextBox_NumOnly_KeyPress);
			this->TextBox_MinForce->Leave += gcnew System::EventHandler(this, &MainForm::TextBox_MinForce_Leave);
			// 
			// TrackBar_MinForce
			// 
			this->TrackBar_MinForce->LargeChange = 50;
			this->TrackBar_MinForce->Location = System::Drawing::Point(5, 203);
			this->TrackBar_MinForce->Maximum = 10000;
			this->TrackBar_MinForce->Name = L"TrackBar_MinForce";
			this->TrackBar_MinForce->Size = System::Drawing::Size(328, 45);
			this->TrackBar_MinForce->SmallChange = 10;
			this->TrackBar_MinForce->TabIndex = 66;
			this->TrackBar_MinForce->TickFrequency = 1000;
			this->TrackBar_MinForce->Value = 2000;
			this->TrackBar_MinForce->Scroll += gcnew System::EventHandler(this, &MainForm::TrackBar_MinForce_Scroll);
			// 
			// TextBox_MaxTyreAngle
			// 
			this->TextBox_MaxTyreAngle->Font = (gcnew System::Drawing::Font(L"Arial", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->TextBox_MaxTyreAngle->ImeMode = System::Windows::Forms::ImeMode::Disable;
			this->TextBox_MaxTyreAngle->Location = System::Drawing::Point(525, 518);
			this->TextBox_MaxTyreAngle->MaxLength = 6;
			this->TextBox_MaxTyreAngle->Name = L"TextBox_MaxTyreAngle";
			this->TextBox_MaxTyreAngle->ShortcutsEnabled = false;
			this->TextBox_MaxTyreAngle->Size = System::Drawing::Size(56, 26);
			this->TextBox_MaxTyreAngle->TabIndex = 71;
			this->TextBox_MaxTyreAngle->Text = L"0";
			this->TextBox_MaxTyreAngle->TextChanged += gcnew System::EventHandler(this, &MainForm::TextBox_MaxTyreAngle_TextChanged);
			this->TextBox_MaxTyreAngle->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MainForm::TextBox_FloatOnly_KeyPress);
			this->TextBox_MaxTyreAngle->Leave += gcnew System::EventHandler(this, &MainForm::TextBox_MaxTyreAngle_Leave);
			// 
			// TrackBar_DeadZoneInside
			// 
			this->TrackBar_DeadZoneInside->LargeChange = 10;
			this->TrackBar_DeadZoneInside->Location = System::Drawing::Point(5, 430);
			this->TrackBar_DeadZoneInside->Maximum = 10000;
			this->TrackBar_DeadZoneInside->Name = L"TrackBar_DeadZoneInside";
			this->TrackBar_DeadZoneInside->Size = System::Drawing::Size(328, 45);
			this->TrackBar_DeadZoneInside->TabIndex = 76;
			this->TrackBar_DeadZoneInside->TickFrequency = 2000;
			this->TrackBar_DeadZoneInside->Scroll += gcnew System::EventHandler(this, &MainForm::TrackBar_DeadZoneInside_Scroll);
			// 
			// TextBox_DeadZoneInside
			// 
			this->TextBox_DeadZoneInside->Font = (gcnew System::Drawing::Font(L"Arial", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->TextBox_DeadZoneInside->ImeMode = System::Windows::Forms::ImeMode::Disable;
			this->TextBox_DeadZoneInside->Location = System::Drawing::Point(263, 404);
			this->TextBox_DeadZoneInside->MaxLength = 6;
			this->TextBox_DeadZoneInside->Name = L"TextBox_DeadZoneInside";
			this->TextBox_DeadZoneInside->ShortcutsEnabled = false;
			this->TextBox_DeadZoneInside->Size = System::Drawing::Size(48, 26);
			this->TextBox_DeadZoneInside->TabIndex = 77;
			this->TextBox_DeadZoneInside->Text = L"50.28";
			this->TextBox_DeadZoneInside->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MainForm::TextBox_FloatOnly_KeyPress);
			this->TextBox_DeadZoneInside->Leave += gcnew System::EventHandler(this, &MainForm::TextBox_DeadZoneInside_Leave);
			// 
			// TrackBar_SoftLockForce
			// 
			this->TrackBar_SoftLockForce->LargeChange = 50;
			this->TrackBar_SoftLockForce->Location = System::Drawing::Point(5, 544);
			this->TrackBar_SoftLockForce->Maximum = 10000;
			this->TrackBar_SoftLockForce->Name = L"TrackBar_SoftLockForce";
			this->TrackBar_SoftLockForce->Size = System::Drawing::Size(328, 45);
			this->TrackBar_SoftLockForce->SmallChange = 10;
			this->TrackBar_SoftLockForce->TabIndex = 80;
			this->TrackBar_SoftLockForce->TickFrequency = 1000;
			this->TrackBar_SoftLockForce->Value = 5000;
			this->TrackBar_SoftLockForce->Scroll += gcnew System::EventHandler(this, &MainForm::TrackBar_SoftLockForce_Scroll);
			// 
			// TextBox_SoftLockForce
			// 
			this->TextBox_SoftLockForce->Font = (gcnew System::Drawing::Font(L"Arial", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->TextBox_SoftLockForce->ImeMode = System::Windows::Forms::ImeMode::Disable;
			this->TextBox_SoftLockForce->Location = System::Drawing::Point(271, 518);
			this->TextBox_SoftLockForce->MaxLength = 5;
			this->TextBox_SoftLockForce->Name = L"TextBox_SoftLockForce";
			this->TextBox_SoftLockForce->ShortcutsEnabled = false;
			this->TextBox_SoftLockForce->Size = System::Drawing::Size(56, 26);
			this->TextBox_SoftLockForce->TabIndex = 81;
			this->TextBox_SoftLockForce->Text = L"0";
			this->TextBox_SoftLockForce->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MainForm::TextBox_NumOnly_KeyPress);
			this->TextBox_SoftLockForce->Leave += gcnew System::EventHandler(this, &MainForm::TextBox_SoftLockForce_Leave);
			// 
			// TextBox_DeadZoneOutside
			// 
			this->TextBox_DeadZoneOutside->Font = (gcnew System::Drawing::Font(L"Arial", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->TextBox_DeadZoneOutside->ImeMode = System::Windows::Forms::ImeMode::Disable;
			this->TextBox_DeadZoneOutside->Location = System::Drawing::Point(263, 461);
			this->TextBox_DeadZoneOutside->MaxLength = 6;
			this->TextBox_DeadZoneOutside->Name = L"TextBox_DeadZoneOutside";
			this->TextBox_DeadZoneOutside->ShortcutsEnabled = false;
			this->TextBox_DeadZoneOutside->Size = System::Drawing::Size(48, 26);
			this->TextBox_DeadZoneOutside->TabIndex = 84;
			this->TextBox_DeadZoneOutside->Text = L"50.28";
			this->TextBox_DeadZoneOutside->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MainForm::TextBox_FloatOnly_KeyPress);
			this->TextBox_DeadZoneOutside->Leave += gcnew System::EventHandler(this, &MainForm::TextBox_DeadZoneOutside_Leave);
			// 
			// TrackBar_DeadZoneOutside
			// 
			this->TrackBar_DeadZoneOutside->LargeChange = 10;
			this->TrackBar_DeadZoneOutside->Location = System::Drawing::Point(5, 487);
			this->TrackBar_DeadZoneOutside->Maximum = 10000;
			this->TrackBar_DeadZoneOutside->Name = L"TrackBar_DeadZoneOutside";
			this->TrackBar_DeadZoneOutside->RightToLeft = System::Windows::Forms::RightToLeft::Yes;
			this->TrackBar_DeadZoneOutside->Size = System::Drawing::Size(328, 45);
			this->TrackBar_DeadZoneOutside->TabIndex = 83;
			this->TrackBar_DeadZoneOutside->TickFrequency = 2000;
			this->TrackBar_DeadZoneOutside->Scroll += gcnew System::EventHandler(this, &MainForm::TrackBar_DeadZoneOutside_Scroll);
			// 
			// TrackBar_MaxTyreAngle
			// 
			this->TrackBar_MaxTyreAngle->LargeChange = 50;
			this->TrackBar_MaxTyreAngle->Location = System::Drawing::Point(340, 544);
			this->TrackBar_MaxTyreAngle->Maximum = 10000;
			this->TrackBar_MaxTyreAngle->Name = L"TrackBar_MaxTyreAngle";
			this->TrackBar_MaxTyreAngle->Size = System::Drawing::Size(328, 45);
			this->TrackBar_MaxTyreAngle->SmallChange = 10;
			this->TrackBar_MaxTyreAngle->TabIndex = 86;
			this->TrackBar_MaxTyreAngle->TickFrequency = 1000;
			this->TrackBar_MaxTyreAngle->Value = 10000;
			this->TrackBar_MaxTyreAngle->Scroll += gcnew System::EventHandler(this, &MainForm::TrackBar_MaxTyreAngle_Scroll);
			// 
			// TyreMonitorButton
			// 
			this->TyreMonitorButton->Font = (gcnew System::Drawing::Font(L"BIZ UDPゴシック", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(128)));
			this->TyreMonitorButton->Location = System::Drawing::Point(469, 55);
			this->TyreMonitorButton->Name = L"TyreMonitorButton";
			this->TyreMonitorButton->Size = System::Drawing::Size(94, 24);
			this->TyreMonitorButton->TabIndex = 89;
			this->TyreMonitorButton->Text = L"タイヤモニター";
			this->TyreMonitorButton->UseVisualStyleBackColor = true;
			this->TyreMonitorButton->Click += gcnew System::EventHandler(this, &MainForm::TyreMonitorButton_Click);
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::Window;
			this->ClientSize = System::Drawing::Size(672, 655);
			this->Controls->Add(this->TyreMonitorButton);
			this->Controls->Add(this->TyreTypeButton);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->TextBox_DeadZoneOutside);
			this->Controls->Add(this->Text_DeadZoneOutside);
			this->Controls->Add(this->Text_DeadZoneOutside_Unit);
			this->Controls->Add(this->TextBox_SoftLockForce);
			this->Controls->Add(this->Text_SoftLockForce);
			this->Controls->Add(this->TextBox_DeadZoneInside);
			this->Controls->Add(this->Text_DeadZoneInside);
			this->Controls->Add(this->Text_DeadZoneInside_Unit);
			this->Controls->Add(this->CheckBox_InvertFFB);
			this->Controls->Add(this->Text_MaxTyreAngleDeg);
			this->Controls->Add(this->Text_MaxTyreAngle_Unit);
			this->Controls->Add(this->TextBox_MaxTyreAngle);
			this->Controls->Add(this->Text_MaxTyreAngle);
			this->Controls->Add(this->TextBox_MinForce);
			this->Controls->Add(this->Text_MinForce);
			this->Controls->Add(this->AxisList);
			this->Controls->Add(this->Text_Axis);
			this->Controls->Add(this->DeviceList);
			this->Controls->Add(this->ChannelSelectBox);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->TextBox_ForceScale);
			this->Controls->Add(this->Text_ForceScale_Unit);
			this->Controls->Add(this->Text_ForceScale);
			this->Controls->Add(this->TextBox_GripFriction);
			this->Controls->Add(this->Text_GripFriction);
			this->Controls->Add(this->TextBox_RotateForce);
			this->Controls->Add(this->Text_RotateForce);
			this->Controls->Add(this->Text_InputAxis);
			this->Controls->Add(this->FFBMonitorButton);
			this->Controls->Add(this->TextBox_TyreDynamicFrictionCoefficient);
			this->Controls->Add(this->Text_TyreDynamicFrictionCoefficient);
			this->Controls->Add(this->TextBox_CenterFrictionZone);
			this->Controls->Add(this->Text_CenterFrictionZone);
			this->Controls->Add(this->TextBox_CenterFrictionMax);
			this->Controls->Add(this->Text_CenterFrictionMax);
			this->Controls->Add(this->FFBState_Text);
			this->Controls->Add(this->FFB_ON_Button);
			this->Controls->Add(this->FFB_OFF_Button);
			this->Controls->Add(this->ProfileReturnToDefaultButton);
			this->Controls->Add(this->ProfileCopyButton);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->ProfileDeleteButton);
			this->Controls->Add(this->ProfileRevertChangesButton);
			this->Controls->Add(this->ProfileSaveButton);
			this->Controls->Add(this->ProfileList);
			this->Controls->Add(this->Bar_InputAxis_Minus);
			this->Controls->Add(this->Bar_InputAxis_Plus);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->TextBox_StaticFriction);
			this->Controls->Add(this->Text_StaticFriction);
			this->Controls->Add(this->TextBox_MovementForce);
			this->Controls->Add(this->Text_MovementForce);
			this->Controls->Add(this->TextBox_MaxForce);
			this->Controls->Add(this->Text_MaxForce);
			this->Controls->Add(this->DeviceName);
			this->Controls->Add(this->Text_Device);
			this->Controls->Add(this->CheckBox_AlwaysOnTop);
			this->Controls->Add(this->Text_Online);
			this->Controls->Add(this->ResetButton);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->FFBState_Bar);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->Text_TyreDynamicFrictionCoefficient_Unit);
			this->Controls->Add(this->TrackBar_MaxTyreAngle);
			this->Controls->Add(this->TrackBar_SoftLockForce);
			this->Controls->Add(this->TrackBar_CenterFrictionZone);
			this->Controls->Add(this->TrackBar_DeadZoneOutside);
			this->Controls->Add(this->TrackBar_CenterFrictionMax);
			this->Controls->Add(this->TrackBar_DeadZoneInside);
			this->Controls->Add(this->TrackBar_StaticFriction);
			this->Controls->Add(this->TrackBar_RotateForce);
			this->Controls->Add(this->TrackBar_GripFriction);
			this->Controls->Add(this->TrackBar_MovementForce);
			this->Controls->Add(this->TrackBar_TyreDynamicFrictionCoefficient);
			this->Controls->Add(this->TrackBar_MaxForce);
			this->Controls->Add(this->TrackBar_ForceScale);
			this->Controls->Add(this->TrackBar_MinForce);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MaximizeBox = false;
			this->MaximumSize = System::Drawing::Size(688, 694);
			this->MinimumSize = System::Drawing::Size(688, 694);
			this->Name = L"MainForm";
			this->Text = L"StormworksFFB";
			this->TopMost = true;
			this->TransparencyKey = System::Drawing::Color::Lime;
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &MainForm::MainForm_FormClosing);
			this->FormClosed += gcnew System::Windows::Forms::FormClosedEventHandler(this, &MainForm::MainForm_FormClosed);
			this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->TrackBar_MaxForce))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->TrackBar_MovementForce))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->TrackBar_StaticFriction))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ChannelSelectBox))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->TrackBar_CenterFrictionMax))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->TrackBar_CenterFrictionZone))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->TrackBar_TyreDynamicFrictionCoefficient))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->TrackBar_RotateForce))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->TrackBar_GripFriction))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->TrackBar_ForceScale))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->TrackBar_MinForce))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->TrackBar_DeadZoneInside))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->TrackBar_SoftLockForce))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->TrackBar_DeadZoneOutside))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->TrackBar_MaxTyreAngle))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private: System::Void ResetButton_Click(System::Object^  sender, System::EventArgs^  e) {
		if (!Profile::IsSameProfile(appProfile, loadProfile)) {//保存されていない変更がある場合、確認ダイアログを表示する
			// メッセージボックスを表示する
			System::String^ message = "アプリケーションをリセットします。よろしいですか？\n※保存されていない変更は破棄されます。";
			System::String^ title = "アプリケーションのリセット";
			System::Windows::Forms::DialogResult dialogResult =
				System::Windows::Forms::MessageBox::Show(message, title, MessageBoxButtons::OKCancel, MessageBoxIcon::Warning);

			if (dialogResult != System::Windows::Forms::DialogResult::OK) {
				return;
			}
		}

		initialized = false;
		NetworkStart();
		initialized = DIInit(GetHInstance(), GetHWND());

		//過去情報のリセット
		preAxisIndex = 0;
		preDeviceIndex = 0;
		

		//最後に選択されていたプロファイル名、デバイス名、使用軸を保存しておく
		UpdateAppData(appData);
		SaveAppDataFile(appData);

		//変更を破棄
		appProfile = loadProfile;

		//appDataの読み込みと付随する初期化
		appData = LoadAppDataFile();
		DeviceListInit();
		AxisListInit();

		//プロファイルUIの初期化
		ProfileRevertChangesButton->Enabled = false;
		ProfileDeleteButton->Enabled = false;
		ProfileSaveButton->Enabled = false;
		ProfileListInit();

		//UIの初期化
		ProfileUIUpdate();
		ProfileButton_Update();
	}

	private: System::Void CheckBox_AlwaysOnTop_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
		this->TopMost = this->CheckBox_AlwaysOnTop->CheckState == CheckState::Checked;
	}

	private: System::Void CheckBox_InvertFFB_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
		appProfile.SetInvertFFB(CheckBox_InvertFFB->CheckState == CheckState::Checked);

		//ボタン更新
		ProfileButton_Update();
	}

	//メインフォーム読み込み時
	private: System::Void MainForm_Load(System::Object^  sender, System::EventArgs^  e) {
		initialized = false;
		NetworkStart();
		initialized = DIInit(GetHInstance(), GetHWND());
		//フォームのTopMostの初期設定にチェックボックスの内容を一致させる
		TopMost = false;
		CheckBox_AlwaysOnTop->CheckState = (TopMost) ? CheckState::Checked : CheckState::Unchecked;

		//appDataの読み込みと付随する初期化
		appData = LoadAppDataFile();
		DeviceListInit();
		AxisListInit();

		//プロファイルUIの初期化
		ProfileRevertChangesButton->Enabled = false;
		ProfileDeleteButton->Enabled = false;
		ProfileSaveButton->Enabled = false;
		ProfileListInit();

		//UIの初期化
		ProfileUIUpdate();
		ProfileButton_Update();

		//UI更新//
		try
		{
			this->Invoke(gcnew Action(this, &MainForm::UIUpdate));
		}
		catch (...)
		{
		}
		//UI更新//

		//タイマー起動
		timer = gcnew System::Timers::Timer();
		{
			timer->Interval = 16;
			timer->AutoReset = true;
			timer->Elapsed += gcnew System::Timers::ElapsedEventHandler(this, &MainForm::OnTick);
			timer->SynchronizingObject = this;
			timer->Start();
		}
	}

	private: System::Void MainForm_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e) {
		initialized = false;
		timer->Stop();
	}

	private: System::Void MainForm_FormClosed(System::Object^  sender, System::Windows::Forms::FormClosedEventArgs^  e) {
		//デフォルトかユーザープロファイル
		if (0 <= ProfileList->SelectedIndex && ProfileList->SelectedIndex < ProfileList->Items->Count - 1) {
			printf_s(msclr::interop::marshal_as<std::string>(ProfileList->SelectedItem->ToString()).c_str());
			//最後に選択されていたプロファイル名、デバイス名、使用軸を保存しておく(次回起動時に存在していれば読み込む)
			UpdateAppData(appData);
			SaveAppDataFile(appData);
		}

		DIRelease();
		NetworkClose();
	}

	private: System::Void NetworkStart() {
		id_max = 0;//最新の情報のid番号

		NetworkClose();

		for (int i = 0; i < channel_max; ++i) {
			// WinSockの初期化処理(Version 2.0)
			WSAStartup(MAKEWORD(2, 0), &wsa_data[i]);

			memset(&src_addr[i], 0, sizeof(src_addr[i]));
			src_addr[i].sin_port = htons(port_number + i);
			src_addr[i].sin_family = AF_INET;
			//src_addr[i].sin_addr.s_addr = inet_addr("127.0.0.1");
			InetPtonA(src_addr[i].sin_family, "127.0.0.1", &src_addr[i].sin_addr.S_un.S_addr);

			// AF_INETはipv4のIPプロトコル & SOCK_STREAMはTCPプロトコル
			src_socket[i] = socket(AF_INET, SOCK_STREAM, 0);

			// サーバ側のソケットを特定のIPアドレスとポートに紐付ける
			if (bind(src_socket[i], (struct sockaddr *) &src_addr[i], sizeof(src_addr[i])) == SOCKET_ERROR) {
				auto e = WSAGetLastError();
				int breakpoint = 0;
			}

			u_long val = 1;
			ioctlsocket(src_socket[i], FIONBIO, &val);

			// 接続の待受を開始する
			if (listen(src_socket[i], 10) == SOCKET_ERROR) {
				auto e = WSAGetLastError();
				int breakpoint = 0;
			}

			dst_socket[i] = accept(src_socket[i], (struct sockaddr *) &dst_addr[i], &dst_addr_size);
		}
	}

	private: System::Void NetworkClose() {
		for (int i = 0; i < channel_max; ++i) {
			closesocket(src_socket[i]);
			closesocket(dst_socket[i]);
		}

		WSACleanup();
	}
			 
	public: System::Void OnTick(System::Object^ obj, System::Timers::ElapsedEventArgs^ args) {
		if (!initialized) {
			return;
		}

		//FFB用通信//
		for (int i = 0; i < channel_max; ++i) {
			std::string str = "";
			// クライアントからの接続を受信する
			if (dst_socket[i] == INVALID_SOCKET) {
				dst_socket[i] = accept(src_socket[i], (struct sockaddr *) &dst_addr[i], &dst_addr_size);
			}
			if (dst_socket[i] == INVALID_SOCKET) {
				auto e = WSAGetLastError();
				int breakpoint = 0;
			}
			else
			{
				while (true) {

					int recv_result = recv(dst_socket[i], recv_buf[i], sizeof(char) * 256, 0);
					if (recv_result == 0 || recv_result == -1) {

						if (recv_result == 0) {
							closesocket(dst_socket[i]);
							dst_socket[i] = accept(src_socket[i], (struct sockaddr *) &dst_addr, &dst_addr_size);

							continue;
						}
						if (recv_result == -1) {
							int err = errno;
							int stop = 0;
							break;
						}
					}
					else
					{
						std::string str = std::string(recv_buf[i]);

						//受信成功の合図として文字列を送る
						send(dst_socket[i], "ffb", sizeof(char) * 4, 0);
						//一度ソケットをクローズして接続しなおす(これをしないと1秒間ソケットがロックされてしまう)
						closesocket(dst_socket[i]);
						dst_socket[i] = accept(src_socket[i], (struct sockaddr *) &dst_addr[i], &dst_addr_size);

						//受信したいチャンネルでなければこれ以上の処理はいらない
						if (i != channel) {
							continue;
						}

						timeoutTimer = timeoutTime;

						if (str.find(std::string("FFB_data=")) != std::string::npos) {
							std::string ffb_str = "";

							unsigned int start = (unsigned int)str.find(std::string("FFB_data=")) + 9;
							int end = (int)str.find(std::string("|END|"));
							if (end != std::string::npos) {
								//FFB用のデータのみの文字列を抽出する
								int len = end - start;
								ffb_str = str.substr(start, len);
							}
							start = 0;

							int id = GetParamInt(ffb_str, start);

							if (9000 < id_max) {
								if (id_max < id) {
									id_max = id;
								}
								else if (id < 1000) {//idの折り返し
									id_max = id;
								}
							}
							else {
								if (id_max < id) {
									id_max = id;
								}
							}
							if (id_max != id) {
								//break;
								continue;
							}

							carState.tireOnGround[LEFT] = (GetParamInt(ffb_str, start) == 0) ? false : true;
							carState.tireOnGround[RIGHT] = (GetParamInt(ffb_str, start) == 0) ? false : true;
							carState.tireSpeed[LEFT] = GetParamFloat(ffb_str, start);
							carState.tireSpeed[RIGHT] = GetParamFloat(ffb_str, start);
							carState.bodySpeedX[LEFT] = GetParamFloat(ffb_str, start);
							carState.bodySpeedX[RIGHT] = GetParamFloat(ffb_str, start);
							carState.bodySpeedZ[LEFT] = GetParamFloat(ffb_str, start);
							carState.bodySpeedZ[RIGHT] = GetParamFloat(ffb_str, start);
							carState.bodyRotateY[LEFT] = GetParamFloat(ffb_str, start);
							carState.bodyRotateY[RIGHT] = GetParamFloat(ffb_str, start);
							carState.ackermannAnglePer = GetParamFloat(ffb_str, start);
							carState.wheelbase = GetParamFloat(ffb_str, start);
							carState.tread = GetParamFloat(ffb_str, start);
						}
					}
				}
			}
		}
		//FFB用通信//
		bool isEnableGamePad = DIGetGamePadState(usingDeviceDID, diJoyState);

		//通信がない間はFFBを切ってidをリセットする
		if (timeoutTimer <= 0) {
			id_max = 0;
			carState.Reset();
			for (int i = 0; i < AXIS::MAX; ++i) {
				FFBReset(usingDeviceDID, i);
			}
		}
		
		FFBUpdate(usingDeviceDID, carState, diJoyState, usingAxisIndex, ffbBootCount / 60.f);

		//UI更新//
		try
		{
			this->Invoke(gcnew Action(this, &MainForm::UIUpdate));
		}
		catch (...)
		{
		}
		//UI更新//

		if (timeoutTimer == timeoutTime)
		{
			TPS = 60.f / tickCount;
			tickCount = 0;
		}

		if (ffbBoot) {
			ffbBootCount++;
		}
		ffbBootCount = min(ffbBootCount, 60);
		tickCount++;
		timeoutTimer = max(timeoutTimer - 1, 0);

		preDiJoyState = diJoyState;
	}

	private: System::Void UIUpdate() {
		//GT Force Proでの入力
		//diJoyState.lX;//ハンドル
		//diJoyState.lY;//アクセル
		//diJoyState.lRz;//ブレーキ
		LONG input = diJoyState.lX;
		LONG preInput = preDiJoyState.lX;
		switch (usingAxisIndex) {
		case 1:
			input = diJoyState.lY;
			preInput = preDiJoyState.lY;
			break;
		case 2:
			input = diJoyState.lZ;
			preInput = preDiJoyState.lZ;
			break;
		case 3:
			input = diJoyState.lRx;
			preInput = preDiJoyState.lRx;
			break;
		case 4:
			input = diJoyState.lRy;
			preInput = preDiJoyState.lRy;
			break;
		case 5:
			input = diJoyState.lRz;
			preInput = preDiJoyState.lRz;
			break;
		}

		Text_InputAxis->Text = input.ToString();
		//FFBモニター
		FFBMonitor_Input_Axis = input;

		//ゲージの更新
		Bar_InputAxis_Plus->Maximum += 1;
		Bar_InputAxis_Plus->Value = Bar_InputAxis_Plus->Maximum;
		Bar_InputAxis_Plus->Value = min(max(input, 0), Bar_InputAxis_Plus->Maximum - 1);
		Bar_InputAxis_Plus->Maximum -= 1;
		Bar_InputAxis_Minus->Maximum += 1;
		Bar_InputAxis_Minus->Value = Bar_InputAxis_Minus->Maximum;
		Bar_InputAxis_Minus->Value = min(max(-input, 0), Bar_InputAxis_Minus->Maximum - 1);
		Bar_InputAxis_Minus->Maximum -= 1;

		bool isOnline = false;

		if (0 < timeoutTimer) {
			Text_Online->Text = "Online";
			Text_Online->ForeColor = System::Drawing::SystemColors::ControlText;
			isOnline = true;
		}
		else {
			Text_Online->Text = "Offline";
			Text_Online->ForeColor = System::Drawing::SystemColors::ControlDark;

			ffbBootCount = 0;
			FFB_Active_Text_Update();
		}

		if (ffbBootCount < 60) {
			FFBState_Bar->Maximum += 1;
			FFBState_Bar->Value = FFBState_Bar->Maximum;
			FFBState_Bar->Value = (int)(ffbBootCount / 60.f * FFBState_Bar->Maximum);
			FFBState_Bar->Maximum -= 1;
		}
		else if (ffbBootCount == 60) {
			if (isOnline) {
				//流れるアニメーションを有効にする
				FFBState_Bar->Value = FFBState_Bar->Maximum;
				FFBState_Bar->Value -= 1;
			}
			else {
				FFBState_Bar->Maximum += 1;
				FFBState_Bar->Value = FFBState_Bar->Maximum;
				FFBState_Bar->Value -= 1;
				FFBState_Bar->Maximum -= 1;
			}
			FFBState_Text->Text = "FFB Active";
		}
	}

	//アルゴリズム：タイヤと進行方向の関係でFFBを生成する
	//private: System::Void FFBUpdate(DIDEV did, CarState carState, DIJOYSTATE diJoyState, float ffb_multiply) {
	//	ffb_multiply = min(max(ffb_multiply, 0), 1);
	//
	//	LONG combined_centerOffset = 0;
	//
	//	{//SpringForce
	//		LONG centerOffset[2] = { 0 };
	//		LONG saturation[2] = { 0 };
	//		LONG coefficient[2] = { 0 };
	//		LONG centering = 0;
	//
	//		for (int i = 0; i < 2; ++i) {//i = LEFT, RIGHT
	//			if (!carState.tireOnGround[i]) { continue; }
	//
	//			float maxTireAngle = 1;//デフォルトのタイヤの最大角(単位:rad)
	//			//(オプションで変更できるようにしたい)
	//
	//			//centerOffset
	//			float driftAngle = Math::Atan2(carState.bodySpeedX[i], carState.bodySpeedZ[i]);
	//			centerOffset[i] = min(max(driftAngle, -maxTireAngle), maxTireAngle) / maxTireAngle * 10000;
	//
	//			//saturation and coefficient
	//			float bodySpeed_Abs = Math::Sqrt((carState.bodySpeedX[i] * carState.bodySpeedX[i]) + (carState.bodySpeedZ[i] * carState.bodySpeedZ[i]));
	//			float tireAngle = (float)diJoyState.lX / DIAXIS_RANGE_MAX * maxTireAngle;
	//			if (0 < carState.ackermannAnglePer && 0 < carState.wheelbase && 0 < carState.tread) {
	//				if ((i == LEFT && 0 < diJoyState.lX) || (i == RIGHT && diJoyState.lX < 0)) {
	//					tireAngle = Ackermann(tireAngle, carState.wheelbase, carState.tread, carState.ackermannAnglePer);
	//				}
	//			}
	//			float tireVecX = Math::Sin(tireAngle) * carState.tireSpeed[i];
	//			float tireVecZ = Math::Cos(tireAngle) * carState.tireSpeed[i];
	//			float tire2bodyVec = Math::Sqrt(Math::Pow(carState.bodySpeedX[i] - tireVecX, 2) + Math::Pow(carState.bodySpeedZ[i] - tireVecZ, 2));
	//			float coefficientPer = Math::Sin(driftAngle - tireAngle);
	//			float tireGrip = 0;
	//			if (tire2bodyVec < (4.92f * 3.6f)) {//4.92m/s未満
	//				tireGrip = 1;
	//			}
	//			else {
	//				tireGrip = appProfile.GetTyreDynamicFrictionCoefficient()/100.f;
	//				//tireGrip = max(tireGrip - coefficientPer, 0);
	//			}
	//
	//			//float paramScale = 1 / 30.f;
	//			float paramScale = 10.f;
	//			//coefficient[i] = bodySpeed_Abs * (appProfile.GetMovementForce() / 10000.f) * coefficientPer * tireGrip * paramScale * 10000;
	//			coefficient[i] = (appProfile.GetMovementForce() / 10000.f) * coefficientPer * tireGrip * min(Math::Abs(carState.bodySpeedX[i] - tireVecX) / (4.92f * 3.6f), 1) * 10000 * paramScale;
	//			saturation[i] = coefficient[i];
	//		}
	//
	//		//combine
	//		LONG effectMax = Math::Abs(coefficient[LEFT]) + Math::Abs(coefficient[RIGHT]);
	//		float effectPer[2] = { 0 };
	//		if (0 < effectMax) {
	//			effectPer[LEFT] = (float)Math::Abs(coefficient[LEFT]) / effectMax;
	//			effectPer[RIGHT] = (float)Math::Abs(coefficient[RIGHT]) / effectMax;
	//		}
	//		combined_centerOffset = min(max(centerOffset[RIGHT] - ((centerOffset[LEFT] - centerOffset[RIGHT]) * effectPer[LEFT]), -10000), 10000);
	//		LONG combined_saturation = min(max(saturation[LEFT] + saturation[RIGHT], 0), appProfile.GetMaxForce()) * ffb_multiply;
	//		LONG combined_coefficient = min(max(coefficient[LEFT] + coefficient[RIGHT], -appProfile.GetMaxForce()), appProfile.GetMaxForce()) * ffb_multiply;
	//
	//		//Update FFB
	//		//DISetFFB_Spring(did, combined_centerOffset, combined_saturation, combined_coefficient, centering);
	//		DISetFFB_Constant(did, combined_coefficient);
	//		//FFBモニター
	//		FFBMonitor_Spring = combined_coefficient;
	//	}
	//
	//	{//Damper
	//		//StaticDamper
	//		float bodySpeed_Abs[2] = { 0 };
	//		bodySpeed_Abs[LEFT] = Math::Sqrt((carState.bodySpeedX[LEFT] * carState.bodySpeedX[LEFT]) + (carState.bodySpeedZ[LEFT] * carState.bodySpeedZ[LEFT]));
	//		bodySpeed_Abs[RIGHT] = Math::Sqrt((carState.bodySpeedX[RIGHT] * carState.bodySpeedX[RIGHT]) + (carState.bodySpeedZ[RIGHT] * carState.bodySpeedZ[RIGHT]));
	//		float speed = 0;
	//		if (carState.tireOnGround[LEFT]) { speed = max(speed, bodySpeed_Abs[LEFT]); }
	//		if (carState.tireOnGround[RIGHT]) { speed = max(speed, bodySpeed_Abs[RIGHT]); }
	//		speed = min(speed, 1);//1 km/h でダンパーが軽くなる
	//
	//		LONG coefficient = (1 - speed) * appProfile.GetStaticDamper() * ffb_multiply;
	//		//FFBモニター
	//		FFBMonitor_Static_Dumper = coefficient;
	//
	//		//CenterDamper
	//		if (0 < appProfile.GetCenterDamperMax() && 0 < appProfile.GetCenterDamperZone()) {
	//			LONG diffHandle = combined_centerOffset - ((float)diJoyState.lX / DIAXIS_RANGE_MAX * 10000);
	//			float per = 1 - ((float)Math::Abs(diffHandle) / appProfile.GetCenterDamperZone());
	//			per = min(max(per, 0), 1);
	//
	//			coefficient += appProfile.GetCenterDamperMax() * per * ffb_multiply;
	//			//FFBモニター
	//			FFBMonitor_Center_Dumper = appProfile.GetCenterDamperMax() * per * ffb_multiply;
	//		}
	//
	//		coefficient = min(coefficient, appProfile.GetMaxForce());
	//
	//		DISetFFB_Damper(did, coefficient);
	//		//FFBモニター
	//		FFBMonitor_Total_Dumper = coefficient;
	//	}
	//}

	private: System::Void FFBReset(DIDEV did, int axis) {
		DISetFFB_Constant(did, (AXIS)axis, 0);
		DISetFFB_Friction(did, (AXIS)axis, 0);
		DISetFFB_Damper(did, (AXIS)axis, 0);
	}

	//アルゴリズム：タイヤの状態と移動ベクトルを元にFFBを生成する
	private: System::Void FFBUpdate(DIDEV did, CarState carState, DIJOYSTATE diJoyState, int axis, float ffb_multiply) {
		ffb_multiply = min(max(ffb_multiply, 0), 1);

		LONG input = 0;
		LONG preInput = 0;
		switch (axis) {
		case 0:
			input = diJoyState.lX;
			preInput = preDiJoyState.lX;
			break;
		case 1:
			input = diJoyState.lY;
			preInput = preDiJoyState.lY;
			break;
		case 2:
			input = diJoyState.lZ;
			preInput = preDiJoyState.lZ;
			break;
		case 3:
			input = diJoyState.lRx;
			preInput = preDiJoyState.lRx;
			break;
		case 4:
			input = diJoyState.lRy;
			preInput = preDiJoyState.lRy;
			break;
		case 5:
			input = diJoyState.lRz;
			preInput = preDiJoyState.lRz;
			break;
		}
		//FFB反転の適応
		if (appProfile.GetInvertFFB()) {
			input = -input;
			preInput = -preInput;
		}
	
		LONG combined_centerOffset = 0;

		//ExtendedCarState
		float gripSpeed = (4.92f * 3.6f);//4.92m/s
		float maxTireAngle = (appProfile.GetPivotWheelMode()) ? 
			(float)(appProfile.GetMaxTyreAngle() / 10000.f * (90 * Math::PI / 180.f)) : 
			(float)(appProfile.GetMaxTyreAngle() / 10000.f);//(単位:rad)
		float driftAngle[2] = { 0 };
		float bodySpeed_Abs[2] = { 0 };
		float tireAngle[2] = { 0 };
		float tireVecX[2] = { 0 };
		float tireVecZ[2] = { 0 };
		float tire2bodyVec[2] = { 0 };
		float maxGripAngle[2] = { 0 };
		float tireGrip[2] = { 1, 1 };
		for (int i = 0; i < 2; ++i) {//i = LEFT, RIGHT
			driftAngle[i] = (float)Math::Atan2(carState.bodySpeedX[i], carState.bodySpeedZ[i]);

			//bodySpeed_Abs
			bodySpeed_Abs[i] = (float)Math::Sqrt((carState.bodySpeedX[i] * carState.bodySpeedX[i]) + (carState.bodySpeedZ[i] * carState.bodySpeedZ[i]));

			//tireAngle
			if (0 < maxTireAngle && 0 < (DIAXIS_RANGE_MAX - appProfile.GetDeadZoneOutside())) {
				//デッドゾーン処理
				float DZAttachedMin = appProfile.GetDeadZoneInside() / 10000.f * DIAXIS_RANGE_MAX;
				float DZAttachedMax = DIAXIS_RANGE_MAX - (appProfile.GetDeadZoneOutside() / 10000.f * DIAXIS_RANGE_MAX);
				float input_deadzoneAttached = 0;
				if (0 < (DZAttachedMax - DZAttachedMin))
				{
					input_deadzoneAttached = (input < 0) ?
						-(max(-input - DZAttachedMin, 0) / (DZAttachedMax - DZAttachedMin)) :
						(max(input - DZAttachedMin, 0) / (DZAttachedMax - DZAttachedMin));
				}
				else if((DZAttachedMax - DZAttachedMin) == 0) {
					if (input < -DZAttachedMin) { input_deadzoneAttached = -1; }
					else if (-DZAttachedMin <= input && input <= DZAttachedMin) { input_deadzoneAttached = 0; }
					else { input_deadzoneAttached = 1; }
				}

				tireAngle[i] = min(max(input_deadzoneAttached, -1), 1) * maxTireAngle;
			}
			if ((i == LEFT && 0 < input) || (i == RIGHT && input < 0)) {
				tireAngle[i] = Ackermann(tireAngle[i], carState.wheelbase, carState.tread, carState.ackermannAnglePer);
			}
			
			//tireVec
			tireVecX[i] = (float)(Math::Sin(tireAngle[i]) * carState.tireSpeed[i]);
			tireVecZ[i] = (float)(Math::Cos(tireAngle[i]) * carState.tireSpeed[i]);

			//tire2bodyVec
			tire2bodyVec[i] = (float)Math::Sqrt(Math::Pow(carState.bodySpeedX[i] - tireVecX[i], 2) + Math::Pow(carState.bodySpeedZ[i] - tireVecZ[i], 2));

			//maxGripAngle
			maxGripAngle[i] = (float)Math::Atan2(gripSpeed, bodySpeed_Abs[i]);

			//tireGrip
			if (gripSpeed <= tire2bodyVec[i]) {
				tireGrip[i] = appProfile.GetTyreDynamicFrictionCoefficient() / 100.f;
			}
		}

		//タイヤモニター
		TyreMonitor_LeftTyreAngle = tireAngle[LEFT];
		TyreMonitor_RightTyreAngle = tireAngle[RIGHT];
	
		{//Spring
			LONG coefficient = 0;

			{//SpringForce
				LONG centerOffset[2] = { 0 };
				LONG saturation[2] = { 0 };
				LONG coefficient_[2] = { 0 };
				LONG centering = 0;

				for (int i = 0; i < 2; ++i) {//i = LEFT, RIGHT
					if (!carState.tireOnGround[i]) { continue; }

					//centerOffset
					if (0 < maxTireAngle) {
						centerOffset[i] = (LONG)(min(max(driftAngle[i], -maxTireAngle), maxTireAngle) / maxTireAngle * 10000);
					}

					//saturation and coefficient
					float coefficientPer = (float)min(max(Math::Sin(driftAngle[i] - tireAngle[i]), -Math::Sin(maxGripAngle[i])), Math::Sin(maxGripAngle[i]));
					//FFB反転の適応
					if (appProfile.GetInvertFFB()) {
						coefficientPer = -coefficientPer;
					}
					float coefficient_speed = (float)(((90 * Math::PI / 180.f) - Math::Atan2(gripSpeed, bodySpeed_Abs[i])) / (90 * Math::PI / 180.f));

					float paramScale = 5.f;
					coefficient_[i] = (LONG)(appProfile.GetMovementForce() * coefficient_speed * coefficientPer * tireGrip[i] * (appProfile.GetForceScale() / 100.f) * paramScale);
					saturation[i] = coefficient_[i];
				}
				
				//combine
				LONG effectMax = Math::Abs(coefficient_[LEFT]) + Math::Abs(coefficient_[RIGHT]);
				float effectPer[2] = { 0 };
				if (0 < effectMax) {
					effectPer[LEFT] = (float)Math::Abs(coefficient_[LEFT]) / effectMax;
					effectPer[RIGHT] = (float)Math::Abs(coefficient_[RIGHT]) / effectMax;
				}
				combined_centerOffset = (LONG)min(max(centerOffset[RIGHT] - ((centerOffset[LEFT] - centerOffset[RIGHT]) * effectPer[LEFT]), -10000), 10000);
				//FFB反転の適応
				if (appProfile.GetInvertFFB()) {
					combined_centerOffset = -combined_centerOffset;
				}
				LONG combined_saturation = (LONG)(min(max(saturation[LEFT] + saturation[RIGHT], 0), appProfile.GetMaxForce()) * ffb_multiply);
				LONG combined_coefficient = (coefficient_[LEFT] + coefficient_[RIGHT]);

				coefficient += combined_coefficient;

				//FFBモニター
				FFBMonitor_Movement_Force = combined_coefficient;
			}

			{//RotateForce
				LONG coefficient_[2] = { 0 };
				for (int i = 0; i < 2; ++i) {//i = LEFT, RIGHT
					if (!carState.tireOnGround[i]) { continue; }

					float paramScale = 6.f;
					coefficient_[i] = (LONG)(-carState.bodyRotateY[i] * appProfile.GetRotateForce() * tireGrip[i] * (appProfile.GetForceScale() / 100.f) * paramScale);

					//FFB反転の適応
					if (appProfile.GetInvertFFB()) {
						coefficient_[i] = -coefficient_[i];
					}

					coefficient += coefficient_[i];
				}
				//FFBモニター
				FFBMonitor_Rotate_Force = coefficient_[LEFT] + coefficient_[RIGHT];
			}

			//MinForceの適応
			if (0 < coefficient) {
				coefficient = (LONG)(appProfile.GetMinForce() + ((appProfile.GetMaxForce() - appProfile.GetMinForce()) * ((float)coefficient / appProfile.GetMaxForce())));
			}
			else if (coefficient < 0) {
				coefficient = (LONG)(-appProfile.GetMinForce() + ((appProfile.GetMaxForce() - appProfile.GetMinForce()) * ((float)coefficient / appProfile.GetMaxForce())));
			}

			//Update FFB
			coefficient = (LONG)(min(max(coefficient, -appProfile.GetMaxForce()), appProfile.GetMaxForce()) * ffb_multiply);

			{//SoftLockForce
				LONG input_ = input;
				LONG preInput_ = preInput;
				//FFB反転を無効化
				if (appProfile.GetInvertFFB()) {
					input_ = -input;
					preInput_ = -preInput;
				}
				int move = input_ - preInput_;
				if (DIAXIS_RANGE_MAX - appProfile.GetDeadZoneOutside() < input_) {
					coefficient = (LONG)min(coefficient, -appProfile.GetSoftLockForce() * min(max(std::powf((input_ - (DIAXIS_RANGE_MAX - appProfile.GetDeadZoneOutside())) / 200.f, 1.5) + (min(move, 0) / 200.f), 0), 1) * ffb_multiply);
				}
				if (input_ < DIAXIS_RANGE_MIN + appProfile.GetDeadZoneOutside()) {
					coefficient = (LONG)max(coefficient, appProfile.GetSoftLockForce() * min(max(std::powf((DIAXIS_RANGE_MIN + appProfile.GetDeadZoneOutside() - input_) / 200.f, 1.5) - (max(move, 0) / 200.f), 0), 1)  * ffb_multiply);
				}
				
			}
			
			DISetFFB_Constant(did, (AXIS)axis, coefficient);

			//FFBモニター
			FFBMonitor_Total_Direction_Force = coefficient;
		}
	
		{//Friction
			LONG coefficient = 0;

			{//GripFriction
				LONG coefficient_[2] = { 0 };
				for (int i = 0; i < 2; ++i) {//i = LEFT, RIGHT
					if (!carState.tireOnGround[i]) { continue; }

					coefficient_[i] = (LONG)(appProfile.GetGripFriction() / 2.f * (appProfile.GetForceScale() / 100.f) * tireGrip[i]);
					coefficient += coefficient_[i];
				}
				//FFBモニター
				FFBMonitor_Grip_Friction = coefficient_[LEFT] + coefficient_[RIGHT];
			}

			{//StaticFriction
				LONG coefficient_[2] = { 0 };
				for (int i = 0; i < 2; ++i) {//i = LEFT, RIGHT
					if (!carState.tireOnGround[i]) { continue; }

					float bodySpeed_Abs = 0;
					bodySpeed_Abs = (float)Math::Sqrt((carState.bodySpeedX[i] * carState.bodySpeedX[i]) + (carState.bodySpeedZ[i] * carState.bodySpeedZ[i]));
					float speed = bodySpeed_Abs;
					speed = min(speed, 10);//10 km/h でダンパーが軽くなる
					float per = (10 - speed) / 10.f;

					coefficient_[i] = (LONG)(per * appProfile.GetStaticFriction() / 2.f * (appProfile.GetForceScale() / 100.f) * tireGrip[i]);
					coefficient += coefficient_[i];
				}
				//FFBモニター
				FFBMonitor_Static_Friction = coefficient_[LEFT] + coefficient_[RIGHT];
			}
	
			{//CenterFriction
				LONG coefficient_[2] = { 0 };
				for (int i = 0; i < 2; ++i) {//i = LEFT, RIGHT
					if (!carState.tireOnGround[i]) { continue; }

					if (0 < appProfile.GetCenterFrictionMax() && 0 < appProfile.GetCenterFrictionZone()) {
						LONG diffHandle = combined_centerOffset - (LONG)((float)input / DIAXIS_RANGE_MAX * 10000);
						float per = 1 - ((float)Math::Abs(diffHandle) / appProfile.GetCenterFrictionZone());
						per = min(max(per, 0), 1);

						coefficient_[i] = (LONG)(appProfile.GetCenterFrictionMax() / 2.f * per * (appProfile.GetForceScale() / 100.f));
						coefficient += coefficient_[i];
					}
				}
				//FFBモニター
				FFBMonitor_Center_Friction = coefficient_[LEFT] + coefficient_[RIGHT];
			}
	
			coefficient = (LONG)(min(coefficient, appProfile.GetMaxForce()) * ffb_multiply);
	
			DISetFFB_Friction(did, (AXIS)axis, coefficient);
			//FFBモニター
			FFBMonitor_Total_Friction = coefficient;
		}
	}

	private: float Ackermann(float insideTireAngle, float wheelbase, float tread, float per)
	{
		per = min(max(per, 0), 1);
		float max = abs(insideTireAngle);

		float angle = 0;
		float min = 0;
		double insideTireAngle_tan = Math::Tan(abs(insideTireAngle));

		if (0 != wheelbase && 0 != tread && !isnan(insideTireAngle_tan)) {
			min = (float)Math::Atan(abs(wheelbase) / (abs(wheelbase) / abs(insideTireAngle_tan) + abs(tread)));
			//-min(x, lerp(x, sgn(x)*atan(abs(w) / (abs(w) / tan(abs(x)) + abs(z)*(x / x))), a / 100))
			//max(x, lerp(x, sgn(x)*atan(abs(w) / (abs(w) / tan(abs(x)) + abs(z)*(x / x))), a / 100))
			angle = max + (min - max) * per;
		}
		else {
			min = 0;
			angle = max + (min - max) * per;
		}

		return (0 < insideTireAngle) ? angle : -angle;
	}
			 
	private: std::string GetParamStr(const std::string &str, unsigned int &start) {
		//startが文字数をオーバーしている
		if (str.length() <= start) return "";

		int end = (int)str.find(std::string(","), start);

		//,が見つからない
		if (end == std::string::npos)return "";

		int len = end - start;
		std::string data = str.substr(start, len);
		start = end + 1;
		return data;
	}

	private: float GetParamFloat(const std::string &str, unsigned int &start) {
		return decompressFloat(GetParamStr(str, start));
	}

	private: int GetParamInt(const std::string &str, unsigned int &start) {
		return decompressInt(GetParamStr(str, start));
	}

	private: float decompressFloat(const std::string& compressed) {
		return decompressInt(compressed) / 10000000.f;//小数点以下7桁
	}

	private: int decompressInt(const std::string& compressed) {
		 std::string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
		 int base = (int)chars.length();
		 long long result = 0;
		 bool minus = false;

		 for (char c : compressed) {
			 if (c == '-') { minus = true; continue; }

			 result *= base;
			 size_t index = chars.find(c);
			 if (index == std::string::npos) {
				 return 0;
			 }
			 result += index;
		 }

		 return (minus) ? (int)-result : (int)result;
	}

	private: System::Void DeviceListInit() {
		DeviceList->Items->Clear();
		DeviceList->Items->Add("None");
		DeviceList->SelectedIndex = 0;//一度Noneにする

		int index = 0;
		int deviceCount = 0;
		for (int did = DID_GAMEPAD1; did < DID_MAX; ++did)
		{
			if (DIExistGamePad((DIDEV)did)) {
				DeviceList->Items->Add(DIGetGamePadName((DIDEV)did));
				deviceCount++;
				
				//初めに選択するデバイスを発見したらindexを保存しておく
				if (DIGetGamePadName_std((DIDEV)did) == appData.GetInitDeviceName()) {
					index = deviceCount;//デバイスは1から(0は"None")
				}
			}
		}

		DeviceList->SelectedIndex = index;
	}

	private: System::Void AxisListInit() {
		AxisList->SelectedIndex = appData.GetAxis(msclr::interop::marshal_as<std::string>(DeviceList->SelectedItem->ToString()));
	}

	private: System::Void UpdateAppData(AppData &appData) {
		//InitDataの更新
		appData.SetInitProfileName(msclr::interop::marshal_as<std::string>(ProfileList->SelectedItem->ToString()));
		if (0 < DeviceList->SelectedIndex) {//ゲームパッドを選択してる場合のみ上書き保存
			appData.SetInitDeviceName(msclr::interop::marshal_as<std::string>(DeviceList->SelectedItem->ToString()));
		}

		////AxisDataの更新(最後に選択されていたデバイスのみ)
		//デバイスの軸設定を保存
		if (0 < preDeviceIndex) {//接続されたデバイスを選択されている
			appData.SetAxis(msclr::interop::marshal_as<std::string>(DeviceList->SelectedItem->ToString()), AxisList->SelectedIndex);
		}
	}

	private: System::Void DeviceList_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
		FFB_OFF();

		//デバイスの軸設定を保存
		if (0 < preDeviceIndex) {//接続されたデバイスを選択されている
			appData.SetAxis(msclr::interop::marshal_as<std::string>(DeviceList->Items[preDeviceIndex]->ToString()), AxisList->SelectedIndex);
		}

		//DIDの設定
		int did_int = DID_NONE;
		if (0 < DeviceList->SelectedIndex) {
			did_int = DID_GAMEPAD1 + (DeviceList->SelectedIndex - 1);
		}
		usingDeviceDID = (DIDEV)did_int;

		//軸の変更
		int axis = appData.GetAxis(msclr::interop::marshal_as<std::string>(DeviceList->SelectedItem->ToString()));
		if (AxisList->SelectedIndex != axis) {
			AxisList->SelectedIndex = axis;
		}

		preDeviceIndex = DeviceList->SelectedIndex;
	}

	private: System::Void AxisList_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
		FFB_OFF();

		usingAxisIndex = AxisList->SelectedIndex;

		//FFBモニター
		FFBMonitor_Input_Axis_Name = msclr::interop::marshal_as<std::string>(AxisList->SelectedItem->ToString());

		preAxisIndex = AxisList->SelectedIndex;
	}

	private: System::Void TrackBar_MinForce_Scroll(System::Object^  sender, System::EventArgs^  e) {
		TrackBar_Scroll(TextBox_MinForce, TrackBar_MinForce);

		//MaxForceとの整合性を取る
		if (TrackBar_MaxForce->Value < TrackBar_MinForce->Value) {
			 TrackBar_MaxForce->Value = TrackBar_MinForce->Value;
			 TrackBar_Scroll(TextBox_MaxForce, TrackBar_MaxForce);
		}

		//OnTick内で使える変数に代入
		appProfile.SetMinForce(TrackBar_MinForce->Value);

		//FFBモニターは無し(不要)

		//ボタン更新
		ProfileButton_Update();
	}

	private: System::Void TextBox_MinForce_Leave(System::Object^  sender, System::EventArgs^  e) {
		TextBox_TextChanged(TextBox_MinForce, TrackBar_MinForce);

		//MaxForceとの整合性を取る
		if (TrackBar_MaxForce->Value < TrackBar_MinForce->Value) {
			TrackBar_MaxForce->Value = TrackBar_MinForce->Value;
			TrackBar_Scroll(TextBox_MaxForce, TrackBar_MaxForce);
		}

		//OnTick内で使える変数に代入
		appProfile.SetMinForce(TrackBar_MinForce->Value);

		//FFBモニターは無し(不要)

		//ボタン更新
		ProfileButton_Update();
	}

	private: System::Void TrackBar_MaxForce_Scroll(System::Object^  sender, System::EventArgs^  e) {
		TrackBar_Scroll(TextBox_MaxForce, TrackBar_MaxForce);

		//MinForceとの整合性を取る
		if (TrackBar_MaxForce->Value < TrackBar_MinForce->Value) {
			TrackBar_MinForce->Value = TrackBar_MaxForce->Value;
			TrackBar_Scroll(TextBox_MinForce, TrackBar_MinForce);
		}

		//OnTick内で使える変数に代入
		appProfile.SetMaxForce(TrackBar_MaxForce->Value);

		//FFBモニター
		FFBMonitor_MaxForce = TrackBar_MaxForce->Value;

		//ボタン更新
		ProfileButton_Update();
	}

	private: System::Void TextBox_MaxForce_Leave(System::Object^  sender, System::EventArgs^  e) {
		TextBox_TextChanged(TextBox_MaxForce, TrackBar_MaxForce);

		//MinForceとの整合性を取る
		if (TrackBar_MaxForce->Value < TrackBar_MinForce->Value) {
			TrackBar_MinForce->Value = TrackBar_MaxForce->Value;
			TrackBar_Scroll(TextBox_MinForce, TrackBar_MinForce);
		}

		//OnTick内で使える変数に代入
		appProfile.SetMaxForce(TrackBar_MaxForce->Value);

		//FFBモニター
		FFBMonitor_MaxForce = TrackBar_MaxForce->Value;

		//ボタン更新
		ProfileButton_Update();
	}

	private: System::Void TrackBar_DeadZoneInside_Scroll(System::Object^  sender, System::EventArgs^  e) {
		TrackBar_Scroll(TextBox_DeadZoneInside, TrackBar_DeadZoneInside, -2);

		//Outsideとの整合性を取る
		if (TrackBar_DeadZoneOutside->Maximum - TrackBar_DeadZoneOutside->Value < TrackBar_DeadZoneInside->Value) {
			TrackBar_DeadZoneOutside->Value = TrackBar_DeadZoneInside->Maximum - TrackBar_DeadZoneInside->Value;
			TrackBar_Scroll(TextBox_DeadZoneOutside, TrackBar_DeadZoneOutside, -2);
		}

		//OnTick内で使える変数に代入
		appProfile.SetDeadZoneInside(TrackBar_DeadZoneInside->Value);
		appProfile.SetDeadZoneOutside(TrackBar_DeadZoneOutside->Value);

		//ボタン更新
		ProfileButton_Update();
	}

	private: System::Void TextBox_DeadZoneInside_Leave(System::Object^  sender, System::EventArgs^  e) {
		TextBox_TextChanged(TextBox_DeadZoneInside, TrackBar_DeadZoneInside, 2);

		//Outsideとの整合性を取る
		if (TrackBar_DeadZoneOutside->Maximum - TrackBar_DeadZoneOutside->Value < TrackBar_DeadZoneInside->Value) {
			TrackBar_DeadZoneOutside->Value = TrackBar_DeadZoneInside->Maximum - TrackBar_DeadZoneInside->Value;
			TrackBar_Scroll(TextBox_DeadZoneOutside, TrackBar_DeadZoneOutside, -2);
		}

		//OnTick内で使える変数に代入
		appProfile.SetDeadZoneInside(TrackBar_DeadZoneInside->Value);
		appProfile.SetDeadZoneOutside(TrackBar_DeadZoneOutside->Value);

		//ボタン更新
		ProfileButton_Update();
	}

	private: System::Void TrackBar_DeadZoneOutside_Scroll(System::Object^  sender, System::EventArgs^  e) {
		TrackBar_Scroll(TextBox_DeadZoneOutside, TrackBar_DeadZoneOutside, -2);

		//Insideとの整合性を取る
		if (TrackBar_DeadZoneOutside->Maximum - TrackBar_DeadZoneOutside->Value < TrackBar_DeadZoneInside->Value) {
			TrackBar_DeadZoneInside->Value = TrackBar_DeadZoneOutside->Maximum - TrackBar_DeadZoneOutside->Value;
			TrackBar_Scroll(TextBox_DeadZoneInside, TrackBar_DeadZoneInside, -2);
		}

		//OnTick内で使える変数に代入
		appProfile.SetDeadZoneInside(TrackBar_DeadZoneInside->Value);
		appProfile.SetDeadZoneOutside(TrackBar_DeadZoneOutside->Value);

		//ボタン更新
		ProfileButton_Update();
	}

	private: System::Void TextBox_DeadZoneOutside_Leave(System::Object^  sender, System::EventArgs^  e) {
		TextBox_TextChanged(TextBox_DeadZoneOutside, TrackBar_DeadZoneOutside, 2);

		//Insideとの整合性を取る
		if (TrackBar_DeadZoneOutside->Maximum - TrackBar_DeadZoneOutside->Value < TrackBar_DeadZoneInside->Value) {
			TrackBar_DeadZoneInside->Value = TrackBar_DeadZoneOutside->Maximum - TrackBar_DeadZoneOutside->Value;
			TrackBar_Scroll(TextBox_DeadZoneInside, TrackBar_DeadZoneInside, -2);
		}

		//OnTick内で使える変数に代入
		appProfile.SetDeadZoneInside(TrackBar_DeadZoneInside->Value);
		appProfile.SetDeadZoneOutside(TrackBar_DeadZoneOutside->Value);

		//ボタン更新
		ProfileButton_Update();
	}

	private: System::Void TrackBar_ForceScale_Scroll(System::Object^  sender, System::EventArgs^  e) {
		TrackBar_Scroll(TextBox_ForceScale, TrackBar_ForceScale);

		//OnTick内で使える変数に代入
		appProfile.SetForceScale(TrackBar_ForceScale->Value);

		//ボタン更新
		ProfileButton_Update();
	}

	private: System::Void TextBox_ForceScale_Leave(System::Object^  sender, System::EventArgs^  e) {
		TextBox_TextChanged(TextBox_ForceScale, TrackBar_ForceScale);

		//OnTick内で使える変数に代入
		appProfile.SetForceScale(TrackBar_ForceScale->Value);

		//ボタン更新
		ProfileButton_Update();
	}

	private: System::Void TrackBar_MovementForce_Scroll(System::Object^  sender, System::EventArgs^  e) {
		TrackBar_Scroll(TextBox_MovementForce, TrackBar_MovementForce);

		//OnTick内で使える変数に代入
		appProfile.SetMovementForce(TrackBar_MovementForce->Value);

		//ボタン更新
		ProfileButton_Update();
	}

	private: System::Void TextBox_MovementForce_Leave(System::Object^  sender, System::EventArgs^  e) {
		TextBox_TextChanged(TextBox_MovementForce, TrackBar_MovementForce);

		//OnTick内で使える変数に代入
		appProfile.SetMovementForce(TrackBar_MovementForce->Value);

		//ボタン更新
		ProfileButton_Update();
	}

	private: System::Void TrackBar_RotateForce_Scroll(System::Object^  sender, System::EventArgs^  e) {
		TrackBar_Scroll(TextBox_RotateForce, TrackBar_RotateForce);

		//OnTick内で使える変数に代入
		appProfile.SetRotateForce(TrackBar_RotateForce->Value);

		//ボタン更新
		ProfileButton_Update();
	}

	private: System::Void TextBox_RotateForce_Leave(System::Object^  sender, System::EventArgs^  e) {
		TextBox_TextChanged(TextBox_RotateForce, TrackBar_RotateForce);

		//OnTick内で使える変数に代入
		appProfile.SetRotateForce(TrackBar_RotateForce->Value);

		//ボタン更新
		ProfileButton_Update();
	}

	private: System::Void TrackBar_CenterFrictionMax_Scroll(System::Object^  sender, System::EventArgs^  e) {
		TrackBar_Scroll(TextBox_CenterFrictionMax, TrackBar_CenterFrictionMax);

		//OnTick内で使える変数に代入
		appProfile.SetCenterFrictionMax(TrackBar_CenterFrictionMax->Value);

		//ボタン更新
		ProfileButton_Update();
	}


	private: System::Void TextBox_CenterFrictionMax_Leave(System::Object^  sender, System::EventArgs^  e) {
		TextBox_TextChanged(TextBox_CenterFrictionMax, TrackBar_CenterFrictionMax);

		//OnTick内で使える変数に代入
		appProfile.SetCenterFrictionMax(TrackBar_CenterFrictionMax->Value);

		//ボタン更新
		ProfileButton_Update();
	}

	private: System::Void TrackBar_CenterFrictionZone_Scroll(System::Object^  sender, System::EventArgs^  e) {
		TrackBar_Scroll(TextBox_CenterFrictionZone, TrackBar_CenterFrictionZone);

		//OnTick内で使える変数に代入
		appProfile.SetCenterFrictionZone(TrackBar_CenterFrictionZone->Value);

		//ボタン更新
		ProfileButton_Update();
	}


	private: System::Void TextBox_CenterFrictionZone_Leave(System::Object^  sender, System::EventArgs^  e) {
		TextBox_TextChanged(TextBox_CenterFrictionZone, TrackBar_CenterFrictionZone);

		//OnTick内で使える変数に代入
		appProfile.SetCenterFrictionZone(TrackBar_CenterFrictionZone->Value);

		//ボタン更新
		ProfileButton_Update();
	}

	private: System::Void TrackBar_GripFriction_Scroll(System::Object^  sender, System::EventArgs^  e) {
		TrackBar_Scroll(TextBox_GripFriction, TrackBar_GripFriction);

		//OnTick内で使える変数に代入
		appProfile.SetGripFriction(TrackBar_GripFriction->Value);

		//ボタン更新
		ProfileButton_Update();
	}

	private: System::Void TextBox_GripFriction_Leave(System::Object^  sender, System::EventArgs^  e) {
		TextBox_TextChanged(TextBox_GripFriction, TrackBar_GripFriction);

		//OnTick内で使える変数に代入
		appProfile.SetGripFriction(TrackBar_GripFriction->Value);

		//ボタン更新
		ProfileButton_Update();
	}

	private: System::Void TrackBar_StaticFriction_Scroll(System::Object^  sender, System::EventArgs^  e) {
		TrackBar_Scroll(TextBox_StaticFriction, TrackBar_StaticFriction);

		//OnTick内で使える変数に代入
		appProfile.SetStaticFriction(TrackBar_StaticFriction->Value);

		//ボタン更新
		ProfileButton_Update();
	}


	private: System::Void TextBox_StaticFriction_Leave(System::Object^  sender, System::EventArgs^  e) {
		TextBox_TextChanged(TextBox_StaticFriction, TrackBar_StaticFriction);

		//OnTick内で使える変数に代入
		appProfile.SetStaticFriction(TrackBar_StaticFriction->Value);

		//ボタン更新
		ProfileButton_Update();
	}

	private: System::Void TrackBar_TyreDynamicFrictionCoefficient_Scroll(System::Object^  sender, System::EventArgs^  e) {
		TrackBar_Scroll(TextBox_TyreDynamicFrictionCoefficient, TrackBar_TyreDynamicFrictionCoefficient);

		//OnTick内で使える変数に代入
		appProfile.SetTyreDynamicFrictionCoefficient(TrackBar_TyreDynamicFrictionCoefficient->Value);

		//ボタン更新
		ProfileButton_Update();
	}


	private: System::Void TextBox_TyreDynamicFrictionCoefficient_Leave(System::Object^  sender, System::EventArgs^  e) {
		TextBox_TextChanged(TextBox_TyreDynamicFrictionCoefficient, TrackBar_TyreDynamicFrictionCoefficient);

		//OnTick内で使える変数に代入
		appProfile.SetTyreDynamicFrictionCoefficient(TrackBar_TyreDynamicFrictionCoefficient->Value);

		//ボタン更新
		ProfileButton_Update();
	}

	private: System::Void TrackBar_SoftLockForce_Scroll(System::Object^  sender, System::EventArgs^  e) {
		TrackBar_Scroll(TextBox_SoftLockForce, TrackBar_SoftLockForce);

		//OnTick内で使える変数に代入
		appProfile.SetSoftLockForce(TrackBar_SoftLockForce->Value);

		//ボタン更新
		ProfileButton_Update();
	}


	private: System::Void TextBox_SoftLockForce_Leave(System::Object^  sender, System::EventArgs^  e) {
		TextBox_TextChanged(TextBox_SoftLockForce, TrackBar_SoftLockForce);

		//OnTick内で使える変数に代入
		appProfile.SetSoftLockForce(TrackBar_SoftLockForce->Value);

		//ボタン更新
		ProfileButton_Update();
	}

	private: System::Void TrackBar_MaxTyreAngle_Scroll(System::Object^  sender, System::EventArgs^  e) {
		TrackBar_Scroll(TextBox_MaxTyreAngle, TrackBar_MaxTyreAngle, -4);

		//OnTick内で使える変数に代入
		appProfile.SetMaxTyreAngle(TrackBar_MaxTyreAngle->Value);

		//deg表記を更新
		DegTextUpdate(TrackBar_MaxTyreAngle->Value, appProfile.GetPivotWheelMode());

		//ボタン更新
		ProfileButton_Update();
	}

	private: System::Void TextBox_MaxTyreAngle_TextChanged(System::Object^ sender, System::EventArgs^  e) {
		//textboxからdeg表記を更新
		DegTextUpdate(ToInt(TextBox_MaxTyreAngle->Text, 4), appProfile.GetPivotWheelMode());
	}

	private: System::Void TextBox_MaxTyreAngle_Leave(System::Object^ sender, System::EventArgs^  e) {
		//textboxに成型済みの値を返す
		TextBox_TextChanged(TextBox_MaxTyreAngle, TrackBar_MaxTyreAngle, 4);

		//OnTick内で使える変数に代入
		appProfile.SetMaxTyreAngle(TrackBar_MaxTyreAngle->Value);

		//deg表記を更新
		DegTextUpdate(TrackBar_MaxTyreAngle->Value, appProfile.GetPivotWheelMode());

		//ボタン更新
		ProfileButton_Update();
	}

	private: System::Void Text_MaxTyreAngleDeg_TextChanged(System::Object^ sender, System::EventArgs^  e) {
		//Text_MaxTyreAngleDeg->Location = Point(588 - Text_MaxTyreAngleDeg->Width, Text_MaxTyreAngleDeg->Location.Y);
	}

	private: System::Void DegTextUpdate(int param, bool PivotWheelMode) {
		//deg表記を更新
		if (isnan((double)param)) {
			DegTextUpdate(0, PivotWheelMode, true);
			return;
		}
		
		if (param != 0) {
			if (PivotWheelMode) {
				Text_MaxTyreAngleDeg->Text = ((param / 10000.f) * 90).ToString("(0.### deg)");
			}
			else {
				Text_MaxTyreAngleDeg->Text = ((param / 10000.f) * 180 / Math::PI).ToString("(0.### deg)");
			}
		}
		else {
			Text_MaxTyreAngleDeg->Text = "(0 deg)";
		}
	}

	private: System::Void DegTextUpdate(int param, bool PivotWheelMode, bool err) {
		//deg表記を更新
		if (err) {
			Text_MaxTyreAngleDeg->Text = "(? deg)";
		}
		else {
			DegTextUpdate(param, PivotWheelMode);
		}
	}

	private: System::Void TyreTypeButton_Click(System::Object^  sender, System::EventArgs^  e) {
		appProfile.SetPivotWheelMode(!appProfile.GetPivotWheelMode());
		PivotWheelModeTextUpdate(appProfile.GetPivotWheelMode());
		DegTextUpdate(TrackBar_MaxTyreAngle->Value, appProfile.GetPivotWheelMode());

		//ボタン更新
		ProfileButton_Update();
	}

	private: System::Void PivotWheelModeTextUpdate(bool PivotWheelMode) {
		if (PivotWheelMode) {
			TyreTypeButton->Text = "Pivot";
			Text_MaxTyreAngle_Unit->Text = "x0.25 turns";
		}
		else {
			TyreTypeButton->Text = "Default";
			Text_MaxTyreAngle_Unit->Text = "rad";
		}
	}

	private: int ToInt(System::String ^text, int digitShift) {
		//数値変換に対応した文字のみのコピーを作成
		System::String ^str = "";
		array<wchar_t> ^trimChars = { ' ', '0' };
		int dotIndex = -1;
		for (int i = 0; i < text->Length; ++i) {
			if ('0' <= text[i] && text[i] <= '9') {
				str += text[i];
			}
			else if (text[i] == '.') {
				//2つめの'.'を見つけた場合、数値変換不可として0を返す
				if (0 <= dotIndex) { return 0; }

				//'.'の位置だけ記録し、strには追加しない
				dotIndex = i;
			}
		}
		//'.'がある場合、不要な0を消す
		if (0 <= dotIndex) {
			str = str->TrimEnd('0');
		}
		else {//'.'がない場合、末尾にあることにする
			dotIndex = str->Length;
		}

		if (0 < dotIndex + digitShift && dotIndex + digitShift <= str->Length) {
			int n = 0;
			Int32::TryParse(str->Substring(0, dotIndex + digitShift), n);
			return n;
		}
		else {
			int n = 0;
			Int32::TryParse(str, n);
			return xEy(n, (dotIndex + digitShift) - str->Length);
		}

		return 0;
	}

	private: System::String^ ToString(int param, int digitShift) {
		if (0 <= digitShift) {
			//右側に0を必要数追加して返す
			return xEy(param, digitShift).ToString();
		}
		else {
			if (param == 0) {//"0.00..."となるので"0"で返す
				return "0";
			}
			System::String^ str = param.ToString();
			if (str->Length <= -digitShift) {//"0.00...1"とかになるパターン
				System::String ^zero = "";
				for (int i = 0; i < 1 + (-(digitShift + str->Length)); ++i) {
					zero += "0";
				}
				return (zero->Insert(1, ".") + str)->TrimEnd('0');
			}
			else {//'.'を挿入するだけのパターン
				return str->Insert(str->Length + digitShift, ".")->Trim('0')->TrimEnd('.');
			}
		}
		return "";
	}

	//x*10のy乗を返す
	private: int xEy(int x, int y) {
		if (y == 0 || x == 0) {
			return x;
		}

		if (0 < y) {
			int n = x;
			for (int i = 0; i < y; ++i) {
				n *= 10;
			}
			return n;
		}

		if (y < 0) {
			System::String^ str = x.ToString();
			if (str->Length <= -y) {
				return 0;
			}
			int n = 0;
			Int32::TryParse(str->Substring(0, str->Length + y), n);
			return n;
		}

		return 0;
	}

	private: System::Void TextBox_TextChanged(TextBox ^textbox, TrackBar ^trackbar) {
		//textboxからtrackbarへ値を送る
		int n = 0;
		Int32::TryParse(textbox->Text, n);
		n = min(max(n, trackbar->Minimum), trackbar->Maximum);

		trackbar->Value = n;

		//textboxにクランプ済みの値を返す
		textbox->Text = n.ToString();
	}

	private: System::Void TextBox_TextChanged(TextBox ^textbox, TrackBar ^trackbar, int digitShift) {
		//textboxからtrackbarへ値を送る
		int n = ToInt(textbox->Text, digitShift);
		n = min(max(n, trackbar->Minimum), trackbar->Maximum);

		trackbar->Value = n;

		//textboxにクランプ済みの値を返す
		textbox->Text = ToString(n, -digitShift);
	}

	private: System::Void TrackBar_Scroll(TextBox ^textbox, TrackBar ^trackbar) {
		textbox->Text = trackbar->Value.ToString();
	}

	private: System::Void TrackBar_Scroll(TextBox ^textbox, TrackBar ^trackbar, int digitShift) {
		textbox->Text = ToString(trackbar->Value, digitShift);
	}

	private: System::Void TextBox_NumOnly_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
		//数値0～9とバックスペースと改行以外が押された時はイベントをキャンセルする
		if ((e->KeyChar < '0' || '9' < e->KeyChar) && e->KeyChar != '\b' && e->KeyChar != '\n' && e->KeyChar != '\r')
		{
			e->Handled = true;
			return;
		}
		else if (e->KeyChar == '\n' || e->KeyChar == '\r') {
			this->ActiveControl = nullptr;
			e->Handled = true;
			return;
		}
	}

	private: System::Void TextBox_FloatOnly_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
		//数値0～9と.とバックスペースと改行以外が押された時はイベントをキャンセルする
		if ((e->KeyChar < '0' || '9' < e->KeyChar) && e->KeyChar != '\b' && e->KeyChar != '\n' && e->KeyChar != '\r' && e->KeyChar != '.')
		{
			e->Handled = true;
			return;
		}
		else if (e->KeyChar == '\n' || e->KeyChar == '\r') {
			this->ActiveControl = nullptr;
			e->Handled = true;
			return;
		}
	}

	//プロファイル変更
	private: System::Void ProfileList_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
		//前回選択したプロファイルと同じなら何もしない
		if (ProfileList->SelectedIndex == preProfileIndex) { return; }

		FFB_OFF();

		if (!Profile::IsSameProfile(appProfile, loadProfile)) {//保存されていない変更がある場合、確認ダイアログを表示する
			// メッセージボックスを表示する
			System::String^ message = "保存されていない変更があります。保存しますか？";
			System::String^ title = "変更の保存";
			System::Windows::Forms::DialogResult dialogResult =
				System::Windows::Forms::MessageBox::Show(this, message, title, MessageBoxButtons::YesNoCancel, MessageBoxIcon::Warning);

			if (dialogResult == System::Windows::Forms::DialogResult::Cancel) {
				ProfileList->SelectedIndex = preProfileIndex;
				return;
			}
			else if (dialogResult == System::Windows::Forms::DialogResult::Yes) {
				if (0 < preProfileIndex && preProfileIndex < ProfileList->Items->Count - 1) {
					if (SaveProfile(appProfile, msclr::interop::marshal_as<std::string>(ProfileList->Items[preProfileIndex]->ToString()))) {
						//loadProfileの更新
						loadProfile = appProfile;
						// メッセージボックスを表示する
						System::String^ message = "変更を保存しました";
						System::String^ title = "変更の保存";
						System::Windows::Forms::DialogResult dialogResult =
							System::Windows::Forms::MessageBox::Show(this, message, title, MessageBoxButtons::OK, MessageBoxIcon::None);
					}
					else {
						// メッセージボックスを表示する
						System::String^ message = "保存に失敗しました";
						System::String^ title = "変更の保存";
						System::Windows::Forms::DialogResult dialogResult =
							System::Windows::Forms::MessageBox::Show(this, message, title, MessageBoxButtons::OK, MessageBoxIcon::Error);
					}
				}
				else if (preProfileIndex == 0) {
					//デフォルトプロファイルの場合新規作成フォームを表示する
					CreateProfileForm form;
					std::string createProfileName = "";
					form.SetData(&appProfile, &createProfileName);
					form.StartPosition = FormStartPosition::CenterScreen;//画面の中心に表示させる(メッセージボックスに合わせる)
					form.ShowDialog(this);
					//新規作成されていたら
					if (createProfileName != "") {
						// メッセージボックスを表示する
						System::String^ message = "変更を保存しました";
						System::String^ title = "変更の保存";
						System::Windows::Forms::DialogResult dialogResult =
							System::Windows::Forms::MessageBox::Show(this, message, title, MessageBoxButtons::OK, MessageBoxIcon::None);
					}
					else {
						//新規作成しなかった場合キャンセル扱い
						ProfileList->SelectedIndex = preProfileIndex;
						return;
					}

					//変更を破棄しておく
					appProfile = loadProfile;

					ProfileListInit();
					int index = ProfileList->FindStringExact(msclr::interop::marshal_as<System::String^>(createProfileName));
					if (0 < index) {//プロファイルが見つかっていたら
						ProfileList->SelectedIndex = index;
					}
					else {
						//検索失敗時はDefaultにする
						ProfileList->SelectedIndex = 0;
					}
					return;
				}
			}
			else if (dialogResult == System::Windows::Forms::DialogResult::No) {
				//変更を破棄
				appProfile = loadProfile;
			}
		}

		//UI更新
		ProfileUIUpdate();
		//ボタン更新
		ProfileButton_Update();

		//選択されたプロファイルを読み込む
		if (0 < ProfileList->SelectedIndex && ProfileList->SelectedIndex < ProfileList->Items->Count - 1) {
			loadProfile = LoadProfile(msclr::interop::marshal_as<std::string>(ProfileList->SelectedItem->ToString()));
			appProfile = loadProfile;
		}
		//Default
		else if (ProfileList->SelectedIndex == 0) {
			loadProfile = Profile();
			appProfile = loadProfile;
		}
		//新規作成
		else if (ProfileList->SelectedIndex == ProfileList->Items->Count - 1) {
			CreateProfileForm form;
			std::string createProfileName = "";
			Profile defaultProfile = Profile();
			form.SetData(&defaultProfile, &createProfileName);
			form.StartPosition = FormStartPosition::CenterParent;//親の中心に表示させる
			form.ShowDialog(this);
			//新規作成されていたら
			if (createProfileName != ""){
				ProfileListInit();
				//追加されたプロファイルを検索してインデックスを変更する
				int index = ProfileList->FindStringExact(msclr::interop::marshal_as<System::String^>(createProfileName));
				if (0 < index) {//プロファイルが見つかっていたら
					ProfileList->SelectedIndex = index;
				}
				else {
					//検索失敗時はDefaultにする
					ProfileList->SelectedIndex = 0;
				}
			}
			//新規作成されていない
			else {
				ProfileList->SelectedIndex = preProfileIndex;
			}
		}

		//UI更新
		ProfileUIUpdate();

		//ボタン更新
		ProfileButton_Update();

		preProfileIndex = ProfileList->SelectedIndex;
	}

	private: System::Void ProfileRevertChangesButton_Click(System::Object^  sender, System::EventArgs^  e) {
		// メッセージボックスを表示する
		System::String^ message = "保存されていない変更を破棄します。よろしいですか？\n※この操作は元に戻せません。";
		System::String^ title = "変更の破棄";
		System::Windows::Forms::DialogResult dialogResult =
			System::Windows::Forms::MessageBox::Show(message, title, MessageBoxButtons::OKCancel, MessageBoxIcon::Warning);

		if (dialogResult == System::Windows::Forms::DialogResult::OK) {
			//ロードしてあるプロファイル設定に戻す
			appProfile = loadProfile;
			//UI更新
			ProfileUIUpdate();
			//ボタン更新
			ProfileButton_Update();
		}
	}

	private: System::Void ProfileSaveButton_Click(System::Object^  sender, System::EventArgs^  e) {
		if (0 < ProfileList->SelectedIndex && ProfileList->SelectedIndex < ProfileList->Items->Count - 1) {
			if (SaveProfile(appProfile, msclr::interop::marshal_as<std::string>(ProfileList->SelectedItem->ToString()))) {
				loadProfile = LoadProfile(msclr::interop::marshal_as<std::string>(ProfileList->SelectedItem->ToString()));
				ProfileSaveButton->Enabled = false;
				ProfileRevertChangesButton->Enabled = false;
			}
		}
	}

	private: System::Void ProfileDeleteButton_Click(System::Object^  sender, System::EventArgs^  e) {
		if (0 < ProfileList->SelectedIndex && ProfileList->SelectedIndex < ProfileList->Items->Count - 1) {
			// メッセージボックスを表示する
			System::String^ message = "プロファイル 「" + ProfileList->SelectedItem->ToString() + "」 を削除します。よろしいですか？\n※この操作は元に戻せません。";
			System::String^ title = "プロファイルの削除";
			System::Windows::Forms::DialogResult dialogResult =
				System::Windows::Forms::MessageBox::Show(message, title, MessageBoxButtons::OKCancel, MessageBoxIcon::Warning);

			if (dialogResult == System::Windows::Forms::DialogResult::OK) {
				if (DeleteProfile(msclr::interop::marshal_as<std::string>(ProfileList->SelectedItem->ToString()))) {
					auto deleteitem = ProfileList->SelectedItem;//選択中のプロファイルが削除対象
					ProfileList->SelectedIndex = 0;//インデックスをDefaultにする
					ProfileList->Items->Remove(deleteitem);//プロファイルリストから削除
				}
				else {
					//削除に失敗した場合、プロファイルフォルダに変更があった可能性があるので、プロファイルリストを更新する
					ProfileListInit();
				}
			}
		}
	}
			 
	private: System::Void ProfileListInit() {
		ProfileList->Items->Clear();//項目全削除
		ProfileList->Items->Add("Default");
		ProfileList->SelectedIndex = 0;//一度Defaultにする
		int index = 0;
		std::string firstProfileName = appData.GetInitProfileName();
		std::vector<std::string> fileNames = GetProfilesName(Profile::FolderName(), Profile::FileExtension());
		for (unsigned int i = 0; i < fileNames.size(); ++i) {
			ProfileList->Items->Add(msclr::interop::marshal_as<System::String^>(fileNames[i]));

			//初めに読み込むプロファイルを発見したらindexを保存しておく
			if (fileNames[i] == firstProfileName) {
				index = i + 1;//ユーザープロファイルは1からなので+1
			}
		}
		ProfileList->Items->Add("＋新規作成");
		ProfileList->SelectedIndex = index;//保存していたindexを選択する
	}

	private: System::Void ProfileUIUpdate() {
		//MinForce
		TrackBar_MinForce->Value = appProfile.GetMinForce();
		TextBox_MinForce->Text = TrackBar_MinForce->Value.ToString();
		//MaxForce
		TrackBar_MaxForce->Value = appProfile.GetMaxForce();
		TextBox_MaxForce->Text = TrackBar_MaxForce->Value.ToString();
		//ForceScale
		TrackBar_ForceScale->Value = appProfile.GetForceScale();
		TextBox_ForceScale->Text = TrackBar_ForceScale->Value.ToString();
		//InvertFFB
		CheckBox_InvertFFB->CheckState = (appProfile.GetInvertFFB()) ? CheckState::Checked : CheckState::Unchecked;
		//MovementForce
		TrackBar_MovementForce->Value = appProfile.GetMovementForce();
		TextBox_MovementForce->Text = TrackBar_MovementForce->Value.ToString();
		//RotateForce
		TrackBar_RotateForce->Value = appProfile.GetRotateForce();
		TextBox_RotateForce->Text = TrackBar_RotateForce->Value.ToString();
		//CenterFrictionMax
		TrackBar_CenterFrictionMax->Value = appProfile.GetCenterFrictionMax();
		TextBox_CenterFrictionMax->Text = TrackBar_CenterFrictionMax->Value.ToString();
		//CenterFrictionZone
		TrackBar_CenterFrictionZone->Value = appProfile.GetCenterFrictionZone();
		TextBox_CenterFrictionZone->Text = TrackBar_CenterFrictionZone->Value.ToString();
		//GripFriction
		TrackBar_GripFriction->Value = appProfile.GetGripFriction();
		TextBox_GripFriction->Text = TrackBar_GripFriction->Value.ToString();
		//StaticFriction
		TrackBar_StaticFriction->Value = appProfile.GetStaticFriction();
		TextBox_StaticFriction->Text = TrackBar_StaticFriction->Value.ToString();
		//TyreDynamicFrictionCoefficient
		TrackBar_TyreDynamicFrictionCoefficient->Value = appProfile.GetTyreDynamicFrictionCoefficient();
		TextBox_TyreDynamicFrictionCoefficient->Text = TrackBar_TyreDynamicFrictionCoefficient->Value.ToString();
		//DeadZoneInside
		TrackBar_DeadZoneInside->Value = appProfile.GetDeadZoneInside();
		TextBox_DeadZoneInside->Text = ToString(TrackBar_DeadZoneInside->Value, -2);
		//DeadZoneOutside
		TrackBar_DeadZoneOutside->Value = appProfile.GetDeadZoneOutside();
		TextBox_DeadZoneOutside->Text = ToString(TrackBar_DeadZoneOutside->Value, -2);
		//SoftLockForce
		TrackBar_SoftLockForce->Value = appProfile.GetSoftLockForce();
		TextBox_SoftLockForce->Text = TrackBar_SoftLockForce->Value.ToString();
		//GetPivotWheelMode
		PivotWheelModeTextUpdate(appProfile.GetPivotWheelMode());
		//MaxTyreAngle
		TrackBar_MaxTyreAngle->Value = appProfile.GetMaxTyreAngle();
		TextBox_MaxTyreAngle->Text = ToString(TrackBar_MaxTyreAngle->Value, -4);
		DegTextUpdate(TrackBar_MaxTyreAngle->Value, appProfile.GetPivotWheelMode());
	}

	private: System::Void ProfileButton_Update() {
		bool isSameProfile = Profile::IsSameProfile(appProfile, loadProfile);
		bool isUserProfile = (0 < ProfileList->SelectedIndex && ProfileList->SelectedIndex < ProfileList->Items->Count - 1);
		bool isDefaultProfile = ProfileList->SelectedIndex == 0;
		bool isDefaultParam = appProfile.IsDefaultParam();
		bool isCreateProfile = ProfileList->SelectedIndex == ProfileList->Items->Count - 1;

		//ロードしてあるプロファイル設定と同じ数値になっていれば上書き保存ボタンを無効化
		if (isSameProfile)
		{
			ProfileSaveButton->Enabled = false;
			ProfileRevertChangesButton->Enabled = false;
		}

		//上書き保存に対応したプロファイルなら有効化
		if(!isSameProfile && isUserProfile)
		{
			ProfileSaveButton->Enabled = true;
			ProfileRevertChangesButton->Enabled = true;
		}

		//Defaultプロファイルなら有効化
		if (!isSameProfile && isDefaultProfile) {
			ProfileRevertChangesButton->Enabled = true;
		}

		//Defaultと同じ設定でないかつユーザープロファイルかDefaultプロファイルなら有効化
		ProfileReturnToDefaultButton->Enabled = !isDefaultParam && (isUserProfile || isDefaultProfile);
		
		//ユーザープロファイルのみ削除ボタンを有効化
		ProfileDeleteButton->Enabled = isUserProfile;

		//新規作成中でなければ有効化
		ProfileCopyButton->Enabled = !isCreateProfile;
	}

	private: System::Void ReturnToDefaultButton_Click(System::Object^  sender, System::EventArgs^  e) {
		// メッセージボックスを表示する
		System::String^ message = "プロファイル 「" + ProfileList->SelectedItem->ToString() + "」 を初期設定に戻します。よろしいですか？\n※この操作は元に戻せません。";
		System::String^ title = "プロファイルの初期化";
		System::Windows::Forms::DialogResult dialogResult =
			System::Windows::Forms::MessageBox::Show(message, title, MessageBoxButtons::OKCancel, MessageBoxIcon::Warning);

		if (dialogResult == System::Windows::Forms::DialogResult::OK) {
			//デフォルト値に戻す
			appProfile = Profile();
			//UI更新
			ProfileUIUpdate();
			//ボタン更新
			ProfileButton_Update();
		}
	}

	private: System::Void ProfileCopyButton_Click(System::Object^  sender, System::EventArgs^  e) {
		CopyProfileForm form;
		std::string dsestinationName = "";
		form.SetData(ProfileList, appProfile, &dsestinationName);
		form.StartPosition = FormStartPosition::CenterParent;//親の中心に表示させる
		form.ShowDialog(this);

		//コピーされている
		if (dsestinationName != "") {
			//変更は破棄する(コピー先に変更後のプロファイルが保存されている為、ユーザーへの警告は無し)
			appProfile = loadProfile;

			//新規作成されている可能性があるためプロファイルリストを更新
			appData.SetInitProfileName(dsestinationName);
			ProfileListInit();
		}

		//プロファイルUI更新
		ProfileUIUpdate();

		//ボタン更新
		ProfileButton_Update();
	}


	private: System::Void FFB_OFF_Button_Click(System::Object^  sender, System::EventArgs^  e) {
		FFB_OFF();
	}

	private: System::Void FFB_OFF() {
		ffbBoot = false;

		FFB_Active_Text_Update();

		FFBState_Bar->Value = 0;

		ffbBootCount = 0;

		//すべてのFFBを切る
		for (int i = 0; i < AXIS::MAX; ++i) {
			FFBReset(usingDeviceDID, i);
		}
	}

	private: System::Void FFB_ON_Button_Click(System::Object^  sender, System::EventArgs^  e) {
		ffbBoot = true;

		FFB_Active_Text_Update();

		ffbBootCount = 0;
	}

	private: System::Void FFB_Active_Text_Update() {
		if (ffbBoot) {
			FFBState_Text->Text = "FFB Activating";
			FFBState_Text->ForeColor = System::Drawing::SystemColors::ControlText;
		}
		else {
			FFBState_Text->Text = "FFB Inactive";
			FFBState_Text->ForeColor = System::Drawing::SystemColors::ControlDark;
		}
	}

	private: System::Void FFBMonitorButton_Click(System::Object^  sender, System::EventArgs^  e) {
		FFBMonitorForm ^ffb_monitor = gcnew FFBMonitorForm();
		
		ffb_monitor->SetData(
			&FFBMonitor_Input_Axis_Name,
			&FFBMonitor_Input_Axis,
			&FFBMonitor_Total_Direction_Force,
			&FFBMonitor_Movement_Force,
			&FFBMonitor_Rotate_Force,
			&FFBMonitor_Total_Friction,
			&FFBMonitor_Grip_Friction,
			&FFBMonitor_Center_Friction,
			&FFBMonitor_Static_Friction,
			&FFBMonitor_MaxForce
		);
		ffb_monitor->Show();
	}

	private: System::Void TyreMonitorButton_Click(System::Object^  sender, System::EventArgs^  e) {
		TyreMonitorForm ^tyre_monitor = gcnew TyreMonitorForm();

		tyre_monitor->SetData(
			&TyreMonitor_LeftTyreAngle,
			&TyreMonitor_RightTyreAngle
		);
		tyre_monitor->Show();
	}

	private: System::Void ChannelSelectBox_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
		//FFB停止
		FFB_OFF();

		//タイムアウト扱いにしてオンライン表示が続かないようにする
		timeoutTimer = 0;

		//チャンネル変更の適応(0 originに変換)
		channel = System::Decimal::ToInt32(ChannelSelectBox->Value) - 1;
	}
};
}