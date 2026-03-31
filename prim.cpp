//All procedures including main
#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>

struct edge{
    int conection1;
    int conection2;
    int weight;
    //bool visited = true;
};

struct points{
    std::unordered_set<int> pointsID;
    std::vector<bool> visited;
};

bool allVisited(points points){
    for(int i = 0; i < points.visited.size(); i++){
        if(!points.visited[i]){
            return false;
        }
    }
    return true;
}

void PrimsAlgorithm(int Vertices, int NumEdges, std::vector<edge>& edges, std::vector<edge>& visitedEdges, points& points) {
    int lastVisitedPoint = 0;
    int lowestWeight = 9999;
    int deletionIndex = 0;
    edge lowestWeightEdge;
    std::vector<edge> conectedEdges;
    for(int i = 0; i < NumEdges; i++){
        if(points.visited[edges[i].conection1] && !points.visited[edges[i].conection2] || !points.visited[edges[i].conection1] && points.visited[edges[i].conection2]){
            conectedEdges.push_back(edges[i]);
        }
    }
    if(conectedEdges.empty()){
        std::cout << "All points have been visited." << std::endl;
        return;
    }
    for(int i = 0; i < conectedEdges.size(); i++){
        if(conectedEdges[i].weight < lowestWeight){
            lowestWeight = conectedEdges[i].weight;
            lowestWeightEdge = conectedEdges[i];
            deletionIndex = i;
        }
    }
    visitedEdges.push_back(lowestWeightEdge);
    points.visited[lowestWeightEdge.conection2] = true;
    points.visited[lowestWeightEdge.conection1] = true;
    lastVisitedPoint = lowestWeightEdge.conection2;
    edges.erase(edges.begin() + deletionIndex);
    std::cout << "Visited edge: " << lowestWeightEdge.conection1 << " - " << lowestWeightEdge.conection2 << " with weight " << lowestWeightEdge.weight << std::endl;
    if(!allVisited(points)){
        PrimsAlgorithm(Vertices, NumEdges - 1, edges, visitedEdges, points);
    }
    
    
    
}

int main()
{
    int Vertices, Edges;
    int counter = 0;
    points points;
    std::cout << "Enter the number of vertices: ";
    std::cin >> Vertices;
    std::cout << "Enter the number of edges: ";
    std::cin >> Edges;
    std::vector<edge> EdgesList;
    edge e;
    while(std::cin >> e.conection1 >> e.conection2 >> e.weight){
        points.pointsID.insert(e.conection1);
        points.pointsID.insert(e.conection2);
        EdgesList.push_back(e);
        counter++;
        if(counter == Edges){
            break;
        }
    }
    for(int i = 0; i < Vertices; i++){
        points.visited.push_back(false);
    }
    points.visited[0] = true;
    PrimsAlgorithm(Vertices, Edges, EdgesList, std::vector<edge>(), points);
    return 0;
}

