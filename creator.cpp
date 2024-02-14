#include "preset.h"

namespace project
{
	std::fstream		binaryFile;
	std::string			binaryFileName;
	std::string			textFileName;
	employee			object;
	std::string			objectName;
	std::string			objectHours;
	std::string			objectID;
	int					records;
	
	void terminate(int status)
	{
		switch (status)
		{
			case 1:
			{
				std::cerr << "Oops! The amount of hours must be a positive number.";
				exit(0);
			}
			case 2:
			{
				std::cerr << "Oops! The length of name must be at most 100 characters.";
				exit(0);
			}
			case 3:
			{
				std::cerr << "Oops! The ID must be a positive number.";
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
				try
				{
					std::stoi(objectHours);
				}
				catch (...)
				{
					result = false;
				}
				if (objectHours[0] == '-')
				{
					result = false;
				}
				break;
			}
			case 2:
			{
				if (objectName.length() > 100)
				{
					result = false;
				}
				break;
			}
			case 3:
			{
				try
				{
					std::stoi(objectID);
				}
				catch (...)
				{
					result = false;
				}
				if (objectID[0] == '-')
				{
					result = false;
				}
				break;
			}
		}
		return result;
	}

	void process(int argc, char* argv[])
	{
		binaryFileName = argv[1];
		records = std::stoi(argv[2]);

		try
		{
			binaryFile.open(binaryFileName, std::ios::binary | std::ios::out);

			if (binaryFile.is_open())
			{
				for (size_t i = 0; i < records; i++)
				{
					std::cout << "\nEnter employee " << i + 1 << ":\nID: ";
					std::cin >> objectID;
					std::cout << "Name: ";
					std::cin >> objectName;
					std::cout << "Hours: ";
					std::cin >> objectHours;
					if (!checker(1)) { terminate(1); }
					if (!checker(2)) { terminate(2); }
					if (!checker(3)) { terminate(3); }
					strcpy_s(object.name, objectName.c_str());
					object.hours = stoi(objectHours);
					object.id = stoi(objectID);
					binaryFile.write((char*)&object, sizeof(employee));
				}
				binaryFile.close();
			}
		}
		catch (...)
		{
			std::cerr << "Process creator.exe failed. Error code: " << GetLastError() << "\n";
			exit(GetLastError());
		}
	}
}

int main(int argc, char* argv[])
{
	project::process(argc, argv);
	return 0;
}