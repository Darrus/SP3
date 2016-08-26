#include "ItemList.h"

ItemList::ItemList()
{

}

ItemList::~ItemList()
{

}

int ItemList::GetTotalItemCount(void)
{
	return TotalItemCount;
}

void ItemList::SetTotalItemCount(int TotalItemCount)
{
	this->TotalItemCount = TotalItemCount;
}

void ItemList::UseItem()
{
	/*if (itemHold[selectedItem].UseItem())
	{

	}*/
}

void ItemList::Add(Items item)
{
	/*if (TotalItemCount < 3)
	{
		itemHold[TotalItemCount] = item;
		TotalItemCount++;
	}*/
}