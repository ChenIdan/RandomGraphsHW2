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
int click_size_new_heuristic(Random_Graph *G);
float click_prob(unsigned int n, unsigned int k);
float click_prob(unsigned int n, unsigned int k);
float  heuristic_expected_click_size(int n);
float  heuristic_expected_click_size2(int n);

#endif /*RANDOM_GRAPHS*/
