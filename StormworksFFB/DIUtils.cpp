#include "DIUtils.h"
#include <math.h>
#define M_PI        3.14159265358979323846264338327950288

static LPDIRECTINPUT8 g_lpDInput8 = NULL;
static LPDIRECTINPUTDEVICE8 g_lpDIDevice8[DID_MAX] = { NULL }; // DirectInputDevice8�I�u�W�F�N�g
static LPDIRECTINPUTEFFECT lpDIEffect_spring[AXIS::MAX] = { NULL };//FFB�p�G�t�F�N�g�I�u�W�F�N�g
static LPDIRECTINPUTEFFECT lpDIEffect_damper[AXIS::MAX] = { NULL };//FFB�p�G�t�F�N�g�I�u�W�F�N�g
static LPDIRECTINPUTEFFECT lpDIEffect_friction[AXIS::MAX] = { NULL };//FFB�p�G�t�F�N�g�I�u�W�F�N�g
static LPDIRECTINPUTEFFECT lpDIEffect_constant[AXIS::MAX] = { NULL };//FFB�p�G�t�F�N�g�I�u�W�F�N�g
static LPDIRECTINPUTEFFECT lpDIEffect_inertia[AXIS::MAX] = { NULL };//FFB�p�G�t�F�N�g�I�u�W�F�N�g


bool DIInit(const HINSTANCE hInstance, const HWND hWnd)
{
	DIRelease();

	if (DI_OK != DirectInput8Create(hInstance, 0x0800, IID_IDirectInput8, (LPVOID*)&g_lpDInput8, NULL)) {
		// �������s
		//printf_s("DirectInput8�I�u�W�F�N�g�������s(DIInit)\n");
		return false;
	}

	bool init = false;

	// �L�[�{�[�h������
	if (DIInitKeyboard(hWnd)) {
		init = true;
	}

	// �}�E�X������
	if (DIInitMouse(hWnd)) {
		init = true;
	}

	// �Q�[���p�b�h������
	if (DIInitGamePad(hWnd)) {
		init = true;
	}

	if (!init) {
		DIRelease();
	}
	

	return true;
}

void DIRelease()
{
	// �G�t�F�N�g�I�u�W�F�N�g�̉��
	for each (auto object in lpDIEffect_spring)
	{
		if (object) {
			object->Unload();// �A�����[�h
			object->Release();// ���
			object = NULL;
		}
	}
	for each (auto object in lpDIEffect_damper)
	{
		if (object) {
			object->Unload();// �A�����[�h
			object->Release();// ���
			object = NULL;
		}
	}
	for each (auto object in lpDIEffect_constant)
	{
		if (object) {
			object->Unload();// �A�����[�h
			object->Release();// ���
			object = NULL;
		}
	}
	for each (auto object in lpDIEffect_inertia)
	{
		if (object) {
			object->Unload();// �A�����[�h
			object->Release();// ���
			object = NULL;
		}
	}

	//if (lpDIEffect_spring) {
	//	lpDIEffect_spring->Unload(); // �A�����[�h
	//	lpDIEffect_spring->Release(); // ���
	//	lpDIEffect_spring = NULL;
	//}
	//if (lpDIEffect_damper) {
	//	lpDIEffect_damper->Unload(); // �A�����[�h
	//	lpDIEffect_damper->Release(); // ���
	//	lpDIEffect_damper = NULL;
	//}
	//if (lpDIEffect_constant) {
	//	lpDIEffect_constant->Unload(); // �A�����[�h
	//	lpDIEffect_constant->Release(); // ���
	//	lpDIEffect_constant = NULL;
	//}
	//if (lpDIEffect_inertia) {
	//	lpDIEffect_inertia->Unload(); // �A�����[�h
	//	lpDIEffect_inertia->Release(); // ���
	//	lpDIEffect_inertia = NULL;
	//}
	

	// �f�o�C�X�I�u�W�F�N�g���
	for (int did = 0; did < DID_MAX; did++)
		DIReleaseDevice((DIDEV)did);


	// DirectInput8�I�u�W�F�N�g���
	if (NULL != g_lpDInput8) { // �|�C���^�`�F�b�N�BNULL�̏ꍇ�͉�����Ȃ�(����K�v���Ȃ�)
		g_lpDInput8->Release(); // DirectInput8�I�u�W�F�N�g���
		g_lpDInput8 = NULL; // NULL�������A�����ȃI�u�W�F�N�g�ł��邱�Ƃ�����
	}
}

