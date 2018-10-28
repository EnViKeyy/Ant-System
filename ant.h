#ifndef ANT_H
#define ANT_H

typedef struct Ant {
    float way_distance;
    int way[6];
    int visited[5];
} ant;

int generation_j(float probability_sum, float probability_selection[], int n);
ant *initialize_ant(int amount, int n);
void fetch_best_way(ant **ants, int n, float distance_matrix[][n], float information_matrix[][n], int amount);
int city_selection(float probability_sum, float probability_selection[], int n);
void change(ant ant, int n, int j, int i);
void decision_rule(ant ant, int i, int n, float information_matrix[][n]);
void updating_statistics(ant **ants, int best_way[], float *best_distance, int amount, int n);
void updating_pheromone(ant **ants, int n, float pheromone_matrix[][n]);
void evaporation(int n, float pheromone_matrix[][n]);
void deposit_pheromone(ant ant, int n, float pheromone_matrix[][n]);
void copy(int way[], int best_way[], int n);
void pheromone(int n, float pheromone_matrix[][n]);
void distance(int n, float distance_matrix[][n]);
void information(int n, float information_matrix[][n], float pheromone_matrix[][n], float distance_matrix[][n]);
float calcule_way_distance(ant ant, int n, float distance_matrix[][n]);


#endif