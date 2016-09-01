#include "ItemList.h"
#include "SoundEngine.h"

ItemList::ItemList() :
MaxItemHold(3),
TotalItemCount(0),
selectedItem(0)
{
	itemHold = new Items*[MaxItemHold];
	for (int i = 0; i < MaxItemHold; ++i)
	{
		itemHold[i] = NULL;
	}

	SoundEngine::GetInstance().AddSound("Item", "Sound//Item.mp3");
	SoundEngine::GetInstance().AddSound("Pickup", "Sound//Pickup.mp3");
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
	if (itemHold[selectedItem] && itemHold[selectedItem]->UseItem())
	{
		SoundEngine::GetInstance().Play("Item");
		Remove();
	}
}

bool ItemList::Add(Items* item)
{
	for (int i = 0; i < MaxItemHold; ++i)
	{
		if (!itemHold[i])
		{
			SoundEngine::GetInstance().Play("Pickup");
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