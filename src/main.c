#include <stdio.h>
#include <stdint.h>
#include <getopt.h>
#include <stdlib.h>
#include <math.h>

struct edge {
    int origin;
    int destiny;
};

struct edge *edge_new(int node_a, int node_b) {
    struct edge *new_edge = malloc(sizeof(*new_edge));
    if (new_edge) {
        new_edge->origin = node_a;
        new_edge->destiny = node_b;
    }
    return new_edge;
}


int main(int argc, char *argv[]) {
    uint8_t vertices = 0;
    struct edge **edges_array = NULL;


    const char * short_options = "v:e:";
    const struct option long_options[] = {
        { "vertices",    required_argument, 0, 'v' },
        { "edges",       required_argument, 0, 'e' },
        { NULL, 0, NULL, 0 }
    };

    int option, successful_inputs, i;
    int node_a, node_b;
    do {
        option = getopt_long(argc, argv, short_options, long_options, NULL);
        switch (option) {
        case 'v':
            successful_inputs = sscanf(optarg, "%hhd", &vertices);
            if (successful_inputs == 1) {
                printf("Se creará un grafo con %d vértices.\n", vertices);
                edges_array = malloc(vertices * sizeof(struct edge*)); /* Nada más creo el arreglo que guarda apuntadores a vértices xd. */
            }
            break;
        case 'e':
                i = 0;
            if (optarg[i++] == '{') {
                do {
                    successful_inputs = sscanf(&optarg[i], "(%d,%d)", &node_a, &node_b);
                    if (successful_inputs == 2) {
                        i += 5 + log10(node_a) + log10(node_b); /* Avanzamos la cantidad de caracteres que se pasó en los paréntesis. */
                        printf("Vertice %d conectado con vértice %d.\n", node_a, node_b);
                        edges_array[i] = edge_new(node_a, node_b);
                    }
                    else {
                        printf("Entrada no válida.\n");
                    }
                } while (optarg[i++] != '}');
            }
            else {
                printf("Sintaxis inválida.\n");
            }
        }
    } while (option != -1);

    return 0;
}
