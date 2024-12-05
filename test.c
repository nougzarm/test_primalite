#include "test.h"

/* En fonction de la valeur de choix_test :
    1. Test de primalité de Fermat sur n (avec k tentatives)
    2. Test de primalité de Solovay-Strassen sur n (avec k tentatives)
    3. Test de primalité de Miller-Rabin sur n (avec k tentatives)
*/

int main() {
    // CHOIX DE L'OPÉRATION --------------------------------------------------------
    int choix_test = 3;

    // CONFIGURATION - CHOIX DE L'ENTIER n et du nombre k de tentatives ------------
    int n = 1874;
    int k = 78;

    // AFFICHAGE DE LA CONFIGURATION -----------------------------------------------
    printf("----------------------------------------------------------------- \n");
    printf("Définitions :\n  - Test de primalité sur n = %d\n", n);
    printf("  - Nombre de tentative k = %d", k); printf("\n\n");
    
    // LANCEMENT DE L'ALGORITHME ---------------------------------------------------
    test(choix_test, n, k);
    printf("\n----------------------------------------------------------------- \n");

    return 1;
}


// Définition des tests
void test(int choix_test, int n, int k){
    if(choix_test == 1){
        int resultat = test_fermat(n, k);
        if(resultat == 0){
            printf("D'après le test de Fermat, %d n'est pas premier.", n);
        }
        else{
            printf("D'après le test de Fermat, %d est premier avoir une probabilité d'au moins 1-1/2^%d", n, k);
        }
    }
    else if(choix_test == 2){
        int resultat = test_solovay_strassen(n, k);
        if(resultat == 0){
            printf("D'après le test de Solovay-Strassen, %d n'est pas premier", n);
        }
        else{
            printf("D'après le test de Solovay-Strassen, %d est premier avoir une probabilité d'au moins 1-1/2^%d", n, k);
        }
    }
    else if(choix_test == 3){
        int resultat = test_miller_rabin(n, k);
        if(resultat == 0){
            printf("D'après le test de Miller-Rabin, %d n'est pas premier", n);
        }
        else{
            printf("D'après le test de Miller-Rabin, %d est premier avoir une probabilité d'au moins 1-1/4^%d", n, k);
        }
    }
    return;
}