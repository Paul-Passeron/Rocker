#include "./RockerAllocator/alloc.h"
#include "./src/generation/fundefs.h"
#include "./src/generation/fundefs_internal.h"
#include "./src/generation/typedefs.h"
typedef struct int_node *int_node;
typedef struct int_linked_list *int_linked_list;
struct int_node {
  int Value;
  int_linked_list Next;
};
struct int_linked_list {
  enum { Tail, Node } tag;
  union {
    int_node Node;
  } data;
};
int not_main() { return 10; }
int main() {
  init_compiler_stack();
  {
    print((string){.data = "Hey !\n", .length = 7});
    return 0;
  }
  kill_compiler_stack();
}
