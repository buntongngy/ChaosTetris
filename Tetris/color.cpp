#include "color.h"

const Color darkGrey = { 26, 31, 40, 255 };
const Color green = { 47, 200, 23, 255 };
const Color red = { 232, 18,18,255 };
const Color orange = { 226, 116 ,17, 255 };
const Color yellow = { 237, 234,4, 255 };
const Color purple = { 166, 0 , 247 ,255 };
const Color cyan = { 21, 204, 209, 255 };
const Color blue = { 13,64,216,255 };
const Color lightBlue = { 59, 85, 162, 255 };
const Color darkBlue = { 44,44,127,255 };
const Color pink = { 255, 192,203,255 };
const Color lightGray = { 179, 182, 183, 255 };
const Color lightOrange = { 255, 165, 0, 255 };
const Color darkGreen{ 20,90,50,255 };
const Color Brown{ 136,76,15,255 };
//const Color Lime{ 7,255,97,255 };
const Color Magenta{ 255,0,255,255 };
const Color Gold{ 255,215,0,255 };
const Color Cream{ 255,253,208, 255 };
const Color DarkRed{ 139,0,0, 255 };
const Color Aquamarine{127, 255,212,255};
const Color Violet{ 143,0,255,255 };


std::vector<Color> GetCellColor()
{
	return { darkGrey, green, red, orange, yellow, purple, cyan, blue,pink, lightGray, lightOrange, darkGreen, Brown, Magenta, Gold, Cream, DarkRed, Aquamarine, Violet};
}