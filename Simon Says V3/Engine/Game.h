/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.h																				  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "Squares.h"
#include <vector>

class Game
{
public:
	Game( class MainWindow& wnd );
	Game( const Game& ) = delete;
	Game& operator=( const Game& ) = delete;
	void Go();
private:
	void ComposeFrame();
	void UpdateModel();
	void SetColor(Square& Gold, int Red, int Green, int Blue);
	void RevertAllColorsToNormalSlowly(Square& Gold, int WhichSquare);
	void WhichColor(std::vector<int> ColorPattern);
	void InitiateEndOfWorld(int NuclearCode, int two);
	/********************************/
	/*  User Functions              */
	/********************************/
private:
	MainWindow& wnd;
	Graphics gfx;
	/********************************/
	/*  User Variables              */
	bool IsComputerTurn = true;
	bool IsColorAdded = false;
	bool GameOver = false;
	std::vector<int> ColorPattern;
	std::vector<int> UserInput;
	int TimeOutForSetColor = 0;
	int IndexForColorPattern= 0;
	const int AxisX = 400;
	const int AxisY = 300;
	Square RedTopLeft;
	Square BlueTopRight;
	Square YellowBottomLeft;
	Square GreenBottomRight;

	/********************************/
};