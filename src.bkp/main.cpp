#include <cmath>

#include <raylib.h>

#define RAYGUI_IMPLEMENTATION
#include <raygui.h>


#include "player.hpp"
#include "coin.hpp"

/*
catch it clone

-player class-
-falling normal guys-
-falling bad guys-
-falling good guys-
-main menu ui-

*/

enum class GameState{
	MainMenu,
	Gameplay
};

Texture2D coinTex;
Texture2D bg;
Texture2D bg_mainmenu;

Player player;
std::vector<Coin> coins;

void Coin_Loop();

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
	GuiSetStyle(DEFAULT, TEXT_SIZE, 30);

	GuiSetStyle(BUTTON, TEXT_COLOR_NORMAL, ColorToInt(WHITE));
	GuiSetStyle(BUTTON, TEXT_COLOR_FOCUSED, ColorToInt(WHITE));
	GuiSetStyle(BUTTON, TEXT_COLOR_PRESSED, ColorToInt(WHITE));

	SetTargetFPS(60);
	while(!WindowShouldClose()){

		BeginDrawing();

		ClearBackground(SKYBLUE);

		switch(state){
			case GameState::MainMenu:{
				DrawTexturePro(bg_mainmenu, {0, 0, (float)bg.width, (float)bg.height}, {0, 0, (float)GetScreenWidth()+10, (float)GetScreenHeight()+10}, {0, 0}, 0, WHITE);

				DrawText("Catch The Coin", 17, 135, 70, BLACK);

				GuiSetStyle(BUTTON, BASE_COLOR_NORMAL, ColorToInt({0, 220, 0, 255}));
				GuiSetStyle(BUTTON, BASE_COLOR_FOCUSED, ColorToInt({0, 190, 0, 255}));
				GuiSetStyle(BUTTON, BASE_COLOR_PRESSED, ColorToInt({0, 150, 0, 255}));

				if(GuiButton({(float)GetScreenWidth()/2 - 150, (float)GetScreenHeight()/2, 300, 70}, "START")){
					state = GameState::Gameplay;
				}

				GuiSetStyle(BUTTON, BASE_COLOR_NORMAL, ColorToInt({220, 30, 30, 255}));
				GuiSetStyle(BUTTON, BASE_COLOR_FOCUSED, ColorToInt({190, 30, 30, 255}));
				GuiSetStyle(BUTTON, BASE_COLOR_PRESSED, ColorToInt({150, 30, 30, 255}));

				if(GuiButton({(float)GetScreenWidth()/2 - 150, (float)GetScreenHeight()/2 + 100, 300, 70}, "QUIT")){
					CloseWindow();
				}

			} break;
			case GameState::Gameplay:{
				player.Update(GetFrameTime());
				DrawTexturePro(bg, {0, 0, (float)bg.width, (float)bg.height}, {0, 0, (float)GetScreenWidth()+10, (float)GetScreenHeight()+10}, {0, 0}, 0, WHITE);

				player.Draw();
				Coin_Loop();

				player.Draw_UI();
			} break;
			default: break;
		}

		EndDrawing();
	}

	CloseWindow();

	return 0;
}

void Coin_Loop(){
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
