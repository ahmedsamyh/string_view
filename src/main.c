#include <ctype.h>
#include <stdio.h>
#define STRING_VIEW_IMPLEMENTATION
#include "string_view.h"

bool is_not_space(int ch) { return !(isspace(ch)); }

int main(int argc, char *argv[]) {
  String_view sv = Sv_make("Hello, World");

  String_view sv2 = Sv_pop_front_while(&sv, is_not_space);

  printf("sv = " Sv_fmt "\n", Sv_arg(sv));

  return 0;
}
