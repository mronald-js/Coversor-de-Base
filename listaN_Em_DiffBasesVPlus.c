#include <stdio.h>
#include <gmp.h>

int converteN(int n, int base, char n_base[])
{
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

    // Inverte a ordem dos dígitos
    int j = 0;
    int k = i - 1;
    while (j < k)
    {
        char temporario = n_base[j];
        n_base[j] = n_base[k];
        n_base[k] = temporario;
        j++;
        k--;
    }

    n_base[i] = '\0';

    return i;
}

void converteParaDecimal(mpz_t n_decimal, const char *n, int base)
{
    mpz_set_ui(n_decimal, 0);
    mpz_t base_z, temp;
    mpz_inits(base_z, temp, NULL);
    mpz_set_ui(base_z, base);

    for (int i = 0; n[i] != '\0'; i++)
    {
        int valor = (n[i] >= 'A') ? (n[i] - 'A' + 10) : (n[i] - '0');
        mpz_mul_ui(temp, n_decimal, base);
        mpz_add_ui(n_decimal, temp, valor);
    }

    mpz_clears(base_z, temp, NULL);
}

int menu()
{
    int opcao_menu;

    printf("\n\nEscolha uma das opções abaixo:\n");
    printf("1 - Converter um número qualquer para decimal\n");
    printf("2 - Converter um número decimal para qualquer base\n");
    printf("0 - Sair\n\n");
    printf("Opção desejada: ");
    scanf("%d", &opcao_menu);

    // Verifica se a opção é válida
    while (opcao_menu < 0 || opcao_menu > 2)
    {
        printf("Opção inválida. Por favor, digite uma opção válida.\n");
        scanf("%d", &opcao_menu);
        // Limpa o buffer do teclado
        while (getchar() != '\n');
    }

}

int main()
{
    int continuar = 1;

    int opcao = menu();


    if (opcao == 0)
    {
        printf("Obrigado por usar o programa!\n");
        continuar = 0;
    }

    while (continuar)
    {
        switch (opcao)
        {
            while(opcao == 1) {
            case 1:
            
                char n[10000], n_convertido[10000];
                int base;

                printf("\nDigite um número: ");
                scanf("%s", n);

                printf("Digite a base do número: ");
                //se o tipo de dado for diferente de inteiro, vai dar erro
                scanf("%d", &base);
                
                //vamos checar se o valor dos algarismos é maior que a base
                //se for, o número não é válido e caso não seja vamos pedir para o usuário digitar novamente
                for (int i = 0; n[i] != '\0'; i++)
                {
                    int valor = (n[i] >= 'A') ? (n[i] - 'A' + 10) : (n[i] - '0');
                    if (valor >= base)
                    {
                        printf("O número digitado não é válido. Por favor, digite um número válido: ");
                        scanf("%s", n);
                        i = -1;
                    }
                }

                mpz_t n_decimal;
                mpz_init(n_decimal);
                converteParaDecimal(n_decimal, n, base);
                gmp_printf("O número convertido para decimal é: {%Zd}\n", n_decimal);

                printf("\nDigite 1 para continuar a operação\nDigite 2 para escolher outra operação\nDigite 0 para sair\n");
                scanf("%d", &opcao);
                // Verifica se a opção é válida
                while (opcao < 0 || opcao > 2)
                {
                    printf("Opção inválida. Por favor, digite uma opção válida.\n");
                    scanf("%d", &opcao);
                    // Limpa o buffer do teclado
                    while (getchar() != '\n')
                        ;
                }

                // no caso de for 1 o case 1 vai executar novamente
                // No caso de for 2 o código vai chamar a função menu
                // No caso de for 0 o código vai sair do programa
                if (opcao == 1)
                {
                    opcao = 1;
                }
                else if (opcao == 2)
                {
                    opcao = menu();
                }
                else if (opcao == 0)
                {   
                    printf("Obrigado por usar o programa!\n");
                    opcao, continuar = 0;
                }
            
            break;
        }

        while (opcao == 2)
        {
            case 2:

            int n, base, opcao;
            char n_convertido[100];

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
            while (scanf("%d", &base) != 1 || (base < 2 || base > 36))
            {
                printf("Entrada inválida. Por favor, digite um número válido.\n");
                //limpa o buffer do teclado
                while (getchar() != '\n');
            }

            n_convertido[converteN(n, base, n_convertido)] = '\0';
            converteN(n, base, n_convertido);

            printf("O número convertido para a base é: {%s}\n", n_convertido);
            printf("\nDeseja continuar? Digite 1 para sim, 2 para escolhar outra opção e 0 para sair: ");

            scanf("%d", &opcao);
            if (opcao == 1)
            {
                opcao = 1;
            }   
            else if (opcao == 2)
            {
                opcao = menu(&continuar);
            }
            else
            {
                printf("Obrigado por usar o programa!\n");
                opcao, continuar = 0;
            }

            break;
        }
        
        {
    }
        default:
            break;
        }
    }

    return 0;
}
