#include <iostream>
#include <windows.h>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <ctype.h>
#include <fstream>
#include <conio.h>
#include <map>


using namespace std;
// ZMIENNE
unsigned long long int gotowka = 0;
int stawka = 0;
bool gotowka_ustalona = 1;


// ZMIANA KOLORU TEKSTU
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
int black = 112;
int red = 116;
int green = 114;
int normal = 15;

//RULETKA
int wlasna_wartosc = -1;
int roulette_menu_choice;
string wybor_opcji_ruletka;
// SLOT MACHINE
    // CZAS LOSOWANIA
    int C = 20;


void Napis(string file)
{
    {
        ifstream napis;
        string napis_line;
        napis.open(file);
        while (getline(napis, napis_line))
            cout << napis_line << endl;
    }
}

void BLACKJACK_ROZGRYWKA()
{
    if (gotowka > 0)
    {
        map<int, char> KARTY = {
        { 11 , 'J' },
        { 12 , 'Q' },
        { 13 , 'K' },
        { 14 , 'A' }
        };
        int karta;
        int stawka;
        int suma_kart_gracza = 0;
        int suma_kart_komp = 0;
        int karty_gracza[10] = {0};
        int karty_komp[10] = {0};
        int licznik_kart = 0;
        int blackjack_game_choice;
        bool stawka_ustalona = 1;
        bool game_on_gracz = 1;
        bool game_on_komp = 0;
        do
        {
            do
            {   cin.clear();
                system("cls");
                cout << "Twoja gotowka: " << gotowka << endl;
                cout << "\n";
                Napis("napis_blackjack.txt");

                cout << "\tPodaj stawke o jaka chcesz zagrac: \n\t>> ";
                cin >> stawka;
                if (cin.good())
                {
                    if (stawka > 0)
                    {
                        if (stawka <= gotowka)
                            stawka_ustalona = 0;
                        else {cout << "\n\tNie masz tyle gotowki (" << gotowka << ")"; getch();}
                    }
                    else {cout << "\n\tWartosc mniejsza lub równa 0"; getch();}
                }

                cin.clear();
                cin.ignore();

            }while(stawka_ustalona);
            blackjack_game_choice = 1;
            do
            {
                system("cls");
                cout << "Twoja gotowka: " << gotowka << "\n\n";
                Napis("napis_blackjack.txt");
                if (suma_kart_gracza == 21)
                {
                    cout << "\tMasz 21 pkt\n\tKonczysz rozgrywke\n\tRuch przeciwnika\n\tWcisnij dowolny klawisz \n\t>> ";
                    getch();
                    game_on_gracz = 0;
                    game_on_komp = 1;
                }
                else if (suma_kart_gracza < 21)
                {
                    if (blackjack_game_choice > 0 && blackjack_game_choice < 3)
                    {
                        switch (blackjack_game_choice)
                        {
                            case 1:
                            {
                                karta = rand()% 13 + 2;

                                if (suma_kart_gracza > 21)
                                    {
                                        for (int i = 0; i < licznik_kart; i++)
                                            if (karty_gracza[i] == 11)
                                            {
                                                cout << "\n\tZamiana A(11) na A(1)";
                                                karty_gracza[i] = 1;
                                                suma_kart_gracza -= 10;
                                            }
                                    }
                                if (karta == 14)
                                {
                                    cout << "\tWylosowana karta: " << KARTY[karta] << "(11)";
                                    karta = 11;
                                    karty_gracza[licznik_kart] = karta;
                                    suma_kart_gracza += karta;

                                }
                                else
                                    if (karta > 10)
                                    {
                                        cout << "\tWylosowana karta: " << KARTY[karta] << "(10)";
                                        karta = 10;
                                        karty_gracza[licznik_kart] = karta;
                                        suma_kart_gracza += karta;
                                    }
                                    else
                                    {
                                        cout << "\tWylosowana karta: " << karta;
                                        karty_gracza[licznik_kart] = karta;
                                        suma_kart_gracza += karta;
                                    }


                            licznik_kart ++;

                            } break;

                        case 2: game_on_gracz = 0; game_on_komp = 1; break;

                        }
                    }
                    else
                    {
                        cout << "\n\n\t*** Bledna wartosc (wcisnij dowolny klawisz aby sprobowac ponownie) ***    ";
                        getch();
                        printf("\33[2K"); // usuwa ostatnia linie

                    }

                if (suma_kart_gracza > 21)
                {
                    for (int i = 0; i < licznik_kart; i++)
                        if (karty_gracza[i] == 11)
                        {
                            karty_gracza[i] = 1;
                            suma_kart_gracza -= 10;
                            break;
                        }
                }
                cout << "\n\n\t  Twoje karty: ";
                for (int i = 0; i < licznik_kart; i++)
                    if (karty_gracza > 0)
                        cout << karty_gracza[i] << " ";
                cout << "\n  \t    Suma kart: " << suma_kart_gracza;
                cout << "\n \t    Ilosc kart: " << licznik_kart;


                if (suma_kart_gracza > 21)
                {
                    cout << "\n\n\tNiestety, przegrales.\n\tOd Twojego konta odjeto " << stawka << " PLN (" << gotowka << " - " << stawka << " = " << gotowka - stawka << " PLN)";
                    gotowka -= stawka;
                    cout << "\n\n\tWcisnij dowolny klawisz, aby kontynuowac ";
                    getch();
                    game_on_gracz = 0;

                }
                if (game_on_gracz)
                {
                    cout << "\n\n\n\tWybierz opcje:\n\n\t1. Doloz karte (Doklada kolejna karte do juz posiadanych)\n\t2. Stop        (Zatrzymuje dokladanie kart. Ruch przeciwnika)\n\t>>";
                    blackjack_game_choice = getch()-48;
                }


                /*if (blackjack_game_choice == 1 && suma_kart_gracza < 21)
                {
                    cout << "\n\n\nWybierz opcje:\n\n1. Doloz karte (Doklada kolejna karte do juz posiadanych)\n2. Stop (Zatrzymuje dokladanie kart. Ruch przeciwnika)\n";
                    blackjack_game_choice = getch()-48;
                }
                */
                }

            } while(game_on_gracz);

            licznik_kart = 0;
            while (game_on_komp)
            {
                system("cls");
                cout << "Twoja gotowka: " << gotowka << "\n\n";
                Napis("napis_blackjack.txt");
                cout << "\n\tTwoj wynik: " << suma_kart_gracza << "\n\n";

                karta = rand()% 13 + 2;
                if (karta == 14)
                {
                    cout << "\tWylosowana karta: " << KARTY[karta] << "(11)";
                    karta = 11;
                    karty_komp[licznik_kart] = karta;
                    suma_kart_komp += karta;
                    if (suma_kart_komp > 21)
                    {
                        for (int i = 0; i < licznik_kart; i++)
                            if (karty_komp[i] == 11)
                            {
                                cout << "\n\tZamiana A(11) na A(1)";
                                karty_komp[i] = 1;
                                suma_kart_komp -= 10;
                            }
                    }
                }
                else
                    if (karta > 10)
                    {
                        cout << "\tWylosowana karta: " << KARTY[karta] << "(10)";
                        karta = 10;
                        karty_komp[licznik_kart] = karta;
                        suma_kart_komp += karta;
                    }
                    else
                    {
                        cout << "\tWylosowana karta: " << karta;
                        cout << "\n\t(Komputer musi grac do uzyskania wyniku min. 17 pkt)\n";
                        karty_komp[licznik_kart] = karta;
                        suma_kart_komp += karta;
                    }

                licznik_kart ++;
                cout << "\n\n\t     Karty przeciwnika: ";
                for (int i = 0; i < licznik_kart; i++)
                    if (karty_komp > 0)
                        cout << karty_komp[i] << " ";
                cout << "\n\t Suma kart przeciwnika: " << suma_kart_komp;
                cout << "\n\tIlosc kart przeciwnika: " << licznik_kart;
                if (suma_kart_komp > 16)
                {
                    if (suma_kart_komp > suma_kart_gracza && suma_kart_komp < 22)
                    {
                        cout << "\n\n\tNiestety, komputer wygral.\n\tOd Twojego konta odjeto " << stawka << " PLN (" << gotowka << " - " << stawka << " = " << gotowka - stawka << " PLN)";
                        gotowka -= stawka;
                        game_on_komp = 0;
                    }
                    else
                        if (suma_kart_komp > 21)
                        {
                            cout << "\n\n\tWygrales, gratulacje!\n\tDo Twojego konta dodano " << stawka << " PLN  (" << gotowka << " + " << stawka << " = " << gotowka + stawka << " PLN)";
                            gotowka += stawka;
                            game_on_komp = 0;
                        }
                        else
                            if (suma_kart_komp == suma_kart_gracza)
                            {
                                cout << "\n\n\tRemis. Twoja konto pozostaje bez zmian (" << gotowka << ")";
                                gotowka += stawka;
                                game_on_komp = 0;
                            }
                    }
                    else
                    {
                        cout << "\n\n\t(Wcisnij dowolny klawisz, aby kontynuowac ruch przeciwnika)";
                    }


            getch();
            }

        } while (game_on_gracz); //blackjack_game_choice != 3
    }
    else cout << "\n\tStan konta: 0\n\n\tKONIEC GRY";

}


