#include <ctype.h>
#include <stdio.h>
#define STRING_VIEW_IMPLEMENTATION
#include "string_view.h"

bool is_not_period(int ch) { return ch != '.'; }

int main(int argc, char *argv[]) {
  String_view sv = Sv_make("file.ext");

  String_view sv2 = Sv_pop_back_while(&sv, is_not_period);

  printf("sv = " Sv_fmt "\n", Sv_arg(sv));
  printf("sv2 = " Sv_fmt "\n", Sv_arg(sv2));

  return 0;
}
