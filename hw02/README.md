# Homework02 4104702S 王重鈞

Use "make" to compile all program file

## 2.1 Wildcard Matching
---
mymatch - split pStr by white space then compare str if match pPattern
mymatch(char ***pppList , const char *pStr, const char *pPattern);

## 2.2 IEEE 754
---
Input a double precision and the program will print number with 2 base.
And show the detail of number.

## 2.3 Puella Magi Madoka Magica
---
Entity_ctor - creat a Entity
Entity *Entity_ctor(Entity *this);

Entity_dtor - delete a Entity
void Entity_dtor(Entity *this);

Entity_is_dead - detect if Entity is dead
int Entity_is_dead(void *this);

Shoujo_ctor - creat a Shoujo
Shoujo *Shoujo_ctor(Shoujo *this, const char *name, const char *wish);

Shoujo_dtor - delete a Shoujo
void Shoujo_dtor(Shoujo *this);

Shoujo_is_dead - detect if Shoujo is dead
int Shoujo_is_despair(void *this);

Shoujo_do_wish - Shoujo do a wish
void Shoujo_do_wish(void *this);

Shoujo_despair - shoujo become despair
void Shoujo_despair(void *this);

Mahoushoujo_ctor_ctor - creat a Mahoushoujo_ctor
Mahoushoujo *Mahoushoujo_ctor(Mahoushoujo *this, const char *name, const char *wish, Skill skill);

Mahoushoujo_dtor - delete a Mahoushoujo
void Mahoushoujo_dtor(Mahoushoujo *this);

Mahoushoujo_do_wish - Mahoushoujo do a wish
void Mahoushoujo_do_wish(void *this);

Mahoushoujo_attack - Mahoushoujo attack enemy
void Mahoushoujo_attack(Mahoushoujo *this, Entity *enemy);

Mahoushoujo_despair - Mahoushoujo become despair
void Mahoushoujo_despair(void *this);

Majo_ctor - creat a Majo
Majo *Majo_ctor(Majo *this, const char *name, const char *wish);

Majo_dtor - delete a Majo
void Majo_dtor(Majo *this);

Majo_attack - Majo attack enemy
void Majo_attack(Majo *this, Entity *enemy);

Majo_kekkai - Majo use kekkai to shoujo
void Majo_kekkai(Majo *this, Shoujo *sj);

Majo_despair - Majo become despair
void Majo_despair(void *this);

Madoka_skill - Madoka use skill
void Madoka_skill(void *this, void *target);

Homura_skill - Homura use skill
void Homura_skill(void *this, void *target);

Sayaka_skill - Sayaka use skill
void Sayaka_skill(void *this, void *target);

Kyoko_skill - Kyoko use skill
void Kyoko_skill(void *this, void *target);

## 2.4 Mixed Fraction Arithmetic
---
Counting Fraction Arithmetic.

## 2.5 Vector
---
myvector_init - init vector
sVector *myvector_init();

myvector_set - set vector
int myvector_set( sVector *pVector , uint8_t type, double a, double b );

myvector_print - print vector data
int myvector_print( const sVector *pVector , uint8_t type );

myvector_add - add two vectors
int myvector_add( sVector *pA, const sVector *pB, const sVector *pC );

myvector_inner_product - inner product two vectors
int myvector_inner_product( double *pA, const sVector *pB, const sVector *pC );

myvector_area - count Area with two vectors
int myvector_area( double *pArea , const sVector *pB, const sVector *pC );

myvector_cvp - find cloest point(pX, pY) to point(pTX, pTY)
int myvector_cvp( double *pX, double *pY, const double *pTx, const double *pTy, const sVector *pA, const sVector *pB );