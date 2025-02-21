#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <list>
#include <queue>
#include <sstream>
#include <stack>
#include <climits>

#include "Jug.h"
using namespace std;

// Constructor
Jug::Jug(int Ca, int Cb, int N,int cfA,int cfB,int ceA,int ceB, int cpAB,int cpBA) {
    this->capacityA = Ca;
    this->capacityB = Cb;
    this->goal = N;
    this->costFillA = cfA;
    this->costFillB = cfB;
    this->costEmptyA = ceA;
    this->costEmptyB = ceB;
    this->costPourAB = cpAB;
    this->costPourBA = cpBA;

    if (!(Ca > 0 && Ca <= Cb) || !(Cb > goal && Cb <= 1000)) {
        return;
    }
    if (cfA < 0 || cfB < 0 || ceA < 0 || ceB < 0 || cpAB < 0 || cpBA < 0) {
        return;
    }
    createGraph(adjList);
}

// Copy Constructor
Jug::Jug(const Jug& other) {
    capacityA = other.capacityA;
    capacityB = other.capacityB;
    goal = other.goal;
    costFillA = other.costFillA;
    costFillB = other.costFillB;
    costEmptyA = other.costEmptyA;
    costEmptyB = other.costEmptyB;
    costPourAB = other.costPourAB;
    costPourBA = other.costPourBA;
    adjList = other.adjList; // std::vector has its own copy constructor
}

// Copy Assignment Operator
Jug& Jug::operator=(const Jug& other) {
    if (this == &other) {
        return *this; // handle self assignment
    }
    capacityA = other.capacityA;
    capacityB = other.capacityB;
    goal = other.goal;
    costFillA = other.costFillA;
    costFillB = other.costFillB;
    costEmptyA = other.costEmptyA;
    costEmptyB = other.costEmptyB;
    costPourAB = other.costPourAB;
    costPourBA = other.costPourBA;
    adjList = other.adjList; // std::vector has its own copy assignment operator
    return *this;
}

// Destructor
Jug::~Jug() {
    // vector will clean up itself
}

// Finds shortest paths from starting vertex to all other vertices in the graph
void Jug::relax() {
    queue<Vertex*> unQ;
    for (unsigned i = 0; i < adjList.size(); ++i) { //initialize all adj elements
        adjList.at(i).distance = INT_MAX;
        adjList.at(i).prev = 0;
        unQ.push(&adjList.at(i));
    }
    adjList.at(0).distance = 0;

    while (!unQ.empty()) { //fixing/relaxing
        Vertex* curr = unQ.front();
        unQ.pop();

        for (unsigned i = 0; i < 6; ++i) {
            int edgeW = curr->neighbor[i].second;
            int alt = curr->distance + edgeW;

            //relaxing
            int A = curr->neighbor[i].first;
            if (alt < adjList.at(A).distance) { //if new path is shorter
                adjList.at(A).distance = alt;
                adjList.at(A).prev = curr;
            }
            //else, do nothing
        }
    }
}

// Checks whether a given vertex state exists in the graph
bool Jug::solutionExists(Vertex &vert) {
    for (unsigned i = 0; i < adjList.size(); ++i) {
        if (adjList.at(i).state.first == vert.state.first && adjList.at(i).state.second == vert.state.second) {
            return true;
        }
    }
    return false;
}

