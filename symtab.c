/* Copyright 1988 by GeoMaker Software                                      */
/* Written by Mark Grand                                                    */

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "symtab.h"

/****************************************************************************/
/*                                                                          */
/*          Symbol Table Support functions                                  */
/*                                                                          */
/****************************************************************************/

/****************************************************************************/
/*                                                                          */
/*                         P R I V A T E   S T U F F                        */
/*                                                                          */
/****************************************************************************/


struct sym_binding
    {
    struct sym_binding *next;           /* pointer to next item in bucket   */
    sym_name_type name;                 /* pointer to symbol name           */
#ifdef SYM_MULTIPLE_NAME_SPACES
    unsigned name_space;                /* name space identifier            */
#endif
#if defined(SYM_DEEP_BINDING)
    sym_scope_id scope;                 /* associate sym_binding with scope */
#endif
#ifdef SYM_POINTS_TO_VALUE
    sym_value_type *value;              /* symbol value                     */
#else
    sym_value_type value;               /* symbol value                     */
#endif
    };

/* Array of hash buckets */
static struct sym_binding *hash_table[SYM_BUCKET_MAX] = { NULL };

/* The following two declarations are parameters that are passed to         */
/* search_linked_list as global data.  This is for the convenience of       */
/* sym_lookup which may call search_linked_list multiple times as it        */
/* searches through nested scopes.                                          */
static const char *my_name;
#ifdef SYM_MULTIPLE_NAME_SPACES
static unsigned my_name_space;          /* local copy of name space param   */
#endif

#ifdef SYM_DEEP_BINDING
/* Nested scopes are enabled.  */

#ifdef SYM_SCOPE_STACK_DEPTH
/* Nested scopes follow stack discipline.  */

/* The nested scope stack.  */
static struct sym_binding *scope_stack[SYM_SCOPE_STACK_DEPTH];

#ifndef SYM_NO_CHECK_POP
/* Array paralel to scope_stack.                                            */
/* Used to determine if curent scope is really the top of stack.            */
/* If an element contains 0 it is above the top of stack.                   */
/*                        1 it is at the top of stack.                      */
/*                        2 it is below the top of stack.                   */
static short scope_level[SYM_SCOPE_STACK_DEPTH] = {0};
#endif

/* #define to return a pointer to a non-global scope given a scope_id.  */
#define sym_get_scope_bindings(x) (scope_stack+(x))

#ifndef SYM_NO_CHECK_POP
/* #define to get scope level */
#define sym_get_level(x) (scope_level[x])

/* #define to set scope level */
#define sym_set_level(x,y) (scope_level[x] = (y))
#endif

#else
/* Nested scopes follow tree discipline.  */

/* #define to return a pointer to a non-global scope given a scope_id.  */
#define sym_get_scope_bindings(x) (&(x)->linked_list)

#ifndef SYM_NO_CHECK_POP
/* #define to get scope level */
#define sym_get_level(x) ((x)->sym_check_pop)

/* #define to set scope level */
#define sym_set_level(x,y) (((x)->sym_check_pop) = (y))
#endif

#endif/* #endif #ifdef SYM_SCOPE_STACK_DEPTH  */

/* The current scope.  Initialized to be the global scope.  */
static sym_scope_id scope_pointer = SYM_ROOT_SCOPE;

/* Pointer provides external read access to scope_pointer.  */
const sym_scope_id *const current_scope = &scope_pointer;

#endif/* #ifdef SYM_DEEP_BINDING */


