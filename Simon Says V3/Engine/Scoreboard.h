#pragma once
#include "Graphics.h"

class Scoreboard
{
public:
	int Score = 0;
	void Draw(int x, int y, Graphics& gfx);
	void Draw0(int x, int y, Graphics& gfx);
	void Draw1(int x, int y, Graphics& gfx);
	void Draw2(int x, int y, Graphics& gfx);
	void Draw3(int x, int y, Graphics& gfx);
	void Draw4(int x, int y, Graphics& gfx);
	void Draw5(int x, int y, Graphics& gfx);
	void Draw6(int x, int y, Graphics& gfx);
	void Draw7(int x, int y, Graphics& gfx);
	void Draw8(int x, int y, Graphics& gfx);
	void Draw9(int x, int y, Graphics& gfx);
	int OnesDigit = 0;
	int TensDigit = 0;
	void UpdateScoreboard();
	Scoreboard() = default;
	

};