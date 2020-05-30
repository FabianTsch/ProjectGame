#include "mobileObject.h"

/* Deklaration der Klasse MobileObject*/

MobileObject::MobileObject(Hero* o) : owner(o) {
	img = "mobiletiles/projectile.bmp";
	mapx = o->getx();
	mapy = o->gety();
	x = o->x;
	y = o->y;
    direction = o->getdirection();
}

int MobileObject::getx() { return mapx; }
int MobileObject::gety() { return mapy; }
std::string MobileObject::getimg() { return img; }
char MobileObject::getdirection() { return direction; }

bool MobileObject::move_left(std::vector<bool>& move) {
    mapx--;
    if (!move.at(mapy * 300 + mapx)){
        mapx++;
        return true;
    }
    return false;
}

bool MobileObject::move_right(std::vector<bool>& move) {
    mapx++;
    if (!move.at(mapy * 300 + mapx)){
        mapx--;
        return true;
    }
    return false;
}

bool MobileObject::move_up(std::vector<bool>& move) {
    mapy--;
            if (!move.at(mapy * 300 + mapx)){
        mapy++;
        return true;
    }
    return false;
}

bool MobileObject::move_down(std::vector<bool>& move) {
    mapy++;
    if (!move.at(mapy * 300 + mapx)){
        mapy--;
        return true;
    }
    return false;
}

/* Funktionen der Klasee Mobile Object*/
void draw_object(MobileObject& obj) {
    draw_image(obj.getimg(), obj.x * 16, obj.y * 16);
}
void check_shot(int spacekey, Hero& f1, std::vector<MobileObject*>& obj, int pause) {
    

    // Erzeugt neues Projektil
    static unsigned int p;
    if (is_pressed(spacekey) && p == 0) {
        p = pause;
        MobileObject* obj_ptr = new MobileObject(&f1);
        obj.push_back(obj_ptr);
    }
    else if (p != 0) {
        p--;
    }
}
void check_obj(MobileObject*& obj, std::vector<Monster*>& m, Hero& h, std::vector<bool>& move) {


    // Treffer abfrage 1
    bool col = false;
    bool hit = false;
    for (auto it = m.begin(); it < m.end(); ++it) {
        if ((*it)->getx() == obj->getx() && (*it)->gety() == obj->gety()) {
            hit = true;
            (*it)->hit();
        }
    }
    // Bewegung des Objekts
    switch (obj->getdirection()) {
    case 'l': col = obj->move_left(move); break;
    case 'r': col = obj->move_right(move); break;
    case 'd': col = obj->move_down(move); break;
    case 'u': col = obj->move_up(move); break;
    }
    // Treffer abfrage 2
    for (auto it = m.begin(); it < m.end(); ++it) {
        if ((*it)->getx() == obj->getx() && (*it)->gety() == obj->gety()) {
            hit = true;
            (*it)->hit();
        }
    }
    // Setzen der Draw Position für das Object
    int dx = obj->getx() - h.getx();
    int dy = obj->gety() - h.gety();
    obj->x = h.x + dx;
    obj->y = h.y + dy;
    
    if (col || hit) { 
        delete obj;
        obj = NULL;
    }
}

void clean_obj(std::vector<MobileObject*>& obj) {
    // Löschen leerer Objekte
    MobileObject* a = NULL;
    std::vector<MobileObject*> puffer = obj;
    obj.clear();
    for (auto it = puffer.begin(); it < puffer.end(); ++it) {
        if (*it != a)
            obj.push_back(*it);
    }
}