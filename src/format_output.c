#include "ToyLisp.h"

void lval_print_expr(lval* v, char open, char close) {
    putchar(open);
    for (int i = 0; i < v->count; i++) {
        lval_print(v->cell[i]);
        if (i != (v->count-1)) {
            putchar(' ');
        }
    }
    putchar(close);
}

void lval_print_str(lval* v) {
    /* Make a Copy of the String */
    char* escaped = malloc(strlen(v->str)+1);
    strcpy(escaped, v->str);
    /* Pass it through the escape function */
    escaped = mpcf_escape(escaped);
    /* Print it between " characters */
    printf("\"%s\"", escaped);
    free(escaped);
}

void lval_print(lval* v) {
    switch (v->type) {
        case LVAL_FUN:
            if (v->builtin) {
                printf("<builtin>");
            } else {
                printf("(\\ ");
                lval_print(v->formals);
                putchar(' ');
                lval_print(v->body);
                putchar(')');
            }
            break;
        case LVAL_NUM:   printf("%li", v->num); break;
        case LVAL_ERR:   printf("Error: %s", v->err); break;
        case LVAL_SYM:   printf("%s", v->sym); break;
        case LVAL_SEXPR: lval_print_expr(v, '(', ')'); break;
        case LVAL_QEXPR: lval_print_expr(v, '{', '}'); break;
        case LVAL_STR: lval_print_str(v); break;
    }
}

void lval_println(lval* v) {
    lval_print(v);
    putchar('\n');
}


