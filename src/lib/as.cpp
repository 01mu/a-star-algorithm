/*
 * a-star-algorithm
 * github.com/01mu
 */

#include "as.h"

char options[4] = {'r', 'd', 'l', 'u'};
vector<node> final_path;
int heuristic_type = 1;

vector<node> open_list;
vector<node> closed_list;

vector<int> start_state;
vector<int> end_state;

node neighbor_node;
node current_node;

void display_path()
{
    int move_count;
    string move;

    cout << "Start state: " << endl;
    output_state(start_state);

    cout << endl << "End state: " << endl;
    output_state(end_state);

    cout << endl << "Finding path using ";

    if(heuristic_type)
    {
        cout << "Manhattan heuristic...";
    }
    else
    {
        cout << "Out of place heuristic...";
    }

    move_count = final_path.size() - 1;

    cout << endl << endl << "Moves:" << endl;

    for(int i = 0; i < final_path.size() - 1; i++)
    {
        move = final_path.at(i).move;

        if(move == "u")
        {
            cout << "Up";
        }
        else if(move == "d")
        {
            cout << "Down";
        }
        else if(move == "l")
        {
            cout << "Left";
        }
        else
        {
            cout << "Right";
        }

        cout << ":" << endl;
        output_state(final_path.at(i).state);
        cout << endl;
    }

    cout << "Move count: " << move_count << endl;
}

void output_state(vector<int> & state)
{
    for(int i = 0; i < 9; i++)
    {
        cout << state.at(i) << " ";

        if(i == 2 || i == 5 || i == 8)
        {
            cout << endl;
        }
    }
}

bool check_neighbor(char option, node & current_node)
{
    bool valid_neighbor = 0;
    int blank = current_node.blank_pos;

    if(option == 'u')
    {
        if(blank - 3 >= 0)
        {
            valid_neighbor = 1;
        }
    }

    if(option == 'd')
    {
        if(blank + 3 <= 8)
        {
            valid_neighbor = 1;
        }
    }

    if(option == 'l')
    {
        if(blank % 3 != 0)
        {
            valid_neighbor = 1;
        }
    }

    if(option == 'r')
    {
        if(blank + ((blank + 1) % 3) > blank)
        {
            valid_neighbor = 1;
        }
    }

    return valid_neighbor;
}

bool check_list(vector<node> & list, node & neighbor_node)
{
    bool same_state;
    bool same_move;
    bool in_list = 0;

    for(int i = 0; i < list.size(); i++)
    {
        same_state = list.at(i).state == neighbor_node.state;
        same_move = list.at(i).move == neighbor_node.move;

        if(same_state && same_move)
        {
            in_list = 1;
        }
    }

    return in_list;
}

node get_lowest_list(vector<node> & list)
{
    int lowest = INT_MAX;
    node lowest_f;

    for(int i = 0; i < list.size(); i++)
    {
        if((list.at(i).heuristic + list.at(i).path_cost) <= lowest)
        {
            lowest = list.at(i).heuristic + list.at(i).path_cost;
            lowest_f = list.at(i);
        }
    }

    return lowest_f;
}

int find_zero(vector<int> & state)
{
    int zero;

    for(int i = 0; i < state.size(); i++)
    {
        if(state.at(i) == 0)
        {
            zero = i;
        }
    }

    return zero;
}

vector<int> update_state(char option, node & n)
{
    vector<int> new_state;
    int temp[9];

    if(option == 'u')
    {
        for(int i = 0; i < n.state.size(); i++)
        {
            if((int) i == n.blank_pos)
            {
                temp[i] = n.state.at(n.blank_pos - 3);
            }
            else if((int)i ==  n.blank_pos - 3)
            {
                temp[i] = 0;
            }
            else
            {
                temp[i] = n.state.at(i);
            }
        }
    }

    if(option == 'd')
    {
        for(int i = 0; i < n.state.size(); i++)
        {
            if((int) i == n.blank_pos)
            {
                temp[i] = n.state.at(n.blank_pos + 3);
            }
            else if((int) i == n.blank_pos + 3)
            {
                temp[i] = 0;
            }
            else
            {
                temp[i] = n.state.at(i);
            }
        }
    }

    if(option == 'l')
    {
        for(int i = 0; i < n.state.size(); i++)
        {
            if((int) i == n.blank_pos)
            {
                temp[i] = n.state.at(n.blank_pos - 1);
            }
            else if((int) i == n.blank_pos - 1)
            {
                temp[i] = 0;
            }
            else
            {
                temp[i] = n.state.at(i);
            }
        }
    }

    if(option == 'r')
    {
        for(int i = 0; i < n.state.size(); i++)
        {
            if((int) i == n.blank_pos)
            {
                temp[i] = n.state.at(n.blank_pos + 1);
            }
            else if((int) i == n.blank_pos + 1)
            {
                temp[i] = 0;
            }
            else
            {
                temp[i] = n.state.at(i);
            }
        }
    }

    for(int i = 0; i < 9; i++)
    {
        new_state.push_back(temp[i]);
    }

    return new_state;
}

