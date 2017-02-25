#include "GUISystem.h"
#include <cmath>
std::string PrintConcLists(UIList<std::string>& uiFirst, UIList<Time>& uiSecond)
{
	std::stringstream msg;
	auto jt = uiSecond.vObjectList.begin();
	for (auto it = uiFirst.vObjectList.begin(); it != uiFirst.vObjectList.end(); ++it)
	{
		msg << *it;

		if (jt != uiSecond.vObjectList.end())
		{
			for (int i = 0; i < std::abs( (int)(25 - it->length())); ++i)
				msg << " ";
			//msg << "\t";
			msg << *jt;
			++jt;
		}
		msg << std::endl;
	}

	/*for (auto it = uiSecond.vObjectList.begin(); it != uiSecond.vObjectList.end(); ++it)
	msg <<  *it << std::endl;*/
	return msg.str();
}
