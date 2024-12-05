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
  "Type Check Error",
  "InterCode Generator Error",
  "none"
};

void _error_print(ErrorType error, const char* msg, const char* file, uint32_t line, int32_t column) {
  if (column == -1) {
    fprintf(
      stderr, "%s[FATAL]: %s, %s%s%s at %u, in %s%s\n",
      colors[RED], _error_msg[error],
      colors[UNDERLINE], msg, colors[RESET],
      line, file, colors[RESET]
    );
    return;
  }
  fprintf(
    stderr, "%s[FATAL]: %s, %s%s%s at %u-%d, in %s%s\n",
    colors[RED], _error_msg[error],
    colors[UNDERLINE], msg, colors[RESET],
    line, column, file, colors[RESET]
  );
}

void _error_assert(ErrorType error, const char* msg, const char* file, uint32_t line) {
  _error_print(error, msg, file, line, -1);
  exit(error);
}

const char* colors[] = {
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


