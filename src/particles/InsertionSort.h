#pragma once
#include "particles/Particle.h"

class InsertionSort
{
public:
	static void sortHighToLow(std::vector<Particle>& list)
	{
		for (size_t i = 1; i < list.size(); ++i)
		{
			Particle item = list[i];
			if (item.getDistance() > list[i - 1].getDistance())
			{
				sortUpHighToLow(list, i);
			}
		}
	}

private:
	static void	sortUpHighToLow(std::vector<Particle>& list, int i)
	{
		Particle item = list[i];
		int attempPos = i - 1;
		while(attempPos != 0 && list[attempPos - 1].getDistance() < item.getDistance())
		{
			attempPos--;
		}
		list.erase(list.begin() + i);
		list.insert(list.begin() + i, item);
	}
};