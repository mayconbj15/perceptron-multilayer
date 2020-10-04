//
//  main.cpp
//  mlperceptron
//
//  Created by Sergei Bugrov on 7/1/17.
//  Copyright © 2017 Sergei Bugrov. All rights reserved.
//

#include <string>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <math.h>
#include <time.h> 

#define N 1200

using namespace std;

vector<float> X {
    5.1, 3.5, 1.4, 0.2, 
    4.9, 3.0, 1.4, 0.2, 
    6.2, 3.4, 5.4, 2.3, 
    5.9, 3.0, 5.1, 1.8
};

//Saída esperada
vector<float> y {
    0,
    0,
    1,
    1 };

//Vetor de pesos
vector<float> W {
    0.5,
    0.5,
    0.5,
    0.5};

vector <float> sigmoid_d (const vector <float>& m1) {
    
    /*  Returns the value of the sigmoid function derivative f'(x) = f(x)(1 - f(x)), 
        where f(x) is sigmoid function.
        Input: m1, a vector.
        Output: x(1 - x) for every element of the input matrix m1.
    */
    
    const unsigned long VECTOR_SIZE = m1.size();
    vector <float> output (VECTOR_SIZE);
    
    
    for( unsigned i = 0; i != VECTOR_SIZE; ++i ) {
        output[ i ] = m1[ i ] * (1 - m1[ i ]);
    }
    
    return output;
}

vector <float> sigmoid (const vector <float>& m1) {
    
    /*  Returns the value of the sigmoid function f(x) = 1/(1 + e^-x).
        Input: m1, a vector.
        Output: 1/(1 + e^-x) for every element of the input matrix m1.
    */
    
    const unsigned long VECTOR_SIZE = m1.size();
    vector <float> output (VECTOR_SIZE);
    
    
    for( unsigned i = 0; i != VECTOR_SIZE; ++i ) {
        output[ i ] = 1 / (1 + exp(-m1[ i ]));
    }
    
    return output;
}

vector <float> operator+(const vector <float>& m1, const vector <float>& m2){
    
    /*  Returns the elementwise sum of two vectors.
        Inputs: 
            m1: a vector
            m2: a vector
        Output: a vector, sum of the vectors m1 and m2.
    */
    
    const unsigned long VECTOR_SIZE = m1.size();
    vector <float> sum (VECTOR_SIZE);
    
    for (unsigned i = 0; i != VECTOR_SIZE; ++i){
        sum[i] = m1[i] + m2[i];
    };
    
    return sum;
}

vector <float> operator-(const vector <float>& m1, const vector <float>& m2){
    
    /*  Returns the difference between two vectors.
        Inputs:
            m1: vector
            m2: vector
        Output: vector, m1 - m2, difference between two vectors m1 and m2.
    */
    
    const unsigned long VECTOR_SIZE = m1.size();
    vector <float> difference (VECTOR_SIZE);
    
    for (unsigned i = 0; i != VECTOR_SIZE; ++i){
        difference[i] = m1[i] - m2[i];
    };
    
    return difference;
}

vector <float> operator*(const vector <float>& m1, const vector <float>& m2){
    
    /*  Returns the product of two vectors (elementwise multiplication).
        Inputs:
            m1: vector
            m2: vector
        Output: vector, m1 * m2, product of two vectors m1 and m2
    */
    
    const unsigned long VECTOR_SIZE = m1.size();
    vector <float> product (VECTOR_SIZE);
    
    for (unsigned i = 0; i != VECTOR_SIZE; ++i){
        product[i] = m1[i] * m2[i];
    };
    
    return product;
}

vector <float> transpose (float *m, const int C, const int R) {
    
    /*  Returns a transpose matrix of input matrix.
        Inputs:
            m: vector, input matrix
            C: int, number of columns in the input matrix
            R: int, number of rows in the input matrix
        Output: vector, transpose matrix mT of input matrix m
    */
    
    vector <float> mT (C*R);
    
    for(unsigned n = 0; n != C*R; n++) {
        unsigned i = n/C;
        unsigned j = n%C;
        mT[n] = m[R*j + i];
    }
    
    return mT;
}