void BLACKJACK()
{

    if (gotowka > 0)
    {
        int blackjack_choice;

        do
        {   system("cls");
            cout << "Twoja gotowka: " << gotowka << "\n\n";
            Napis("napis_blackjack.txt");

            cout << "\n\tWITAMY W GRZE BLACKJACK\n\tWybierz opcje:\n\n\
        1. Rozgrywka\n\
        2. Zasady\n\
        3. Menu glowne\n\t>> ";
            blackjack_choice = getch()-48;

            if (blackjack_choice > 0 && blackjack_choice < 4)
            {
                switch (blackjack_choice)
                {
                    case 1: BLACKJACK_ROZGRYWKA();
                            break;
                    case 2: cout<< "\n\t\n\tZasady blackjacka opieraja sie na liczbie 21.\n\tGracz w rozdawanych mu przez krupiera kartach musi uzyskac 21 punktow lub maksymalnie zblizyc sie do \
tej liczby,\n\tw zadnym wypadku nie mogac jej przekroczyc. W blackjacku punktacja za poszczegolne figury prezentuje sie nastepujaco:\n\
    \t> Blotki - zgodnie z wartoscia numerowa, czyli na przyklad osemka oznacza 8 punktow\n\
    \t> Walet, Dama, Krol - 10 punktow\n\
    \t> As - 1 lub 11 punktow, w zaleznosci od tego, ktora opcja jest korzystniejsza\n\n\t(wcisnij dowolny klawisz aby kontynuowac)\n\t>> "; getch();
                    case 3: break;
                }
            }
            else
            {
                cout << "\n\n\t*** Bledna wartosc (wcisnij dowolny klawisz aby sprobowac ponownie) ***    \n\t>> ";
                getch();
            }
            if (gotowka == 0) break;

        } while(blackjack_choice != 3);

    }


}

