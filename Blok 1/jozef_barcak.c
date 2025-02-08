#pragma warning(disable:4996)
#include <stdio.h>
#include <string.h>

void dvojkovy_prevod(int a, int kod)
{
    int dvojkove_cislo_zvysok[64]; int index_cislo = 0;

    while (a > 0)
    {
        dvojkove_cislo_zvysok[index_cislo] = a%2;
        a /= 2;
        index_cislo += 1;
    }
    printf("Číslo v dvojkovej sustave: ");
    for (int i = index_cislo - 1; i >= 0; i--)
    {
        printf("%d", dvojkove_cislo_zvysok[i]);
    }
    printf("\n");

    int dvojkovy_kod_zvysok[64]; int index_kod = 0;
    while (kod > 0)
    {
        dvojkovy_kod_zvysok[index_kod] = kod%2;
        kod /= 2;
        index_kod += 1;
    }
    printf("Znak má v ASCII tabuľke v dvojkovej sustave kód: ");
    for (int j = index_kod - 1; j >= 0; j--)
    {
        printf("%d", dvojkovy_kod_zvysok[j]);
    }
    printf("\n");

}

void Prevod_na_rimske(int cislo)
{
    char* jednotky[] = {"","I", "II", "III","IV", "V", "VI", "VII", "VIII","IX"};
    char* desiatky[] = {"","X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC", "C"};

    printf("Výsledok: ");
    if (cislo == 100)
    {
        printf("%s", desiatky[10]);
    }
    else
    {
        printf("%s", desiatky[cislo/10]);
        printf("%s", jednotky[cislo%10]);
    }
}

void Fibonacci(int k)
{
    int cislo1 = 1, cislo2 = 1, cislo3;
    printf("Čísla Fibonacciho postupnosti ktore sú menšie alebo rovné ako k:\n");
    printf("%d %d ", cislo1, cislo2);

    while (1)
    {
        cislo3 = cislo1 + cislo2;
        if (cislo3 <= k)
        {
            printf("%d ", cislo3);
        }
        else
        {
            break;
        }

        cislo1 = cislo2;
        cislo2 = cislo3;
    }
}

void IntelHex(char ret[64])
{
    int par = 0, i = 0, sucet = 0, mod, komplement, vysledok;
    while (i < strlen(ret) - 3)
    {
        sscanf(ret + i + 1, "%2X", &par);
        sucet += par;
        i += 2;
    }
    mod = sucet % 256;
    komplement = 255 - mod;
    vysledok = komplement + 1;
    printf("%X\n",vysledok);
}

int main()
{
    int vyber = 0;
    printf("Vyber číslo úlohy (1, 2, 3, 6): ");
    scanf("%d", &vyber);

    if (vyber == 1)               //Úloha 1.1
    {
        int a; char znak;
        printf("Zadaj číslo (na prevod do sústav): ");
        scanf("%d", &a);
        printf("Zadaj znak (prevod jeho kódu v ASCII do sústav): ");
        scanf(" %c", &znak);
        int kod = (int)znak;
        printf("Číslo: %d    ", a);
        printf("Znak: %c\n", znak);
        dvojkovy_prevod(a, kod);
        printf("Číslo v desiatkovej sústave: %d\n", a);
        printf("Znak má v ASCII tabuľke v desiatkovej sústave kód: %d\n", kod);
        printf("Číslo v šestnástkovej sústave: %x\n", a);
        printf("Znak má v ASCII tabuľke v šestnástkovej sústave kód: %x\n", kod);
    }

    else if (vyber == 2)            //Úloha 1.2
    {
        int cislo;
        printf("Zadaj číslo (prevod na rímske čísla): ");
        scanf("%d", &cislo);
        if (cislo >= 1 && cislo <= 100)
        {
            Prevod_na_rimske(cislo);
        }
        else
        {
            printf("Číslo nie je z rozsahu 1 - 100");
        }
    }

    else if (vyber == 3)             //Úloha 1.3
    {
        int k;
        printf("Zadaj hranicu čísiel z fibonacciho postupnosti (k >= 2): ");
        scanf("%d", &k);
        Fibonacci(k);
    }

    else if (vyber == 6)             //Úloha 1.6
    {
        char ret[64];
        printf("Zadaj IntelHex: ");
        scanf("%s", &ret);
        IntelHex(ret);
    }
    else
    {
        printf("Nesprávne zvolené číslo úlohy!");
    }

    return 0;
}