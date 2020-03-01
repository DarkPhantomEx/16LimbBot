#pragma once
#define NUM_OF_PARTS 16

struct vert {
	float x, y;
};

class Rect {
public:
	vert V[4];
	float colors[3];
	float rotation;

	static void drawBot();

	Rect();
};

void initBot();

void init();

void drawQuad(Rect);