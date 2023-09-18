#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>
#include "forca.h"

//variáveis globais
char palavraSecreta[TAMANHO_PALAVRA];
int chutesDados;
char chutes[26];

void abertura(){
	
    printf("****************************\n");
    printf("*Bem Vindo ao Jogo da Forca*\n");
    printf("****************************\n");
}

/*captura um novo chute;
A variável aqui é diferente da variável
que está no main, mesmo tendo o mesmo nome.
Uma dica é colocar
outro nome para a variável que está na função.
As variáveis só existem no contexto onde são declaradas.
*/
void chuta(){
	
    char chute;
    printf("Qual letra? ");
    scanf(" %c", &chute);

    chutes[chutesDados] = chute;
    chutesDados++;
}

int jaChutou(char letra){
	
    int achou = 0;

    for(int j = 0; j < chutesDados; j++){
    	
        if(chutes[j] == letra){
        	
            achou = 1;
            break;
        }
    }

    return achou;
}

void desenharForca(){
	
    int erros = chutesErrados();

    printf("  _______      \n");
    printf(" |/      |     \n");
    printf(" |      %c%c%c \n", (erros>=1 ? '(' : ' '), (erros>=1 ? '_' : ' '), (erros>=1 ? ')' : ' '));
    printf(" |      %c%c%c \n", (erros>=3 ? '\\' : ' '), (erros>=2 ? '|' : ' '), erros>=3 ? '/' : ' ');
    printf(" |       %c    \n", (erros>=2 ? '|': ' '));
    printf(" |      %c %c  \n", (erros>=4 ? '/': ' '), (erros>=4 ? '\\' : ' '));
    printf(" |             \n");
    printf("_|___          \n");
    printf("\n\n");

    for(int i = 0; i < strlen(palavraSecreta); i++){
    	
            int achou = jaChutou(palavraSecreta[i]);

            if(achou){
            	
                printf("%c ", palavraSecreta[i]);
            }
            else{
            	
                printf("_ ");
            }
        }
    printf("\n");
}

void adicionaPalavra(){
	
    char quer;

    printf("Voce deseja adicionar uma nova palavra no jogo? (S/N)");
    scanf(" %c", &quer);

    if(quer == 'S'){
    	
        char novaPalavra[TAMANHO_PALAVRA];
        printf("Qual a nova palavra? ");
        scanf("%s", novaPalavra);

        FILE* f;

        f = fopen("palavras.txt", "r+");
        if(f == 0){
        	
        	printf("Desculpe, banco de dados não disponível\n\n");
        	printf("Tente novamente mais tarde.");
        	exit(1);
        }

        int qtd;
        fscanf(f, "%d", &qtd);
        qtd++;

        fseek(f, 0, SEEK_SET); //posiciona no começo
        fprintf(f, "%d", qtd);

        fseek(f, 0, SEEK_END); //posiciona no final
        fprintf(f, "\n%s", novaPalavra);

        fclose(f);
    }
}

void escolhePalavra(){
	
    FILE* f;

    f = fopen("palavras.txt", "r");
    if(f == 0){

        printf("Desculpe, banco de dados não disponível\n\n");
        printf("Tente novamente mais tarde.");
        exit(1);
    }

    int qtdPalavras;
    fscanf(f, "%d", &qtdPalavras);

    srand(time(0));
    int randomico = rand() % qtdPalavras;

    for(int i = 0; i <= randomico; i++){
        
        fscanf(f, "%s", palavraSecreta);
    }
    fclose(f);
}

int acertou(){

    for(int i = 0; i < strlen(palavraSecreta); i++)
        if(!jaChutou(palavraSecreta[i])){

        return 0;
    }
    return 1;
}

int chutesErrados(){
	
    int erros = 0;

    for(int i = 0; i < chutesDados; i++){
    	
        int existe = 0;

        for(int j = 0; j < strlen(palavraSecreta); j++){
        	
            if(chutes[i] == palavraSecreta[j]){
            	
                existe = 1;
                break;
            }
        }
        if(!existe) erros++; 
    }
    return erros;
}

int enforcou(){
	
    return chutesErrados() >= 5;
}


int main(){
	
    setlocale(LC_ALL, "Portuguese");

    escolhePalavra();
    abertura();

    do{
        desenharForca();
        chuta();

    }while(!acertou() && !enforcou());


    if(acertou()){

        printf("Parabens! Voce acertou!!!\n\n");
        printf("         _____________     \n");
        printf("         '._==_==_=_.'     \n");
        printf("         .-\\:      /-.     \n");
        printf("        | (|:.     |) |    \n");
        printf("         '-|:.     |-'     \n");
        printf("           \\::.    /       \n");
        printf("            '::. .'        \n");
        printf("              ) (          \n");
        printf("            _.' '._        \n");
        printf("           |||||||||       \n");
        printf("                            \n");

    }else{

        printf("Mas que pena, voce foi enforcado!\n");
        printf("A palavra secreta era: %s.\n\n", palavraSecreta);

        printf("         _______________        \n");
        printf("        /               \\       \n");
        printf("       /                 \\      \n");
        printf("     //                   \\/\\   \n");
        printf("     \\|   XXXX     XXXX   | /   \n");
        printf("      |   XXXX     XXXX   |/    \n");
        printf("      |   XXX       XXX   |     \n");
        printf("      |                   |     \n");
        printf("      \\__      XXX      __/     \n");
        printf("        |\\     XXX     /|       \n");
        printf("        | |           | |       \n");
        printf("        | I I I I I I I |       \n");
        printf("        |  I I I I I I  |       \n");
        printf("        \\_             _/       \n");
        printf("          \\_         _/         \n");
        printf("            \\_______/           \n");
        printf("\n\n");
        
    }
    adicionaPalavra();
}
