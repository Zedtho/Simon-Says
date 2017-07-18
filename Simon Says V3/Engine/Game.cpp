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
	GreenBottomRight(0, 255, 0, +5, +150, +150, +5),
	RedButtonSound(L"Square One.wav"),
	BlueButtonSound(L"Square Two.wav"),
	YellowButtonSound(L"Square Three.wav"),
	GreenButtonSound(L"Square Four.wav")

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
			if (AfterGameOver)
			{
				scrbrd.Score = 0;
				scrbrd.UpdateScoreboard();
				AfterGameOver = false;
			}
			if (IsColorAdded == false)
			{
				srand(int(time(NULL)));
				ColorPattern.push_back(rand() % 4 + 1);
				IsColorAdded = true;
			}
			if (TimeOutForSetColor == 0)
			{

				WhichColor(ColorPattern);
				TimeOutForSetColor = 15;
				IndexForColorPattern++;
				if (IndexForColorPattern == ColorPattern.size())
				{
					IsComputerTurn = false;
					IsColorAdded = false;
					IndexForColorPattern = 0;
					TimeOutForSetColor = 7;
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
				
				if (RedTopLeft.IsSelected(AxisX, AxisY, wnd)&& TimeOutForSetColor == 0)
				{
					UserInput.push_back(1);
					SetColor(RedTopLeft, 255, 150, 150);
					TimeOutForSetColor = 5;
					RedButtonSound.Play();
					if (UserInput[UserInput.size() - 1] != ColorPattern[UserInput.size() - 1])
					{
						GameOver = true;
						ColorPattern.clear();
						UserInput.clear();
						AfterGameOver = true;
					}
				}
				if (BlueTopRight.IsSelected(AxisX, AxisY, wnd) && TimeOutForSetColor == 0 )				{
					UserInput.push_back(2);
					SetColor(BlueTopRight, 150, 150, 255);
					TimeOutForSetColor = 5;
					BlueButtonSound.Play();
					if (UserInput[UserInput.size() - 1] != ColorPattern[UserInput.size() - 1])
					{
						GameOver = true;
						ColorPattern.clear();
						UserInput.clear();
						AfterGameOver = true;
					}
				}
				if (YellowBottomLeft.IsSelected(AxisX, AxisY, wnd) && TimeOutForSetColor == 0)
				{
					UserInput.push_back(3);
					SetColor(YellowBottomLeft, 255, 255, 255);
					TimeOutForSetColor = 5;
					YellowButtonSound.Play();
					if (UserInput[UserInput.size() - 1] != ColorPattern[UserInput.size() - 1])
					{
						GameOver = true;
						ColorPattern.clear();
						UserInput.clear();
						AfterGameOver = true;
					}
				}
				if (GreenBottomRight.IsSelected(AxisX, AxisY, wnd) && TimeOutForSetColor == 0)
				{
					UserInput.push_back(4);
					SetColor(GreenBottomRight, 150, 255, 150);
					TimeOutForSetColor = 5;
					GreenButtonSound.Play();
					if (UserInput[UserInput.size() - 1] != ColorPattern[UserInput.size() - 1])
					{
						GameOver = true;
						ColorPattern.clear();
						UserInput.clear();
						AfterGameOver = true;
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
				TimeOutForSetColor = 25;
				scrbrd.Score = ColorPattern.size();
				scrbrd.UpdateScoreboard();

			}
			
		}
	}
}

void Game::ComposeFrame()
{
	if (GameOver)
	{
		brd.DrawTitleScreen(gfx);
		
	}
	else
	{
		if (IsComputerTurn) {
			brd.DrawWatch(gfx);
			
		}
		else
		{
			brd.DrawRepeat(gfx);
			
		}
		RedTopLeft.Draw(AxisX, AxisY, gfx);
		BlueTopRight.Draw(AxisX, AxisY, gfx);
		YellowBottomLeft.Draw(AxisX, AxisY, gfx);
		GreenBottomRight.Draw(AxisX, AxisY, gfx);
	}
	scrbrd.Draw(Graphics::ScreenWidth - 60 , Graphics::ScreenHeight - 100, gfx);
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
		if (Gold.GreenV > 10)
		{
			Gold.GreenV--;
			Gold.GreenV--;
			Gold.GreenV--;
			Gold.GreenV--;
			Gold.GreenV--;
			Gold.GreenV--;
			Gold.GreenV--;
			Gold.GreenV--;
			Gold.GreenV--;
			Gold.GreenV--;
		}
		if (Gold.BlueV  > 10) {
			Gold.BlueV--;
			Gold.BlueV--;
			Gold.BlueV--;
			Gold.BlueV--;
			Gold.BlueV--;
			Gold.BlueV--;
			Gold.BlueV--;
			Gold.BlueV--;
			Gold.BlueV--;
			Gold.BlueV--;
		}
		break;
	case 2:
		if (Gold.RedV   > 10) {
			Gold.RedV--;
			Gold.RedV--;
			Gold.RedV--;
			Gold.RedV--;
			Gold.RedV--;
			Gold.RedV--;
			Gold.RedV--;
			Gold.RedV--;
			Gold.RedV--;
			Gold.RedV--;


		}
		if (Gold.GreenV > 10)
		{
			Gold.GreenV--;
			Gold.GreenV--;
			Gold.GreenV--;
			Gold.GreenV--;
			Gold.GreenV--;
			Gold.GreenV--;
			Gold.GreenV--;
			Gold.GreenV--;
			Gold.GreenV--;
			Gold.GreenV--;
		}
		break;
	case 3:
		if (Gold.BlueV  > 17) {
			Gold.BlueV--;
			Gold.BlueV--;
			Gold.BlueV--;
			Gold.BlueV--;
			Gold.BlueV--;
			Gold.BlueV--;
			Gold.BlueV--;
			Gold.BlueV--;
			Gold.BlueV--;
			Gold.BlueV--;
			Gold.BlueV--;
			Gold.BlueV--;
			Gold.BlueV--;
			Gold.BlueV--;
			Gold.BlueV--;
			Gold.BlueV--;
			Gold.BlueV--;
		}
		break;
	case 4:
		if (Gold.RedV   > 10) {
			Gold.RedV--;
			Gold.RedV--;
			Gold.RedV--;
			Gold.RedV--;
			Gold.RedV--;
			Gold.RedV--;
			Gold.RedV--;
			Gold.RedV--;
			Gold.RedV--;
			Gold.RedV--;

		}
		if (Gold.BlueV  > 10) {
			Gold.BlueV--;
			Gold.BlueV--;
			Gold.BlueV--;
			Gold.BlueV--;
			Gold.BlueV--;
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
			RedButtonSound.Play();
			break;
		case 2:
			SetColor(BlueTopRight, 150, 150, 255);
			BlueButtonSound.Play();
			break;
		case 3:
			SetColor(YellowBottomLeft, 255, 255, 255);
			YellowButtonSound.Play();
			break;
		case 4:
			SetColor(GreenBottomRight, 150, 255, 150);
			GreenButtonSound.Play();
			break;

	}		
}

