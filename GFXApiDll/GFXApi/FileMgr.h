#pragma once
#include "../stdafx.h"

class FileMgr {

private:
	std::fstream _mFile;
public:
	FileMgr(std::wstring sFileName, std::ios_base::openmode iMode) 
	{
		/*
		WHAT IF IT FAILS?
		R: Dunno, check if it's null or smth I guess
		*/
		_mFile.open(sFileName, iMode);

	}
	FileMgr(std::string sFileName, std::ios_base::openmode iMode) : _mFile(sFileName, iMode)
	{
		/*
		WHAT IF IT FAILS?
		R: Dunno, check if it's null or smth I guess
		*/


	}
	std::vector<std::string> VectorOfListNames();
	template<typename T>
	void WriteVectorOfData(std::vector<T> Data);
	void WriteString(std::string & inString);
	void const Close() { _mFile.close(); };
	template < typename T> std::vector<T> TokenRead(T TT,char Del);
	static bool FileExists(std::wstring In);

};
template<typename T>
inline void FileMgr::WriteVectorOfData(std::vector<T> Data)
{
	std::stringstream sWrited;
	for (auto it = Data.begin(); it != Data.end(); ++it)
		sWrited << *it << "\n";
	_mFile << sWrited;
}

template<typename T>
inline std::vector<T> FileMgr::TokenRead(T TT,char Del)
{
	
	std::string sTemp;
	std::vector<T> TupleVector;
//	std::cout << std::tuple_size<T>::value << std::endl;
	char Ts;
	while (std::getline(_mFile, sTemp))
	{
		std::stringstream in(sTemp);
		T tTemp;
			
			if (!((in >> Ts >> std::get<0>(tTemp) >> Ts >> std::get<1>(tTemp) >> Ts >> std::get<2>(tTemp) >> Ts >> std::get<3>(tTemp)) && (Ts == ',')))
			{
				//std::cout << "INIF:::::: " << in.str() << std::endl;
				continue;
			}

			//std::cout << "OutOfIf " << in.str() << std::endl;
			
			TupleVector.push_back(tTemp);
	}
		return TupleVector;
}
