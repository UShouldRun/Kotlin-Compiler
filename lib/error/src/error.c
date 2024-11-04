#include "error.h"

#define SIZEOF_ENUM(e) (int)(e##_end - e##_start + 1)
#define ERROR_SIZE SIZEOF_ENUM(error)

static const char* _error_msg[ERROR_SIZE] = {
  "nil",
  "nullptr",
  "Memory Error",
  "Invalid Argument",
  "Unexpected",
  "IO Error",
  "Parser Error",
  "none"
};

static const char* _error_color[] = {
  "\033[0m",  // Reset
  "\033[30m", // Black
  "\033[31m", // Red
  "\033[32m", // Green
  "\033[33m", // Yellow
  "\033[34m", // Blue
  "\033[35m", // Magenta
  "\033[36m", // Cyan
  "\033[37m", // White
  "\033[1m",  // Bold
  "\033[4m",  // Underline
  "\033[7m",  // Reversed
  "\033[90m", // Bright Black (Gray)
  "\033[91m", // Bright Red
  "\033[92m", // Bright Green
  "\033[93m", // Bright Yellow
  "\033[94m", // Bright Blue
  "\033[95m", // Bright Magenta
  "\033[96m", // Bright Cyan
  "\033[97m", // Bright White
  "\033[40m", // Background Black
  "\033[41m", // Background Red
  "\033[42m", // Background Green
  "\033[43m", // Background Yellow
  "\033[44m", // Background Blue
  "\033[45m", // Background Magenta
  "\033[46m", // Background Cyan
  "\033[47m", // Background White
};

#define RESET 0
#define BLACK 1
#define RED 2
#define GREEN 3
#define YELLOW 4
#define BLUE 5
#define MAGENTA 6
#define CYAN 7
#define WHITE 8
#define BOLD 9
#define UNDERLINE 10
#define REVERSED 11
#define BRIGHT_BLACK 12
#define BRIGHT_RED 13
#define BRIGHT_GREEN 14
#define BRIGHT_YELLOW 15
#define BRIGHT_BLUE 16
#define BRIGHT_MAGENTA 17
#define BRIGHT_CYAN 18
#define BRIGHT_WHITE 19
#define BG_BLACK 20
#define BG_RED 21
#define BG_GREEN 22
#define BG_YELLOW 23
#define BG_BLUE 24
#define BG_MAGENTA 25
#define BG_CYAN 26
#define BG_WHITE 27

void _error_assert(ErrorType error, const char* msg, const char* file, uint32_t line) {
  fprintf(
    stderr, "%s[FATAL]: %s, %s%s%s at %u, in %s%s\n",
    _error_color[RED], _error_msg[error],
    _error_color[UNDERLINE], msg, _error_color[RESET],
    line, file, _error_color[RESET]
  );
  exit(error);
}
