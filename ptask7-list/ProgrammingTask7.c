// Group Members:
// Clarence Ignacio
// Gabriel Valderama 
// Jan Kevin Gerona
// Karl Joseph Logdat

#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// rename unsigned int to u32 for ease of typing
typedef unsigned int u32;

typedef struct Node
{
	u32 vertex;
	struct Node *next;
} Node;

typedef struct Graph
{
	u32 size;
	Node **adj_list;
} Graph;

Graph *graph()
{
	Graph *g = malloc(sizeof(Graph));
	g->size = 0;
	g->adj_list = NULL;
	return g;
}

Node *node(u32 vertex)
{
	Node *n = malloc(sizeof(Node));
	n->vertex = vertex;
	n->next = NULL;
	return n;
}

// insert disconnected node to graph
void graph_insert_dnode(Graph *g)
{
	g->size++;

	g->adj_list = realloc(g->adj_list, g->size * sizeof(Node *));
	if (g->adj_list == NULL)
	{
		perror("Unable to allocate memory for adjacency list");
		exit(EXIT_FAILURE);
	}

	g->adj_list[g->size - 1] = NULL;
}

// insert node connected to all existing nodes
void graph_insert_cnode(Graph *g)
{
	Node *n = node(g->size);
	g->size++;

	g->adj_list = realloc(g->adj_list, g->size * sizeof(Node *));

	g->adj_list[g->size - 1] = NULL;

	for (u32 i = 0; i < g->size - 1; ++i)
	{
		Node *new_connection = node(g->size - 1);
		new_connection->next = g->adj_list[i];
		g->adj_list[i] = new_connection;

		Node *existing_connection = node(i);
		existing_connection->next = g->adj_list[g->size - 1];
		g->adj_list[g->size - 1] = existing_connection;
	}
}

void free_adjacency_list_entry(Node *list)
{
	while (list != NULL)
	{
		Node *temp = list;
		list = list->next;
		free(temp);
	}
}

void graph_delete_node_at(Graph *g, u32 index)
{
	// add proper checking g.size == 0 and g.size < index
	if (g->size == 0)
	{
		fprintf(stderr, "Cannot delete from empty graph\n");
		return;
	}

	if (g->size <= index)
	{
		fprintf(stderr, "Index out of Graph bounds\n");
		return;
	}

	free_adjacency_list_entry(g->adj_list[index]);

	for (u32 i = 0; i < g->size; i++)
	{
		if (i == index)
			continue;

		Node *current = g->adj_list[i];
		Node *prev = NULL;

		while (current != NULL)
		{
			if (current->vertex == index)
			{
				if (prev == NULL)
				{
					g->adj_list[i] = current->next;
				}
				else
				{
					prev->next = current->next;
				}

				free(current);
				break;
			}

			prev = current;
			current = current->next;
		}

		current = g->adj_list[i];
		while (current != NULL)
		{
			if (current->vertex > index)
			{
				current->vertex--;
			}
			current = current->next;
		}
	}

	// shift values starting at index
	for (u32 i = index; i < g->size - 1; ++i)
	{
		g->adj_list[i] = g->adj_list[i + 1];
	}

	Node **temp = realloc(g->adj_list, (g->size - 1) * sizeof(Node *));
	if (temp == NULL && g->size > 1)
	{
		perror("Failed to resize array after deletion");
		exit(EXIT_FAILURE);
	}

	g->adj_list = temp;
	g->size--;
}

u32 graph_get_connections_of_node(Graph *g, u32 index)
{
	if (g == NULL || g->adj_list == NULL)
	{
		fprintf(stderr, "Graph not initialized\n");
		return 0;
	}

	if (index >= g->size)
	{
		fprintf(stderr, "Index out of graph bounds\n");
		return 0;
	}

	u32 connections = 0;

	Node *temp = g->adj_list[index];
	while (temp != NULL)
	{
		connections++;
		temp = temp->next;
	}

	return connections;
}

/**
 * Function implementing task requirements. Accepts
 * `u32` as arguments (as indicated by the task)
 * and performs the following directives based on
 * array contents.
 *
 * Directives:
 * 	`0`: Add disconnected node
 * 	`1`: Add new node, connected to every existing node
 *  `m > 1`: Remove all nodes whose degree is divisible by `m`.
 * 	     Since `0` is divisible by all `m`, all disconnected
 * 	     nodes must be removed.
 */
u32 ptask_7(u32 directives[], u32 size)
{
	Graph *g = graph();

	for (u32 i = 0; i < size; ++i)
	{
		printf("\nProcessing directive %u: %u\n", i, directives[i]);

		if (directives[i] == 0)
		{
			graph_insert_dnode(g);
			printf("Added disconnected node. Graph size: %u\n", g->size);
			// Print degrees of all nodes
			for (u32 k = 0; k < g->size; k++)
			{
				printf("Node %u degree: %u\n", k, graph_get_connections_of_node(g, k));
			}
		}
		else if (directives[i] == 1)
		{
			graph_insert_cnode(g);
			printf("Added connected node. Graph size: %u\n", g->size);
			// Print degrees of all nodes
			for (u32 k = 0; k < g->size; k++)
			{
				printf("Node %u degree: %u\n", k, graph_get_connections_of_node(g, k));
			}
		}
		else
		{
			while (true)
			{
				bool any_deleted = false;
				// First find nodes with degree 0
				for (int j = 0; j < g->size; j++)
				{
					u32 degree = graph_get_connections_of_node(g, j);
					if (degree == 0)
					{ // Always delete disconnected nodes first
						graph_delete_node_at(g, j);
						any_deleted = true;
						break;
					}
				}
				if (any_deleted)
					continue;

				// Then find nodes with degree divisible by m
				for (int j = 0; j < g->size; j++)
				{
					u32 degree = graph_get_connections_of_node(g, j);
					if (degree != 0 && degree % directives[i] == 0)
					{
						graph_delete_node_at(g, j);
						any_deleted = true;
						break;
					}
				}
				if (!any_deleted)
					break;
			}
		}
	}

	printf("Final graph size: %u\n", g->size);
	printf("Final node degrees:\n");
	for (u32 k = 0; k < g->size; k++)
	{
		printf("Node %u degree: %u\n", k, graph_get_connections_of_node(g, k));
	}
	return g->size;
}

int main(void)
{
	u32 directives[] = {0, 0, 1, 1, 0, 0, 1, 1, 2, 5, 7, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 8};
	u32 directives_size = 27;

	u32 remaining = ptask_7(directives, directives_size);

	printf(
	    "Remaining nodes in the graph: %u\n",
	    remaining);

	return 0;
}
