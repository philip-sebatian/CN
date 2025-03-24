#include <stdio.h>
#include <stdlib.h>

#define INF 9999  // Represents infinity for unreachable nodes
#define MAX_NODES 10

typedef struct {
    int cost[MAX_NODES][MAX_NODES]; // Cost matrix
    int distance[MAX_NODES];        // Distance vector
    int nextHop[MAX_NODES];         // Next hop for each node
} Router;

int numRouters;

// Function to initialize routers
void initializeRouters(Router routers[]) {
    printf("Enter the number of routers: ");
    scanf("%d", &numRouters);

    printf("Enter the cost matrix (use %d for no direct link):\n", INF);
    for (int i = 0; i < numRouters; i++) {
        for (int j = 0; j < numRouters; j++) {
            scanf("%d", &routers[i].cost[i][j]);
            routers[i].distance[j] = routers[i].cost[i][j];
            routers[i].nextHop[j] = (routers[i].cost[i][j] == INF) ? -1 : j;
        }
    }
}

// Function to update the routing tables using Bellman-Ford
void updateRoutingTables(Router routers[]) {
    int updated;
    do {
        updated = 0;
        for (int i = 0; i < numRouters; i++) { // Each router
            for (int j = 0; j < numRouters; j++) { // Each destination
                for (int k = 0; k < numRouters; k++) { // Each neighbor
                    if (routers[i].distance[k] + routers[k].distance[j] < routers[i].distance[j]) {
                        routers[i].distance[j] = routers[i].distance[k] + routers[k].distance[j];
                        routers[i].nextHop[j] = k;
                        updated = 1;
                    }
                }
            }
        }
    } while (updated);
}

// Function to display routing tables
void displayRoutingTables(Router routers[]) {
    for (int i = 0; i < numRouters; i++) {
        printf("\nRouting table for Router %d:\n", i);
        printf("Destination\tCost\tNext Hop\n");
        for (int j = 0; j < numRouters; j++) {
            printf("%d\t\t%d\t%d\n", j, routers[i].distance[j], routers[i].nextHop[j]);
        }
    }
}

// Main function
int main() {
    Router routers[MAX_NODES];
    
    initializeRouters(routers);
    updateRoutingTables(routers);
    displayRoutingTables(routers);

    return 0;
}
