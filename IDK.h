#pragma once

//Basic location class
class Location {
	protected:
		int x, y;

	public:
		Location(int new_x, int new_y);
		~Location();
		int  getX();
		void setX(int new_x);
		int  getY();
		void setY(int new_y);
};

class Point : public Location {
	protected:
		bool visible;
		int* color;
	public:
		Point(int new_x, int new_y);
		~Point();
		void setVisible(bool new_visible);
		bool isVisible();
		void setColor(int red, int green, int blue);
		void moveTo(int new_x, int new_y);
		virtual void Show();
		virtual void Hide();
};

class Circle : public Point {
protected:
	int radius;
public:
	Circle(int new_x, int new_y, int new_radius);
	~Circle();
	int  getRadius();
	void setRadius(int new_radius);
	virtual void Show();
	virtual void Hide();
	//void Expand(int deltarad);
	//void Reduce(int deltarad);
};

class Ellipse_ : public Point {
protected:
	int focus1; //focus OX
	int focus2; //focus OY
public:
	Ellipse_(int new_x, int new_y, int new_focus1,  int new_focus2);
	~Ellipse_();
	int  getFocus1();
	int  getFocus2();
	void setFocus1(int new_focus1);
	void setFocus2(int new_focus2);
	virtual void Show();
	virtual void Hide();
	void TurnToCircle();
	//void TurnBack();
};

class Triangle : public Point { //рассматриваются равнобедренные треугольнкии
protected:
	int height;  //высота треугольника
	int base;	 //длина основания
public:
	Triangle(int new_x, int new_y, int new_height, int new_base);
	~Triangle();
	int  getHeight();
	int  getBase();
	void setHeight(int new_height);
	void setBase(int new_base);
	virtual void Show();
	virtual void Hide();
	/*void Expand(int deltarad);
	void Reduce(int deltarad);*/
};

//common fish
class Fish {
protected:
	Ellipse_* body;
	Triangle* rear_fin; //задний плавник
	Triangle* top_fin;
	Triangle* bottom_fin;
	Circle*   eye;
	Triangle* mouth;
public:
	Fish(int new_x, int new_y);
	~Fish();
	Ellipse_* getBody();
	Triangle* getRearFin(); // задний плавник
	Triangle* getTopFin();
	Triangle* getBottomFin();
	Circle*   getEye();
	Triangle* getMouth();

	//Удалю, если не понадобится
	void setBody(Ellipse_* new_body);
	void setRearFin(Triangle* rear_fin);
	void setTopFin(Triangle* top_fin);
	void setBottomFin(Triangle* bottom_fin);
	void setEye(Circle* eye);
	void setMouth(Triangle* mouth);

	virtual void Show();
	virtual void Hide();
	virtual void moveTo(int new_x, int new_y); //move different parts = virtual
	void drag(int step);
};

class PatrioticFish : public Fish {
protected:
	Ellipse_* beret;
public:
	PatrioticFish(int new_x, int new_y);
	~PatrioticFish();
	virtual void Show();
	virtual void Hide();
	virtual void moveTo(int new_x, int new_y);
	void patrioticForm();
	void baseForm();
};