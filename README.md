# Idea projektu
Kod przeprowadzajacy symulacje perkolacji macierzowej w C i Pythonie.
## Konwencja adresowania tablicy
W kodzie dla osobistej wygody przyjąłem konwnecje adresowania tylko 1-ną zmienną "__i__".
Aby uzyskać standardowe adresowanie w układzie kartezjańskim w macierzy przyjąłem transformatę $(x,y)$--->$(i\%n,i/n)$ gdzie $n$ to długość/szerkość macierzy. W takim układzie odpada mi pare problemów z poprawnym nazewnictwem komórek i warunków klastrów. 
# Mechanizm projektu
W projekcie tworzę macierz __NxN__ (rozmiar zadany przez urzytkownika) który następnie wypełniam
jedynkami dla pełnej komórki (prawdopodobieństwo wypełnienia zadane przez urzytkownika) oraz zerami puste komórki. Nastepnie przechodząc po macierzy za pomocą wyznaczonych wcześniej warunków sprawdzam, czy i jak licznie występuja w macierzy klastry o numerach od 2 do $\frac{n^2}{2}$ (_to najgorszy przypadek kiedy tablica jest wypełniona w sposób szachownicy i każda komórka jes wtedy swoim klastrem_) 
Potem sprawdzana jest macierz zamian, jednowymiarowa lista trzymajaca indeksy klastrów niepoprawnie zaadresowanych. Przechodzimy jeszcze raz po tablicy zmieniając indeksy istniejące w macierzy zmian i mamy poprawnie nazwane kalstry w naszej macierzy.
Na końcu badam, czy którykolwiek klaster ma elementy na skrajnych "ścianach tablllicy". Jeżeli jedne lub więcej klastrów spełnia ten warunek, są to klastry perkolujące. 