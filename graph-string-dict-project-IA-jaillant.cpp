#include <string>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>
#include <unordered_map>
#include <set>
#include <limits>
#include <algorithm>
#include <functional>

class Graph;

class Edge {
    friend class Graph;
    friend class Vertex;
    class Vertex* destination;
    double weight;

    Edge(Vertex* dest, double w) : destination(dest), weight(w) {}
};

class Vertex {
    friend class Graph;
    std::string name;
    std::vector<Edge*> edges;

    explicit Vertex(std::string n) : name(std::move(n)) {}
    
    ~Vertex() {
        // Utilisation de std::for_each avec une lambda pour la destruction
        std::for_each(edges.begin(), edges.end(), [](Edge* e) { delete e; });
    }
};

class Graph {
private:
    std::vector<Vertex*> vertices;
    std::unordered_map<std::string, int> name_to_index;

    // Classe Matrix interne aplatie (1D) pour une meilleure localité de cache
    class Matrix {
    private: // Les données restent privées
        size_t size;
        std::vector<double> data;

    public: // <-- C'EST LE MOT MAGIQUE QUI MANQUAIT !
        Matrix() : size(0) {}
        
        void init(size_t n, double default_val) {
            size = n;
            data.assign(n * n, default_val);
        }
        
        // Surcharge de l'opérateur () pour accéder aux éléments comme mat(i, j)
        double& operator()(size_t row, size_t col) { return data[row * size + col]; }
        const double& operator()(size_t row, size_t col) const { return data[row * size + col]; }
    } adj_matrix;

    Vertex* get_or_create_vertex(const std::string& name) {
        auto it = name_to_index.find(name);
        if (it != name_to_index.end()) {
            return vertices[it->second];
        }
        Vertex* new_v = new Vertex(name);
        name_to_index.emplace(name, vertices.size());
        vertices.push_back(new_v);
        return new_v;
    }

public:
    Graph() = default;

    ~Graph() {
        for (Vertex* v : vertices) delete v;
    }

    // Désactivation de la copie (bonne pratique quand on gère des pointeurs bruts)
    Graph(const Graph&) = delete;
    Graph& operator=(const Graph&) = delete;

    void add_edge(const std::string& begin, const std::string& end, double value) {
        Vertex* v_begin = get_or_create_vertex(begin);
        Vertex* v_end = get_or_create_vertex(end);
        v_begin->edges.push_back(new Edge(v_end, value));
    }

    void dfs() {
        std::set<std::string> visited;
        std::cout << "DFS: ";

        // Fonction lambda récursive (nécessite std::function pour s'appeler elle-même)
        std::function<void(Vertex*)> explore = [&](Vertex* v) {
            visited.insert(v->name);
            std::cout << v->name << " ";
            for (Edge* e : v->edges) {
                if (!visited.count(e->destination->name)) {
                    explore(e->destination);
                }
            }
        };

        for (Vertex* v : vertices) {
            if (!visited.count(v->name)) explore(v);
        }
        std::cout << "\n";
    }

    void build_adjacency_matrix() {
        size_t n = vertices.size();
        constexpr double INF = std::numeric_limits<double>::infinity();
        
        adj_matrix.init(n, INF);

        for (size_t i = 0; i < n; ++i) {
            adj_matrix(i, i) = 0.0;
            for (Edge* e : vertices[i]->edges) {
                size_t j = name_to_index[e->destination->name];
                adj_matrix(i, j) = e->weight;
            }
        }
    }

    void floyd_warshall() {
        size_t n = vertices.size();
        for (size_t k = 0; k < n; ++k) {
            for (size_t i = 0; i < n; ++i) {
                for (size_t j = 0; j < n; ++j) {
                    adj_matrix(i, j) = std::min(adj_matrix(i, j), adj_matrix(i, k) + adj_matrix(k, j));
                }
            }
        }
    }
};

/*

EXPLICATIONS DU CODE GÉNÉRÉ PAR L'IA 


Ce code utilise plusieurs concepts du C++ moderne (C++11 et ultérieurs) qui 
diffèrent d'une implémentation classique vue en cours. Voici les explications :

1) La structure Matrix aplatie (1D) au lieu d'un tableau 2D :
   Au lieu d'utiliser std::vector<std::vector<double>>, l'IA utilise un seul 
   std::vector<double> de taille N*N. 
   - Pourquoi ? C'est beaucoup plus performant pour le processeur. Les données 
     sont contiguës en mémoire (meilleure "localité de cache").
   - Comment on y accède ? L'IA a surchargé l'opérateur () : `operator()(row, col)`. 
     L'indice réel dans le tableau 1D est calculé avec la formule `row * size + col`.
   - Note technique : Il a fallu ajouter "public:" dans cette sous-classe pour que 
     le graphe puisse utiliser ses méthodes (init, operator()).

2) std::move dans le constructeur de Vertex :
   `explicit Vertex(std::string n) : name(std::move(n)) {}`
   std::move permet de "voler" le contenu de la chaîne 'n' pour le mettre 
   directement dans l'attribut 'name', au lieu d'en faire une copie en mémoire. 
   C'est une optimisation classique en C++ moderne.

3) Suppression de la copie (Graph(const Graph&) = delete) :
   Comme la classe Graph gère manuellement sa mémoire avec `new` et `delete`, 
   si on copiait le graphe (ex: Graph g2 = g1;), on ne copierait que les pointeurs 
   (Shallow copy). À la fin du programme, le destructeur ferait un `delete` deux 
   fois sur les mêmes objets (Double Free). Le mot clé `= delete` interdit au 
   compilateur d'autoriser la copie de cet objet.

4) Les expressions Lambda dans le parcours DFS :
   Au lieu de créer une méthode privée récursive dans la classe Graph, l'IA a 
   créé une fonction locale directement dans `dfs()`. 
   `std::function<void(Vertex*)> explore = [&](Vertex* v) { ... };`
   - Le `[&]` (capture par référence) permet à cette sous-fonction d'accéder à 
     la variable `visited` qui est déclarée juste au-dessus.
   - On utilise std::function pour que la lambda puisse s'appeler elle-même (récursion).

5) std::min dans l'algorithme de Floyd-Warshall :
   Au lieu du classique `if (dist[i][k] + dist[k][j] < dist[i][j])`, l'IA 
   utilise la fonction standard `std::min` : 
   `mat(i, j) = std::min(mat(i, j), mat(i, k) + mat(k, j));`
   Cela rend le code plus compact et lisible.

6) std::for_each dans le destructeur de Vertex :
   `std::for_each(edges.begin(), edges.end(), [](Edge* e) { delete e; });`
   C'est l'équivalent fonctionnel d'une boucle `for` classique. Elle applique une 
   petite fonction lambda (qui fait un `delete`) sur chaque élément du vecteur `edges`.
*/