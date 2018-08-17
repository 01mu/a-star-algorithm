/*
* A* algorithm sliding game solver
*
* github.com/01mu
*/

#include <iostream>
#include <vector>
#include <limits.h>
#include <time.h>
#include <stdlib.h>
#include <queue>
#include <string>

using namespace std;

// node structure
struct node
{
    struct node *parent;

    std::vector<int> state;

    int blankPosition = 0;
    int pathCost = 1;
    int heuristic = 0;

    string move = "";
    string path = "";
};

/* check to determine whether a neighbor position is valid
 * given the position of 0 (the blank space) in state */
bool checkNeighbor(char, node);

// check to see if a node is in either the open or closed list
bool checkList(std::vector<node>, node);

// get the node with the lowest f value
node getLowestOpenList(std::vector<node>);

// find the value of 0 (the blank space) in a node's state (board)
int findZero(std::vector<int>);

/* update the state (board) of a given neighbor node based
 * on its position relative to 0 (the blank space) */
std::vector<int> updateState(char, node);

// determine heuristic value based on node's state (board)
int updateHeuristic(std::vector<int>, node);

// get index value for manhattan heurstic function
int getIndex(std::vector<int>, int);

// determine manhattan heuristic value based on node's state (board)
int updateMHeuristic(std::vector<int>, node);

// configure the neighbor node for the a* search
void configureNeighbor(node &, node &, std::vector<int> &,
    std::vector<node> &, std::vector<node> &, char);

// configure the neighbor node for the dfbb search
void configureNeighborDFBB(node &, node &, std::vector<int> &,
    char, std::vector<node> &, std::vector<node> &, int);

// do a* search
void aStarSearch(node &, node &, std::vector<int> &, std::vector<node> &,
    std::vector<node> &);

// do dbff search
void dfbbSearch(node &, node &, std::vector<int> &, int, std::vector<node> &);

void outputStates(vector<int> &, vector<int> &);

/* program will use the out of place heuristic if value = 0
 * and the manhattan heuristic if value = 1 */
int heuristicType = 1;

int main()
{
    clock_t tStart = clock();

    // create the open list of nodes, initially empty
    std::vector<node> openList;

    // create the closed list of nodes, initially empty
    std::vector<node> closedList;

    // EASY (out of place: ~0.001 seconds) (manhattan: ~0.002 seconds)
    int startStateArray[9] = {1, 3, 4, 8, 6, 2, 7, 0, 5};

    // MEDIUM (out of place: ~0.005 seconds) (manhattan: ~0.005 seconds)
    //int startStateArray[9] = {2, 8, 1, 0, 4, 3, 7, 6, 5};

    // HARD (out of place: ~0.035 seconds) (manhattan: ~0.012 seconds)
    //int startStateArray[9] = {2, 8, 1, 4, 6, 3, 0, 7, 5};

    // WORST (out of place: long) (manhattan: ~229.237 seconds)
    //int startStateArray[9] = {5, 6, 7, 4, 0, 8, 3, 2, 1};

    // GOAL
    int endStateArray[9] =  {1, 2, 3, 8, 0, 4, 7, 6, 5};

    // initialize state vectors
    std::vector<int> startState;
    std::vector<int> endState;

    // fill state vectors
    for(int i = 0; i < 9; i++)
    {
        startState.push_back(startStateArray[i]);
        endState.push_back(endStateArray[i]);
    }

    // neighbor node to be updated with info later
    node neighborNode;

    // first node
    node currentNode;

    // first node start state
    currentNode.state = startState;

     // first node path cost
    currentNode.pathCost = 0;

     // position of 0 (blank value) in state
    currentNode.blankPosition = findZero(startState);

    if(heuristicType == 0)
    {
        // set first node heuristic
        currentNode.heuristic = updateHeuristic(endState, currentNode);
    }
    else
    {
        currentNode.heuristic = updateMHeuristic(endState, currentNode);
    }

    outputStates(startState, endState);

    // a* search
    aStarSearch(neighborNode, currentNode, endState, closedList, openList);

    // dfbb search
    //dfbbSearch(neighborNode, currentNode, endState,
    //    currentNode.heuristic, closedList);

    cout << endl << "Time: " << ((double)(clock() - tStart) / CLOCKS_PER_SEC)
        << " seconds" << endl;

    return 0;
}

