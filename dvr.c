#include <stdio.h>

#define MAX 10
#define INF 9999

int cost[MAX][MAX];
int distance[MAX][MAX];
int next[MAX][MAX];

void setCost(int num) {
    for (int i = 0; i < num; i++) {
        for (int j = 0; j < num; j++) {
            if (i == j) {
                cost[i][j] = 0;  // Self-cost should always be 0
                next[i][j] = -1; // No next hop needed
            } else {
                printf("Enter distance from %d to %d (9999 for no link): ", i, j);
                scanf("%d", &cost[i][j]);
                next[i][j] = (cost[i][j] == INF) ? -1 : j;
            }
            distance[i][j] = cost[i][j];
        }
    }
}

void bellmanford(int nums) {
    int updated;
    do {
        updated = 0;
        for (int i = 0; i < nums; i++) {
            for (int j = 0; j < nums; j++) {
                for (int k = 0; k < nums; k++) {
                    if (distance[i][k] != INF && distance[k][j] != INF &&
                        (distance[i][k] + distance[k][j] < distance[i][j])) {
                        updated = 1;
                        distance[i][j] = distance[i][k] + distance[k][j];
                        next[i][j] = next[i][k];  // Correct next-hop update
                    }
                }
            }
        }
    } while (updated);
}

void display(int nums) {
    for (int i = 0; i < nums; i++) {
        printf("\nRouting Table for Router %d:\n", i);
        printf("Destination\tDistance\tNext Hop\n");
        for (int j = 0; j < nums; j++) {
            printf("%d\t\t", j);
            if (distance[i][j] == INF)
                printf("INF\t\t");
            else
                printf("%d\t\t", distance[i][j]);

            if (next[i][j] == -1)
                printf("N/A\n");
            else
                printf("%d\n", next[i][j]);
        }
    }
}

int main() {
    int numRouters;
    printf("Enter number of routers: ");
    scanf("%d", &numRouters);

    setCost(numRouters);
    bellmanford(numRouters);
    display(numRouters);

    return 0;
}
