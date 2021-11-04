/*
    AUTHORS:
    Andrea Cecchini                -> andrea.cecchini13@studio.unibo.it
    Nicolò D'Addabbo               -> nicolo.daddabbo@studio.unibo.it
    Leonardo David Matteo Magnani  -> leonardo.magnani6@studio.unibo.it
    Luca Oskari Fiumanò            -> lucaoskari.fiumano@studio.unibo.it
*/

#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#define LENGHT 100

//Questa funzione permette di ottenere una stringa pseudo-casuale
void randomString(char *, size_t);
/*
Questa funzione permette di simulare la 'decryptazione' della stringa casuale
in quella inserita dall'utente.
*/
void decrypted(char *, char *);

void waiting(float seconds);


int main(){
    char initString[LENGHT+1];
    char cryptedString[LENGHT+1];
    //Inserimento della stringa di input da parte dell'utente
    printf("Inserire qui sotto la stringa: \n");
    fgets(initString, LENGHT, stdin);
    randomString(cryptedString, strlen(initString));
    initString [strcspn(initString, "\n\r")] = 0;
    cryptedString [strcspn(cryptedString, "\n\r")] = 0;
    decrypted(cryptedString, initString);
    return 0;
}


void randomString(char *cryptedString, size_t lenght) {
    srand(time(NULL));
    //Questo ciclo permette di riempire i valori del vettore stringa con valori casuali
    for (int i = 0; i < lenght-1; i++)
    {
        cryptedString[i] = 'A' + (rand() % 26);
    }
    cryptedString[lenght] = '\0';
}

bool isDecrypted(char *cryptedString, char *original){
    for(int i = 0 ; i < strlen(cryptedString) ; i++){
        if(cryptedString[i] != original[i]){
            return false;
        }
    }

    return true;
}


//Questa funzione permette di simulare la decriptazione del messaggio nell'input iniziale dell'utente
void decrypted(char *cryptedString, char *result){
    int index[strlen(cryptedString)];
    int i;
    int count= 0;
    printf("Stringa criptata\n%s", cryptedString);
    //array[0] = result[0];
    //Ritorno alla parte inziale della stringa
    do{
        printf("\r");
        i = rand()%(strlen(result));
        cryptedString[i] = result[i];
        for(int j = 0; j < strlen(result); j++){
            printf("%c", cryptedString[j]);
        }
        waiting(0.1);
    }while(!isDecrypted(cryptedString, result));
}




    /*
    do{
        printf("\r");
        for (int k = 0; k < strlen(cryptedString); k++) {
            printf("%c", cryptedString[k]);
        }
        i = rand()%(strlen(result));
        if(cryptedString[i] != result[i])
            count++;
        cryptedString[i] = result[i];
        waiting(0.1);
    }while(count < strlen(cryptedString));
    */




void waiting(float seconds){
    clock_t now = clock();
    for( ; clock() - now  < seconds * CLOCKS_PER_SEC; );  // Wait seconds
}
