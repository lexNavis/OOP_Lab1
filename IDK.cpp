#include <iostream>
#include <Windows.h>
#include "IDK.h"

#define KEY_DOWN(vk) (GetAsyncKeyState(vk) & 0x8000)

using namespace std;

HWND hWnd = FindWindowA("ConsoleWindowClass", NULL);
HDC hdc = GetDC(hWnd);
int PEN_WIDTH = 1;

//defining Location methods

Location::Location(int new_x, int new_y) { 
	x = new_x; 
	y = new_y; 
}
Location::~Location() {}

int  Location::getX()			{ return x; }
int  Location::getY()			{ return y; }
void Location::setX(int new_x)	{ x = new_x; }
void Location::setY(int new_y)	{ y = new_y; }

//defining Point methods

Point::Point(int new_x, int new_y) : Location(new_x, new_y) { 
	visible = false; 
	color = new int[3];
	setColor(0, 0, 0); //мб уберу отсюда
}
Point::~Point() {}

void Point::setVisible(bool new_visible) { visible = new_visible; }
bool Point::isVisible() { return visible; }
void Point::setColor(int red, int green, int blue) {
	color[0] = red;
	color[1] = green;
	color[2] = blue;
}
void Point::moveTo(int new_x, int new_y) {
	Hide();
	setX(new_x);
	setY(new_y);
	Show();
}
void Point::Show() {
	visible = true;
	SetPixel(hdc, x, y, RGB(0, 0, 0));
}
void Point::Hide() {
	visible = false;
	SetPixel(hdc, x, y, RGB(255, 255, 255));
}

//defining Circle methods

Circle::Circle(int new_x, int new_y, int new_radius) : Point(new_x, new_y) { radius = new_radius; }
Circle::~Circle() {}

int  Circle::getRadius()				{ return radius; }
void Circle::setRadius(int new_radius)	{ radius = new_radius; }

void Circle::Show() {
	visible = true;

	HPEN hPen = CreatePen(PS_SOLID, PEN_WIDTH, RGB(0, 0, 0)); // Черный цвет
	SelectObject(hdc, hPen);
	Ellipse(hdc, x - radius, y - radius, x + radius, y + radius);
	DeleteObject(hPen);

	HBRUSH hBrush = CreateSolidBrush(RGB(color[0], color[1], color[2])); //для заливки
	SelectObject(hdc, hBrush);
	Ellipse(hdc, x - radius, y - radius, x + radius, y + radius);
	DeleteObject(hBrush);
}
void Circle::Hide() { 
	visible = false;

	HPEN hPen = CreatePen(PS_SOLID, PEN_WIDTH, RGB(255, 255, 255)); // Красный цвет
	SelectObject(hdc, hPen);
	Ellipse(hdc, x - radius, y - radius, x + radius, y + radius);
	DeleteObject(hPen);

	HBRUSH hBrush = CreateSolidBrush(RGB(255, 255, 255));
	SelectObject(hdc, hBrush);
	Ellipse(hdc, x - radius, y - radius, x + radius, y + radius);
	DeleteObject(hBrush);
}

//defining Ellipse methods

Ellipse_::Ellipse_(int new_x, int new_y, int new_focus1, int new_focus2) : Point(new_x, new_y) {
	focus1 = new_focus1;
	focus2 = new_focus2;
}
Ellipse_::~Ellipse_() {}

int  Ellipse_::getFocus1()					{ return focus1; }
int  Ellipse_::getFocus2()					{ return focus2; }
void Ellipse_::setFocus1(int new_focus1)	{ focus1 = new_focus1; }
void Ellipse_::setFocus2(int new_focus2)	{ focus2 = new_focus2; }

void Ellipse_::Show() {
	visible = true;

	HPEN hPen = CreatePen(PS_SOLID, PEN_WIDTH, RGB(0, 0, 0)); // Черный цвет
	SelectObject(hdc, hPen);
	Ellipse(hdc, x - focus1, y - focus2, x + focus1, y + focus2);
	DeleteObject(hPen);

	HBRUSH hBrush = CreateSolidBrush(RGB(color[0], color[1], color[2])); //для заливки
	SelectObject(hdc, hBrush);
	Ellipse(hdc, x - focus1, y - focus2, x + focus1, y + focus2);
	DeleteObject(hBrush);
}

void Ellipse_::Hide() {
	visible = false;

	HPEN hPen = CreatePen(PS_SOLID, PEN_WIDTH, RGB(255, 255, 255)); // Красный цвет
	SelectObject(hdc, hPen);
	Ellipse(hdc, x - focus1, y - focus2, x + focus1, y + focus2);
	DeleteObject(hPen);

	HBRUSH hBrush = CreateSolidBrush(RGB(255, 255, 255));
	SelectObject(hdc, hBrush);
	Ellipse(hdc, x - focus1, y - focus2, x + focus1, y + focus2);
	DeleteObject(hBrush);
}

