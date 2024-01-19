
#include "stdafx.h"
#include "render.h"
#include "sys.h"
#include "core.h"
#include "font.h"
#include "vector2d.h"
#include "ball.h"

extern GLuint texbkg;
extern GLuint texsmallball;
extern Ball balls[NUM_BALLS];

extern double time_fps;
extern double totalTime;
extern double totalFrameTime;

//SharedData sharedData;

const char* FloatToString(float value) {
	static char buffer[32]; // Adjust the buffer size based on your needs
	snprintf(buffer, sizeof(buffer), "%f", value);
	return buffer;
}

void RenderInitialization()
{
	FONT_Init();	// Characters and symbols initialization to draw on screen.

	// Load textures
	texbkg = CORE_LoadPNG("data/circle-bkg-128.png", true);
	texsmallball = CORE_LoadPNG("data/tyrian_ball.png", false);


	// Set up rendering.
	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT); // Sets up clipping.
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);	// Specifies clear values for the color buffers.
	glMatrixMode(GL_PROJECTION);	// Specifies projection matrix is the current matrix.
	glLoadIdentity();	// Replaces the current matrix with the identity matrix.
	glOrtho(0.0, SCR_WIDTH, 0.0, SCR_HEIGHT, 0.0, 1.0);	// Multiplies the current matrix by an orthographic matrix.
	glEnable(GL_TEXTURE_2D);	// Enabling two-dimensional texturing.
	glEnable(GL_BLEND);	// Blend the incoming RGBA color values with the values in the color buffers.
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	// Blend func. for alpha color.
}

void Render()
{
	glClear(GL_COLOR_BUFFER_BIT);	// Clear color buffer to preset values.

	// Render background
	for (int i = 0; i <= SCR_WIDTH / 128; i++) {
		for (int j = 0; j <= SCR_HEIGHT / 128; j++) {
			CORE_RenderCenteredSprite(vec2(i * 128.f + 64.f, j * 128.f + 64.f), vec2(128.f, 128.f), texbkg);
		}
	}

	// Render balls
	for (int i = 0; i < NUM_BALLS; i++) {
		CORE_RenderCenteredSprite(balls[i].pos, vec2(balls[i].radius * 2.f, balls[i].radius * 2.f), balls[i].gfx);
	}

	// Text
	FONT_DrawString(vec2(SCR_WIDTH / 2 - 6 * 16, 16), "HELLO WORLD");

	// Time Passed
	char currentTimeString[50] = { 0 };
	snprintf(currentTimeString, 50, "TIME:%f", totalTime);
	FONT_DrawString(vec2(SCR_WIDTH - 128, SCR_HEIGHT - 16), currentTimeString);

	char fpsString[50] = { 0 };
	snprintf(fpsString, 50, "FPS:%f", 1 / time_fps);
	FONT_DrawString(vec2(0, SCR_HEIGHT - 16), fpsString);

	char tickString[50] = { 0 };
	snprintf(tickString, 50, "TICK:%f", totalFrameTime);
	FONT_DrawString(vec2(SCR_WIDTH - 128, SCR_HEIGHT - 40), tickString);


		// Exchanges the front and back buffers
	SYS_Show();

}