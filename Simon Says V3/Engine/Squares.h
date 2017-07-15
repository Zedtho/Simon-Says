#pragma once

class Square
{
public:
	int RedV;
	int GreenV;
	int BlueV;
    int HorizontalLeft;
    int HorizontalRight;
    int VerticalBottom;
    int VerticalTop;	
	Square(int GivenRedV, int GivenGreenV, int GivenBlueV, int GivenHorizontalLeft, int GivenHorizontalRight, int GivenVerticalBottom, int GivenVerticalTop)
	{
		RedV = GivenRedV;
		GreenV = GivenGreenV;
		BlueV = GivenBlueV;
		HorizontalLeft = GivenHorizontalLeft;
		HorizontalRight = GivenHorizontalRight;
		VerticalBottom = GivenVerticalBottom;
		VerticalTop = GivenVerticalTop;
	}
	void Draw(int AxisX, int AxisY, Graphics& gfx)
	{
		for (int TempX = HorizontalLeft; TempX < HorizontalRight; TempX++)
		{
			for (int TempY = VerticalTop; TempY < VerticalBottom; TempY++)
			{
				gfx.PutPixel(AxisX + TempX, AxisY + TempY, RedV, GreenV, BlueV);
			}
		}
	};
	bool IsSelected(int AxisX, int AxisY, MainWindow& wnd)
	{
		int AbsoluteXLeft = AxisX + HorizontalLeft;
		int AbsoluteXRight = AxisX + HorizontalRight;
		int AbsoluteYTop = AxisY + VerticalTop;
		int AbsoluteYBottom = AxisY + VerticalBottom;
		
		return (AbsoluteXLeft < wnd.mouse.GetPosX() && wnd.mouse.GetPosX() < AbsoluteXRight && AbsoluteYTop < wnd.mouse.GetPosY() && wnd.mouse.GetPosY() < AbsoluteYBottom && wnd.mouse.LeftIsPressed());

	}
};

