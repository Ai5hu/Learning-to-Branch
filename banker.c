#include <stdio.h>

#define MAX 10
#define MAX_RESOURCES 10

int isSafeState(int P, int R, int avail[], int max[][R], int allot[][R], int need[][R]) {
    int finish[P];
    int safeSeq[P];
    int work[R];
    int count = 0;

    for (int i = 0; i < P; i++) {
        finish[i] = 0;
    }
    for (int i = 0; i < R; i++) {
        work[i] = avail[i];
    }

    while (count < P) {
        int found = 0;

        for (int p = 0; p < P; p++) {
            if (!finish[p]) {
                int canProceed = 1;
                for (int i = 0; i < R; i++) {
                    if (need[p][i] > work[i]) {
                        canProceed = 0;
                        break;
                    }
                }

                if (canProceed) {
                    for (int i = 0; i < R; i++) {
                        work[i] += allot[p][i];
                    }
                    finish[p] = 1;
                    safeSeq[count++] = p;
                    found = 1;
                    break;
                }
            }
        }

        if (!found) {
            printf("System is not in a safe state\n");
            return 0;
        }
    }

    printf("System is in a safe state\nSafe sequence: ");
    for (int i = 0; i < P; i++) {
        printf("P%d ", safeSeq[i]);
    }
    printf("\n");
    return 1;
}

int main() {
    int P, R;

    printf("Enter number of processes: ");
    scanf("%d", &P);
    printf("Enter number of resources: ");
    scanf("%d", &R);

    int max[P][R], allot[P][R], avail[R], need[P][R];

    printf("\nEnter maximum resources for each process (Max matrix):\n");
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            printf("Max[%d][%d]: ", i, j);
            scanf("%d", &max[i][j]);
        }
    }

    printf("\nEnter allocated resources for each process (Allot matrix):\n");
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            printf("Allot[%d][%d]: ", i, j);
            scanf("%d", &allot[i][j]);
        }
    }

    printf("\nEnter available resources (Avail vector):\n");
    for (int i = 0; i < R; i++) {
        printf("Avail[%d]: ", i);
        scanf("%d", &avail[i]);
    }

    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            need[i][j] = max[i][j] - allot[i][j];
        }
    }

    isSafeState(P, R, avail, max, allot, need);

    return 0;
}

