typedef unsigned float_bits;
int float_to_int(float_bits f);

static inline float u2f(unsigned u)
{
    return *(float *) &u;
}

int float_to_int(float_bits f)
{
    const unsigned sign = f >> 31;
    const unsigned exp = f >> 23 /* Fill Your Code */ & 0xFF;
    const unsigned frac = f & 0x7FFFFF /* Fill Your Code */;
    const unsigned bias = 0x7F;
    int result;

    if (exp < bias) {
        /* the float number is less than 1 */
        result = 0;
    } else if (exp >= 31 + bias) {
        /* overflow */
        result = 0x80000000;
    } else {
        /* normal */
        unsigned E = exp - bias;
        unsigned M = frac | 0x800000;   // M 是為了無條件進位
        if (E > 23 /* Fill Your Code */) {
            result = M << (E - 23) /* Fill Your Code */;
        } else {
            /* round to zero */
            result = M >> (23 - E) /* Fill Your Code */;
        }
    }
    return sign ? -result : result;
}