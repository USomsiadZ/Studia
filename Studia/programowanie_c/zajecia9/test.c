#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Definicja struktury punktu
typedef struct {
    double x; // Długość
    double y; // Szerokość
} Point;

// --- FUNKCJA 1: Weryfikacja pliku ---
// Zwraca ilość par (punktów) lub -1, jeśli plik jest błędny
long validate_file(const char* filename) {
    FILE* f = fopen(filename, "r");
    if (!f) {
        printf("Błąd: Nie można otworzyć pliku %s\n", filename);
        return -1;
    }

    double temp;
    long count = 0;
    int read_status;

    // Pętla czyta liczby jedna po drugiej
    while ((read_status = fscanf(f, "%lf", &temp)) != EOF) {
        if (read_status == 0) {
            // fscanf zwrócił 0, co znaczy, że napotkał znak niebędący liczbą
            printf("Błąd: Plik zawiera niedozwolone znaki (nie liczby).\n");
            fclose(f);
            return -1;
        }
        count++;
    }

    fclose(f);

    if (count % 2 != 0) {
        printf("Błąd: Liczba wartości w pliku jest nieparzysta (%ld). Nie można utworzyć par.\n", count);
        return -1;
    }

    return count / 2; // Zwracamy liczbę PAR (punktów)
}

// --- FUNKCJA 2: Wczytywanie danych ---
Point* load_coordinates(const char* filename, long count) {
    FILE* f = fopen(filename, "r");
    if (!f) return NULL;

    // Alokacja pamięci dynamicznej
    Point* points = (Point*)malloc(count * sizeof(Point));
    if (!points) {
        printf("Błąd: Nie udało się przydzielić pamięci.\n");
        fclose(f);
        return NULL;
    }

    for (long i = 0; i < count; i++) {
        fscanf(f, "%lf %lf", &points[i].x, &points[i].y);
    }

    fclose(f);
    return points;
}

// --- FUNKCJA 3: Obliczanie odległości ---
double calculate_distance(Point p1, Point p2) {
    return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
}

// --- FUNKCJA 4: Filtrowanie punktów ---
// Modyfikuje tablicę "in-place" i zwraca nowy rozmiar
long filter_points(Point* points, long count, Point ship_pos, double radius) {
    long new_count = 0;

    for (long i = 0; i < count; i++) {
        double dist = calculate_distance(ship_pos, points[i]);
        
        // Jeśli punkt jest w zasięgu
        if (dist <= radius) {
            // Przepisujemy go na pozycję 'new_count' (kompresja tablicy)
            points[new_count] = points[i];
            new_count++;
        }
    }
    
    // Opcjonalnie: można użyć realloc, aby zmniejszyć fizycznie tablicę, 
    // ale dla wydajności często wystarczy po prostu pamiętać nowy rozmiar.
    return new_count;
}

// --- FUNKCJA 5: Zapis binarny ---
void save_binary(const char* filename, Point* points, long count) {
    FILE* f = fopen(filename, "wb"); // "wb" - write binary
    if (!f) {
        printf("Błąd: Nie można utworzyć pliku wyjściowego.\n");
        return;
    }

    // Zapisujemy całą tablicę jednym rzutem
    size_t written = fwrite(points, sizeof(Point), count, f);
    
    if (written == count) {
        printf("Sukces: Zapisano %ld punktów do pliku %s.\n", count, filename);
    } else {
        printf("Błąd zapisu danych.\n");
    }

    fclose(f);
}

// --- GŁÓWNA FUNKCJA (Orchestrator) ---
int main() {
    const char* INPUT_FILE = "coordinates.txt";
    const char* OUTPUT_FILE = "valid_targets.bin";
    
    // 1. Walidacja
    printf("--- KROK 1: Weryfikacja danych ---\n");
    long point_count = validate_file(INPUT_FILE);
    
    if (point_count <= 0) {
        return 1; // Koniec programu w przypadku błędu
    }
    printf("Plik poprawny. Znaleziono %ld punktów.\n", point_count);

    // 2. Wczytanie do pamięci
    printf("\n--- KROK 2: Wczytywanie do pamieci ---\n");
    Point* galaxy_map = load_coordinates(INPUT_FILE, point_count);
    if (!galaxy_map) return 2;

    // Wyświetlenie wczytanych danych (dla użytkownika)
    printf("Wczytane wspolrzedne:\n");
    for(long i=0; i<point_count; i++) {
        printf("[%ld] X: %.2f, Y: %.2f\n", i+1, galaxy_map[i].x, galaxy_map[i].y);
    }

    // 3. Pobranie danych od kapitana
    Point ship_pos;
    double radar_radius;
    
    printf("\n--- KROK 3: Panel Sterowania Oriona ---\n");
    printf("Podaj biezaca pozycje statku (X Y): ");
    if (scanf("%lf %lf", &ship_pos.x, &ship_pos.y) != 2) {
        printf("Błędne dane wejściowe.\n");
        free(galaxy_map);
        return 3;
    }
    
    printf("Podaj promien radaru: ");
    if (scanf("%lf", &radar_radius) != 1) {
        printf("Błędne dane wejściowe.\n");
        free(galaxy_map);
        return 3;
    }

    // 4. Filtrowanie
    printf("\n--- KROK 4: Filtrowanie celow ---\n");
    long visible_count = filter_points(galaxy_map, point_count, ship_pos, radar_radius);
    printf("Liczba punktow w zasiegu: %ld (odrzucono %ld)\n", visible_count, point_count - visible_count);

    // Wyświetlenie po filtracji
    for(long i=0; i<visible_count; i++) {
         double dist = calculate_distance(ship_pos, galaxy_map[i]);
         printf("Cel [%ld]: X: %.2f, Y: %.2f (Odleglosc: %.2f)\n", i+1, galaxy_map[i].x, galaxy_map[i].y, dist);
    }

    // 5. Zapis binarny
    if (visible_count > 0) {
        printf("\n--- KROK 5: Archiwizacja danych ---\n");
        save_binary(OUTPUT_FILE, galaxy_map, visible_count);
    } else {
        printf("\nBrak punktow do zapisania.\n");
    }

    // 6. Sprzątanie
    free(galaxy_map);
    printf("\nOperacja zakonczona.\n");

    return 0;
}