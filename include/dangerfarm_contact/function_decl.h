#include <dangerfarm_contact/macro_tricks.h>

/**
 * We don't really version this code, but if we did, we can adjust this symbol.
 */
#define DANGERFARM_CONTACT_VERSION_SYM V0_1

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

/**
 * The DANGERFARM_CONTACT_SYM macro elevates a given symbol to the
 * DANGERFARM_CONTACT namespace.
 */
#define DANGERFARM_CONTACT_SYM(sym) \
    DANGERFARM_CONTACT_SYM_COMBINE1( \
        DANGERFARM_CONTACT_UNIQUE_NAME, DANGERFARM_CONTACT_VERSION_SYM, sym)

/**
 * Begin an export section.
 */
#define DANGERFARM_CONTACT_BEGIN_EXPORT \
    _Pragma("GCC diagnostic push") \
    _Pragma("GCC diagnostic ignored \"-Wunused-function\"")

/**
 * End an export section.
 */
#define DANGERFARM_CONTACT_END_EXPORT \
    _Pragma("GCC diagnostic pop")

/**
 * Begin a contract helper section.
 */
#define DANGERFARM_CONTACT_BEGIN_CONTRACT_HELPER \
    _Pragma("GCC diagnostic push") \
    _Pragma("GCC diagnostic ignored \"-Wunused-parameter\"")

/**
 * End a contract helper section.
 */
#define DANGERFARM_CONTACT_END_CONTRACT_HELPER \
    _Pragma("GCC diagnostic pop")