int SLOT_NUMBER_CHOOSE()
{
    int i, j, number, slot_number;
    for (i=0 ; i < 3; i++)
        {   number = rand() % 255 + 1;

            switch(number)
            {
                case   1 ...  12: slot_number = 0; break;
                case  13 ...  39: slot_number = 1; break;
                case  40 ...  66: slot_number = 2; break;
                case  67 ...  93: slot_number = 3; break;
                case  94 ... 120: slot_number = 4; break;
                case 121 ... 147: slot_number = 5; break;
                case 148 ... 174: slot_number = 6; break;
                case 175 ... 201: slot_number = 7; break;
                case 202 ... 228: slot_number = 8; break;
                case 229 ... 255: slot_number = 9; break;
            }
        }
        return slot_number;
}

void JEDNOREKI_BANDYTA_LOSOWANIE(int s1, int s2, int s3)
{
    string slot_choice[3][11];
    int i, k;
    string file;
    // DLA s1
    for (i = 0 ; i < 11; i++)
    {
        file = "slot_" + to_string(s1) + ".txt";
        ifstream napis;
        string napis_line;
        napis.open(file);
        k = 0;
        while (getline(napis, napis_line))
        {
            slot_choice[0][k] = napis_line;
            k++;
        }
    }
    // DLA s2
    for (i = 0 ; i < 11; i++)
    {
        file = "slot_" + to_string(s2) + ".txt";
        ifstream napis;
        string napis_line;
        napis.open(file);
        k = 0;
        while (getline(napis, napis_line))
        {
            slot_choice[1][k] = napis_line;
            k++;
        }
    }
    // DLA s3
    for (i = 0 ; i < 11; i++)
    {
        file = "slot_" + to_string(s3) + ".txt";
        ifstream napis;
        string napis_line;
        napis.open(file);
        k = 0;
        while (getline(napis, napis_line))
        {
            slot_choice[2][k] = napis_line;
            k++;
        }
    }
    system("cls");
    string s;
    int CZAS_LOSOWANIA = C;
    do
    {

        cout << "Twoja gotowka: " << gotowka << "\n\n";
        Napis("napis_slot_machine.txt");
        CZAS_LOSOWANIA--;
        cout << "\n\n\n";
        if (CZAS_LOSOWANIA%2==0) s="-------------------"; else s = "||||||||||||||||||||";
        for (i = 0 ; i < 11; i++)
        {
            cout << "\t" << s << "   " << s << "   " << s << endl;
        }
        system("cls");
    } while (CZAS_LOSOWANIA > 1);

    cout << "Twoja gotowka: " << gotowka << "\n\n";
    Napis("napis_slot_machine.txt");
    cout << "\n\t Twoje losowanie:\n\n";
    for (i = 0 ; i < 11; i++)
    {
        cout << "\t";
        SetConsoleTextAttribute(hConsole, (s1+1)*16);
        cout << slot_choice[0][i];
        SetConsoleTextAttribute(hConsole, normal);
        cout << "   ";
        SetConsoleTextAttribute(hConsole, (s2+1)*16);
        cout << slot_choice[1][i];
        SetConsoleTextAttribute(hConsole, normal);
        cout << "   ";
        SetConsoleTextAttribute(hConsole, (s3+1)*16);
        cout << slot_choice[2][i] << endl;
    }
    SetConsoleTextAttribute(hConsole, normal);
}