/* Compute addess of pointer to hash bucket                                 */
static struct sym_binding ** hash_bucket(void)
    {
    register unsigned hash_sum;
    const char * s = my_name;

    hash_sum = *s;
    while (*s++)                        /* Compute hash sum                 */
        {
        hash_sum = (hash_sum << 1) ^ *s;
        }

    /* Map hash_sum into a hash bucket index.  This is done using the %     */
    /* operator.  Depending on the application and the C compiler, the time */
    /* required to perform the % operation may not be small in comparison   */
    /* to the time spent searching a hash bucket.  In this case, the        */
    /* performance can be tweaked by making SYM_BUCKET_MAX a power of 2 and */
    /* changing                                                             */
    /* % SYM_BUCKET_MAX                                                     */
    /* in the following two statements to be                                */
    /* & the_base_2_log_of_SYM_BUCKET_MAX                                   */
#ifdef SYM_MULTIPLE_NAME_SPACES
    return hash_table + (hash_sum + my_name_space) % SYM_BUCKET_MAX;
#else
    return hash_table + hash_sum % SYM_BUCKET_MAX;
#endif
    }

/* Search a non-global scope or a hash bucket for binding with given name.  */
static int search_linked_list(struct sym_binding ***const ptr)
    {
    struct sym_binding **sym;

    sym = *ptr;

    while (*sym)
        {
        if (
#ifdef SYM_MULTIPLE_NAME_SPACES
            (*sym)->name_space == my_name_space &&
#endif
                    SYM_COMPARE_NAME_FUNCTION((*sym)->name, my_name) == 0 )
            {
#ifdef SYM_SELF_ORGANIZING_LISTS
            /* Move binding to head of linked list */
            register struct sym_binding *temp;

            temp = *sym;
            *sym = temp->next;
            temp->next = **ptr;
            **ptr = temp;
#else
            *ptr = sym;
#endif
            return 0;
            }
        sym = &(*sym)->next;
        }

    return 1;
    }

/* Find binding. Sets parameter to a pointer to a pointer to the binding if */
/* the binding is found.  Otherwise, to a pointer to a pointer in the scope */
/* that should be set if a new binding is to be computed.                   */
/* Returns 0 if binding is found, 1 if not.                                 */
#ifdef SYM_MULTIPLE_NAME_SPACES
static int lookup_binding(sym_name_type name,
                          struct sym_binding ***ptr,
                          unsigned name_space)
#else
static int lookup_binding(sym_name_type name,
                          struct sym_binding ***ptr)
#endif
    {
    my_name = sym_extract_name(name);
#ifdef SYM_MULTIPLE_NAME_SPACES
    my_name_space = name_space;
#endif

#ifdef SYM_DEEP_BINDING
    if (scope_pointer != SYM_ROOT_SCOPE)
#ifdef SYM_SCOPE_STACK_DEPTH
        *ptr = scope_stack + scope_pointer;
#else
        *ptr = &scope_pointer->linked_list;
#endif
    else
#endif
        /* Find hash bucket */
        *ptr = hash_bucket();

    /* Look for binding in bucket                                           */
    return search_linked_list(ptr);
    }


/****************************************************************************/
/*                                                                          */
/*                         P U B L I C   S T U F F                          */
/*                                                                          */
/****************************************************************************/

/* Create new symbol table entry                                            */
/* Return either SYMTAB_OK, SYMTAB_DUPLICATE or SYMTAB_NO_MEMORY            */
#ifdef SYM_MULTIPLE_NAME_SPACES
int sym_add(sym_name_type  name, sym_value_type *value, unsigned name_space)
#else
int sym_add(sym_name_type  name, sym_value_type *value)
#endif
    {
    struct sym_binding **ptr, *sym;

#ifdef SYM_MULTIPLE_NAME_SPACES
    if (!lookup_binding(name, &ptr, name_space))
#else
    if (!lookup_binding(name, &ptr))
#endif
        return SYMTAB_DUPLICATE;

    /* Not found in symbol table so create a new symble table entry.        */
    sym = (struct sym_binding *)
                malloc(sizeof(struct sym_binding)); /* Allocate table entry */
    if (sym == NULL)
        return SYMTAB_NO_MEMORY;

    /* Fill in information about the symbol                                 */
    sym->name = name;
#ifdef SYM_MULTIPLE_NAME_SPACES
    sym->name_space = name_space;
#endif
#ifdef SYM_POINTS_TO_VALUE
    sym->value = value;
#else
    sym->value = *value;
#endif
    SYM_ADD_NAME_BOOKKEEPING(name);
    SYM_ADD_VALUE_BOOKKEEPING(value);

    /* Insert into linked list                                              */
    sym->next = *ptr;
    *ptr = sym;

    return SYMTAB_OK;                   /* All's well that ends well.       */
    }