int update_heuristic(vector<int> & h, node & n)
{
    int heuristic = 0;

    for(int i = 0; i < h.size(); i++)
    {
        if(h.at(i) != n.state.at(i))
        {
            heuristic++;
        }
    }

    return heuristic;
}

int get_index(vector<int> & vector, int value)
{
    int index;

    for(int i = 0; i < vector.size(); i++)
    {
        if(vector.at(i) == value)
        {
            index = i;
        }
    }

    return index;
}

int update_m_heuristic(vector<int> & end_state, node & n)
{
    int heuristic = 0;
    int state_distance;

    for(int i = 0; i < 9; i++)
    {
        state_distance = abs(get_index(end_state, i) - get_index(n.state, i));

        switch(state_distance)
        {
            case 0:
                heuristic += 0;
                break;
            case 1:
                heuristic += 1;
                break;
            case 2:
                heuristic += 2;
                break;
            case 3:
                heuristic += 1;
                break;
            case 4:
                if(abs(get_index(end_state, i) || get_index(n.state, i)) == 2)
                {
                    heuristic += 4;
                }
                else
                {
                    heuristic += 2;
                }
                break;
            case 5:
                heuristic += 3;
                break;
            case 6:
                heuristic += 2;
                break;
            case 7:
                heuristic += 3;
                break;
            case 8:
                heuristic += 4;
                break;
            default:
                break;
        }
    }

    return heuristic;
}

node config_neigh_a_star(char option)
{
    bool cl;

    neighbor_node.state = update_state(option, current_node);
    neighbor_node.move = option;
    neighbor_node.blank_pos = find_zero(neighbor_node.state);

    if(heuristic_type == 0)
    {
        neighbor_node.heuristic = update_heuristic(end_state, neighbor_node);
    }
    else
    {
        neighbor_node.heuristic = update_m_heuristic(end_state, neighbor_node);
    }

    cl = check_list(closed_list, neighbor_node);

    if(cl && current_node.path_cost < neighbor_node.path_cost)
    {
        for(int i = 0; i < closed_list.size(); i++)
        {
            if(closed_list.at(i).state == neighbor_node.state)
            {
                closed_list.erase(closed_list.begin() + i);
            }
        }

        neighbor_node.path_cost = current_node.path_cost;
        open_list.push_back(neighbor_node);
    }

    cl = check_list(open_list, neighbor_node);

    if(cl && current_node.path_cost < neighbor_node.path_cost)
    {
        neighbor_node.path_cost = current_node.path_cost;
    }

    if(!cl && check_list(closed_list, neighbor_node) == 0)
    {
        neighbor_node.path_cost = 1 + current_node.path_cost;
        open_list.push_back(neighbor_node);
    }

    return neighbor_node;
}

void a_star_search()
{
    vector<node> lowest;
    node temp;

    open_list.push_back(current_node);

    while(neighbor_node.state != end_state && current_node.state != end_state)
    {
        current_node = get_lowest_list(open_list);

        for(int i = 0; i < open_list.size(); i++)
        {
            if(open_list.at(i).state == current_node.state)
            {
                open_list.erase(open_list.begin() + i);
            }
        }

        closed_list.push_back(current_node);

        for(int i = 0; i < 4; i++)
        {
            if(check_neighbor(options[i], current_node))
            {
                temp = config_neigh_a_star(options[i]);

                lowest.push_back(temp);
            }
        }

        final_path.push_back(get_lowest_list(lowest));
        lowest.clear();
    }
}

node config_neigh_dfbb(char option, int best_score)
{
    int check_open;
    int check_closed;

    neighbor_node.state = update_state(option, current_node);
    neighbor_node.move = option;
    neighbor_node.blank_pos = find_zero(neighbor_node.state);

    if(heuristic_type == 0)
    {
        neighbor_node.heuristic = update_heuristic(end_state, neighbor_node);
    }
    else
    {
        neighbor_node.heuristic = update_m_heuristic(end_state, neighbor_node);
    }

    check_open = check_list(open_list, neighbor_node);
    check_closed = check_list(closed_list, neighbor_node);

    if(neighbor_node.heuristic <= best_score)
    {
        if(!check_open && !check_closed)
        {
            neighbor_node.path_cost = 1 + current_node.path_cost;
            open_list.push_back(neighbor_node);
        }
    }

    return neighbor_node;
}

void dfbb_search()
{
    vector<node> lowest;
    node temp;

    bool same_state;
    bool same_move;

    int best_score = current_node.heuristic;

    open_list.push_back(current_node);

    while(open_list.size() != 0)
    {
        current_node = get_lowest_list(open_list);

        for(int i = 0; i < open_list.size(); i++)
        {
            same_state = open_list.at(i).state == current_node.state;
            same_move = open_list.at(i).move == current_node.move;

            if(same_state && same_move)
            {
                open_list.erase(open_list.begin() + i);
            }
        }

        closed_list.push_back(current_node);

        if(current_node.heuristic < best_score)
        {
            best_score = current_node.heuristic;
        }

        for(int i = 0; i < 4; i++)
        {
            if(check_neighbor(options[i], current_node))
            {
                config_neigh_dfbb(options[i], best_score);

                lowest.push_back(temp);
            }
        }

        final_path.push_back(get_lowest_list(lowest));
        lowest.clear();
    }
}
