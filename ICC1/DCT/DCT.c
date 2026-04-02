#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
    int N, i, j, x, y;
    double a, b, G, somatorio = 0, pi = 3.141592;
    scanf("%d", &N);
    double matriz[N][N], matriz_transformada[N][N];

    for(x = 0; x < N; x++) {
        for(y = 0; y < N; y++) {
            scanf("%lf", &matriz[x][y]);
        }
    }
    
    for(i = 0; i < N; i++){
        for(j = 0; j < N; j++){
            if((i == 0)) {
                a = (1.0 / sqrt(N));
            } else {
                a = sqrt(2.0 / N);
            }
            if((j == 0)) {
                b = (1.0 / sqrt(N));
            } else {
                b = sqrt(2.0 / N);
            }

            for(x = 0; x < N; x++) {
                for(y = 0; y < N; y++) {
                    somatorio = somatorio + matriz[x][y] * cos(((2.0 * y + 1.0) * j * pi) / (2.0 * N)) * cos(((2.0 * x + 1.0) * i * pi) / (2.0 * N));
                }
            }  

            G = a * b * somatorio;
                 
            somatorio = 0;

        
            matriz_transformada[i][j] = G;
            printf("%9.3lf ", matriz_transformada[i][j]);
            if(j == N - 1) {
                printf("\n");
            }
        }
    }
}