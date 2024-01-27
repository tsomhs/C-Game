#pragma once
#include <vector>
#include <iostream>
char** init(int&,int&); // dynamically allocates the array and asks for coordinates
                        //return the array(gameboard)
void generate_map(int,int,char**);

void print_array(char**, int, int,int);

bool move_check(char**, int, int, char);

void magic_pot(char**, int, int);

//hyperclass
class creature {
protected:
     int power, pots, hp, def, x, y;
public:
    creature(int x1 = 0, int y1 = 0, int hp1 = 0, int power1 = 0, int def1 = 0, int pots1 = 0) : x(x1), y(y1), hp(hp1), power(power1), def(def1), pots(pots1) {};
    virtual void move(int*, int*, int) { "."; };
    void print_pots();
    int get_pots();
    void set_pots(int);
    int get_x();
    int get_y();
    int get_hp();
    void set_hp(int);
    void set_hp_v(int*);
    void set_x(int*);
    void set_y(int*);
    bool cr_move_check(char**, int, int);
    bool action_check(char**, int*, int*, int, int);
    int get_att();
    int get_def();
    bool is_dead = false;
};

// player functions and class
class ang :public creature {
private:
    char team;
public:
    ang(int x1 = 0, int y1 = 0, int hp1 = 0, int power1 = 0, int def1 = 0, int pots1 = 1) : creature(x1, y1, hp1, power1, def1, pots1) {};
    void set_team(char);
    char get_team();
    void change_coor(char);
};

void place_player(int, int, char**, ang);

// werewolf functions and class
class werewolf : public creature {
public:
    werewolf(int x1 = 0, int y1 = 0, int hp1 = 3, int power1 = 0, int def1 = 0, int pots1 = 0) : creature(x1,y1,hp1,power1,def1,pots1) {};
    void move(int*, int*, int);
};

void create_array_w(int, int, char**, werewolf*);
int place_werewolves(int, int, char**);

// vampire functions and class
class vampire :public creature {
public:
    vampire(int x1 = 0, int y1 = 0, int hp1= 3 , int power1 = 0, int def1 = 0, int pots1 = 0) : creature(x1, y1, hp1, power1, def1, pots1) {};
    void move(int*, int*, int);
};

void create_array_v(int, int, char**, vampire*);
void place_vampires(int, int, int, char**);
