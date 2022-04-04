#include <iostream>
#include <fstream>
using namespace std;

class wezel
{
public:
    int waga;
    string slowo;
    wezel* tlumaczenie;
    wezel* lewy;
    wezel* prawy;
    Wezel()
    {
        this->tlumaczenie = NULL;
        this->lewy = NULL;
        this->prawy = NULL;
        waga = 0;
    }
    ~wezel()
    {
        delete tlumaczenie;
        delete lewy;
        delete prawy;
    }
};

class avl
{
public:
    wezel* korzen = NULL;
    void insert(string sl, string tl, avl* &a)
    {
        wezel* w = new wezel;
        wezel* tlumaczenie = new wezel;
        tlumaczenie->slowo = tl;
        tlumaczenie->lewy = NULL;
        tlumaczenie->prawy = NULL;
        tlumaczenie->waga = 0;
        tlumaczenie->tlumaczenie = w;
        w->slowo = sl;
        w->lewy = NULL;
        w->prawy = NULL;
        w->tlumaczenie = tlumaczenie;
        w->waga = 0;
        if(korzen == NULL)
        {
            korzen = w;
            if(a->korzen == NULL) a->korzen = tlumaczenie;
        }

        else
        {
            wstaw(w, korzen);
            a->wstaw(tlumaczenie, a->korzen);
        }
    }
    void insertC(string sl, string tl, avl* &a)
    {
        wezel* w = new wezel;
        wezel* tlumaczenie = new wezel;
        tlumaczenie->slowo = tl;
        tlumaczenie->lewy = NULL;
        tlumaczenie->prawy = NULL;
        tlumaczenie->waga = 0;
        tlumaczenie->tlumaczenie = w;
        w->slowo = sl;
        w->lewy = NULL;
        w->prawy = NULL;
        w->tlumaczenie = tlumaczenie;
        w->waga = 0;
        if(korzen == NULL)
        {
            korzen = w;
            if(a->korzen == NULL) a->korzen = tlumaczenie;
        }

        else
        {
            wstawC(w, korzen);
            a->wstawC(tlumaczenie, a->korzen);
        }
    }
    int test(string s1, string s2)
    {
        int dl = max(s1.length(), s2.length());
        for(int i = 0; i < dl; i++)
        {
            if(s1[i] > s2[i]) return 1;
            else if(s1[i] < s2[i]) return -1;
        }
        return 0;
    }
    void wstaw(wezel* w, wezel* &w1)
    {
        if(w1 == NULL) w1 = w;
        else if(!test(w->slowo, w1->slowo))
        {
            cout<<"Podane slowo juz istnieje"<<endl;
            return;
        }
        else if(test(w->slowo, w1->slowo) == -1) wstaw(w, w1->lewy);
        else wstaw(w, w1->prawy);
        w1->waga = waga(w1);
        if(w1->waga == 2 || w1->waga == -2) rownowaz(w1);
    }
    void wstawC(wezel* w, wezel* &w1)
    {
        if(w1 == NULL) w1 = w;
        else if(!test(w->slowo, w1->slowo))
            return;
        else if(test(w->slowo, w1->slowo) == -1) wstaw(w, w1->lewy);
        else wstaw(w, w1->prawy);
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
        cout<<w->slowo<<" "<<w->tlumaczenie<<endl;
        klp(w->lewy);
        klp(w->prawy);
        return;
    }
    void szukaj(string klucz)
    {
        if(korzen == NULL)
        {
            cout<<"Nie znaleziono"<<endl;
            return;
        }
        if(test(klucz, korzen->slowo) == 0)
            cout<<korzen->slowo<<" "<<korzen->tlumaczenie->slowo<<endl;
        else if(test(klucz, korzen->slowo) == 1) szukaj2(klucz, korzen->prawy);
        else szukaj2(klucz, korzen->lewy);
    }
    void szukaj2(string klucz, wezel* w)
    {
        if(w == NULL)
        {
            cout<<"Nie znaleziono"<<endl;
            return;
        }
        if(!test(klucz, w->slowo))
            cout<<w->slowo<<" "<<w->tlumaczenie->slowo<<endl;
        else if(test(klucz, w->slowo) == 1 ) szukaj2(klucz, w->prawy);
        else szukaj2(klucz, w->lewy);
    }
    void usun(string klucz, avl* &a, int d = 0)
    {
        if(d < 2) usun2(klucz, korzen, a, d);
    }
    void usun2(string klucz, wezel* &w, avl* &a, int d)
    {
        if(w == NULL)
        {
            cout<<"Nie znaleziono elementu"<<endl;
            return;
        }
        if(!test(klucz, w->slowo))
        {
            if(d == 0)
                    d++;
            a->usun(w->tlumaczenie->slowo, a, d);
            if(w->lewy != NULL)
            {
                w = znajdzNajwiekszy(w->lewy, w);
                znajdzDoUsuniecia(w->slowo, w->lewy);
            }
            else if(w->prawy != NULL) w = w->prawy;
            else w = NULL;
        }
        else if(test(klucz, korzen->slowo) == 1)
            usun2(klucz, w->prawy, a, d);
        else
            usun2(klucz, w->lewy, a, d);
        if(w != NULL) rownowaz(w);

    }
    wezel* znajdzNajwiekszy(wezel* &w, wezel* w1)
    {
        if(w->prawy == NULL)
        {
            wezel* pom = new wezel;
            pom->slowo = w->slowo;
            pom->lewy = w1->lewy;
            pom->prawy = w1->prawy;
            pom->tlumaczenie = w1->tlumaczenie;
            if(w->lewy != NULL)
                w = w->lewy;
            return pom;
        }
        else return znajdzNajwiekszy(w->prawy, w1);
    }
    void znajdzDoUsuniecia(string klucz, wezel* &w)
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
    void klpP(wezel* w, fstream &p)
    {
        if(w == NULL) return;
        p<<w->slowo<<" "<<w->tlumaczenie->slowo<<endl;
        klpP(w->lewy, p);
        klpP(w->prawy, p);
        return;
    }
    Avl()
    {
        korzen = new wezel;
    }
};

