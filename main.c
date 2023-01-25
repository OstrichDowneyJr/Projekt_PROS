#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define TAB_SIZE 64 // maksymalna dlugosc jednego wymiaru tablicy 
typedef enum { false, true } bool;

// konwencja adresowania (x,y)--->(i%user_size,i/user_size)

int main(void){

    int index;
    int cluster = 2;
    int treshhold; //? poziom zapelniania komorek z przypadkowej funkcji 
    int user_size; //? rozmiar tablicy wybrany przez urzytkownika


    //? rezerwowanie pamiecie dla tablicy
    int* tab = (int*) malloc(sizeof(int) * TAB_SIZE*TAB_SIZE); 
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

//? rezerwowanie pamieci dla tablicy zmain 
    int* tab_zmian = (int*) malloc(sizeof(int) * TAB_SIZE*TAB_SIZE/2);  
        if(tab_zmian == NULL) { 
            printf("Error! memory not allocated.");
            exit(0);
        }

    int* tab_wynik = (int*) malloc(sizeof(int) *TAB_SIZE);  
            if(tab_wynik == NULL) { 
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
    //TODO naprawic indeksowanie 
    //? numerowanie klastrow
    for(int i = 0; i < user_size*user_size; i++){
            if(tab[i]==1){ // czy wgl pracujemy na wlasciwej komórce 
                if(tab[poprzedni]==cluster) && (tab[dolny]==cluster){
                    tab[i]=cluster; 
                }
                else if( tab[poprzedni]!=cluster ) && (tab[dolny]==cluster){
                    tab[i]=cluster;
                    tab_zmian[poprzedni]=cluster;
                }
                else if (tab[dolny]==0) && (tab[poprzedni]==cluster){
                    tab[i]=cluster;
                }
                else if(tab[dolny]==cluster) && (tab[poprzedni]==0){
                    tab[i]=cluster;
                }
                else if(i%user_size==0) && (tab[dolny]==cluster){//przypadek kiedy jestesmy w pierwszej kolumnie
                    tab[i]=cluster;
                }
                else if(i/n==0) && (tab[poprzedni]==cluster){//przypadke kiedy jestesmy w pierwszym rzedzie
                    tab[i]=cluster;
                }
                else{
                    cluster=+1;
                    tab[i]=cluster;
                }
            }
        }


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
    //prerkolacja 
    //*(i%user_size==0 && i%user_size==user_size-1)
    //*(i/user_size==0 && i/user_size==user_size-1)
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
            if(top&&down){
                tab_wynik[index]=k;
                index++;
                continue;
            }
            if(left&&right){
                tab_wynik[index]=k;
                index++;
                continue;
            }
            
        }

    }
    if(index==0){
        printf("Nie występują klastry perkolujace!");
    }
    else{
        printf("Wystepuja nastepujace klastry perkolujace:\n");
        for (size_t i = 0; i < index; i++){
            printf("%d,\t",tab_wynik[i]);
        }
    }
    
    

    free(tab);
    free(tab_zmian);
    free(tab_wynik);
    return 0; 

}