void Ellipse_::TurnToCircle() {
	Hide();
	focus2 = focus1;
	Show();
}

//defining Triangle methods

Triangle::Triangle(int new_x, int new_y, int new_height, int new_base) : Point(new_x, new_y) {
	height = new_height;
	base = new_base;
	//points = new POINT[3];
	//points[0] = { x - height / 2, y - base / 2 };
	//points[1] = { x - height / 2, y + base / 2 };
	//points[2] = { x + height / 2, y };				//вершина лежит на ОХ
}
Triangle::~Triangle() {}

int  Triangle::getHeight()					{ return height; }
int  Triangle::getBase()					{ return base; }
void Triangle::setHeight(int new_height)	{ height = new_height; }
void Triangle::setBase(int new_base)		{ base = new_base; }

void Triangle::Show() {
	POINT* points = new POINT[3];
	points[0] = { x - height / 2, y - base / 2 };
	points[1] = { x - height / 2, y + base / 2 };
	points[2] = { x + height / 2, y };

	visible = true;

	HPEN hPen = CreatePen(PS_SOLID, PEN_WIDTH, RGB(0, 0, 0)); // Черный цвет
	SelectObject(hdc, hPen);
	Polygon(hdc, points, 3);
	DeleteObject(hPen);

	HBRUSH hBrush = CreateSolidBrush(RGB(color[0], color[1], color[2])); //для заливки
	SelectObject(hdc, hBrush);
	Polygon(hdc, points, 3);
	DeleteObject(hBrush);
}

void Triangle::Hide() {
	POINT* points = new POINT[3];
	points[0] = { x - height / 2, y - base / 2 };
	points[1] = { x - height / 2, y + base / 2 };
	points[2] = { x + height / 2, y };

	visible = false;

	HPEN hPen = CreatePen(PS_SOLID, PEN_WIDTH, RGB(255, 255, 255)); // Красный цвет
	SelectObject(hdc, hPen);
	Polygon(hdc, points, 3);
	DeleteObject(hPen);

	HBRUSH hBrush = CreateSolidBrush(RGB(255, 255, 255));
	SelectObject(hdc, hBrush);
	Polygon(hdc, points, 3);
	DeleteObject(hBrush);
}

//void Triangle::Expand(int deltarad) {
//	Hide();
//	points[0] = { x - height / 2, y - base / 2 - deltarad};
//	points[1] = { x - height / 2, y + base / 2 + deltarad };
//	Show();
//}
//
//void Triangle::Reduce(int deltarad) {
//	Hide();
//	points[0] = { x - height / 2, y - base / 2 + deltarad };
//	points[1] = { x - height / 2, y + base / 2 - deltarad };
//	Show();
//}

//defining Fish methods
Fish::Fish(int new_x, int new_y) {
	body = new Ellipse_(new_x, new_y, 100, 40);
	int f1 = body->getFocus1();
	int f2 = body->getFocus2();
	rear_fin = new Triangle(new_x - f1, new_y, 70, 100); //height = 70 (35=height/2), base = 100
	top_fin = new Triangle(new_x + 25, new_y - f2 - 15, 50, 60); //height = 50, base = 100
	bottom_fin = new Triangle(new_x - 25, new_y + f2 + 15, -50, -60); //height = 70, base = 100
	eye = new Circle(new_x + f1 / 2 + 30, new_y - 10, 7);
	mouth = new Triangle(new_x + f1 - 20, new_y + 10, -30, -8);

	//Setting color
	body		->	setColor(128, 128, 128);
	rear_fin	->	setColor(211, 211, 211);
	top_fin		->	setColor(211, 211, 211);
	bottom_fin	->	setColor(211, 211, 211);
	eye			->	setColor(0, 0, 0);
	mouth		->	setColor(255, 192, 203);
}

Fish::~Fish() {
	delete body;
	delete rear_fin;
	delete top_fin;
	delete bottom_fin;
	delete eye;
	delete mouth;
}

void Fish::Show() {
	rear_fin	->	Show();
	top_fin		->	Show();
	bottom_fin	->	Show();
	body		->	Show();
	eye			->	Show();
	mouth		->	Show();
}

void Fish::Hide() {
	body		->	Hide();
	rear_fin	->	Hide();
	top_fin		->	Hide();
	bottom_fin	->	Hide();
	eye			->	Hide();
	mouth		->	Hide();
}

