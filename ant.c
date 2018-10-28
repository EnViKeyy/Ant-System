#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include "ant.h"

ant *initialize_ant(int amount, int n)
{
    srand((unsigned int)time(NULL));

    int i, j, randon;

    ant *new_ant = (ant*) malloc(sizeof(ant));
    new_ant->way_distance = 0.0;
    for(i = 0; i <= n; i++)
    {
        randon = rand() % n;
        new_ant->way[i] = randon;
        for(j = 0; j < i; j++)
		{
			if(new_ant->way[j] == new_ant->way[i])
			{
                randon = rand() % n;
				new_ant->way[i] = randon;
				j = 0;
			}
		}
    }

    return new_ant;
}

void fetch_best_way(ant **ants, int n, float distance_matrix[][n], float information_matrix[][n], int amount)
{
    int i = 0;
    int step = 0;
    int j, k;

    for(k = 0; k < amount; k++)
        for(i = 0; i < n; i++)
            ants[k]->visited[i] = 0;
            
    for(k = 0; k < amount; k++, i++)
    {
        if(i > 4)
            i = 0;

        ants[k]->way[step] = i;
        ants[k]->visited[i] = 1;
    }

    while(step < n)
    {
        step++;
        for(k = 0; k < amount; k++)
            decision_rule(*ants[k], step, n, information_matrix);
    }

    for(k = 0; k < amount; k++)
    {
        ants[k]->way[n] = ants[k]->way[0];
        ants[k]->way_distance = calcule_way_distance(*ants[k], n, distance_matrix);
    }
}

void decision_rule(ant ant, int i, int n, float information_matrix[][n])
{
    int c = ant.way[i-1];
    float probability_sum = 0.0;
    int j, k;
    float probability_selection[n], randon, p;

    for(j = 0; j < n; j++)
    {
        if(ant.visited[j])
            probability_selection[j] = 0.0;
        else
        {
            probability_selection[j] = information_matrix[c][j];
            probability_sum += probability_selection[j];
        }
    }

    if(i > n)
        return;

    j = city_selection(probability_sum, probability_selection, n);
    change(ant, n, j, i);
}

int city_selection(float probability_sum, float probability_selection[], int n)
{
    srand((unsigned int)time(NULL));

    int max_mix = rand() % 100;
    int i, j;
    float p, randon;

    for (i = 0; i < max_mix; i++) 
        rand(); 

    randon = ((float)rand() / (float)RAND_MAX ) * probability_sum;
    j = 0;
    p = probability_selection[j];

    while(p < randon)
    {
        j++;
        p += probability_selection[j];
    }

    return j;
}

void change(ant ant, int n, int j, int i)
{
    int k, aux;

    aux = ant.way[i];
    ant.way[i] = j;

    for(k = 0; k < n; k++)
        if(j == ant.way[k])
            break;

    ant.way[i] = j;
    ant.way[k] = aux;
    ant.visited[j] = 1;
}

float calcule_way_distance(ant ant, int n, float distance_matrix[][n])
{
    int i, j;
    float sum_distance = 0.0;

    for(i = 0; i < n; i++)
        sum_distance += distance_matrix[ant.way[i]][ant.way[i+1]];

    return sum_distance;
}

void updating_statistics(ant **ants, int best_way[], float *best_distance, int amount, int n)
{
    int k;
    float best_way_distance = 999999;
    for(k = 0; k < amount; k++)
    {
        if(ants[k]->way_distance < best_way_distance)
        {
            copy(ants[k]->way, best_way, n);
            *best_distance = best_way_distance = ants[k]->way_distance;
        }
    }
}

void updating_pheromone(ant **ants, int n, float pheromone_matrix[][n])
{
    int k;
    evaporation(n, pheromone_matrix);

    for(k = 0; k < n; k++)
        deposit_pheromone(*ants[k], n, pheromone_matrix);
}

void evaporation(int n, float pheromone_matrix[][n])
{
    float p = 0.1;
    int i, j;
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            pheromone_matrix[i][j] *= (1 - p);
            pheromone_matrix[j][i] = pheromone_matrix[i][j];
        }
    }
}

void deposit_pheromone(ant ant, int n, float pheromone_matrix[][n])
{
    int i, j, l;
    float tal, Q = 1;
    tal = Q / ant.way_distance;

    for(i = 0; i < n; i++)
    {
        j = ant.way[i];
        l = ant.way[i+1];
        pheromone_matrix[j][l] += tal;
        pheromone_matrix[l][j] = pheromone_matrix[j][l];
    }
}

void copy(int way[], int best_way[], int n)
{
    int i;
    for(i = 0; i <= n; i++)
        best_way[i] = way[i];
}

void pheromone(int n, float pheromone_matrix[][n])
{
    int i, j;
    for(i = 0; i < n; i++)
        for(j = 0; j < n; j++)
            pheromone_matrix[i][j] = 0.1;
}

void distance(int n, float distance_matrix[][n])
{
    distance_matrix[0][0] = 0.0;
    distance_matrix[0][1] = 1.0;
    distance_matrix[0][2] = 2.2;
    distance_matrix[0][3] = 2.0;
    distance_matrix[0][4] = 4.1;

    distance_matrix[1][0] = 1.0;
    distance_matrix[1][1] = 0.0;
    distance_matrix[1][2] = 1.4;
    distance_matrix[1][3] = 2.2;
    distance_matrix[1][4] = 4.0;

    distance_matrix[2][0] = 2.2;
    distance_matrix[2][1] = 1.4;
    distance_matrix[2][2] = 0.0;
    distance_matrix[2][3] = 2.2;
    distance_matrix[2][4] = 3.4;

    distance_matrix[3][0] = 2.0;
    distance_matrix[3][1] = 2.2;
    distance_matrix[3][2] = 2.2;
    distance_matrix[3][3] = 0.0;
    distance_matrix[3][4] = 2.2;

    distance_matrix[4][0] = 4.1;
    distance_matrix[4][1] = 4.0;
    distance_matrix[4][2] = 3.2;
    distance_matrix[4][3] = 2.2;
    distance_matrix[4][4] = 0.0;
}

void information(int n, float information_matrix[][n], float pheromone_matrix[][n], float distance_matrix[][n])
{
    int i, j;
    float alpha = 0.9;
    float beta = 2;
    for(i = 0; i < n; i++)
        for(j = 0; j < n; j++)
            information_matrix[i][j] = distance_matrix[i][j] == 0.0 ? 0.0 : (pow(pheromone_matrix[i][j], alpha) * pow(1/distance_matrix[i][j], beta));
}
