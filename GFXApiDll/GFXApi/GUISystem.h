#pragma once
#include "..\stdafx.h"
#include "Timer.h"
class UIObject
{
protected:
	RECT Coordinates;
public:
	UIObject()
	{

	}
	UIObject(RECT desiredPos) : Coordinates(desiredPos)
	{


	}
	virtual std::string Update() = 0;
	void SetPos(POINT pDesiredPos) { Coordinates.left = pDesiredPos.x; Coordinates.top = pDesiredPos.y; };
};

/*template< typename Ts, typename TT>
void PrintConcLists(UIList<Ts> &uiFirst, UIList<TT> &uiSecond);*/
template < typename T>
class UIList;
extern std::string PrintConcLists(UIList<std::string> &uiFirst, UIList<Time> &uiSecond);
template < typename T>
class UIList : public  UIObject
{

private:
	std::vector< T > vObjectList;
	// Optional Hint
public:
	UIList()
	{

	}
	UIList(RECT desiredPos) : UIObject(desiredPos)
	{


	}

	friend std::string PrintConcLists(UIList<std::string> &uiFirst, UIList<Time> &uiSecond);
	//friend void TestFriend<T>(T b);
	void AddObject(T &tObject);
	void AddWithVector(std::vector<T> &tObject);
	std::string Update(); // Draw the stuff

};

template<typename T>
inline void UIList<T>::AddObject(T & tObject)
{
	vObjectList.push_back(tObject);
}

template<typename T>
inline void UIList<T>::AddWithVector(std::vector<T>& tObject)
{
	vObjectList = tObject;
}

template<typename T>
inline std::string UIList<T>::Update()
{
	std::stringstream msg;

	for (auto it = vObjectList.begin(); it != vObjectList.end(); ++it)
		msg << *it << std::endl;
	return msg.str();
}
