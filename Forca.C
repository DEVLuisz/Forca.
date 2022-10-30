#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include "functions.h"

char secretWord[WORD_SIZE];
char chutes[26];
int chutesDados = 0;

void logo(){
    printf("/*************************/\n");
    printf("/      Jogo da Forca      /\n");
    printf("/ Utilize letras maiusculas/ \n");
    printf("/     Powered by Void    /\n\n");
    printf("/***********************/\n\n");
}

void chuts(){
    char chute;
    scanf(" %c", &chute);

    chutes[chutesDados] = chute;
    chutesDados ++;
}

int jaChutou(char letra){
    int achou = 0;

    for(int j = 0; j < chutesDados; j ++){
        if(chutes[j] == letra){
            achou = 1;
            break;
        }
    }

    return achou;
}

void drawGallows(){

    int mistakes = chutesErrados();

    printf("  _______       \n");
    printf(" |/      |      \n");
    printf(" |      %c%c%c  \n", (mistakes>=1?'(':' '), (mistakes>=1?'_':' '), (mistakes>=1?')':' '));
    printf(" |      %c%c%c  \n", (mistakes>=3?'\\':' '), (mistakes>=2?'|':' '), (mistakes>=3?'/': ' '));
    printf(" |       %c     \n", (mistakes>=2?'|':' '));
    printf(" |      %c %c   \n", (mistakes>=4?'/':' '), (mistakes>=4?'\\':' '));
    printf(" |              \n");
    printf("_|___           \n");
    printf("\n\n");

    for(int i = 0; i < strlen(secretWord); i ++){

        int achou = jaChutou(secretWord[i]);

        if(achou) {
            printf("%c ", secretWord[i]);
        }
        else {
            printf("_ ");
        }
    }

    printf("\n");
}

void addWord(){

    char quer;

    printf("Deseja adicionar uma nova palavra? (S/N) \n");
    scanf(" %c", &quer);

    if(quer == 'S'){

        char newWord[WORD_SIZE];
        printf("Qual a nova palavra? ");
        scanf("%s", newWord);

        FILE* f;

        f = fopen("words.txt", "r+");
        if(f == 0){
            printf("Desculpe, erro no Banco de Dados.");
            exit(1);
        }

        int qtd;
        fscanf(f, "%d", &qtd);
        qtd ++;

        fseek(f, 0, SEEK_SET);
        fprintf(f, "%d", qtd);

        fseek(f, 0, SEEK_END);
        fprintf(f, "\n%s", newWord);

        fclose(f);
    }
}

void chooseWord(){
    FILE* f;

    f = fopen("words.txt", "r");

    if(f == 0){
        printf("Desculpe, erro no Banco de Dados.");
        exit(1);
    }

    int qtdDePalavras;
    fscanf(f, "%d", &qtdDePalavras);

    srand(time(0));
    int random = rand() % qtdDePalavras;

    for(int i = 0; i <= random; i ++){
        fscanf(f, "%s", secretWord);
    }

    fclose(f);
}

int win(){

    for(int i = 0; i < strlen(secretWord); i ++){
        if(!jaChutou(secretWord[i])){
            return 0;
        }
    }
    return 1;
}

int chutesErrados(){
    int mistakes = 0;

    for(int i = 0; i < chutesDados; i ++){
        int exist = 0;

        for(int j = 0; j < strlen(secretWord); j ++){

            if(chutes[i] == secretWord[j]){
                exist = 1;
                break;
            }
        }
        if(!exist) mistakes ++;
    }
    return mistakes;
}

int hanged(){

    return chutesErrados() >= 5;
}

int main() {
    setlocale(LC_ALL, "portuguese");

    chooseWord();
    logo();

    do {

        drawGallows();
        chuts();

    } while(!win() && !hanged());

    if(win()){
        wprintf(L"\nParabéns, você ganhou!\n\n");

        printf("       ___________      \n");
        printf("      '._==_==_=_.'     \n");
        printf("      .-\\:      /-.    \n");
        printf("     | (|:.     |) |    \n");
        printf("      '-|:.     |-'     \n");
        printf("        \\::.    /      \n");
        printf("         '::. .'        \n");
        printf("           ) (          \n");
        printf("         _.' '._        \n");
        printf("        '-------'       \n\n");
        wprintf(L"Desenvolvido por Luís - Void  \n");
    } else {
        wprintf(L"\nPuxa, o Luís foi enforcado!\n");
        printf("A palavra era **%s**\n\n", secretWord);

        printf("    _______________         \n");
        printf("   /               \\       \n");
        printf("  /                 \\      \n");
        printf("//                   \\/\\  \n");
        printf("\\|   XXXX     XXXX   | /   \n");
        printf(" |   XXXX     XXXX   |/     \n");
        printf(" |   XXX       XXX   |      \n");
        printf(" |                   |      \n");
        printf(" \\__      XXX      __/     \n");
        printf("   |\\     XXX     /|       \n");
        printf("   | |           | |        \n");
        printf("   | I I I I I I I |        \n");
        printf("   |  I I I I I I  |        \n");
        printf("   \\_             _/       \n");
        printf("     \\_         _/         \n");
        printf("       \\_______/           \n\n");
        wprintf(L"Desenvolvido por Luís - Void  \n");
    }
    addWord();
    system("pause");
}
