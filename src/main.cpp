/*
 * a-star-algorithm
 * github.com/01mu
 */

#include <iostream>
#include "lib/as.cpp"

using namespace std;

int main()
{
    int start_array[9] = {1, 3, 4, 8, 6, 2, 7, 0, 5};
    //int start_array[9] = {2, 8, 1, 0, 4, 3, 7, 6, 5};
    //int start_array[9] = {2, 8, 1, 4, 6, 3, 0, 7, 5};
    //int start_array[9] = {5, 6, 7, 4, 0, 8, 3, 2, 1};

    int end_array[9] =  {1, 2, 3, 8, 0, 4, 7, 6, 5};

    for(int i = 0; i < 9; i++)
    {
        start_state.push_back(start_array[i]);
        end_state.push_back(end_array[i]);
    }

    current_node.state = start_state;
    current_node.path_cost = 0;
    current_node.blank_pos = find_zero(start_state);

    if(heuristic_type)
    {
        current_node.heuristic = update_m_heuristic(end_state, current_node);
    }
    else
    {
        current_node.heuristic = update_heuristic(end_state, current_node);
    }

    a_star_search();
    display_path();

    return 0;
}
