#include "raylib.h"
#include "resource_dir.h"

#include "Player.h"

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

static int score1;
static int score2;

static int p1Score;
static int p2Score;

static Image puckImg;
static Texture2D p;

static Image rpiLogo;
static Texture2D logo;

static Image p1Img;
static Texture2D p1;

static Image p2Img;
static Texture2D p2;

static Sound goalSound;

static bool gamePaused;

static Rectangle p1GoalBox;
static Rectangle p2GoalBox;

int main() {
	// Included with Raylib-Quickstart to easily load media
	SearchAndSetResourceDir("resources");

	// School logo at center of rink
	logoImg = LoadImage("rpi-logo.png");
	// ImageResize(&logoImg, (int)(logoImg.width / 16), (int)(logoImg.height / 16));
	logo = LoadTextureFromImage(rpiLogo);

	puckImg = LoadImage("puck.png");
	// ImageResize(&puckImg, (int)(puckImg.width / 16), (int)(puckImg.height / 16));
	p = LoadTextureFromImage(puckImg);

	// Player 1 image
	p1Img = LoadImage("puckman.png");
	// ImageResize(&p1Img, (int)(p1Img.width / 1.75), (int)(p1Img.height / 1.75));
	p1 = LoadTextureFromImage(p1Img);

	// Player 2 image
	p2Img = LoadImage("greenpuckman.png");
	// ImageResize(&p2Img, (int)(p2Img.width / 1.75), (int)(p2Img.height / 1.75));
	p2 = LoadTextureFromImage(p2Img);

	goalSound = LoadSound("rpigoalsfx.mp3");

	// Goal box rectangles
	p2GoalBox = (Rectangle){screenWidth-15, screenHeight / 3 + screenHeight/27, 4, screenHeight/3 - screenHeight/15};
	p1GoalBox = (Rectangle){20,screenHeight / 3 + screenHeight/27, 4, screenHeight/3 - screenHeight/14};

	// Initialize Players
	
}
