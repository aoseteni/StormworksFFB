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

#define DIRECTINPUT_VERSION     0x0800          // DirectInput�̃o�[�W�����w��
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

//Stormworks�����FFB�p�M���󂯎��p//

// �|�[�g�ԍ�
const int port_number = 4091;
int channel = 0;

//�`�����l���̍ő吔
const int channel_max = 10;

// Windows Sockets�d�l�Ɋւ�������i�[����\����
WSADATA wsa_data[channel_max];

// �T�[�o���\�P�b�g�쐬
SOCKET src_socket[channel_max];

// sockaddr_in�\���̂̍쐬�ƃ|�[�g�ԍ��AIP�^�C�v�̓���
struct sockaddr_in src_addr[channel_max];


// �N���C�A���g���̃\�P�b�g�ݒ�
SOCKET dst_socket[channel_max];
struct sockaddr_in dst_addr[channel_max];
int dst_addr_size = sizeof(dst_addr);

// ����M�Ɏg�p����o�b�t�@
char recv_buf[channel_max][256];
char send_buf[channel_max][256];

//�eFFB�p�����[�^
enum {
	LEFT,
	RIGHT
};

struct CarState
{
	float tireSpeed[2];//�P��:km/h
	bool tireOnGround[2];//true�Őڒn
	float bodySpeedX[2];//�P��:km/h
	float bodySpeedZ[2];//�P��:km/h
	float bodyRotateY[2];//�P��:1��]/sec
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

int id_max = 0;//�ŐV�̏���id�ԍ�

const int timeoutTime = 30;//�P��:tick
int timeoutTimer = 0;
float TPS = 0;
int tickCount = 0;

//Stormworks�����FFB�p�M���󂯎��p//

//DirectInput�p//
BYTE byKeyState[256];		//�L�[�{�[�h
DIMOUSESTATE diMouseState;	//�}�E�X
DIDEV usingDeviceDID = DID_NONE;//�g�p���̃f�o�C�X�ԍ�
int usingAxisIndex = 0;		//�g�p���̎��ԍ�
DIJOYSTATE diJoyState;		//�Q�[���p�b�h
DIJOYSTATE preDiJoyState;	//1tick�O�̃Q�[���p�b�h
bool initialized = false;

Profile loadProfile;//���[�h�����v���t�@�C��(���[�h��ύX�֎~)
Profile appProfile;//�ݒ���ꎞ�I�ɕۑ�����p
AppData appData;//�N�����ɓǂݍ��ސݒ�

//�t�H�[��UI�p�ϐ�
int preProfileIndex = 0;
int preDeviceIndex = 0;
int preAxisIndex = 0;
bool ffbBoot = false;
int ffbBootCount = 0;

//FFB���j�^�[�p�ϐ�
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

//�^�C�����j�^�[�p�ϐ�
float TyreMonitor_LeftTyreAngle = 0;//�P��:rad
float TyreMonitor_RightTyreAngle = 0;//�P��:rad


//�f�o�b�O�p�ϐ�
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
	/// MainForm �̊T�v
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
		{
			InitializeComponent();
			//
			//TODO: �����ɃR���X�g���N�^�[ �R�[�h��ǉ����܂�
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
		/// �g�p���̃��\�[�X�����ׂăN���[���A�b�v���܂��B
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
		/// �K�v�ȃf�U�C�i�[�ϐ��ł��B
		/// </summary>
		//OnTick�p�^�C�}�[
		System::Timers::Timer^ timer;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// �f�U�C�i�[ �T�|�[�g�ɕK�v�ȃ��\�b�h�ł��B���̃��\�b�h�̓��e��
		/// �R�[�h �G�f�B�^�[�ŕύX���Ȃ��ł��������B
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
			this->toolTip1->SetToolTip(this->ResetButton, L"�A�v���P�[�V�����̃��Z�b�g���s���܂�\r\n�f�o�C�X�̕ύX�y�уA�v���P�[�V�����O�ł̃v���t�@�C���̕ύX���s��ꂽ�ۂɎg�p���Ă�������");
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
			this->toolTip1->SetToolTip(this->Text_Online, L"�I�����ꂽ�`�����l����Stormworks���r�[�N�������FFB�p�M���̎�M�ɐ������Ă����Online�A���Ȃ����Offline�ɂȂ�܂�");
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
			this->toolTip1->SetToolTip(this->Text_InputAxis, L"FFB�̑ΏۂƂȂ鎲�̓��͒l��\���܂�");
			// 
			// CheckBox_AlwaysOnTop
			// 
			this->CheckBox_AlwaysOnTop->AutoSize = true;
			this->CheckBox_AlwaysOnTop->Font = (gcnew System::Drawing::Font(L"BIZ UDP�S�V�b�N", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(128)));
			this->CheckBox_AlwaysOnTop->Location = System::Drawing::Point(558, 630);
			this->CheckBox_AlwaysOnTop->Name = L"CheckBox_AlwaysOnTop";
			this->CheckBox_AlwaysOnTop->Size = System::Drawing::Size(108, 16);
			this->CheckBox_AlwaysOnTop->TabIndex = 4;
			this->CheckBox_AlwaysOnTop->Text = L"��ɑO�ʂɕ\��";
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
			this->toolTip1->SetToolTip(this->Text_MaxForce, L"FFB�̍ő�l��ݒ肵�܂�");
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
			this->toolTip1->SetToolTip(this->Text_MovementForce, L"�ԑ̐i�s�����ւ̗͂̋�����ݒ肵�܂�");
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
			this->toolTip1->SetToolTip(this->Text_StaticFriction, L"�Î~���̖��C�̋�����ݒ肵�܂�");
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
			this->toolTip1->SetToolTip(this->Text_CenterFrictionMax, L"�Z���^�[�t�߂̖��C�̍ő勭����ݒ肵�܂�");
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
			this->toolTip1->SetToolTip(this->Text_CenterFrictionZone, L"�Z���^�[�t�߂̖��C�͈̔͂�ݒ肵�܂�");
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
			this->toolTip1->SetToolTip(this->Text_TyreDynamicFrictionCoefficient, L"�^�C�����X���b�v�����ۂ̖��C�W���{����ݒ肵�܂�");
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
			this->toolTip1->SetToolTip(this->Text_RotateForce, L"�ԑ̉�]���̗͂̋�����ݒ肵�܂�");
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
			this->toolTip1->SetToolTip(this->Text_GripFriction, L"�^�C���ڒn���̖��C�̋�����ݒ肵�܂�");
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
			this->toolTip1->SetToolTip(this->Text_ForceScale, L"FFB�̔{����ݒ肵�܂�");
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
			this->toolTip1->SetToolTip(this->label6, L"�`�����l����I�����܂�\r\n�ڑ����Stormworks���r�[�N���Ɠ������l��I�����Ă�������");
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
			this->toolTip1->SetToolTip(this->ChannelSelectBox, L"�`�����l����I�����܂�\r\n�ڑ����Stormworks���r�[�N���Ɠ������l��I�����Ă�������");
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
			this->toolTip1->SetToolTip(this->DeviceList, L"�g�p����f�o�C�X��I�����܂�");
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
			this->toolTip1->SetToolTip(this->AxisList, L"FFB���o�͂��鎲��I�����܂�");
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
			this->toolTip1->SetToolTip(this->Text_MinForce, L"FFB�̍ŏ��l��ݒ肵�܂�");
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
			this->toolTip1->SetToolTip(this->Text_MaxTyreAngle, L"�^�C���̍ő�؂�p��ݒ肵�܂�");
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
			this->toolTip1->SetToolTip(this->CheckBox_InvertFFB, L"FFB�M���𔽓]���܂�");
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
			this->toolTip1->SetToolTip(this->Text_DeadZoneInside, L"�����̃f�b�h�]�[����ݒ肵�܂�\r\n�w�肵�������ȉ��̓��͂͂��ׂčŏ��l�Ƃ��Ĉ����܂�");
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
			this->toolTip1->SetToolTip(this->Text_SoftLockForce, L"�n���h����\"Dead Zone (outside)\"�ɓ��B�����ۂɂ�����͂�ݒ肵�܂�\r\n���̐ݒ��\"Max Force\"�y��\"Min Force\"�̉e�����󂯂�"
				L"����");
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
			this->toolTip1->SetToolTip(this->Text_DeadZoneOutside, L"�O���̃f�b�h�]�[����ݒ肵�܂�\r\n�w�肵�������ȏ�̓��͂͂��ׂčő�l�Ƃ��Ĉ����܂�");
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
			this->toolTip1->SetToolTip(this->label5, L"�^�C�����Ȃ��������I�����܂�");
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
			this->ProfileSaveButton->Font = (gcnew System::Drawing::Font(L"BIZ UDP�S�V�b�N", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(128)));
			this->ProfileSaveButton->Location = System::Drawing::Point(231, 588);
			this->ProfileSaveButton->Name = L"ProfileSaveButton";
			this->ProfileSaveButton->Size = System::Drawing::Size(73, 26);
			this->ProfileSaveButton->TabIndex = 25;
			this->ProfileSaveButton->Text = L"�㏑���ۑ�";
			this->ProfileSaveButton->UseVisualStyleBackColor = true;
			this->ProfileSaveButton->Click += gcnew System::EventHandler(this, &MainForm::ProfileSaveButton_Click);
			// 
			// ProfileRevertChangesButton
			// 
			this->ProfileRevertChangesButton->Font = (gcnew System::Drawing::Font(L"BIZ UDP�S�V�b�N", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(128)));
			this->ProfileRevertChangesButton->Location = System::Drawing::Point(305, 588);
			this->ProfileRevertChangesButton->Name = L"ProfileRevertChangesButton";
			this->ProfileRevertChangesButton->Size = System::Drawing::Size(73, 26);
			this->ProfileRevertChangesButton->TabIndex = 26;
			this->ProfileRevertChangesButton->Text = L"�ύX��j��";
			this->ProfileRevertChangesButton->UseVisualStyleBackColor = true;
			this->ProfileRevertChangesButton->Click += gcnew System::EventHandler(this, &MainForm::ProfileRevertChangesButton_Click);
			// 
			// ProfileDeleteButton
			// 
			this->ProfileDeleteButton->Font = (gcnew System::Drawing::Font(L"BIZ UDP�S�V�b�N", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(128)));
			this->ProfileDeleteButton->Location = System::Drawing::Point(379, 588);
			this->ProfileDeleteButton->Name = L"ProfileDeleteButton";
			this->ProfileDeleteButton->Size = System::Drawing::Size(73, 26);
			this->ProfileDeleteButton->TabIndex = 27;
			this->ProfileDeleteButton->Text = L"�ݒ���폜";
			this->ProfileDeleteButton->UseVisualStyleBackColor = true;
			this->ProfileDeleteButton->Click += gcnew System::EventHandler(this, &MainForm::ProfileDeleteButton_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"BIZ UDP�S�V�b�N", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(12, 573);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(70, 12);
			this->label1->TabIndex = 28;
			this->label1->Text = L"�v���t�@�C��";
			// 
			// ProfileCopyButton
			// 
			this->ProfileCopyButton->Font = (gcnew System::Drawing::Font(L"BIZ UDP�S�V�b�N", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(128)));
			this->ProfileCopyButton->Location = System::Drawing::Point(574, 588);
			this->ProfileCopyButton->Name = L"ProfileCopyButton";
			this->ProfileCopyButton->Size = System::Drawing::Size(88, 26);
			this->ProfileCopyButton->TabIndex = 29;
			this->ProfileCopyButton->Text = L"�ݒ�̃R�s�[";
			this->ProfileCopyButton->UseVisualStyleBackColor = true;
			this->ProfileCopyButton->Click += gcnew System::EventHandler(this, &MainForm::ProfileCopyButton_Click);
			// 
			// ProfileReturnToDefaultButton
			// 
			this->ProfileReturnToDefaultButton->Font = (gcnew System::Drawing::Font(L"BIZ UDP�S�V�b�N", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(128)));
			this->ProfileReturnToDefaultButton->Location = System::Drawing::Point(453, 588);
			this->ProfileReturnToDefaultButton->Name = L"ProfileReturnToDefaultButton";
			this->ProfileReturnToDefaultButton->Size = System::Drawing::Size(120, 26);
			this->ProfileReturnToDefaultButton->TabIndex = 31;
			this->ProfileReturnToDefaultButton->Text = L"�f�t�H���g�l�ɖ߂�";
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
			this->FFB_OFF_Button->Font = (gcnew System::Drawing::Font(L"BIZ UDP�S�V�b�N", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
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
			this->FFB_ON_Button->Font = (gcnew System::Drawing::Font(L"BIZ UDP�S�V�b�N", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
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
			this->FFBMonitorButton->Font = (gcnew System::Drawing::Font(L"BIZ UDP�S�V�b�N", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(128)));
			this->FFBMonitorButton->Location = System::Drawing::Point(565, 55);
			this->FFBMonitorButton->Name = L"FFBMonitorButton";
			this->FFBMonitorButton->Size = System::Drawing::Size(94, 24);
			this->FFBMonitorButton->TabIndex = 48;
			this->FFBMonitorButton->Text = L"FFB���j�^�[";
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
			this->TyreMonitorButton->Font = (gcnew System::Drawing::Font(L"BIZ UDP�S�V�b�N", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(128)));
			this->TyreMonitorButton->Location = System::Drawing::Point(469, 55);
			this->TyreMonitorButton->Name = L"TyreMonitorButton";
			this->TyreMonitorButton->Size = System::Drawing::Size(94, 24);
			this->TyreMonitorButton->TabIndex = 89;
			this->TyreMonitorButton->Text = L"�^�C�����j�^�[";
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
		if (!Profile::IsSameProfile(appProfile, loadProfile)) {//�ۑ�����Ă��Ȃ��ύX������ꍇ�A�m�F�_�C�A���O��\������
			// ���b�Z�[�W�{�b�N�X��\������
			System::String^ message = "�A�v���P�[�V���������Z�b�g���܂��B��낵���ł����H\n���ۑ�����Ă��Ȃ��ύX�͔j������܂��B";
			System::String^ title = "�A�v���P�[�V�����̃��Z�b�g";
			System::Windows::Forms::DialogResult dialogResult =
				System::Windows::Forms::MessageBox::Show(message, title, MessageBoxButtons::OKCancel, MessageBoxIcon::Warning);

			if (dialogResult != System::Windows::Forms::DialogResult::OK) {
				return;
			}
		}

		initialized = false;
		NetworkStart();
		initialized = DIInit(GetHInstance(), GetHWND());

		//�ߋ����̃��Z�b�g
		preAxisIndex = 0;
		preDeviceIndex = 0;
		

		//�Ō�ɑI������Ă����v���t�@�C�����A�f�o�C�X���A�g�p����ۑ����Ă���
		UpdateAppData(appData);
		SaveAppDataFile(appData);

		//�ύX��j��
		appProfile = loadProfile;

		//appData�̓ǂݍ��݂ƕt�����鏉����
		appData = LoadAppDataFile();
		DeviceListInit();
		AxisListInit();

		//�v���t�@�C��UI�̏�����
		ProfileRevertChangesButton->Enabled = false;
		ProfileDeleteButton->Enabled = false;
		ProfileSaveButton->Enabled = false;
		ProfileListInit();

		//UI�̏�����
		ProfileUIUpdate();
		ProfileButton_Update();
	}

	private: System::Void CheckBox_AlwaysOnTop_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
		this->TopMost = this->CheckBox_AlwaysOnTop->CheckState == CheckState::Checked;
	}

	private: System::Void CheckBox_InvertFFB_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
		appProfile.SetInvertFFB(CheckBox_InvertFFB->CheckState == CheckState::Checked);

		//�{�^���X�V
		ProfileButton_Update();
	}

	//���C���t�H�[���ǂݍ��ݎ�
	private: System::Void MainForm_Load(System::Object^  sender, System::EventArgs^  e) {
		initialized = false;
		NetworkStart();
		initialized = DIInit(GetHInstance(), GetHWND());
		//�t�H�[����TopMost�̏����ݒ�Ƀ`�F�b�N�{�b�N�X�̓��e����v������
		TopMost = false;
		CheckBox_AlwaysOnTop->CheckState = (TopMost) ? CheckState::Checked : CheckState::Unchecked;

		//appData�̓ǂݍ��݂ƕt�����鏉����
		appData = LoadAppDataFile();
		DeviceListInit();
		AxisListInit();

		//�v���t�@�C��UI�̏�����
		ProfileRevertChangesButton->Enabled = false;
		ProfileDeleteButton->Enabled = false;
		ProfileSaveButton->Enabled = false;
		ProfileListInit();

		//UI�̏�����
		ProfileUIUpdate();
		ProfileButton_Update();

		//UI�X�V//
		try
		{
			this->Invoke(gcnew Action(this, &MainForm::UIUpdate));
		}
		catch (...)
		{
		}
		//UI�X�V//

		//�^�C�}�[�N��
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
		//�f�t�H���g�����[�U�[�v���t�@�C��
		if (0 <= ProfileList->SelectedIndex && ProfileList->SelectedIndex < ProfileList->Items->Count - 1) {
			printf_s(msclr::interop::marshal_as<std::string>(ProfileList->SelectedItem->ToString()).c_str());
			//�Ō�ɑI������Ă����v���t�@�C�����A�f�o�C�X���A�g�p����ۑ����Ă���(����N�����ɑ��݂��Ă���Γǂݍ���)
			UpdateAppData(appData);
			SaveAppDataFile(appData);
		}

		DIRelease();
		NetworkClose();
	}

	private: System::Void NetworkStart() {
		id_max = 0;//�ŐV�̏���id�ԍ�

		NetworkClose();

		for (int i = 0; i < channel_max; ++i) {
			// WinSock�̏���������(Version 2.0)
			WSAStartup(MAKEWORD(2, 0), &wsa_data[i]);

			memset(&src_addr[i], 0, sizeof(src_addr[i]));
			src_addr[i].sin_port = htons(port_number + i);
			src_addr[i].sin_family = AF_INET;
			//src_addr[i].sin_addr.s_addr = inet_addr("127.0.0.1");
			InetPtonA(src_addr[i].sin_family, "127.0.0.1", &src_addr[i].sin_addr.S_un.S_addr);

			// AF_INET��ipv4��IP�v���g�R�� & SOCK_STREAM��TCP�v���g�R��
			src_socket[i] = socket(AF_INET, SOCK_STREAM, 0);

			// �T�[�o���̃\�P�b�g������IP�A�h���X�ƃ|�[�g�ɕR�t����
			if (bind(src_socket[i], (struct sockaddr *) &src_addr[i], sizeof(src_addr[i])) == SOCKET_ERROR) {
				auto e = WSAGetLastError();
				int breakpoint = 0;
			}

			u_long val = 1;
			ioctlsocket(src_socket[i], FIONBIO, &val);

			// �ڑ��̑Ҏ���J�n����
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

		//FFB�p�ʐM//
		for (int i = 0; i < channel_max; ++i) {
			std::string str = "";
			// �N���C�A���g����̐ڑ�����M����
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

						//��M�����̍��}�Ƃ��ĕ�����𑗂�
						send(dst_socket[i], "ffb", sizeof(char) * 4, 0);
						//��x�\�P�b�g���N���[�Y���Đڑ����Ȃ���(��������Ȃ���1�b�ԃ\�P�b�g�����b�N����Ă��܂�)
						closesocket(dst_socket[i]);
						dst_socket[i] = accept(src_socket[i], (struct sockaddr *) &dst_addr[i], &dst_addr_size);

						//��M�������`�����l���łȂ���΂���ȏ�̏����͂���Ȃ�
						if (i != channel) {
							continue;
						}

						timeoutTimer = timeoutTime;

						if (str.find(std::string("FFB_data=")) != std::string::npos) {
							std::string ffb_str = "";

							unsigned int start = (unsigned int)str.find(std::string("FFB_data=")) + 9;
							int end = (int)str.find(std::string("|END|"));
							if (end != std::string::npos) {
								//FFB�p�̃f�[�^�݂̂̕�����𒊏o����
								int len = end - start;
								ffb_str = str.substr(start, len);
							}
							start = 0;

							int id = GetParamInt(ffb_str, start);

							if (9000 < id_max) {
								if (id_max < id) {
									id_max = id;
								}
								else if (id < 1000) {//id�̐܂�Ԃ�
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
		//FFB�p�ʐM//
		bool isEnableGamePad = DIGetGamePadState(usingDeviceDID, diJoyState);

		//�ʐM���Ȃ��Ԃ�FFB��؂���id�����Z�b�g����
		if (timeoutTimer <= 0) {
			id_max = 0;
			carState.Reset();
			for (int i = 0; i < AXIS::MAX; ++i) {
				FFBReset(usingDeviceDID, i);
			}
		}
		
		FFBUpdate(usingDeviceDID, carState, diJoyState, usingAxisIndex, ffbBootCount / 60.f);

		//UI�X�V//
		try
		{
			this->Invoke(gcnew Action(this, &MainForm::UIUpdate));
		}
		catch (...)
		{
		}
		//UI�X�V//

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
		//GT Force Pro�ł̓���
		//diJoyState.lX;//�n���h��
		//diJoyState.lY;//�A�N�Z��
		//diJoyState.lRz;//�u���[�L
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
		//FFB���j�^�[
		FFBMonitor_Input_Axis = input;

		//�Q�[�W�̍X�V
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
				//�����A�j���[�V������L���ɂ���
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

	//�A���S���Y���F�^�C���Ɛi�s�����̊֌W��FFB�𐶐�����
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
	//			float maxTireAngle = 1;//�f�t�H���g�̃^�C���̍ő�p(�P��:rad)
	//			//(�I�v�V�����ŕύX�ł���悤�ɂ�����)
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
	//			if (tire2bodyVec < (4.92f * 3.6f)) {//4.92m/s����
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
	//		//FFB���j�^�[
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
	//		speed = min(speed, 1);//1 km/h �Ń_���p�[���y���Ȃ�
	//
	//		LONG coefficient = (1 - speed) * appProfile.GetStaticDamper() * ffb_multiply;
	//		//FFB���j�^�[
	//		FFBMonitor_Static_Dumper = coefficient;
	//
	//		//CenterDamper
	//		if (0 < appProfile.GetCenterDamperMax() && 0 < appProfile.GetCenterDamperZone()) {
	//			LONG diffHandle = combined_centerOffset - ((float)diJoyState.lX / DIAXIS_RANGE_MAX * 10000);
	//			float per = 1 - ((float)Math::Abs(diffHandle) / appProfile.GetCenterDamperZone());
	//			per = min(max(per, 0), 1);
	//
	//			coefficient += appProfile.GetCenterDamperMax() * per * ffb_multiply;
	//			//FFB���j�^�[
	//			FFBMonitor_Center_Dumper = appProfile.GetCenterDamperMax() * per * ffb_multiply;
	//		}
	//
	//		coefficient = min(coefficient, appProfile.GetMaxForce());
	//
	//		DISetFFB_Damper(did, coefficient);
	//		//FFB���j�^�[
	//		FFBMonitor_Total_Dumper = coefficient;
	//	}
	//}

	private: System::Void FFBReset(DIDEV did, int axis) {
		DISetFFB_Constant(did, (AXIS)axis, 0);
		DISetFFB_Friction(did, (AXIS)axis, 0);
		DISetFFB_Damper(did, (AXIS)axis, 0);
	}

	//�A���S���Y���F�^�C���̏�Ԃƈړ��x�N�g��������FFB�𐶐�����
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
		//FFB���]�̓K��
		if (appProfile.GetInvertFFB()) {
			input = -input;
			preInput = -preInput;
		}
	
		LONG combined_centerOffset = 0;

		//ExtendedCarState
		float gripSpeed = (4.92f * 3.6f);//4.92m/s
		float maxTireAngle = (appProfile.GetPivotWheelMode()) ? 
			(float)(appProfile.GetMaxTyreAngle() / 10000.f * (90 * Math::PI / 180.f)) : 
			(float)(appProfile.GetMaxTyreAngle() / 10000.f);//(�P��:rad)
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
				//�f�b�h�]�[������
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

		//�^�C�����j�^�[
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
					//FFB���]�̓K��
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
				//FFB���]�̓K��
				if (appProfile.GetInvertFFB()) {
					combined_centerOffset = -combined_centerOffset;
				}
				LONG combined_saturation = (LONG)(min(max(saturation[LEFT] + saturation[RIGHT], 0), appProfile.GetMaxForce()) * ffb_multiply);
				LONG combined_coefficient = (coefficient_[LEFT] + coefficient_[RIGHT]);

				coefficient += combined_coefficient;

				//FFB���j�^�[
				FFBMonitor_Movement_Force = combined_coefficient;
			}

			{//RotateForce
				LONG coefficient_[2] = { 0 };
				for (int i = 0; i < 2; ++i) {//i = LEFT, RIGHT
					if (!carState.tireOnGround[i]) { continue; }

					float paramScale = 6.f;
					coefficient_[i] = (LONG)(-carState.bodyRotateY[i] * appProfile.GetRotateForce() * tireGrip[i] * (appProfile.GetForceScale() / 100.f) * paramScale);

					//FFB���]�̓K��
					if (appProfile.GetInvertFFB()) {
						coefficient_[i] = -coefficient_[i];
					}

					coefficient += coefficient_[i];
				}
				//FFB���j�^�[
				FFBMonitor_Rotate_Force = coefficient_[LEFT] + coefficient_[RIGHT];
			}

			//MinForce�̓K��
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
				//FFB���]�𖳌���
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

			//FFB���j�^�[
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
				//FFB���j�^�[
				FFBMonitor_Grip_Friction = coefficient_[LEFT] + coefficient_[RIGHT];
			}

			{//StaticFriction
				LONG coefficient_[2] = { 0 };
				for (int i = 0; i < 2; ++i) {//i = LEFT, RIGHT
					if (!carState.tireOnGround[i]) { continue; }

					float bodySpeed_Abs = 0;
					bodySpeed_Abs = (float)Math::Sqrt((carState.bodySpeedX[i] * carState.bodySpeedX[i]) + (carState.bodySpeedZ[i] * carState.bodySpeedZ[i]));
					float speed = bodySpeed_Abs;
					speed = min(speed, 10);//10 km/h �Ń_���p�[���y���Ȃ�
					float per = (10 - speed) / 10.f;

					coefficient_[i] = (LONG)(per * appProfile.GetStaticFriction() / 2.f * (appProfile.GetForceScale() / 100.f) * tireGrip[i]);
					coefficient += coefficient_[i];
				}
				//FFB���j�^�[
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
				//FFB���j�^�[
				FFBMonitor_Center_Friction = coefficient_[LEFT] + coefficient_[RIGHT];
			}
	
			coefficient = (LONG)(min(coefficient, appProfile.GetMaxForce()) * ffb_multiply);
	
			DISetFFB_Friction(did, (AXIS)axis, coefficient);
			//FFB���j�^�[
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
		//start�����������I�[�o�[���Ă���
		if (str.length() <= start) return "";

		int end = (int)str.find(std::string(","), start);

		//,��������Ȃ�
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
		return decompressInt(compressed) / 10000000.f;//�����_�ȉ�7��
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
		DeviceList->SelectedIndex = 0;//��xNone�ɂ���

		int index = 0;
		int deviceCount = 0;
		for (int did = DID_GAMEPAD1; did < DID_MAX; ++did)
		{
			if (DIExistGamePad((DIDEV)did)) {
				DeviceList->Items->Add(DIGetGamePadName((DIDEV)did));
				deviceCount++;
				
				//���߂ɑI������f�o�C�X�𔭌�������index��ۑ����Ă���
				if (DIGetGamePadName_std((DIDEV)did) == appData.GetInitDeviceName()) {
					index = deviceCount;//�f�o�C�X��1����(0��"None")
				}
			}
		}

		DeviceList->SelectedIndex = index;
	}

	private: System::Void AxisListInit() {
		AxisList->SelectedIndex = appData.GetAxis(msclr::interop::marshal_as<std::string>(DeviceList->SelectedItem->ToString()));
	}

	private: System::Void UpdateAppData(AppData &appData) {
		//InitData�̍X�V
		appData.SetInitProfileName(msclr::interop::marshal_as<std::string>(ProfileList->SelectedItem->ToString()));
		if (0 < DeviceList->SelectedIndex) {//�Q�[���p�b�h��I�����Ă�ꍇ�̂ݏ㏑���ۑ�
			appData.SetInitDeviceName(msclr::interop::marshal_as<std::string>(DeviceList->SelectedItem->ToString()));
		}

		////AxisData�̍X�V(�Ō�ɑI������Ă����f�o�C�X�̂�)
		//�f�o�C�X�̎��ݒ��ۑ�
		if (0 < preDeviceIndex) {//�ڑ����ꂽ�f�o�C�X��I������Ă���
			appData.SetAxis(msclr::interop::marshal_as<std::string>(DeviceList->SelectedItem->ToString()), AxisList->SelectedIndex);
		}
	}

	private: System::Void DeviceList_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
		FFB_OFF();

		//�f�o�C�X�̎��ݒ��ۑ�
		if (0 < preDeviceIndex) {//�ڑ����ꂽ�f�o�C�X��I������Ă���
			appData.SetAxis(msclr::interop::marshal_as<std::string>(DeviceList->Items[preDeviceIndex]->ToString()), AxisList->SelectedIndex);
		}

		//DID�̐ݒ�
		int did_int = DID_NONE;
		if (0 < DeviceList->SelectedIndex) {
			did_int = DID_GAMEPAD1 + (DeviceList->SelectedIndex - 1);
		}
		usingDeviceDID = (DIDEV)did_int;

		//���̕ύX
		int axis = appData.GetAxis(msclr::interop::marshal_as<std::string>(DeviceList->SelectedItem->ToString()));
		if (AxisList->SelectedIndex != axis) {
			AxisList->SelectedIndex = axis;
		}

		preDeviceIndex = DeviceList->SelectedIndex;
	}

	private: System::Void AxisList_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
		FFB_OFF();

		usingAxisIndex = AxisList->SelectedIndex;

		//FFB���j�^�[
		FFBMonitor_Input_Axis_Name = msclr::interop::marshal_as<std::string>(AxisList->SelectedItem->ToString());

		preAxisIndex = AxisList->SelectedIndex;
	}

	private: System::Void TrackBar_MinForce_Scroll(System::Object^  sender, System::EventArgs^  e) {
		TrackBar_Scroll(TextBox_MinForce, TrackBar_MinForce);

		//MaxForce�Ƃ̐����������
		if (TrackBar_MaxForce->Value < TrackBar_MinForce->Value) {
			 TrackBar_MaxForce->Value = TrackBar_MinForce->Value;
			 TrackBar_Scroll(TextBox_MaxForce, TrackBar_MaxForce);
		}

		//OnTick���Ŏg����ϐ��ɑ��
		appProfile.SetMinForce(TrackBar_MinForce->Value);

		//FFB���j�^�[�͖���(�s�v)

		//�{�^���X�V
		ProfileButton_Update();
	}

	private: System::Void TextBox_MinForce_Leave(System::Object^  sender, System::EventArgs^  e) {
		TextBox_TextChanged(TextBox_MinForce, TrackBar_MinForce);

		//MaxForce�Ƃ̐����������
		if (TrackBar_MaxForce->Value < TrackBar_MinForce->Value) {
			TrackBar_MaxForce->Value = TrackBar_MinForce->Value;
			TrackBar_Scroll(TextBox_MaxForce, TrackBar_MaxForce);
		}

		//OnTick���Ŏg����ϐ��ɑ��
		appProfile.SetMinForce(TrackBar_MinForce->Value);

		//FFB���j�^�[�͖���(�s�v)

		//�{�^���X�V
		ProfileButton_Update();
	}

	private: System::Void TrackBar_MaxForce_Scroll(System::Object^  sender, System::EventArgs^  e) {
		TrackBar_Scroll(TextBox_MaxForce, TrackBar_MaxForce);

		//MinForce�Ƃ̐����������
		if (TrackBar_MaxForce->Value < TrackBar_MinForce->Value) {
			TrackBar_MinForce->Value = TrackBar_MaxForce->Value;
			TrackBar_Scroll(TextBox_MinForce, TrackBar_MinForce);
		}

		//OnTick���Ŏg����ϐ��ɑ��
		appProfile.SetMaxForce(TrackBar_MaxForce->Value);

		//FFB���j�^�[
		FFBMonitor_MaxForce = TrackBar_MaxForce->Value;

		//�{�^���X�V
		ProfileButton_Update();
	}

	private: System::Void TextBox_MaxForce_Leave(System::Object^  sender, System::EventArgs^  e) {
		TextBox_TextChanged(TextBox_MaxForce, TrackBar_MaxForce);

		//MinForce�Ƃ̐����������
		if (TrackBar_MaxForce->Value < TrackBar_MinForce->Value) {
			TrackBar_MinForce->Value = TrackBar_MaxForce->Value;
			TrackBar_Scroll(TextBox_MinForce, TrackBar_MinForce);
		}

		//OnTick���Ŏg����ϐ��ɑ��
		appProfile.SetMaxForce(TrackBar_MaxForce->Value);

		//FFB���j�^�[
		FFBMonitor_MaxForce = TrackBar_MaxForce->Value;

		//�{�^���X�V
		ProfileButton_Update();
	}

	private: System::Void TrackBar_DeadZoneInside_Scroll(System::Object^  sender, System::EventArgs^  e) {
		TrackBar_Scroll(TextBox_DeadZoneInside, TrackBar_DeadZoneInside, -2);

		//Outside�Ƃ̐����������
		if (TrackBar_DeadZoneOutside->Maximum - TrackBar_DeadZoneOutside->Value < TrackBar_DeadZoneInside->Value) {
			TrackBar_DeadZoneOutside->Value = TrackBar_DeadZoneInside->Maximum - TrackBar_DeadZoneInside->Value;
			TrackBar_Scroll(TextBox_DeadZoneOutside, TrackBar_DeadZoneOutside, -2);
		}

		//OnTick���Ŏg����ϐ��ɑ��
		appProfile.SetDeadZoneInside(TrackBar_DeadZoneInside->Value);
		appProfile.SetDeadZoneOutside(TrackBar_DeadZoneOutside->Value);

		//�{�^���X�V
		ProfileButton_Update();
	}

	private: System::Void TextBox_DeadZoneInside_Leave(System::Object^  sender, System::EventArgs^  e) {
		TextBox_TextChanged(TextBox_DeadZoneInside, TrackBar_DeadZoneInside, 2);

		//Outside�Ƃ̐����������
		if (TrackBar_DeadZoneOutside->Maximum - TrackBar_DeadZoneOutside->Value < TrackBar_DeadZoneInside->Value) {
			TrackBar_DeadZoneOutside->Value = TrackBar_DeadZoneInside->Maximum - TrackBar_DeadZoneInside->Value;
			TrackBar_Scroll(TextBox_DeadZoneOutside, TrackBar_DeadZoneOutside, -2);
		}

		//OnTick���Ŏg����ϐ��ɑ��
		appProfile.SetDeadZoneInside(TrackBar_DeadZoneInside->Value);
		appProfile.SetDeadZoneOutside(TrackBar_DeadZoneOutside->Value);

		//�{�^���X�V
		ProfileButton_Update();
	}

	private: System::Void TrackBar_DeadZoneOutside_Scroll(System::Object^  sender, System::EventArgs^  e) {
		TrackBar_Scroll(TextBox_DeadZoneOutside, TrackBar_DeadZoneOutside, -2);

		//Inside�Ƃ̐����������
		if (TrackBar_DeadZoneOutside->Maximum - TrackBar_DeadZoneOutside->Value < TrackBar_DeadZoneInside->Value) {
			TrackBar_DeadZoneInside->Value = TrackBar_DeadZoneOutside->Maximum - TrackBar_DeadZoneOutside->Value;
			TrackBar_Scroll(TextBox_DeadZoneInside, TrackBar_DeadZoneInside, -2);
		}

		//OnTick���Ŏg����ϐ��ɑ��
		appProfile.SetDeadZoneInside(TrackBar_DeadZoneInside->Value);
		appProfile.SetDeadZoneOutside(TrackBar_DeadZoneOutside->Value);

		//�{�^���X�V
		ProfileButton_Update();
	}

	private: System::Void TextBox_DeadZoneOutside_Leave(System::Object^  sender, System::EventArgs^  e) {
		TextBox_TextChanged(TextBox_DeadZoneOutside, TrackBar_DeadZoneOutside, 2);

		//Inside�Ƃ̐����������
		if (TrackBar_DeadZoneOutside->Maximum - TrackBar_DeadZoneOutside->Value < TrackBar_DeadZoneInside->Value) {
			TrackBar_DeadZoneInside->Value = TrackBar_DeadZoneOutside->Maximum - TrackBar_DeadZoneOutside->Value;
			TrackBar_Scroll(TextBox_DeadZoneInside, TrackBar_DeadZoneInside, -2);
		}

		//OnTick���Ŏg����ϐ��ɑ��
		appProfile.SetDeadZoneInside(TrackBar_DeadZoneInside->Value);
		appProfile.SetDeadZoneOutside(TrackBar_DeadZoneOutside->Value);

		//�{�^���X�V
		ProfileButton_Update();
	}

	private: System::Void TrackBar_ForceScale_Scroll(System::Object^  sender, System::EventArgs^  e) {
		TrackBar_Scroll(TextBox_ForceScale, TrackBar_ForceScale);

		//OnTick���Ŏg����ϐ��ɑ��
		appProfile.SetForceScale(TrackBar_ForceScale->Value);

		//�{�^���X�V
		ProfileButton_Update();
	}

	private: System::Void TextBox_ForceScale_Leave(System::Object^  sender, System::EventArgs^  e) {
		TextBox_TextChanged(TextBox_ForceScale, TrackBar_ForceScale);

		//OnTick���Ŏg����ϐ��ɑ��
		appProfile.SetForceScale(TrackBar_ForceScale->Value);

		//�{�^���X�V
		ProfileButton_Update();
	}

	private: System::Void TrackBar_MovementForce_Scroll(System::Object^  sender, System::EventArgs^  e) {
		TrackBar_Scroll(TextBox_MovementForce, TrackBar_MovementForce);

		//OnTick���Ŏg����ϐ��ɑ��
		appProfile.SetMovementForce(TrackBar_MovementForce->Value);

		//�{�^���X�V
		ProfileButton_Update();
	}

	private: System::Void TextBox_MovementForce_Leave(System::Object^  sender, System::EventArgs^  e) {
		TextBox_TextChanged(TextBox_MovementForce, TrackBar_MovementForce);

		//OnTick���Ŏg����ϐ��ɑ��
		appProfile.SetMovementForce(TrackBar_MovementForce->Value);

		//�{�^���X�V
		ProfileButton_Update();
	}

	private: System::Void TrackBar_RotateForce_Scroll(System::Object^  sender, System::EventArgs^  e) {
		TrackBar_Scroll(TextBox_RotateForce, TrackBar_RotateForce);

		//OnTick���Ŏg����ϐ��ɑ��
		appProfile.SetRotateForce(TrackBar_RotateForce->Value);

		//�{�^���X�V
		ProfileButton_Update();
	}

	private: System::Void TextBox_RotateForce_Leave(System::Object^  sender, System::EventArgs^  e) {
		TextBox_TextChanged(TextBox_RotateForce, TrackBar_RotateForce);

		//OnTick���Ŏg����ϐ��ɑ��
		appProfile.SetRotateForce(TrackBar_RotateForce->Value);

		//�{�^���X�V
		ProfileButton_Update();
	}

	private: System::Void TrackBar_CenterFrictionMax_Scroll(System::Object^  sender, System::EventArgs^  e) {
		TrackBar_Scroll(TextBox_CenterFrictionMax, TrackBar_CenterFrictionMax);

		//OnTick���Ŏg����ϐ��ɑ��
		appProfile.SetCenterFrictionMax(TrackBar_CenterFrictionMax->Value);

		//�{�^���X�V
		ProfileButton_Update();
	}


	private: System::Void TextBox_CenterFrictionMax_Leave(System::Object^  sender, System::EventArgs^  e) {
		TextBox_TextChanged(TextBox_CenterFrictionMax, TrackBar_CenterFrictionMax);

		//OnTick���Ŏg����ϐ��ɑ��
		appProfile.SetCenterFrictionMax(TrackBar_CenterFrictionMax->Value);

		//�{�^���X�V
		ProfileButton_Update();
	}

	private: System::Void TrackBar_CenterFrictionZone_Scroll(System::Object^  sender, System::EventArgs^  e) {
		TrackBar_Scroll(TextBox_CenterFrictionZone, TrackBar_CenterFrictionZone);

		//OnTick���Ŏg����ϐ��ɑ��
		appProfile.SetCenterFrictionZone(TrackBar_CenterFrictionZone->Value);

		//�{�^���X�V
		ProfileButton_Update();
	}


	private: System::Void TextBox_CenterFrictionZone_Leave(System::Object^  sender, System::EventArgs^  e) {
		TextBox_TextChanged(TextBox_CenterFrictionZone, TrackBar_CenterFrictionZone);

		//OnTick���Ŏg����ϐ��ɑ��
		appProfile.SetCenterFrictionZone(TrackBar_CenterFrictionZone->Value);

		//�{�^���X�V
		ProfileButton_Update();
	}

	private: System::Void TrackBar_GripFriction_Scroll(System::Object^  sender, System::EventArgs^  e) {
		TrackBar_Scroll(TextBox_GripFriction, TrackBar_GripFriction);

		//OnTick���Ŏg����ϐ��ɑ��
		appProfile.SetGripFriction(TrackBar_GripFriction->Value);

		//�{�^���X�V
		ProfileButton_Update();
	}

	private: System::Void TextBox_GripFriction_Leave(System::Object^  sender, System::EventArgs^  e) {
		TextBox_TextChanged(TextBox_GripFriction, TrackBar_GripFriction);

		//OnTick���Ŏg����ϐ��ɑ��
		appProfile.SetGripFriction(TrackBar_GripFriction->Value);

		//�{�^���X�V
		ProfileButton_Update();
	}

	private: System::Void TrackBar_StaticFriction_Scroll(System::Object^  sender, System::EventArgs^  e) {
		TrackBar_Scroll(TextBox_StaticFriction, TrackBar_StaticFriction);

		//OnTick���Ŏg����ϐ��ɑ��
		appProfile.SetStaticFriction(TrackBar_StaticFriction->Value);

		//�{�^���X�V
		ProfileButton_Update();
	}


	private: System::Void TextBox_StaticFriction_Leave(System::Object^  sender, System::EventArgs^  e) {
		TextBox_TextChanged(TextBox_StaticFriction, TrackBar_StaticFriction);

		//OnTick���Ŏg����ϐ��ɑ��
		appProfile.SetStaticFriction(TrackBar_StaticFriction->Value);

		//�{�^���X�V
		ProfileButton_Update();
	}

	private: System::Void TrackBar_TyreDynamicFrictionCoefficient_Scroll(System::Object^  sender, System::EventArgs^  e) {
		TrackBar_Scroll(TextBox_TyreDynamicFrictionCoefficient, TrackBar_TyreDynamicFrictionCoefficient);

		//OnTick���Ŏg����ϐ��ɑ��
		appProfile.SetTyreDynamicFrictionCoefficient(TrackBar_TyreDynamicFrictionCoefficient->Value);

		//�{�^���X�V
		ProfileButton_Update();
	}


	private: System::Void TextBox_TyreDynamicFrictionCoefficient_Leave(System::Object^  sender, System::EventArgs^  e) {
		TextBox_TextChanged(TextBox_TyreDynamicFrictionCoefficient, TrackBar_TyreDynamicFrictionCoefficient);

		//OnTick���Ŏg����ϐ��ɑ��
		appProfile.SetTyreDynamicFrictionCoefficient(TrackBar_TyreDynamicFrictionCoefficient->Value);

		//�{�^���X�V
		ProfileButton_Update();
	}

	private: System::Void TrackBar_SoftLockForce_Scroll(System::Object^  sender, System::EventArgs^  e) {
		TrackBar_Scroll(TextBox_SoftLockForce, TrackBar_SoftLockForce);

		//OnTick���Ŏg����ϐ��ɑ��
		appProfile.SetSoftLockForce(TrackBar_SoftLockForce->Value);

		//�{�^���X�V
		ProfileButton_Update();
	}


	private: System::Void TextBox_SoftLockForce_Leave(System::Object^  sender, System::EventArgs^  e) {
		TextBox_TextChanged(TextBox_SoftLockForce, TrackBar_SoftLockForce);

		//OnTick���Ŏg����ϐ��ɑ��
		appProfile.SetSoftLockForce(TrackBar_SoftLockForce->Value);

		//�{�^���X�V
		ProfileButton_Update();
	}

	private: System::Void TrackBar_MaxTyreAngle_Scroll(System::Object^  sender, System::EventArgs^  e) {
		TrackBar_Scroll(TextBox_MaxTyreAngle, TrackBar_MaxTyreAngle, -4);

		//OnTick���Ŏg����ϐ��ɑ��
		appProfile.SetMaxTyreAngle(TrackBar_MaxTyreAngle->Value);

		//deg�\�L���X�V
		DegTextUpdate(TrackBar_MaxTyreAngle->Value, appProfile.GetPivotWheelMode());

		//�{�^���X�V
		ProfileButton_Update();
	}

	private: System::Void TextBox_MaxTyreAngle_TextChanged(System::Object^ sender, System::EventArgs^  e) {
		//textbox����deg�\�L���X�V
		DegTextUpdate(ToInt(TextBox_MaxTyreAngle->Text, 4), appProfile.GetPivotWheelMode());
	}

	private: System::Void TextBox_MaxTyreAngle_Leave(System::Object^ sender, System::EventArgs^  e) {
		//textbox�ɐ��^�ς݂̒l��Ԃ�
		TextBox_TextChanged(TextBox_MaxTyreAngle, TrackBar_MaxTyreAngle, 4);

		//OnTick���Ŏg����ϐ��ɑ��
		appProfile.SetMaxTyreAngle(TrackBar_MaxTyreAngle->Value);

		//deg�\�L���X�V
		DegTextUpdate(TrackBar_MaxTyreAngle->Value, appProfile.GetPivotWheelMode());

		//�{�^���X�V
		ProfileButton_Update();
	}

	private: System::Void Text_MaxTyreAngleDeg_TextChanged(System::Object^ sender, System::EventArgs^  e) {
		//Text_MaxTyreAngleDeg->Location = Point(588 - Text_MaxTyreAngleDeg->Width, Text_MaxTyreAngleDeg->Location.Y);
	}

	private: System::Void DegTextUpdate(int param, bool PivotWheelMode) {
		//deg�\�L���X�V
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
		//deg�\�L���X�V
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

		//�{�^���X�V
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
		//���l�ϊ��ɑΉ����������݂̂̃R�s�[���쐬
		System::String ^str = "";
		array<wchar_t> ^trimChars = { ' ', '0' };
		int dotIndex = -1;
		for (int i = 0; i < text->Length; ++i) {
			if ('0' <= text[i] && text[i] <= '9') {
				str += text[i];
			}
			else if (text[i] == '.') {
				//2�߂�'.'���������ꍇ�A���l�ϊ��s�Ƃ���0��Ԃ�
				if (0 <= dotIndex) { return 0; }

				//'.'�̈ʒu�����L�^���Astr�ɂ͒ǉ����Ȃ�
				dotIndex = i;
			}
		}
		//'.'������ꍇ�A�s�v��0������
		if (0 <= dotIndex) {
			str = str->TrimEnd('0');
		}
		else {//'.'���Ȃ��ꍇ�A�����ɂ��邱�Ƃɂ���
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
			//�E����0��K�v���ǉ����ĕԂ�
			return xEy(param, digitShift).ToString();
		}
		else {
			if (param == 0) {//"0.00..."�ƂȂ�̂�"0"�ŕԂ�
				return "0";
			}
			System::String^ str = param.ToString();
			if (str->Length <= -digitShift) {//"0.00...1"�Ƃ��ɂȂ�p�^�[��
				System::String ^zero = "";
				for (int i = 0; i < 1 + (-(digitShift + str->Length)); ++i) {
					zero += "0";
				}
				return (zero->Insert(1, ".") + str)->TrimEnd('0');
			}
			else {//'.'��}�����邾���̃p�^�[��
				return str->Insert(str->Length + digitShift, ".")->Trim('0')->TrimEnd('.');
			}
		}
		return "";
	}

	//x*10��y���Ԃ�
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
		//textbox����trackbar�֒l�𑗂�
		int n = 0;
		Int32::TryParse(textbox->Text, n);
		n = min(max(n, trackbar->Minimum), trackbar->Maximum);

		trackbar->Value = n;

		//textbox�ɃN�����v�ς݂̒l��Ԃ�
		textbox->Text = n.ToString();
	}

	private: System::Void TextBox_TextChanged(TextBox ^textbox, TrackBar ^trackbar, int digitShift) {
		//textbox����trackbar�֒l�𑗂�
		int n = ToInt(textbox->Text, digitShift);
		n = min(max(n, trackbar->Minimum), trackbar->Maximum);

		trackbar->Value = n;

		//textbox�ɃN�����v�ς݂̒l��Ԃ�
		textbox->Text = ToString(n, -digitShift);
	}

	private: System::Void TrackBar_Scroll(TextBox ^textbox, TrackBar ^trackbar) {
		textbox->Text = trackbar->Value.ToString();
	}

	private: System::Void TrackBar_Scroll(TextBox ^textbox, TrackBar ^trackbar, int digitShift) {
		textbox->Text = ToString(trackbar->Value, digitShift);
	}

	private: System::Void TextBox_NumOnly_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
		//���l0�`9�ƃo�b�N�X�y�[�X�Ɖ��s�ȊO�������ꂽ���̓C�x���g���L�����Z������
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
		//���l0�`9��.�ƃo�b�N�X�y�[�X�Ɖ��s�ȊO�������ꂽ���̓C�x���g���L�����Z������
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

	//�v���t�@�C���ύX
	private: System::Void ProfileList_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
		//�O��I�������v���t�@�C���Ɠ����Ȃ牽�����Ȃ�
		if (ProfileList->SelectedIndex == preProfileIndex) { return; }

		FFB_OFF();

		if (!Profile::IsSameProfile(appProfile, loadProfile)) {//�ۑ�����Ă��Ȃ��ύX������ꍇ�A�m�F�_�C�A���O��\������
			// ���b�Z�[�W�{�b�N�X��\������
			System::String^ message = "�ۑ�����Ă��Ȃ��ύX������܂��B�ۑ����܂����H";
			System::String^ title = "�ύX�̕ۑ�";
			System::Windows::Forms::DialogResult dialogResult =
				System::Windows::Forms::MessageBox::Show(this, message, title, MessageBoxButtons::YesNoCancel, MessageBoxIcon::Warning);

			if (dialogResult == System::Windows::Forms::DialogResult::Cancel) {
				ProfileList->SelectedIndex = preProfileIndex;
				return;
			}
			else if (dialogResult == System::Windows::Forms::DialogResult::Yes) {
				if (0 < preProfileIndex && preProfileIndex < ProfileList->Items->Count - 1) {
					if (SaveProfile(appProfile, msclr::interop::marshal_as<std::string>(ProfileList->Items[preProfileIndex]->ToString()))) {
						//loadProfile�̍X�V
						loadProfile = appProfile;
						// ���b�Z�[�W�{�b�N�X��\������
						System::String^ message = "�ύX��ۑ����܂���";
						System::String^ title = "�ύX�̕ۑ�";
						System::Windows::Forms::DialogResult dialogResult =
							System::Windows::Forms::MessageBox::Show(this, message, title, MessageBoxButtons::OK, MessageBoxIcon::None);
					}
					else {
						// ���b�Z�[�W�{�b�N�X��\������
						System::String^ message = "�ۑ��Ɏ��s���܂���";
						System::String^ title = "�ύX�̕ۑ�";
						System::Windows::Forms::DialogResult dialogResult =
							System::Windows::Forms::MessageBox::Show(this, message, title, MessageBoxButtons::OK, MessageBoxIcon::Error);
					}
				}
				else if (preProfileIndex == 0) {
					//�f�t�H���g�v���t�@�C���̏ꍇ�V�K�쐬�t�H�[����\������
					CreateProfileForm form;
					std::string createProfileName = "";
					form.SetData(&appProfile, &createProfileName);
					form.StartPosition = FormStartPosition::CenterScreen;//��ʂ̒��S�ɕ\��������(���b�Z�[�W�{�b�N�X�ɍ��킹��)
					form.ShowDialog(this);
					//�V�K�쐬����Ă�����
					if (createProfileName != "") {
						// ���b�Z�[�W�{�b�N�X��\������
						System::String^ message = "�ύX��ۑ����܂���";
						System::String^ title = "�ύX�̕ۑ�";
						System::Windows::Forms::DialogResult dialogResult =
							System::Windows::Forms::MessageBox::Show(this, message, title, MessageBoxButtons::OK, MessageBoxIcon::None);
					}
					else {
						//�V�K�쐬���Ȃ������ꍇ�L�����Z������
						ProfileList->SelectedIndex = preProfileIndex;
						return;
					}

					//�ύX��j�����Ă���
					appProfile = loadProfile;

					ProfileListInit();
					int index = ProfileList->FindStringExact(msclr::interop::marshal_as<System::String^>(createProfileName));
					if (0 < index) {//�v���t�@�C�����������Ă�����
						ProfileList->SelectedIndex = index;
					}
					else {
						//�������s����Default�ɂ���
						ProfileList->SelectedIndex = 0;
					}
					return;
				}
			}
			else if (dialogResult == System::Windows::Forms::DialogResult::No) {
				//�ύX��j��
				appProfile = loadProfile;
			}
		}

		//UI�X�V
		ProfileUIUpdate();
		//�{�^���X�V
		ProfileButton_Update();

		//�I�����ꂽ�v���t�@�C����ǂݍ���
		if (0 < ProfileList->SelectedIndex && ProfileList->SelectedIndex < ProfileList->Items->Count - 1) {
			loadProfile = LoadProfile(msclr::interop::marshal_as<std::string>(ProfileList->SelectedItem->ToString()));
			appProfile = loadProfile;
		}
		//Default
		else if (ProfileList->SelectedIndex == 0) {
			loadProfile = Profile();
			appProfile = loadProfile;
		}
		//�V�K�쐬
		else if (ProfileList->SelectedIndex == ProfileList->Items->Count - 1) {
			CreateProfileForm form;
			std::string createProfileName = "";
			Profile defaultProfile = Profile();
			form.SetData(&defaultProfile, &createProfileName);
			form.StartPosition = FormStartPosition::CenterParent;//�e�̒��S�ɕ\��������
			form.ShowDialog(this);
			//�V�K�쐬����Ă�����
			if (createProfileName != ""){
				ProfileListInit();
				//�ǉ����ꂽ�v���t�@�C�����������ăC���f�b�N�X��ύX����
				int index = ProfileList->FindStringExact(msclr::interop::marshal_as<System::String^>(createProfileName));
				if (0 < index) {//�v���t�@�C�����������Ă�����
					ProfileList->SelectedIndex = index;
				}
				else {
					//�������s����Default�ɂ���
					ProfileList->SelectedIndex = 0;
				}
			}
			//�V�K�쐬����Ă��Ȃ�
			else {
				ProfileList->SelectedIndex = preProfileIndex;
			}
		}

		//UI�X�V
		ProfileUIUpdate();

		//�{�^���X�V
		ProfileButton_Update();

		preProfileIndex = ProfileList->SelectedIndex;
	}

	private: System::Void ProfileRevertChangesButton_Click(System::Object^  sender, System::EventArgs^  e) {
		// ���b�Z�[�W�{�b�N�X��\������
		System::String^ message = "�ۑ�����Ă��Ȃ��ύX��j�����܂��B��낵���ł����H\n�����̑���͌��ɖ߂��܂���B";
		System::String^ title = "�ύX�̔j��";
		System::Windows::Forms::DialogResult dialogResult =
			System::Windows::Forms::MessageBox::Show(message, title, MessageBoxButtons::OKCancel, MessageBoxIcon::Warning);

		if (dialogResult == System::Windows::Forms::DialogResult::OK) {
			//���[�h���Ă���v���t�@�C���ݒ�ɖ߂�
			appProfile = loadProfile;
			//UI�X�V
			ProfileUIUpdate();
			//�{�^���X�V
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
			// ���b�Z�[�W�{�b�N�X��\������
			System::String^ message = "�v���t�@�C�� �u" + ProfileList->SelectedItem->ToString() + "�v ���폜���܂��B��낵���ł����H\n�����̑���͌��ɖ߂��܂���B";
			System::String^ title = "�v���t�@�C���̍폜";
			System::Windows::Forms::DialogResult dialogResult =
				System::Windows::Forms::MessageBox::Show(message, title, MessageBoxButtons::OKCancel, MessageBoxIcon::Warning);

			if (dialogResult == System::Windows::Forms::DialogResult::OK) {
				if (DeleteProfile(msclr::interop::marshal_as<std::string>(ProfileList->SelectedItem->ToString()))) {
					auto deleteitem = ProfileList->SelectedItem;//�I�𒆂̃v���t�@�C�����폜�Ώ�
					ProfileList->SelectedIndex = 0;//�C���f�b�N�X��Default�ɂ���
					ProfileList->Items->Remove(deleteitem);//�v���t�@�C�����X�g����폜
				}
				else {
					//�폜�Ɏ��s�����ꍇ�A�v���t�@�C���t�H���_�ɕύX���������\��������̂ŁA�v���t�@�C�����X�g���X�V����
					ProfileListInit();
				}
			}
		}
	}
			 
	private: System::Void ProfileListInit() {
		ProfileList->Items->Clear();//���ڑS�폜
		ProfileList->Items->Add("Default");
		ProfileList->SelectedIndex = 0;//��xDefault�ɂ���
		int index = 0;
		std::string firstProfileName = appData.GetInitProfileName();
		std::vector<std::string> fileNames = GetProfilesName(Profile::FolderName(), Profile::FileExtension());
		for (unsigned int i = 0; i < fileNames.size(); ++i) {
			ProfileList->Items->Add(msclr::interop::marshal_as<System::String^>(fileNames[i]));

			//���߂ɓǂݍ��ރv���t�@�C���𔭌�������index��ۑ����Ă���
			if (fileNames[i] == firstProfileName) {
				index = i + 1;//���[�U�[�v���t�@�C����1����Ȃ̂�+1
			}
		}
		ProfileList->Items->Add("�{�V�K�쐬");
		ProfileList->SelectedIndex = index;//�ۑ����Ă���index��I������
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

		//���[�h���Ă���v���t�@�C���ݒ�Ɠ������l�ɂȂ��Ă���Ώ㏑���ۑ��{�^���𖳌���
		if (isSameProfile)
		{
			ProfileSaveButton->Enabled = false;
			ProfileRevertChangesButton->Enabled = false;
		}

		//�㏑���ۑ��ɑΉ������v���t�@�C���Ȃ�L����
		if(!isSameProfile && isUserProfile)
		{
			ProfileSaveButton->Enabled = true;
			ProfileRevertChangesButton->Enabled = true;
		}

		//Default�v���t�@�C���Ȃ�L����
		if (!isSameProfile && isDefaultProfile) {
			ProfileRevertChangesButton->Enabled = true;
		}

		//Default�Ɠ����ݒ�łȂ������[�U�[�v���t�@�C����Default�v���t�@�C���Ȃ�L����
		ProfileReturnToDefaultButton->Enabled = !isDefaultParam && (isUserProfile || isDefaultProfile);
		
		//���[�U�[�v���t�@�C���̂ݍ폜�{�^����L����
		ProfileDeleteButton->Enabled = isUserProfile;

		//�V�K�쐬���łȂ���ΗL����
		ProfileCopyButton->Enabled = !isCreateProfile;
	}

	private: System::Void ReturnToDefaultButton_Click(System::Object^  sender, System::EventArgs^  e) {
		// ���b�Z�[�W�{�b�N�X��\������
		System::String^ message = "�v���t�@�C�� �u" + ProfileList->SelectedItem->ToString() + "�v �������ݒ�ɖ߂��܂��B��낵���ł����H\n�����̑���͌��ɖ߂��܂���B";
		System::String^ title = "�v���t�@�C���̏�����";
		System::Windows::Forms::DialogResult dialogResult =
			System::Windows::Forms::MessageBox::Show(message, title, MessageBoxButtons::OKCancel, MessageBoxIcon::Warning);

		if (dialogResult == System::Windows::Forms::DialogResult::OK) {
			//�f�t�H���g�l�ɖ߂�
			appProfile = Profile();
			//UI�X�V
			ProfileUIUpdate();
			//�{�^���X�V
			ProfileButton_Update();
		}
	}

	private: System::Void ProfileCopyButton_Click(System::Object^  sender, System::EventArgs^  e) {
		CopyProfileForm form;
		std::string dsestinationName = "";
		form.SetData(ProfileList, appProfile, &dsestinationName);
		form.StartPosition = FormStartPosition::CenterParent;//�e�̒��S�ɕ\��������
		form.ShowDialog(this);

		//�R�s�[����Ă���
		if (dsestinationName != "") {
			//�ύX�͔j������(�R�s�[��ɕύX��̃v���t�@�C�����ۑ�����Ă���ׁA���[�U�[�ւ̌x���͖���)
			appProfile = loadProfile;

			//�V�K�쐬����Ă���\�������邽�߃v���t�@�C�����X�g���X�V
			appData.SetInitProfileName(dsestinationName);
			ProfileListInit();
		}

		//�v���t�@�C��UI�X�V
		ProfileUIUpdate();

		//�{�^���X�V
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

		//���ׂĂ�FFB��؂�
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
		//FFB��~
		FFB_OFF();

		//�^�C���A�E�g�����ɂ��ăI�����C���\���������Ȃ��悤�ɂ���
		timeoutTimer = 0;

		//�`�����l���ύX�̓K��(0 origin�ɕϊ�)
		channel = System::Decimal::ToInt32(ChannelSelectBox->Value) - 1;
	}
};
}