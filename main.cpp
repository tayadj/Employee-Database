#include "preset.h"

namespace project
{
	std::string			cmdCreator;
	std::wstring		cmdCreator_;
	std::string			cmdReporter;
	std::wstring		cmdReporter_;

	LPWSTR				cmdProcessCode;
	STARTUPINFO			settingsInfo;
	PROCESS_INFORMATION processInfo;

	std::fstream		inputFile;
	std::fstream		outputFile;
	std::string			binaryFileName;
	std::string			textFileName;
	std::string			records;

	void terminate(int status)
	{
		switch (status)
		{
			case 1:
			{
				std::cerr << "Oops! The binary file's name must be next format: \'fileName.bin\'";
				exit(0);
			}
			case 2:
			{
				std::cerr << "Oops! The number of records must be a positive number.";
				exit(0);
			}
		}
	}

	bool checker(int status)
	{
		bool result = true;
		switch (status)
		{
			case 1:
			{
				
				if (binaryFileName.length() < 5 || binaryFileName.substr(binaryFileName.length() - 4) != ".bin")
				{
					result = false;
				}
				break;
			}
			case 2:
			{
				try
				{
					std::stoi(records);
				}
				catch (...)
				{
					result = false;
				}
				if (records[0] == '-')
				{
					result = false;
				}
				break;
			}
		}
		return result;
	}

	void receiveData()
	{
		std::clog << "Starting project...\n";
		std::cout << "Input the binary file name: ";
		std::cin >> binaryFileName;
		if (!checker(1)) { terminate(1); }
		std::cout << "Input the number of records: ";
		std::cin >> records;
		if (!checker(2)) { terminate(2); }
	}

	void printFile()
	{

	}

	void openCreator()
	{
		cmdCreator = "creator.exe " + binaryFileName + " " + records;
		cmdCreator_ = std::wstring(cmdCreator.begin(), cmdCreator.end());

		cmdProcessCode = &cmdCreator_[0];

		ZeroMemory(&settingsInfo, sizeof(STARTUPINFO));
		settingsInfo.cb = sizeof(STARTUPINFO);

		try
		{
			CreateProcess(nullptr, cmdProcessCode, nullptr, nullptr, TRUE, CREATE_NEW_CONSOLE, nullptr, nullptr, &settingsInfo, &processInfo);
		}
		catch (...)
		{
			std::cerr << "Process creator.exe failed.\n";
			exit(GetLastError());
		}

		WaitForSingleObject(processInfo.hProcess, INFINITE);
	}

	void openReporter()
	{

	}
}

int main(int argc, char* argv[])
{
	project::receiveData();
	project::openCreator();
	return 0;
}



