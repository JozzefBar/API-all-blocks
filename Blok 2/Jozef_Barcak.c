#include <stdio.h>
#include <string.h>
#include <windows.h>

void assembler_sucet(int a, int b, int vysledok)
{
    __asm__(
        "mov %[a], %%eax;"
        "mov %[b], %%ecx;"
        "add %%ecx, %%eax;"
        "mov %%eax, %[vysledok];"
        : [vysledok] "=r" (vysledok)
        : [a] "r" (a), [b] "r" (b)
        : "%eax", "%ecx"
        );

    printf("Súčet dvoch premenných: %d\n", vysledok);
}

void assembler_nasobenie_dvomi(int c, int vysledok)
{
    __asm__(
            "mov %[c], %%eax;"
            "shl %%eax;"
            "mov %%eax, %[vysledok];"
            : [vysledok] "=r" (vysledok)
            : [c] "r" (c)
            : "%eax", "%ecx"
    );
    printf("Výsledok násobenia dvomi: %d\n", vysledok);
}

void assembler_prevod_cislic(int d, int znak)
{
    __asm__(
            "mov %[d], %%eax;"
            "mov $9, %%ecx;"
            "cmp %%ecx, %%eax;"
            "jg vacsie_ako_9;"
            "add $'0', %%eax;"
            "mov %%eax, %[znak];"
            "jmp koniec;"
         "vacsie_ako_9:"
            "add $55, %%eax;"
            "mov %%eax, %[znak];"
         "koniec:"
            : [znak] "=r" (znak)
            : [d] "r" (d)
            : "%eax", "%ecx"
    );
    printf("ASCII znak: %c\n", znak);
}

void assembler_procesor () {
    char VEN[13];
    __asm__(
            "mov $0, %%eax;"
            "cpuid;"
            "mov %%ebx, %0;"
            "mov %%edx, %1;"
            "mov %%ecx, %2;"
            : "=m" (VEN[0]), "=m" (VEN[4]), "=m" (VEN[8])
            :
            : "%eax", "%ebx", "%ecx", "%edx"
            );

    VEN[12] = '\0';
    printf("Typ procesora: %s\n", VEN);
}

void pamat()
{
/*
    //1
    char znaky[] = "architektura_pocitacov_je_super_predmet";
    printf("%s\n", znaky);
    //2
    char *pointer = znaky;
    printf("%p\n",pointer);
    //3
    char *pointer_1 = znaky + 1;
    *pointer_1 = 'x';
    printf("%s\n", pointer_1);
    //4
    char *pointer_2 = znaky + 10000000;
    *pointer_2 = 'x';
    printf("%s\n", pointer_2);
*/

    //1
    int pole_cisel[] = {4,5,3,0};
    for (int i = 0; i < 4; i++)
        printf("%d ", pole_cisel[i]);
    //2
    int *pointer_cisla = pole_cisel;
    printf("\n%p",pointer_cisla);
    //3
    printf("\n");
    int *pointer_cisel_1 = pole_cisel + 2;
    *pointer_cisel_1 = 9;
    for (int j = 0; j < 4; j++)
        printf("%d ", pole_cisel[j]);
    printf("\n%p",pointer_cisel_1);
}

void poviedka()
{
    FILE *subor;
    FILE *vystupny_subor;
    subor = fopen("poviedka.html", "r");
    vystupny_subor = fopen("spravna_poviedka.html", "w");
    char riadok[1000] = "";
    while (fgets(riadok, sizeof(riadok), subor) != NULL)
    {
        for (int i = 0; i < strlen(riadok); i++)
        {
            switch((char)riadok[i])
            {
                case (char)165:
                    riadok[i] = (char)188;
                    break;
                case (char)169:
                    riadok[i] = (char)138;
                    break;
                case (char)171:
                    riadok[i] = (char)141;
                    break;
                case (char)174:
                    riadok[i] = (char)142;
                    break;
                case (char)181:
                    riadok[i] = (char)190;
                    break;
                case (char)185:
                    riadok[i] = (char)154;
                    break;
                case (char)187:
                    riadok[i] = (char)157;
                    break;
                case (char)190:
                    riadok[i] = (char)158;
                    break;
            }
        }
        fprintf(vystupny_subor, "%s", riadok);
    }
    fclose(subor);
    fclose(vystupny_subor);
}

#define Dlzka1 2050

void koniec_poviedky()
{
    FILE *subor;
    FILE *vystupny_subor;
    subor = fopen("koniec_poviedky.html", "rb");
    vystupny_subor = fopen("spravny_koniec_poviedky.html", "w");
    unsigned char znaky[Dlzka1];
    if (fgets((char*) znaky, sizeof(znaky), subor) != NULL)
    {
        for (int i = 0; i < Dlzka1 &&  znaky[i] != '\0'; i++)
            znaky[i] = znaky[i]^27;
    }
    fprintf(vystupny_subor, "%s", znaky);
    fclose(subor);
    fclose(vystupny_subor);
}