/* Create new or replace existing symbol table entry                        */
/* Return either SYMTAB_OK, SYMTAB_DUPLICATE or SYMTAB_NO_MEMORY            */
#ifdef SYM_MULTIPLE_NAME_SPACES
int sym_enter(sym_name_type  name, sym_value_type *value, unsigned name_space)
#else
int sym_enter(sym_name_type  name, sym_value_type *value)
#endif
    {
    struct sym_binding **ptr;

#ifdef SYM_MULTIPLE_NAME_SPACES
    if (lookup_binding(name, &ptr, name_space))
#else
    if (lookup_binding(name, &ptr))
#endif
        { /* Not found in symbol table so create a new symbol table entry.  */
        struct sym_binding *sym;

        sym = (struct sym_binding *)
            malloc(sizeof(struct sym_binding));/* Allocate table entry      */
        if (sym == NULL)
            return SYMTAB_NO_MEMORY;

        /* Fill in information about the symbol                                 */
        sym->name = name;
#ifdef SYM_MULTIPLE_NAME_SPACES
        sym->name_space = name_space;
#endif
#ifdef SYM_POINTS_TO_VALUE
        sym->value = value;
#else
        sym->value = *value;
#endif
        SYM_ADD_VALUE_BOOKKEEPING(value);
        SYM_ADD_NAME_BOOKKEEPING(name);

        /* Insert into linked list                                          */
        sym->next = *ptr;
        *ptr = sym;

        return SYMTAB_OK;               /* Binding successfully created.    */
        }
    else
        {
#ifdef SYM_POINTS_TO_VALUE
        SYM_REMOVE_VALUE_BOOKKEEPING((*ptr)->value);
        (*ptr)->value = value;
#else
        SYM_REMOVE_VALUE_BOOKKEEPING(&(*ptr)->value);
        (*ptr)->value = *value;
#endif
        SYM_ADD_VALUE_BOOKKEEPING(value);

        return SYMTAB_DUPLICATE;        /* Inform caller name already       */
                                        /* existed so replaced value.       */
        }
    }


/* Look for name in symbol table.                                           */
/* If found return SYMTAB_OK and update the value parameter                 */
/* If not found return SYMTAB_NOT_FOUND                                     */
int sym_lookup(sym_name_type  name,
#ifdef SYM_POINTS_TO_VALUE
               sym_value_type **value
#else
               sym_value_type *value
#endif
#ifdef SYM_MULTIPLE_NAME_SPACES
              ,unsigned name_space
#endif
                                  )
    {
    struct sym_binding **ptr;
#ifdef SYM_DEEP_BINDING

    sym_scope_id scope;

    my_name = sym_extract_name(name);
#ifdef SYM_MULTIPLE_NAME_SPACES
    my_name_space = name_space;
#endif

    for ( scope = scope_pointer;
          scope != SYM_ROOT_SCOPE;
          scope = sym_prev_scope(scope))
        {
        ptr = sym_get_scope_bindings(scope);
        if (search_linked_list(&ptr) == 0)
            {
            goto exit;
            }
        }
    ptr = hash_bucket();
    if (search_linked_list(&ptr))
        return SYMTAB_NOT_FOUND;

exit:
#else

#ifdef SYM_MULTIPLE_NAME_SPACES
    if (lookup_binding(name, &ptr, name_space))
#else
    if (lookup_binding(name, &ptr))
#endif
        return SYMTAB_NOT_FOUND;

#endif
    *value = (*ptr)->value;
    return SYMTAB_OK;
    }