bool DIInitKeyboard(const HWND hWnd)
{
#ifdef _DEBUG
	if (NULL == g_lpDInput8) {
		//printf_s("*** Error - DirectInput��������(DIInitKeyboard)\n");
		return false;
	}
#endif
	DIReleaseDevice(DID_KEYBOARD);
	// �f�o�C�X�I�u�W�F�N�g����
	if (DI_OK != g_lpDInput8->CreateDevice(GUID_SysKeyboard, &g_lpDIDevice8[DID_KEYBOARD], NULL))
		return false;
	// �f�[�^�t�H�[�}�b�g�ݒ�
	if (DI_OK != g_lpDIDevice8[DID_KEYBOARD]->SetDataFormat(&c_dfDIKeyboard)) {
		//printf_s("*** Error - �f�[�^�t�H�[�}�b�g�ݒ莸�s(DIInitKeyboard)\n");
		DIReleaseDevice(DID_KEYBOARD);
		return false;
	}
	// �������x���ݒ�
	if (DI_OK != g_lpDIDevice8[DID_KEYBOARD]->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)) {
		//printf_s("*** Error - �������x���ݒ莸�s(DIInitKeyboard)\n");
		DIReleaseDevice(DID_KEYBOARD);
		return false;
	}
	// �A�N�Z�X���擾
	g_lpDIDevice8[DID_KEYBOARD]->Acquire();

	return true;
}

bool DIInitMouse(const HWND hWnd)
{
#ifdef _DEBUG
	if (NULL == g_lpDInput8) {
		//printf_s("*** Error - DirectInput��������(DIInitMouse)\n");
		return false;
	}
#endif
	DIReleaseDevice(DID_MOUSE);
	// �f�o�C�X�I�u�W�F�N�g����
	if (DI_OK != g_lpDInput8->CreateDevice(GUID_SysMouse, &g_lpDIDevice8[DID_MOUSE], NULL))
		return false;
	// �f�[�^�t�H�[�}�b�g�ݒ�
	if (DI_OK != g_lpDIDevice8[DID_MOUSE]->SetDataFormat(&c_dfDIMouse)) {
		//printf_s("*** Error - �f�[�^�t�H�[�}�b�g�ݒ莸�s(DIInitMouse)\n");
		DIReleaseDevice(DID_MOUSE);
		return false;
	}
	// �������x���ݒ�
	if (DI_OK != g_lpDIDevice8[DID_MOUSE]->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)) {
		//printf_s("*** Error - �������x���ݒ莸�s(DIInitMouse)\n");
		DIReleaseDevice(DID_MOUSE);
		return false;
	}
	// �A�N�Z�X���擾
	g_lpDIDevice8[DID_MOUSE]->Acquire();
	return true;
}

bool DIInitGamePad(const HWND hWnd)
{
#ifdef _DEBUG
	if (NULL == g_lpDInput8) {
		//printf_s("*** Error - DirectInput��������(DIInitGamePad)\n");
		return false;
	}
#endif
	for (int i = DID_GAMEPAD1; i < DID_MAX; i++)
		DIReleaseDevice((DIDEV)i);
	// �Q�[���p�b�h��
	//g_lpDInput8->EnumDevices(DI8DEVCLASS_GAMECTRL, (LPDIENUMDEVICESCALLBACK)DIEnumGamePadProc, hWnd, DIEDFL_FORCEFEEDBACK | DIEDFL_ATTACHEDONLY);//FFB�Ή��R���g���[���[�̂ݎ擾
	g_lpDInput8->EnumDevices(DI8DEVCLASS_GAMECTRL, (LPDIENUMDEVICESCALLBACK)DIEnumGamePadProc, hWnd, DIEDFL_ATTACHEDONLY);//�ʏ�R���g���[���[���擾�ł���
	if (NULL == g_lpDIDevice8[DID_GAMEPAD1]) {
		//printf_s("*** Error - �Q�[���p�b�h�I�u�W�F�N�g�������s(DICreateGamePad)\n");
		return false;
	}
	for (int i = DID_GAMEPAD1; i < DID_MAX; i++) {
		if (g_lpDIDevice8[i]) {
			// �A�N�Z�X���擾
			g_lpDIDevice8[i]->Acquire();
		}
	}
	return true;
}

