## Descrição

Projeto de Programação Concorrente para cálculo do produto interno de dois vetores de números reais. O programa implementa uma versão sequencial e uma concorrente usando threads (pthread) em C. Também mede o tempo de execução e compara os resultados.
Projeto feito para a matéria de Programação Concorrente.

## Arquivos

Produto_Interno.c → Programa principal, cálculo concorrente do produto interno.

gera_binario.c → Gera arquivos binários de teste com vetores aleatórios e resultado sequencial.

timer.h → Header que fornece macro GET_TIME para medição de tempo.

## Como Compilar
'''bash
gcc binario.c -o binario.exe
.\binario.exe arquivo.bin 1000 #dimensão do vetor. mude de acordo com a necessidade)
.\Produto_Interno.exe arquivo.bin 4 (n de threads. mude de acordo com a necessidade)
'''

## Observação

Coloquei os .exe apenas para entregar o trabalho completo.
Não tente executar os arquivos usando o meu .exe, já que cada computador pode precisar de um executável diferente. Compile o .c localmente e rode.
