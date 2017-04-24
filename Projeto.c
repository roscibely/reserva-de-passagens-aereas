/*Este programa serve para ler os dados do arquivo se eles estiverem ordenados como:
    Nº do Aviao
    Origem
    Destino
    Lugares disponiveis*/
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

#define TITULO_OPCAO1 "Consultar"
#define TITULO_OPCAO2 "Efetuar reserva"
#define TITULO_OPCAO3 "Sair"
#define TITULO_1SubOPCAO1 "Por numero do voo"
#define TITULO_2SubOPCAO1 "Por origem"
#define TITULO_3SubOPCAO1 "Por destino"

#define N_OPCOES 3
#define OPCAO1 '1'
#define N_SUB_OPCOES 3
#define SUB_OPCAO1 '1'
#define SUB_OPCAO2 '2'
#define SUB_OPCAO3 '3'
#define OPCAO2 '2'
#define OPCAO3 '3'

#define AVIOES 3
/*_______________________________________________________*/
void LimpaBuffer(void);
int LeOpcao(int menorValor, int maiorValor);
int LeInteiro(void);
char* LeString(void);
void ApresentaMenu(int nItens, int menorOpcao, ...);
/*_______________________________________________________*/
void LimpaBuffer(void) {
    int valorLido; /* valorLido deve ser int! */
    do {
        valorLido = getchar();
    } while ((valorLido != '\n') && (valorLido != EOF));
}
/*_______________________________________________________*/
int LeOpcao(int menorValor, int maiorValor) {
    int op;
    while (1) {
        printf("\nDigite sua opcao: ");
        op = getchar();
        if (op >= menorValor && op <= maiorValor) {
            LimpaBuffer();
            break;
        }
        else {
            printf("\nOpcao invalida. Tente novamente.");
            printf("\nA opcao deve estar entre %c e %c. \n",
                   menorValor, maiorValor);
            LimpaBuffer();
        }
    }
    return op;
}
/*_______________________________________________________*/
int LeInteiro(void) {
    int umInt, nValoresLidos;
    /*printf("Numero do voo ao qual deseja viajar: ");*/
    nValoresLidos = scanf("%d", &umInt);
    while (nValoresLidos == 0) { /*Nenhum inteiro foi lido*/
        LimpaBuffer();
        printf("Entrada incorreta. Digite um valor inteiro: ");
        nValoresLidos = scanf("%d", &umInt);
    }
    LimpaBuffer();
    return umInt;
}
/*_______________________________________________________*/
void ApresentaMenu(int nItens, int menorOpcao, ...) {
    int i;
    va_list argumentos;
    /* Inicia lista de argumentos variáveis */
    va_start(argumentos, menorOpcao);
    /* Lê cada argumento e imprime na tela. Note que o */
    /* tipo de cada argumento é char *, que é o tipo que */
    /* representa strings em C */
    for(i = 0; i < nItens; ++i) {
        printf("%c-%s\n", menorOpcao++, va_arg(argumentos, char *));
    }
    va_end(argumentos);/* Encerra processamento de argumentos */
}
/*_______________________________________________________*/
char* LeString(void){
    char aux[121];
    scanf(" %120[^\n]", aux);
    int n = strlen(aux);
    char* string = (char*) malloc((n+1)*sizeof(char));
    strcpy(string, aux);
    LimpaBuffer();

return string;
}
/*_______________________________________________________*/
int main(void){
    char op, origem[21], destino[21];
    int inteiro1, c, k, s, n, i,t;
    t=n=0;
    s=2; k=1; c=3;
    char linha[121];
    char *ORIGEM[AVIOES];
    char *DESTINO[AVIOES];
    int LUGARESdisponiveis[AVIOES];
    int voo[AVIOES];
    unsigned int saida = 0;
    FILE* fp;
    char *origem1, *destino1;

    fp = fopen("entrada.txt", "rt");
    if(fp == NULL) {
        printf("Erro na abertura do arquivo!\n");
        exit(1);
    }
    while(fgets(linha, 121, fp) !=NULL){ /* Ler todos os dados do arquivo*/
        if(n%5==0)
            sscanf(linha, "%d ", &voo[n/5]);
        if(n==c){
            c+=5;
            sscanf(linha, "%d ", &LUGARESdisponiveis[(n-3)/5]);}
        if(n==k){
            k+=5;
            sscanf(linha, "%20[^\n] ", origem);
            i = strlen(origem);
            ORIGEM[(n-1)/5] = (char*) malloc((i+1)*sizeof(char));
            strcpy(ORIGEM[(n-1)/5], origem);
        }
        if(n==s){
            s+=5;
            sscanf(linha, "%20[^\n] ", destino);
            i = strlen(destino);
            DESTINO[(n-2)/5] = (char*) malloc((i+1)*sizeof(char));
            strcpy(DESTINO[(n-2)/5], destino);
            }
    n++;
    }
fclose(fp);
    do {
        ApresentaMenu(N_OPCOES, OPCAO1, TITULO_OPCAO1, TITULO_OPCAO2, TITULO_OPCAO3);
        op = LeOpcao(OPCAO1, OPCAO1 + N_OPCOES - 1);
        switch(op) {

            case OPCAO1:
                ApresentaMenu(N_SUB_OPCOES, SUB_OPCAO1, TITULO_1SubOPCAO1, TITULO_2SubOPCAO1, TITULO_3SubOPCAO1);
                char sub_op;
                sub_op = LeOpcao(SUB_OPCAO1, SUB_OPCAO1 + N_SUB_OPCOES - 1);
                switch(sub_op){

                    case SUB_OPCAO1:
                        printf("\nDigite o numero do voo\n");
                        inteiro1 = LeInteiro();
                        t=0;
                        for(i=0; i<AVIOES; i++){
                            if(inteiro1==voo[i]){
                                printf("\n Voo existente \n Origem: %s \n Destino: %s \n Lugares disponiveis: %d \n \n",
                                        ORIGEM[i], DESTINO[i], LUGARESdisponiveis[i] );
                                t=1;
                                break;
                            }
                        }
                        if(!t)
                            printf("\n Numero do voo nao encontrado \n \n");
                        break;

                    case SUB_OPCAO2:
                        origem1 = LeString();
                        t=0;
                        for(i=0; i<AVIOES; i++){
                            if(!strcmp(ORIGEM[i], origem1)){
                                printf("\n Voo: %d \n Lugares Disponiveis: %d \n Destino: %s \n \n",
                                        voo[i], LUGARESdisponiveis[i], DESTINO[i]);
                                t=1;
                            }
                        }
                        if(!t)
                            printf("\n Origem nao existente \n \n");
                    break;

                    case SUB_OPCAO3:
                        destino1 = LeString();
                        t=0;
                        for(i=0; i<AVIOES; i++){
                            if(!strcmp(DESTINO[i],destino1)){
                                printf("\n Voo: %d \n Lugares Disponiveis: %d \n Origem: %s \n \n",
                                        voo[i], LUGARESdisponiveis[i], ORIGEM[i]);
                                t=1;
                                break;
                            }
                        }
                    if(!t)
                        printf("\n Destino nao existente \n \n");
                    break;
            }
            break;

            case OPCAO2:
                printf("Informe  o numero do voo no qual deseja viajar\n");
                inteiro1 = LeInteiro();
                t=0;
                for(i=0; i<AVIOES; i++){
                    if(inteiro1==voo[i]){
                        if(LUGARESdisponiveis[i]!=0){
                            LUGARESdisponiveis[i]--;
                            printf("\n Reserva confirmada \n \n");
                        }
                        else
                            printf("\n Voo lotado \n \n");
                    t=1;
                    break;
                    }

                }
                if(!t)
                    printf("\n Voo inexistente \n \n");
                break;

            case OPCAO3:
                saida = 1;
                printf("Obrigado por usar este programa.");
                break;

            default:
                printf("Este programa possui um bug.");
                return 1;
        }
    } while(!saida);
    return 0;
}
