#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
using namespace std;

class wezel
{
public:
    int waga;
    int liczba;
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
    void insert(int klucz)
    {
        wezel* w = new wezel;
        w->liczba = klucz;
        w->lewy = NULL;
        w->prawy = NULL;
        w->waga = 0;
        if(korzen == NULL) korzen = w;
        else wstaw(w, korzen);
    }
    void insertC(int klucz)
    {
        wezel* w = new wezel;
        w->liczba = klucz;
        w->lewy = NULL;
        w->prawy = NULL;
        w->waga = 0;
        if(korzen == NULL) korzen = w;
        else wstawC(w, korzen);
    }
    void wstaw(wezel* w, wezel* &w1)
    {
        if(w1 == NULL) w1 = w;
        else if(w1->liczba == w->liczba)
        {
            cout<<"Podana liczba juz istnieje"<<endl;
            return;
        }
        else if(w1->liczba > w->liczba) wstaw(w, w1->lewy);
        else wstaw(w, w1->prawy);
        w1->waga = waga(w1);
        if(w1->waga == 2 || w1->waga == -2) rownowaz(w1);
    }
    void wstawC(wezel* w, wezel* &w1)
    {
        if(w1 == NULL) w1 = w;
        else if(w1->liczba == w->liczba)
            return;
        else if(w1->liczba > w->liczba) wstawC(w, w1->lewy);
        else wstawC(w, w1->prawy);
        w1->waga = waga(w1);
        if(w1->waga == 2 || w1->waga == -2) rownowaz(w1);
    }
    int wysokosc(wezel* w)
    {
        if(w == NULL)
            return 0;
        return max(wysokosc(w->lewy), wysokosc(w->prawy)) + 1;
    }
    int waga(wezel* w)
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
                w = LR(w);
            else
                w = RR(w);
        }
        if(w->waga == -2)
        {
            if(waga(w->prawy) == 1)
                w = RL(w);
            else
                w = LL(w);
        }
        w->waga = waga(w);
        if(w->lewy != NULL)w->lewy->waga = waga(w->lewy);
        if(w->prawy != NULL)w->prawy->waga = waga(w->prawy);
    }
    wezel* RR(wezel* w)
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
    void wypisz()
    {
        klp(korzen);
    }
    void klp(wezel* w)
    {
        if(w == NULL) return;
        cout<<w->liczba<<" "<<w->waga<<endl;
        klp(w->lewy);
        klp(w->prawy);
        return;
    }
    void szukaj(int klucz)
    {
        int poziom = 0;
        if(korzen == NULL)
        {
            cout<<"Nie znaleziono"<<endl;
            return;
        }
        if(klucz == korzen->liczba)
            cout<<"Znaleziono na poziomie: "<<poziom<<" Waga: "<<korzen->waga<<endl;
        else if(klucz > korzen->liczba) szukaj2(klucz, korzen->prawy, poziom+1);
        else szukaj2(klucz, korzen->lewy, poziom+1);
    }
    void szukaj2(int klucz, wezel* w, int poziom)
    {
        if(w == NULL)
        {
            cout<<"Nie znaleziono"<<endl;
            return;
        }
        if(klucz == w->liczba)
            cout<<"Znaleziono na poziomie: "<<poziom<<" Waga: "<<w->waga<<endl;
        else if(klucz > w->liczba) szukaj2(klucz, w->prawy, poziom+1);
        else szukaj2(klucz, w->lewy, poziom+1);
    }
    void usun(int klucz)
    {
        usun2(klucz, korzen);
    }
    void usun2(int klucz, wezel* &w)
    {
        if(w == NULL)
        {
            cout<<"Nie znaleziono elementu"<<endl;
            return;
        }
        if(klucz == w->liczba)
        {
            if(w->lewy != NULL)
            {
                w->liczba = znajdzNajwiekszy(w->lewy, w);
                znajdzDoUsuniecia(w->liczba, w->lewy);

            }
            else if(w->prawy != NULL) w = w->prawy;
            else w = NULL;
        }
        else if(klucz > w->liczba)
            usun2(klucz, w->prawy);
        else
            usun2(klucz, w->lewy);
        if(w != NULL) rownowaz(w);
    }
    int znajdzNajwiekszy(wezel* &w, wezel* w1)
    {
        if(w->prawy == NULL)
        {
            int pom;
            pom = w->liczba;
            //wezel* pom = new wezel;
            //pom->liczba = w->liczba;
            //pom->lewy = w1->lewy;
            //pom->prawy = w1->prawy;
            if(w->lewy != NULL)
                w = w->lewy;
            return pom;
        }
        else return znajdzNajwiekszy(w->prawy, w1);
    }
    void znajdzDoUsuniecia(int klucz, wezel* &w)
    {
        if(w == NULL) return;
        if(w->liczba == klucz)
        {
            w = NULL;
            return;
        }
        else if(w->liczba > klucz)
            znajdzDoUsuniecia(klucz, w->lewy);
        else
            znajdzDoUsuniecia(klucz, w->prawy);
        rownowaz(w);
    }
    void zapisz(fstream &p)
    {
        p.open("OutTest3.txt", ios::out | ios::trunc);
        klpP(korzen, p);
        p.close();
    }
    void klpP(wezel* w, fstream &p)
    {
        if(w == NULL) return;
        p<<w->liczba<<" ("<<w->waga<<") ";
        klpP(w->lewy, p);
        klpP(w->prawy, p);
        return;
    }
    Avl()
    {
        korzen = new wezel;
    }
};

int main()
{
    avl *p = new avl;
    int n, zakresP, zakresK, ilosc, pom;
    fstream plik;
    srand(time(NULL));
    for(;;)
    {
        cout<<"1. Wczytaj z pliku\n";
        cout<<"2. Losuj z zakresu\n";
        cout<<"3. Zapisz do pliku\n";
        cout<<"4. Znajdz element\n";
        cout<<"5. Dodaj element\n";
        cout<<"6. Usun element\n";
        cout<<"7. Wypisz elementy\n";
        cout<<"8. Zakoncz\n";
        cin>>n;
        switch(n)
        {
        case 1:
            plik.open("InTest1.txt", ios::in);
            while(!plik.eof())
            {
                plik>>n;
                p->insertC(n);
            }
            plik.close();
            break;
        case 2:
            plik.open("OutTest2.txt", ios::out | ios::trunc );
            cout<<"Podaj zakres: \n";
            cin>>zakresP;
            cin>>zakresK;
            cout<<"Podaj ilosc: \n";
            cin>>ilosc;
            for(int i = 0; i< ilosc; i++)
            {
                pom = rand()%(zakresK+1-zakresP) + zakresP;
                plik<<pom<<" ";
                p->insertC(pom);
            }
            plik.close();
            break;
        case 3:
            p->zapisz(plik);
            break;
        case 4:
            cout<<"Jaki element chcesz znalezc? ";
            cin>>pom;
            p->szukaj(pom);
            break;
        case 5:
            cout<<"Podaj klucz elementu: ";
            cin>>pom;
            p->insert(pom);
            break;
        case 6:
            cout<<"Podaj klucz elementu: ";
            cin>>pom;
            p->usun(pom);
            break;
        case 7:
            p->wypisz();
            break;
        case 8:
            return 0;
        }
    }
    return 0;
}