/* remove symbol from symbol table */
/* return SYMTAB_OK or SYMTAB_NOT_FOUND */
#ifdef SYM_MULTIPLE_NAME_SPACES
int sym_remove(sym_name_type  name, unsigned name_space)
#else
int sym_remove(sym_name_type  name)
#endif
    {
    struct sym_binding **ptr, *tmp;

#ifdef SYM_MULTIPLE_NAME_SPACES
    if (lookup_binding(name, &ptr, name_space))
#else
    if (lookup_binding(name, &ptr))
#endif
        return SYMTAB_NOT_FOUND;

    tmp = *ptr;
    SYM_REMOVE_NAME_BOOKKEEPING(tmp->name);
#ifdef SYM_POINTS_TO_VALUE
    SYM_REMOVE_VALUE_BOOKKEEPING(tmp->value);
#else
    SYM_REMOVE_VALUE_BOOKKEEPING(&tmp->value);
#endif
    *ptr = (*ptr)->next;
    free(tmp);
    return SYMTAB_OK;
    }



#ifdef SYM_DEEP_BINDING
/* push a new scope */
#ifdef SYM_SCOPE_STACK_DEPTH
int sym_push_scope(void)
    {
    if (scope_pointer + 1 >= SYM_SCOPE_STACK_DEPTH)
        return SYMTAB_STACK_OVERFLOW;
#ifndef SYM_NO_CHECK_POP
    if (scope_pointer != SYM_ROOT_SCOPE)
        sym_set_level(scope_pointer, 2);
#endif
    scope_stack[++scope_pointer] = NULL;
#ifndef SYM_NO_CHECK_POP
    sym_set_level(scope_pointer, 1);
#endif
    return SYMTAB_OK;
    }
#else
int sym_push_scope(sym_scope_id old_scope)
    {
    struct sym_scope_header *new_scope;

#ifndef SYM_NO_CHECK_POP
    if (scope_pointer != SYM_ROOT_SCOPE)
        sym_set_level(scope_pointer, 1 + sym_get_level(scope_pointer));
#endif
    new_scope = malloc(sizeof(struct sym_scope_header));
    if (new_scope == NULL)
        return SYMTAB_NO_MEMORY;
    new_scope->linked_list = NULL;
    new_scope->previous_scope = old_scope;
    scope_pointer = new_scope;
#ifndef SYM_NO_CHECK_POP
    sym_set_level(scope_pointer, 1);
#endif
    return SYMTAB_OK;
    }
#endif/* #ifdef SYM_SCOPE_STACK_DEPTH */

/* pop and free and old scope */
int sym_pop_scope(void)
    {
    struct sym_binding *binding;

    if (scope_pointer == SYM_ROOT_SCOPE)
        return SYMTAB_STACK_UNDERFLOW;
#ifndef SYM_NO_CHECK_POP
    if (sym_get_level(scope_pointer) != 1)
        return SYMTAB_NOT_TOP;
#endif
    binding = *sym_get_scope_bindings(scope_pointer);
    scope_pointer = sym_prev_scope(scope_pointer);

    while (binding != NULL)
        {
        struct sym_binding *tmp;

        SYM_REMOVE_NAME_BOOKKEEPING(binding->name);
#ifdef SYM_POINTS_TO_VALUE
        SYM_REMOVE_VALUE_BOOKKEEPING(binding->value);
#else
        SYM_REMOVE_VALUE_BOOKKEEPING(&binding->value);
#endif
        tmp = binding;
        binding = binding->next;
        free(tmp);
        }
    return SYMTAB_OK;
    }
#endif/* SYM_DEEP_BINDING */


