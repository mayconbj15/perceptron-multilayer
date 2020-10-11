# Perceptron multilayer neural network :alien:

Inspired by https://cognitivedemons.wordpress.com/2017/07/06/a-neural-network-in-10-lines-of-c-code/

#### Gerar entrada de dados
    $g++ generateInput.cpp -o generateInput -std=c++11 && ./generateInput
    
#### Compilar e executar

    $ g++ neural.cpp -o neural -fopenmp -std=c++11 && time ./neural

#### Compilar e executar versão otimizada por vetorização

    $ g++ -O3 neural.cpp -o neural -fopenmp -std=c++11 && time ./neural

Nessa versão do algoritmo foi feita uma paralelização nas camadas ocultas (hidden layer) por ser uma seção independente e altamente paralelizável. Também foi escolhida essa parte por ter a opção de mudar a quantidade de neurônios, então foi feita uma comparação entre números de threads e números de neurônios. Nessa parte do algoritmo existe uma multiplicação entre duas matrizes que gera a saída dos neurônios dessa camada, e foi escolhido esse cálculo para ser paralelizado, sendo ele o cálculo mais custoso da aplicação com a complexidade de O($n^3$).

Todas as etapas desse algoritmo é muito bem paralelizável pois as operações estão bem definidas e separadas, e a implementação é altamente vetorizável. Mas decidimos por apenas paralelizar a camada oculta nesse primeiro momento para ter menos variáveis na comparação com outras versões e por ser o cálculo mais custoso da aplicação.

Está implementação da rede neural leva muito proveito também da vetorização já que toda a implementação é baseada em vetores, sendo todas as operações básicas sobrepostas para operações de vetores, por exemplo, o operador de soma é redefinido para somar dois vetores float ao invés de somar dois números float.

Abaixo segue os valores de execução com a paralelização da camada oculta, com e sem vetorização, para valores de 1, 2, 4 e 8 threads e com os valores de 1, 2, 4 e 8 neurônios. Obs: valores obtidos executando no servidor parcode do ICEI da PUC Minas.

**Tempos paralelos por número de threads com 1 neurônio**

|                     | 1 thread  | 2 threads | 4 threads | 8 threads |
| ------------------- | --------- | --------- | --------- | --------- |
| Tempo sequencial    | 0m8.067s  | -         | -         | -         |
| Paralelo            | 0m8.687s  | 0m4.417s  | 0m3.699s  | 0m3.722s  |
| Paralelo vetorizado | 0m1.728s  | 0m2.402s  | 0m1.869s  | 0m1.748s  |

**Tempos paralelos por número de threads com 2 neurônios**

|                     | 1 thread  | 2 threads | 4 threads | 8 threads |
| ------------------- | --------- | --------- | --------- | --------- |
| Tempo sequencial    | 0m8.269s  | -         | -         | -         |
| Paralelo            | 0m9.163s  | 0m6.015s  | 0m4.496s  | 0m4.532s  |
| Paralelo vetorizado | 0m2.002s  | 0m1.868s  | 0m1.739s  | 0m1.739s  |

**Tempos paralelos por número de threads com 4 neurônios**

|                     | 1 thread  | 2 threads | 4 threads | 8 threads |
| ------------------- | --------- | --------- | --------- | --------- |
| Tempo sequencial    | 0m18.171s | -         | -         | -         |
| Paralelo            | 0m15.432s | 0m11.634s | 0m6.262s  | 0m6.614s  |
| Paralelo vetorizado | 0m2.443s  | 0m2.239s  | 0m1.912s  | 0m2.023s  |

**Tempos paralelos por número de threads com 8 neurônios**

|                     | 1 thread  | 2 threads | 4 threads | 8 threads |
| ------------------- | --------- | --------- | --------- | --------- |
| Tempo sequencial    | 0m24.796s | -         | -         | -         |
| Paralelo            | 0m28.154s | 0m15.542s | 0m9.745s  | 0m9.992s  |
| Paralelo vetorizado | 0m3.778s  | 0m2.990s  | 0m2.592s  | 0m2.704s  |

Aumentar o número de threads ajudou no desempenho do algoritmo, porém aumentar o número de neurônios deixou a execução mais lenta.
