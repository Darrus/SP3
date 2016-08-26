#include "ItemList.h"

ItemList::ItemList()
//HealthPotionCount(3)
{

}

ItemList::~ItemList()
{

}

//int ItemList::GetHealthPotionCount(void)
//{
//	return HealthPotionCount;
//}
//
//void ItemList::SetHealthPotionCount(int HealthPotionCount)
//{
//	this->HealthPotionCount = HealthPotionCount;
//}

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
	if (TotalItemCount < 3)
	{
		itemHold[TotalItemCount] = item;
		TotalItemCount++;
	}
}

void ItemList::Remove(Items item)
{
	if (TotalItemCount > 0)
	{
		itemHold[TotalItemCount] = item;
		TotalItemCount--;
	}
	else if (TotalItemCount <= 0)
	{
		TotalItemCount = 0;
	}
}

