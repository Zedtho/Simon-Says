/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
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
#include "MainWindow.h"
#include "Game.h"
#include <ctime>

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	RedTopLeft(255, 0, 0, -150, -5, -5, -150),
	BlueTopRight(0, 0, 255, +5, +150, -5, -150),
	YellowBottomLeft(255, 255, 0, -150, -5, +150, +5),
	GreenBottomRight(0, 255, 0, +5, +150, +150, +5)
{
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	if(GameOver)
	{
		if (wnd.kbd.KeyIsPressed(VK_RETURN))
		{
			GameOver = false;
			TimeOutForSetColor = 40;
			SetColor(RedTopLeft, 255, 0, 0);
			SetColor(BlueTopRight, 0, 0, 255);
			SetColor(YellowBottomLeft, 255, 255, 0);
			SetColor(GreenBottomRight, 0, 255, 0);
		}
	}
	else
	{
		if (IsComputerTurn)
		{
			if (IsColorAdded == false)
			{
				srand(time(NULL));
				ColorPattern.push_back(rand() % 4 + 1);
				IsColorAdded = true;
			}
			if (TimeOutForSetColor == 0)
			{

				WhichColor(ColorPattern);
				TimeOutForSetColor = 25;
				IndexForColorPattern++;
				if (IndexForColorPattern == ColorPattern.size())
				{
					IsComputerTurn = false;
					IsColorAdded = false;
					IndexForColorPattern = 0;
					TimeOutForSetColor = 30;
				}
			}
			RevertAllColorsToNormalSlowly(RedTopLeft, 1);
			RevertAllColorsToNormalSlowly(BlueTopRight, 2);
			RevertAllColorsToNormalSlowly(YellowBottomLeft, 3);
			RevertAllColorsToNormalSlowly(GreenBottomRight, 4);
			if (TimeOutForSetColor != 0) { TimeOutForSetColor--; }
		}
		else
		{
			if (UserInput.size() != ColorPattern.size())
			{
				
				if (wnd.mouse.GetPosX() < AxisX && wnd.mouse.GetPosX() > AxisX + RedTopLeft.HorizontalLeft && wnd.mouse.GetPosY() < AxisY && wnd.mouse.GetPosY() > AxisY + RedTopLeft.VerticalTop && wnd.mouse.LeftIsPressed() && TimeOutForSetColor == 0)
				{
					UserInput.push_back(1);
					SetColor(RedTopLeft, 255, 150, 150);
					TimeOutForSetColor = 15;
					if (UserInput[UserInput.size() - 1] != ColorPattern[UserInput.size() - 1])
					{
						GameOver = true;
						ColorPattern.clear();
					}
				}
				if (wnd.mouse.GetPosX() > AxisX && wnd.mouse.GetPosX() < AxisX + BlueTopRight.HorizontalRight && wnd.mouse.GetPosY() < AxisY && wnd.mouse.GetPosY() > AxisY + BlueTopRight.VerticalTop && wnd.mouse.LeftIsPressed() && TimeOutForSetColor == 0 )
				{
					UserInput.push_back(2);
					SetColor(BlueTopRight, 150, 150, 255);
					TimeOutForSetColor = 15;
					if (UserInput[UserInput.size() - 1] != ColorPattern[UserInput.size() - 1])
					{
						GameOver = true;
						ColorPattern.clear();
					}
				}
				if (wnd.mouse.GetPosX() > YellowBottomLeft.HorizontalLeft + AxisX && wnd.mouse.GetPosX() < AxisX && wnd.mouse.GetPosY() > AxisY && wnd.mouse.GetPosY() < AxisY + YellowBottomLeft.VerticalBottom && wnd.mouse.LeftIsPressed() && TimeOutForSetColor == 0)
				{
					UserInput.push_back(3);
					SetColor(YellowBottomLeft, 255, 255, 150);
					TimeOutForSetColor = 15;
					if (UserInput[UserInput.size() - 1] != ColorPattern[UserInput.size() - 1])
					{
						GameOver = true;
						ColorPattern.clear();
					}
				}
				if (wnd.mouse.GetPosX() > AxisX && wnd.mouse.GetPosX() < AxisX + GreenBottomRight.HorizontalRight && wnd.mouse.GetPosY() > AxisY && wnd.mouse.GetPosY() < AxisY + GreenBottomRight.VerticalBottom && wnd.mouse.LeftIsPressed() && TimeOutForSetColor == 0)
				{
					UserInput.push_back(4);
					SetColor(GreenBottomRight, 150, 255, 150);
					TimeOutForSetColor = 15;
					if (UserInput[UserInput.size() - 1] != ColorPattern[UserInput.size() - 1])
					{
						GameOver = true;
						ColorPattern.clear();
					}
				}
				
				if (TimeOutForSetColor != 0) { TimeOutForSetColor--; }
				
				RevertAllColorsToNormalSlowly(RedTopLeft, 1);
				RevertAllColorsToNormalSlowly(BlueTopRight, 2);
				RevertAllColorsToNormalSlowly(YellowBottomLeft, 3);
				RevertAllColorsToNormalSlowly(GreenBottomRight, 4);
			}
			else
			{
				IsComputerTurn = true;
				UserInput.clear();
				TimeOutForSetColor = 60;

			}
			
		}
	}
}

