//O programa vai listar qualquer n_decimal para outro n em qualquer base

//Sera incluida as bibliotecas math e stdio
#include <stdio.h>
#include <math.h>

//Será criada uma função que transforme determinado n na base decimal em um n na base passada pelo usuário
int converteN(int n, int base, char n_base[]){

    int i = 0;

    //Será usado um laço no qual será funcional para qualquer valor digitado maior do que 0
    while (n > 0)
    {
        //Capturaremos o resto da divisao do numero passado pela base informada
        int resto = n % base;

        //Faremos uma checagem lógica, caso o resto seja menor do que 10 obteremos o valor número de resto
        if (resto < 10)
        {
            n_base[i] = resto + '0';
        }
        else
        {
            /*
                a partir do momento em que resto for igual ou maior do que 10 nós somaremos o valor de
                'A' ao resto e subtrairemos 10 para obter o valor correto de acordo com a Tabela ASCII
            */
            n_base[i] = resto + 'A' - 10;
        }
        // A cada iteração de n nós dividermos o n pela base
        n /= base;
        // e incrementaremos um no nosso contador para percorrer o array de n_base
        i++;
        
    }
    // por fim n_base recebe o \0 como caracter nulo para indicar o fim do Array
    n_base[i] = '\0';

    //A seguinte operaçao inverte o array de forma a mostrar os valores de forma correta;
    //A variavel start se refere ao começo do index do array
    //A variavel end se refere ao fim do index do array
    int start = 0;
    int end = i - 1;  
    while (start < end)
    {
        char temporario = n_base[start];
        n_base[start] = n_base[end];
        n_base[end] = temporario;
        start++;
        end--;
    }
    
}

int main(){
    
    //declarando as variáveis, só lembrando que n_convertido é do tipo char pois armazena valores Alfanuméricos
    int n_qualquer, base;
    char n_convertido[100];

    //imprimindo e lendo os valores
    printf("Digite um numero qualquer em decimal: ");
    scanf("%d", &n_qualquer);

    printf("Digite a base a ser convertida: ");
    scanf("%d", &base);

    //Usando a função converteN para receber os valores digitados como parametro
    converteN(n_qualquer, base, n_convertido);

    // mostrando a saída
    printf("O número %d convertido na base %d É = %s\n", n_qualquer, base, n_convertido);

    return 0;
}