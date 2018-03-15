/**
 * The contents of this file are only a suggestion.
 * Feel free to change anything.
 */
#include <stdio.h>
#include "matcher.h"

/**
 * Returns true if partial_line matches pattern, starting from
 * the first char of partial_line.
 */
int matches_leading(char *partial_line, char *pattern) {
  int print = 0;
  // You can use this recommended helper function, or not.
  if (print == 1) {
    printf("  matches_leading new call ");
    printf("*partial_line: %s", partial_line);
    printf(" *pattern: %s", pattern);
    printf("\n");
  }
  if (*(pattern) == 0) {
    if (print == 1)
      printf("  matches_leading returned 1\n");
    return 1;
  }
  else {
    if (*(pattern) == '\\') {
      if (print == 1)
        printf("    matches_leading found a backslash!\n");
      return matches_leading((partial_line), (pattern + 1));
    }
    else if (*(pattern) == '.' && *(pattern - 1) != '\\') {
      if (*(pattern + 1) == '+') {    
        if (print == 1)
          printf("  matches_leading returned 1 due to \".+\"\n");
        return 1;
      }
      else {
        if (print == 1)
          printf("    matches_leading found a dot!\n");
        return matches_leading((partial_line + 1), (pattern + 1));
      }
    }
    else if (*(partial_line) == *(pattern)) { 
      if (print == 1)
        printf("    matches_leading found a matching non special symbol!\n");
      if (*(pattern + 1) == '?'  && *(pattern - 1) != '\\'){
        if (print == 1)
          printf("      matches_leading found a question mark!\n");
        return matches_leading((partial_line + 1), (pattern + 2)) || 
          matches_leading((partial_line), (pattern + 2));
      }      
      else if (*(pattern + 1) == '+' && *(pattern - 1) != '\\'){
        if (print == 1)
          printf("      matches_leading found a plus sign!\n");
        int index = 0;
        while (*(partial_line + 1 + index) == *(pattern)) {
          index++;
        }
        if (print == 1) {
          printf("      matches_leading index with plus sign is ");
          printf("%d", index);
          printf("\n");
        }
        return matches_leading((partial_line + index + 1), (pattern + 2));
      }
      else {
        if (print == 1)
          printf("      matches_leading found nothing!\n");
        return matches_leading((partial_line + 1), (pattern + 1));
      }
    }    
    else if (*(pattern + 1) == '?' && *(pattern - 1) != '\\') {
      if (print == 1)
        printf("    matches_leading found a question mark!\n");
      return matches_leading((partial_line), (pattern + 2));
    } 
    else {
      if (print == 1)
        printf("  matches_leading returned 0\n");
      return 0;
    }
  }
  return 0;
}

/**
 * Implementation of your matcher function, which
 * will be called by the main program.
 *
 * You may assume that both line and pattern point
 * to reasonably short, null-terminated strings.
 */
int rgrep_matches(char *line, char *pattern) {

  int print = 0;
    //
    // TODO put your code here.
    //
    if (print == 1)
      printf("\nStarted rgrep_matches\n");
    int index = 0;
    while (*(line + index) != 0) {
      if (print == 1)
        printf("\n  Started matches_leading\n");
      if (matches_leading((line + index), pattern) == 1) {
        if (print == 1)
          printf("\nrgrep_matches returned 1\n\n");
        return 1;
      } 
      index++;
    }
    if (index == 0) {
      return 0;
    }
    if (print == 1)
      printf("\nrgrep_matches returned 0\n\n");
    return 0;
}


