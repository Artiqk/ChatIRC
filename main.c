#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define FILENAME "messageTemp.data"

int main () {
    FILE *output = fopen(FILENAME, "w");

    time_t rawTime;
    struct tm *timeInfo;

    time(&rawTime);

    timeInfo = localtime(&rawTime);

    int hours = timeInfo->tm_hour;
    int minutes = timeInfo->tm_min;
    int seconds = timeInfo->tm_sec;

    if (output == NULL) {
        printf("Error opening file.");
        exit(EXIT_FAILURE);
    }

    fprintf(output, "[%d:%d:%d] Hello World!", hours, minutes, seconds);

    return 0;
}