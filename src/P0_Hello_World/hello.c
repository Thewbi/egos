/* Uncomment this code block
 * when implementing formatted output
 */
/**/
#include <string.h>  // for strlen() and strcat()
#include <stdlib.h>  // for itoa()
#include <stdarg.h>  // for va_start(), va_end() and va_arg()

// https://www.ijs.si/software/snprintf/
#include "snprintf.h"

void terminal_write(const char *str, int len) {
    for (int i = 0; i < len; i++) {
        *(char*)(0x10000000) = str[i];
    }
}

void format_to_str(char* out, const char* fmt, va_list args) {
    for(out[0] = 0; *fmt != '\0'; fmt++) {
        if (*fmt != '%') {
            strncat(out, fmt, 1);
        } else {
            fmt++;
            if (*fmt == 's') {
                strcat(out, va_arg(args, char*));
            } else if (*fmt == 'd') {
                itoa(va_arg(args, int), out + strlen(out), 10);
            }
        }
    }
}

int format_to_str_len(const char* fmt, va_list args) {
	// https://cboard.cprogramming.com/c-programming/136741-how-find-out-length-printf-before-its-printed.html
	// C99 compliant snprintf will accept NULL as buffer. and return the number of characters that would have been written.
	//
	// https://stackoverflow.com/questions/514870/is-there-any-way-to-determine-how-many-characters-will-be-written-by-sprintf
	// What this means is that you can call snprintf with a size of 0. Nothing will get written, and the return value will tell 
	// you how much space you need to allocate to your string:
	return snprintf(NULL, 0, fmt, args);
}

/*
int printf(const char* format, ...) {
    char buf[512];
    va_list args;
    va_start(args, format);
    format_to_str(buf, format, args);
    va_end(args);
    terminal_write(buf, strlen(buf));

    return 0;
}
*/

// from https://egos.fun/book/p0_hello.html
int printf(const char* format, ...) {	
    va_list args;	
    va_start(args, format);
    unsigned int len = format_to_str_len(format, args);
    char *buf = malloc(len);
    format_to_str(buf, format, args);
    va_end(args);
    terminal_write(buf, strlen(buf));
    free(buf);	

    return 0;
}

/* Uncomment this code block
 * when implementing dynamic memory allocation
 */
/**/
extern char __heap_start, __heap_end;
static char* brk = &__heap_start;
char* _sbrk(int size) {
    if (brk + size > (char*)&__heap_end) {
        terminal_write("_sbrk: heap grows too large\r\n", 29);
        return NULL;
    }

    char* old_brk = brk;
    brk += size;
    return old_brk;
}

#define printf my_printf
int INFO(const char* format, ...);
int FATAL(const char* format, ...);
int SUCCESS(const char* format, ...);
int CRITICAL(const char* format, ...);
int my_printf(const char* format, ...);

/*
#define LOG(prefix, suffix)                                                    \
    char buf[512];                                                             \
    strcpy(buf, prefix);                                                       \
    va_list args;                                                              \
    va_start(args, format);                                                    \
    format_to_str(buf + strlen(prefix), format, args);                         \
    va_end(args);                                                              \
    strcat(buf, suffix);                                                       \
    term_write(buf, strlen(buf));
*/

#define LOG(prefix, suffix)                                                    \
	char buf[512];                                                             \
    va_list args;                                                              \
    va_start(args, format);                                                    \
    format_to_str(buf, format, args);                                          \
    va_end(args);                                                              \
    terminal_write(buf, strlen(buf));                                          

int my_printf(const char* format, ...) { LOG("", ""); }

int INFO(const char* format, ...) { LOG("[INFO] ", "\n\r") }

int FATAL(const char* format, ...) {
    LOG("\x1B[1;31m[FATAL] ", "\x1B[1;0m\n\r") // \x1B[1;31m means red.
    while (1);
}

int SUCCESS(const char* format, ...) {
    LOG("\x1B[1;32m[SUCCESS] ", "\x1B[1;0m\n\r") // \x1B[1;32m means green.
}

int CRITICAL(const char* format, ...) {
    LOG("\x1B[1;33m[CRITICAL] ", "\x1B[1;0m\n\r") // \x1B[1;33m means yellow.
}


int main() {
    char* msg = "Hello, World!\n\r";
    terminal_write(msg, 15);

    /* Uncomment this line of code
     * when implementing formatted output
     */
    /**/ printf("%s-%d is awesome!", "egos", 2000); 

    return 0;
}
