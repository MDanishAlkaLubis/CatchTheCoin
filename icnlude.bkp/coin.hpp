#pragma once

#include <cmath>
#include <vector>
#include <map>

#include <raylib.h>

enum class CoinType{
	Normal,
	Good,
	Bad
};

struct Coin{
	Vector2 pos;
	int speed;
	CoinType type;

	bool operator==(const Coin& other) const {
		return std::fabs(pos.x - other.pos.x) < 0.001f &&
		std::fabs(pos.y - other.pos.y) < 0.001f &&
		speed == other.speed &&
		type == other.type;
	}
};

void AddCoin(std::vector<Coin>& coins);

static std::map<CoinType, Color> typeToColor = {
	{CoinType::Normal, WHITE},
	{CoinType::Good, GREEN},
	{CoinType::Bad, RED}
};

