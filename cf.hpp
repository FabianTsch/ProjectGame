#ifndef CF_H
#define CF_H
#include "mcigraph.hpp"
#include "init.h"
#include "figure.h"
#include "mobileObject.h"
#include "map.h"
#include <time.h>
#include <algorithm>
#include <string>
#include <vector>
#include <string>
#include <sstream>

namespace cf{
    class WGA{
    private:
        Hero* player;
        std::vector<Monster*>* monster;
        char status = 'r';
    public:
        WGA(Hero*, std::vector<Monster*>*);
        bool check_running();
        void eofg();
    };

    void draw_monster_number(size_t size);
}//namespace cf


#endif
