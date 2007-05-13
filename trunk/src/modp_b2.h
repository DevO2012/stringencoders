/* -*- mode: c++; c-basic-offset: 4; indent-tabs-mode: nil; tab-width: 4 -*- */
/* vi: set expandtab shiftwidth=4 tabstop=4: */

/**
 * \file
 * <PRE>
 * MODP_B2 -- Base 2 (binary) encode/decoder
 * http://code.google.com/p/stringencoders/
 *
 * Copyright &copy; 2007, Nick Galbreath -- nickg [at] modp [dot] com
 * All rights reserved.
 *
 * Released under bsd license.  See modp_b2.c for details.
 * </PRE>
 *
 */

#ifndef MODP_B2
#define MODP_B2

#ifdef __cplusplus
extern "C" {
#endif

/**
 * encode a string into binary (base 2, '0' and '1')
 *
 * \param[out] dest the output string.  Must have at least modp_b16_encode_len
 *   bytes allocated
 * \param[in] str the input string
 * \param[in] len of the input string
 * \return strlen of dest
 */
int modp_b2_encode(char* dest, const char* str, int len);

/**
 * Decode a hex-encoded string.
 *
 * \param[out] dest output, must have at least modp_b16_decode_len bytes allocated,
 *   input must be a mutliple of 2, and be different than the source buffer.
 * \param[in] src the hex encoded source
 * \param[in] len the length of the source
 * \return the length of the the output, or -1 if an error
 */
int modp_b2_decode(char* dest, const char* src, int len);

/**
 * Encode length.
 * 2 x the length of A, round up the next high mutliple of 2
 * +1 for null byte added
 */
#define modp_b2_encode_len(A) (8*A + 1)

/**
 * Encode string length
 */
#define modp_b2_encode_strlen(A) (8*A)

/**
 * Decode string length
 */
#define modp_b2_decode_len(A) ((A + 1)/ 8)

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
#include <string>

namespace modp {
/**
 * hex encode a string (self-modified)
 * \param[in,out] s the input string to be encoded
 * \return a reference to the input string.
 */
inline std::string& b16_encode(std::string& s)
{
    std::string x(modp_b2_encode_len(s.size()), '\0');
    int d = modp_b2_encode(const_cast<char*>(x.data()), s.data(), s.size());
    x.erase(d, std::string::npos);
    s.swap(x);
    return s;
}

/**
 * Decode a hex-encoded string.  On error, input string is cleared.
 * This function does not allocate memory.
 *
 * \param[in,out] s the input string
 * \return a reference to the input string
 */
inline std::string& b2_decode(std::string& s)
{
    int d = modp_b2_decode(const_cast<char*>(s.data()), s.data(), s.size());
    if (d < 0) {
        s.clear();
    } else {
        s.erase(d, std::string::npos);
    }
    return s;
}

} /* namespace modp */

#endif  /* ifdef __cplusplus */

#endif  /* ifndef modp_b16 */