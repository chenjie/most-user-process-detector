#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
    int filter_ppid = 0;
    if (argc == 2) {
        filter_ppid = strtol(argv[1], NULL, 10);
    } else if (argc > 2) {
        fprintf(stderr, "USAGE: most_processes [ppid]\n");
        exit(1);
    }

    char line[1024];
    char uid[32];
    char last_uid[32];

    int first = 1;
    int max = 0;
    char max_uid[32];
    int counter = 0;
    int ppid;
    while (fgets(line, 1024, stdin) != NULL) {
        if (sscanf(line, "%s %*d %d", uid, &ppid) == 2) {
            if (first != 1) {
                if (strcmp(last_uid, uid) != 0) {
                    if (counter > max) {
                        max = counter;
                        strcpy(max_uid, last_uid);
                    }
                    counter = 0;
                }
            }

            if (filter_ppid == 0) {
                counter += 1;
                strcpy(last_uid, uid);
                first = 0;
            } else {
                if (ppid == filter_ppid) {
                    counter += 1;
                    strcpy(last_uid, uid);
                    first = 0;
                }
            }
        }
    }
    if (counter > max) {
        max = counter;
        strcpy(max_uid, last_uid);
    }
    if (max != 0) {
        printf("%s %d\n", max_uid, max);
    }


    return 0;
}
