#include <stdio.h>
#include <stdlib.h>
#include <time.h>


typedef enum { false, true } bool;

int perkolacja(int user_size,int treshhold);

int main(int argc, char const *argv[])
{
    perkolacja(5,3);
    return 0;
}


// konwencja adresowania (x,y)--->(i%user_size,i/user_size)


int perkolacja(int user_size,int treshhold){

    int index = 0;
    int cluster = 2;    


    //? rezerwowanie pamiecie dla tablicy
    int* tab = (int*) malloc(sizeof(int) * user_size*user_size);
    if(tab == NULL) {
        printf("Error! memory not allocated.");
        exit(0);
    }


//? rezerwowanie pamieci dla tablicy zmain
    int* tab_zmian = (int*) malloc(sizeof(int) * user_size*user_size/2);
        if(tab_zmian == NULL) {
            printf("Error! memory not allocated.");
            exit(0);
        }
        for(int i=0;i<user_size*user_size/2;i++){
            tab_zmian[i]=0;
        }

    int* tab_wynik = (int*) malloc(sizeof(int) *user_size);
            if(tab_wynik == NULL) {
                printf("Error! memory not allocated.");
                exit(0);
            }

    //? inicjowanie przypadkowosci w kodzie
    time_t tt;
    int seed = time(&tt);
    srand(seed);


    //? wypelnianie tablicy
    for(int i = 0; i < user_size*user_size; i++){
            int guess = rand()%100;
            if(guess>treshhold) tab[i]=1;
            else tab[i]=0;

    }

    // printf("macierz bez klastrow\n");
    // for(int i=0;i<user_size*user_size;i++){
    //     if(i%user_size==0)printf("\n");
    //     printf("%d ",tab[i]);

    // }
    //         printf("\n");

    //?inicjalizacja klastrów
    for(int i = 0; i < user_size*user_size; i++){
            if (tab[i]==1){
                tab[i]=cluster;
                break;
        }
    }

    //? numerowanie klastrow
    for(int i = 0; i < user_size*user_size; i++){
        if(tab[i]==1){ // czy pracujemy na wlasciwej komórce?
            if(i%user_size!=0 && i/user_size!=0){// czy jestesmy na granicy?
                if(tab[i-1]!=0 && tab[i-user_size]!=0){//czy okoliczne komorki sa zerami?
                    if(tab[i-1]==tab[i-user_size]){
                        tab[i]=tab[i-1];
                    }
                    if(tab[i-1]!=tab[i-user_size]){
                        tab[i]=tab[i-user_size];
                        tab_zmian[tab[i-1]]=tab[i-user_size];
                    }
                }
                if(tab[i-1]!=0 && tab[i-user_size]==0){
                    if(tab[i-1]!=0){
                        tab[i]=tab[i-1];//? problem z inkrementacja clustra
                    }
                }
                if(tab[i-1]==0 && tab[i-user_size]!=0){
                    if(tab[i-user_size]!=0){
                        tab[i]=tab[i-user_size];
                    }
                }
                if(tab[i-1]==0 && tab[i-user_size]==0){
                    cluster++;
                    tab[i]=cluster;
                }
            }
            else if(i%user_size==0 && i/user_size!=0){ //pierwsza kolumna
                if(tab[i-user_size]!=0){
                    tab[i]=tab[i-user_size];
                }
                if(tab[i-user_size]==0){
                    cluster++;
                    tab[i]=cluster;
                }
            }
            else if(i%user_size!=0 && i/user_size==0){ // pierwszy rzad
                if(tab[i-1]!=0){
                    tab[i]=tab[i-1];
                }
                if(tab[i-1]==0){
                    cluster++;
                    tab[i]=cluster;
                }

            }
        }
    }

    // printf("macierz z klastrami\n");
    // for(int i=0;i<user_size*user_size;i++){
    //     if(i%user_size==0)printf("\n");
    //     printf("%d ",tab[i]);
    // }
    // printf("\n");

    // printf("macierz zmian\n");
    // for(int i=0;i<user_size*user_size/2;i++){
    //     printf("%d |",tab_zmian[i]);
    // }
    // printf("\n");


    //podmiana klastrow niewlasciwie ponumerowanych
    for(int k=cluster;k>1;k--){
        if(tab_zmian[k]!=0){
            for(int i = 0; i < user_size*user_size; i++){
                if (tab[i]==k){
                    tab[i]=tab[k];
                }
            }
        }
    }


    // printf("macierz z klastrami poprawiona\n");
    // for(int i=0;i<user_size*user_size;i++){
    //     if(i%user_size==0)printf("\n");
    //     printf("%d ",tab[i]);
    // }
    // printf("\n");

    //prerkolacja
    for(int k=cluster;k>1;k--){
        bool left = false;
        bool right = false;
        bool top = false;
        bool down = false;
        for(int i=0;i<user_size*user_size;i++){
            if(tab[i]==k){
                if(i%user_size==0) left = true;
                if(i%user_size==user_size-1) right = true;
                if(i/user_size==0) down = true;
                if(i/user_size==user_size-1) top = true;
            }
        }
        if(top&&down){
            tab_wynik[index]=k;
            index++;
        }
        else if(left&&right){
            tab_wynik[index]=k;
            index++;
        }

        }

    if(index==0){
        printf("Nie wystepuja klastry perkolujace!");
    }
    else{
        printf("Wystepuja nastepujace klastry perkolujace:\n");
        for (int i = 0; i < index; i++){
            printf("%d,\t",tab_wynik[i]);
        }
    }

    free(tab);
    free(tab_zmian);
    free(tab_wynik);

    return 0;
}