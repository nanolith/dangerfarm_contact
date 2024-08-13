#include <dangerfarm_contact/macro_tricks.h>

/**
 * A UUID symbol to make names unique.
 */
#define DANGERFARM_CONTACT_UNIQUE_NAME 6a32746c_5353_11ef_b2d0_18c04d8c76eb

/**
 * Concatenate two symbols together.
 */
#define DANGERFARM_CONTACT_CONCAT(x,y) x ## y

/**
 * Symbol expansion and combination macros.
 */
#define DANGERFARM_CONTACT_SYM_COMBINE(x, y, z) \
    dangerfarm_contact ## _ ## x ## _ ## y ## _ ## z
#define DANGERFARM_CONTACT_SYM_COMBINE1(x, y, z) \
    DANGERFARM_CONTACT_SYM_COMBINE(x, y, z)
