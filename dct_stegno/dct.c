#include <math.h>
#include "dct.h"

#define PI 3.14159265358979323846

void dct(double block[8][8]) {
    double tmp[8][8] = {0};
    for (int u = 0; u < 8; u++) {
        for (int v = 0; v < 8; v++) {
            double sum = 0;
            for (int x = 0; x < 8; x++) {
                for (int y = 0; y < 8; y++) {
                    sum += block[x][y] *
                           cos(((2 * x + 1) * u * PI) / 16) *
                           cos(((2 * y + 1) * v * PI) / 16);
                }
            }
            double cu = (u == 0) ? 1 / sqrt(2) : 1;
            double cv = (v == 0) ? 1 / sqrt(2) : 1;
            tmp[u][v] = 0.25 * cu * cv * sum;
        }
    }
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            block[i][j] = tmp[i][j];
}

void idct(double block[8][8]) {
    double tmp[8][8] = {0};
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            double sum = 0;
            for (int u = 0; u < 8; u++) {
                for (int v = 0; v < 8; v++) {
                    double cu = (u == 0) ? 1 / sqrt(2) : 1;
                    double cv = (v == 0) ? 1 / sqrt(2) : 1;
                    sum += cu * cv * block[u][v] *
                           cos(((2 * x + 1) * u * PI) / 16) *
                           cos(((2 * y + 1) * v * PI) / 16);
                }
            }
            tmp[x][y] = 0.25 * sum;
        }
    }
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            block[i][j] = tmp[i][j];
}
