#include "raylib.h"
#include "../include/resource_dir.h"

#include "IceObj.h"

/*
 * Browser support
 * See https://github.com/raysan5/raylib/wiki/Working-for-Web-(HTML5)
 */
#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

static void UpdateFrame();
static void DrawingFrame();

static const int screenWidth = 800;
static const int screenHeight = 450;

static int score1 = 0;
static int score2 = 0;

static Image puckImg;
static Texture2D p;

static Image logoImg;
static Texture2D logo;

static Image p1Img;
static Texture2D p1;

static Image p2Img;
static Texture2D p2;

static Sound goalSound;

static bool gamePaused;

static Rectangle p1GoalBox;
static Rectangle p2GoalBox;

static IceObj play1(100, 225);
static IceObj play2(700, 225);
// static IceObj puck;

int main() {
	InitWindow(screenWidth, screenHeight, "Puckman Ball");

	// Included with Raylib-Quickstart to easily load media
	SearchAndSetResourceDir("resources");

	/* TODO resize images prior to runtime */

	// School logo at center of rink
	logoImg = LoadImage("rpi-logo.png");
	ImageResize(&logoImg, (int)(logoImg.width / 16), (int)(logoImg.height / 16));
	logo = LoadTextureFromImage(logoImg);

	puckImg = LoadImage("puck.png");
	ImageResize(&puckImg, (int)(puckImg.width / 16), (int)(puckImg.height / 16));
	p = LoadTextureFromImage(puckImg);

	// Player 1 image
	p1Img = LoadImage("puckman.png");
	ImageResize(&p1Img, (int)(p1Img.width / 1.75), (int)(p1Img.height / 1.75));
	p1 = LoadTextureFromImage(p1Img);

	// Player 2 image
	p2Img = LoadImage("greenpuckman.png");
	ImageResize(&p2Img, (int)(p2Img.width / 1.75), (int)(p2Img.height / 1.75));
	p2 = LoadTextureFromImage(p2Img);

	goalSound = LoadSound("rpigoalsfx.mp3");

	// Goal box rectangles
	p2GoalBox = (Rectangle){screenWidth-15, screenHeight / 3 + screenHeight/27, 4, screenHeight/3 - screenHeight/15};
	p1GoalBox = (Rectangle){20,screenHeight / 3 + screenHeight/27, 4, screenHeight/3 - screenHeight/14};

	score1 = 0;
	score2 = 0;

	#if defined(PLATFORM_WEB)
    		emscripten_set_main_loop(UpdateDrawFrame, 0, 1);
	#else
    		SetTargetFPS(30);
	#endif

	// game loop runs until ESC key is pressed
	while (!WindowShouldClose()) { 
		if (IsKeyPressed('P')) {gamePaused = !gamePaused;}
		if (!gamePaused) { UpdateFrame(); }
		DrawingFrame();
	}

	/* UNLOAD all sounds and images here */
	UnloadSound(goalSound);
	UnloadTexture(logo);
	UnloadImage(logoImg);

	UnloadTexture(p);
	UnloadImage(puckImg);

	UnloadTexture(p1);
	UnloadImage(p1Img);

	UnloadTexture(p2);
	UnloadImage(p2Img);

	// close the window and exit cleanly
	CloseWindow();
	return 0;

}

static void UpdateFrame() {
	// Handle user input (WASD for play1, arrows for play2)
	if ( IsKeyDown(KEY_W) ) { play1.accel.y = -0.25; }
	if ( IsKeyDown(KEY_S) ) { play1.accel.y = 0.25; }
	if ( IsKeyDown(KEY_A) ) { play1.accel.x = -0.25; }
	if ( IsKeyDown(KEY_D) ) { play1.accel.x = 0.25; }
	if ( IsKeyDown(KEY_UP) ) { play2.accel.y = -0.25; }
	if ( IsKeyDown(KEY_DOWN) ) { play2.accel.y = 0.25; }
	if ( IsKeyDown(KEY_LEFT) ) { play2.accel.x = -0.25; }
	if ( IsKeyDown(KEY_RIGHT) ) { play2.accel.x = 0.25; }
	// reset accel if neither direction is pressed
	if ( !IsKeyDown(KEY_LEFT) && !IsKeyDown(KEY_RIGHT) ) {
		play2.accel.x = -0.02;
	}
	if ( !IsKeyDown(KEY_UP) && !IsKeyDown(KEY_DOWN) ) {
           	play2.accel.y = -0.02;
        }
	if ( !IsKeyDown(KEY_A) && !IsKeyDown(KEY_D) ) {
            	play1.accel.x = -0.02;
        }
	if ( !IsKeyDown(KEY_W) && !IsKeyDown(KEY_S) ) {
            	play1.accel.x = -0.02;
        }	

	play1.updatePosition();
	play2.updatePosition();
	/* update puck position */

	/* TODO rounded corner collision with Vector2DotProduct() */


	/* TODO switch to circle hitboxes */
	// Rectangle puckBox = (Rectangle){puck.position.x, puck.position.y, p.width, p.height};

	Rectangle p1Box = (Rectangle){play1.position.x, play1.position.y, (float)p1.width, (float)p1.height};
	Rectangle p2Box = (Rectangle){play2.position.x, play2.position.y, (float)p2.width, (float)p2.height};

	/* TODO find math functions for angle collision */

	// reset players if (CheckCollisionRecs(p1GoalBox, puckBox))
		
}

