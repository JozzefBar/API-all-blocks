#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")

#define DEFAULT_BUFLEN 4096

char* zvysok_po_deleni(char *ID_ret)
{
    int ID[5] = {0};
    int sucet = 0, x;
    for(x = 0; x < strlen(ID_ret) - 2; x++)
    {
        ID[x] = ID_ret[x] - '0';
        sucet += ID[x];
    }

    char *zvysok = malloc(3 * sizeof(char));

    sprintf(zvysok, "%d", sucet % ID[4]);
    zvysok[2] = '\0';
    return zvysok;
}

char* desifrovanie(char* text)
{
    for (int p = 0; p <= 148; p++)
        text[p] ^= 55;
    return text;
}

int jePrvocislo(int cislo)
{
    for(int i = 2; i < cislo; i++)
    {
        if(cislo % i == 0)
            return 0;
    }
    return 1;
}

char* prvocislo_string(char* text)
{
    int dlzka = (int)strlen(text);
    char* upraveny_text = malloc(dlzka * sizeof(char));
    int j = 0;
    for(int s = 2; s < dlzka; s++)
        if (jePrvocislo(s) == 1)
        {
            upraveny_text[j] = text[s - 1];
            j++;
        }
    upraveny_text[j] = '\0';
    return upraveny_text;
}

int prijimanie_odosielanie(int iResult, SOCKET ConnectSocket)
{
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);

    short int suradnica_x = consoleInfo.dwCursorPosition.X;
    short int suradnica_y = consoleInfo.dwCursorPosition.Y;
    COORD suradnice = {suradnica_x,suradnica_y};
    SetConsoleCursorPosition(hConsole, suradnice);

    FILE* subor;
    subor = fopen("zaznam.txt", "w");
    if (subor == NULL)
        return 1;

    int pocet_id = 1;
    while(1)
    {
        //odosielanie
        char name[1024];
        int size = 1024;

        fgets(name, size, stdin);
        fputs("      Môj text: ", subor);
        SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
        if (strcmp(name, "128090\n") == 0 && pocet_id == 2)
        {
            char *vysledok = zvysok_po_deleni(name);
            iResult = send(ConnectSocket, vysledok, (int)strlen(vysledok), 0);
            printf("%s\n\n", vysledok);
            fprintf(subor, "%s", vysledok);
            free(vysledok);
        }
        else if(strcmp(name, "END\n") == 0)
        {
            fprintf(subor, "%s", name);
            break;
        }
        else
        {
            iResult = send(ConnectSocket, name, (int)strlen(name), 0);
            printf("%s\n", name);
            fprintf(subor, "%s", name);
            if (strcmp(name, "128090\n") == 0)
                pocet_id = 2;
        }

        if (iResult == SOCKET_ERROR)
        {
            printf("send failed: %d\n", WSAGetLastError());
            fclose(subor);
            closesocket(ConnectSocket);
            WSACleanup();
            return 1;
        }

        SetConsoleTextAttribute(hConsole, consoleInfo.wAttributes);
        printf("Bytes Sent: %d\n", iResult);

        //prijimanie
        int recvbuflen = DEFAULT_BUFLEN;
        char recvbuf[DEFAULT_BUFLEN];

        iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);

        if ( iResult > 0 )
        {
            SetConsoleOutputCP(CP_UTF8);
            printf("Bytes received: %d\n", iResult);
            printf("Received data: \n");

            if(strcmp(name, "123\n") == 0)
                desifrovanie(recvbuf);
            else if(strcmp(name, "PRIMENUMBER\n") == 0)
            {
                char *upraveny_string = prvocislo_string(recvbuf);
                strcpy(recvbuf, upraveny_string);
                free(upraveny_string);
            }

            SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
            suradnice.X = (short)(consoleInfo.dwSize.X/2);
            suradnice.Y += 5;
            if (suradnice.Y > consoleInfo.dwSize.Y - 1)
                suradnice.Y = (short)(consoleInfo.dwSize.Y - 2);
            SetConsoleCursorPosition(hConsole, suradnice);

            for(int i = 0; i < strlen(recvbuf); i++)
            {
                if (recvbuf[i] == '\n')
                    recvbuf[i] = '\0';
                if (suradnice.X > consoleInfo.dwSize.X - 2)
                {
                    suradnice.X = (short)(consoleInfo.dwSize.X/2);
                    if (suradnice.Y < consoleInfo.dwSize.Y - 1)
                        suradnice.Y++;
                    else
                    {
                        suradnice.Y = (short)(consoleInfo.dwSize.Y - 1);
                        printf("\n");
                    }
                    SetConsoleCursorPosition(hConsole, suradnice);
                }
                printf("%c", recvbuf[i]);
                suradnice.X++;
                fflush(stdout);
                Sleep(10);
            }
            SetConsoleTextAttribute(hConsole, consoleInfo.wAttributes);
            printf("\n");
            fprintf(subor, "%s", recvbuf);
            fputc('\n', subor);
            fputc('\n', subor);
            suradnice.Y++;
        }
        else if ( iResult == 0 )
        {
            printf("Connection closed\n");
            break;
        }
        else
        {
            printf("recv failed with error: %d\n", WSAGetLastError());
            break;
        }
    }
    fclose(subor);
    return 0;
}

int main()
{
    //uvodne nastavovacky
    WSADATA wsaData;
    int iResult;

    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0)
    {
        printf("WSAStartup failed: %d\n", iResult);
        return 1;
    }

    struct addrinfo *result = NULL, *ptr = NULL;
    struct addrinfo hints;

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    iResult = getaddrinfo("147.175.115.34", "777", &hints, &result);
    if (iResult != 0)
    {
        printf("getaddrinfo failed: %d\n", iResult);
        WSACleanup();
        return 1;
    }
    else
        printf("getaddrinfo didn’t fail…\n");

    //vytvorenie socketu a pripojenie sa
    SOCKET ConnectSocket = INVALID_SOCKET;
    ptr = result;

    ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype,ptr->ai_protocol);

    if (ConnectSocket == INVALID_SOCKET)
    {
        printf("Error at socket(): %d\n", WSAGetLastError());
        freeaddrinfo(result);
        WSACleanup();
        return 1;
    }
    else
        printf("Error at socket DIDN’T occur…\n");

    iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
    if (iResult == SOCKET_ERROR)
        printf("Not connected to server…\n");
    else
    printf("Connected to server!\n");

    if (iResult == SOCKET_ERROR)
    {
        closesocket(ConnectSocket);
        ConnectSocket = INVALID_SOCKET;
        WSACleanup();
        return 1;
    }
    Sleep(250);

    if (prijimanie_odosielanie(iResult, ConnectSocket) == 1)
        return 1;

    closesocket(ConnectSocket);
    WSACleanup();

    return 0;
}