BOOL CALLBACK DIEnumGamePadProc(LPDIDEVICEINSTANCE lpDIDInst, LPVOID lpRef)
{
	int did = DID_GAMEPAD1;
	while (NULL != g_lpDIDevice8[did]) {
		did++;
		if (DID_MAX <= did) {
			return DIENUM_STOP;
		}
	}
	//�Q�[���p�b�h�����o��
	//wprintf_s(lpDIDInst->tszProductName);
	//printf_s("\n");
	

	// �Q�[���p�b�h�I�u�W�F�N�g����
	if (DI_OK != g_lpDInput8->CreateDevice(lpDIDInst->guidInstance, &g_lpDIDevice8[did], NULL)) {
		//printf_s("*** Error - �Q�[���p�b�h�I�u�W�F�N�g�������s(DIEnumGamePadProc)\n");
		return DIENUM_CONTINUE; // ���̃Q�[���p�b�h��
	}
	// �f�[�^�t�H�[�}�b�g�ݒ�
	if (DI_OK != g_lpDIDevice8[did]->SetDataFormat(&c_dfDIJoystick)) {
		//printf_s("*** Error - �f�[�^�t�H�[�}�b�g�ݒ莸�s(DIEnumGamePadProc)\n");
		DIReleaseDevice((DIDEV)did);
		return DIENUM_CONTINUE;
	}
	// �������x���ݒ�
	if (DI_OK != g_lpDIDevice8[did]->SetCooperativeLevel((HWND)lpRef, DISCL_BACKGROUND | DISCL_EXCLUSIVE)) {
		//printf_s("*** Error - �������x���ݒ莸�s(DIEnumGamePadProc)\n");
		DIReleaseDevice((DIDEV)did);
		return DIENUM_CONTINUE;
	}
	// �o�b�t�@�T�C�Y�ݒ�
	DIPROPDWORD dipd;
	ZeroMemory(&dipd, sizeof(dipd));
	dipd.diph.dwSize = sizeof(dipd);
	dipd.diph.dwHeaderSize = sizeof(dipd.diph);
	dipd.diph.dwObj = 0;
	dipd.diph.dwHow = DIPH_DEVICE;
	dipd.dwData = 0; // �o�b�t�@�̐�
	
	if (FAILED(g_lpDIDevice8[did]->SetProperty(DIPROP_BUFFERSIZE, &dipd.diph))) {
		//printf_s("*** Error - �o�b�t�@�T�C�Y�ݒ莸�s(DIEnumGamePadProc)\n");
		DIReleaseDevice((DIDEV)did);
		return DIENUM_CONTINUE;
	}
	// ���̗�
	if (FAILED(g_lpDIDevice8[did]->EnumObjects((LPDIENUMDEVICEOBJECTSCALLBACK)DIEnumGamePadAxesProc, (LPVOID)did, DIDFT_AXIS))) {
		DIReleaseDevice((DIDEV)did);
		return DIENUM_CONTINUE;
	}
	return DIENUM_CONTINUE;
}

BOOL CALLBACK DIEnumGamePadAxesProc(LPCDIDEVICEOBJECTINSTANCE lpDIDObjInst, LPVOID lpRef)
{
	//printf_s("��: ");
	//wprintf_s(lpDIDObjInst->tszName);
	//wprintf_s(L"\n");
	g_lpDIDevice8[(int)lpRef]->EnumEffects((LPDIENUMEFFECTSCALLBACK)DIEnumGamePadEffectsProc, lpRef, NULL);

	// ��Ύ��̏ꍇ�A���͈̔͂�ݒ�
	if (0 != (lpDIDObjInst->dwType & DIDFT_ABSAXIS)) {
		DIPROPRANGE dipr;
		dipr.diph.dwSize = sizeof(dipr);
		dipr.diph.dwHeaderSize = sizeof(dipr.diph);
		dipr.diph.dwHow = DIPH_BYID;
		dipr.diph.dwObj = lpDIDObjInst->dwType;
		dipr.lMin = DIAXIS_RANGE_MIN;
		dipr.lMax = DIAXIS_RANGE_MAX;
		g_lpDIDevice8[(int)lpRef]->SetProperty(DIPROP_RANGE, &dipr.diph);
		//if (FAILED(g_lpDIDevice8[(int)lpRef]->SetProperty(DIPROP_RANGE, &dipr.diph)))
			//printf_s("*** Error - ���͈͐ݒ莸�s(DISetAxesProp)\n");
	}
	// �f�b�h�]�[���ݒ�
	DIPROPDWORD dipdw;
	dipdw.diph.dwSize = sizeof(dipdw);
	dipdw.diph.dwHeaderSize = sizeof(dipdw.diph);;
	dipdw.diph.dwHow = DIPH_BYID;
	dipdw.diph.dwObj = lpDIDObjInst->dwType;
	dipdw.dwData = 0;
	g_lpDIDevice8[(int)lpRef]->SetProperty(DIPROP_DEADZONE, &dipdw.diph);
	//if (FAILED(g_lpDIDevice8[(int)lpRef]->SetProperty(DIPROP_DEADZONE, &dipdw.diph)))
		//printf_s("*** Error - �f�b�h�]�[���ݒ莸�s(DISetAxesProp)\n");

	return DIENUM_CONTINUE;
}