// Finds the optimal sequence of operations to achieve the goal state
int Jug::solve(string &solution) {
    stringstream ss;

    if (costFillA < 0 || costFillB < 0 || costEmptyA < 0 || costEmptyB < 0 || costPourAB < 0 || costPourBA < 0) {
        solution = ""; // no solution, return -1 because cannot operate on negative weights
        return -1;
    }

    if (capacityA <= 0 || capacityA > capacityB || capacityB <= 0) {
        solution = "";
        return -1;
    }

    if (goal > capacityB || capacityB > 1000 || goal > 1000) {
        solution = "";
        return -1;
    }

    int index = 0;
    bool indexAssigned = false;
    for (unsigned i = 0; i < adjList.size(); ++i) {
        if (adjList.at(i).state.first == 0 && adjList.at(i).state.second == goal) {
            index = i;
            indexAssigned = true;
        }
    }

    if (!indexAssigned) {
        solution = "";
        return 0;
    }

    relax(); 

    stack<Vertex*> vertexStack;
    Vertex *curr = &adjList.at(index);

    
    while (curr != 0) {
        vertexStack.push(curr);
        curr = curr->prev;
    }

    while (vertexStack.size() - 1 != 0) {
        curr = vertexStack.top();
        vertexStack.pop();

        Vertex* prior = vertexStack.top();

        if (&adjList.at(curr->neighbor[0].first) == prior) {
            ss << "fill A" << endl;
        }
        if (&adjList.at(curr->neighbor[1].first) == prior) {
            ss << "fill B" << endl;
        }
        if (&adjList.at(curr->neighbor[2].first) == prior) {
            ss << "empty A" << endl;
        }
        if (&adjList.at(curr->neighbor[3].first) == prior) {
            ss << "empty B" << endl;
        }
        if (&adjList.at(curr->neighbor[4].first) == prior) {
            ss << "pour A B" << endl;
        }
        if (&adjList.at(curr->neighbor[5].first) == prior) {
            ss << "pour B A" << endl;
        }
    }
    ss << "success " << adjList.at(index).distance; //print shortest distance set by relax
    solution = ss.str();

    return 1; //valid solution found, returning 1
}

// Locates the given vertex state in the adjacency list
int Jug::locate(Vertex &vert) {
    for (unsigned i = 0; i < adjList.size(); ++i) {
        if (adjList.at(i).state.first == vert.state.first
            && adjList.at(i).state.second == vert.state.second) {
            return i;
        }
    }
    return -1;
}

// Updates the state of a vertex by filling jug A to its max capacity
void Jug::fillA(Vertex &vert) {
    vert.state.first = capacityA;
    return;
}

// Updates the state of a vertex by filling jug B to its maximum capacity
void Jug::fillB(Vertex &vert) {
    vert.state.second = capacityB;
    return;
}

// Pours water from jug A to B until either jug A is empty or jug B is full
void Jug::pourAB(Vertex &vert) {
    while (vert.state.first != 0) {
        if (vert.state.second == capacityB) {
            return;
        }
        vert.state.first--;
        vert.state.second++;
    }
    return;
}

// Pours water from jug B to jug A until either jug B is empty or jug A is full
void Jug::pourBA(Vertex &vert) {
    while (vert.state.second != 0) {
        if (vert.state.second == capacityB) {
            return;
        }
        vert.state.second--;
        vert.state.first++;
    }
    return;
}

// empties jug A
void Jug::emptyA(Vertex &vert) {
    vert.state.first = 0;
    return;
}

// empties jug B
void Jug::emptyB(Vertex &vert) {
    vert.state.second = 0;
    return;
}

// Constructs a graph representing all possible states of the jugs and their
void Jug::createGraph(vector<Vertex> &vert) { //vertices
    Vertex v;
    Vertex init;
    vert.push_back(v);

    for (unsigned i = 0; i < vert.size(); ++i) {
        //  cout << i << endl;
        init = vert.at(i);
        Vertex vert1 = init;
        Vertex vert2 = init;
        Vertex vert3 = init;
        Vertex vert4 = init;
        Vertex vert5 = init;
        Vertex vert6 = init;

        fillA(vert1); 
        fillB(vert2);
        emptyA(vert3);
        emptyB(vert4);
        pourAB(vert5);
        pourBA(vert6);

        if(!solutionExists(vert1)) {
            vert.push_back(vert1);
        }
        if(!solutionExists(vert2)) {
            vert.push_back(vert2);
        }
        if(!solutionExists(vert3)) {
            vert.push_back(vert3);
        }
        if(!solutionExists(vert4)) {
            vert.push_back(vert4);
        }
        if(!solutionExists(vert5)) {
            vert.push_back(vert5);
        }
        if(!solutionExists(vert6)) {
            vert.push_back(vert6);
        }

                                        //location index, cost
        init.neighbor[0] = pair<int,int>(locate(vert1),costFillA);
        init.neighbor[1] = pair<int,int>(locate(vert2),costFillB);
        init.neighbor[2] = pair<int,int>(locate(vert3),costEmptyA);
        init.neighbor[3] = pair<int,int>(locate(vert4),costEmptyB);
        init.neighbor[4] = pair<int,int>(locate(vert5),costPourAB);
        init.neighbor[5] = pair<int,int>(locate(vert6),costPourBA);

        vert.at(i) = init;
    }
}