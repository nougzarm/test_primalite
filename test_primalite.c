#include "test_primalite.h"


/*  |----------------------------------------------------------------------------------------------------------------|
    |----------------------------------------------------------------------------------------------------------------|
    |                                           FONCTIONS INTERMEDIAIRES                                             |   
    |----------------------------------------------------------------------------------------------------------------|
    |----------------------------------------------------------------------------------------------------------------|                                                     
 */
int ordre_deux(int m){
    int i = 0;
    while (m % 2 != 0){
        i++;
        m = m/2;
    }
    return i;
}

int puissance(int m, int e){
    if ( e==0 ){
        return 1;
    }
    else if (( e%2==0 )&( e!=0 )){
        return puissance(m*m, e/2);
    }
    else {
        return m*puissance(m*m, (e-1)/2);
    }
}

int modulo(int a, int b){
    return a%b + (b * (a%b<0));
}

int puissance_modulo(int m, int e, int p){
    int result = 1;
    for (int i = 1; i <= e; i++){
        result = modulo(result, p)*m;
    }
    return modulo(result, p);
}

int pgcd(int a, int b){
    int r0 = a, r1 = b, r2 = r0%r1;
    while ( r2 != 0 ){
        r0 = r1;
        r1 = r2;
        r2 = modulo(r0, r1);
    }
    return r1;
}

int jacobi(int a, int b){
    if(b%2==0){
        return 0;
    }
    if(pgcd(a, b) != 1){
        return 0;
    }
    a = modulo(a, b);
    
    int signe = 1;
    int inter_reserve = 0;  // réserve pour le swap

    // Boucle de la 'réduction' via loi de réciprocité quadratique
    while ( ( b%a != 0 )&&( a != 2 ) ){
        if ( a%2 == 0 ){
            a = a/2;
            if ( (modulo(b, 8) == 3) || (modulo(b, 8) == 5) ){
                signe = signe*(-1);
            }
        }
        else {
            if ( ((a-1)*(b-1))%8 != 0 ){
            signe = signe*(-1);
            }
            inter_reserve = a;
            a = modulo(b, a);
            b = inter_reserve; 
        }
    }
    if ( a == 1 ){
        return signe;
    }
    if ( a == 2 ){
        int c = 1;
        if ( (modulo(b, 8) == 3) || (modulo(b, 8) == 5) ){
            c = -1;
        }
        return c*signe;
    }
    else{
        return 0;
    }
}


/*  |----------------------------------------------------------------------------------------------------------------|
    |----------------------------------------------------------------------------------------------------------------|
    |                                             FONCTIONS PRINCIPALES                                              |   
    |----------------------------------------------------------------------------------------------------------------|
    |----------------------------------------------------------------------------------------------------------------|                                                     
 */
/*  Test de Fermat : 
        - Si renvoie 0 alors n n'est pas premier
        - si renvoie 1 alors n est premier avec proba supérieur à 1-1/(2^k) 
    Remarque : Nécessite l'existence de c tel que c^{n-1} != 1 [n] 
*/
int test_fermat(int n, int k){
    int b;
    for(int i=0; i<k; i++){
        b = 2 + (rand()%(n-4));
        if(pgcd(n, b) == 1){
            if(puissance_modulo(b, n-1, n) != 1){
                return 0;
            }
        }
        else{
            return 0;
        }
    }
    return 1;
}


/*  Test de Solovay-Strassen : 
        - Si renvoie 0 alors n n'est pas premier
        - si renvoie 1 alors n est premier avec proba supérieur à 1-1/(2^k)
*/
int test_solovay_strassen(int n, int k){
    if(n==4){
        return 0;
    }
    if(n==2){
        return 1;
    }
    int b;
    for(int i=0; i<k; i++){
        b = 2 + (rand()%(n-4));
        if(pgcd(n, b) == 1){
            if(modulo(jacobi(b, n) - puissance_modulo(b, (n-1)/2, n), n) != 0){
                return 0;
            }
        }
        else{
            return 0;
        }
    }
    return 1;
}


/*  Test de Miller-Rabin : 
        - Si renvoie 0 alors n n'est pas premier
        - si renvoie 1 alors n est premier avec proba supérieur à 1-1/(4^k)
*/
int test_miller_rabin(int n, int k){
    int s = ordre_deux(n-1);
    int t = (n-1)/(puissance(2, s));
    int b; 
    int b_puissance_t;
    int b_puissance_finale;
    for(int j=0; j<k; j++){
        b = 2 + (rand()%(n-4));
        if(pgcd(n, b) == 1){
            b_puissance_t = puissance_modulo(b, t, n);
            if(b_puissance_t != -1 && b_puissance_t != 1){
                for(int i=1; i<s-1; i++){
                    b_puissance_finale = puissance_modulo(b_puissance_t, puissance(2, i), n);
                    if(b_puissance_finale == n-1){
                        break;
                    }
                    else if(b_puissance_finale == 1){
                        return 0;
                    }
                }
                b_puissance_finale = puissance_modulo(b_puissance_t, puissance(2, s-1), n);
                if(b_puissance_finale == n-1 || b_puissance_finale == 1){
                    return 0;
                }
            }
        }
        else{
            return 0;
        }
    }
    return 1;
}