vector <float> dot (const vector <float>& m1, const vector <float>& m2, const int m1_rows, const int m1_columns, const int m2_columns) {
    
    /*  Returns the product of two matrices: m1 x m2.
        Inputs:
            m1: vector, left matrix of size m1_rows x m1_columns
            m2: vector, right matrix of size m1_columns x m2_columns (the number of rows in the right matrix 
                must be equal to the number of the columns in the left one)
            m1_rows: int, number of rows in the left matrix m1
            m1_columns: int, number of columns in the left matrix m1
            m2_columns: int, number of columns in the right matrix m2
        Output: vector, m1 * m2, product of two vectors m1 and m2, a matrix of size m1_rows x m2_columns
    */
    
    vector <float> output (m1_rows*m2_columns);
    
	#pragma omp parallel for num_threads(8)
    for( int row = 0; row < m1_rows; ++row ) {
        for( int col = 0; col < m2_columns; ++col ) {
            output[ row * m2_columns + col ] = 0.f;
            for( int k = 0; k < m1_columns; ++k ) {
                output[ row * m2_columns + col ] += m1[ row * m1_columns + k ] * m2[ k * m2_columns + col ];
            }
        }
    }
    
    return output;
}

void print ( const vector <float>& m, int n_rows, int n_columns ) {
    
    /*  "Couts" the input vector as n_rows x n_columns matrix.
        Inputs:
            m: vector, matrix of size n_rows x n_columns
            n_rows: int, number of rows in the left matrix m1
            n_columns: int, number of columns in the left matrix m1
    */
    
    for( int i = 0; i != n_rows; ++i ) {
        for( int j = 0; j != n_columns; ++j ) {
            cout << m[ i * n_columns + j ] << " ";
        }
        cout << '\n';
    }
    cout << endl;
}

float random_between_two_int(float min, float max)    
{    
    srand (time(NULL));
    return (min + 1) + (((float) rand()) / (float) RAND_MAX) * (max - (min + 1));    
}

vector<float> getVector(FILE* file, int numNumbers){
    vector<float> T;
    float number;
    long deslocamento = 0;
    for (int i = 0; i < numNumbers; i++)
    {
        fseek(file, deslocamento, SEEK_SET);
        deslocamento += sizeof(float);
        fread(&number, sizeof(float), 1, file);
        //printf("%g\n", number);
        T.push_back(number);
    }

    return T;
}


void preencheDados(){   
    //Entradas 
    FILE* file = fopen("X.txt", "r");   
    X = getVector(file, N*N);
    cout << "Size X: " << X.size() << endl;
    fclose(file);
    
    //Valores esperados
    file = fopen("Y.txt", "r");   
    y = getVector(file, N);
    fclose(file); 

   /*  file = fopen("W.txt", "r");   
    W = getVector(file, N);
    fclose(file);*/
}

int main(int argc, const char * argv[]) {
    preencheDados();
    int QuantNeuronios = 4;
   /*  cout << "Digite a quantidade de neurônios";
    cin >> QuantNeuronios; */

    vector<float> Pesos(QuantNeuronios*N, 0.5);
    
	W = Pesos;
    cout << "Size W: " << W.size() << endl;
    
    int epochs = 50; //Ciclos de aprendizado
    for (unsigned i = 0; i != epochs; ++i) {
        vector<float> pred = sigmoid(dot(X, W, N, N, QuantNeuronios ) ); //Calcula o valor da saída de cada neurônio
        vector<float> pred_error = y - pred; //Calcula o erro --> erro = saida_esperada - saida_do_neurônio  
        vector<float> pred_delta = pred_error * sigmoid_d(pred); //Calcula o erro do neurônio        
        vector<float> W_delta = dot(transpose( &X[0], N, N ), pred_delta, N, N, QuantNeuronios); //Calcula as atualizações dos pesos dos neurônios        
        W = W + W_delta; //Atualiza o peso dos neurônios
        
        if (i == epochs-1){
            print ( pred, N, QuantNeuronios );
        };
    };

    return 0;
}