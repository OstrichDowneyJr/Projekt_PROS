#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define TAB_SIZE 64 // maksymalna dlugosc jednego wymiaru tablicy 


// konwencja adresowania (x,y)--->(i%user_size,i/user_size)

int main(void){

    int cluster = 2;
    int treshhold; //? poziom zapelniania komorek z przypadkowej funkcji 
    int user_size; //? rozmiar tablicy wybrany przez urzytkownika


    //? rezerwowanie pamiecie dla tablicy
    int* tab = (char*) malloc(sizeof(int) * TAB_SIZE*TAB_SIZE); // pamiec dla tablicy 
    if(tab == NULL) { 
        printf("Error! memory not allocated.");
        exit(0);
    }

    //? wybor rozmiaru tablicy
    printf("Podaj rozmiar tablicy, maks %d\n", TAB_SIZE);
    scanf("%d",&user_size);
    while (user_size>TAB_SIZE){
        printf("Rozmiar tablicy za duży, podaj poprawny rozmiar\n");
        scanf("%d",&user_size);
    }

    int* tab_zmian = (char*) malloc(sizeof(int) * TAB_SIZE*TAB_SIZE/2); // pamiec dla tablicy 
        if(tab_zmian == NULL) { 
            printf("Error! memory not allocated.");
            exit(0);
        }

    //? inicjowanie przypadkowosci w kodzie 
    time_t tt;
    int seed = time(&tt); 
    srand(seed);

    //? podaj jakie prawdopodobienstwo zapelnienia komorki 
    printf("Podaj prawdopodobienstwo\n");
    scanf("&d",&treshhold);

    //? wypelnianie tablicy
    for(int i = 0; i < user_size*user_size; i++){
            int guess = rand()%100;
            if(guess>treshhold) tab[i]=1; 
            else tab[i]=0;
        
    }

    //?inicjalizacja klastrów
    for(int i = 0; i < user_size*user_size; i++){
            if (tab[i]==1){
                tab[i]=cluster;
                continue;
        }
    }

    // zmiana nazwenictwa dla wygody czytania
    int poprzedni = i-1; 
    int dolny = (i%user_size)-1;
    int aktualny = i; 

    //? numerowanie klastrow
    for(int i = 0; i < user_size*user_size; i++){
            if(tab[aktualny]==1){ // czy wgl pracujemy na wlasciwej komórce 
                if(tab[poprzedni]==cluster) && (tab[dolny]==cluster){
                    tab[aktualny]=cluster; 
                }
                else if( tab[poprzedni]!=cluster ) && (tab[dolny]==cluster){
                    tab[aktualny]=cluster;
                    tab_zmian[poprzedni]=cluster;
                }
                else if (tab[dolny]==0) && (tab[poprzedni]==cluster){
                    tab[aktualny]=cluster;
                }
                else if(tab[dolny]==cluster) && (tab[poprzedni]==0){
                    tab[aktualny]=cluster;
                }
                else if(i%user_size==0) && (tab[dolny]==cluster){//przypadek kiedy jestesmy w pierwszej kolumnie
                    tab[aktualny]=cluster;
                }
                else if(i/n==0) && (tab[poprzedni]==cluster){//przypadke kiedy jestesmy w pierwszym rzedzie
                    tab[aktualny]=cluster;
                }
                else{
                    cluster=+1;
                    tab[aktualny]=cluster;
                }
            }
        }


    //podmiana klastrow niewlasciwie ponumerowanych 
    for(int k=cluster,k>1,k--){
        if(tab_zmian[k]!=0){
            for(int i = 0; i < user_size*user_size; i++){
                if (tab[i]==k){
                    tab[i]=tab[k];
                }   
            }
        }
    }
    //prerkolacja 
    //*(i%user_size==0 && i%user_size==user_size-1)
    //*(i/user_size==0 && i/user_size==user_size-1)
    for(int k=cluster,k>1,k--){
        for(int i=0,i<user_size,i++){
            
        }
    }

    free(tab);
    return 0; 

}
