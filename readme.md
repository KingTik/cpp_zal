# Dzien dobry
W tym sktomnym repo znajdują się programy na zaliczenie zaawansowanego prgoramowania C++

## Co się udało zrobic ?
bieda unique_ptr -> custom_pointer.cpp
super bieda shared_ptr -> custom_pointer_with_cnt.cpp
macierze -> matrix.cpp
liczenie liczb pierwszych -> prime.cpp
ring buffer -> ring.cpp

## Rzeczy ktore warto dopowiedziec
### Generalnie o programach

Wszystkie programy ktore napisalem uruchamia sie bez zadnych parametrow. W main'ach za duzo nie ma bo tylko wpisywalem niektore bieda-testy lub wyswietlanie. 

### Macierze 

Zrobione na std::array poniewaz: czemu nie `¯\_(ツ)_/¯ `
Takie rozwiazanie ma swoje ograniczenia przy dzialaniu w runtime'ie ale za to 
jezyk robi za mnie duzo sprawdzania rozmiarow :D - jak dla mnie value

### Liczby pierwsze

Od razu zaznacze, ze nie pisałem algorytmow do sprawdzenia liczby pierwszej tylko gdzies znalazlem. W takim przypadku co zrobilem? Ugh. No generalnie pomysl byl taki zeby miec N watkow, kazdemu przekazac liczbe i niech sobie mieli.  W glownym watku sprawdzac czy juz skonczy. Jezeli skonczyl to dostanie kolejna liczbe do rozgryzienia. W ten sposob nie dziele danych na sztywne podgrupy i upewniam sie ze watki sa w miare mozliwosci rowno obdarowane praca.
