#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node
{
	unsigned int vertex;
	struct Node *next;
} Node;

typedef struct Graph
{
	unsigned int size;
	Node **adj_list;
} Graph;

Graph *graph()
{
	Graph *g = malloc(sizeof(Graph));
	g->size = 0;
	g->adj_list = NULL;
	return g;
}

Node *node(unsigned int vertex)
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

	for (unsigned int i = 0; i < g->size - 1; ++i)
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

void graph_delete_node_at(Graph *g, unsigned int index)
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

	for (unsigned int i = 0; i < g->size; i++)
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
	for (unsigned int i = index; i < g->size - 1; ++i)
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

unsigned int graph_get_connections_of_node(Graph *g, unsigned int index)
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

	unsigned int connections = 0;

	Node *temp = g->adj_list[index];
	while (temp != NULL)
	{
		connections++;
		temp = temp->next;
	}

	return connections;
}

int main(void)
{
	Graph *g = graph();

	graph_insert_dnode(g);
	graph_insert_cnode(g);
	graph_insert_dnode(g);
	graph_insert_cnode(g);
	graph_insert_dnode(g);
	graph_insert_cnode(g);

	for (unsigned int i = 0; i < g->size; ++i)
	{
		if (graph_get_connections_of_node(g, i) % 3)
		{
			graph_delete_node_at(g, i);
		}
	}

	fprintf(stdout, "Remaining nodes: %u\n", g->size);

	printf("Hello world what the fuck\n");
	return 0;
}
