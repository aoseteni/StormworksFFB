#pragma once

#include <stdio.h>
#include <dinput.h>
#include <string>


#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")


// デバイス指定
enum DIDEV {
	DID_NONE,
	DID_KEYBOARD, // キーボード
	DID_MOUSE, // マウス
	DID_GAMEPAD1, // ゲームパッド
	DID_GAMEPAD2,
	DID_GAMEPAD3,
	DID_GAMEPAD4,
	DID_GAMEPAD5,
	DID_GAMEPAD6,
	DID_GAMEPAD7,
	DID_GAMEPAD8,
	DID_GAMEPAD9,
	DID_GAMEPAD10,
	DID_GAMEPAD11,
	DID_GAMEPAD12,

	DID_MAX // デバイス最大数
};

enum {
	DIAXIS_RANGE_MIN = -10000,
	DIAXIS_RANGE_MAX = 10000,
	DIAXIS_RANGE_CENTER = (DIAXIS_RANGE_MAX + DIAXIS_RANGE_MIN + 1) / 2
};

enum AXIS {
	X,
	Y,
	Z,
	RX,
	RY,
	RZ,

	MAX
};

bool DIInit(const HINSTANCE hInstance, const HWND hWnd);
void DIRelease();
bool DIInitKeyboard(const HWND hWnd);
bool DIInitMouse(const HWND hWnd);
bool DIInitGamePad(const HWND hWnd);
BOOL CALLBACK DIEnumGamePadProc(LPDIDEVICEINSTANCE lpDIDInst, LPVOID lpRef);
BOOL CALLBACK DIEnumGamePadAxesProc(LPCDIDEVICEOBJECTINSTANCE lpDIDObjInst, LPVOID lpRef);
BOOL CALLBACK DIEnumGamePadEffectsProc(LPCDIEFFECTINFO lpDIEffectInfo, LPVOID lpRef);
void DIReleaseDevice(const DIDEV did);
bool DIGetKeyboardState(BYTE byKeyState[]);
bool DIGetMouseState(DIMOUSESTATE& diMouseState);
bool DIGetGamePadState(const DIDEV did, DIJOYSTATE& diGamePadState);
LONG DISetFFB_Spring(const DIDEV did, AXIS axis, LONG centerOffset, LONG saturation, LONG coefficient, LONG centering=0);
void DISetFFB_Damper(const DIDEV did, AXIS axis, LONG coefficient);
void DISetFFB_Friction(const DIDEV did, AXIS axis, LONG coefficient);
void DISetFFB_Constant(const DIDEV did, AXIS axis, LONG coefficient);
void DISetFFB_Inertia(const DIDEV did, AXIS axis, LONG coefficient);
DWORD AXIS_Convert(AXIS axis);
System::String^ DIGetGamePadName(const DIDEV did);
std::string DIGetGamePadName_std(const DIDEV did);
bool DIExistGamePad(const DIDEV did);