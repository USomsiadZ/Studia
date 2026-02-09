#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>

#define CREW_SIZE 6
#define SENSOR_COUNT 20

struct CrewMember {
    char role[32];
    char name[32];
};
int loadCrew(const char *path, struct CrewMember crew[], int maxCount);
void printCrew(const struct CrewMember crew[], int count);
void generateSensorFile(const char *path);
int computeAmplitude(const int *data, int count);
int* loadSensorLogs(const char *path, int *outCount);
int* filterLogs(const int *data, int count, int threshold, int *outCount);
void saveReport(const char *path, const struct CrewMember crew[],
                int crewCount, int amplitude);
void saveFilteredBinary(const char *path, const int *data, int count);

int main(int argc, char *argv[]) {

    /* 1. Walidacja: nazwa pliku załogi musi być podana */
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <crew_file>\n", argv[0]);
        return 1;
    }

    const char *crewPath = argv[1];

    /* 2. Wczytanie załogi */
    struct CrewMember crew[CREW_SIZE];
    int loadedCrew = loadCrew(crewPath, crew, CREW_SIZE);

    if (loadedCrew <= 0) {
        fprintf(stderr, "Error: crew file invalid or empty.\n");
        return 1;
    }

    printCrew(crew, loadedCrew);


    /* 3. Generowanie sensor.bin, jeśli brak */
    generateSensorFile("sensor.bin");


    /* 4. Wczytanie logów sensorów */
    int count = 0;
    int *logs = loadSensorLogs("sensor.bin", &count);

    printf("Captain Kirk: \"Mr. Spock, please analyze the sensor readings.\"\n");
    printf("Spock: \"Acknowledged, Captain. Beginning analysis.\"\n\n");

    if (!logs) return 1;


    /* 5. Analiza: amplituda */
    int amplitude = computeAmplitude(logs, count);
    printf("Spock: \"Sensor amplitude is %d units.\"\n", amplitude);


    /* 6. Filtrowanie odczytów > 50 */
    int filteredCount = 0;
    int *filtered = filterLogs(logs, count, 50, &filteredCount);

    printf("Spock: \"%d significant readings above threshold.\"\n\n",
           filteredCount);


    /* 7. Zapis raportu */
    saveReport("report.txt", crew, loadedCrew, amplitude);
    printf("[INFO] report.txt saved.\n");


    /* 8. Zapis przefiltrowanych odczytów */
    saveFilteredBinary("filtered.bin", filtered, filteredCount);
    printf("[INFO] filtered.bin saved (%d records).\n\n",
           filteredCount);


    /* 9. Sprzątanie */
    free(logs);
    free(filtered);

    printf("Spock: \"Analysis complete, Captain. Report delivered.\".\n");

    return 0;
}
int loadCrew(const char *path, struct CrewMember crew[], int maxCount) {
    FILE *f = fopen(path, "r");
    if (!f) {
        perror("Error opening crew file");
        return -1;
    }

    char line[128];
    int count = 0;

    while (fgets(line, sizeof(line), f) != NULL && count < maxCount) {
        line[strcspn(line, "\n")] = '\0';  // usuń \n

        char *role = strtok(line, ":");
        char *name = strtok(NULL, ":");

        if (role && name) {
            strncpy(crew[count].role, role, sizeof(crew[count].role));
            strncpy(crew[count].name, name, sizeof(crew[count].name));
            count++;
        }
    }

    fclose(f);
    return count;
}

//   Wypisywanie załogi
void printCrew(const struct CrewMember crew[], int count) {
    printf("=== USS Enterprise Crew on Duty ===\n");
    for (int i = 0; i < count; i++) {
        printf("%s %s reporting for duty.\n",
               crew[i].role,
               crew[i].name);
    }
    printf("\n");
}
//   Generowanie sensor.bin, jeśli brak
void generateSensorFile(const char *path) {
    FILE *f = fopen(path, "rb");
    if (f) {
        fclose(f);
        return; // Plik istnieje
    }

    printf("[INFO] sensor.bin not found — generating new sensor logs...\n");

    f = fopen(path, "wb");
    if (!f) {
        perror("Error creating sensor.bin");
        exit(1);
    }

    srand((unsigned)time(NULL));
    int data[SENSOR_COUNT];

    for (int i = 0; i < SENSOR_COUNT; i++) {
        data[i] = rand() % 101; // 0-100
    }

    fwrite(data, sizeof(int), SENSOR_COUNT, f);
    fclose(f);

    printf("[INFO] sensor.bin generated.\n\n");
}
//   Wczytywanie danych binarnych
int* loadSensorLogs(const char *path, int *outCount) {
    FILE *f = fopen(path, "rb");
    if (!f) {
        perror("Error opening sensor.bin");
        return NULL;
    }

    int *data = malloc(sizeof(int) * SENSOR_COUNT);
    if (!data) {
        perror("Memory allocation error");
        fclose(f);
        return NULL;
    }

    size_t read = fread(data, sizeof(int), SENSOR_COUNT, f);
    fclose(f);

    if (read != SENSOR_COUNT) {
        fprintf(stderr, "Error: expected %d readings, got %zu\n",
                SENSOR_COUNT, read);
        free(data);
        return NULL;
    }

    *outCount = SENSOR_COUNT;
    return data;
}
//Obliczanie amplitudy
int computeAmplitude(const int *data, int count) {
    int min = data[0];
    int max = data[0];

    for (int i = 1; i < count; i++) {
        if (data[i] < min) min = data[i];
        if (data[i] > max) max = data[i];
    }
    return max - min;
}
//Filtrowanie logów — odczyty > threshold
int* filterLogs(const int *data, int count, int threshold, int *outCount) {
    int *filtered = malloc(sizeof(int) * count);
    if (!filtered) return NULL;

    int k = 0;
    for (int i = 0; i < count; i++) {
        if (data[i] > threshold) {
            filtered[k++] = data[i];
        }
    }

    *outCount = k;
    return filtered;
}
void saveReport(const char *path, const struct CrewMember crew[],
                int crewCount, int amplitude) 
{
    FILE *f = fopen(path, "w");
    if (!f) {
        perror("Error writing report.txt");
        return;
    }

    fprintf(f, "Starfleet Sensor Report\n");
    fprintf(f, "-----------------------\n\n");

    fprintf(f, "Crew on duty:\n");
    for (int i = 0; i < crewCount; i++) {
        fprintf(f, "- %s (%s)\n", crew[i].name, crew[i].role);
    }

    fprintf(f, "\nSensor amplitude: %d units\n", amplitude);

    if (amplitude < 20)
        fprintf(f, "Status: All systems within normal parameters.\n");
    else if (amplitude < 50)
        fprintf(f, "Status: Moderate fluctuations detected.\n");
    else
        fprintf(f, "Status: Significant anomalies present.\n");

    fclose(f);
}
void saveFilteredBinary(const char *path, const int *data, int count) {
    FILE *f = fopen(path, "wb");
    if (!f) {
        perror("Error writing filtered.bin");
        return;
    }

    fwrite(data, sizeof(int), count, f);
    fclose(f);
}















