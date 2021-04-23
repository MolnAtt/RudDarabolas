/** /
Ez a program nem m�k�dik, de nagyon tanuls�gos a hiba, hogy mi�rt nem.

A MESTER-en is megtal�lhat� r�ddarabol�s feladatr�l van sz�, a feladat l�nyege igaz�b�l l�nyegtelen. A l�nyeg az, hogy a program h�rom f�ggv�nyb�l �p�l fel:
    
    1) Beolvas: Beolvassa az adatokat �s l�trehozza az input strukt�r�t
    2) Feldolgoz: Megkapja az input-strukt�r�t �s csin�l bel�le egy Output-strukt�r�t
    3) Ki�r: Ki�rja az adatokat.

Viszont nem m�k�dik. Step-by-step az lesz, hogy 
    - Input l�trej�n, 
    - c�met visszaadja, f�ggv�nyen k�v�l is l�tszik, hogy l�teznek ott az adatok, 
    - Feldolgozba bemegy az input, ott is l�tni, hogy norm�lisak az adatok
    - De amint elkezd futni az output konstruktora, megv�ltozik az input elemsz�ma. M�s viszont �rdekes m�don nem.

    Ez az�rt van, mert...
    " Input egy lok�lis, azaz stacken lak� v�ltoz�
      Beolvas const&-el t�r vissza, nincs se copy, se move, hanem a stacken l�v� v�ltoz� c�met adja vissza, 
        azt�n lefuttatja a destruktor�t, majd lebontja a stack frame-et. 
      Ut�na ezt a c�met (ami m�r hivatalosan "sehova" mutat, de a val�s�gban m�g ott van a stacken az �rt�k), 
        �tadja a feldolgoznak, aki, mik�zben l�trehozza a saj�t stack frame-j�t, fel�l�rja az adatot
    
    Sz�val ez egy sz�p p�lda arra, hogy lehet olyan adattal is dolgozni, ami nincs is ott.
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
    int* masik; // ezt egy eg�sz v�ltoz�val is ki lehetne v�ltani, de �tl�that� t�le a k�d �s k�nny� ellen�rizni ki�r�skor.
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