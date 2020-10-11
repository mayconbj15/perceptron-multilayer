# Perceptron multilayer neural network :alien:

Inspired by https://cognitivedemons.wordpress.com/2017/07/06/a-neural-network-in-10-lines-of-c-code/

#### Compilar e executar

    $ g++ neural.cpp -o neural -fopenmp -std=c++11 && time ./neural

#### Compilar e executar versão otimizada por vetorização

    $ g++ -O3 neural.cpp -o neural -fopenmp -std=c++11 && time ./neural

Nessa versão do algoritmo foi feita uma paralelização nas camadas ocultas (hidden layer) por ser uma seção independente e altamente paralelizável. Nessa parte do algoritmo existe uma multiplicação entre duas matrizes que gera a saída dos neurônios dessa camada, e foi escolhido esse cálculo para ser paralelizado, sendo ele o cálculo mais custoso da aplicação com a complexidade de O($n^3$).

Todas as etapas desse algoritmo é muito bem paralelizável pois as operações estão bem definidas e separadas, e a implementação é altamente vetorizável. Mas decidimos por apenas paralelizar a camada oculta nesse primeiro momento para ter menos variáveis na comparação com outras versões e ser o cálculo mais custoso da aplicação.

Está implementação da rede neural leva muito proveito também da vetorização já que toda a implementação é baseada em vetores, sendo todas as operações básicas sobrepostas para operações de vetores, por exemplo, o operador de soma é redefinido para somar dois vetores float ao invés de somar dois números float.

Abaixo segue os valores de execução com a paralelização da camada oculta, com e sem vetorização, para valores de 1, 2, 4 e 8 threads. Obs: valores obtidos executando no servidor parcode do ICEI da PUC Minas.

**Tempos paralelos por número de threads**

|                     | 1 thread  | 2 threads | 4 threads | 8 threads |
| ------------------- | --------- | --------- | --------- | --------- |
| Tempo sequencial    | 0m18.171s | -         | -         | -         |
| Paralelo            | 0m15.432s | 0m11.634s | 0m6.262s  | 0m6.614s  |
| Paralelo vetorizado | 0m2.443s  | 0m2.239s  | 0m1.912s  | 0m2.023s  |
