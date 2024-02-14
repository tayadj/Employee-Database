#include "preset.h"

namespace project
{
	std::string			cmdCreator;
	std::wstring		cmdCreator_;
	std::string			cmdReporter;
	std::wstring		cmdReporter_;

	LPWSTR				cmdCreatorCode;	
	LPWSTR				cmdReporterCode;
	STARTUPINFO			settingsInfo;
	PROCESS_INFORMATION processInfo;

	std::fstream		binaryFile;
	std::fstream		textFile;
	std::string			binaryFileName;
	std::string			textFileName;
	std::string			records;
	std::string			wages;
	std::string			buffer;
	employee			object;

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
				std::cerr << "Oops! The amount of records must be a positive number.";
				exit(0);
			}
			case 3:
			{
				std::cerr << "Oops! The text file's name must be next format: \'fileName.txt\'";
				exit(0);
			}
			case 4:
			{
				std::cerr << "Oops! The amount of wages must be a positive number.";
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
					if (std::stoi(records) == 0)
					{
						result = false;
					}
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
			case 3:
			{
				if (textFileName.length() < 5 || textFileName.substr(textFileName.length() - 4) != ".txt")
				{
					result = false;
				}
				break;
			}
			case 4:
			{
				try
				{
					if (std::stoi(wages) == 0)
					{
						result = false;
					}
				}
				catch (...)
				{
					result = false;
				}
				if (wages[0] == '-')
				{
					result = false;
				}
				break;
			}
		}
		return result;
	}

	void receiveDataCreator()
	{
		std::cout << "Input the binary file name: ";
		std::cin >> binaryFileName;
		if (!checker(1)) { terminate(1); }
		std::cout << "Input the number of records: ";
		std::cin >> records;
		if (!checker(2)) { terminate(2); }
	}

	void openCreator()
	{
		cmdCreator = "creator.exe " + binaryFileName + " " + records;
		cmdCreator_ = std::wstring(cmdCreator.begin(), cmdCreator.end());

		cmdCreatorCode = &cmdCreator_[0];

		ZeroMemory(&settingsInfo, sizeof(STARTUPINFO));
		settingsInfo.cb = sizeof(STARTUPINFO);
		ZeroMemory(&processInfo, sizeof(PROCESS_INFORMATION));

		try
		{
			if (!CreateProcess(nullptr, cmdCreatorCode, nullptr, nullptr, FALSE, 0, nullptr, nullptr, &settingsInfo, &processInfo))
			{
				std::cerr << "Process creator.exe failed. Error code: " << GetLastError() << "\n";
				exit(GetLastError());
			}
		}
		catch (...)
		{
			std::cerr << "Process creator.exe failed. Error code: " << GetLastError() << "\n";
			exit(GetLastError());
		}

		WaitForSingleObject(processInfo.hProcess, INFINITE);

		CloseHandle(processInfo.hProcess);
		CloseHandle(processInfo.hThread);

		std::clog << "\nBinary file created. Review:\nID\t\t\tName\t\t\tHours\n";
		binaryFile.open(binaryFileName, std::ios::binary | std::ios::in);
		while (binaryFile.read((char*)&object, sizeof(employee)))
		{
			std::clog << object.id << "\t\t\t" << object.name << "\t\t\t" << object.hours << '\n';
		}
		binaryFile.close();
	}

	void receiveDataReporter()
	{
		std::cout << "\nInput the text file name: ";
		std::cin >> textFileName;
		if (!checker(3)) { terminate(3); }
		std::cout << "Input the amount of wages: ";
		std::cin >> wages;
		if (!checker(4)) { terminate(4); }
	}

	void openReporter()
	{
		cmdReporter = "reporter.exe " + binaryFileName + " " + textFileName + " " + wages;
		cmdReporter_ = std::wstring(cmdReporter.begin(), cmdReporter.end());

		cmdReporterCode = &cmdReporter_[0];

		try
		{
			if (!CreateProcess(nullptr, cmdReporterCode, nullptr, nullptr, FALSE, 0, nullptr, nullptr, &settingsInfo, &processInfo))
			{
				std::cerr << "Process reporter.exe failed. Error code: " << GetLastError() << "\n";
				exit(GetLastError());
			}
		}
		catch (...)
		{
			std::cerr << "Process reporter.exe failed. Error code: " << GetLastError() << "\n";
			exit(GetLastError());
		}

		WaitForSingleObject(processInfo.hProcess, INFINITE);

		CloseHandle(processInfo.hProcess);
		CloseHandle(processInfo.hThread);

		std::clog << "\nText file created. Review:\n";
		textFile.open(textFileName, std::ios::in);
		while (!textFile.eof())
		{
			std::getline(textFile, buffer);
			std::clog << buffer << '\n';
		}
		textFile.close();
	}
}

int main(int argc, char* argv[])
{
	std::clog << "Starting project...\n\n";
	project::receiveDataCreator();
	project::openCreator();
	project::receiveDataReporter();
	project::openReporter();
	std::clog << "Finishing project...\n\n";
	return 0;
}


