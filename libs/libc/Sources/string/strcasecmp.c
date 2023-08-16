/**
  * @file
  *
  * @brief Case insensitive string compare
  *
  * This converts each character to lowercase before comparing.
  */
#include <string.h>
#include <ctype.h>

int strcasecmp (const char *s1, const char *s2) {
    int diff = 0;

    while(1) {
        const int c1 = tolower(*s1++);
        const int c2 = tolower(*s2++);
        if(((diff = c1 - c2) != 0) || (c2 == '\0')) {
            break;
        }
    }
    return diff;
}

int strncasecmp(const char *s1, const char *s2, size_t n) {
  int diff = 0;
  for( ; n != 0; n--) {
        const int c1 = tolower(*s1++);
        const int c2 = tolower(*s2++);
        if (((diff = c1 - c2) != 0) || (c2 == '\0')) {
            break;
        }
    }

    return diff;
}
