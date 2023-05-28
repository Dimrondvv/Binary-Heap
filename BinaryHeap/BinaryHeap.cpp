
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <time.h>
#include <cstdlib>

using namespace std;

template <typename T>

class Kopiec {
public:
    //Konstruktor i destruktor 
    Kopiec() {
        //k.resize(1);
        rozmiar = 0;
    };
    ~Kopiec() {
        usun();
    };

    //Dodawanie z kopcowaniem w gore
    void Dodawanie(T dane) {
        rozmiar++;
        k.push_back(dane);
        kopcowanieGora(k.size() - 1);
    }

    //pokzywanie z indeksami odrazu wiadomo o co chodzi 
    void pokaz() {
        cout << "Rozmiar: " << k.size() << endl;
        

        if (k.size() > 10) {
            for (int i = 0; i < 10; i++)
            {
                if (i == 0) {
                    cout << "Rodzic : NULL" << "\t" << "Indeks: " << i << "\n";
                }
                else
                {
                    cout << "Rodzic : " << (i - 1) / 2 << "\t" << "Indeks: " << i << "\n";
                }

            }
        }
        
        
        
        /*
            int in = 1
            for (auto i : k) {
            in++;
            cout << "Rodzic: " << (in - 1) / 2 << "\t";
            cout << i << "\n";
        }*/
    }

    // Usuwanie maxymalnej wartosci w tym wypadku root'a
    T usunMax(){
        if (k[0])
        {
            auto tmp = k.back();
            k[0] = k.back();

            k.pop_back();

            kopcowanieDol(0);
            return tmp;
        }
        else
        {
            return NULL;
        }
           
    }

    // Usuniecie calego Kopca
    void usun() {
        k.erase(k.begin(), k.end());
    }

private:
    // Kopcoanie w gore prywatne zeby inni nie mogli odstac (rekurencja)
    void kopcowanieGora(int indeks) {
        if (indeks != 0) {
            int rIndeks = (indeks - 1)/2;
            
            if (k[indeks] >= k[rIndeks]) {
                swap(k[rIndeks], k[indeks]);
                kopcowanieGora(rIndeks);
            } 
        }
    }

    // Kopcowanie w dol ale byla maskara
    void kopcowanieDol(int indeks) {
        int max = indeks; // max indeks jaki jest
        int lDziecko = 2 * indeks + 1; // lewe dziecko
        int pDziecko = 2 * indeks + 2; // prawe dziecko
        
        if (lDziecko < k.size() && k[lDziecko] > k[indeks]) { // Sprwadzamy czyl lewe dziecko jest mniejsze od rozmiaru i wartosc lewego dziecka wieksza od indeksu
            max = lDziecko; // no jesli wszystko sie zgadza max wtedy jest lewym dzieckiem
        }

        if (pDziecko < k.size() && k[pDziecko] > k[max]) // Sprwadzamy czy prawe dziecko jest mniejsze od rozmiaru i czy wartosc prawego dziecka jest wieksza od wartosci max
        {
            max = pDziecko; // jesli jset wieksza max wtedy staje sie prawym dzieckiem
        }
        
        if (max != indeks) { // max rozny od indeksu 
            swap(k[indeks], k[max]); // zamieniamy ter wartosci wkocu
            kopcowanieDol(max); // leci rekurencja
        }
        
        
    }



    vector<T> k;
    T dane;
    int rozmiar;
};

int main()
{
    Kopiec<int> k;
 
    const int Max_order = 7;

    for (int i = 0; i <= Max_order; i++)
    {
        const int n = pow(10, i);

        clock_t start = clock();
        // Dodawanie Kopiec binarny
        for (int x = 0; x < n; x++)
        {
            srand(time(NULL));
            int liczba = rand() % 100000 + 1;
            k.Dodawanie(liczba);
        }
        clock_t stop = clock();

        k.pokaz();

        double czas_dla_elementu = ((stop - start) / (double)CLOCKS_PER_SEC) /*/ wielkosc*/;
        cout << "===========================================================\n";
        cout << "Dla n elementow " << n << "\n Dodawanie : \n";
        cout << "Czas calokowity: " << czas_dla_elementu << "\n";
        cout << "Czas sredni: " << czas_dla_elementu / n << "\n";

        start = clock();
        // Usuwanie Max Kopiec binarny
        cout << "_____________________________________________________________\n";
        cout << "Usuwanie Max: \n";
        for (int x = 0; x < n; x++)
        {
            k.usunMax();
        }
         stop = clock();

         czas_dla_elementu = ((stop - start) / (double)CLOCKS_PER_SEC) /*/ wielkosc*/;
         cout << "Dla n elementow " << n << "\n Dodawanie : \n";
         cout << "Czas calokowity: " << czas_dla_elementu << "\n";
         cout << "Czas sredni: " << czas_dla_elementu / n << "\n";

         k.usun();
    }
}


