#ifndef ITEMLIST_H
#define ITEMLIST_H

#include "Items.h"

class ItemList
{
public:
	ItemList();
	~ItemList();
	void UseItem();
	void Add(Items item);
	void Remove(Items item);

	int GetSelectedItem(void);
	void SetSelectedItem(int selectedItem);

	int GetTotalItemCount(void);
	void SetTotalItemCount(int TotalItemCount);

private:
	Items itemHold[3];
	int selectedItem;
	int TotalItemCount;

};



#endif