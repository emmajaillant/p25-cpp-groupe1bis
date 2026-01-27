#include <iostream>
#include <vector>
#include <stdexcept>

struct Graph {

    int size;
    //Vertex* b;
    std::vector<Vertex*> v;
    void addEdge(int begin, int end, double value){
        if (begin > v.size or end > v.size){
            //créer un nouveau sommet
        }
        Edge* e = new Edge;
        e->begin = begin;
        e->end = end;
        e->value = value;

        v[begin]->edges.push_back(e);

    }

    void dfs(){}
    
    addvertex(int){
        
    };

};

struct Edge{
    int value;
    int begin;
    int end;
    void print(){
        std::cout<<"--"<<value<<"-->";
    }    

};

struct Vertex {
    name(indice);
    std::vector<Edge*>
    void print(){
        std::cout<<"--"<<value<<"-->";
    }
};

int main()
{
    Graph g;
    
    g.addEdge(2, 5, 17.9);
    g.addEdge(5, 3, 23.9);
    g.addEdge(3, 4, 16.9);
    g.addEdge(4, 0, 699.9); 
    
    g.dfs();
}