void Game::ComposeFrame()
{
	if (GameOver)
	{
		//Try again next time
	}
	else {
		RedTopLeft.Draw(AxisX, AxisY, gfx);
		BlueTopRight.Draw(AxisX, AxisY, gfx);
		YellowBottomLeft.Draw(AxisX, AxisY, gfx);
		GreenBottomRight.Draw(AxisX, AxisY, gfx);
	}
}

void Game::SetColor(Square& Gold, int GivenRedV, int GivenGreenV, int GivenBlueV)
{
	Gold.RedV = GivenRedV;
	Gold.GreenV = GivenGreenV;
	Gold.BlueV = GivenBlueV;
}

void Game::RevertAllColorsToNormalSlowly(Square& Gold, int WhichSquare)
{
	switch (WhichSquare)
	{
	case 1:
		if (Gold.GreenV > 5)
		{
			Gold.GreenV--;
			Gold.GreenV--;
			Gold.GreenV--;
			Gold.GreenV--;
			Gold.GreenV--;
		}
		if (Gold.BlueV  > 5) {
			Gold.BlueV--;
			Gold.BlueV--;
			Gold.BlueV--;
			Gold.BlueV--;
			Gold.BlueV--;
		}
		break;
	case 2:
		if (Gold.RedV   > 5) {
			Gold.RedV--;
			Gold.RedV--;
			Gold.RedV--;
			Gold.RedV--;
			Gold.RedV--;


		}
		if (Gold.GreenV > 5)
		{
			Gold.GreenV--;
			Gold.GreenV--;
			Gold.GreenV--;
			Gold.GreenV--;
			Gold.GreenV--;
		}
		break;
	case 3:
		if (Gold.BlueV  > 5) {
			Gold.BlueV--;
			Gold.BlueV--;
			Gold.BlueV--;
			Gold.BlueV--;
			Gold.BlueV--;
		}
		break;
	case 4:
		if (Gold.RedV   > 5) {
			Gold.RedV--;
			Gold.RedV--;
			Gold.RedV--;
			Gold.RedV--;
			Gold.RedV--;


		}
		if (Gold.BlueV  > 5) {
			Gold.BlueV--;
			Gold.BlueV--;
			Gold.BlueV--;
			Gold.BlueV--;
			Gold.BlueV--;
		}
		break;
	}
}

void Game::WhichColor(std::vector<int> ColorPattern)
{
	switch (ColorPattern[IndexForColorPattern])
	{
		case 1:
			SetColor(RedTopLeft, 255, 150, 150);
			break;
		case 2:
			SetColor(BlueTopRight, 150, 150, 255);
			break;
		case 3:
			SetColor(YellowBottomLeft, 255, 255, 150);
			break;
		case 4:
			SetColor(GreenBottomRight, 150, 255, 150);
			break;

	}		
}