struct slownik
{
    avl* pol = new avl;
    avl* ang = new avl;
};

int main()
{
    slownik* sl = new slownik;
    string pom, napis;
    fstream plik;
    int s;
    for(;;)
    {
        cout<<endl<<"1. Plik -> Wczytaj"<<endl;
        cout<<"2. Plik -> Zapisz"<<endl;
        cout<<"3. Wstaw -> Polskie slowo"<<endl;
        cout<<"4. Wstaw -> Angielskie slowo"<<endl;
        cout<<"5. Wyszukaj -> Polskie slowo"<<endl;
        cout<<"6. Wyszukaj -> Angielskie slowo"<<endl;
        cout<<"7. Usun -> Polskie slowo"<<endl;
        cout<<"8. Usun -> Angielskie slowo"<<endl;
        cout<<"9. Zamknij"<<endl;
        cin>>s;
        switch(s)
        {
        case 1:
            plik.open("InTest20501.txt", ios::in);
            while(!plik.eof())
            {
               plik>>napis;
               pom = napis;
               plik>>napis;
               sl->ang->insertC(pom, napis, sl->pol);
            }
            plik.close();
            break;
        case 2:
            sl->ang->zapisz(plik);
            break;
        case 3:
            cout<<"Podaj slowo: ";
            cin>>napis;
            pom = napis;
            cout<<"Podaj tlumaczenie: ";
            cin>>napis;
            sl->pol->insert(pom, napis, sl->ang);
            break;
        case 4:
            cout<<"Podaj slowo: ";
            cin>>napis;
            pom = napis;
            cout<<"Podaj tlumaczenie: ";
            cin>>napis;
            sl->ang->insert(pom, napis, sl->pol);
            break;
        case 5:
            cout<<"Podaj slowo: ";
            cin>>napis;
            sl->pol->szukaj(napis);
            break;
        case 6:
            cout<<"Podaj slowo: ";
            cin>>napis;
            sl->ang->szukaj(napis);
            break;
        case 7:
            cout<<"Podaj slowo: ";
            cin>>napis;
            sl->pol->usun(napis, sl->ang);
            break;
        case 8:
            cout<<"Podaj slowo: ";
            cin>>napis;
            sl->ang->usun(napis, sl->pol);
            break;
        case 9:
            return 0;
        }
    }
    return 0;
}