void outputStates(vector<int> & startState, vector<int> & endState)
{
    cout << "Start state: ";

    for(int i = 0; i < 9; i++)
    {
        cout << startState.at(i) << " ";
    }

    cout << endl << "End state: ";

    for(int i = 0; i < 9; i++)
    {
        cout << endState.at(i) << " ";
    }

    cout << endl << endl;
}

bool checkNeighbor(char option, node currentNode)
{
    bool validNeighbor = 0;

    if(option == 'u')
    {
        if(currentNode.blankPosition - 3 >= 0)
        {
            validNeighbor = 1;
        }
    }

    if(option == 'd')
    {
        if(currentNode.blankPosition + 3 <= 8)
        {
            validNeighbor = 1;
        }
    }
    if(option == 'l')
    {
        if(currentNode.blankPosition % 3 != 0)
        {
            validNeighbor = 1;
        }
    }

    if(option == 'r')
    {
        if(currentNode.blankPosition + ((currentNode.blankPosition + 1) % 3)
            > currentNode.blankPosition)
        {
            validNeighbor = 1;
        }
    }

    return validNeighbor;
}

bool checkList(std::vector<node> list, node neighborNode)
{
    bool inList = 0;

    for(unsigned int i = 0; i < list.size(); i++)
    {
        if(list.at(i).state == neighborNode.state
            && list.at(i).move == neighborNode.move)
        {
            inList = 1;
        }
    }

    return inList;
}

node getLowestOpenList(std::vector<node> list)
{
    int lowest = INT_MAX;
    node lowestF;

    for(unsigned int i = 0; i < list.size(); i++)
    {
        if((list.at(i).heuristic + list.at(i).pathCost) <= lowest)
        {
            lowest = list.at(i).heuristic + list.at(i).pathCost;
            lowestF = list.at(i);
        }
    }

    return lowestF;
}

int findZero(std::vector<int> state)
{
    int zero;

    for(unsigned int i = 0; i < state.size(); i++)
    {
        if(state.at(i) == 0)
        {
            zero = i;
        }
    }

    return zero;
}

