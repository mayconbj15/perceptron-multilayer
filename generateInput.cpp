#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define N 1200
#define SEED 5
//800
using namespace std;

float random_between_two_int(float min, float max);
void geraEntrada(FILE *file, int n);

float random_between_two_int(float min, float max)    
{    
    return (min + 1) + (((float) rand()) / (float) RAND_MAX) * (max - (min + 1));    
}

void geraEntrada(FILE *file, int n){
    int numNumbers = n;
    float number;

    for (int i = 0; i < numNumbers; i++)
    {
        number = random_between_two_int(0,5);
        //number = rand() % SEED;
        fwrite(&number, sizeof(int), 1, file);
    }
}


int main(){
    srand (time(NULL));

    FILE* file = fopen("X.txt", "w");
    geraEntrada(file, N*N);
    fclose(file);

    file = fopen("W.txt", "w");
    geraEntrada(file, N);
    fclose(file);

    file = fopen("Y.txt", "w");
    geraEntrada(file, N);
    fclose(file);

    return 0;
}