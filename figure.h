#ifndef FIGURE_H
#define FIGURE_H

#include "mcigraph.hpp"
#include <vector>
#include <string>
#include <deque>

class Figure {
protected:
	int mapx, mapy;
	std::string img;
	char direction = 'd';
	unsigned short health = 100;

public:
	int x = 32;
	int y = 24;
	Figure(int mapx, int mapy, std::string str) : mapx(mapx), mapy(mapy), img(str) {}
	int getx();
	int gety();
	char getdirection();
	unsigned short gethealth();
	void sethealth(unsigned short);
	void hit();
	std::string getimg();
	void move_left(std::vector<bool>&);
	void move_right(std::vector<bool>&);
	void move_up(std::vector<bool>&);
	void move_down(std::vector<bool>&);
};

class Hero : public Figure {
private:
	std::string img_up;
	std::string img_down;
	std::string img_right;
	std::string img_left;

public:
	Hero();
	Hero(int, int, std::string, std::string, std::string, std::string);
	void move_left(std::vector<bool>&);
	void move_right(std::vector<bool>&);
	void move_up(std::vector<bool>&);
	void move_down(std::vector<bool>&);
};

class Monster : public Figure {
private:
	std::string img_up;
	std::string img_down;
	std::string img_right;
	std::string img_left;

public:
	Hero* Target;
	std::deque<int> pathx;
	std::deque<int> pathy;

	Monster(int, int, std::string, std::string, std::string, std::string, Hero*);
	void move_left(std::vector<bool>&);
	void move_right(std::vector<bool>&);
	void move_up(std::vector<bool>&);
	void move_down(std::vector<bool>&);
};

/* Funktionen Für Figure*/
void draw_figure( Figure& );
void check_movement(int leftkey, int rightkey, int upkey, int downkey, Hero& f1, std::vector<bool>& move);
void spawnPatter(std::vector<Monster*>&, Hero&, std::vector<int>&);
void check_monster( Monster*&, std::vector<bool>& );
void clean_monster(std::vector<Monster*>&);
#endif