static void DrawingFrame() {
	BeginDrawing();

	ClearBackground(LIGHTGRAY);

	// Draw the stadium to screen

	DrawRectangleRounded( (Rectangle){5, 5, screenWidth - 10, screenHeight - 10}, 0.3f, 1, DARKGRAY);
	DrawRectangleRounded( (Rectangle){10, 10, screenWidth - 20, screenHeight - 20}, 0.3f, 1, WHITE);

	DrawRectangle(screenWidth/2 - 2, 10, 4, screenHeight - 20, RED);
	DrawRectangle((int)(screenWidth * 0.15) - 2, 10, 4, screenHeight- 20, RED);
	DrawRectangle((int)(screenWidth * 0.85) - 2, 10, 4, screenHeight- 20, RED);

	DrawText(TextFormat("%i", score1), screenWidth * 1 / 4 - 10, screenHeight/10, 70, BLACK);
	DrawText(TextFormat("%i", score2), screenWidth * 3 / 4 - 10, screenHeight/10, 70, BLACK);

	DrawCircle(screenWidth/2, screenHeight/2, 40, RED);
	DrawCircle(screenWidth/2, screenHeight/2, 37, WHITE);
	DrawTexture(logo, screenWidth/2 - logo.width/2, screenHeight/2 - logo.height/2, WHITE);
	
	// Right/Player 2 Goal Box
	DrawRectangle(screenWidth - screenWidth/16, screenHeight / 3, screenWidth/16 - 10, screenHeight/3, ColorFromHSV(180, 1, 1));
	DrawRectangle(screenWidth - screenWidth/16 + 3, screenHeight / 3 + 3, screenWidth/16 - 13, screenHeight/3 - 6, WHITE);

	DrawRectangle(screenWidth-15,screenHeight / 3 + screenHeight/27, 4, screenHeight/3 - screenHeight/14,BLACK);

	// Left/Player 1 Goal Box
	DrawRectangle(10, screenHeight / 3, screenWidth/16 - 10, screenHeight/3, RED);
	DrawRectangle(10, screenHeight / 3 + 3, screenWidth/16 - 13, screenHeight/3 - 6, WHITE);

	DrawRectangle(15,screenHeight / 3 + screenHeight/27, 4, screenHeight/3 - screenHeight/14,BLACK);

	// Draw puck and player
	DrawTexture(p1, (int)(play1.position.x - p1.width / 2), (int)(play1.position.y - p1.height / 2), WHITE);
	DrawTexture(p2, (int)(play2.position.x - p1.width / 2), (int)(play2.position.y - p2.height / 2), WHITE);
	// DrawTexture(p, (int)(puck.position.x - 25), (int)(puck.position.y - 25), WHITE);
	
	// Draw puck and player
	DrawTexture(p1, (int)(play1.position.x - p1.width / 2), (int)(play1.position.y - p1.height / 2), WHITE);
	DrawTexture(p2, (int)(play2.position.x - p1.width / 2), (int)(play2.position.y - p2.height / 2), WHITE);
	// DrawTexture(p, (int)(puck.position.x - 25), (int)(puck.position.y - 25), WHITE);

	if (score1 == 7) {
		DrawText("Player 1 Wins", screenWidth/4, screenHeight/2, 50, BLACK);
	} else if (score2 == 7) {
		DrawText("Player 2 Wins", screenWidth/4, screenHeight/2, 50, BLACK);
	}

	EndDrawing();
}
