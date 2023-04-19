//**************************************************************************//
//                                                                          //
//                                                                          //
//                                   Projekt 1                              //
//                                Práca s textom                            //
//                                  Jakub Vaňo                              //
//                                                                          //
//                                                                          //
//**************************************************************************//

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define stringlen 102

//prevod mena na číslo
char *prevod(char *buffer){
       for(int i = 0; buffer[i] != '\0'; i++){
            if (('a' <= buffer[i] && buffer[i] <= 'c') || ('A' <= buffer[i] && buffer[i] <= 'C')) buffer[i] = '2';
            if (('d' <= buffer[i] && buffer[i] <= 'e') || ('D' <= buffer[i] && buffer[i] <= 'E')) buffer[i] = '3';
            if (('f' <= buffer[i] && buffer[i] <= 'h') || ('F' <= buffer[i] && buffer[i] <= 'H')) buffer[i] = '4';
            if (('i' <= buffer[i] && buffer[i] <= 'k') || ('I' <= buffer[i] && buffer[i] <= 'K')) buffer[i] = '5';
            if (('l' <= buffer[i] && buffer[i] <= 'n') || ('L' <= buffer[i] && buffer[i] <= 'N')) buffer[i] = '6';
            if (('o' <= buffer[i] && buffer[i] <= 's') || ('O' <= buffer[i] && buffer[i] <= 'S')) buffer[i] = '7';
            if (('t' <= buffer[i] && buffer[i] <= 'v') || ('T' <= buffer[i] && buffer[i] <= 'V')) buffer[i] = '8';
            if (('w' <= buffer[i] && buffer[i] <= 'z') || ('W' <= buffer[i] && buffer[i] <= 'Z')) buffer[i] = '9';
            if (buffer[i] == '+') buffer[i] = '0';
        }
    return buffer;
}

char* kontrolacisla(char *buffer){
    for(int i = 0; buffer[i] != '\0'; i++){
            if (buffer[i] == '+')
            buffer[i] = '0';
    }
    return buffer;
}

int main(int argc, char *argv[]){
    char *CISLO;
    char previusbuff[stringlen];
    char savebuff[stringlen];
    char buffer[stringlen];
    int i = 0;
    if(argc >= 2){
        CISLO = argv[1];
        //ak vstup nieje číslo
        if(!isdigit(*CISLO)){
            fprintf(stderr, "Zly vstup, zadaj cislo\n");
            return 1;
        }
    }
    else{
        //výstup bez zadania hľadaného čísla
        while(fgets(buffer, stringlen, stdin) != NULL){
            strcpy(savebuff, buffer);
            printf("%.*s, %s", (int)(strlen(savebuff))-1, savebuff, fgets(buffer + 1, stringlen, stdin));
            i = 1;
        }
    }
    //čítanie riadka zo súbora
    while(fgets(buffer, stringlen, stdin) != NULL){
        strcpy(savebuff, buffer);
        if(strlen(buffer) > stringlen - 2){
            fprintf(stderr, "Prilis dlhy vstup\n");
            return 1;
        }
        //podmianka či je buffer číslo alebo meno
        if(kontrolacisla(buffer) && isdigit(buffer[1])){
            //vyhodnotenie
            if(strstr(buffer, CISLO) != NULL){
                //výpis
                printf("%.*s, %s", (int)(strlen(previusbuff))-1, previusbuff, savebuff);
                i++;
            }
        }
        //vyhodnotenie mena
        else if(strstr(prevod(buffer), CISLO) != NULL){
                //výpis
                printf("%.*s, %s", (int)(strlen(savebuff))-1, savebuff, fgets(buffer, stringlen, stdin));
                i++;
            }
        strcpy(previusbuff, savebuff);
    }
    //podmienka ak hľadané čislo nebolo v súboraňe
    if(i == 0){
        printf("Not found\n");
        return 1;
    }
    return 0;
}