void JEDNOREKI_BANDYTA_SPRAWDZENIE(int s1, int s2, int s3)
{

    int mnoznik_wygranej = 0;


    if (s1 == 0) {mnoznik_wygranej += 20; cout << "\tGwiazda na miejscu 1! +20 do mnoznika wyniku! (*" << mnoznik_wygranej << ")\n\n";}
    if (s2 == 0) {mnoznik_wygranej += 20; cout << "\tGwiazda na miejscu 2! +20 do mnoznika wyniku! (*" << mnoznik_wygranej << ")\n\n";}
    if (s3 == 0) {mnoznik_wygranej += 20; cout << "\tGwiazda na miejscu 3! +20 do mnoznika wyniku! (*" << mnoznik_wygranej << ")\n\n";}


    if (s1 == s2 && s2 == s3)
    {
        mnoznik_wygranej += 20;
        cout << "\n\n\tBrawo! Trzy takie same! +20 do mnoznika wyniku! (*" << mnoznik_wygranej << ")\n\n";
    }
    else
        if (s1 == s2 || s1 == s3 || s2 == s3)
        {
            mnoznik_wygranej += 10;
            cout << "\n\n\tBrawo! Dwa takie same! +10 do mnoznika wyniku! (*" << mnoznik_wygranej << ")\n\n";
        }
        else
            if (s1 != 0 && s2 != 0 && s3 != 0)
            {
                cout << "\n\n\tNiestety... Sprobuj ponownie \n\n";
            }
    cout << "\tTwoja wygrana (stawka * mnoznik): \n\t\t" << stawka  << " * " << mnoznik_wygranej << " = " << stawka * mnoznik_wygranej << "\n\
    Posiadana gotowka (gotowka + wygrana):\n\t\t" << gotowka << " + " << stawka * mnoznik_wygranej << " = " << gotowka + (stawka * mnoznik_wygranej);
    gotowka = gotowka + (stawka * mnoznik_wygranej);
}

void JEDNOREKI_BANDYTA_ROZGRYWKA()
{

    int wygrana;
    bool stawka_ustalona = 1;
    int slot_machine_choice = 0;
    bool slot_machine_continue = 0;
    do
    {

        do
            {   cin.clear();
                system("cls");
                cout << "Twoja gotowka: " << gotowka << endl;
                cout << "\n";
                Napis("napis_slot_machine.txt");

                cout << "\n\tPodaj stawke o jaka chcesz zagrac: \n\t>> ";
                cin >> stawka;
                if (cin.good())
                {
                    if (stawka > 0)
                    {
                        if (stawka <= gotowka)
                            stawka_ustalona = 0;
                        else {cout << "\n\tNie masz tyle gotowki (" << gotowka << ")"; getch();}
                    }
                    else {cout << "\n\tWartosc mniejsza lub rowna 0"; getch();}
                }

                cin.clear();
                cin.ignore();

            }while(stawka_ustalona);
        gotowka -= stawka;
        slot_machine_choice = 1;

        cin.clear();
        system("cls");
        cout << "Twoja gotowka: " << gotowka << endl;
        cout << "\n";
        Napis("napis_slot_machine.txt");


        int slot_number_first = SLOT_NUMBER_CHOOSE();
        int slot_number_second = SLOT_NUMBER_CHOOSE();
        int slot_number_third = SLOT_NUMBER_CHOOSE();

        JEDNOREKI_BANDYTA_LOSOWANIE(slot_number_first, slot_number_second, slot_number_third);
        printf("\ns1: %i,  s2: %i,  s3: %i\n", slot_number_first, slot_number_second, slot_number_third);
        JEDNOREKI_BANDYTA_SPRAWDZENIE(slot_number_first, slot_number_second, slot_number_third);
        cout << "\n\n\tWcisnij dowolny klawisz, aby kontynuowac";
        getch();
    do
    {
        if (gotowka == 0)
        {
            stawka_ustalona == 0;
            break;
        }
        system("cls");
        cout << "Twoja gotowka: " << gotowka << "\n\n";
        Napis("napis_slot_machine.txt");

        cout << "\n\tWybierz opcje:\n\n\
        1. Zagraj ponownie za ta sama stawke (" << stawka << ")\n\
        2. Zmien stawke i zagraj ponownie\n\
        3. Menu gry\n\t>> ";
        slot_machine_choice = getch() - 48;

        if (slot_machine_choice > 0 && slot_machine_choice < 4)
        {
            switch (slot_machine_choice)
            {
                case 1:
                {
                    gotowka -= stawka;
                    slot_number_first = SLOT_NUMBER_CHOOSE();
                    slot_number_second = SLOT_NUMBER_CHOOSE();
                    slot_number_third = SLOT_NUMBER_CHOOSE();

                    JEDNOREKI_BANDYTA_LOSOWANIE(slot_number_first, slot_number_second, slot_number_third);
                    JEDNOREKI_BANDYTA_SPRAWDZENIE(slot_number_first, slot_number_second, slot_number_third);
                    cout << "\n\n\tWcisnij dowolny klawisz, aby kontynuowac";
                    getch();
                    break;
                }
                case 2: JEDNOREKI_BANDYTA_ROZGRYWKA(); break;
                case 3:
                {
                   break;
                }
            }
        }
        else
        {
            cout << "\n\n\t*** Bledna wartosc (wcisnij dowolny klawisz aby sprobowac ponownie) ***    \n>>";
            getch();
        }
        if (gotowka == 0)
        {
            stawka_ustalona == 0;
            break;
        }

    } while(slot_machine_choice != 3);

    } while (stawka_ustalona);
}


