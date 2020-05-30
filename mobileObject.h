#ifndef MOBILEOBJECT_H
#define MOBILEOBJECT_H

#include "mcigraph.hpp"
#include "figure.h"
#include <vector>
#include <string>
#include <algorithm>

class MobileObject {
protected:
	int mapx, mapy;
	std::string img;
	char direction;
public:
	int x;
	int y;
	Hero* owner;
	MobileObject(Hero*);
	int getx();
	int gety();
	char getdirection();
	std::string getimg();
	bool move_left(std::vector<bool>&);
	bool move_right(std::vector<bool>&);
	bool move_up(std::vector<bool>&);
	bool move_down(std::vector<bool>&);

};

/* Fuktionen für Mobile Objekt*/
void draw_object(MobileObject&);
void check_shot(int, Hero&, std::vector<MobileObject*>&, int);
void check_obj(MobileObject*&, std::vector<Monster*>&,Hero&, std::vector<bool>&);
void clean_obj(std::vector<MobileObject*>&);

#endif // MOBILEOBJECT_H
