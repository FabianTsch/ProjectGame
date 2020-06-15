#include "cf.hpp"

// Konstructor
cf::WGA::WGA(Hero* c, std::vector<Monster*>* m) : player(c), monster(m){}

// Memberfunction
void cf::WGA::eofg(){
    while(!is_pressed(KEY_SPACE) && (running()) ){
        if(status == 'l'){
            draw_image("img/gameover.bmp",0,0);
        }
        else if(status == 'w'){
            draw_image("img/win.bmp",0,0);
        }
            present();
    }
    status = 'r';
}

bool cf::WGA::check_running(){
    if(running() && monster->size()>0 && player->gethealth())
        return true;
    else if(running() && monster->size()>0){
        status = 'l';
        return false;
    }
    else if(running() && player->gethealth()){
        status = 'w';
        return false;
    }
    else return false;
}
