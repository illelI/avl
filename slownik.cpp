#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
using namespace std;

class wezel
{
public:
    int waga;
    string slowo;
    vector<string> tlumaczenie;
    wezel* lewy;
    wezel* prawy;
    Wezel()
    {
        this->lewy = NULL;
        this->prawy = NULL;
        waga = 0;
    }
    ~wezel()
    {
        delete lewy;
        delete prawy;
    }
};

class avl
{
public:
    wezel* korzen = NULL;
    void insert(string sl, string tl) //tworzy nowy obiekt typu wezel*, dodaje slowo i tlumaczenie przeslane do funkcji
    {                                  //sprzawdza, czy korzen jest nullem, jesli tak to ustawia korzen jako w, jesli nie to wywoluje funkcje wstaw
        wezel* w = new wezel;
        w->slowo = sl;
        w->lewy = NULL;
        w->prawy = NULL;
        w->tlumaczenie.push_back(tl);
        w->waga = 0;
        if(korzen == NULL)
            korzen = w;
        else
            wstaw(w, korzen);
    }
    int test(string s1, string s2) //porownuje slowa
    {
        int dl = max(s1.length(), s2.length());
        for(int i = 0; i < dl; i++) //idzie po dluzszym slowie i zwraca 1 jestli s1 ma na i-tej pozycji wieksza litere od s2 lub -1 jesli mniejsza
        {
            if(s1[i] > s2[i]) return 1;
            else if(s1[i] < s2[i]) return -1;
        }
        return 0; //jesli przeleci cala petle, oznacza to, ze slowa sa takie same
    }
    void wstaw(wezel* w, wezel* &w1)
    {
        if(w1 == NULL) w1 = w; //sprawdza czy w1 jest nullem, jesli tak to ustawia je jako w
        else if(!test(w->slowo, w1->slowo)) //jesli nie jest nullem i slowa sa takie same to wyswietla komunikat i wraca
        {
            cout<<"Podane slowo juz istnieje"<<endl;
            return;
        }
        else if(test(w->slowo, w1->slowo) == -1) wstaw(w, w1->lewy); //jesli test zwroci -1 to idzie do lewego syna
        else wstaw(w, w1->prawy); //jesli nie to idzie do prawego
        w1->waga = waga(w1); //gdy rekurencja sie wraca to liczy wagi dla aktualnego wezla
        if(w1->waga == 2 || w1->waga == -2) rownowaz(w1); //jesli waga wynosi 2 lub -2 to rownowazy drzewp
    }
    int wysokosc(wezel* w) //zwraca wieksza wysokosc z lewego lub prawego poddewa i dodaje 1 do niej
    {
        if(w == NULL)
            return 0;
        return max(wysokosc(w->lewy), wysokosc(w->prawy)) + 1;
    }
    int waga(wezel* w) //na podstawie wysokosci lewego i prawego poddrzewa zwraca wage
    {
        if(w == NULL)
            return 0;
        return wysokosc(w->lewy) - wysokosc(w->prawy);
    }
    void rownowaz(wezel* &w)
    {
        w->waga = waga(w);
        if(w->waga == 2)
        {
            if(waga(w->lewy) == -1)
                w = LR(w); //jesli waga w wynosi 2, a lewego podsyna -1 to rotacja lewo prawo
            else
                w = RR(w); //jesli waga w wynosi 2, a lewego podsyna 0 lub 1 to rotacja w prawo
        }
        if(w->waga == -2)
        {
            if(waga(w->prawy) == 1)
                w = RL(w); //jesli waga w wynosi -2, a praweho podsyna 1 to rotacja prawo lewo
            else
                w = LL(w); //jesli waga w wynosi -2, a praweho podsyna 0 lub -1 to rotacja w lewo
        }
        w->waga = waga(w); //obliczanie nowej wagi
        if(w->lewy != NULL)w->lewy->waga = waga(w->lewy); //jesli synowie nie sa nullami to oblicza jeszcze dla nich nowa wage
        if(w->prawy != NULL)w->prawy->waga = waga(w->prawy);
    }
    wezel* RR(wezel* w) //te 4 funkcje to rotacje,  w rr i ll to samo przepinanie wskaznikow dla rl i lr dodatkowo wywolanie pojedynczej rotacji dla syna, a nastepnie dla siebie
    {
        wezel* pom = new wezel;
        pom = w->lewy;
        w->lewy = pom->prawy;
        pom->prawy = w;
        return pom;
    }
    wezel* LL(wezel* w)
    {
        wezel* pom = new wezel;
        pom = w->prawy;
        w->prawy = pom->lewy;
        pom->lewy = w;
        return pom;
    }
    wezel* RL(wezel* w)
    {
        wezel* pom = new wezel;
        pom = w->prawy;
        w->prawy = RR(pom);
        return LL(w);
    }
    wezel* LR(wezel* w)
    {
        wezel* pom = new wezel;
        pom = w->lewy;
        w->lewy = LL(pom);
        return RR(w);
    }
    void szukaj(string klucz)
    {
        if(korzen == NULL)
        {
            cout<<"Brak tlumaczen slowa "<<klucz<<endl;
            return;
        }
        if(test(klucz, korzen->slowo) == 0) { //jesli slowa sa takie same to wypisuje slowo i wszystkie tlumacznia
            cout<<korzen->slowo<<" ";
            for(string s : korzen->tlumaczenie)
                cout<<s<<" ";
            cout<<endl;
        }
        else if(test(klucz, korzen->slowo) == 1) szukaj2(klucz, korzen->prawy); //jesli slowa sie roznia to wywoluje szukaj2 w zaleznosci od tego, ktore slowo jest pierwsze w porzadku alfabetycznym
        else szukaj2(klucz, korzen->lewy);
    }
    void szukaj2(string klucz, wezel* w) //w zasadzie to samo co szukaj, tyle, ze tutaj przekazywany jest jeszcze aktualny wezel, w ktorym sie znajdujemy
    {
        if(w == NULL)
        {
            cout<<"Brak tlumaczen slowa "<<klucz<<endl;
            return;
        }
        if(!test(klucz, w->slowo)) {
            cout<<w->slowo<<" ";
            for(string s : w->tlumaczenie)
                cout<<s<<" ";
            cout<<endl;
        }
        else if(test(klucz, w->slowo) == 1 ) szukaj2(klucz, w->prawy);
        else szukaj2(klucz, w->lewy);
    }
    void usun(string klucz)
    {
        usun2(klucz, korzen);
    }
    void usun2(string klucz, wezel* &w) //usuwanie zrobilem tak, ze wybiera z lewego poddrzewa "najwiekszy" element, ktory trafia w miejsce usuwanego elementu
    {
        if(w == NULL)
        {
            cout<<"Nie znaleziono elementu"<<endl;
            return;
        }
        if(!test(klucz, w->slowo)) //slowo do usuniecia zostalo znalezione
        {
            if(w->lewy != NULL) //posiada lewego syna
            {
                w = znajdzNajwiekszy(w->lewy, w); //przypisuje do w najwiekszy element z lewego poddrzewa
                znajdzDoUsuniecia(w->slowo, w->lewy); //usuwa ten element z lewego poddrzewa
            }
            else if(w->prawy != NULL) w = w->prawy;  //jesli nie posiada lewego syna, a posiada prawego syna to sie staje tym prawym
            else w = NULL; //jesli nie ma synow to staje sie nullem
        }
        else if(test(klucz, korzen->slowo) == 1)
            usun2(klucz, w->prawy);
        else
            usun2(klucz, w->lewy);
        if(w != NULL) rownowaz(w); //jesli nie jest nullem to oblicza nowe wagi wracajac z rekurencji

    }
    wezel* znajdzNajwiekszy(wezel* &w, wezel* w1)
    {
        if(w->prawy == NULL)                    //jesli nie moze isc bardziej na prawo
        {                                        //to tworzy nowy obiekt, przepisuje z aktualnego jego slowo oraz tlumaczenie
            wezel* pom = new wezel;                //a jako synow ustawia synow tego elementu, ktory uswami
            pom->slowo = w->slowo;
            pom->lewy = w1->lewy;
            pom->prawy = w1->prawy;
            pom->tlumaczenie = w->tlumaczenie; //<- w tej linijce zapomnialem poprawic i ci stara wersje wyslalem, wiec jak cos to tutaj ma byc w->tlumaczenie, a nie w1->tlumaczenie
            if(w->lewy != NULL) //jesli ten element ma lewego podsyna to sie nim staje
                w = w->lewy;
            return pom;
        }
        else return znajdzNajwiekszy(w->prawy, w1);
    }
    void znajdzDoUsuniecia(string klucz, wezel* &w) //jesli znajdzie element, ktorego slowo jest takie samo jak klucz to ustawia go na nulla
    {
        if(w == NULL) return;
        if(!test(klucz, w->slowo))
        {
            w = NULL;
            return;
        }
        else if(test(klucz, w->slowo) == -1)
            znajdzDoUsuniecia(klucz, w->lewy);
        else
            znajdzDoUsuniecia(klucz, w->prawy);
        rownowaz(w);
    }
    void zapisz(fstream &p)
    {
        p.open("OutTest5.txt", ios::out | ios::trunc);
        klpP(korzen, p);
        p.close();
    }
    void klpP(wezel* w, fstream &p) //wrzuca do pliku slowa, ilosc tlumaczen i wszystkie tlumaczenia, a nastepnie wywojue sie dla lewego syna i prawego syna
    {
        if(w == NULL) return;
        p<<w->slowo<<" "<<w->tlumaczenie.size()<<" ";
        for(string s : w->tlumaczenie)
            p<<s<<" ";
        p<<endl;
        klpP(w->lewy, p);
        klpP(w->prawy, p);
        return;
    }
    void dodajtl(string klucz, string tlumaczenie) //to samo co w szukaj, tylko zamiast wypisywac slowa i jego tlumaczenia to dodaje kolejne tlumaczenie
    {
        if(korzen == NULL)
        {
            cout<<"Brak slowa w slowniku"<<endl;
            return;
        }
        if(test(klucz, korzen->slowo) == 0)
            korzen->tlumaczenie.push_back(tlumaczenie);
        else if(test(klucz, korzen->slowo) == 1) dodajtl2(klucz, korzen->prawy, tlumaczenie);
        else dodajtl2(klucz, korzen->lewy, tlumaczenie);
    }
    void dodajtl2(string klucz, wezel* w, string tlumaczenie)
    {
        if(w == NULL)
        {
            cout<<"Brak slowa w slowniku"<<endl;
            return;
        }
        if(!test(klucz, w->slowo))
            w->tlumaczenie.push_back(tlumaczenie);
        else if(test(klucz, w->slowo) == 1 ) dodajtl2(klucz, w->prawy, tlumaczenie);
        else dodajtl2(klucz, w->lewy, tlumaczenie);
    }
    Avl()
    {
        korzen = new wezel;
    }
};


