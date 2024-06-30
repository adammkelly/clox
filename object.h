#ifndef CLOX_OBJECT_H
#define CLOX_OBJECT_H

#include "common.h"
#include "chunk.h"
#include "value.h"

#define OBJ_TYPE(value)        (AS_OBJ(value)->type)

#define IS_CLOSURE(value)      is_obj_type(value, OBJ_CLOSURE)
#define IS_FUNCTION(value)     is_obj_type(value, OBJ_FUNCTION)
#define IS_NATIVE(value)       is_obj_type(value, OBJ_NATIVE)
#define IS_STRING(value)       is_obj_type(value, OBJ_STRING)

#define AS_CLOSURE(value)      ((obj_closure_t *)AS_OBJ(value))
#define AS_FUNCTION(value)     ((obj_function_t *)AS_OBJ(value))
#define AS_NATIVE(value) \
    (((obj_native_fn_t *)AS_OBJ(value))->function)
#define AS_STRING(value)       ((obj_string_t *)AS_OBJ(value))
#define AS_CSTRING(value)      (((obj_string_t *)AS_OBJ(value))->chars)

typedef enum {
  OBJ_CLOSURE,
  OBJ_FUNCTION,
  OBJ_NATIVE,
  OBJ_STRING,
  OBJ_UPVALUE
} obj_type_t;

struct obj {
  obj_type_t type;
  bool is_marked;
  struct obj* next;
};

struct obj_string {
  object_t obj;
  int length;
  char* chars;
  uint32_t hash;
};

typedef struct obj_upvalue {
  object_t obj;
  value_t* location;
  value_t closed;
  struct obj_upvalue* next;
} obj_upvalue_t;

typedef struct {
  object_t obj;
  int arity;
  int upvalue_count;
  chunk_t chunk;
  obj_string_t* name;
} obj_function_t;

typedef struct {
  object_t obj;
  obj_function_t* function;
  obj_upvalue_t **upvalues;
  int upvalue_count;
} obj_closure_t;

typedef value_t (*native_fn_t)(int arg_count, value_t* args);

typedef struct {
  object_t obj;
  native_fn_t function;
} obj_native_fn_t;


obj_closure_t* new_closure(obj_function_t* function);
obj_function_t* new_function();
obj_native_fn_t* new_native(native_fn_t function);

obj_string_t* take_string(char* chars, int length);
obj_string_t* copy_string(const char* chars, int length);
obj_upvalue_t* new_upvalue(value_t* slot);
void print_object(value_t value);

static inline bool is_obj_type(value_t value, obj_type_t type) {
  return IS_OBJ(value) && AS_OBJ(value)->type == type;
}

#endif