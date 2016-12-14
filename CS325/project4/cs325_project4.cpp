#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <limits>
#include <math.h>

using namespace std;

struct vertex{
    int id;
    int x;
    int y;
};

struct result{
    vector<int> visited;        //Holds the IDs of each vertex visited, in order
    int distance;               //Total distance of path
};

//Gets the vertices from the input file
vector<struct vertex *> readFromFile(string fileName);

//Returns the distance between two vertices
int getDistance(struct vertex * a, struct vertex * b);

/* Returns a result struct of greedy shortest path from given starting point.
 * Starting point is the index of the vertex vector to start at.
 */
struct result * findPath(vector<struct vertex *> S, int startingPoint);

/* Runs the function above for all possible starting points and returns the
 * result struct with the shortest distance.
 */
struct result * findPathAll(vector<struct vertex *> vertices,int search_differential);

//Writes the results to file
void writeResults(struct result * r, string inputFileName);

int main(int argc, char *argv[]){

    string fileName;
    vector<struct vertex *> vertices;                   //The set of vertices read from the file
    struct result * bestResult;                         //Holds path length and order of shortest overall path


    //Check for proper arguments
    if(argc != 2){
        cout << "Usage: tsp <input filename>" << endl;
        return(1);
    }

    //Get vertices from file
    fileName = string(argv[1]);
    vertices = readFromFile(fileName);

    //Testing stuff
    /*
    cout << "Contents of vertex vector: << endl;
    for(int i = 0; i < vertices.size(); i++){
        cout << vertices[i]->id << " " << vertices[i]->x << " " << vertices[i]->y << endl;
    }/*
    /*
    cout << "Distance between 1 and 2: " << getDistance(vertices[0], vertices[1]) << endl
         << "Distance between 2 and 3: " << getDistance(vertices[1], vertices[2]) << endl;
    */

    int search_differential = 1;
    if (vertices.size() > 20)
    {
        search_differential = floor(vertices.size()/20);
    }
    //cout<<search_differential;
    clock_t tStart = clock();
    bestResult = findPathAll(vertices,search_differential);
    printf("Time taken: %.10fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);

    /*//More testing stuff
    cout << "Path length: " << bestResult->distance << endl;
    cout << "Order: " << endl;
    for(int i = 0; i < bestResult->visited.size(); i++){
        cout << bestResult->visited[i] << " ";
    }
    cout << endl;*/

    writeResults(bestResult, fileName);

    return 0;
}

//Function to read vertices from file
vector<struct vertex *> readFromFile(string fileName){
    ifstream fileIn(fileName.c_str());
    vector<struct vertex *> S;
    int id;
    int x;
    int y;

    //Create vertex for each line and add it to vector
    while(fileIn >> id >> x >> y){
        struct vertex * cur = new struct vertex();
        cur->id = id;
        cur->x = x;
        cur->y = y;
        S.push_back(cur);
    }
    fileIn.close();
    return S;
}

//Function to find the distance between two vertices
int getDistance(struct vertex * a, struct vertex * b){
    int result;
    //Get difference of x and y values
    double x = a->x - b->x;
    double y = a->y - b->y;
    //Square the differences
    x = x * x;
    y = y * y;
    x = x + y;      //Add them together (just use x to hold it)
    x = sqrt(x);    //Get square root
    return result = round(x);
}

struct result * findPath(vector<struct vertex *> S, int startingPoint){

    struct result * r = new struct result;
    r->distance = 0;

    //Special case for single vertex
    if(S.size() == 1){
        r->distance = 0;
        r->visited.push_back(S[0]->id);
        return r;
    }

    //Special case for 2 vertices
    if(S.size() == 2){
        r->distance = numeric_limits<int>::max();
        r->visited.push_back(S[0]->id);
        r->visited.push_back(S[1]->id);
        return r;
    }

    //Set current vertex
    struct vertex * curVertex = S[startingPoint];

    //Swap curVertex to beginning of vector to make iteration easier
    S[startingPoint] = S[0];
    S[0] = curVertex;

    //Save copy of first vertex so distance from last element can be determined later
    struct vertex * startVertex = S[0];

    //"Pull" starting point (now first element) from vector and place in result
    r->visited.push_back(S[0]->id);
    S[0] = NULL;

    //Find nearest neighbor of each element beginning from starting point
    int shortestEdge;
    for(int i = 1; i < S.size(); i++){
        shortestEdge = 2000000000;
        int closestPos;     //Index of closest remaining neighbor
        int curDistance;    //Distance between curVertex and current comparison
        //Find the nearest remaining vertex to the current vertex
        for(int j = 0; j < S.size(); j++){
            //Compare vertices if not null
            if(S[j] != NULL){
                curDistance = getDistance(curVertex, S[j]);
                if(curDistance < shortestEdge){
                    shortestEdge = curDistance;     //Record new shortest edge
                    closestPos = j;                 //Record position of new shortest edge
                }
            }
        }
        /*Set curVertex to closest neighbor, add closest neighbor to result, remove from S*/
        curVertex = S[closestPos];
        r->visited.push_back(S[closestPos]->id);
        r->distance += shortestEdge;
        S[closestPos] = NULL;
    }

    /* After the above loop, curVertex should be the last element visited
     * Find distance between it and the start vertex and add that distance
     * to the result's path length*/
    shortestEdge = getDistance(curVertex, startVertex);
    r->distance += shortestEdge;
    //Finally, add the start vertex to the result - Edit, doesn't look like it's supposed to be added
    //r->visited.push_back(startVertex->id);

    return r;

}

struct result * findPathAll(vector<struct vertex *> S,int search_differential){
    struct result * curResult = new struct result;  //Holds current result
    struct result * bestResult = new struct result; //Holds the current best result
    bestResult->distance = 2000000000;              //Init to really big number

    //Call greedy shortest path algorithm on all possible starting points
    //Keep track of shortest result
/*
    int search_differential = 1;
    if (S.size() > 250)
    {
        search_differential = S.size() % 250;
        if (search_differential==0)
        {
            search_differential++;
        }
    }
*/

    for(int i = 0; i < S.size(); (i+=search_differential)){
        curResult = findPath(S, i);
        if(curResult->distance < bestResult->distance){
            bestResult = curResult;
        }
    }
    return bestResult;
}

void writeResults(struct result * r, string inputFileName){

    string fileName = inputFileName + ".tour";
    ofstream fileOut(fileName.c_str());

    fileOut << r->distance << endl;
    for(int i = 0; i < r->visited.size(); i++){
        fileOut << r->visited[i] << endl;
    }
    fileOut.close();
    return;
}