int main()
{
    string pom, napis;
    avl* sl = new avl;
    fstream plik;
    int s, tmp;
    for(;;)
    {
        cout<<endl<<"1. Plik -> Wczytaj"<<endl;
        cout<<"2. Plik -> Zapisz"<<endl;
        cout<<"3. Wstaw"<<endl;
        cout<<"4. Dodaj tlumaczenie"<<endl;
        cout<<"5. Wyszukaj"<<endl;
        cout<<"6. Usun"<<endl;
        cout<<"7. Zamknij"<<endl;
        cin>>s;
        switch(s)
        {
        case 1:
            plik.open("InTest20501.txt", ios::in);
            while(!plik.eof())
            {
               plik>>pom;
               plik>>tmp;
               plik>>napis;
               sl->insert(pom, napis);
               for(int i = 0; i < tmp - 1; i++)
               {
                   plik>>napis;
                   sl->dodajtl(pom, napis);
               }
            }
            plik.close();
            break;
        case 2:
            sl->zapisz(plik);
            break;
        case 3:
            cout<<"Podaj slowo: ";
            cin>>napis;
            pom = napis;
            cout<<"Podaj tlumaczenie: ";
            cin>>napis;
            sl->insert(pom, napis);
            break;
        case 4:
            cout<<"Podaj slowo: ";
            cin>>napis;
            pom = napis;
            cout<<"Podaj tlumaczenie: ";
            cin>>napis;
            sl->dodajtl(pom, napis);
            break;
        case 5:
            cout<<"Podaj slowo: ";
            cin>>napis;
            sl->szukaj(napis);
            break;
        case 6:
            cout<<"Podaj slowo: ";
            cin>>napis;
            sl->usun(napis);
            break;
        case 7:
            return 0;
        }
    }
    return 0;
}

// format pliku:
// sl_angielskie ilosc_tlumaczen tlumaczenia
// s³owa zapisane w porz¹dku klp
