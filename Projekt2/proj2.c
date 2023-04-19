//**************************************************************************//
//                                                                          //
//                                                                          //
//                                   Projekt 2                              //
//                                Iteračné výpočty                          //
//                                  Jakub Vaňo                              //
//                                                                          //
//                                                                          //
//**************************************************************************//

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define I_0 1e-12
#define U_t 25.8563e-3

//vyjadrena rovnica I_p - I_r = 0
double func(double U_p, double U_0, double R)
{
    double e = exp(U_p / U_t);
    return ((I_0 * (e - 1)) - ((U_0 - U_p) / R));
}

//funkcia na bisekciu
double diode(double U_0, double R, double EPS)
{
    double a = 0.0;
    double b = U_0;
    double U_p;
    while ((b - a) >= EPS)
    {
        U_p = (a + b) / 2.0;
        if (func(U_p, U_0, R) == 0.0)
            break;
        else if (func(U_p, U_0, R) * func(a, U_0, R) < 0)
            b = U_p;
        else
            a = U_p;
    }
    return U_p;
}

int main(int argc, char *argv[])
{
    double U_0, R, EPS = 0.0;
    char *str[3];
    //zapis
    if (argc == 4)
    {
        U_0 = strtod(argv[1], &str[0]);
        R = strtod(argv[2], &str[1]);
        EPS = strtod(argv[3], &str[2]);
    }
    //chybne vstupy
    if (argc < 4 || argc > 4)
    {
        fprintf(stderr, "INVALID INPUT\n");
        return 1;
    }
    //chybne vstupy
    if (U_0 < 0 || R <= 0)
    {
        fprintf(stderr, "Invalid arguments\n");
        return 1;
    }
    //chybne vstupy
    for (int i = 0; i < 3; i++)
    {
        if (*str[i] != 0)
        {
            fprintf(stderr, "Invalid arguments\n");
            return 1;
        }
    }
    if (EPS < 1e-15)
        EPS = 1e-15;
    double U_p = diode(U_0, R, EPS);
    //vypis
    printf("U_p = %g V\n", U_p);
    printf("I_p = %g A\n", I_0 * (exp(U_p / U_t) - 1));
    return 0;
}