#ifndef _STRING_VIEW_H_
#define _STRING_VIEW_H_

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  const char *data;
  size_t len;
} String_view;

#define Sv_fmt "%.*s"
#define Sv_arg(sv) (int)sv.len, sv.data
#define SV(cstr)                                                               \
  (String_view) { .data = cstr, .len = strlen(cstr) }

String_view Sv_make(const char *cstr);
bool Sv_starts_with(String_view sv, const char *str);
bool Sv_ends_with(String_view sv, const char *str);
String_view Sv_pop_front(String_view *sv, size_t size);
String_view Sv_pop_back(String_view *sv, size_t size);
String_view Sv_pop_front_while(String_view *sv, bool (*condition)(int));
String_view Sv_pop_back_while(String_view *sv, bool (*condition)(int));
const char *Sv_to_cstr(String_view sv);
//////////////////////////////////////////////////
#ifdef STRING_VIEW_IMPLEMENTATION
String_view Sv_make(const char *cstr) {
  String_view sv = {0};
  sv.len = strlen(cstr);
  sv.data = cstr;
  return sv;
}
bool Sv_starts_with(String_view sv, const char *str) {
  if (sv.len < strlen(str))
    return false;
  assert(sv.len >= strlen(str));
  String_view sv_start = Sv_pop_front(&sv, strlen(str));
  return (strcmp(str, Sv_to_cstr(sv_start)) == 0);
}
bool Sv_ends_with(String_view sv, const char *str) {
  if (sv.len < strlen(str))
    return false;
  assert(sv.len >= strlen(str));
  String_view sv_end = Sv_pop_back(&sv, strlen(str));
  return (strcmp(str, Sv_to_cstr(sv_end)) == 0);
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
String_view Sv_pop_back_while(String_view *sv, bool (*condition)(int)) {
  size_t i = 0;
  while (condition(sv->data[sv->len - i]) && i < sv->len) {
    i++;
  }
  String_view popped = {0};
  popped.data = sv->data + (sv->len - i) + 1;
  popped.len = i;

  sv->len -= i - 1;

  return popped;
}
const char *Sv_to_cstr(String_view sv) {
  char *cstr = (char *)calloc(sv.len, sizeof(char));

  memcpy(cstr, sv.data, sv.len);

  cstr[sv.len] = '\0';

  return cstr;
}
#endif

#endif /* _STRING_VIEW_H_ */
