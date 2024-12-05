#ifndef TEST_PRIMALITE_INCLUDED
#define TEST_PRIMALITE_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//  Structure de liste 
typedef struct{
    int* element;
    int taille;
}liste;


/*  |----------------------------------------------------------------------------------------------------------------|
    |----------------------------------------------------------------------------------------------------------------|
    |                                           FONCTIONS INTERMEDIAIRES                                             |   
    |----------------------------------------------------------------------------------------------------------------|
    |----------------------------------------------------------------------------------------------------------------|                                                     
 */
/*  Test de Fermat : 
        - Si renvoie 0 alors n n'est pas premier
        - si renvoie 1 alors n est premier avec proba supérieur à 1-1/(2^k) 
    Remarque : Nécessite l'existence de c tel que c^{n-1} != 1 [n] 
*/
int test_fermat(int n, int k);

/*  Test de Solovay-Strassen : 
        - Si renvoie 0 alors n n'est pas premier
        - si renvoie 1 alors n est premier avec proba supérieur à 1-1/(2^k)
*/
int test_solovay_strassen(int n, int k);

/*  Test de Miller-Rabin : 
        - Si renvoie 0 alors n n'est pas premier
        - si renvoie 1 alors n est premier avec proba supérieur à 1-1/(4^k)
*/
int test_miller_rabin(int n, int k);


/*  |----------------------------------------------------------------------------------------------------------------|
    |----------------------------------------------------------------------------------------------------------------|
    |                                              FONCTIONS PRIMAIRES                                               |   
    |----------------------------------------------------------------------------------------------------------------|
    |----------------------------------------------------------------------------------------------------------------|                                                     
 */
int ordre_deux(int m);          //  La 2-valuation de m
int puissance(int m, int e);    //  Renvoie m puissance e
int modulo(int a, int b);                       //  Renvoie a modulo b
int puissance_modulo(int m, int e, int p);      //  Renvoie m^e modulo p
int inverse(int a, int p);                      //  Inverse de a dans Z/pZ lorsque pgcd(a,p)=1
int pgcd(int a, int b);                 //  PGCD
int partie_entiere(double n);           //  Partie entière de n
int racine_carree_entiere_mn(int n);    //  Racine carrée entière de n (algo naïf)
int jacobi(int a, int b);       //  Symbole de Jacobi

#endif // TEST_PRIMALITE_INCLUDED