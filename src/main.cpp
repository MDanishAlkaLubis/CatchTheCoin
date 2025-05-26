#include <vector>

#include <raylib.h>

#define RAYGUI_IMPLEMENTATION
#include <raygui.h>

#include "coin.hpp"
#include "player.hpp"

enum class GameState{
	MainMenu,
	Gameplay
};

Texture2D bg_mainmenu;
Texture2D bg;
Texture2D coinTex;

Player player;
std::vector<Coin> coins;

void CoinLoop();

int main(){
	InitWindow(576, 950, "Game Duta Siswa");

	coinTex = LoadTexture("res/coin.png");
	bg = LoadTexture("res/bg_flap.png");
	bg_mainmenu = LoadTexture("res/bg_mainmenu.png");

	player = Player({(float)GetScreenWidth()/2 + 48, (float)GetScreenHeight() - 200}, "res/bird.png");

	for(int i = 0; i < 5; i++) {
		AddCoin(coins);
	}


	GameState state = GameState::MainMenu;

	SetTargetFPS(60);
	while(!WindowShouldClose()){
		BeginDrawing();
		ClearBackground(SKYBLUE);

		switch(state){
			case GameState::MainMenu:{
				DrawTexturePro(bg_mainmenu, {0, 0, (float)bg_mainmenu.width, (float)bg_mainmenu.height}, {0, 0, (float)GetScreenWidth()+10, (float)GetScreenHeight()+10}, {0, 0}, 0, WHITE);

				DrawText("Catch The Coin", 17, 135, 70, BLACK);

				if(GuiButton({(float)GetScreenWidth()/2 - 150, (float)GetScreenHeight()/2, 300, 70}, "START")){
					state = GameState::Gameplay;
				}

				if(GuiButton({(float)GetScreenWidth()/2 - 150, (float)GetScreenHeight()/2 + 100, 300, 70}, "QUIT")){
					CloseWindow();
				}
			} break;
			case GameState::Gameplay:{
				DrawTexturePro(bg, {0, 0, (float)bg.width, (float)bg.height}, {0, 0, (float)GetScreenWidth()+10, (float)GetScreenHeight()+10}, {0, 0}, 0, WHITE);
				player.Update(GetFrameTime());

				player.Draw();
				CoinLoop();

				player.Draw_UI();

			} break;
			default: break;
		}

		EndDrawing();
	}

	CloseWindow();
	return 0;
}
void CoinLoop(){
	for(auto& coin : coins){
		coin.pos.y += coin.speed * GetFrameTime();

		DrawTextureEx(coinTex, coin.pos, 0, 1.5, typeToColor[coin.type]);

		if(CheckCollisionRecs(player.get_body(), {coin.pos.x, coin.pos.y, (float)coinTex.width, (float)coinTex.height})){
			player.increase_coin(coin);

			std::erase(coins, coin);
			AddCoin(coins);
		}

		if(coin.pos.y > GetScreenHeight()){
			AddCoin(coins);
			std::erase(coins, coin);
		}
	}
}