int RULETKA_MENU()
{
    do
    {
        system("cls");
        cout << "Twoja gotowka: " << gotowka << "\n\n";
        Napis("napis_roulette.txt");

        cout << "\n\tStawka: "<< stawka << "\n\n\tWybierz opcje:\n\n\
        1. Zielone 0\n\
        2. Parzyste - Czarne\n\
        3. Nieparzyste - Czerwone\n\
        4. Wartosc z przedzialu: 1-12\n\
        5. Wartosc z przedzialu: 13-24\n\
        6. Wartosc z przedzialu: 25-36\n\
        7. Wlasna wartosc: \n\n\t ";
        roulette_menu_choice = getch()-48;

        if (roulette_menu_choice > 0 && roulette_menu_choice < 8)
        {
            switch (roulette_menu_choice)
            {
                case 1: {wybor_opcji_ruletka = "Zielone 0"; return roulette_menu_choice;}
                case 2: {wybor_opcji_ruletka = "Parzyste - Czarne"; return roulette_menu_choice;}
                case 3: {wybor_opcji_ruletka = "Nieparzyste - Czerwone"; return roulette_menu_choice;}
                case 4: {wybor_opcji_ruletka = "Wartosc z przedzialu: 1-12"; return roulette_menu_choice;}
                case 5: {wybor_opcji_ruletka = "Wartosc z przedzialu: 13-24"; return roulette_menu_choice;}
                case 6: {wybor_opcji_ruletka = "Wartosc z przedzialu: 25-36"; return roulette_menu_choice;}
                case 7:
                {
                    cout << "\n\tPodaj wlasna wartosc (0-36)\n\t>> ";
                    cin >> roulette_menu_choice;
                    if (cin.good())
                    {
                        if (roulette_menu_choice >= 0)
                        {
                            if (roulette_menu_choice < 37)
                            {
                                wlasna_wartosc = roulette_menu_choice;
                                wybor_opcji_ruletka = "Wlasna wartosc: " + to_string(wlasna_wartosc);
                                return roulette_menu_choice;
                            }
                            else cout << "\n\tMaksymalna wartosc to 36";
                        }
                        else cout << "\n\tMinimalna wartosc to 0";
                    }
                    getch();

                    cin.clear();
                    cin.ignore();
                }

            }
        }
        else
        {
            cout << "\n\n\t*** Bledna wartosc (wcisnij dowolny klawisz aby sprobowac ponownie) ***    \n\t>> ";
            getch();
        }
        if (gotowka == 0) break;

    } while(true);
}


int RULETKA_ROZGRYWKA()
{
    srand (time(NULL));
    int balls_laps_counter = 0;
    int add = rand()%27 + 9;

    int timer = 1;
    int ball_position = 0;
    string blank_line = "        ";
    do
    {
        system("cls");
        cout << "Twoja gotowka: " << gotowka << "\n\n";
        Napis("napis_roulette.txt");
        cout << "\tStawka: "<< stawka << "\n\t Opcja: " << wybor_opcji_ruletka << "   add: " << add << "   timer: " << timer << "   wynik: " << ball_position;
        cout << "\n\n        ";

        for(int k = 0; k < 37; k++)
        {
            if ( k < 10)
            {
                if (k == 0)
                {
                    // 0 = zielone
                    SetConsoleTextAttribute(hConsole, green);
                    cout << "  0 ";
                }
                else
                {
                    if (k%2 == 0)
                    {
                        // parzyste = czarne
                        SetConsoleTextAttribute(hConsole, black);
                        cout << "  " << k << " ";
                    }
                    else
                    {
                        // nieparzyste = czerwone
                        SetConsoleTextAttribute(hConsole, red);
                        cout << "  " << k << " ";
                    }
                }
            }
            else
            {

                if (k%2 == 0)
                {
                    // parzyste = czarne
                    SetConsoleTextAttribute(hConsole, black);
                    cout << " " << k << " ";
                }
                else
                {
                    // nieparzyste = czerwone
                    SetConsoleTextAttribute(hConsole, red);
                    cout << " " << k << " ";
                }
            }
            //SetConsoleTextAttribute(hConsole, black);
            //cout << "|";
        }

        // zmiana na normalny kolor
        SetConsoleTextAttribute(hConsole, normal);
        if (ball_position == 37)
        {
            balls_laps_counter += 1;
            ball_position = 0;
            blank_line = "        ";
        }
        cout << "\n" << blank_line + "  O\n";
        blank_line += "    ";
        ball_position += 1;
        Sleep(timer);

        if (balls_laps_counter >= 2)
            timer += add;
        if (timer > 325)
        {
            ball_position--;
            break;
        }
    } while (true);
    return ball_position;
}

