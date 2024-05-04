#include "../include/preset.h"

namespace project
{
	std::fstream		binaryFile;
	std::fstream		textFile;
	std::string		binaryFileName;
	std::string		textFileName;
	employee		object;
	int			wages;

	void process(int argc, char* argv[])
	{
		binaryFileName = argv[1];
		textFileName = argv[2];
		wages = std::stoi(argv[3]);

		try
		{
			binaryFile.open(binaryFileName, std::ios::binary | std::ios::in);
			textFile.open(textFileName, std::ios::out);

			if (binaryFile.is_open() && textFile.is_open())
			{
				textFile << "Report via " << binaryFileName << "\nID\t\t\tName\t\t\tHours\t\t\tSalary\n";
				while (binaryFile.read((char*)&object, sizeof(employee)))
				{
					textFile << object.id << "\t\t\t" << object.name << "\t\t\t" << object.hours << "\t\t\t" << object.hours * wages << '\n';
				}
				textFile.close();
				binaryFile.close();
			}
		}
		catch (...)
		{
			std::cerr << "Process reporter.exe failed. Error code: " << GetLastError() << "\n";
			exit(GetLastError());
		}
	}
}

int main(int argc, char* argv[])
{
	project::process(argc, argv);
	return 0;
}