BOOL CALLBACK DIEnumGamePadEffectsProc(LPCDIEFFECTINFO lpDIEffectInfo, LPVOID lpRef) {
	//wprintf_s(lpDIEffectInfo->tszName);
	//wprintf_s(L"\n");
	return DIENUM_CONTINUE;
}

void DIReleaseDevice(const DIDEV did)
{
	if (did < 0 || DID_MAX <= did) {
		return;
	}
	if (NULL == g_lpDIDevice8[did])
		return;
	g_lpDIDevice8[did]->Unacquire();
	g_lpDIDevice8[did]->Release();
	g_lpDIDevice8[did] = NULL;
}

bool DIGetKeyboardState(BYTE byKeyState[])
{
	ZeroMemory(byKeyState, 256); // �z����[���N���A
	if (NULL == g_lpDIDevice8[DID_KEYBOARD]) {
		//printf_s("*** Error - �L�[�{�[�h��������(DIGetKeyboardState)\n");
		return false;
	}
	HRESULT hr = g_lpDIDevice8[DID_KEYBOARD]->GetDeviceState(256, byKeyState);
	if (DI_OK != hr) {
		if (DIERR_INPUTLOST == hr || DIERR_NOTACQUIRED == hr)
		{
			hr = g_lpDIDevice8[DID_KEYBOARD]->Acquire(); // �A�N�Z�X���̍Ď擾
		}
		//printf_s("*** Error - �L�[�{�[�h��Ԏ擾���s(DIGetKeyboardState)\n");
		return false;
	}
	return true;
}

bool DIGetMouseState(DIMOUSESTATE& diMouseState)
{
	ZeroMemory(&diMouseState, sizeof(diMouseState)); // �\���̂��[���N���A
	if (NULL == g_lpDIDevice8[DID_MOUSE]) {
		//printf_s("*** Error - �}�E�X��������(DIGetMouseState)\n");
		return false;
	}
	const HRESULT hr = g_lpDIDevice8[DID_MOUSE]->GetDeviceState(sizeof(diMouseState), &diMouseState);
	if (DI_OK != hr) {
		if (DIERR_INPUTLOST == hr || DIERR_NOTACQUIRED == hr)
			g_lpDIDevice8[DID_MOUSE]->Acquire(); // �A�N�Z�X���̍Ď擾
		//printf_s("*** Error - �}�E�X��Ԏ擾(DIGetMouseState)\n");
		return false;
	}
	return true;
}

bool DIGetGamePadState(const DIDEV did, DIJOYSTATE& diGamePadState)
{
	ZeroMemory(&diGamePadState, sizeof(diGamePadState));
	diGamePadState.lX = diGamePadState.lY = diGamePadState.lZ = DIAXIS_RANGE_CENTER;
	diGamePadState.lRx = diGamePadState.lRy = diGamePadState.lRz = DIAXIS_RANGE_CENTER;
#ifdef _DEBUG
	if (did < DID_GAMEPAD1 || DID_MAX <= did) {
		//printf_s("*** Error - �f�o�C�X�w��G���[(DIGetGamePadState)\n");
		return false;
	}
#endif
	if (NULL == g_lpDIDevice8[did]) {
		//printf_s("*** Error - �Q�[���p�b�h��������(DIGetGamePadState)\n");
		return false;
	}
	g_lpDIDevice8[did]->Poll();
	const HRESULT hr = g_lpDIDevice8[did]->GetDeviceState(sizeof(diGamePadState), &diGamePadState);
	if (DI_OK != hr) {
		if (DIERR_INPUTLOST == hr || DIERR_NOTACQUIRED == hr)
			g_lpDIDevice8[did]->Acquire();
		//printf_s("*** Error - �Q�[���p�b�h��Ԏ擾(DIGetGamePadState)\n");
		return false;
	}
	return true;
}

