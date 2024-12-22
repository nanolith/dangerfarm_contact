#include <stddef.h>
#include <stdint.h>
#include <unistd.h>
#include <stdarg.h>
#include <stdbool.h>
#include <kcgi.h>

#include "../../src/contactform/contactform_internal.h"

int nondet_value();

int choose_method()
{
    int retval = nondet_value();

    MODEL_ASSUME(
        retval == KMETHOD_ACL
     || retval == KMETHOD_CONNECT
     || retval == KMETHOD_COPY
     || retval == KMETHOD_DELETE
     || retval == KMETHOD_GET
     || retval == KMETHOD_HEAD
     || retval == KMETHOD_LOCK
     || retval == KMETHOD_MKCALENDAR
     || retval == KMETHOD_MKCOL
     || retval == KMETHOD_MOVE
     || retval == KMETHOD_OPTIONS
     || retval == KMETHOD_POST);

    return retval;
}

int choose_invalid_method()
{
    int retval = nondet_value();

    MODEL_ASSUME(
        retval != KMETHOD_ACL
     && retval != KMETHOD_CONNECT
     && retval != KMETHOD_COPY
     && retval != KMETHOD_DELETE
     && retval != KMETHOD_GET
     && retval != KMETHOD_HEAD
     && retval != KMETHOD_LOCK
     && retval != KMETHOD_MKCALENDAR
     && retval != KMETHOD_MKCOL
     && retval != KMETHOD_MOVE
     && retval != KMETHOD_OPTIONS
     && retval != KMETHOD_POST);

    return retval;
}

int main(int argc, char* argv[])
{
    MODEL_ASSERT(prop_valid_request_method(choose_method()));
    MODEL_ASSERT(!prop_valid_request_method(choose_invalid_method()));

    return 0;
}
