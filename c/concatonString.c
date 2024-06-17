#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *concatStrings(const char *str1, const char *str2) {
  // Calculate lengths of both strings
  size_t len1 = strlen(str1);
  size_t len2 = strlen(str2);

  // Allocate memory for the new string with enough space for both + null
  // terminator
  char *result = (char *)malloc(len1 + len2 + 1);
  if (!result) { // Check if malloc succeeded
    fprintf(stderr, "Memory allocation failed\n");
    // Instead of directly exiting, consider returning NULL or handling error
    // differently
    exit(EXIT_FAILURE);
  }

  // Copy str1 into result
  // To enhance security, use strncpy instead of strcpy, though in this specific
  // case it's safe since we control the source and know it's a valid
  // null-terminated string.
  strncpy(result, str1, len1 + 1); // Include null-terminator

  // Append str2 to result
  // Again, using strncpy for consistency and habit, though it's slightly less
  // efficient here.
  strncpy(result + len1, str2, len2 + 1); // Include null-terminator

  // Ensure the final string is properly null-terminated, in case source strings
  // were not. This is redundant in this specific example but good practice for
  // general use.
  result[len1 + len2] = '\0';

  return result;
}

int main() {
  const char *str1 = "Hello, ";
  const char *str2 = "World!";
  char *result = concatStrings(str1, str2);
  printf("%s\n", result); // Output: Hello, World!
  free(result);           // Don't forget to free allocated memory
  return 0;
}
