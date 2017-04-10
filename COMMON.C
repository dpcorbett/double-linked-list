#include <stdio.h>
#include <stdlib.h>
// stderr uses stdout to display warnings during runtime.
void Warning(char *message) {
    fprintf(stderr,"%s\n",message);
}
// stderr uses stdout to display errors during runtime.
void Error(char *message) {
    fprintf(stderr,"%s\n",message);
    exit(EXIT_FAILURE);
}