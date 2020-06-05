#include "figure.h"


/* Deklarationen der Klasse Figure*/
int Figure::getx() { return mapx; }
int Figure::gety() { return mapy; }
char Figure::getdirection() { return direction; }
unsigned short Figure::gethealth() { return health; }
void Figure::sethealth(unsigned short h) { health = h; }
void Figure::hit() { if (health > 0) health -= 10; }

std::string Figure::getimg() { return img; }

void Figure::move_left(std::vector<bool>& move) {
    mapx--;
    if (!move.at(mapy * 300 + mapx))
        mapx++;
}

void Figure::move_right(std::vector<bool>& move) {
    mapx++;
    if (!move.at(mapy * 300 + mapx))
        mapx--;
}

void Figure::move_up(std::vector<bool>& move) {
    mapy--;
    if (!move.at(mapy * 300 + mapx))
        mapy++;
}

void Figure::move_down(std::vector<bool>& move) {
    mapy++;
    if (!move.at(mapy * 300 + mapx))
        mapy--;
}

/* Deklaration der Klasse Hero*/

Hero::Hero() : Figure(0, 0, "") {}

Hero::Hero(int mapx, int mapy, std::string up, std::string down, std::string right, std::string left)
    : Figure(mapx, mapy, down), img_up(up), img_down(down), img_right(right), img_left(left) {}

void Hero::move_left(std::vector<bool>& move) {
    img = img_left;
    direction = 'l';
    Figure::move_left(move);
}

void Hero::move_right(std::vector<bool>& move) {
    img = img_right;
    direction = 'r';
    Figure::move_right(move);
}

void Hero::move_up(std::vector<bool>& move) {
    img = img_up;
    direction = 'u';
    Figure::move_up(move);
}
void Hero::move_down(std::vector<bool>& move) {
    img = img_down;
    direction = 'd';
    Figure::move_down(move);
}

/* Deklaration der Klasse Monster*/
Monster::Monster(int mapx, int mapy, std::string up, std::string down, std::string right, std::string left, Hero* t)
    : Figure(mapx, mapy, down), img_up(up), img_down(down), img_right(right), img_left(left), Target(t) {
    x = 0;
    y = 0;
}

void Monster::move_left(std::vector<bool>& move) {
    img = img_left;
    Figure::move_left(move);
}

void Monster::move_right(std::vector<bool>& move) {
    img = img_right;
    Figure::move_right(move);
}

void Monster::move_up(std::vector<bool>& move) {
    img = img_up;
    Figure::move_up(move);
}
void Monster::move_down(std::vector<bool>& move) {
    img = img_down;
    Figure::move_down(move);
}


/* Funktionen für Figure */
void draw_figure(Figure& f) {
    draw_image(f.getimg(), f.x * 16, f.y * 16);

    // Healthbar
    int lenght = 20 * f.gethealth() / 100;
    draw_rect(f.x * 16 - 2, f.y * 16 - 5, 19, 4, false, 255, 0, 0);
    draw_rect(f.x * 16 - 2, f.y * 16 - 5, lenght, 4, false, 0, 255, 0);

}

void spawnPatter(std::vector<Monster*>& m, Hero& c, std::vector<int>& patter) {
    for (size_t i = 0; i < patter.size(); ++i) {
        if (patter.at(i) != -1) {
            int y = i / 300;
            int x = i % 300;
            m.push_back(new Monster(x, y, "monster/ghost_up.bmp",
                "monster/ghost_down.bmp", "monster/ghost_right.bmp", "monster/ghost_left.bmp", &c));
        }
    }
}

void check_movement(int leftkey, int rightkey, int upkey, int downkey, Hero& f1, std::vector<bool>& move) {
    if (is_pressed(leftkey))
        f1.move_left(move);
    if (is_pressed(rightkey))
        f1.move_right(move);
    if (is_pressed(upkey))
        f1.move_up(move);
    if (is_pressed(downkey))
        f1.move_down(move);
}

void clean_monster(std::vector<Monster*>& m) {
    // Löschen leerer Objekte
    Monster* a = NULL;
    std::vector<Monster*> puffer = m;
    m.clear();
    for (auto it = puffer.begin(); it < puffer.end(); ++it) {
        if (*it != a)
            m.push_back(*it);
    }

}

void check_monster(Monster*& m, std::vector<bool>& move) {
    // Setzen der Draw Position für das Monster
    int dx = m->getx() - m->Target->getx();
    int dy = m->gety() - m->Target->gety();
    m->x = m->Target->x + dx;
    m->y = m->Target->y + dy;

    // Bewegung des Monsters
    if ((dy < 15 && dy > -15 && dx < 15 && dx > -15) || m->pathx.size() != 0 || m->gethealth() < 100) {
        if (m->pathx.size() == 0) { // Erstes einlesen der Target pos
            m->pathx.push_back(m->Target->getx());
            m->pathy.push_back(m->Target->gety());
        }

        if (m->pathx.back() != m->Target->getx() || m->pathy.back() != m->Target->gety()) {
            m->pathx.push_back(m->Target->getx());
            m->pathy.push_back(m->Target->gety());
        }

        // Differenz zwischen erster Pfad pos und aktuelle pos
        int dpx = m->pathx.front() - m->getx();
        int dpy = m->pathy.front() - m->gety();

        // Für die Beschleunigung von Monstern (kann mit entschleunigung getauscht werden)
        /*if (dpx == 0 && dpy == 0) {
            m->pathx.pop_front();
            m->pathy.pop_front();
            if (m->pathy.size() && m->pathx.size()) {
                dpy = m->pathy.front() - m->gety();
                dpx = m->pathx.front() - m->getx();
            }
        }*/
        if (dpx > 0)
            m->move_right(move);
        else if (dpx < 0)
            m->move_left(move);
        if (dpy > 0)
            m->move_down(move);
        else if (dpy < 0)
            m->move_up(move);
        // Für die Entschleunigung des Monsters
        if (dpx == 0 && dpy == 0) {
            m->pathx.pop_front();
            m->pathy.pop_front();
        }
    }

    // Angriff
    if (m->getx() == m->Target->getx() && m->gety() == m->Target->gety()) {
        m->Target->hit();
    }

    // Löschen des Monsters falls Tod
    if (!(m->gethealth())) {
        delete m;
        m = NULL;
    }

}