LONG DISetFFB_Spring(const DIDEV did, AXIS axis, LONG centerOffset, LONG saturation, LONG coefficient, LONG centering) {
	if (did < DID_GAMEPAD1 || DID_MAX <= did) {
		return 0;
	}
	if (NULL == g_lpDIDevice8[did]) {
		//printf_s("*** Error - �Q�[���p�b�h��������(DISetFFB_Spring)\n");
		return 0;
	}

	centerOffset = min(max(centerOffset, -10000), 10000);
	saturation = min(max(saturation, 0), 10000);
	coefficient = min(max(coefficient, 0), 10000);
	centering = min(max(centering, 0), 10000);

	DIJOYSTATE diJoyState;
	if (!DIGetGamePadState(DID_GAMEPAD1, diJoyState)) {
		return 0;
	}
	LONG handle = diJoyState.lX * 10000 / DIAXIS_RANGE_MAX;
	LONG diffHandle = handle - centerOffset;
	LONG centeringCorrection = diffHandle * centering / 10000;

	//�R���X�^���g�t�H�[�X�ŃX�v�����O���Č�
	LONG coef = (LONG)(diffHandle * coefficient / 10000.f);
	//LONG coef = (0 < diffHandle) ? coefficient : -coefficient;
	if (0 < saturation) {
		coef = min(max(coef, -saturation), saturation);
	}
	coef = min(max(coef, -10000),10000);
	DISetFFB_Constant(did, axis, coef);
	return coef;

	// �G�t�F�N�g�����ݒ�
	DICONDITION dicondition;
	ZeroMemory(&dicondition, sizeof(dicondition));
	dicondition.lDeadBand = 0;
	dicondition.dwNegativeSaturation = saturation;
	dicondition.dwPositiveSaturation = saturation;
	dicondition.lNegativeCoefficient = coefficient;
	dicondition.lPositiveCoefficient = coefficient;
	dicondition.lOffset = centerOffset-centeringCorrection;

	// �U���G�t�F�N�g�ݒ�
	DWORD dwAxes[] = { AXIS_Convert(axis) }; // �G�t�F�N�g��
	LONG lDirection[] = { 0 }; // �G�t�F�N�g����
	DIEFFECT diEffect;
	ZeroMemory(&diEffect, sizeof(diEffect));
	diEffect.dwSize = sizeof(diEffect);
	diEffect.dwFlags = DIEFF_CARTESIAN | DIEFF_OBJECTOFFSETS;
	diEffect.dwDuration = INFINITE; // �G�t�F�N�g�p������
	diEffect.dwGain = DI_FFNOMINALMAX;
	diEffect.dwTriggerButton = DIEB_NOTRIGGER;
	diEffect.dwTriggerRepeatInterval = 0;
	diEffect.cAxes = sizeof(dwAxes) / sizeof(dwAxes[0]);
	diEffect.rgdwAxes = dwAxes;
	diEffect.rglDirection = lDirection;
	diEffect.lpEnvelope = NULL; // �G���x���[�v�\����
	diEffect.cbTypeSpecificParams = sizeof(dicondition); // �G�t�F�N�g�����\���̂̃T�C�Y
	diEffect.lpvTypeSpecificParams = &dicondition; // �G�t�F�N�g�����\����
	// �G�t�F�N�g����
	if (!lpDIEffect_spring[(int)axis]) {
		HRESULT hr = g_lpDIDevice8[did]->CreateEffect(GUID_Spring, &diEffect, &lpDIEffect_spring[(int)axis], NULL);
	}

	if (lpDIEffect_spring[(int)axis]) {
		lpDIEffect_spring[(int)axis]->SetParameters(&diEffect, DIEP_TYPESPECIFICPARAMS | DIEP_START);
	}
}

