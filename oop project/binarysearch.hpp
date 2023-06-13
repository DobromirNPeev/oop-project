#pragma once
#include "SocialNetwork.h"

template<typename T>
int SocialNetwork::binarySearchInVector(const Vector<T>& arr, int el)
{
	int left = 0, right = arr.getSize() - 1;

	while (left <= right)
	{
		unsigned mid = left + (right - left) / 2;
		if (arr[mid].getID() == el)
			return mid;
		else if (arr[mid].getID() > el)
			right = mid - 1;
		else //arr[mid] < el
			left = mid + 1;
	}
	return -1;
}