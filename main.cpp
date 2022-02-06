#include <iostream>
#include "TSP.hpp"
#include "Genetic.hpp"

int main(int argc, char const *argv[])
{
    TSP tsp;
    uint8_t selected = -1;
    int stopCriteria = 1000;
    int populationSize = 100;
    double mutationFactor = 0.01;
    double crossFactor = 0.8;
    int crossMethodVariant = 1;
    int mutationMethodVariant = 2;
    string filename;
    bool dataLoaded = false;
    
    while (selected != '0')
    {
        cout << '\a';

        cout << "\n\nPEA Projekt - Tobiasz Puślecki 241354" << endl;
        cout << "1.Wczytanie danych z pliku i wyświetlenie" << endl;
        cout << "2.Kryterium stopu" << endl;
        cout << "3.Ustawienie wielkości populacji początkowej" << endl;
        cout << "4.Ustawienie współczynnika mutacji" << endl;
        cout << "5.Ustawienie współczynnika krzyżowania" << endl;
        cout << "6.Wybór metody krzyżowania" << endl;
        cout << "7.Wybór metody mutacji" << endl;
        cout << "8.Uruchomienie algorytmu genetycznego" << endl;
        cout << "0. Wyjście" << endl;
        cout << ">>> ";
        cin >> selected;
        
        if(selected == '1')
        {
            cout << "Podaj nazwę pliku: ";
            cin >> filename;
            
            TSP tsp_(filename);
            tsp = tsp_;
            dataLoaded = true;
            
            if(dataLoaded)
                tsp.printMatrix();
            else
                cout << "Nie wczytano/wylosowano danych!\n";
            
        }
        else if (selected == '2')
        {
            int stopCriteria_;
            cout << "Podaj kryterium stopu w sekundach (>0)\n";
            cin >> stopCriteria_;
            if (stopCriteria_ > 0 and stopCriteria_ < INT_MAX)
            {
                stopCriteria = stopCriteria_;
            }
            else
            {
                cout << "Niepoprawne dane ! \n";
            }
        }
        else if (selected == '3')
        {
            int populationSize_;
            cout << "Podaj wielkość populacji początkowej (>0)\n";
            cin >> populationSize_;
            if (populationSize_ > 0 and populationSize_ < INT_MAX)
            {
                populationSize = populationSize_;
            }
            else
            {
                cout << "Niepoprawne dane ! \n";
            }
        }
        else if (selected == '4')
        {
            double mutationFactor_;
            cout << "Podaj współczynnik mutacji (0:1)\n";
            cin >> mutationFactor_;
            if (mutationFactor_ > 0 and mutationFactor_ < 1)
            {
                mutationFactor = mutationFactor_;
            }
            else
            {
                cout << "Niepoprawne dane ! \n";
            }
        }
        else if (selected == '5')
        {
            double crossFactor_;
            cout << "Podaj współczynnik krzyżowania (0;1)\n";
            cin >> crossFactor_;
            if (crossFactor_ > 0 and crossFactor_ < 1)
            {
                crossFactor = crossFactor_;
            }
            else
            {
                cout << "Niepoprawne dane ! \n";
            }
        }
        else if (selected == '6')
        {
            int crossMethodVariant_;
            cout << "Wybierz metodę krzyżowania (1 lub 2)\n";
            cin >> crossMethodVariant_;
            if (crossMethodVariant_ > 0 and crossMethodVariant_ < 3)
            {
                crossMethodVariant = crossMethodVariant_;
            }
            else
            {
                cout << "Niepoprawne dane ! \n";
            }
        }
        else if (selected == '7')
        {
            int mutationMethodVariant_;
            cout << "Wybierz metodę mutacji (1 lub 2)\n";
            cin >> mutationMethodVariant_;
            if (mutationMethodVariant_ > 0 and mutationMethodVariant_ < 3)
            {
                mutationMethodVariant = mutationMethodVariant_;
            }
            else
            {
                cout << "Niepoprawne dane ! \n";
            }
        }
        else if (selected == '8')
        {
            if(dataLoaded)
            {
                Genetic genetic(tsp.getMatrix());
                cout << fixed << endl;
                cout << "Genetic| path: " << genetic.calculate(stopCriteria, populationSize, mutationFactor, crossFactor, crossMethodVariant, mutationMethodVariant) << "  in time:  " << genetic.getExecutionTime() << "\n\n\n";
                
//                cout << "\nMutationFactor: " << stopCriteria;
//                cout << "\npopulationSize: " << populationSize;
//                cout << "\nmutationFactor: " << mutationFactor;
//                cout << "\ncrossFactor: " << crossFactor;
//                cout << "\ncrossMethodVariant: " << crossMethodVariant;
//                cout << "\nmutationMethodVariant: " << mutationMethodVariant;
                
            }
            else
            {
                cout << "Nie wczytano/wylosowano danych!\n";
            }
        }
    }
  return 0;
}
