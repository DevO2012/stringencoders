/* -*- mode: c++; c-basic-offset: 4; indent-tabs-mode: nil; tab-width: 4 -*- */
/* vi: set expandtab shiftwidth=4 tabstop=4: */

#ifndef COM_MODP_QSITER
#define COM_MODP_QSITER

#include <string.h>

#include "extern_c_begin.h"

/**
 * \file modp_qsiter.h
 * \brief URL Query string key-value pair iterator.  Uses no heap, makes
 *        no copy, makes no modification of input.  Think of this as a
 *        super-strtok_r.
 *
 * This also does not do query-string un-escaping.
 *
 * \code
 * qsiiter_t qsi;
 * const char* qs = "foo=bar&ding=bar";
 * qsiter_reset(&qsi, qs, strlen(qs));
 * while  (qsiter_next(&qsi)) {
 *    // we only get start and length of key,value
 *    // up to you how to copy it or not, on heap or stack
 *    // with strcpy, strncpy, strndup, memcpy, mempcpy, strlcpy, whatever
 *    // callers job to alloc/free memory
 *
 *    const char* key = (const char*) malloc(qsi.keylen + 1);
 *    strcpy(key, qsi->key, qsi->keylen);
 *    const char* val = (const char*) malloc(qsi.vallen + 1);
 *    strcpy(val, qsi->val, qsi->vallen);
 *    printf("key = %s, value = %s\n", key, val);
 *    free(key);
 *    free(value);
 * }
 * \endcode
 *
 */
struct qsiter_t {
  const char* s;
  size_t pos;
  size_t len;

  const char* key;
  size_t keylen;

  const char* val;
  size_t vallen;
};


/**
 * Reset a qsiter to an initial start (constructor)
 *
 * This does not modifiy the original string, nor makes a copy.
 *
 * \param[out] qsi data struct used in iterator
 * \param[in] s input string (does not need to be 0-terminated)
 * \param[in] len input string length
 *
 */
void qsiter_reset(struct qsiter_t* qsi, const char* s, size_t len);

/**
 * Get next key/value pair in query string
 *
 * \param[out] qsi data struct
 * \return 1 if found a key value pair, 0 if no more data
 */
int qsiter_next(struct qsiter_t* qsi);

#include "extern_c_end.h"

#endif  /* MODP_QSITER */
