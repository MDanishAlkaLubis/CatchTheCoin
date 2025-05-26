#pragma once

#include <raylib.h>

#include "coin.hpp"

class Player{
private:
	Rectangle body;
	Texture2D tex;

	int coins;
	int flip;
public:
	Rectangle get_body(){return body;}
	int get_total_coins(){return coins;}

	void change_scale(float scale);
	void increase_coin(Coin coin);

	void Draw();
	void Draw_UI();
	void Update(float dt);

	Player(Vector2 pos, const char* tex_path);
	Player(){};
};
