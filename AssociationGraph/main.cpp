// AssociationGraph.cpp : Defines the entry point for the application.
//

#include "Graph/Graph.h"


using namespace std;

template<typename Value>
void PrintGraph(Graph<Value>& g, const string& indent) {
    cout << indent << "graph (" << g.Size() << " members):" << endl;
    for (int i = 0; i < g.Size(); i++) {
        Vertex<Value>& v = g[i];
        cout << indent << "  " << v.GetValue() << " -> ";
        const auto& neighbors = v.GetAdjacentVertices();
        if (neighbors.empty()) {
            cout << "(none)";
        } else {
            for (const auto& n : neighbors) {
                cout << n.GetValue() << " ";
            }
        }
        cout << endl;
    }
}

template<typename Value>
void BuildLevel(Graph<Value>& current, int depth, int maxDepth) {
    string indent(maxDepth - depth, ' ');
    cout << indent << "-> depth " << (maxDepth - depth + 1) << "/" << maxDepth << endl;
    if (depth == 0) {
        cout << indent << "   base case, returning" << endl;
        return;
    }
    Graph<Value> next;
    for (int i = 65; i < 91; i++) {
        Vertex<Value> v(static_cast<Value>(i));
        next.AddMember(v);
    }
    PrintGraph(next, indent + "   ");
    BuildLevel(next, depth - 1, maxDepth);
    cout << indent << "<- leaving depth " << (maxDepth - depth + 1) << endl;
}

int main() {
    cout << "=== AssociationGraph recursive build ===" << endl;

    // Quick sanity test: build one small graph and print its adjacency.
    cout << "-- small test: A, B, C --" << endl;
    Graph<char> test;
    Vertex<char> a('A'), b('B'), c('C');
    test.AddMember(a);
    test.AddMember(b);
    test.AddMember(c);
    PrintGraph(test, "");

    cout << "-- recursive build (depth 3) --" << endl;
    Graph<char> g;
    BuildLevel(g, 3, 3);

    cout << "=== done ===" << endl;
    return 0;
}