void Fish::moveTo(int new_x, int new_y) {
	Hide();	//чтобы картинка нормально отображалась
	rear_fin	->	moveTo(new_x - body->getFocus1(), new_y);
	top_fin		->	moveTo(new_x + 25, new_y - body->getFocus2() - 15);
	bottom_fin	->	moveTo(new_x - 25, new_y + body->getFocus2() + 15);
	body		->	moveTo(new_x, new_y);
	eye			->	moveTo(new_x + (body->getFocus1()) / 2 + 30, new_y - 10);
	mouth		->	moveTo(new_x + body->getFocus1() - 20, new_y + 10);
	Show(); //убрать затирания
}
void Fish::drag(int step) {
	//за основу берем центр эллипса
	int pos_x = getBody()->getX();
	int pos_y = getBody()->getY();
	while (1) {
		if (KEY_DOWN(VK_ESCAPE)) break;
		else if (KEY_DOWN(VK_LEFT))  pos_x = (pos_x - step) % 1920; //деления можно и убрать, кратко не напишешь
		else if (KEY_DOWN(VK_RIGHT)) pos_x = (pos_x + step) % 1920;
		else if (KEY_DOWN(VK_UP))    pos_y = (pos_y - step) % 1080;
		else if (KEY_DOWN(VK_DOWN))  pos_y = (pos_y + step) % 1080; 
		moveTo(pos_x, pos_y);
		Sleep(50);//чтоб эпилепсии не было
	}
}

Ellipse_* Fish::getBody()	    { return body; }
Triangle* Fish::getRearFin()    { return rear_fin; }
Triangle* Fish::getTopFin()     { return top_fin; }
Triangle* Fish::getBottomFin()  { return bottom_fin; }
Circle*   Fish::getEye()		{ return eye; }
Triangle* Fish::getMouth()		{ return mouth; }

//Удалю, если не понадобится
void Fish::setBody(Ellipse_* new_body)				{ body = new_body; }
void Fish::setRearFin(Triangle* new_rear_fin)		{ rear_fin = new_rear_fin; }
void Fish::setTopFin(Triangle* new_top_fin)			{ top_fin = new_top_fin; }
void Fish::setBottomFin(Triangle* new_bottom_fin)	{ bottom_fin = new_bottom_fin; }
void Fish::setEye(Circle* new_eye)					{ eye = new_eye; }
void Fish::setMouth(Triangle* new_mouth)			{ mouth = new_mouth; }

//Defininition of PatrioticFish methods

PatrioticFish::PatrioticFish(int new_x, int new_y) : Fish(new_x, new_y) {
	beret = new Ellipse_(new_x, new_y - body->getFocus2() - 5, 50, 10);

	body		->	setColor(0, 100, 0);
	rear_fin	->	setColor(135, 206, 235);
	top_fin		->	setColor(135, 206, 235);
	bottom_fin	->	setColor(135, 206, 235);
	beret		->	setColor(255, 0, 0);
}
PatrioticFish::~PatrioticFish() {}

void PatrioticFish::Show() {
	rear_fin	->	Show();
	top_fin		->	Show();
	bottom_fin	->	Show();
	body		->	Show();
	eye			->	Show();
	mouth		->	Show();
	beret		->	Show();
}
void PatrioticFish::Hide() {
	rear_fin	->	Hide();
	top_fin		->	Hide();
	bottom_fin	->	Hide();
	body		->	Hide();
	eye			->	Hide();
	mouth		->	Hide();
	beret		->	Hide();
}
void PatrioticFish::moveTo(int new_x, int new_y) {
	Hide();	//чтобы картинка нормально отображалась
	rear_fin	->	moveTo(new_x - body->getFocus1(), new_y);
	top_fin		->	moveTo(new_x + 25, new_y - body->getFocus2() - 15);
	bottom_fin	->	moveTo(new_x - 25, new_y + body->getFocus2() + 15);
	body		->	moveTo(new_x, new_y);
	eye			->	moveTo(new_x + (body->getFocus1()) / 2 + 30, new_y - 10);
	mouth		->	moveTo(new_x + body->getFocus1() - 20, new_y + 10);
	beret		->	moveTo(new_x, new_y - body->getFocus2() - 5);
	Show(); //убрать затирания
}
void PatrioticFish::patrioticForm() {
	Hide();
	body		->	setColor(0, 0, 255);
	rear_fin	->	setColor(0, 0, 255);
	top_fin		->	setColor(255, 255, 255);
	bottom_fin	->	setColor(255, 0, 0);
	Show();
}
void PatrioticFish::baseForm() {
	Hide();
	body		->	setColor(0, 100, 0);
	rear_fin	->	setColor(135, 206, 235);
	top_fin		->	setColor(135, 206, 235);
	bottom_fin	->	setColor(135, 206, 235);
	Show();
}