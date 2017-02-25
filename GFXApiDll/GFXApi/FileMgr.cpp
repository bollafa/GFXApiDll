#include "FileMgr.h"

std::vector<std::string> FileMgr::VectorOfListNames()
{
	std::vector<std::string> vElements;
	if (_mFile)
	{
		//std::cout << "Nope!" << std::endl;


		std::string CurrentLine;
		while (std::getline(_mFile, CurrentLine))
		{

			vElements.push_back(CurrentLine);


		}




	}
	return vElements;
}

void FileMgr::WriteString(std::string & inString)
{
	_mFile << inString;
}

bool FileMgr::FileExists(std::wstring In)
{
	
		std::ifstream infile(In);
		return infile.good();
	
	
}
