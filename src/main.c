#include <ctype.h>
#include <stdio.h>
#define STRING_VIEW_IMPLEMENTATION
#include "string_view.h"

bool is_not_space(int ch) { return !(isspace(ch)); }

int main(int argc, char *argv[]) {
  String_view sv = Sv_make("Hello, World");

  const char *cstr = Sv_to_cstr(sv);

  printf("cstr from sv = %s\n", cstr);

  printf("sv = " Sv_fmt "\n", Sv_arg(sv));
  printf("sv = " Sv_fmt "\n", Sv_arg(sv));
  printf("sv = " Sv_fmt "\n", Sv_arg(sv));

  return 0;
}
