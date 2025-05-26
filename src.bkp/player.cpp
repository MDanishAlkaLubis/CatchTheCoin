#include "player.hpp"

#include <string>

#define SPEED 400

void Player::change_scale(float scale){
	body.width *= scale;
	body.height *= scale;
}

void Player::increase_coin(Coin coin){
	switch(coin.type){
		case CoinType::Normal: coins++; break;
		case CoinType::Good: coins+=3; break;
		case CoinType::Bad: coins-=1; break;
		default:
		break;
	}
}

void Player::Draw(){
	DrawTexturePro(tex, {0, 0, (float)tex.width*flip, (float)tex.height}, body, {0, 0}, 0, WHITE);
}

void Player::Draw_UI(){
	DrawText(std::to_string(coins).c_str(), 20, 20, 35, YELLOW);
}

void Player::Update(float dt){
	if(IsKeyDown(KEY_D)){ body.x += SPEED * dt; flip = 1; }
	if(IsKeyDown(KEY_A)){ body.x -= SPEED * dt; flip = -1; }}


Player::Player(Vector2 pos, const char* tex_path)
:body{pos.x, pos.y, 86*1.5, 50*1.5}, tex{LoadTexture(tex_path)}, coins{0}, flip{1}{
}
