// TODO Napisz co masz wgl do zrobienie w tym projekcie 
// popros o rozmiar tablicy NxN
// wypełnij tablice 
// sprawdz jakie ma klastry wewnatrz
// ponumeruj kalstry 
// zaznacz które klastry są przeciekające 

#include <stdio.h>
#include <stdlib.h>
#include <time.h>



#define TAB_SIZE 64

int main(void){

    int treshhold; //? poziom zapelniania komorek z przypadkowej funkcji 
    int user_size; //? rozmiar tablicy wybrany przez urzytkownika

    // rezerwowanie pamiecie dla tablicy
    int* tab = (char*) malloc(sizeof(int) * TAB_SIZE*TAB_SIZE); // pamiec dla tablicy 
    if(tab == NULL) { 
        printf("Error! memory not allocated.");
        exit(0);
    }

    // wybor rozmiaru tablicy
    printf("Podaj rozmiar tablicy, maks %d\n", TAB_SIZE);
    scanf("%d",&user_size);

    while (user_size>TAB_SIZE){
        printf("Rozmiar tablicy za duży, podaj poprawny rozmiar\n");
        scanf("%d",&user_size);
    }

    //inicjowanie przypadkowosci w kodzie 
    time_t tt;
    int seed = time(&tt); 
    srand(seed);

    //podaj jakie prawdopodobienstwo zapelnienia komorki 
    printf("Podaj prawdopodobienstwo\n");
    scanf("&d",&treshhold);

    // wypelnianie tablicy
    for(int i = 0; i < user_size; i++){
        for (int j = 0; i < user_size; i++){
            int guess = rand()%100;
            if(guess>treshhold) tab[i*user_size + j]=1; //? wyrazenie w nawaiasach adresuje tablice jako 1-wymarowa do pracy
        }
    }



    free(tab);
    return 0; 

}