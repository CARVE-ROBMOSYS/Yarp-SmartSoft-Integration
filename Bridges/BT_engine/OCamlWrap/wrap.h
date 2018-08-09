#define CAML_NAME_SPACE
#include <caml/mlvalues.h>


/*
  type return_enum = Runn | Fail | Succ
  (corresponding C values: int 0,1,2)
 */

/* C interface to OCaml functions readbt, tick */
extern "C"
{
	value read_bt(const char *filename);
	int tick(value bt);
}
/* OCaml interface to the C function ExecuteSkill */
CAMLprim value exec(value v);
