#include <stdio.h>
#include <string.h>
#define CAML_NAME_SPACE
#include <caml/mlvalues.h>
#include <caml/memory.h>
#include <caml/alloc.h>
#include <caml/custom.h>
#include <caml/callback.h>

extern int ExecuteSkill(char *name);

/*
  type return_enum = Runn | Fail | Succ
  (corresponding C values: int 0,1,2)
 */

/* C interface to OCaml functions readbt, tick */

value read_bt(const char *filename) {
  CAMLparam0();
  static value *readbt_closure = NULL;
  if (readbt_closure == NULL) readbt_closure = caml_named_value("readbt");
  CAMLreturn (caml_callback(*readbt_closure, caml_copy_string(filename)));
}

int tick(value bt) {
  CAMLparam1(bt);
  static value *tick_closure = NULL;
  if (tick_closure == NULL) tick_closure = caml_named_value("tick");
  return Int_val(caml_callback(*tick_closure, bt));
}

/* OCaml interface to the C function ExecuteSkill */

CAMLprim value exec(value v) {
  return Val_int(ExecuteSkill(String_val(v)));
}
