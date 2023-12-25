#include "ProfileSave.h"



std::vector<std::string> GetProfilesName(const std::string& directory, const std::string& extension) {
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

bool SaveProfile(Profile saveProfile, std::string name) {
	int saveDataVersion = 1;

	// フォルダを作成
	std::filesystem::create_directory(Profile::FolderName());

	// ファイル名として使用する文字列
	std::string filePath = Profile::FolderName() + "/" + name + Profile::FileExtension();

	// ファイルを開く
	std::ofstream file(filePath);

	// ファイルが正しく開けたかを確認
	if (file.is_open()) {
		// 変数の値をファイルに書き込む
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

		// ファイルを閉じる
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

	// ファイル名として使用する文字列
	std::string filePath = Profile::FolderName() + "/" + name + Profile::FileExtension();

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

		// ファイルを閉じる
		file.close();
	}
	else {
		printf_s("*** Error - プロファイルロード失敗(");
		printf_s(filePath.c_str());
		printf_s(")\n");
	}

	return profile;
}

Profile LoadProfile_v1(std::string filePath) {
	Profile profile = Profile();

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

		// ファイルを閉じる
		file.close();
	}
	else {
		printf_s("*** Error - プロファイルロード失敗(");
		printf_s(filePath.c_str());
		printf_s(")\n");
	}

	return profile;
}

bool DeleteProfile(std::string name) {
	// ファイル名として使用する文字列
	std::string filePath_ = Profile::FolderName() + "/" + name + Profile::FileExtension();

	try {
		std::filesystem::path filePath(filePath_);

		// ファイルが存在するか確認
		if (std::filesystem::exists(filePath) && std::filesystem::is_regular_file(filePath)) {
			// ファイルを削除
			std::filesystem::remove(filePath);
			return true;
		}
		else {
			printf_s("*** Error - プロファイル削除失敗(指定されたファイル(");
			printf_s(name.c_str());
			printf_s(")が存在しません)");
			return false;
		}
	}
	catch (const std::filesystem::filesystem_error&) {
		printf_s("*** Error - プロファイル削除失敗(ファイルの削除中にエラーが発生しました(");
		printf_s(name.c_str());
		printf_s(")");
		return false;
	}
}

bool SaveFirstProfileName(std::string name) {
	// フォルダを作成
	std::filesystem::create_directory("Init");

	// ファイル名として使用する文字列
	std::string filePath = "Init/profile.init";

	// ファイルを開く
	std::ofstream file(filePath);

	// ファイルが正しく開けたかを確認
	if (file.is_open()) {
		// 変数の値をファイルに書き込む
		file << name << std::endl;

		// ファイルを閉じる
		file.close();

		return true;
	}
	else {
		return false;
	}

	return false;
}

std::string LoadFirstProfileName() {
	// ファイル名として使用する文字列
	std::string filePath = "Init/profile.init";

	// ファイルを開く
	std::ifstream file(filePath);

	// ファイルが正しく開けたかを確認
	if (file.is_open()) {
		// 変数の値をファイルから読み込む
		std::string line;
		std::getline(file, line);//1行目のみ判定

		// ファイルを閉じる
		file.close();

		return line;
	}

	return "";
}

bool FindProfile(std::string name) {
	// ファイル名として使用する文字列
	std::string filePath_ = Profile::FolderName() + "/" + name + Profile::FileExtension();

	try {
		std::filesystem::path filePath(filePath_);

		// ファイルが存在するか確認
		return (std::filesystem::exists(filePath) && std::filesystem::is_regular_file(filePath));
	}
	catch (const std::filesystem::filesystem_error&) {
		printf_s("*** Error - プロファイル確認失敗(ファイルの検索中にエラーが発生しました(");
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