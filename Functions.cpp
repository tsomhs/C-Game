#include <iostream>
#include "Definitions.h"
#include <cstdlib>
#include <time.h>
#include <vector>
using namespace std;

//player
void place_player(int x,int y,char** arr,ang player){
    if(player.get_team() == 'W') {
        arr[x - 2][y / 2] = 'W';
    }
    else if(player.get_team() == 'V'){       
		arr[x - 2][y / 2] = 'V';
    }
}

// creatures
bool creature::action_check(char** arr, int* p_x, int* p_y, int x, int y) {

	if (arr[x - 1][y] == 'v' || arr[x - 1][y] == 'w' || arr[x - 1][y] == '$') {
		*p_x = x - 1;
		*p_y = y;
		return true;
	}
	else if (arr[x + 1][y] == 'v' || arr[x + 1][y] == 'w' || arr[x + 1][y] == '$') {
		*p_x = x + 1;
		*p_y = y;
		return true;
	}
	else if (arr[x][y - 1] == 'v' || arr[x][y - 1] == 'w' || arr[x][y - 1] == '$') {
		*p_x = x;
		*p_y = y - 1;
		return true;
	}
	else if (arr[x][y + 1] == 'v' || arr[x][y + 1] == 'w' || arr[x][y + 1] == '$') {
		*p_x = x;
		*p_y = y + 1;
		return true;
	}
	return false;
}

bool creature::cr_move_check(char** arr, int x, int y) {
	if (arr[x][y] == '|' || arr[x][y] == '=' || arr[x][y] == '#' || arr[x][y] == 'w' || arr[x][y] == 'v' || arr[x][y] == '%' || arr[x][y] == 'W' || arr[x][y] == 'V' || arr[x][y] == '$')
        return false;
    return true;
}

int creature::get_x() {
    return this->x;
}

int creature::get_y() {
    return this->y;
}

int creature::get_hp() {
    return this->hp;
}

void creature::set_hp(int hp) {
    this->hp = hp;
}

void creature::set_hp_v(int* hp) {
    this->hp = *hp;
}

void creature::set_x(int* x) {
    this->x = *x;
}

void creature::set_y(int* y) {
    this->y = *y;
}

int creature::get_pots() {
    return this->pots ;
}

void creature::set_pots(int pots){
    this->pots = pots;
}

void creature::print_pots() {
    cout << this->pots;
    cout << endl;
}

int creature::get_att() {
    return this->power;
}
int creature::get_def() {
    return this->def;
}

//player functions
void ang::change_coor(char ch) {
    if (ch == 'U')
        this->y = this->get_y() - 1;
    else if (ch == 'D')
        this->y = this->get_y() + 1;
    else if (ch == 'R')
        this->x = this->get_x() + 1;
    else if (ch == 'L')
        this->x = this->get_x() - 1;
}

void ang::set_team(char ch) {
    if (ch == 'W')
        this->team = 'W';
    else if (ch == 'V')
        this->team = 'V';
}
char ang::get_team() {
    return this->team;
}

void magic_pot(char** arr, int x, int y) {
	int random_y = rand() % (y - 2) + 1;
	int random_x = rand() % (x - 2) + 1;
	if (arr[random_y][random_x] == ' ')
		arr[random_y][random_x] = '$';
	else
		magic_pot(arr, random_x, random_y);
}

//werewolves
void werewolf::move(int* x, int* y,int random) {
    if( random == 1)    //STAY
		return;
    else if( random == 2)   //UP
        *x -= 1;
    else if( random == 3)   //DOWN
        *x += 1;
    else if( random == 4)   // left
		*y -= 1;
	else    //RIGHT
        *y += 1;
    return;
}

void create_array_w(int x, int y, char** arr, werewolf* c_arr) {
    int arr_counter = 0;
    srand(time(0));
    for (int i = 1; i < x - 1; i++) {
        for (int j = 1; j < y - 1; j++) {
            if (arr[i][j] == 'w') {
                int random_at = rand() % 3 + 1;
                int random_def = rand() % 2 + 1;
                int rand_pots = rand() % 3;
                werewolf c1(i, j, 3, random_at, random_def, rand_pots);
                c_arr[arr_counter] = c1;
                arr_counter++;
            }
        }
    }
}
    
bool move_check(char** arr, int x, int y, char dest) {
	if (dest == 'U') {
		if (arr[x][y - 1] == '|' || arr[x][y - 1] == '#' || arr[x][y - 1] == 'w' || arr[x][y - 1] == 'v' || arr[x][y - 1] == '%' || arr[x][y - 1] == 'W' || arr[x][y - 1] == 'V')
			return 0;
	}
	else if (dest == 'D') {
		if (arr[x][y + 1] == '|' || arr[x][y + 1] == '#' || arr[x][y + 1] == 'w' || arr[x][y + 1] == 'v' || arr[x][y + 1] == '%' || arr[x][y + 1] == 'W' || arr[x][y + 1] == 'V')
			return 0;
	}
	else if (dest == 'R') {
		if (arr[x + 1][y] == '=' || arr[x + 1][y] == '#' || arr[x + 1][y] == 'w' || arr[x + 1][y] == 'v' || arr[x + 1][y] == '%' || arr[x + 1][y] == 'W' || arr[x + 1][y] == 'V')
			return 0;
	}
	else if (dest == 'L') {
		if (arr[x - 1][y] == '=' || arr[x - 1][y] == '#' || arr[x - 1][y] == 'w' || arr[x - 1][y] == 'v' || arr[x - 1][y] == '%' || arr[x - 1][y] == 'W' || arr[x - 1][y] == 'V')
			return 0;
	}
	return 1;
}

