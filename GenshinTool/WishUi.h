#pragma once

#define MAXLOAD_HISTORY 200

#include <vector>
#include "Display.h"
#include "Data.h"
#include "Option.h"
#include "WishPool.h"

using namespace std;

class WishUi 
{
private:
	vector<WishPool> wishPool;

	void connectVector(vector<string>* subject, vector<string>* object);

	string showItem(WishHistory item);

	void createLimitWishPool();
	void createWeaponWishPool();
	void createStayWishPool();

	unsigned int showHistoryList(string type, unsigned int poolPos, unsigned int minNum, unsigned int maxNum,
		short selectStarMin = 0, short selectStarMax = 5, int itemType = -1, string name = "",
		unsigned int minDistance = 1, unsigned int maxDistance = 90);
	WishHistory selectHistory(unsigned int poolPos, short star);
	WishHistory selectHistory(unsigned int poolPos, short star, int type);

public:
	WishUi();

	void showUi();

	void showLimitWishPoolUi(int poolId = 1);
	void showWeaponWishPoolUi();
	void showStayWishPoolUi();
	void showChooseUi();
	void showHistoryUi(bool isStatic);
	void showSelectHistoryUi();
	void showItemList(int poolId);

	void singleWishResult(int poolId);
	void templeWishResult(int poolId);
	void nWishResult(int poolId, int n);
};