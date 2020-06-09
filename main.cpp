#include "mcigraph.hpp"
#include "init.h"
#include "figure.h"
#include "mobileObject.h"
#include "map.h"
#include <time.h>
#include <algorithm>

int main(int argc, char* argv[]) {

    // Laden der Map Layer
    std::vector<int> Background = init::loadm("map_Background.csv", 90000); // Laden des Backgroundlayers
    std::vector<int> Path = init::loadm("map_path.csv", 90000);
    std::vector<int> Layer1 = init::loadm("map_Layer1.csv");
    std::vector<int> Objects = init::loadm("map_Objects.csv");
    std::vector<int> spawnpatter = init::loadm("map_monster.csv");


    // Kollisions initialisierung
    std::vector<bool> move(300*300);
    for (std::vector<bool>::iterator it = move.begin(); it < move.end(); ++it) { *it = true; } // Setz alle werte der move variable auf true
    noMove(move, Objects);
    noMove(move, Layer1);

    while (running()) {
        // Spieler und Klassen Initialisierung
        Hero c(150, 150, "character/up.bmp", "character/down.bmp", "character/right.bmp", "character/left.bmp");
        std::vector<Monster*> monster;
        spawnPatter(monster, c, spawnpatter);
        std::vector<MobileObject*> projectil;

            while (c.gethealth() > 0 && running()) {
                set_delay(33);

                // Zeichnen der Map
                draw_map(Background,c.getx(), c.gety());
                draw_map(Path, c.getx(), c.gety());
                draw_map(Layer1, c.getx(), c.gety());
                draw_map(Objects, c.getx(), c.gety());

                // Routinen Für die Klassen
                check_shot(KEY_SPACE, c, projectil, 4); // Feuerrate festlegen
                for (auto it = projectil.begin(); it < projectil.end(); ++it) {check_obj(*it, monster, c, move);}
                for (auto it = monster.begin(); it < monster.end(); ++it) { check_monster(*it, move); };
                check_movement(KEY_LEFT, KEY_RIGHT, KEY_UP, KEY_DOWN, c, move);
                clean_obj(projectil);
                clean_monster(monster);

                // Zeichnen der Klassen
                draw_figure(c);
                for (auto it = monster.begin(); it < monster.end(); ++it) { draw_figure(**it); };
                for (auto it = projectil.begin(); it < projectil.end(); ++it) { draw_object(**it); }
                present();
            }
        // Aufäumen der restlichen Objekte
        for_each(monster.begin(), monster.end(), []( Monster* m ){delete m;});
        for_each(projectil.begin(), projectil.end(), [](MobileObject* mo){delete mo;});
    }
    return 0;
}
