#pragma once

struct Vec
{
	float x, y;
};

struct RGB
{
	float r, g, b;
};

struct Rect
{
	float left, right, top, bottom;
};




inline bool collision(Rect a, Rect b)
{
	if (a.bottom < b.top)
		return false;

	if (a.top > b.bottom)
		return false;

	if (a.right < b.left)
		return false;

	if (a.left > b.right)
		return false;

	return true;
}