void DISetFFB_Damper(const DIDEV did, AXIS axis, LONG coefficient) {
	if (did < DID_GAMEPAD1 || DID_MAX <= did) {
		return;
	}
	if (NULL == g_lpDIDevice8[did]) {
		//printf_s("*** Error - �Q�[���p�b�h��������(DISetFFB_Damper)\n");
		return;
	}

	coefficient = min(max(coefficient, 0), 10000);

	// �G�t�F�N�g�����ݒ�
	DICONDITION dicondition;
	ZeroMemory(&dicondition, sizeof(dicondition));
	dicondition.lDeadBand = 0;
	dicondition.dwNegativeSaturation = 0;
	dicondition.dwPositiveSaturation = 0;
	dicondition.lNegativeCoefficient = coefficient;
	dicondition.lPositiveCoefficient = coefficient;
	dicondition.lOffset = 0;

	// �U���G�t�F�N�g�ݒ�
	DWORD dwAxes[] = { AXIS_Convert(axis) }; // �G�t�F�N�g��
	LONG lDirection[] = { 0 }; // �G�t�F�N�g����
	DIEFFECT diEffect;
	ZeroMemory(&diEffect, sizeof(diEffect));
	diEffect.dwSize = sizeof(diEffect);
	diEffect.dwFlags = DIEFF_CARTESIAN | DIEFF_OBJECTOFFSETS;
	diEffect.dwDuration = INFINITE; // �G�t�F�N�g�p������
	diEffect.dwGain = DI_FFNOMINALMAX;
	diEffect.dwTriggerButton = DIEB_NOTRIGGER;
	diEffect.dwTriggerRepeatInterval = 0;
	diEffect.cAxes = sizeof(dwAxes) / sizeof(dwAxes[0]);
	diEffect.rgdwAxes = dwAxes;
	diEffect.rglDirection = lDirection;
	diEffect.lpEnvelope = NULL; // �G���x���[�v�\����
	diEffect.cbTypeSpecificParams = sizeof(dicondition); // �G�t�F�N�g�����\���̂̃T�C�Y
	diEffect.lpvTypeSpecificParams = &dicondition; // �G�t�F�N�g�����\����
	// �G�t�F�N�g����
	if (!lpDIEffect_damper[(int)axis]) {
		//HRESULT hr = g_lpDIDevice8[did]->CreateEffect(GUID_Damper, &diEffect, &lpDIEffect_damper, NULL);
		HRESULT hr = g_lpDIDevice8[did]->CreateEffect(GUID_Friction, &diEffect, &lpDIEffect_damper[(int)axis], NULL);
	}

	if (lpDIEffect_damper[(int)axis]) {
		lpDIEffect_damper[(int)axis]->SetParameters(&diEffect, DIEP_TYPESPECIFICPARAMS | DIEP_START);
	}
}

void DISetFFB_Friction(const DIDEV did, AXIS axis, LONG coefficient) {
	if (NULL == g_lpDIDevice8[did]) {
		//printf_s("*** Error - �Q�[���p�b�h��������(DISetFFB_Damper)\n");
		return;
	}

	coefficient = min(max(coefficient, 0), 10000);

	// �G�t�F�N�g�����ݒ�
	DICONDITION dicondition;
	ZeroMemory(&dicondition, sizeof(dicondition));
	dicondition.lDeadBand = 0;
	dicondition.dwNegativeSaturation = 0;
	dicondition.dwPositiveSaturation = 0;
	dicondition.lNegativeCoefficient = coefficient;
	dicondition.lPositiveCoefficient = coefficient;
	dicondition.lOffset = 0;

	// �U���G�t�F�N�g�ݒ�
	DWORD dwAxes[] = { AXIS_Convert(axis) }; // �G�t�F�N�g��
	LONG lDirection[] = { 0 }; // �G�t�F�N�g����
	DIEFFECT diEffect;
	ZeroMemory(&diEffect, sizeof(diEffect));
	diEffect.dwSize = sizeof(diEffect);
	diEffect.dwFlags = DIEFF_CARTESIAN | DIEFF_OBJECTOFFSETS;
	diEffect.dwDuration = INFINITE; // �G�t�F�N�g�p������
	diEffect.dwGain = DI_FFNOMINALMAX;
	diEffect.dwTriggerButton = DIEB_NOTRIGGER;
	diEffect.dwTriggerRepeatInterval = 0;
	diEffect.cAxes = sizeof(dwAxes) / sizeof(dwAxes[0]);
	diEffect.rgdwAxes = dwAxes;
	diEffect.rglDirection = lDirection;
	diEffect.lpEnvelope = NULL; // �G���x���[�v�\����
	diEffect.cbTypeSpecificParams = sizeof(dicondition); // �G�t�F�N�g�����\���̂̃T�C�Y
	diEffect.lpvTypeSpecificParams = &dicondition; // �G�t�F�N�g�����\����
	// �G�t�F�N�g����
	if (!lpDIEffect_friction[(int)axis]) {
		HRESULT hr = g_lpDIDevice8[did]->CreateEffect(GUID_Friction, &diEffect, &lpDIEffect_friction[(int)axis], NULL);
	}

	if (lpDIEffect_friction[(int)axis]) {
		lpDIEffect_friction[(int)axis]->SetParameters(&diEffect, DIEP_TYPESPECIFICPARAMS | DIEP_START);
	}
}