void RULETKA()
{
   if (gotowka > 0)
    {
        int roulette_choice;
        int mnoznik_ruletka = 0;

        do
        {   system("cls");
            cout << "Twoja gotowka: " << gotowka << "\n\n";
            Napis("napis_roulette.txt");

            cout << "\n\tWITAMY W GRZE SLOT MACHINE\n\tWybierz opcje:\n\n\
        1. Rozgrywka\n\
        2. Zasady\n\
        3. Menu glowne\n\t>> ";
            roulette_choice = getch()-48;

            if (roulette_choice > 0 && roulette_choice < 4)
            {
                switch (roulette_choice)
                {
                    case 1:
                    {
                        do
                        {
                            cin.clear();
                            system("cls");
                            cout << "Twoja gotowka: " << gotowka << endl;
                            cout << "\n";
                            Napis("napis_slot_machine.txt");

                            cout << "\n\tPodaj stawke o jaka chcesz zagrac: \n\t>> ";
                            cin >> stawka;
                            if (cin.good())
                            {
                                if (stawka > 0)
                                {
                                    if (stawka <= gotowka)
                                        break;
                                    else {cout << "\n\tNie masz tyle gotowki (" << gotowka << ")"; getch();}
                                }
                                else {cout << "\n\tWartosc mniejsza lub rowna 0"; getch();}
                            }

                            cin.clear();
                            cin.ignore();

                        }while(true);
                        gotowka -= stawka;

                        int roulette_choice_game = RULETKA_MENU();
                        int wynik = RULETKA_ROZGRYWKA();
                        cout << "\n\n";
                        //cout << "\t" << wybor_opcji_ruletka << "\n";
                        cout << "\tWynik: ";
                        if (wynik == 0)
                        {
                            SetConsoleTextAttribute(hConsole, green);
                            cout << "ZIELONE  0";
                        }
                        else
                        {
                            if (wynik%2 == 0)
                            {
                                SetConsoleTextAttribute(hConsole, black);
                                cout << "CZARNE  " << wynik;
                            }
                            else
                            {
                                SetConsoleTextAttribute(hConsole, red);
                                cout << "CZERWONE  " << wynik;
                            }
                        }
                        SetConsoleTextAttribute(hConsole, normal);
                        //wynik = 0;
                        if (wlasna_wartosc >= 0)
                        {
                            //gracz wybral wlasna wartosc
                            mnoznik_ruletka += 36;
                            if (wlasna_wartosc == wynik)
                                cout << "\n\n\tGratulacje! Wygrales "<<  stawka << " * " << mnoznik_ruletka << " = " << stawka * mnoznik_ruletka << " (" << gotowka << " + " << stawka * mnoznik_ruletka << " = " << gotowka + (stawka * mnoznik_ruletka) << ")";
                                gotowka += stawka * mnoznik_ruletka;
                                cout << "\n\n\t(wcisnij dowolny klawisz aby kontynuowac)\n\t>> ";
                                getch();
                        }
                        else
                        {

                            switch (roulette_menu_choice)
                            {case 1: //zielone 0
                                {
                                    if (wynik == 0)
                                    {
                                        mnoznik_ruletka += 36;
                                        cout << "\n\n\tGratulacje! Wygrales "<<  stawka << " * " << mnoznik_ruletka << " = " << stawka * mnoznik_ruletka << " (" << gotowka << " + " << stawka * mnoznik_ruletka << " = " << gotowka + (stawka * mnoznik_ruletka) << ")";
                                        gotowka += stawka * mnoznik_ruletka;
                                    }
                                    else
                                    {
                                        cout << "\n\n\tNiestety nie trafiles..\n";
                                    }
                                    break;
                                }
                            case 2: //Parzyste - Czarne
                                {
                                   if (wynik %2== 0)
                                    {
                                        mnoznik_ruletka += 18;
                                        cout << "\n\n\tGratulacje! Wygrales "<<  stawka << " * " << mnoznik_ruletka << " = " << stawka * mnoznik_ruletka << " (" << gotowka << " + " << stawka * mnoznik_ruletka << " = " << gotowka + (stawka * mnoznik_ruletka) << ")";
                                        gotowka += stawka * mnoznik_ruletka;
                                    }
                                    else
                                    {
                                        cout << "\n\n\tNiestety nie trafiles..\n";
                                    }
                                    break;
                                }
                            case 3: // 3. Nieparzyste - Czerwone
                                {
                                    if (wynik %2== 1)
                                    {
                                        mnoznik_ruletka += 18;
                                        cout << "\n\n\tGratulacje! Wygrales "<<  stawka << " * " << mnoznik_ruletka << " = " << stawka * mnoznik_ruletka << " (" << gotowka << " + " << stawka * mnoznik_ruletka << " = " << gotowka + (stawka * mnoznik_ruletka) << ")";
                                        gotowka += stawka * mnoznik_ruletka;
                                    }
                                    else
                                    {
                                        cout << "\n\n\tNiestety nie trafiles..\n";
                                    }
                                    break;
                                }
                            case 4: // Wartosc z przedzialu: 1-12
                                {
                                    if (wynik > 0 && wynik < 13)
                                    {
                                        mnoznik_ruletka += 12;
                                        cout << "\n\n\tGratulacje! Wygrales "<<  stawka << " * " << mnoznik_ruletka << " = " << stawka * mnoznik_ruletka << " (" << gotowka << " + " << stawka * mnoznik_ruletka << " = " << gotowka + (stawka * mnoznik_ruletka) << ")";
                                        gotowka += stawka * mnoznik_ruletka;
                                    }
                                    else
                                    {
                                        cout << "\n\n\tNiestety nie trafiles..\n";
                                    }
                                    break;
                                }
                            case 5: // Wartosc z przedzialu: 13-24
                                {
                                    if (wynik > 12 && wynik < 25)
                                    {
                                        mnoznik_ruletka += 12;
                                        cout << "\n\n\tGratulacje! Wygrales "<<  stawka << " * " << mnoznik_ruletka << " = " << stawka * mnoznik_ruletka << " (" << gotowka << " + " << stawka * mnoznik_ruletka << " = " << gotowka + (stawka * mnoznik_ruletka) << ")";
                                        gotowka += stawka * mnoznik_ruletka;
                                    }
                                    else
                                    {
                                        cout << "\n\n\tNiestety nie trafiles..\n";
                                    }
                                    break;
                                }
                            case 6: //Wartosc z przedzialu: 25-36
                                {
                                    if (wynik > 24 && wynik < 37)
                                    {
                                        mnoznik_ruletka += 12;
                                        cout << "\n\n\tGratulacje! Wygrales "<<  stawka << " * " << mnoznik_ruletka << " = " << stawka * mnoznik_ruletka << " (" << gotowka << " + " << stawka * mnoznik_ruletka << " = " << gotowka + (stawka * mnoznik_ruletka) << ")";
                                        gotowka += stawka * mnoznik_ruletka;
                                    }
                                    else
                                    {
                                        cout << "\n\n\tNiestety nie trafiles..\n";
                                    }
                                }break;}


                        mnoznik_ruletka = 0;
                        cout << "\n\n\t(wcisnij dowolny klawisz aby kontynuowac)\n\t>> ";
                        getch();
                        break;
                        }}


                    case 2: cout<< "\n\t\n\tZasady blackjacka opieraja sie na liczbie 21.\n\tGracz w rozdawanych mu przez krupiera kartach musi uzyskac 21 punktow lub maksymalnie zblizyc sie do \
tej liczby,\n\tw zadnym wypadku nie mogac jej przekroczyc. W blackjacku punktacja za poszczegolne figury prezentuje sie nastepujaco:\n\
    \t> Blotki - zgodnie z wartoscia numerowa, czyli na przyklad osemka oznacza 8 punktow\n\
    \t> Walet, Dama, Krol - 10 punktow\n\
    \t> As - 1 lub 11 punktow, w zaleznosci od tego, ktora opcja jest korzystniejsza\n\n\t(wcisnij dowolny klawisz aby kontynuowac)\n\t>> "; getch();
                    case 3: break;
                }
            }
            else
            {
                cout << "\n\n\t*** Bledna wartosc (wcisnij dowolny klawisz aby sprobowac ponownie) ***    \n\t>> ";
                getch();
            }
            if (gotowka == 0) break;



        } while(roulette_choice != 3);

    }
}


