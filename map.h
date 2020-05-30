#ifndef MAP_H
#define Map_H

#include <vector>
#include <string>
#include <algorithm>
#include "mcigraph.hpp"

/* Funktionen für Map*/
std::vector<bool>& noMove(std::vector<bool>&, const std::vector<int>&);
void draw_map(std::vector<int>& map, int posx, int posy);

#endif // MAP_H
