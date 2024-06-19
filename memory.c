#include <stdlib.h>

#include "memory.h"
#include "vm.h"

void *
reallocate(void *pointer, size_t old_size, size_t new_size)
{
    void *r = NULL;

    if (new_size == 0) {
        free(pointer);
        return NULL;
    }

    r = realloc(pointer, new_size);
    if (!r) {
        exit(1);
    }
    return r;
}

static void
free_object(object_t* object) {
  switch (object->type) {
    case OBJ_STRING: {
      obj_string_t* string = (obj_string_t*)object;
      FREE_ARRAY(char, string->chars, string->length + 1);
      FREE(obj_string_t, object);
      break;
    }
  }
}

void
free_objects()
{
  object_t* object = vm.objects;
  while (object != NULL) {
    object_t* next = object->next;
    free_object(object);
    object = next;
  }
}