void JEDNOREKI_BANDYTA()
{
    int slot_machine_choice;
    if (gotowka > 0)
    {
        do
    {   system("cls");
        cout << "Twoja gotowka: " << gotowka << "\n\n";
        Napis("napis_slot_machine.txt");

        cout << "\n\tWITAMY W GRZE JEDNOREKI BANDYTA\n\tWybierz opcje:\n\n\
        1. Rozgrywka\n\
        2. Zasady\n\
        3. Menu glowne\n\t>> ";
        slot_machine_choice = getch()-48;

        if (slot_machine_choice > 0 && slot_machine_choice < 4)
        {
            switch (slot_machine_choice)
            {
                case 1: JEDNOREKI_BANDYTA_ROZGRYWKA();
                        break;
                case 2: cout << "\n\n\tGra Jednoreki Bandyta polega na wylosowaniu 3 takich samych obrazkow. \n\
        Zdobywana gotowka jest liczona w nastepujacy sposob (stawka * mnoznik):\n\
        >> Kazde dwa takie same obrazki dodaja x10 do mnoznika\n\
        >> Kazda gwiazda dodaje x20 do mnoznika!\n\
            Przyklady dla stawki 20 zl:\n\
                > Dwie szostki     20 * 10 =  200 zl!\n\
                > Trzy siodemki    20 * 20 =  400 zl!\n\
                > Dwie dwojki \n\
                  i jedna gwiazdka 20 * 30 =  600 zl!\n\
                > Dwie gwiazdki    20 * 50 = 1000 zl!\n\
                > Trzy gwiazdki    20 * 80 = 1600 zl!\n\
        \n\t(wcisnij dowolny klawisz aby kontynuowac)\n\t>> "; getch();
                case 3: break;
            }
        }
        else
        {
            cout << "\n\n\t*** Bledna wartosc (wcisnij dowolny klawisz aby sprobowac ponownie) ***    \n>>";
            getch();
        }
        if (gotowka == 0) break;

    } while(slot_machine_choice != 3);
    }


}

