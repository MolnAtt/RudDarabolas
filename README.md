# Tanulságos bug: RudDarabolas

Ez a program nem működik, de nagyon tanulságos a hiba, hogy miért nem.

A MESTER-en is megtalálható rúddarabolás feladatról van szó, a feladat lényege igazából lényegtelen. A lényeg az, hogy a program három függvényből épül fel:
    
1. Beolvas: Beolvassa az adatokat és létrehozza az input struktúrát
2. Feldolgoz: Megkapja az input-struktúrát és csinál belőle egy Output-struktúrát
3. Kiír: Kiírja az adatokat.

Viszont nem működik. Step-by-step az lesz, hogy 
- Input létrejön, címet visszaadja, függvényen kívül is látszik, hogy léteznek ott az adatok, 
- Feldolgozba bemegy az input, ott is látni, hogy normálisak az adatok.
- De amint elkezd futni az Output konstruktora, megváltozik az input elemszáma. Más viszont érdekes módon nem.

Ez azért van, mert...
"Input egy lokális, azaz stacken lakó változó
Beolvas const&-el tér vissza, nincs se copy, se move, hanem a stacken lévő változó címet adja vissza, 
aztán lefuttatja a destruktorát, majd lebontja a stack frame-et. 
Utána ezt a címet (ami már hivatalosan "sehova" mutat, de a valóságban még ott van a stacken az érték), 
átadja a feldolgoznak, aki, miközben létrehozza a saját stack frame-jét, felülírja az adatot"
    
**Szóval ez egy szép példa arra, hogy lehet olyan adattal is dolgozni, ami nincs is ott.**

## A problémás függvények
```cpp
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
```