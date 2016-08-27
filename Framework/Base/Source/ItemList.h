#ifndef ITEMLIST_H
#define ITEMLIST_H

#include "Items.h"

class ItemList
{
public:
	ItemList();
	~ItemList();
	void UseItem();
	bool Add(Items* item);
	void Remove();

	Items* GetSelectedItem(void);
	void SetSelectedItem(int selectedItem);

	int GetTotalItemCount(void);
	void SetTotalItemCount(int TotalItemCount);

	void CycleItems();

private:
	const int MaxItemHold;
	Items** itemHold;
	int selectedItem;
	int TotalItemCount;
};



#endif