void WPLATA_GOTOWKI()
{
    int wplata;
    do
    {
        system("cls");
        cout << "Twoja gotowka: " << gotowka << "\n\n";
        Napis("napis_casino.txt");

        cout << "\tPodaj kwota jaka chcesz wplacic (min 1000, max 20 000): \n\t>> ";
        cin >> wplata;
        if (cin.good())
        {
            if (wplata > 1000)
            {
                if (wplata <= 20000)
                {
                    gotowka_ustalona = 0;
                    gotowka += wplata;
                }
                else cout << "\n\tJednorazowa maksymalna kwota wplaty to 20 000 zl";
            }
            else cout << "\n\tJednorazowa minimalna kwota wplaty to 1000 zl";
        }

        cin.clear();
        cin.ignore();

    }while(gotowka_ustalona);
}


int main()
{
    srand (time(NULL));
    // Wyœwietlenie terminalu w fullscreen
    ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
    //gotowka = rand() % 50 + 900;

    // do usuniecia
    //gotowka = 5000;
    //gotowka_ustalona = 0;
    ///////////////


    int mainloop_choice;

    if (gotowka_ustalona);
    {
        do
        {
            system("cls");
            cout << "Twoja gotowka: " << gotowka << "\n\n";
            Napis("napis_casino.txt");
            cout << "\n\t\t\t\t       WITAMY SERDECZNIE W NASZYM KASYNIE! ZYCZYMY JAK NAJWYZSZYCH WYGRANYCH!\n";

            cout << "\n\tProsze wybrac jedna z ponizszych opcji:\n\n\
        1. Wplata gotowki (min 1000, max 20 000):\n\
        2. Wyjscie \n\n\
        >> ";
            mainloop_choice = getch()-48;
            if (mainloop_choice > 0 && mainloop_choice < 3)
            {
                switch(mainloop_choice)
                {
                    case 1: WPLATA_GOTOWKI();
                            break;
                    case 2: cout << "\n\n\tDziekujemy i zapraszamy ponownie.\n\n";
                            return 0;

                }
            }
            else
            {
                cout << "\n\n\t*** Bledna wartosc (wcisnij dowolny klawisz aby sprobowac ponownie) ***    \n\t>> ";
                getch();
                system("cls");
            }

        } while (mainloop_choice != 2 && gotowka_ustalona);
    }

    if (gotowka > 0)
        do
        {
            if (gotowka == 0) break;
            system("cls");
            cout << "Twoja gotowka: " << gotowka << "\n\n";
            Napis("napis_casino.txt");
            cout << "\n\t\t\t\t       WITAMY SERDECZNIE W NASZYM KASYNIE! ZYCZYMY JAK NAJWYZSZYCH WYGRANYCH!\n";

            cout << "\n\tProsze wybrac jedna z ponizszych opcji:\n\n\
        1. BlackJack \n\
        2. Jednoreki bandyta \n\
        3. Ruletka \n\
        4. Wyjscie \n\
        >> ";
            mainloop_choice = getch()-48;
            if (mainloop_choice > 0 && mainloop_choice < 6)
            {
                switch(mainloop_choice)
                {
                    case 1: BLACKJACK();
                            break;
                    case 2: JEDNOREKI_BANDYTA();
                            break;
                    case 3: RULETKA();
                            break;
                    case 4: cout << "\n\n\tDziekujemy i zapraszamy ponownie.\n\n"; return 0;
                }
            }
            else
            {
                cout << "\n\n\t*** Bledna wartosc (wcisnij dowolny klawisz aby sprobowac ponownie) ***    \n\t>> ";
                getch();
                system("cls");
            }

        } while (mainloop_choice != 5);

    if (gotowka == 0 && stawka == 0)
        system("cls");
        system("cls");
        cout << "Twoja gotowka: " << gotowka << "\n\n";
        Napis("napis_casino.txt");

        cout << "\n\n\tNiestety nie posiadasz juz pieniedzy. Dziekujemy za gre.\n\n";


    return 0;
}