#ifdef SYM_HISTOGRAM
#ifndef BUFSIZ
#include <stdio.h>
#endif
/* Displays a histogram of the sizes of the global hash buckets.            */
void sym_histogram()
    {
    int i;

    for (i = 0; i < SYM_BUCKET_MAX ; i++)
        {
        struct sym_binding *b;
        unsigned j;

        b = hash_table[i];
        j = 0;
        while (b)
            {
            j += 1;
            b = b->next;
            }
        printf("bucket %d contains %u\n", i, j);
        }
    }
#endif

#ifdef SYM_REQUIRE_SET_SCOPE
void sym_set_scope(sym_scope_id scope)
    {
    scope_pointer = scope;
    }
#endif

#if defined(SYM_DEEP_BINDING) && defined(SYM_REQUIRE_GLOBAL)
/* Create new global symbol table entry                                     */
/* Return either SYMTAB_OK, SYMTAB_DUPLICATE or SYMTAB_NO_MEMORY            */
#ifdef SYM_MULTIPLE_NAME_SPACES
int sym_global_add(sym_name_type  name,
                   sym_value_type *value,
                   unsigned name_space)
#else
int sym_global_add(sym_name_type  name, sym_value_type *value)
#endif
    {
    int rc;
    sym_scope_id scope;

    scope = scope_pointer;
    scope_pointer = SYM_ROOT_SCOPE;
#ifdef SYM_MULTIPLE_NAME_SPACES
    rc = sym_add(name, value, name_space);
#else
    rc = sym_add(name, value);
#endif
    scope_pointer = scope;
    return rc;
    }


/* Create new or replace existing global symbol table entry                 */
/* Return either SYMTAB_OK or SYMTAB_NO_MEMORY                              */
#ifdef SYM_MULTIPLE_NAME_SPACES
int sym_global_enter(sym_name_type  name,
                     sym_value_type *value,
                     unsigned name_space)
#else
int sym_global_enter(sym_name_type  name, sym_value_type *value)
#endif
    {
    int rc;
    sym_scope_id scope;

    scope = scope_pointer;
    scope_pointer = SYM_ROOT_SCOPE;
#ifdef SYM_MULTIPLE_NAME_SPACES
    rc = sym_enter(name, value, name_space);
#else
    rc = sym_enter(name, value);
#endif
    scope_pointer = scope;
    return rc;
    }


/* Look for global name in symbol table.                                    */
/* If found return SYMTAB_OK and update the value parameter.                */
/* If not found return SYMTAB_NOT_FOUND.                                    */
int sym_global_lookup(sym_name_type  name,
#ifdef SYM_POINTS_TO_VALUE
                      sym_value_type **value
#else
                      sym_value_type *value
#endif
#ifdef SYM_MULTIPLE_NAME_SPACES
                     ,unsigned name_space
#endif
                                         )
    {
    struct sym_binding **ptr;

    my_name = sym_extract_name(name);
#ifdef SYM_MULTIPLE_NAME_SPACES
    my_name_space = name_space;
#endif

    /* Find hash bucket */
    ptr = hash_bucket();

    /* Look for binding in bucket                                           */
    if (search_linked_list(&ptr))
        return SYMTAB_NOT_FOUND;
    *value = (*ptr)->value;
    return SYMTAB_OK;
    }


/* remove symbol from symbol table */
/* return SYMTAB_OK or SYMTAB_NOT_FOUND */
#ifdef SYM_MULTIPLE_NAME_SPACES
int sym_global_remove(sym_name_type  name, unsigned name_space)
#else
int sym_global_remove(sym_name_type  name)
#endif
    {
    int rc;
    sym_scope_id scope;

    scope = scope_pointer;
    scope_pointer = SYM_ROOT_SCOPE;
#ifdef SYM_MULTIPLE_NAME_SPACES
    rc = sym_remove(name, name_space);
#else
    rc = sym_remove(name);
#endif
    scope_pointer = scope;
    return rc;
    }
#endif
