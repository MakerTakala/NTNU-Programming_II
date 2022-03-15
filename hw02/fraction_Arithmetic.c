

typedef struct _sMixedNumber {
}sMixedNumber;

void mixed_add( sMixedNumber *pNumber , const sMixedNumber r1, const
sMixedNumber r2);
// pNumber = r1 + r2
void mixed_sub( sMixedNumber *pNumber , const sMixedNumber r1, const
sMixedNumber r2);
// pNumber = r1 - r2
void mixed_mul( sMixedNumber *pNumber , const sMixedNumber r1, const
sMixedNumber r2);
// pNumber = r1 * r2
void mixed_div( sMixedNumber *pNumber , const sMixedNumber r1, const
sMixedNumber r2);
// pNumber = r1 / r2