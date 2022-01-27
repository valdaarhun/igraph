/* -*- mode: C -*-  */

#include <igraph.h>
#include <stdio.h>

int main(){
    igraph_t g;
    igraph_vector_t types;
    igraph_real_t assortativity;

/* Create directed graph */
    igraph_small(&g, 10, IGRAPH_DIRECTED, 
                 0, 1, 0, 2, 0, 3, 0, 5,
                 3, 6,
                 4, 5,
                 6, 4, 6, 7,
                 7, 8, 7, 9,
                 8, 9,
                 9, 0,
                 -1);

    igraph_vector_init(&types, 0);
    igraph_degree(&g, &types, igraph_vss_all(), IGRAPH_ALL, /* No self-loops */ 0);

    igraph_assortativity(&g, &types, 0, &assortativity, /* ignore edge directions */ 0);
    printf("Assortativity of undirected graph = %g\n", assortativity);
    igraph_assortativity(&g, &types, 0, &assortativity, /* consider edge directions */ 1);
    printf("Assortativity of directed graph = %g\n", assortativity);
    
    igraph_vector_destroy(&types);
    igraph_destroy(&g);
}
