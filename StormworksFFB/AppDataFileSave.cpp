#include "AppDataFileSave.h"

bool SaveAppDataFile(AppData appData) {
	// フォルダを作成
	std::filesystem::create_directory(AppData::FolderName());

	//init.swffbの保存//
	{
		// ファイル名として使用する文字列
		std::string filePath = AppData::FolderName() + "/" + AppData::FileName_InitFile() + AppData::FileExtension_InitFile();

		// ファイルを開く
		std::ofstream file(filePath);

		// ファイルが正しく開けたかを確認
		if (file.is_open()) {
			// 変数の値をファイルに書き込む
			file << AppData::ProfileNameText().c_str() << "=" << appData.GetInitProfileName() << std::endl;
			file << AppData::DeviceNameText().c_str() << "=" << appData.GetInitDeviceName() << std::endl;

			// ファイルを閉じる
			file.close();
		}
		else {
			return false;
		}
	}
	//init.swffbの保存//

	//Axis情報の保存//
	{
		// フォルダを作成
		std::filesystem::create_directory(AppData::FolderName_Axis());

		std::unordered_map<std::string, int> axis_map = appData.GetAxisMap();
		for (auto map : axis_map) {
			// ファイル名として使用する文字列
			std::string filePath = AppData::FolderName_Axis() + "/" + map.first + AppData::FileExtension_AxisFile();

			if (map.second == 0) { //X軸ならファイル削除&保存しない
				// ファイルが存在するか確認
				if (std::filesystem::exists(filePath) && std::filesystem::is_regular_file(filePath)) {
					// ファイルを削除
					std::filesystem::remove(filePath);
				}
				continue; 
			}

			// ファイルを開く
			std::ofstream file(filePath);

			// ファイルが正しく開けたかを確認
			if (file.is_open()) {
				// 変数の値をファイルに書き込む
				file << AppData::AxisText() << "=" << map.second << std::endl;

				// ファイルを閉じる
				file.close();
			}
		}
	}
	//Axis情報の保存//

	return true;
}

AppData LoadAppDataFile() {
	AppData appData = AppData();

	//init.swffbの読み込み//
	{
		// ファイル名として使用する文字列
		std::string filePath = AppData::FolderName() + "/" + AppData::FileName_InitFile() + AppData::FileExtension_InitFile();

		// ファイルを開く
		std::ifstream file(filePath);

		// ファイルが正しく開けたかを確認
		if (file.is_open()) {
			// 変数の値をファイルから読み込む
			std::string line;
			while (std::getline(file, line)) {
				// 変数名と値を抽出
				std::size_t pos = line.find("=");
				std::string varName = line.substr(0, pos);
				std::string varValue = line.substr(pos + 1);

				// 変数名に応じて値を適切な変数に代入
				if (varName == AppData::ProfileNameText()) {
					appData.SetInitProfileName(varValue);
				}
				else if (varName == AppData::DeviceNameText()) {
					appData.SetInitDeviceName(varValue);
				}
			}

			// ファイルを閉じる
			file.close();
		}
		else {
			printf_s("*** Error - 初期化ファイルロード失敗(");
			printf_s(filePath.c_str());
			printf_s(")\n");
		}
	}
	//init.swffbの読み込み//

	//Axis情報の読み込み//
	{
		std::vector<std::string> axisFilesName = GetAxisFilesName(AppData::FolderName_Axis(), AppData::FileExtension_AxisFile());

		for (auto fileName : axisFilesName) {
			// ファイル名として使用する文字列
			std::string filePath = AppData::FolderName_Axis() + "/" + fileName + AppData::FileExtension_AxisFile();

			// ファイルを開く
			std::ifstream file(filePath);

			// ファイルが正しく開けたかを確認
			if (file.is_open()) {
				// 変数の値をファイルから読み込む
				int axisIndex = 0;

				std::string line;
				while (std::getline(file, line)) {
					// 変数名と値を抽出
					std::size_t pos = line.find("=");
					std::string varName = line.substr(0, pos);
					std::string varValue = line.substr(pos + 1);

					// 変数名に応じて値を適切な変数に代入
					if (varName == AppData::AxisText()) {
						axisIndex = ToInt(varValue);
					}
				}

				appData.SetAxis(fileName, axisIndex);

				// ファイルを閉じる
				file.close();
			}
		}
	}
	//Axis情報の読み込み//

	return appData;
}

std::vector<std::string> GetAxisFilesName(const std::string& directory, const std::string& extension) {
	std::vector<std::string> filenames;

	//フォルダが存在するか確認
	std::filesystem::path path(directory);
	if (!std::filesystem::exists(path) || !std::filesystem::is_directory(path)) {
		return filenames;
	}

	for (const auto& entry : std::filesystem::directory_iterator(directory)) {
		if (entry.is_regular_file()) {
			std::string filename = entry.path().filename().string();
			std::string fileExtension = entry.path().extension().string();

			// 拡張子を無視してファイル名のみを取得
			if (fileExtension == extension) {
				// 拡張子を除いたファイル名を配列に追加
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