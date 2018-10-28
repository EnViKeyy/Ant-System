#include <stdlib.h>
#include <stdio.h>
#include "ant.h"

void main()
{
    int i, j;
    int n = 5;
    int amount = 10;
    int max_interarions = 100;
    float distance_matrix[n][n];
    float pheromone_matrix[n][n];
    float information_matrix[n][n];
    float best_distance;
    int best_way[n+1];
    ant *ant[amount];

    distance(n, distance_matrix);
    pheromone(n, pheromone_matrix);
    information(n, information_matrix, pheromone_matrix, distance_matrix);

    for(i = 0; i < amount; i++)
        ant[i] = initialize_ant(amount, n);

    for(i = 0; i < max_interarions; i++)
    {
        fetch_best_way(ant, n, distance_matrix, information_matrix, amount);
        updating_statistics(ant, best_way, &best_distance, amount, n);
        updating_pheromone(ant, n, pheromone_matrix);
    }

    printf("\n");
    for(i = 0; i < amount; i += 5)
    {
        printf("\t\tant[%d]->way => %.2f\t", i, ant[i]->way_distance);
        printf("\t\tant[%d]->way => %.2f\t", i+1, ant[i+1]->way_distance);
        printf("\t\tant[%d]->way => %.2f\t", i+2, ant[i+2]->way_distance);
        printf("\t\tant[%d]->way => %.2f\t", i+3, ant[i+3]->way_distance);
        printf("\t\tant[%d]->way => %.2f\n", i+4, ant[i+4]->way_distance);
        for(j = 0; j < n; j++)
        {
            printf("\t\tant[%d]->way[%d] => %d\t", i, j, ant[i]->way[j]);
            printf("\t\tant[%d]->way[%d] => %d\t", i+1, j, ant[i+1]->way[j]);
            printf("\t\tant[%d]->way[%d] => %d\t", i+2, j, ant[i+2]->way[j]);
            printf("\t\tant[%d]->way[%d] => %d\t", i+3, j, ant[i+3]->way[j]);
            printf("\t\tant[%d]->way[%d] => %d\n", i+4, j, ant[i+4]->way[j]);
        }
        printf("\t\tant[%d]->way[%d] => %d\t", i, j, ant[i]->way[j]);
        printf("\t\tant[%d]->way[%d] => %d\t", i+1, j, ant[i+1]->way[j]);
        printf("\t\tant[%d]->way[%d] => %d\t", i+2, j, ant[i+2]->way[j]);
        printf("\t\tant[%d]->way[%d] => %d\t", i+3, j, ant[i+3]->way[j]);
        printf("\t\tant[%d]->way[%d] => %d\n\n", i+4, j, ant[i+4]->way[j]);
    }

    printf("melhor caminho: ");
    for(i = 0; i < n; i++)
        printf("%d - ", best_way[i]);
    printf("%d\n", best_way[i]);

    printf("\nmelhor distancia: ");
    printf("%f\n\n", best_distance);

    for(i = 0; i < n; i++)
    {
        free(ant[i]);
        ant[i] = NULL;
    }

    printf("\nFormigas esterminadas sem dangling pointers?\n\t%s\n\n", ant[0] == NULL && ant[amount] == NULL ? "Sure!" : "Wah Wah Wah Waaaaaaaah!");

}