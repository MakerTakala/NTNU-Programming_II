#pragma once

#include "madoka.h"

Entity *Entity_ctor(Entity *this) {
    
}
void Entity_dtor(Entity *this);
int Entity_is_dead(void *this);

Shoujo *Shoujo_ctor(Shoujo *this, const char *name, const char *wish);
void Shoujo_dtor(Shoujo *this);
int Shoujo_is_despair(void *this);
void Shoujo_do_wish(void *this);
void Shoujo_despair(void *this);

Mahoushoujo *Mahoushoujo_ctor(Mahoushoujo *this, const char *name, const char *wish, Skill skill);
void Mahoushoujo_dtor(Mahoushoujo *this);
void Mahoushoujo_do_wish(void *this);
void Mahoushoujo_attack(Mahoushoujo *this, void *enemy);
void Mahoushoujo_despair(void *this);

Majo *Majo_ctor(Majo *this, const char *name, const char *wish);
void Majo_dtor(Majo *this);
void Majo_attack(Majo *this, void *enemy);
void Majo_kekkai(Majo *this, Shoujo *sj);
void Majo_despair(void *this);

Majo *mhsj_to_mj(Mahoushoujo *mhsj);

void Madoka_skill(void *this, void *target);
void Homura_skill(void *this, void *target);
void Sayaka_skill(void *this, void *target);
void Kyoko_skill(void *this, void *target);