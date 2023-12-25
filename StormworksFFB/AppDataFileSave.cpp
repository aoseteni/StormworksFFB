#include "AppDataFileSave.h"

bool SaveAppDataFile(AppData appData) {
	// �t�H���_���쐬
	std::filesystem::create_directory(AppData::FolderName());

	//init.swffb�̕ۑ�//
	{
		// �t�@�C�����Ƃ��Ďg�p���镶����
		std::string filePath = AppData::FolderName() + "/" + AppData::FileName_InitFile() + AppData::FileExtension_InitFile();

		// �t�@�C�����J��
		std::ofstream file(filePath);

		// �t�@�C�����������J���������m�F
		if (file.is_open()) {
			// �ϐ��̒l���t�@�C���ɏ�������
			file << AppData::ProfileNameText().c_str() << "=" << appData.GetInitProfileName() << std::endl;
			file << AppData::DeviceNameText().c_str() << "=" << appData.GetInitDeviceName() << std::endl;

			// �t�@�C�������
			file.close();
		}
		else {
			return false;
		}
	}
	//init.swffb�̕ۑ�//

	//Axis���̕ۑ�//
	{
		// �t�H���_���쐬
		std::filesystem::create_directory(AppData::FolderName_Axis());

		std::unordered_map<std::string, int> axis_map = appData.GetAxisMap();
		for (auto map : axis_map) {
			// �t�@�C�����Ƃ��Ďg�p���镶����
			std::string filePath = AppData::FolderName_Axis() + "/" + map.first + AppData::FileExtension_AxisFile();

			if (map.second == 0) { //X���Ȃ�t�@�C���폜&�ۑ����Ȃ�
				// �t�@�C�������݂��邩�m�F
				if (std::filesystem::exists(filePath) && std::filesystem::is_regular_file(filePath)) {
					// �t�@�C�����폜
					std::filesystem::remove(filePath);
				}
				continue; 
			}

			// �t�@�C�����J��
			std::ofstream file(filePath);

			// �t�@�C�����������J���������m�F
			if (file.is_open()) {
				// �ϐ��̒l���t�@�C���ɏ�������
				file << AppData::AxisText() << "=" << map.second << std::endl;

				// �t�@�C�������
				file.close();
			}
		}
	}
	//Axis���̕ۑ�//

	return true;
}

AppData LoadAppDataFile() {
	AppData appData = AppData();

	//init.swffb�̓ǂݍ���//
	{
		// �t�@�C�����Ƃ��Ďg�p���镶����
		std::string filePath = AppData::FolderName() + "/" + AppData::FileName_InitFile() + AppData::FileExtension_InitFile();

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
				if (varName == AppData::ProfileNameText()) {
					appData.SetInitProfileName(varValue);
				}
				else if (varName == AppData::DeviceNameText()) {
					appData.SetInitDeviceName(varValue);
				}
			}

			// �t�@�C�������
			file.close();
		}
		else {
			printf_s("*** Error - �������t�@�C�����[�h���s(");
			printf_s(filePath.c_str());
			printf_s(")\n");
		}
	}
	//init.swffb�̓ǂݍ���//

	//Axis���̓ǂݍ���//
	{
		std::vector<std::string> axisFilesName = GetAxisFilesName(AppData::FolderName_Axis(), AppData::FileExtension_AxisFile());

		for (auto fileName : axisFilesName) {
			// �t�@�C�����Ƃ��Ďg�p���镶����
			std::string filePath = AppData::FolderName_Axis() + "/" + fileName + AppData::FileExtension_AxisFile();

			// �t�@�C�����J��
			std::ifstream file(filePath);

			// �t�@�C�����������J���������m�F
			if (file.is_open()) {
				// �ϐ��̒l���t�@�C������ǂݍ���
				int axisIndex = 0;

				std::string line;
				while (std::getline(file, line)) {
					// �ϐ����ƒl�𒊏o
					std::size_t pos = line.find("=");
					std::string varName = line.substr(0, pos);
					std::string varValue = line.substr(pos + 1);

					// �ϐ����ɉ����Ēl��K�؂ȕϐ��ɑ��
					if (varName == AppData::AxisText()) {
						axisIndex = ToInt(varValue);
					}
				}

				appData.SetAxis(fileName, axisIndex);

				// �t�@�C�������
				file.close();
			}
		}
	}
	//Axis���̓ǂݍ���//

	return appData;
}

std::vector<std::string> GetAxisFilesName(const std::string& directory, const std::string& extension) {
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

int ToInt(const std::string &str) {
	try {
		return std::stoi(str);
	}
	catch (...) {
		return 0;
	}
}