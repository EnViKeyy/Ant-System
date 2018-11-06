#include <stdlib.h>
#include <stdio.h>
#include "ant.h"

void main()
{
    int i, j;
    int n = 5;
    int amount = 25;
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
        updating_pheromone(ant, amount, n, pheromone_matrix);
        printf("%d\n", i);
        // if(i == 0)
        // {
            printf("melhor caminho: ");
            for(j = 0; j < n; j++)
                printf("%d - ", best_way[j]);
            printf("%d\n", best_way[j]);

            printf("melhor distancia: ");
            printf("%f\n\n", best_distance);
        // }
    }

    printf("\n");
    // for(i = 0; i < amount; i++)
    // {
    //     printf("ant[%d]->way => %.2f\n", i, ant[i]->way_distance);
    //     // printf("\t\tant[%d]->way => %.2f\t", i+1, ant[i+1]->way_distance);
    //     // printf("\t\tant[%d]->way => %.2f\n", i+2, ant[i+2]->way_distance);
    //     for(j = 0; j < n; j++)
    //     {
    //         printf("ant[%d]->way[%d] => %d\n", i, j, ant[i]->way[j]);
    //         // printf("\t\tant[%d]->way[%d] => %d\t", i+1, j, ant[i+1]->way[j]);
    //         // printf("\t\tant[%d]->way[%d] => %d\n", i+2, j, ant[i+2]->way[j]);
    //     }
    //     printf("ant[%d]->way[%d] => %d\n\n", i, j, ant[i]->way[j]);
    //     // printf("\t\tant[%d]->way[%d] => %d\t", i+1, j, ant[i+1]->way[j]);
    //     // printf("\t\tant[%d]->way[%d] => %d\n\n", i+2, j, ant[i+2]->way[j]);
    // }

    printf("melhor caminho: ");
    for(i = 0; i < n; i++)
        printf("%d - ", best_way[i]);
    printf("%d\n", best_way[i]);

    printf("melhor distancia: ");
    printf("%f\n\n", best_distance);

    for(i = 0; i < amount; i++)
    {
        free(ant[i]);
        ant[i] = NULL;
    }

    printf("\nFormigas esterminadas sem dangling pointers?\n\t%s\n\n", ant[0] == NULL && ant[amount] == NULL ? "Sure!" : "Wah Wah Wah Waaaaaaaah!");

}