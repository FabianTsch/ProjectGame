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

// Funktion
void cf::draw_monster_number(size_t size){
    // Read Numbers
    std::string str;
    std::stringstream ss;
    int posx = 59;
   // int posy = 0;

    ss << size;
    ss >> str;

    std::reverse(str.begin(),str.end());
    size = str.size();


    for(size_t i = 0; i < size; i++){
        char a = str.at(i);
        switch(a){
        case '0': draw_image("numbers/0.bmp",(posx-i*4)*16,0*16); break;
        case '1': draw_image("numbers/1.bmp",(posx-i*4)*16,0*16); break;
        case '2': draw_image("numbers/2.bmp",(posx-i*4)*16,0*16); break;
        case '3': draw_image("numbers/3.bmp",(posx-i*4)*16,0*16); break;
        case '4': draw_image("numbers/4.bmp",(posx-i*4)*16,0*16); break;
        case '5': draw_image("numbers/5.bmp",(posx-i*4)*16,0*16); break;
        case '6': draw_image("numbers/6.bmp",(posx-i*4)*16,0*16); break;
        case '7': draw_image("numbers/7.bmp",(posx-i*4)*16,0*16); break;
        case '8': draw_image("numbers/8.bmp",(posx-i*4)*16,0*16); break;
        case '9': draw_image("numbers/9.bmp",(posx-i*4)*16,0*16); break;
        }
    }
}
