//O programa vai listar qualquer n_decimal para outro n em qualquer base
//ou converter um n_qualquer em outro base decimal;
#include <stdio.h>
#include <math.h>
#include <gmp.h>

int converteN(long int n, int base, char n_base[]){
    int i = 0;

    while (n > 0)
    {
        int resto = n % base;
        if (resto < 10)
        {
            n_base[i] = resto + '0';
        }
        else
        {
            n_base[i] = resto + 'A' - 10;
        }
        n /= base;
        i++;
        
    }

    n_base[i] = '\0';

    //Inverte o array;
    int j = 0;
    int k = i - 1;
    {
        char temporario = n_base[j];
        n_base[j] = n_base[k];
        n_base[k] = temporario;
        j++;
        k--;
    }
    
    return i;
}

//função que converte um número qualquer para decimal mesmo que seja negativo ou muito grande usando a biblioteca gmp
int converteParaDecimal(long int n, int base){
    long int n_decimal = 0;
    int i = 0;
    while (n > 0)
    {
        int resto = n % 10;
        n_decimal += resto * pow(base, i);
        n /= 10;
        i++;
    }
    return n_decimal;
}


//função menu
int menu(){
    //menu de opções
        int opcao;
        printf("\n\nEscolha uma das opções abaixo:\n");
        printf("1 - Converter um número qualquer para decimal\n");
        printf("2 - Converter um número decimal para qualquer base\n");
        printf("0 - Sair\n\n");
        printf("Opção desejada: ");
        scanf("%d", &opcao);

    //checkar se a opção é válida
        while (opcao < 0 || opcao > 2)
        {
            printf("Opção inválida. Por favor, digite uma opção válida.\n");
            scanf("%d", &opcao);
            //limpa o buffer do teclado
            while (getchar() != '\n');
        }

        return opcao;
}

int main(){
    
    int n, base, opcao, continuar = 1;
    char n_convertido[10000];

    printf("\nEste programa vai converter um numero decimal para seu respectivo valor em qualquer base passada \nou converter um n de uma outra base qualquer em decimal");

    opcao = menu();

    do
    {

        switch (opcao)
        {

        case 1:
            
            printf("\nDigite um número qualquer: ");
            //se o tipo de dado for diferente de inteiro, vai dar erro
            while(scanf("%d", &n) != 1)
            {
                printf("Entrada inválida. Por favor, digite um número inteiro.\n");
                //limpa o buffer do teclado
                while (getchar() != '\n');
            }
            

            //realizar a validação do número digitado

            printf("Digite a base do número: ");
            scanf("%d", &base);
            //se o numero não existir na base digitada, vai dar erro, por exemplo, se o número for 2 e a base for 2 porém se for 1010 e a base for 2, não vai dar erro
            while (n % 10 >= base)
            {
                printf("Entrada inválida. Por favor, digite um número que exista na base digitada.\n");
                scanf("%d", &n);
            }

            //Os inteiros gmp são inicializados com a função mpz_init e armazenados em mp
            long int n_decimal = converteParaDecimal(n, base);
            printf("O número convertido para decimal é: %ld\n", n_decimal);

            //A ideia é que o usuário possa escolher se quer continuar no programa ou não
            printf("Deseja continuar? Digite 1 para sim, 2 para escolhar outra opção e 0 para sair: ");
            scanf("%d", &opcao);
            
            if (opcao == 1)
            {
                continuar = 1;
            }   
            else if (opcao == 2)
            {
                menu();
            }
            else
            {
                continuar = 0;
                return 0;
            }
            break;
        case 2:
            do
        {
            printf("\nDigite um numero qualquer em decimal: ");
            //se o tipo de dado for diferente de inteiro, vai dar erro
            //então é necessário usar o scanf com o tipo de dado inteiro
            while (scanf("%d", &n) != 1)
            {
                printf("Entrada inválida. Por favor, digite um número inteiro.\n");
                //limpa o buffer do teclado
                while (getchar() != '\n');
            }

            printf("Digite a base a ser convertida: ");
            while (scanf("%d", &base) != 1)
            {
                printf("Entrada inválida. Por favor, digite um número inteiro.\n");
                //limpa o buffer do teclado
                while (getchar() != '\n');
            }
            n_convertido[0] = '\0';
            converteN(n, base, n_convertido);

            printf("O número convertido para a base é: %s\n", n_convertido);
            printf("Deseja continuar? Digite 1 para sim, 2 para escolhar outra opção e 0 para sair: ");

            scanf("%d", &opcao);
            if (opcao == 1)
            {
                continuar = 1;
            }   
            else if (opcao == 2)
            {
                menu();
            }
            else
            {
                continuar = 0;
                return 0;
            }

        } while (n != 0);
            break;
        default:
            break;
        }
    } while (continuar);
    


    return 0;
}