/** /
Ez a program nem mûködik, de nagyon tanulságos a hiba, hogy miért nem.

A MESTER-en is megtalálható rúddarabolás feladatról van szó, a feladat lényege igazából lényegtelen. A lényeg az, hogy a program három függvénybõl épül fel:
    
    1) Beolvas: Beolvassa az adatokat és létrehozza az input struktúrát
    2) Feldolgoz: Megkapja az input-struktúrát és csinál belõle egy Output-struktúrát
    3) Kiír: Kiírja az adatokat.

Viszont nem mûködik. Step-by-step az lesz, hogy 
    - Input létrejön, 
    - címet visszaadja, függvényen kívül is látszik, hogy léteznek ott az adatok, 
    - Feldolgozba bemegy az input, ott is látni, hogy normálisak az adatok
    - De amint elkezd futni az output konstruktora, megváltozik az input elemszáma. Más viszont érdekes módon nem.

    Ez azért van, mert...
    " Input egy lokális, azaz stacken lakó változó
      Beolvas const&-el tér vissza, nincs se copy, se move, hanem a stacken lévõ változó címet adja vissza, 
        aztán lefuttatja a destruktorát, majd lebontja a stack frame-et. 
      Utána ezt a címet (ami már hivatalosan "sehova" mutat, de a valóságban még ott van a stacken az érték), 
        átadja a feldolgoznak, aki, miközben létrehozza a saját stack frame-jét, felülírja az adatot
    
    Szóval ez egy szép példa arra, hogy lehet olyan adattal is dolgozni, ami nincs is ott.
/**/


/** /
const Input& Beolvas()
{
    Input be;

    cerr << "a darabok szama: ";
    cin >> be.N;


    for (int i = 0; i < be.N; i++)
    {
        cerr << "az " << i << ". darab hossza: ";
        cin >> be.T[i];
    }
    return be;
}

Output Feldolgoz(const Input& be)
{
    Output ki(be.N);
    priority_queue<int, vector<int>, greater<int>> kupac;

    // ezt majd a konstruktorba



    for (int i = 0; i < be.N; i++)
    {
        kupac.push(be.T[i]);
    }



    for (int i = ki.N - 1; i >= 0; i--)
    {
        ki.egyik[i] = kupac.top();
        kupac.pop();
        ki.masik[i] = kupac.top();
        kupac.pop();
        ki.egesz[i] = ki.egyik[i] + ki.masik[i];
        ki.koltseg += ki.egesz[i];
        kupac.push(ki.egesz[i]);
    }

    return ki;
}
/**/

#include <iostream>
#include <queue>
using namespace std;

struct Input
{
    static const int max_N = 1000;
    int T[max_N];
    int N;
};

struct Output
{
    static const int max_N = 999;
    int* egesz;
    int* egyik;
    int* masik; // ezt egy egész változóval is ki lehetne váltani, de átlátható tõle a kód és könnyû ellenõrizni kiíráskor.
    int koltseg;
    int N;

    Output(const int db)
    {
        N = db - 1;
        egyik = new int[N];
        masik = new int[N];
        egesz = new int[N];
        koltseg = 0;
    }
};

const Input& Beolvas();
Output Feldolgoz(const Input&);
void Kiir(const Output&);

int main()
{
    Kiir(Feldolgoz(Beolvas()));
}

const Input& Beolvas()
{
    Input be;

    cerr << "a darabok szama: ";
    cin >> be.N;


    for (int i = 0; i < be.N; i++)
    {
        cerr << "az " << i << ". darab hossza: ";
        cin >> be.T[i];
    }
    return be;
}

Output Feldolgoz(const Input& be)
{
    Output ki(be.N);
    priority_queue<int, vector<int>, greater<int>> kupac;

    // ezt majd a konstruktorba



    for (int i = 0; i < be.N; i++)
    {
        kupac.push(be.T[i]);
    }



    for (int i = ki.N - 1; i >= 0; i--)
    {
        ki.egyik[i] = kupac.top();
        kupac.pop();
        ki.masik[i] = kupac.top();
        kupac.pop();
        ki.egesz[i] = ki.egyik[i] + ki.masik[i];
        ki.koltseg += ki.egesz[i];
        kupac.push(ki.egesz[i]);
    }

    return ki;
}

void Kiir(const Output& ki)
{
    cout << ki.koltseg << endl;
    for (int i = 0; i < ki.N; i++)
    {
        cerr << "az " << i<<". lepesben kettevagando rud hossza ";
        cout << ki.egesz[i] << " ";
        cerr << ", az igy keletkezo (egyik) rud hossza pedig ";
        cout << ki.egyik[i];
        cerr << " " << ki.masik[i] << endl;
        cout << endl;
    }
}