int place_werewolves(int x, int y, char** arr) {
    int count = 0, randomness = 15;
    srand(time(0));
    for (int i = 1; i < x - 1; i++) {
        for (int j = 1; j < y - 1; j++) {
            int random = rand() % randomness + 1;
            if (random == 1 && count < (x-2) * (y-2) / 15 && arr[i][j] != '%') {
                arr[i][j] = 'w';
                count++;
            }           
        }
    }
    return count;
}

//vampires
void vampire::move(int* x, int* y, int random) {
	if (random == 1) { //STAY
		return;
	}
	else if (random == 2) { //UP
		*x -= 1;
	}
	else if (random == 3) { //DOWN
		*x += 1;
	}
	else if (random == 4) {//LEFT
		*y -= 1;
	}
	else if(random == 5) {//RIGHT
		*y += 1;
	}
    else if (random == 6) {//UP LEFT
        *x -= 1;
        *y -= 1;
    }
    else if (random == 7) { // UP RIGHT
        *x -= 1;
        *y += 1;
    }
    else if (random == 8) {// DOWN LEFT
        *x += 1;
        *y -= 1;
    }
	else{   // DOWN RIGHT
	    *x += 1;
        *y += 1;
    }
}

void create_array_v(int x, int y, char** arr, vampire* c_arr) {
    int arr_counter = 0;
    srand(time(0));
    for (int i = 1; i < x - 1; i++) {
        for (int j = 1; j < y - 1; j++) {
            if (arr[i][j] == 'v') {
                int random_at = rand() % 3 + 1;
                int random_def = rand() % 2 + 1;
                int rand_pots = rand() % 3;
                vampire c1(i, j,3, random_at, random_def, rand_pots);
                c_arr[arr_counter] = c1;
                arr_counter++;
            }
        }
    }
}

void place_vampires(int x, int y,int boarder, char** arr) {
    int randomness = 15;
    srand(time(0));
    for (int i = 1; i < x - 1; i++) {
        for (int j = 1; j < y - 1; j++) {
            int random = rand() % randomness + 1;
            if (boarder == 0)
                return;
            else if(random == 3) {
                if (arr[i][j] != 'w' && arr[i][j] != 'v') { 
                    arr[i][j] = 'v';
                    boarder--;
                }
                else{
                    int temp= 0;
                    while (arr[i][j] != ' ') {
                        if (j < y - 1) 
                            j++;
                        else if( i < x - 1 ) {
                            temp = j;
                            j = 1;
                            i++;
                        }
                    }
                    j = temp;
                    arr[i][j] = 'v';
                }
            }
        }
    }
    //cleaning
    for (int i = 1; i < x - 1; i++) {
        for (int j = 1; j < y - 1; j++) {
            if (arr[i][j] == 'w' && boarder != 0) {
                arr[i][j] = ' ';
                boarder--;
            }
        }
    }
}

//General Utility Functions
char** init(int& x, int& y) {
    //interface
    cout << "Give the dimensions of the map(At least 15) " << endl << " x : ";
    cin >> x;
    cout << " y : ";
    cin >> y;
    while (x < 15 || y < 15) {
        cout << "Give the dimensions of the map(At least 15) " << endl << " x : ";
        cin >> x;
        cout << " y : ";
        cin >> y;
    }
    x += 2;//we dont want the game map count '=' and '|' as space
    y += 2;
    char** arr = new char* [x];
    for (int i = 0; i < x; i++) {
        arr[i] = new char[y];
    }
    return arr;
}

//print array
void print_array(char** arr, int x, int y,int day) {
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            cout << arr[i][j];
        }
        cout << "\n";
    }
    if (day == 0 || day == 1) {
        cout << "        DAY        " << endl;
    }
    else if(day == 2 || day == 3){
        cout << "        NIGHT        " << endl;
    }
}

//generate map
void generate_map(int x,int y,char** arr) {
    srand(time(0));
    //assigning values to array 
    //borders,trees
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            if (i == 0 || i == x - 1) {
                arr[i][j] = '=';
            }
            else if (j == 0 || j == y - 1) {
                arr[i][j] = '|';
            }
            else {
                int random = rand() % (x - 2) / 2 + 1;
                if (random == 2) {
                    arr[i][j] = '#';
                    continue;
                }
                arr[i][j] = ' ';
            }
        }
    }
    //lakes
    for (int i = 1; i < x - 2; i++) {
        for (int j = 1; j < y - 2; j++) {
            int random = rand() % (x * y / 8) + 1;
            if (random == 1 && j < y - 3 && i < x - 3) {
                if (x < 35 && y < 35) {
                    arr[i][j] = '%'; // 2x2 lake
                    arr[i + 1][j] = '%';
                    arr[i][j + 1] = '%';
                    arr[i + 1][j + 1] = '%';
                }
                else {
                    arr[i][j] = '%'; // 4x4 lake
                    arr[i + 1][j] = '%';
                    arr[i][j + 1] = '%';
                    arr[i + 1][j + 1] = '%';

                    arr[i][j + 2] = '%';
                    arr[i][j + 3] = '%';

                    arr[i + 1][j + 2] = '%';
                    arr[i + 1][j + 3] = '%';

                    arr[i + 2][j] = '%';
                    arr[i + 3][j] = '%';

                    arr[i + 2][j + 1] = '%';
                    arr[i + 3][j + 1] = '%';

                    arr[i + 2][j + 2] = '%';
                    arr[i + 3][j + 2] = '%';

                    arr[i + 2][j + 3] = '%';
                    arr[i + 3][j + 3] = '%';
                }
            }
        }
    }
}
