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


//DICHIARAZIONE DELLE FUNZIONI

//Questa funzione permette di ottenere una stringa pseudo-casuale
void randomString(char *, size_t);
/*
Questa funzione permette di simulare la 'decryptazione' della stringa casuale
in quella inserita dall'utente.
*/
void decrypted(char *, char *);
/*
Questa funzione permette di controllare se la stringa e` stata "decryptata" completamente nell'originale.
Richiede come parametri due puntatori a carattere, in questo ordine
- char * : puntatore a carattere della stringa da "decryptare"
- char * : puntatore a carattere della stringa originale
*/
bool isDecrypted(char *, char *);
//Questa funzione permette di effettuare un delay in secondi esplicitati nell'argomento
void waiting(float seconds);


int main(){
    //LENGHT + \0
    char initString[LENGHT+1];
    char cryptedString[LENGHT+1];
    //Inserimento della stringa di input da parte dell'utente
    printf("Inserire qui sotto la stringa: \n");
    fgets(initString, LENGHT, stdin);
    randomString(cryptedString, strlen(initString));
    initString [strcspn(initString, "\n\r")] = 0;
    cryptedString [strcspn(cryptedString, "\n\r")] = 0;
    //Chiamata alla funzione di "decryptazione"
    decrypted(cryptedString, initString);
    return 0;
}



void randomString(char *cryptedString, size_t lenght) {
    srand(time(NULL));
    //Questo ciclo permette di riempire i valori del vettore stringa con valori casuali
    for (int i = 0; i < lenght - 1; i++)
    {
        cryptedString[i] = 'A' + (rand() % 26);
    }
    cryptedString[lenght-1] = '\0';
}

bool isDecrypted(char *cryptedString, char *original){
    for(int i = 0 ; i < strlen(cryptedString) ; i++){
        if(cryptedString[i] != original[i]){
            return false;
        }
    }

    return true;
}

void decrypted(char *cryptedString, char *result){
    srand(time(NULL));
    int index[strlen(cryptedString)];
    int i;
    int count= 0;
    printf("Stringa criptata\n%s", cryptedString);
    //array[0] = result[0];
    //Ritorno alla parte inziale della stringa
    do{
        printf("\r");
        /*
        Generazione casuale dell'indice della stringa che verra decriptata
        Questo accesso alla stringa permette di dare l'effetto ottico di decryptazione dei caratteri in modo non sequeziale.
        */
        i = rand()%(strlen(result));
        //Se i caratteri sono uguali non si ha la necessita` di riscreve la stringa, e per non sprecare istruzioni attraverso continue si esegue un salto alla fine del for.
        if(cryptedString[i]==result[i])
            continue;
        //Assegnazione del carattere "decryptato" alla stringa stampata
        cryptedString[i] = result[i];
        for(int j = 0; j < strlen(result); j++){
            /*
             Se la stringa non e` stata "decryptata" e i valori sono diversi allora viene generato un carattere casuale da mettere nella cella j.
             Queste istruzioni mi permettono di dare l'effetto ottico desiderato, come da clip.
            */
            if(cryptedString[j]!= result[j])
                cryptedString[j] = 11 + rand()% (40-11+1);
            //Stampa carattere per carattere la stringa con un carattere "decryptato" in piu`
            printf("%c", cryptedString[j]);
        }
        //0.05s delay per generare l'effetto ottico e non avere il risultato immediatamente
        waiting(0.05);
    }while(!isDecrypted(cryptedString, result));
}

void waiting(float seconds){
    clock_t now = clock();
    for( ; clock() - now  < seconds * CLOCKS_PER_SEC; );  // Wait seconds
}

