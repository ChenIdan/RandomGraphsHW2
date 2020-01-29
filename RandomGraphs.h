#include <stdbool.h>
#ifndef RANDOM_GRAPH_H
#define RANDOM_GRAPH_H
typedef struct{
    bool **edges;
    bool initialized;
    unsigned long int n, e;
    double p;
    

}Random_Graph; 

Random_Graph* Create_Graph(int VertexNum, double p);
void print_graph(Random_Graph *G);
void init_graph(Random_Graph *G);
int click_size(Random_Graph* G);
long double  heuristic_expected_click_size(int n);
int click_size_new_heuristic(Random_Graph *G);
#endif /*RANDOM_GRAPH_H*/
