// Group Members:
// Clarence Ignacio
// Gabriel Valderama 
// Jan Kevin Gerona
// Karl Joseph Logdat

#include <stdio.h>
#include <stdbool.h>

#define MAX_NODES 100

typedef struct {
    bool adjacency[MAX_NODES][MAX_NODES];
    int node_count;
} Graph;

void init_graph(Graph *g) {
    g->node_count = 0;
    for (int i = 0; i < MAX_NODES; ++i) {
        for (int j = 0; j < MAX_NODES; ++j) {
            g->adjacency[i][j] = false;
        }
    }
}

/*
 * disconnected node has no connections so just increment graph size
 */
void add_dc_node(Graph *g) {
    if (g->node_count > MAX_NODES) 
        return;

    g->node_count++;
}

/*
 * mark all nodes in the new node column and row as connected
 * to show connection
 */
void add_c_node(Graph *g) {
    if (g->node_count > MAX_NODES)
        return;

    for (int i = 0; i < g->node_count; ++i) {
        g->adjacency[g->node_count][i] = true;
        g->adjacency[i][g->node_count] = true;
    }
    g->node_count++;
}

/*
 * traverse row of @node and increment degree if connection is
 * seen (true value)
 */
int get_deg(Graph *g, int node) {
    int deg = 0;
    for (int i = 0; i < g->node_count; ++i) {
        if (g->adjacency[node][i])
            deg++;
    }
    return deg;
}

/*
 * using @get_deg(), create new array of bool values,
 * representing nodes and mark as true if node degree
 * is equal to @deg parameter.
 *
 * next, create new adjacency matrix, copy values of original
 * adjacency matrix if the current node is not in the remove 
 * list while keeping track of new adj list indeces.
 *
 * finalize new graph by setting new size and copying new adj
 * list to graph
 */
void remove_by_deg(Graph *g, int deg) {
    bool rem[MAX_NODES] = {false};
    int rem_count = 0;

    for (int i = 0; i < g->node_count; ++i) {
        int curr_node_deg = get_deg(g, i);
        if (curr_node_deg % deg == 0) {
            rem[i] = true;
            rem_count++;
        }
    }

    if (rem_count == 0)
        return;

    bool new_adjacency[MAX_NODES][MAX_NODES] = {false};
    int new_index = 0;

    for (int i = 0; i < g->node_count; ++i) {
        if (!rem[i]) {
            int new_j = 0;
            for (int j = 0; j < g->node_count; ++j) {
                if (!rem[j]) {
                    new_adjacency[new_index][new_j] = g->adjacency[i][j];
                    new_j++;
                }
            }
            new_index++;
        }
    }

    g->node_count -= rem_count;
    for (int i = 0; i < g->node_count; ++i) {
        for (int j = 0; j < g->node_count; ++j) {
            g->adjacency[i][j] = new_adjacency[j][i];
        }
    }
}

/*
 * process directive list using functions defined above
 */
int process_directives(int directives[], int dir_count) {
    Graph g;
    init_graph(&g);

    for (int i = 0; i < dir_count; ++i) {
        int dir = directives[i];
        if (dir == 0) {
            add_dc_node(&g);
        } else if (dir == 1) {
            add_c_node(&g);
        } else {
            remove_by_deg(&g, dir);
        }
    }

    return g.node_count;
}

int main(void) {
    int directives[] = {0,0,1,1,0,0,1,1,2,5,7,0,1,1,1,1,1,0,1,1,1,1,1,1,1,1,8};
    printf("%d\n", process_directives(directives, 27));
}