void DISetFFB_Constant(const DIDEV did, AXIS axis, LONG coefficient) {
	if (did < DID_GAMEPAD1 || DID_MAX <= did) {
		return;
	}
	if (NULL == g_lpDIDevice8[did]) {
		//printf_s("*** Error - �Q�[���p�b�h��������(DISetFFB_Constant)\n");
		return;
	}

	coefficient = min(max(-coefficient, -10000), 10000);

	// �G�t�F�N�g�����ݒ�
	DICONSTANTFORCE diconstant;
	ZeroMemory(&diconstant, sizeof(diconstant));
	diconstant.lMagnitude = coefficient;

	// �U���G�t�F�N�g
	DWORD dwAxes[] = { AXIS_Convert(axis) }; // �G�t�F�N�g��
	//DWORD dwAxes[] = { DIJOFS_RZ }; // �G�t�F�N�g��
	LONG lDirection[] = { 0 }; // �G�t�F�N�g����
	DIEFFECT diEffect;
	ZeroMemory(&diEffect, sizeof(diEffect));
	diEffect.dwSize = sizeof(diEffect);
	diEffect.dwFlags = DIEFF_CARTESIAN | DIEFF_OBJECTOFFSETS;
	diEffect.dwDuration = INFINITE; // �G�t�F�N�g�p������
	diEffect.dwGain = DI_FFNOMINALMAX;
	diEffect.dwTriggerButton = DIEB_NOTRIGGER;
	diEffect.dwTriggerRepeatInterval = 0;
	diEffect.cAxes = sizeof(dwAxes) / sizeof(dwAxes[0]);
	diEffect.rgdwAxes = dwAxes;
	diEffect.rglDirection = lDirection;
	diEffect.lpEnvelope = NULL; // �G���x���[�v�\����
	diEffect.cbTypeSpecificParams = sizeof(diconstant); // �G�t�F�N�g�����\���̂̃T�C�Y
	diEffect.lpvTypeSpecificParams = &diconstant; // �G�t�F�N�g�����\����
	// �G�t�F�N�g����
	if (!lpDIEffect_constant[(int)axis]) {
		HRESULT hr = g_lpDIDevice8[did]->CreateEffect(GUID_ConstantForce, &diEffect, &lpDIEffect_constant[(int)axis], NULL);
	}

	if (lpDIEffect_constant[(int)axis]) {
		lpDIEffect_constant[(int)axis]->SetParameters(&diEffect, DIEP_TYPESPECIFICPARAMS | DIEP_START);
	}
}

void DISetFFB_Inertia(const DIDEV did, AXIS axis, LONG coefficient) {
	if (did < DID_GAMEPAD1 || DID_MAX <= did) {
		return;
	}
	if (NULL == g_lpDIDevice8[did]) {
		//printf_s("*** Error - �Q�[���p�b�h��������(DISetFFB_Inertia)\n");
		return;
	}

	coefficient = min(max(coefficient, -10000), 10000);

	// �G�t�F�N�g�����ݒ�
	DICONDITION dicondition;
	ZeroMemory(&dicondition, sizeof(dicondition));
	dicondition.lDeadBand = 0;
	dicondition.dwNegativeSaturation = 0;
	dicondition.dwPositiveSaturation = 0;
	dicondition.lNegativeCoefficient = coefficient;
	dicondition.lPositiveCoefficient = coefficient;
	dicondition.lOffset = 0;

	// �U���G�t�F�N�g�ݒ�
	DWORD dwAxes[] = { AXIS_Convert(axis) }; // �G�t�F�N�g��
	LONG lDirection[] = { 0 }; // �G�t�F�N�g����
	DIEFFECT diEffect;
	ZeroMemory(&diEffect, sizeof(diEffect));
	diEffect.dwSize = sizeof(diEffect);
	diEffect.dwFlags = DIEFF_CARTESIAN | DIEFF_OBJECTOFFSETS;
	diEffect.dwDuration = INFINITE; // �G�t�F�N�g�p������
	diEffect.dwGain = DI_FFNOMINALMAX;
	diEffect.dwTriggerButton = DIEB_NOTRIGGER;
	diEffect.dwTriggerRepeatInterval = 0;
	diEffect.cAxes = sizeof(dwAxes) / sizeof(dwAxes[0]);
	diEffect.rgdwAxes = dwAxes;
	diEffect.rglDirection = lDirection;
	diEffect.lpEnvelope = NULL; // �G���x���[�v�\����
	diEffect.cbTypeSpecificParams = sizeof(dicondition); // �G�t�F�N�g�����\���̂̃T�C�Y
	diEffect.lpvTypeSpecificParams = &dicondition; // �G�t�F�N�g�����\����
	// �G�t�F�N�g����
	if (!lpDIEffect_inertia[(int)axis]) {
		HRESULT hr = g_lpDIDevice8[did]->CreateEffect(GUID_Inertia, &diEffect, &lpDIEffect_inertia[(int)axis], NULL);
	}

	if (lpDIEffect_inertia[(int)axis]) {
		lpDIEffect_inertia[(int)axis]->SetParameters(&diEffect, DIEP_TYPESPECIFICPARAMS | DIEP_START);
	}
}