void semigrafika(char*par1, char*par2, char*par3, char*par4, short int x, short int y)
{
    int pocet_riadkov = 10, najdlhsi_udaj = 0;
    unsigned long dlzka_udaju1 = strlen(par1);
    unsigned long dlzka_udaju2 = strlen(par2);
    unsigned long dlzka_udaju3 = strlen(par3);
    unsigned long dlzka_udaju4 = strlen(par4);
    char* par[] = {par1, par2, par3, par4};
    for (int i = 0; i < 4; i++)
    {
        unsigned long dlzka = strlen(par[i]);
        if (dlzka > najdlhsi_udaj)
            najdlhsi_udaj = (int)dlzka;
    }
    int najdlhsi_riadok = 15 + najdlhsi_udaj;
    int nadpis = 12;
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);

    while (pocet_riadkov > 0)
    {
        COORD point = {x,y};
        SetConsoleCursorPosition(hConsole, point);
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
        int znaky = 0;
        for(znaky; znaky < najdlhsi_riadok; znaky++)
        {
            if (pocet_riadkov == 10)
            {
                if (znaky == 0)
                    printf("\u250C");
                else if (znaky == najdlhsi_riadok - 1)
                    printf("\u2510");
                else if (znaky == (najdlhsi_riadok - nadpis)/2)
                {
                    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
                    printf(" Záznam 001 ");
                    znaky += nadpis - 1;
                }
                else
                    printf("\u2500");
            }
            else if (pocet_riadkov == 1)
            {
                if (znaky == 0)
                    printf("\u2514");
                else if (znaky == najdlhsi_riadok - 1)
                    printf("\u2518");
                else
                    printf("\u2500");
            }
            else if(pocet_riadkov % 2 == 1)
            {
                if (znaky == 0)
                    printf("\u251C");
                else if (znaky == najdlhsi_riadok - 1)
                    printf("\u2524");
                else
                    printf("\u2500");
            }
            else if(pocet_riadkov % 2 == 0)
            {
                if (znaky == 11 || znaky == 0 || znaky == najdlhsi_riadok - 1)
                    printf("\u2502");
                else if (pocet_riadkov == 8)
                {
                    if(znaky == 2)
                    {
                        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
                        printf("Meno");
                        znaky += 3;
                    }
                    else if (znaky + (int)dlzka_udaju1 == najdlhsi_riadok - 2)
                    {
                        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
                        printf("%s", par1);
                        znaky += (int)dlzka_udaju1 - 1;
                    }
                    else
                        printf(" ");
                }
                else if (pocet_riadkov == 6)
                {
                    if(znaky == 2)
                    {
                        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
                        printf("Výška");
                        znaky += 4;
                    }
                    else if (znaky + (int)dlzka_udaju2 == najdlhsi_riadok - 2)
                    {
                        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
                        printf("%s", par2);
                        znaky += (int)dlzka_udaju2 - 1;
                    }
                    else
                        printf(" ");
                }
                else if (pocet_riadkov == 4)
                {
                    if(znaky == 2)
                    {
                        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
                        printf("Hmotnosť");
                        znaky += 7;
                    }
                    else if (znaky + (int)dlzka_udaju3 == najdlhsi_riadok - 2)
                    {
                        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
                        printf("%s", par3);
                        znaky += (int)dlzka_udaju3 - 1;
                    }
                    else
                        printf(" ");

                }
                else if (pocet_riadkov == 2)
                {
                    if(znaky == 2)
                    {
                        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
                        printf("Tel.");
                        znaky += 3;
                    }
                    else if (znaky + (int)dlzka_udaju4 == najdlhsi_riadok - 2)
                    {
                        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
                        printf("%s", par4);
                        znaky += (int)dlzka_udaju4 - 1;
                    }
                    else
                        printf(" ");
                }
            }
        }
        printf("\n");
        pocet_riadkov--;
        y++;
    }
    SetConsoleTextAttribute(hConsole, consoleInfo.wAttributes);
}

int main()
{
    int vstup, uloha;
    printf("Zadaj číslo úloh (1, 2, 3, 5): ");
    scanf("%d", &vstup);
    if (vstup == 1)
    {
        printf("Zadaj číslo konkrétneho príkladu (1, 2, 3, 4): ");
        scanf("%d", &uloha);
        int vysledok = 0;
        if (uloha == 1)
        {
            int a = 7, b = 5;
            assembler_sucet(a,b, vysledok);
        }
        else if (uloha == 2)
        {
            int c = 7;
            assembler_nasobenie_dvomi(c, vysledok);
        }
        else if (uloha == 3)
        {
            int d = 12, znak = 0;
            assembler_prevod_cislic(d, znak);
        }
        else if (uloha == 4)
            assembler_procesor();
    }
    if (vstup == 2)
        pamat();
    if (vstup == 3)
    {
        printf("Zadaj číslo konkrétneho príkladu (1, 2): ");
        scanf("%d", &uloha);
        if (uloha == 1)
            poviedka();
        if (uloha == 2)
            koniec_poviedky();
    }
    if (vstup == 5)
    {
        char par1[50], par2[50], par3[50], par4[50];
        short int x,y;
        scanf("%hd %hd", &x, &y);
        while (getchar() != '\n');
        fgets(par1, sizeof(par1), stdin);
        par1[strcspn(par1, "\n")] = '\0';
        fgets(par2, sizeof(par2), stdin);
        par2[strcspn(par2, "\n")] = '\0';
        fgets(par3, sizeof(par3), stdin);
        par3[strcspn(par3, "\n")] = '\0';
        fgets(par4, sizeof(par4), stdin);
        par4[strcspn(par4, "\n")] = '\0';
        semigrafika(par1, par2, par3, par4, x, y);
    }
    return 0;
}
