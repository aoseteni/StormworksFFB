#include "ProfileSave.h"



std::vector<std::string> GetProfilesName(const std::string& directory, const std::string& extension) {
	std::vector<std::string> filenames;

	//�t�H���_�����݂��邩�m�F
	std::filesystem::path path(directory);
	if (!std::filesystem::exists(path) || !std::filesystem::is_directory(path)) {
		return filenames;
	}

	for (const auto& entry : std::filesystem::directory_iterator(directory)) {
		if (entry.is_regular_file()) {
			std::string filename = entry.path().filename().string();
			std::string fileExtension = entry.path().extension().string();

			// �g���q�𖳎����ăt�@�C�����݂̂��擾
			if (fileExtension == extension) {
				// �g���q���������t�@�C������z��ɒǉ�
				std::string filenameWithoutExtension = filename.substr(0, filename.length() - fileExtension.length());
				filenames.push_back(filenameWithoutExtension);
			}
		}
	}

	return filenames;
}

bool SaveProfile(Profile saveProfile, std::string name) {
	int saveDataVersion = 1;

	// �t�H���_���쐬
	std::filesystem::create_directory(Profile::FolderName());

	// �t�@�C�����Ƃ��Ďg�p���镶����
	std::string filePath = Profile::FolderName() + "/" + name + Profile::FileExtension();

	// �t�@�C�����J��
	std::ofstream file(filePath);

	// �t�@�C�����������J���������m�F
	if (file.is_open()) {
		// �ϐ��̒l���t�@�C���ɏ�������
		file << Profile::SaveDataVersionText().c_str() << "=" << saveDataVersion << std::endl;
		file << Profile::MinForceText().c_str() << "=" << saveProfile.GetMinForce() << std::endl;
		file << Profile::MaxForceText().c_str() << "=" << saveProfile.GetMaxForce() << std::endl;
		file << Profile::ForceScaleText().c_str() << "=" << saveProfile.GetForceScale() << std::endl;
		file << Profile::InvertFFBText().c_str() << "=" << (saveProfile.GetInvertFFB() ? 1 : 0) << std::endl;
		file << Profile::MovementForceText().c_str() << "=" << saveProfile.GetMovementForce() << std::endl;
		file << Profile::RotateForceText().c_str() << "=" << saveProfile.GetRotateForce() << std::endl;
		file << Profile::CenterFrictionMaxText().c_str() << "=" << saveProfile.GetCenterFrictionMax() << std::endl;
		file << Profile::CenterFrictionZoneText().c_str() << "=" << saveProfile.GetCenterFrictionZone() << std::endl;
		file << Profile::GripFrictionText().c_str() << "=" << saveProfile.GetGripFriction() << std::endl;
		file << Profile::StaticFrictionText().c_str() << "=" << saveProfile.GetStaticFriction() << std::endl;
		file << Profile::TyreDynamicFrictionCoefficientText().c_str() << "=" << saveProfile.GetTyreDynamicFrictionCoefficient() << std::endl;
		file << Profile::DeadZoneInsideText().c_str() << "=" << saveProfile.GetDeadZoneInside() << std::endl;
		file << Profile::DeadZoneOutsideText().c_str() << "=" << saveProfile.GetDeadZoneOutside() << std::endl;
		file << Profile::SoftLockForceText().c_str() << "=" << saveProfile.GetSoftLockForce() << std::endl;
		file << Profile::MaxTyreAngleText().c_str() << "=" << saveProfile.GetMaxTyreAngle() << std::endl;
		file << Profile::PivotWheelModeText().c_str() << "=" << (saveProfile.GetPivotWheelMode() ? 1 : 0) << std::endl;

		// �t�@�C�������
		file.close();

		return true;
	}
	else {
		return false;
	}

	return false;
}

Profile LoadProfile(std::string name) {
	Profile profile = Profile();

	// �t�@�C�����Ƃ��Ďg�p���镶����
	std::string filePath = Profile::FolderName() + "/" + name + Profile::FileExtension();

	// �t�@�C�����J��
	std::ifstream file(filePath);

	// �t�@�C�����������J���������m�F
	if (file.is_open()) {
		// �ϐ��̒l���t�@�C������ǂݍ���
		std::string line;
		while (std::getline(file, line)) {
			// �ϐ����ƒl�𒊏o
			std::size_t pos = line.find("=");
			std::string varName = line.substr(0, pos);
			std::string varValue = line.substr(pos + 1);

			// �ϐ����ɉ����Ēl��K�؂ȕϐ��ɑ��
			if (varName == Profile::SaveDataVersionText()) {
				switch (ToLONG(varValue))
				{
				case 1:
					profile = LoadProfile_v1(filePath);
					break;
				}
				break;
			}
			
		}

		// �t�@�C�������
		file.close();
	}
	else {
		printf_s("*** Error - �v���t�@�C�����[�h���s(");
		printf_s(filePath.c_str());
		printf_s(")\n");
	}

	return profile;
}

