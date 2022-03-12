#pragma once

typedef struct
{
    int hp;
    int (*is_dead)(void *);
} Entity;

typedef struct
{
    Entity base;
    char *name;
    char *wish;
    int kimoji;
    int (*is_dead)(void *);
    int (*is_despair) (void *);
    void (*do_wish) (void *);
    void (*despair) (void *);
} Shoujo;

typedef void (*Skill) (void *, void *);

typedef struct _mhsj Mahoushoujo;
struct _mhsj
{
    Shoujo base;
    int atk;
    int (*is_dead)(void *);
    void (*do_wish) (void *);
    void (*attack) (Mahoushoujo *, Entity *);
    Skill skill;
};


typedef struct _mj Majo;
struct _mj
{
    Shoujo base;
    int atk;
    int (*is_dead)(void *);
    void (*attack) (Majo *, Entity *);
    void (*kekkai) (Majo *, Shoujo *);
};

Entity *Entity_ctor(Entity *);
void Entity_dtor(Entity *);
int Entity_is_dead(void *);

Shoujo *Shoujo_ctor(Shoujo *, const char *, const char *);
void Shoujo_dtor(Shoujo *);
int Shoujo_is_despair(void *);
void Shoujo_do_wish(void *);
void Shoujo_despair(void *);

Mahoushoujo *Mahoushoujo_ctor(Mahoushoujo *, const char *, const char *, Skill );
void Mahoushoujo_dtor(Mahoushoujo *);
void Mahoushoujo_do_wish(void *);
void Mahoushoujo_attack(Mahoushoujo *, void *);
void Mahoushoujo_despair(void *);

Majo *Majo_ctor(Majo *, const char *name, const char *wish);
void Majo_dtor(Majo *);
void Majo_attack(Majo *, void *enemy);
void Majo_kekkai(Majo *, Shoujo *sj);
void Majo_despair(void *);

Majo *mhsj_to_mj(Mahoushoujo *mhsj);

void Madoka_skill(void *, void *target);
void Homura_skill(void *, void *target);
void Sayaka_skill(void *, void *target);
void Kyoko_skill(void *, void *target);

#include <stdlib.h>
#include <stddef.h>
