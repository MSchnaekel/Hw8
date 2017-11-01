//**********************************************************************************	
//	
//	Name: Mackenzie Schnaekel
//
//	Date: April 10, 2017
//
//	Description: This is the implementation for the space class 
//
//**********************************************************************************

#include<iostream>
#include"space.h"
using namespace std;

space::space()
{
	empty = true;
	magenta = false;
	green = false;
	king = false;
}
void space::make_empty()
{
	magenta = false;
	green = false;	
	empty = true;
	king = false;
}

bool space::is_empty()const
{
	return empty;
}

void space::make_magenta()
{
	magenta = true;
	green = false;
	empty = false;
	king = false;
}
bool space::is_magenta()const
{
	return magenta;
}

void space::make_green()
{
	green = true;
	magenta = false;	
	empty = false;
	king = false;
}

bool space::is_green()const
{
	return green;
}

void space::green_king_me()
{
	king = true;
	green = true;
	magenta = false;
	empty = false;
}
void space::magenta_king_me()
{
	king = true;
	magenta = true;	
	green = false;
	empty = false;
}
bool space::is_king()const
{
	return king;
}

