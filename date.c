#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>

#define ZONEINFO_DIR "/usr/share/zoneinfo/"

static void print_help(void) {
    puts("Usage: date_tool [TIME_ZONE]");
    puts("Display the current date and time.");
    puts("");
    puts("TIME_ZONE is an IANA time-zone name, such as America/New_York or Asia/Tokyo.");
    puts("Without TIME_ZONE, the system's local date and time are displayed.");
    puts("");
    puts("Options:");
    puts("  -h, --help  Show this help message and exit");
}

static int valid_zone_name(const char *name) {
    if (name[0] == '\0' || name[0] == '/') {
        return 0;
    }

    const char *component = name;
    for (const char *p = name; ; p++) {
        if (*p == '/' || *p == '\0') {
            size_t length = (size_t)(p - component);
            if (length == 0 ||
                (length == 1 && component[0] == '.') ||
                (length == 2 && component[0] == '.' && component[1] == '.')) {
                return 0;
            }
            if (*p == '\0') {
                break;
            }
            component = p + 1;
        } else if (!( (*p >= 'A' && *p <= 'Z') ||
                      (*p >= 'a' && *p <= 'z') ||
                      (*p >= '0' && *p <= '9') ||
                      *p == '_' || *p == '-' || *p == '+')) {
            return 0;
        }
    }

    return 1;
}

static int zone_exists(const char *name) {
    char path[512];
    int length = snprintf(path, sizeof(path), "%s%s", ZONEINFO_DIR, name);
    if (length < 0 || (size_t)length >= sizeof(path)) {
        return 0;
    }

    struct stat info;
    return stat(path, &info) == 0 && S_ISREG(info.st_mode);
}

int main(int argc, char *argv[]) {
    const char *zone = NULL;

    if (argc == 2 && (strcmp(argv[1], "-h") == 0 ||
                      strcmp(argv[1], "--help") == 0)) {
        print_help();
        return 0;
    }
    if (argc > 2) {
        fprintf(stderr, "Error: Too many arguments provided.\n");
        fprintf(stderr, "Try 'date_tool --help' for more information.\n");
        return 1;
    }
    if (argc == 2) {
        zone = argv[1];
        if (zone[0] == '-') {
            fprintf(stderr, "Error: Unknown option '%s'.\n", zone);
            fprintf(stderr, "Try 'date_tool --help' for more information.\n");
            return 1;
        }
        if (!valid_zone_name(zone) || !zone_exists(zone)) {
            fprintf(stderr, "Error: Unknown or invalid time zone '%s'.\n", zone);
            fprintf(stderr, "Use an IANA time-zone name, such as Asia/Tokyo.\n");
            return 1;
        }
        if (setenv("TZ", zone, 1) != 0) {
            perror("Error: Could not set the requested time zone");
            return 1;
        }
        tzset();
    }

    time_t now = time(NULL);
    if (now == (time_t)-1) {
        perror("Error: Could not read the current time");
        return 1;
    }

    struct tm current_time;
    if (localtime_r(&now, &current_time) == NULL) {
        perror("Error: Could not convert the current time");
        return 1;
    }

    char formatted[128];
    if (strftime(formatted, sizeof(formatted), "%A, %B %d, %Y %H:%M:%S %Z (%z)",
                 &current_time) == 0) {
        fprintf(stderr, "Error: Could not format the current date and time.\n");
        return 1;
    }

    puts(formatted);
    return 0;
}
