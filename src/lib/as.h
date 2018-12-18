/*
 * a-star-algorithm
 * github.com/01mu
 */

#ifndef AS_H_
#define AS_H_

#include <iostream>
#include <vector>
#include <limits.h>
#include <time.h>
#include <stdlib.h>
#include <queue>
#include <string>

using namespace std;

struct node
{
    vector<int> state;

    int blank_pos = 0;
    int path_cost = 0;
    int heuristic = 0;

    string move = "";
};

bool check_neighbor(char, node &);
bool check_list(vector<node> &, node &);
node get_lowest_list(vector<node> &);
int find_zero(vector<int> &);
vector<int> update_state(char, node &);
int update_heuristic(vector<int> &, node &);
int update_m_heuristic(vector<int> &, node &);
int get_index(vector<int> &, int);
node config_neigh_a_star(char);
node config_neigh_dfbb(char, int);
void a_star_search();
void dfbb_search();
void output_state(vector<int> &);
void display_path();

extern char options[4];
extern vector<node> final_path;
extern int heuristic_type;

extern vector<node> open_list;
extern vector<node> closed_list;

extern vector<int> start_state;
extern vector<int> end_state;

extern node neighbor_node;
extern node current_node;

#endif
