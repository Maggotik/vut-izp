#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

typedef struct {
  int rows;
  int cols;
  unsigned char *cells;
} Map;

void map_init(char *file, Map *m);
int map_load(char *file, Map *m);
void map_free(Map *map);
bool isborder(Map *map, int r, int c, int border);
int start_border(Map *map, int r, int c, int leftright);
bool map_test(char *file, Map *map);
int pathfinding(Map *map, int r, int c, int leftright);

int main(int argc, char *argv[]){
    int hand;
    if(argc == 2){
        if (strcmp(argv[1], "--help") == 0){
            printf("--test subor.txt = zkontroluje, ze subor dany druhym argumentem programu obsahuje riadnu definiciu mapy bludiska. Ak odpoveda vypise 'Valid' v opacnom pripade 'Invalid'\n");
            printf("--rpath R C subor.txt = hlada priechod bludiskom na vstupu na riadku R a stlpci C. Priechod hlada pomocou pravidla pravej ruky (prava ruka vzdy na stene).\n");
            printf("--lpath R C subor.txt = hlada priechod bludiskom na vstupu na riadku R a stlpci C. Priechod hlada pomocou pravidla lavej ruky (lava ruka vzdy na stene).\n");
            return 0;
        }
    }
    Map map;
    if (strcmp(argv[1], "--test") == 0){
        map_init(argv[2], &map);
        bool test = map_test(argv[2], &map);
        if (test == true){
            printf ("Valid\n");
        }
        else printf ("Invalid\n");
        map_free(&map);
        return 0;
    }
    if (strcmp(argv[1], "--rpath") == 0){
        hand = -1;
    }
    else hand = 1;
    if (argc == 5){
        int r = atoi(argv[2])-1;
        int c = atoi(argv[3])-1;
        map_init(argv[4], &map);
        bool test = map_test(argv[4], &map);
        if (test == false){
            printf("Invalid map\n");
            map_free(&map);
            return 1;
        }
        pathfinding(&map, r, c, hand);
        map_free(&map);
    }
    return 0;
}

void map_init(char *file, Map *m){
    FILE *map;
    map = fopen(file, "r");
    fscanf(map, "%d %d", &m->rows, &m->cols);
    m->cells = malloc(((m->rows * m->cols) + 1)*  sizeof(unsigned char));
    fclose(map);
}

int map_load(char *file, Map *m){
    FILE *map;
    map = fopen(file, "r");
    if(map==NULL)return -1;
    int c;
    int i = 0;
    int counter;
    while ((c != '\n' && i <= (m->rows * m->cols))){
        c = getc(map);
    }
    while ((c != EOF)){
        c = getc(map);
        if (isdigit(c)){
            m->cells[i] = c;
            i++;
        }
        counter++;
    }
    m->cells[i] = '\0';
    fclose(map);
    return i;
}

void map_free(Map *map){
    free(map->cells);
}

bool isborder(Map *map, int r, int c, int border){
    int n = map->cells[(r * map->cols) + c] - '0';
    return n & (1 << border);
}

int start_border(Map *map, int r, int c, int leftright){
    // -1 = prava 1 = lava
    int evenodd;
    if((r % 2) == (c % 2)){
        evenodd = 0;
    }
    else evenodd = 1;
    //zhora
    if(r == 0){
                if (isborder(map, r, c, 2) == true){
            return -1;
        }
         if (leftright == -1){
             return 0;
         }
         else{
             return 1;
         }
    }
    //zdola
    if(r == map->rows){
        if (isborder(map, r, c, 2) == true){
            return -1;
        }
        if (leftright == -1){
            return 1;
        }
        else{
            return 0;
        }    
    }
    //zlava
    if(c == 0){
        if (isborder(map, r, c, 0) == true){
            return -1;
        }
        if (leftright == -1){
            if (evenodd == 0){
                return 1;
                }
            else{
                return 2;
            }
        }   
        else {
            if (evenodd == 0){
                return 2;
            }
            else{
                return 1;
            }
        } 
    }
    //sprava
    if(c == map->cols){
        if (isborder(map, r, c, 1) == true){
            return -1;
        }
        if (leftright == -1){
            if (evenodd == 0){
                return 2;
                }
            else{
                return 0;
            }
        } 
        else{
            if (evenodd == 0){
                return 0;
            }
            else{
                return 2;
            }
        } 
    }
    return 0; 
}

int my_start_border(Map *map, int r, int c){
    if(r == 0){
        if(r%2==c%2)
        if (!isborder(map, r, c, 2))
        return 2;
    }
    //zdola
    if(r == map->rows-1){
        if(r%2!=c%2)
        if (!isborder(map, r, c, 2))
        return 2;
    }
    //zlava
    if(c == 0){
        if (!isborder(map, r, c, 0))
        return 1;
    }
    //sprava
    if(c == map->cols-1){
        if (!isborder(map, r, c, 1))
        return 0;
    }
    return -1;
}

bool map_test(char *file, Map *map){
    bool left;
    bool right;
    bool up;
    bool bottom;
    int count = map_load(file, map);
    if(count<=0)return false;
    for (int i = 0; i < map->rows; i++){
        for(int j = 0; j < map->cols; j++){
            left = isborder(map, i, j, 1);
            if(j + 1 < map->cols){
                right = isborder(map, i, j + 1, 0);
                 if (left != right)
                return false;
            }
            if ((i % 2) != (j % 2) && (i + 1 < map->rows)){
                up = isborder(map, i, j, 2);
                bottom = isborder(map, i + 1, j, 2);
                if (up != bottom)
                    return false;
            } 
        }
    }
    if ((map->rows * map->cols) != count){
        return false;
    }
    return true;
}

int get_move(Map *map, int r, int c, int leftright, int last_border, int *move){
    if(last_border==0)last_border=1;
    else
    if(last_border==1)last_border=0;
    if(r%2==c%2)leftright*=-1;
    for(int i = 0; i < 3 && i > -3;){
        i += leftright;
        if(!isborder(map,r,c,(last_border+i+3)%3)){
            switch ((last_border+i+3)%3)
            {
            case 0: 
                    move[1]=-1; 
                    move[0]=0;
                    break;
            case 1: 
                    move[1] = 1; 
                    move[0]=0; 
                    break;
            case 2:
                if(r%2==c%2)
                    move[0]=-1;
                else
                    move[0]=1;

                move[1]=0;
                break;
            }
            return (last_border+i+3)%3;
        }
    }
    return -1;
}

int is_in_map(Map *map, int r, int c){
    if(r<0||r>=map->rows)
    return 0;
    if(c<0||c>=map->cols)
    return 0;
    return 1;
}

int pathfinding(Map *map, int r, int c, int leftright){
    int last_border = my_start_border(map, r, c);
    if (last_border == -1){
        printf("Cannot enter\n");
        return 1;
    }
    int move[2] = {0,0};
    while(is_in_map(map,r,c) && (last_border = get_move(map, r, c, leftright, last_border, move))!=-1){
        printf("%d,%d\n",r+1,c+1);
        r+=move[0];
        c+=move[1];
    }
    return 0;
}
    