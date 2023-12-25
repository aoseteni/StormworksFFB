#pragma once

#include <Windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <filesystem>
#include <unordered_map>


public struct AppData
{
private:
	std::string initProfileName = "";
	std::string initDeviceName = "";
	std::unordered_map<std::string, int> axis_map;

public:
	std::string GetInitProfileName() { return initProfileName; }
	void SetInitProfileName(std::string name) { initProfileName = name; }

	std::string GetInitDeviceName() { return initDeviceName; }
	void SetInitDeviceName(std::string name) { initDeviceName = name; }

	int GetAxis(std::string deviceName) { 
		if (axis_map.count(deviceName)) {//�f�[�^�̑��݊m�F(���݂��Ȃ��ꍇ�ɐV�K�쐬�����̂�h��)
			return axis_map[deviceName];
		}
		return 0;//�f�[�^���������lX��Ԃ�
	}
	std::unordered_map<std::string, int> GetAxisMap() { return axis_map; }
	void SetAxis(std::string deviceName, int v) { axis_map[deviceName] = min(max(v, 0), 5); }

	static std::string ProfileNameText() { return "ProfileName"; }
	static std::string DeviceNameText() { return "DeviceName"; }
	static std::string AxisText() { return "Axis"; }
	static std::string FolderName() { return "AppData"; }
	static std::string FolderName_Axis() { return "AppData/Axis"; }
	static std::string FileName_InitFile() { return "init"; }
	static std::string FileName_AxisFile() { return "axis"; }
	static std::string FileExtension_InitFile() { return  ".swffb"; }
	static std::string FileExtension_AxisFile() { return  ".axis"; }
};

bool SaveAppDataFile(AppData appData);//�N�����ɓǂݍ��ރt�@�C����ۑ�����
AppData LoadAppDataFile();
std::vector<std::string> GetAxisFilesName(const std::string& directory, const std::string& extension);

int ToInt(const std::string &str);