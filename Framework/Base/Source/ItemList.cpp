#include "ItemList.h"

ItemList::ItemList() :
MaxItemHold(3),
TotalItemCount(0),
selectedItem(0)
//HealthPotionCount(3)
{
	itemHold = new Items*[MaxItemHold];
	for (int i = 0; i < MaxItemHold; ++i)
	{
		itemHold[i] = NULL;
	}
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
	if (itemHold[selectedItem] && itemHold[selectedItem]->UseItem())
		Remove();
}

bool ItemList::Add(Items* item)
{
	for (int i = 0; i < MaxItemHold; ++i)
	{
		if (!itemHold[i])
		{
			item->pos.Set(-500.f, -500.f, 1.f);
			itemHold[i] = item;
			return true;
		}
	}
	return false;
}

void ItemList::Remove()
{
	itemHold[selectedItem]->active = false;
	itemHold[selectedItem] = NULL;
}

void ItemList::CycleItems()
{
	selectedItem = (selectedItem + 1) % MaxItemHold;
}

Items* ItemList::GetSelectedItem(void)
{
	return itemHold[selectedItem];
}