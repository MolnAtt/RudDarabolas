#include <iostream>
#include <string>
#include <queue>
using namespace std;

// Fõbb összetett típusdeklarációk

struct Input
{
    static const int max_N = 1000;
    static const int min_N = 1;
    static const int max_T_i = 1000;
    static const int min_T_i = 1;
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

Input Beolvas();
Output Feldolgoz(const Input&);
void Kiir(const Output&);

// segédfüggvények
int Int_bekerese(string, int, int);


int main()
{
    Kiir(Feldolgoz(Beolvas()));
}

Input Beolvas()
{
    Input be;

    be.N = Int_bekerese("Adja meg a vagando darabok szamat!", Input::min_N, Input::max_N);

    for (int i = 0; i < be.N; i++)
    {
        be.T[i] = Int_bekerese("  Adja meg a(z) " + to_string(i + 1) + ". darab hosszat!", Input::min_T_i, Input::max_T_i);
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
    cerr << "Az osszkoltseg: ";
    cout << ki.koltseg << endl;
    for (int i = 0; i < ki.N; i++)
    {
        cerr << "a(z) " << i+1<<". lepesben kettevagando rud hossza ";
        cout << ki.egesz[i] << " ";
        cerr << ", \n    az igy keletkezo (kisebbik) rud hossza ";
        cout << ki.egyik[i];
        cerr << ", \n    a masik rud hossza pedig " << ki.masik[i] << endl; // ellenõrzéshez
        cout << endl;
    }
}



// segédfüggvények:

int Int_bekerese(string keres, int a, int f)
{
    string nyers;
    int result;
    cout << keres;
    cout << " (" << a << " <= X <= " << f << "): ";

    bool szame = false;
    bool jo = false;

    do
    {
        cin >> nyers;

        try
        {
            result = stoi(nyers);
            szame = true;
        }
        catch (...)
        {
            cout << " HIBA! Nem egesz szamot adott meg. Probalkozzon ujra!\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            szame = false;
        }

        if (szame)
        {
            if (result < a)
                cout << " HIBA! Tul kicsi szamot adott meg. Probalkozzon ujra!\n";
            else if (result > f)
                cout << " HIBA! Tul nagy szamot adott meg. Probalkozzon ujra!\n";
            else jo = true;
        }
    } 	while (!jo);
    return result;
}