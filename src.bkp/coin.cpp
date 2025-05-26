#include "coin.hpp"

void AddCoin(std::vector<Coin>& coins){
	float x = GetRandomValue(0, GetScreenWidth() - 64);
	int speed = GetRandomValue(420, 470);

	int coin_rand = GetRandomValue(0, 5);
	CoinType type;
	switch(coin_rand){
		case 0: type = CoinType::Bad; break;
		case 1: type = CoinType::Good; break;
		default: type = CoinType::Normal; break;
	}

	coins.push_back({{x, 0.0f}, speed, type});
}
