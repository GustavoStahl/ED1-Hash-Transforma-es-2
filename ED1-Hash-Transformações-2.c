#include <stdio.h>
#include <string.h>
#define MAX 100

int verificaPosicao(int posicao, int M){
    if(posicao>M){
        char novaPosicao[MAX];
        sprintf(novaPosicao, "%d", posicao);
        novaPosicao[strlen(novaPosicao)-1] = '\0';
        return atoi(novaPosicao);
    }
    else
        return posicao;
}

int extracao(char chave[], int M){
    int i, posicao;
    char posicao_string[MAX], M_string[MAX];
    M--; //Casos M = 100, 0-99 posicoes
    posicao_string[0] = '\0';
    sprintf(M_string, "%d", M);
    for(i=0; i<strlen(chave) && i<strlen(M_string); i++)
        strncat(posicao_string, &chave[i], 1);
    posicao = atoi(posicao_string);
    return verificaPosicao(posicao, M);;
}

int enlacamento_deslocado(char chave_string[], char M_string[]){
    int i, j, posicao=0;
    for(i=0; i<strlen(chave_string); i+=strlen(M_string)){
        char bloco[MAX];
        bloco[0] = '\0';
        for(j=i; j<i+strlen(M_string); j++){
            strncat(bloco, &chave_string[j], 1);
        }
        posicao+=atoi(bloco);
    }
    return posicao;
}

int enlacamento_limite(char chave_string[], char M_string[]){
    int i, j, count, posicao=0;
    for(i=0, count=1; i<strlen(chave_string); i+=strlen(M_string), count++){
        char bloco[MAX];
        bloco[0] = '\0';
        if(count%2 == 0)
            for(j=i+strlen(M_string)-1; j>=i; j--)
                strncat(bloco, &chave_string[j], 1);
        else
            for(j=i; j<i+strlen(M_string); j++)
                strncat(bloco, &chave_string[j], 1);

        posicao+=atoi(bloco);
    }
    return posicao;
}

int enlacamento(char chave_string[], int M, int tipo){
    int i, posicao;
    char  M_string[MAX];
    M--; //Casos M = 100, 0-99 posicoes
    sprintf(M_string, "%d", M);

    while(strlen(chave_string) % strlen(M_string) != 0){
        chave_string[strlen(chave_string)] = '0';
        chave_string[strlen(chave_string)+1] = '\0';
    }

    char posicao_string[MAX];
    if(tipo == 1)
        posicao = enlacamento_deslocado(chave_string, M_string);
    else
        posicao = enlacamento_limite(chave_string, M_string);

    sprintf(posicao_string, "%d", posicao);
    if(strlen(posicao_string) >= strlen(M_string) || posicao>M)
        posicao %= M+1;
        
    return posicao;
}

int dobra(char chave_string[MAX], int M){
    int i, j, count, posicao;
    char blocoPrincipal[MAX], blocoSecundario[MAX], M_string[MAX];
    M--; //Casos M = 100, 0-99 posicoes
    blocoPrincipal[0] = '\0';
    blocoSecundario[0] = '\0';
    sprintf(M_string, "%d", M);

    while(strlen(chave_string) % strlen(M_string) != 0){
        chave_string[strlen(chave_string)] = '0';
        chave_string[strlen(chave_string)+1] = '\0';
    }

    for(i=0; i<strlen(chave_string); i++){
        if(i<strlen(M_string))
            strncat(blocoPrincipal, &chave_string[i], 1);
        else
            strncat(blocoSecundario, &chave_string[i], 1);
    }

    blocoPrincipal[strlen(blocoPrincipal)+1] = '\0';
    blocoSecundario[strlen(blocoSecundario)+1] = '\0';

    for(i=0; i<strlen(blocoSecundario); i+=strlen(M_string)){
        for(j=i, count=0; j<i+strlen(M_string); j++, count++){
            char numero_string[3], numero1[2], numero2[2];
            numero_string[0] = numero1[0] = numero2[0] = '\0';

            strncat(numero1, &blocoPrincipal[count], 1);
            strncat(numero2, &blocoSecundario[i+strlen(M_string)-count-1], 1);

            int soma = atoi(numero1) + atoi(numero2);
            if(soma>9)
                soma-=10;

            sprintf(numero_string, "%d", soma);
            blocoPrincipal[count] = numero_string[0];
        }        
    }

    posicao = atoi(blocoPrincipal);
    if(posicao>=M_string)
        posicao %= M+1;

    return posicao;
}

int main(){
    int M, posicao;
    char chave[MAX];
    printf("Digite M: ");
    scanf("%d", &M);
    printf("Digite a chave (somente numeros): ");
    scanf("%s", chave);
    posicao = extracao(chave, M);
    printf("\nExtracao: %d\n", posicao);
    posicao = enlacamento(chave, M, 1);
    printf("Enlacamento deslocado: %d\n", posicao);
    posicao = enlacamento(chave, M, 2);
    printf("Enlacamento limite: %d\n", posicao);
    posicao = dobra(chave, M);
    printf("Dobra: %d\n", posicao);
}