DWORD AXIS_Convert(AXIS axis) {
	switch (axis) {
	case AXIS::X:
		return DIJOFS_X;
	case AXIS::Y:
		return DIJOFS_Y;
	case AXIS::Z:
		return DIJOFS_Z;
	case AXIS::RX:
		return DIJOFS_RX;
	case AXIS::RY:
		return DIJOFS_RY;
	case AXIS::RZ:
		return DIJOFS_RZ;
	}
	return DIJOFS_X;
}

System::String^ DIGetGamePadName(const DIDEV did) {
	if (did < DID_GAMEPAD1 || DID_MAX <= did) {
		return "No Device";
	}
	DIDEVICEINSTANCE lpDeviceInst;
	lpDeviceInst.dwSize = sizeof(DIDEVICEINSTANCE);
	if (g_lpDIDevice8[did]) {
		g_lpDIDevice8[did]->GetDeviceInfo(&lpDeviceInst);
		if (&lpDeviceInst) {
			System::String^ s = gcnew System::String("");
			int i = 0;
			while (lpDeviceInst.tszProductName[i]) {
				s += lpDeviceInst.tszProductName[i];
				i++;
			}
			return s;
		}
	}
	return "No Device";
}
std::string DIGetGamePadName_std(const DIDEV did) {
	if (did < DID_GAMEPAD1 || DID_MAX <= did) {
		return "No Device";
	}
	DIDEVICEINSTANCE lpDeviceInst;
	lpDeviceInst.dwSize = sizeof(DIDEVICEINSTANCE);
	if (g_lpDIDevice8[did]) {
		g_lpDIDevice8[did]->GetDeviceInfo(&lpDeviceInst);
		if (&lpDeviceInst) {
			std::string s = "";
			int i = 0;
			while (lpDeviceInst.tszProductName[i]) {
				s += (char)lpDeviceInst.tszProductName[i];
				i++;
			}
			return s;
		}
	}
	return "No Device";
}

bool DIExistGamePad(const DIDEV did) {
	if (did < DID_GAMEPAD1 || DID_MAX <= did) {
		return false;
	}
	return g_lpDIDevice8[did];
}

void All_DIERR(HRESULT hr) {
	int t = 0;
	switch (hr)
	{
	case DIERR_ACQUIRED: t = 0; break;
	case DIERR_ALREADYINITIALIZED: t = 0; break;
	case DIERR_BADDRIVERVER: t = 0; break;
	case DIERR_BETADIRECTINPUTVERSION: t = 0; break;
	case DIERR_DEVICEFULL: t = 0; break;
	case DIERR_DEVICENOTREG: t = 0; break;
	case DIERR_EFFECTPLAYING: t = 0; break;
	case DIERR_GENERIC: t = 0; break;
	case DIERR_HANDLEEXISTS: t = 0; break;
	case DIERR_HASEFFECTS: t = 0; break;
	case DIERR_INCOMPLETEEFFECT: t = 0; break;
	case DIERR_INPUTLOST: t = 0; break;
	case DIERR_INSUFFICIENTPRIVS: t = 0; break;
	case DIERR_INVALIDPARAM: t = 0; break;
	case DIERR_MAPFILEFAIL: t = 0; break;
	case DIERR_MOREDATA: t = 0; break;
	case DIERR_NOAGGREGATION: t = 0; break;
	case DIERR_NOINTERFACE: t = 0; break;
	case DIERR_NOTACQUIRED: t = 0; break;
	case DIERR_NOTBUFFERED: t = 0; break;
	case DIERR_NOTDOWNLOADED: t = 0; break;
	case DIERR_NOTEXCLUSIVEACQUIRED: t = 0; break;
	case DIERR_NOTFOUND: t = 0; break;
	case DIERR_NOTINITIALIZED: t = 0; break;
		//case DIERR_OBJECTNOTFOUND: t = 0; break;
	case DIERR_OLDDIRECTINPUTVERSION: t = 0; break;
		//case DIERR_OTHERAPPHASPRIO: t = 0; break;
	case DIERR_OUTOFMEMORY: t = 0; break;
		//case DIERR_READONLY: t = 0; break;
	case DIERR_REPORTFULL: t = 0; break;
	case DIERR_UNPLUGGED: t = 0; break;
	case DIERR_UNSUPPORTED: t = 0; break;
	default:
		break;
	}
}