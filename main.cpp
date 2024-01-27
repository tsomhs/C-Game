#include <iostream>
#include "Definitions.h"
#include <vector>
#include <chrono>
#include <thread>
#include <windows.h>
using namespace std;

int main()
{
	int x, y;
    char** arr;// game map
    arr = init(x, y);  
    generate_map(x, y,arr);


    char answer; // choosing team
    std::cout << "Which team would you like to support ? (W or V)" << endl;
    cin >> answer;
    ang player(x-2,y/2,0,0,0,1);
    while (answer != 'W' && answer != 'V') {
        std::cout << "Wrong " << endl;
        cin >> answer;
    }
    player.set_team(answer);
    place_player(x, y, arr, player);
    int werewolf_count;
    werewolf_count = place_werewolves(x, y, arr); //Note: place_werewolves returns how many werewolves where placed + - some(cause of cleaning in place_vampires)
    place_vampires(x, y, werewolf_count, arr);
    int vampire_count = 0;
    for (int i = 1; i < x - 1; i++) {
        for (int j = 1; j < y - 1; j++) {
            if (arr[i][j] == 'v')
                vampire_count++;
        }
    }
    werewolf_count = 0;
    for (int i = 1; i < x - 1; i++) {
        for (int j = 1; j < y - 1; j++) {
            if (arr[i][j] == 'w')
                werewolf_count++;
        }
    }

    werewolf* w_arr = new werewolf[werewolf_count];// creating two arrays that store the objects
    vampire* v_arr = new vampire[vampire_count];

    create_array_w(x,y,arr,w_arr);
    create_array_v(x,y,arr,v_arr);

    std::cout << "The game begins in 3";
    this_thread::sleep_for(1000ms);
    std::cout << "  2";
    this_thread::sleep_for(1000ms);
    std::cout << "  1";
    this_thread::sleep_for(1000ms);
    std::cout << "\nLet the game begin!!!!" << endl;

    int day = 0;
    int v_arr_size = vampire_count;
    int w_arr_size = werewolf_count;
    //game begin
    bool game_over = false;
    bool toggle = true;
    bool temp_tog;
	magic_pot(arr, x, y);
    print_array(arr, x, y,day);

    while (game_over != true) {
        bool a = false;
        //players moves
        this_thread::sleep_for(200ms);	// for the time pace
        if ((GetKeyState(VK_LEFT) & 0x8000) && toggle == true) {
            system("cls");
            if (move_check(arr, player.get_x(), player.get_y(), 'U') == 1) {
                if (arr[player.get_x()][player.get_y() - 1] == '$') {
                    player.set_pots(player.get_pots() + 1);
                }    
                arr[player.get_x()][player.get_y()] = ' ';
                player.change_coor('U');
                arr[player.get_x()][player.get_y()] = answer;
            }
            a = true;
        }
        else if ((GetKeyState(VK_RIGHT) & 0x8000) && toggle == true) {
            system("cls");
            if (move_check(arr, player.get_x(), player.get_y(), 'D') == 1) {
                if (arr[player.get_x()][player.get_y() + 1] == '$') {
                    player.set_pots(player.get_pots() + 1);
                }    
                arr[player.get_x()][player.get_y()] = ' ';
                player.change_coor('D');
                arr[player.get_x()][player.get_y()] = answer;
            }
            a = true;
        }
        else if ((GetKeyState(VK_DOWN) & 0X8000) && toggle == true) {
            system("cls");
            if (move_check(arr, player.get_x(), player.get_y(), 'R') == 1) {
                if(arr[player.get_x()+1][player.get_y()] == '$'){
					player.set_pots(player.get_pots() + 1);
                }
                arr[player.get_x()][player.get_y()] = ' ';
                player.change_coor('R');
                arr[player.get_x()][player.get_y()] = answer;
            }
            a = true;
        }
        else if ((GetKeyState(VK_UP) & 0X8000) && toggle == true) {
            system("cls");
            if (move_check(arr, player.get_x(), player.get_y(), 'L') == 1) {
                if (arr[player.get_x() - 1][player.get_y()] == '$') {
					player.set_pots(player.get_pots() + 1);
                }
                arr[player.get_x()][player.get_y()] = ' ';
                player.change_coor('L');
                arr[player.get_x()][player.get_y()] = answer;
            }
            a = true;
        }
        else if (GetKeyState('F') & 0X8000) {
            if (answer == 'W' && day >= 2 && player.get_pots() > 0) {
                for (int i = 0; i < w_arr_size; i++) {
					if (w_arr[i].get_hp() <= 2 && w_arr[i].is_dead == 0)
						w_arr[i].set_hp(w_arr[i].get_hp() + 1);
                }
                player.set_pots(player.get_pots() - 1);
                cout << " Healed!!!!!! " << endl; 
            }
            else if(answer == 'V' && day < 2 && player.get_pots() > 0) {
                for (int i = 0; i < v_arr_size; i++) {
                    if(v_arr[i].get_hp() <= 2 && v_arr[i].is_dead == 0)
                        v_arr[i].set_hp(v_arr[i].get_hp() + 1);
                }
                player.set_pots(player.get_pots() + 1);
                cout << "Healed all vampires" << endl;
            }
            else
                cout << "Unable to heal" << endl;
        }
        else if ((GetKeyState('P') & 0X8000)) {
            system("cls");
            if (toggle == true) {
                std::cout << "\nGAME PAUSED: \n";
                std::cout << "Werewolves: " << werewolf_count << endl;
                std::cout << "Vampires: " << vampire_count << endl;
                std::cout << "Magic Potions: ";
                player.print_pots();
                std::cout << "Unpause to continue ..." << endl;
				std::cout << endl;
				temp_tog = true;
                toggle = false;
            }
            else {
                std::cout << "GAME RESUMED" << endl;
                print_array(arr, x, y,day);
                toggle = true;
            }
            day--;
        }
        else
            a = false;
        //werewolves play
        if (a == true) {
            day++;
            srand(time(0));
            std::cout << endl;

            for (int i = 0; i <= w_arr_size - 1; i++) {
                if (w_arr[i].is_dead == true) continue; // if werewolf is dead then go to the next one
                int d1 = x*y;
                int d2 = x*y;
                int* p1 = &d1;
                int* p2 = &d2;

                if (w_arr[i].action_check(arr, p1, p2,w_arr[i].get_x(),w_arr[i].get_y()) == true) { // there is an action to be performed
                    if (arr[*p1][*p2] == 'w') { // the action involves another werewolf
                        //heal
                        int z = 0;
                        for (z = 0; z <= w_arr_size - 1; z++) { // find werewolf using the array
                            if (w_arr[z].get_x() == *p1 && w_arr[z].get_y() == *p2)
                                break;
                        }
                        int h = w_arr[z].get_hp();
                        if (h < 3 && h > 0 ) {
                            h = h + 1;
                            w_arr[z].set_hp(h);
                        }                        
                        else { // move -> function ????
                            int random = rand() % 5 + 1;
                            int num_x = w_arr[i].get_x();
                            int num_y = w_arr[i].get_y();
                            int* p_x = &num_x;
                            int* p_y = &num_y;
                            w_arr[i].move(p_x, p_y, random);
                            if (w_arr[i].cr_move_check(arr, *p_x, *p_y) == 1) {
                                arr[w_arr[i].get_x()][w_arr[i].get_y()] = ' ';
                                w_arr[i].set_x(p_x);
                                w_arr[i].set_y(p_y);
                                arr[w_arr[i].get_x()][w_arr[i].get_y()] = 'w';
                            }
                        }
                    }
                    else if (arr[*p1][*p2] == 'v') {
                        int z = 0;
                        for (z = 0; z <= v_arr_size - 1; z++) { // find vampire using the array
                            if (v_arr[z].is_dead == true)
                                continue;
                            if (v_arr[z].get_x() == *p1 && v_arr[z].get_y() == *p2) {
                                break;
                            }
                        }
                        int hp_temp = v_arr[z].get_hp();
                        int* h = &hp_temp;
                        if (w_arr[i].get_att() >= v_arr[z].get_att() && w_arr[i].get_att() > v_arr[z].get_def() && v_arr[z].is_dead == false) {
                            *h = *h - (w_arr[i].get_att() - v_arr[z].get_def());
                            v_arr[z].set_hp_v(h);
                            if (v_arr[z].get_hp() <= 0) { //dead
                                v_arr[z].is_dead = true;
                                arr[v_arr[z].get_x()][v_arr[z].get_y()] = ' ';
                                int val = -7;
                                int* point_temp = &val;
                                v_arr[z].set_x(point_temp);
                                v_arr[z].set_y(point_temp);
                                vampire_count--;
                            }
                        }
                        else { //move
                            int random = rand() % 5 + 1;
                            int num_x = w_arr[i].get_x();
                            int num_y = w_arr[i].get_y();
                            int* p_x = &num_x;
                            int* p_y = &num_y;
                            w_arr[i].move(p_x, p_y, random);
                            if (w_arr[i].cr_move_check(arr, *p_x, *p_y) == 1) {
                                arr[w_arr[i].get_x()][w_arr[i].get_y()] = ' ';
                                w_arr[i].set_x(p_x);
                                w_arr[i].set_y(p_y);
                                arr[w_arr[i].get_x()][w_arr[i].get_y()] = 'w';
                            }
                        }
                    }
                }
                else { //choice == move
                    int random = rand() % 5 + 1;
                    int num_x = w_arr[i].get_x();
                    int num_y = w_arr[i].get_y();
                    int* p_x = &num_x;
                    int* p_y = &num_y;
                    w_arr[i].move(p_x, p_y, random);
                    if (w_arr[i].cr_move_check(arr, *p_x, *p_y) == 1) {
                        arr[w_arr[i].get_x()][w_arr[i].get_y()] = ' ';
                        w_arr[i].set_x(p_x);
                        w_arr[i].set_y(p_y);
                        arr[w_arr[i].get_x()][w_arr[i].get_y()] = 'w';
                    }
                }
            }


            //vampires play
            for (int i = 0; i <= v_arr_size - 1; i++) {
                if (v_arr[i].is_dead == true)
                    continue; //if vampire is dead then go to the next one
                int d1 = x*y;
                int d2 = x*y;
                int* p1 = &d1;
                int* p2 = &d2;

                if (v_arr[i].action_check(arr, p1, p2, v_arr[i].get_x(), v_arr[i].get_y()) == true) { // there is an action to be performed
                    if (arr[*p1][*p2] == 'v') { //the action involves another vampire
                        //heal
                        int z = 0;
                        for (z = 0; z <= v_arr_size - 1; z++) { //find vampire using the array
                            if (v_arr[z].is_dead == true) continue;
                            if (v_arr[z].get_x() == *p1 && v_arr[z].get_y() == *p2) {
                                break;
                            }
                        }
                        int h = v_arr[z].get_hp();
                        if (h < 3 && h > 0) {
                            h = h + 1;
                            v_arr[z].set_hp(h);
                          
                        }
                        else { //move -> function ????
                            int random = rand() % 8 + 1;
                            int num_x = v_arr[i].get_x();
                            int num_y = v_arr[i].get_y();
                            int* p_x = &num_x;
                            int* p_y = &num_y;
                            v_arr[i].move(p_x, p_y, random);
                            if (v_arr[i].cr_move_check(arr, *p_x, *p_y) == 1) {
                                arr[v_arr[i].get_x()][v_arr[i].get_y()] = ' ';
                                v_arr[i].set_x(p_x);
                                v_arr[i].set_y(p_y);
                                arr[v_arr[i].get_x()][v_arr[i].get_y()] = 'v';
                            }
                        }
                    }
                    else if (arr[*p1][*p2] == 'w') {
                        int z = 0;
                        for (z = 0; z <= w_arr_size - 1; z++) { //find werewolf using the array
                            if (w_arr[z].get_x() == *p1 && w_arr[z].get_y() == *p2) {
                                break;
                            }
                        }
                        int hp_temp = w_arr[z].get_hp();
                        int* h = &hp_temp;
                        if (v_arr[i].get_att() >= w_arr[z].get_att() && v_arr[i].get_att() > w_arr[z].get_def() && w_arr[z].is_dead == false) {
                            *h = *h - (v_arr[i].get_att() - w_arr[z].get_def());
                            w_arr[z].set_hp_v(h);
                            if (w_arr[z].get_hp() <= 0) { //dead
                                w_arr[z].is_dead = true;
                                arr[w_arr[z].get_x()][w_arr[z].get_y()] = ' ';
                                int val = -7;
                                int* point_temp = &val;
                                w_arr[z].set_x(point_temp);
                                w_arr[z].set_y(point_temp);
                                werewolf_count--;
                            }
                        }
                        else { //move
                            int random = rand() % 8 + 1;
                            int num_x = v_arr[i].get_x();
                            int num_y = v_arr[i].get_y();
                            int* p_x = &num_x;
                            int* p_y = &num_y;
                            v_arr[i].move(p_x, p_y, random);
                            if (v_arr[i].cr_move_check(arr, *p_x, *p_y) == 1) {
                                arr[v_arr[i].get_x()][v_arr[i].get_y()] = ' ';
                                v_arr[i].set_x(p_x);
                                v_arr[i].set_y(p_y);
                                arr[v_arr[i].get_x()][v_arr[i].get_y()] = 'v';
                            }
                        }
                    }
                }
                else {
                    //choice == move
                    int random = rand() % 8 + 1;
                    int num_x = v_arr[i].get_x();
                    int num_y = v_arr[i].get_y();
                    int* p_x = &num_x;
                    int* p_y = &num_y;
                    v_arr[i].move(p_x, p_y, random);
                    if (v_arr[i].cr_move_check(arr, *p_x, *p_y) == 1) {
                        arr[v_arr[i].get_x()][v_arr[i].get_y()] = ' ';
                        v_arr[i].set_x(p_x);
                        v_arr[i].set_y(p_y);
                        arr[v_arr[i].get_x()][v_arr[i].get_y()] = 'v';
                    }
                }
            }
            if (day == 4)
                day = 0;        
			print_array(arr, x, y, day);			
        }
        if (werewolf_count == 0) {
            cout << "The vampires won !!!" << endl;
            game_over = true;
        }
        else if (vampire_count == 0) {
            cout << "The werewolves won !!!" << endl;
            game_over = true;
        }
   }
   cout << "Game over." << " Thank you for playing :) " << endl; 
   for (int i = 0; i < x; i++)
       delete arr[i];
   delete arr;
   delete w_arr;
   delete v_arr;
}

