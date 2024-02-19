#include "ast.h"
#include "../RockerAllocator/alloc.h"
#include <stdio.h>

ast_t new_ast(node_t node) {
  ast_t ptr = allocate_compiler_persistent(sizeof(node_t));
  *ptr = node;
  return ptr;
}

ast_array_t new_ast_array(void) {
  ast_array_t res;
  res.data = allocate_compiler_persistent(sizeof(ast_t) * INIT_AST_ARR);
  res.length = 0;
  res.capacity = INIT_AST_ARR;
  return res;
}

void push_ast_array(ast_array_t *arr, ast_t a) {
  if (arr->capacity <= arr->length) {
    arr->capacity *= 2;
    arr->data = reallocate_compiler_persistent(arr->data,
                                               arr->capacity * sizeof(ast_t));
  }
  arr->data[arr->length++] = a;
}

// Placeholder for print_token_bis function
void print_token_bis(token_t token) {
  // Implement based on your token printing needs
  printf("Token(%s, %s)", lexeme_of_type(token.type), token.lexeme);
}

// Forward declaration for the recursive function
void print_ast_node(ast_t node, int depth);

void print_indent(int depth) {
  for (int i = 0; i < depth; i++) {
    printf("|  ");
  }
}

void print_ast(ast_t root) {
  if (!root) {
    printf("Empty AST\n");
    return;
  }
  print_ast_node(root, 0);
}

void print_ast_node(ast_t node, int depth) {
  if (!node)
    return;

  print_indent(depth);

  switch (node->tag) {
  case op:
    printf("Operation: %s\n", lexeme_of_type(node->data.op.op));
    print_ast_node(node->data.op.left, depth + 1);
    print_ast_node(node->data.op.right, depth + 1);
    break;
  case literal:
    printf("Literal: ");
    print_token_bis(
        node->data.literal
            .lit); // Assuming print_token_bis is a function you have
    printf("\n");
    break;
  case identifier:
    printf("Identifier: ");
    print_token_bis(node->data.identifier.id);
    printf("\n");
    break;
  case fundef:
    printf("Function Definition: ");
    print_token_bis(node->data.fundef.name);
    printf("\n");
    print_indent(depth + 1);
    printf("Arguments: [");
    for (int i = 0; i < node->data.fundef.args.length; ++i) {
      if (i > 0)
        printf(", ");
      print_token_bis(node->data.fundef.args.data[i]);
    }
    printf("]\n");

    // Print argument types if any
    if (node->data.fundef.types.length > 0) {
      print_indent(depth + 1);
      printf("Types:\n");
      for (int i = 0; i < node->data.fundef.types.length; ++i) {
        print_ast_node(node->data.fundef.types.data[i], depth + 2);
        if (i < node->data.fundef.types.length - 1)
          printf(",\n");
      }
    }

    // Print return type if specified
    if (node->data.fundef.ret_type) {
      print_indent(depth + 1);
      printf("Return Type:\n");
      print_ast_node(node->data.fundef.ret_type, depth + 2);
    }

    // Print function body
    print_indent(depth + 1);
    printf("Body:\n");
    print_ast_node(node->data.fundef.body, depth + 2);
    // Args, types, body, and ret_type would be printed similarly
    break;
  case funcall: {
    printf("Function Call: ");
    print_token_bis(node->data.funcall.name); // Print the name of the function
    printf("\n");

    // Check if there are any arguments to print
    if (node->data.funcall.args.length > 0) {
      print_indent(depth + 1);
      printf("Arguments:\n");
      for (int i = 0; i < node->data.funcall.args.length; ++i) {
        // Recursively print each argument in the function call
        print_ast_node(node->data.funcall.args.data[i], depth + 2);
      }
    } else {
      print_indent(depth + 1);
      printf("No arguments\n");
    }
  } break;
  // Add cases for other node types here
  case tupledef: {
    printf("Tuple Definition:\n");
    // Iterate over the signature tokens and print each
    for (int i = 0; i < node->data.tupledef.signature.length; ++i) {
      print_indent(depth + 1);
      print_token_bis(node->data.tupledef.signature.data[i]);
      if (i < node->data.tupledef.signature.length - 1) {
        printf(",");
      }
      printf("\n");
    }

  } break;
  case compound: {
    printf("Compound Statement:\n");
    for (int i = 0; i < node->data.compound.stmts.length; ++i) {
      // Recursively print each statement in the compound
      print_ast_node(node->data.compound.stmts.data[i], depth + 1);
    }
  } break;

  case ret: {
    printf("Return Statement\n");
    if (node->data.ret.expr) {
      print_indent(depth + 1);
      printf("Expression:\n");
      // Recursively print the expression being returned
      print_ast_node(node->data.ret.expr, depth + 2);
    } else {
      // It's possible to have return statements without an expression in some
      // languages
      print_indent(depth + 1);
      printf("No expression\n");
    }
    break;
  }

  case program:
    printf("Program:\n");
    for (int i = 0; i < node->data.program.prog.length; ++i) {
      print_ast_node(node->data.program.prog.data[i], depth + 1);
    }
    break;
  // Handle other structures like compound, vardef, etc.
  default:
    printf("Unknown node type %d", node->tag);
  }
}
