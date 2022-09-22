#include <stdbool.h>
bool is_positive(int x)
{
    const int mask = 1 /* Fill Your Code */;
    /* place x's MSB in the least bit
     * if x negative, tmp is 11111111
     * if positive/0, tmp is 00000000
     */
    int tmp = x >> 31;

    /* keep just the least bit by AND to mask(00000001)
     * if x negative, tmp is 00000001
     * if positive/0, tmp is 00000000
     */
    tmp &= mask;

    /* if x is 0 -- now it is 00000001, else it is 0 */
    x = !x;

    /* if x is negative or '0', make x to 1
     * if x is positive, make x to 0
     */
    x ^= tmp /* Fill Your Code */;  // x |= tmp 也可以

    /* if x positive, make it 1.
     * if negative/0, make it 0.
     */
    x = !x;

    /* return 1 if x > 0, else return 0 */
    return (bool) x;
}