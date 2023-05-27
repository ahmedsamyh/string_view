#ifndef _STRING_VIEW_H_
#define _STRING_VIEW_H_

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  const char *data;
  size_t len;
} String_view;

#define Sv_fmt "%.*s"
#define Sv_arg(sv) (int)sv.len, sv.data

String_view Sv_make(const char *cstr);
bool Sv_starts_with(const char *str, String_view sv);
bool Sv_ends_with(const char *str, String_view sv);
String_view Sv_pop_front(String_view *sv, size_t size);
String_view Sv_pop_back(String_view *sv, size_t size);
String_view Sv_pop_front_while(String_view *sv, bool (*condition)(int));
//////////////////////////////////////////////////
#ifdef STRING_VIEW_IMPLEMENTATION
String_view Sv_make(const char *cstr) {
  String_view sv = {0};
  sv.len = strlen(cstr);
  sv.data = cstr;
  return sv;
}
bool Sv_starts_with(const char *str, String_view sv) {
  if (sv.len < strlen(str))
    return false;

  for (size_t i = 0; i < strlen(str); ++i) {
    if (str[i] != sv.data[i]) {
      return false;
    }
  }
  return true;
}
bool Sv_ends_with(const char *str, String_view sv) {
  if (sv.len < strlen(str))
    return false;

  for (size_t i = 0; i < strlen(str); ++i) {
    if (str[strlen(str) - i] != sv.data[sv.len - i]) {
      return false;
    }
  }
  return true;
}
String_view Sv_pop_front(String_view *sv, size_t size) {
  if (size > sv->len) {
    return (String_view){0};
  }
  String_view popped = {0};
  popped.data = sv->data;
  popped.len = size;

  sv->data += size;
  sv->len -= size;
  return popped;
}
String_view Sv_pop_back(String_view *sv, size_t size) {
  if (size > sv->len) {
    return (String_view){0};
  }
  String_view popped = {0};
  popped.data = (sv->data + sv->len) - size;
  popped.len = size;

  sv->len -= size;

  return popped;
}
String_view Sv_pop_front_while(String_view *sv, bool (*condition)(int)) {
  size_t i = 0;
  while (condition(sv->data[i]) && i < sv->len) {
    i++;
  }
  String_view popped = {0};
  popped.data = sv->data;
  popped.len = i;

  sv->data += i;
  sv->len -= i;

  return popped;
}
#endif

#endif /* _STRING_VIEW_H_ */
