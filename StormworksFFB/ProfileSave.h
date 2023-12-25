#pragma once
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>


public struct Profile {
private:
	LONG MinForce;
	LONG MaxForce;
	LONG ForceScale;
	bool InvertFFB;
	LONG MovementForce;
	LONG RotateForce;
	LONG CenterFrictionMax;
	LONG CenterFrictionZone;
	LONG GripFriction;
	LONG StaticFriction;
	LONG TyreDynamicFrictionCoefficient;
	LONG DeadZoneInside;
	LONG DeadZoneOutside;
	LONG SoftLockForce;
	LONG MaxTyreAngle;
	bool PivotWheelMode;

public:
	Profile() {
		//デフォルト値設定
		MinForce = 0;//0-10000
		MaxForce = 10000;//0-10000
		ForceScale = 100;//0-300
		InvertFFB = false;//false:反転なし, true:反転あり
		MovementForce = 5000;//0-10000
		RotateForce = 5000;//0-10000
		CenterFrictionMax = 0;//0-10000
		CenterFrictionZone = 0;//0-10000
		GripFriction = 2000;//0-10000
		StaticFriction = 2000;//0-10000
		TyreDynamicFrictionCoefficient = 60;//0-100
		DeadZoneInside = 0;//0-10000(0-100.00)
		DeadZoneOutside = 0;//0-10000(0-100.00)
		SoftLockForce = 10000;//0-10000
		MaxTyreAngle = 10000;//0-10000
		PivotWheelMode = false;//false:Default, true:Pivot
	}

	LONG GetMinForce() { return MinForce; }
	void SetMinForce(LONG v) { MinForce = min(max(v, 0), 10000); }

	LONG GetMaxForce() { return MaxForce; }
	void SetMaxForce(LONG v) { MaxForce = min(max(v, 0), 10000); }

	LONG GetForceScale() { return ForceScale; }
	void SetForceScale(LONG v) { ForceScale = min(max(v, 0), 300); }

	bool GetInvertFFB() { return InvertFFB; }
	void SetInvertFFB(bool v) { InvertFFB = v; }

	LONG GetMovementForce() { return MovementForce; }
	void SetMovementForce(LONG v) { MovementForce = min(max(v, 0), 10000); }

	LONG GetRotateForce() { return RotateForce; }
	void SetRotateForce(LONG v) { RotateForce = min(max(v, 0), 10000); }

	LONG GetCenterFrictionMax() { return CenterFrictionMax; }
	void SetCenterFrictionMax(LONG v) { CenterFrictionMax = min(max(v, 0), 10000); }

	LONG GetCenterFrictionZone() { return CenterFrictionZone; }
	void SetCenterFrictionZone(LONG v) { CenterFrictionZone = min(max(v, 0), 10000); }

	LONG GetGripFriction() { return GripFriction; }
	void SetGripFriction(LONG v) { GripFriction = min(max(v, 0), 10000); }

	LONG GetStaticFriction() { return StaticFriction; }
	void SetStaticFriction(LONG v) { StaticFriction = min(max(v, 0), 10000); }

	LONG GetTyreDynamicFrictionCoefficient() { return TyreDynamicFrictionCoefficient; }
	void SetTyreDynamicFrictionCoefficient(LONG v) { TyreDynamicFrictionCoefficient = min(max(v, 0), 100); }

	LONG GetDeadZoneInside() { return DeadZoneInside; }
	void SetDeadZoneInside(LONG v) { DeadZoneInside = min(max(v, 0), 10000); }

	LONG GetDeadZoneOutside() { return DeadZoneOutside; }
	void SetDeadZoneOutside(LONG v) { DeadZoneOutside = min(max(v, 0), 10000); }

	LONG GetSoftLockForce() { return SoftLockForce; }
	void SetSoftLockForce(LONG v) { SoftLockForce = min(max(v, 0), 10000); }

	LONG GetMaxTyreAngle() { return MaxTyreAngle; }
	void SetMaxTyreAngle(LONG v) { MaxTyreAngle = min(max(v, 0), 10000); }

	bool GetPivotWheelMode() { return PivotWheelMode; }
	void SetPivotWheelMode(bool v) { PivotWheelMode = v; }

	static bool IsSameProfile(Profile a, Profile b) {
		return
			a.GetMinForce() == b.GetMinForce() &&
			a.GetMaxForce() == b.GetMaxForce() &&
			a.GetForceScale() == b.GetForceScale() &&
			a.GetInvertFFB() == b.GetInvertFFB() &&
			a.GetMovementForce() == b.GetMovementForce() &&
			a.GetRotateForce() == b.GetRotateForce() &&
			a.GetCenterFrictionMax() == b.GetCenterFrictionMax() &&
			a.GetCenterFrictionZone() == b.GetCenterFrictionZone() &&
			a.GetGripFriction() == b.GetGripFriction() &&
			a.GetStaticFriction() == b.GetStaticFriction() &&
			a.GetTyreDynamicFrictionCoefficient() == b.GetTyreDynamicFrictionCoefficient() && 
			a.GetDeadZoneInside() == b.GetDeadZoneInside() &&
			a.GetDeadZoneOutside() == b.GetDeadZoneOutside() &&
			a.GetSoftLockForce() == b.GetSoftLockForce() && 
			a.GetMaxTyreAngle() == b.GetMaxTyreAngle() &&
			a.GetPivotWheelMode() == b.GetPivotWheelMode();
	}

	bool IsDefaultParam() {
		Profile defaultParam = Profile();
		return IsSameProfile(*this, defaultParam);
	}

	static std::string SaveDataVersionText() { return "SaveDataVersion"; }
	static std::string MinForceText() { return "MinForce"; }
	static std::string MaxForceText() { return "MaxForce"; }
	static std::string ForceScaleText() { return "ForceScale"; }
	static std::string InvertFFBText() { return "InvertFFB"; }
	static std::string MovementForceText() { return "MovementForce"; }
	static std::string RotateForceText() { return "RotateForce"; }
	static std::string CenterFrictionMaxText() { return "CenterFrictionMax"; }
	static std::string CenterFrictionZoneText() { return "CenterFrictionZone"; }
	static std::string GripFrictionText() { return "GripFriction"; }
	static std::string StaticFrictionText() { return "StaticFriction"; }
	static std::string TyreDynamicFrictionCoefficientText() { return "TyreDynamicFrictionCoefficient"; }
	static std::string DeadZoneInsideText()  { return "DeadZoneInside"; }
	static std::string DeadZoneOutsideText() { return "DeadZoneOutside"; }
	static std::string SoftLockForceText()   { return "SoftLockForce"; }
	static std::string MaxTyreAngleText()    { return "MaxTyreAngle"; }
	static std::string PivotWheelModeText() { return "PivotWheelMode"; }
	static std::string FolderName() { return "Profile"; }
	static std::string FileExtension() { return  ".profile"; }
};



std::vector<std::string> GetProfilesName(const std::string& directory, const std::string& extension);
bool SaveProfile(Profile saveProfile, std::string name);
Profile LoadProfile(std::string name);
Profile LoadProfile_v1(std::string filePath);
bool DeleteProfile(std::string name);
bool SaveFirstProfileName(std::string name);//初めに読み込むプロファイル名を保存する
std::string LoadFirstProfileName();//初めに読み込むプロファイル名を読み込む
bool FindProfile(std::string name);

LONG ToLONG(const std::string &str);