std::vector<int> updateState(char option, node n)
{
    std::vector<int> newState;
    int temp[9];

    if(option == 'u')
    {
        for(unsigned int i = 0; i < n.state.size(); i++)
        {
            if((int) i == n.blankPosition)
            {
                temp[i] = n.state.at(n.blankPosition - 3);
            }
            else if((int)i ==  n.blankPosition - 3)
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
        for(unsigned int i = 0; i < n.state.size(); i++)
        {
            if((int) i == n.blankPosition)
            {
                temp[i] = n.state.at(n.blankPosition + 3);
            }
            else if((int) i == n.blankPosition + 3)
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
        for(unsigned int i = 0; i < n.state.size(); i++)
        {
            if((int) i == n.blankPosition)
            {
                temp[i] = n.state.at(n.blankPosition - 1);
            }
            else if((int) i == n.blankPosition - 1)
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
        for(unsigned int i = 0; i < n.state.size(); i++)
        {
            if((int) i == n.blankPosition)
            {
                temp[i] = n.state.at(n.blankPosition + 1);
            }
            else if((int) i == n.blankPosition + 1)
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
        newState.push_back(temp[i]);
    }

    return newState;
}

int updateHeuristic(std::vector<int> h, node n)
{
    int heuristic = 0;

    for(unsigned int i = 0; i < h.size(); i++)
    {
        if(h.at(i) != n.state.at(i))
        {
            heuristic++;
        }
    }

    return heuristic;
}

int getIndex(std::vector<int> vector, int value)
{
    int index;

    for(unsigned int i = 0; i < vector.size(); i++)
    {
        if(vector.at(i) == value)
        {
            index = i;
        }
    }

    return index;
}

int updateMHeuristic(std::vector<int> endState, node n)
{
    int heuristic = 0;
    int stateDistance;

    for(unsigned int i = 0; i < 9; i++)
    {
        stateDistance = abs(getIndex(endState, i) - getIndex(n.state, i));

        switch(stateDistance)
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
            if(abs(getIndex(endState, i) || getIndex(n.state, i)) == 2)
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

void configureNeighbor(node &neighborNode, node &currentNode,
    std::vector<int> &endState, std::vector<node> &closedList,
    std::vector<node> &openList, char option)
{
    // update neighbor node board state
    neighborNode.state = updateState(option, currentNode);
    neighborNode.move = option;

    // find position of blank space in neighbor node
    neighborNode.blankPosition = findZero(neighborNode.state);

    // update neighbor node heuristic values
    if(heuristicType == 0)
    {
        neighborNode.heuristic = updateHeuristic(endState, neighborNode);
    }
    else
    {
        neighborNode.heuristic = updateMHeuristic(endState, neighborNode);
    }

    if(checkList(closedList, neighborNode)
        && currentNode.pathCost < neighborNode.pathCost)
    {
        // move the node from closed list to open list
        for(unsigned int i = 0; i < closedList.size(); i++)
        {
            if(closedList.at(i).state == neighborNode.state)
            {
                closedList.erase(closedList.begin() + i);
            }
        }

        // update the neighbor with the new, lower, g value
        neighborNode.pathCost = currentNode.pathCost;

        // change the neighbor's parent to our current node
        neighborNode.parent = &currentNode;

        // move the node to open list
        openList.push_back(neighborNode);
    }

    if(checkList(openList, neighborNode)
        && currentNode.pathCost < neighborNode.pathCost)
    {
        // update the neighbor with the new, lower, g value
        neighborNode.pathCost = currentNode.pathCost;

        // change the neighbor's parent to our current node
        neighborNode.parent = &currentNode;
    }

    if(checkList(openList, neighborNode) == 0
        && checkList(closedList, neighborNode) == 0)
    {
        // set its g value
        neighborNode.pathCost = 1 + currentNode.pathCost;

        // add the neighbor to the open list
        openList.push_back(neighborNode);
    }

    if(neighborNode.heuristic == 0)
    {
        cout << endl;
    }

    switch(option)
    {
    case 'r':
        cout << "(RIGHT) ";
        break;
    case 'd':
        cout << "(DOWN) ";
        break;
    case 'l':
        cout << "(LEFT) ";
        break;
    case 'u':
        cout << "(UP) ";
        break;
    default:
        break;
    }

    cout << "(" << neighborNode.pathCost << " + "
        << neighborNode.heuristic << ") ";

    cout << "(OPEN LIST " << openList.size()
        << ") (CLOSED LIST " << closedList.size() << ") [ ";

    for(int i = 0; i < 9; i++)
    {
        cout << neighborNode.state.at(i) << " ";
    }

    cout << "]";

    if(neighborNode.heuristic == 0)
    {
        cout << "\n^ WINNER\n";
    }

    cout << "\n";
}

void configureNeighborDFBB(node &neighborNode, node &currentNode,
    std::vector<int> &endState, char option, std::vector<node> &closedList,
    std::vector<node> &openList, int bestScore)
{
    // update neighbor node board state
    neighborNode.state = updateState(option, currentNode);
    neighborNode.move = option;

    // find position of blank space in neighbor node
    neighborNode.blankPosition = findZero(neighborNode.state);

    // update neighbor node heuristic values
    if(heuristicType == 0)
    {
        neighborNode.heuristic = updateHeuristic(endState, neighborNode);
    }
    else
    {
        neighborNode.heuristic = updateMHeuristic(endState, neighborNode);
    }

    if(neighborNode.heuristic <= bestScore)
    {
        if(checkList(openList, neighborNode) == 0
            && checkList(closedList, neighborNode) == 0)
        {
            // set its g value
            neighborNode.pathCost = 1 + currentNode.pathCost;

            // add the neighbor to the open list
            openList.push_back(neighborNode);
        }
    }

    if(neighborNode.heuristic == 0)
    {
        cout << endl;
    }

    switch(option)
    {
    case 'r':
        cout << "(RIGHT) ";
        break;
    case 'd':
        cout << "(DOWN) ";
        break;
    case 'l':
        cout << "(LEFT) ";
        break;
    case 'u':
        cout << "(UP) ";
        break;
    default:
        break;
    }

    cout << "(" << neighborNode.pathCost << " + "
        << neighborNode.heuristic << ") [ ";

    for(int i = 0; i < 9; i++)
    {
        cout << neighborNode.state.at(i) << " ";
    }

    cout << "]";

    if(neighborNode.heuristic == 0)
    {
        cout << "\n^ WINNER\n";
    }

    cout << "\n";
}

void aStarSearch(node &neighborNode, node &currentNode,
    std::vector<int> &endState, std::vector<node> &closedList,
    std::vector<node> &openList)
{
    int nodeCount = 0;

    // output results title
    cout << "(Move made) (G value + H value) (Open lists) " <<
        "(Closed lists) [Board state]" << endl;

    // create the open list of nodes, initially containing only starting node
    openList.push_back(currentNode);

    while(neighborNode.state != endState && currentNode.state != endState)
    {
        /* consider the best node in the open list
         *  (the node with the lowest f value)*/
        currentNode = getLowestOpenList(openList);

        // remove current node from open list
        for(unsigned int i = 0; i < openList.size(); i++)
        {
            if(openList.at(i).state == currentNode.state)
            {
                openList.erase(openList.begin() + i);
            }
        }

        /* move the current node to the closed list and
         * consider all of its neighbors*/
        closedList.push_back(currentNode);

        if(checkNeighbor('r', currentNode))
        {
            configureNeighbor(neighborNode, currentNode, endState,
                closedList, openList, 'r');
        }

        if(checkNeighbor('d', currentNode))
        {
            configureNeighbor(neighborNode, currentNode, endState,
                closedList, openList, 'd');
        }

        if(checkNeighbor('l', currentNode))
        {
            configureNeighbor(neighborNode, currentNode, endState,
                closedList, openList, 'l');
        }

        if(checkNeighbor('u', currentNode))
        {
            configureNeighbor(neighborNode, currentNode, endState,
                closedList, openList, 'u');
        }

        nodeCount++;
    }

    cout << endl << "# Nodes: " << nodeCount;
}

void dfbbSearch(node &neighborNode, node &currentNode,
    std::vector<int> &endState, int bound, std::vector<node> &closedList)
{
    int nodeCount = 0;

    // score of best solution so far
    int bestScore = bound;

    // Let open list Q = {S}
    std::vector<node> openListDBB;

    openListDBB.push_back(currentNode);

    // While Q is not empty
    while(openListDBB.size() != 0)
    {
        currentNode = getLowestOpenList(openListDBB);

        // remove current node from open list
        for(unsigned int i = 0; i < openListDBB.size(); i++)
        {
            if(openListDBB.at(i).state == currentNode.state
                && openListDBB.at(i).move == currentNode.move)
            {
                openListDBB.erase(openListDBB.begin() + i);
            }
        }

        closedList.push_back(currentNode);

        if(currentNode.heuristic < bestScore)
        {
            bestScore = currentNode.heuristic;
        }

        // For each child node n do:
        if(checkNeighbor('r', currentNode))
        {
            configureNeighborDFBB(neighborNode, currentNode, endState,
                'r', closedList, openListDBB, bestScore);
        }

        if(checkNeighbor('d', currentNode))
        {
            configureNeighborDFBB(neighborNode, currentNode, endState,
                'd', closedList, openListDBB, bestScore);
        }

        if(checkNeighbor('l', currentNode))
        {
            configureNeighborDFBB(neighborNode, currentNode, endState,
                'l', closedList, openListDBB, bestScore);
        }

        if(checkNeighbor('u', currentNode))
        {
            configureNeighborDFBB(neighborNode, currentNode, endState,
                'u', closedList, openListDBB, bestScore);
        }

        nodeCount++;
    }

    cout << endl << "# Nodes: " << nodeCount;
    cout << endl << "closeList: " << closedList.size();
}