Profile LoadProfile_v1(std::string filePath) {
	Profile profile = Profile();

	// �t�@�C�����J��
	std::ifstream file(filePath);

	// �t�@�C�����������J���������m�F
	if (file.is_open()) {
		// �ϐ��̒l���t�@�C������ǂݍ���
		std::string line;
		while (std::getline(file, line)) {
			// �ϐ����ƒl�𒊏o
			std::size_t pos = line.find("=");
			std::string varName = line.substr(0, pos);
			std::string varValue = line.substr(pos + 1);

			// �ϐ����ɉ����Ēl��K�؂ȕϐ��ɑ��
			if (varName == Profile::MinForceText()) {
				profile.SetMinForce(ToLONG(varValue));
			}
			else if (varName == Profile::MaxForceText()) {
				profile.SetMaxForce(ToLONG(varValue));
			}
			else if (varName == Profile::ForceScaleText()) {
				profile.SetForceScale(ToLONG(varValue));
			}
			else if (varName == Profile::InvertFFBText()) {
				profile.SetInvertFFB(ToLONG(varValue) != 0);
			}
			else if (varName == Profile::MovementForceText()) {
				profile.SetMovementForce(ToLONG(varValue));
			}
			else if (varName == Profile::RotateForceText()) {
				profile.SetRotateForce(ToLONG(varValue));
			}
			else if (varName == Profile::CenterFrictionMaxText()) {
				profile.SetCenterFrictionMax(ToLONG(varValue));
			}
			else if (varName == Profile::CenterFrictionZoneText()) {
				profile.SetCenterFrictionZone(ToLONG(varValue));
			}
			else if (varName == Profile::GripFrictionText()) {
				profile.SetGripFriction(ToLONG(varValue));
			}
			else if (varName == Profile::StaticFrictionText()) {
				profile.SetStaticFriction(ToLONG(varValue));
			}
			else if (varName == Profile::TyreDynamicFrictionCoefficientText()) {
				profile.SetTyreDynamicFrictionCoefficient(ToLONG(varValue));
			}
			else if (varName == Profile::DeadZoneInsideText()) {
				profile.SetDeadZoneInside(ToLONG(varValue));
			}
			else if (varName == Profile::DeadZoneOutsideText()) {
				profile.SetDeadZoneOutside(ToLONG(varValue));
			}
			else if (varName == Profile::SoftLockForceText()) {
				profile.SetSoftLockForce(ToLONG(varValue));
			}
			else if (varName == Profile::MaxTyreAngleText()) {
				profile.SetMaxTyreAngle(ToLONG(varValue));
			}
			else if (varName == Profile::PivotWheelModeText()) {
				profile.SetPivotWheelMode(ToLONG(varValue) != 0);
			}
		}

		// �t�@�C�������
		file.close();
	}
	else {
		printf_s("*** Error - �v���t�@�C�����[�h���s(");
		printf_s(filePath.c_str());
		printf_s(")\n");
	}

	return profile;
}

bool DeleteProfile(std::string name) {
	// �t�@�C�����Ƃ��Ďg�p���镶����
	std::string filePath_ = Profile::FolderName() + "/" + name + Profile::FileExtension();

	try {
		std::filesystem::path filePath(filePath_);

		// �t�@�C�������݂��邩�m�F
		if (std::filesystem::exists(filePath) && std::filesystem::is_regular_file(filePath)) {
			// �t�@�C�����폜
			std::filesystem::remove(filePath);
			return true;
		}
		else {
			printf_s("*** Error - �v���t�@�C���폜���s(�w�肳�ꂽ�t�@�C��(");
			printf_s(name.c_str());
			printf_s(")�����݂��܂���)");
			return false;
		}
	}
	catch (const std::filesystem::filesystem_error&) {
		printf_s("*** Error - �v���t�@�C���폜���s(�t�@�C���̍폜���ɃG���[���������܂���(");
		printf_s(name.c_str());
		printf_s(")");
		return false;
	}
}

bool SaveFirstProfileName(std::string name) {
	// �t�H���_���쐬
	std::filesystem::create_directory("Init");

	// �t�@�C�����Ƃ��Ďg�p���镶����
	std::string filePath = "Init/profile.init";

	// �t�@�C�����J��
	std::ofstream file(filePath);

	// �t�@�C�����������J���������m�F
	if (file.is_open()) {
		// �ϐ��̒l���t�@�C���ɏ�������
		file << name << std::endl;

		// �t�@�C�������
		file.close();

		return true;
	}
	else {
		return false;
	}

	return false;
}

std::string LoadFirstProfileName() {
	// �t�@�C�����Ƃ��Ďg�p���镶����
	std::string filePath = "Init/profile.init";

	// �t�@�C�����J��
	std::ifstream file(filePath);

	// �t�@�C�����������J���������m�F
	if (file.is_open()) {
		// �ϐ��̒l���t�@�C������ǂݍ���
		std::string line;
		std::getline(file, line);//1�s�ڂ̂ݔ���

		// �t�@�C�������
		file.close();

		return line;
	}

	return "";
}

bool FindProfile(std::string name) {
	// �t�@�C�����Ƃ��Ďg�p���镶����
	std::string filePath_ = Profile::FolderName() + "/" + name + Profile::FileExtension();

	try {
		std::filesystem::path filePath(filePath_);

		// �t�@�C�������݂��邩�m�F
		return (std::filesystem::exists(filePath) && std::filesystem::is_regular_file(filePath));
	}
	catch (const std::filesystem::filesystem_error&) {
		printf_s("*** Error - �v���t�@�C���m�F���s(�t�@�C���̌������ɃG���[���������܂���(");
		printf_s(name.c_str());
		printf_s(")");
		return false;
	}
}



LONG ToLONG(const std::string &str) {
	try {
		return std::stoi(str);
	}
	catch (...) {
		return 0;
	}
}