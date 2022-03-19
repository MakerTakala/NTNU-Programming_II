#include "madoka.h"
#include <stdio.h>


Entity *Entity_ctor(Entity *this) {
    if( this == NULL ) {
        return NULL;
    }
    this->hp = 100;
    this->is_dead = Entity_is_dead;
    return this;
}
void Entity_dtor(Entity *this) {
    if( this == NULL ) {
        return;
    }
    free(this);
    return;
}
int Entity_is_dead(void *this){
    if( this == NULL ) {
        return -1;
    }
    return ((Entity*)this)->hp <= 0;
}

Shoujo *Shoujo_ctor(Shoujo *this, const char *name, const char *wish) {
    if(this == NULL || name == NULL || wish == NULL) {
        return NULL;
    }
    Entity_ctor( &(this->base) );
    this->name = (char*)name;
    this->wish = (char*)wish;
    this->kimoji = 100;
    this->is_dead = Entity_is_dead;
    this->is_despair = Shoujo_is_despair;
    this->do_wish = Shoujo_do_wish;
    this->despair = Shoujo_despair;
    return this;
}
void Shoujo_dtor(Shoujo *this) {
    if( this == NULL ) {
        return;
    }
    free(this);
    return;
}
int Shoujo_is_despair(void *this) {
    if( this == NULL ) {
        return -1;
    }
    return ((Shoujo*)this)->kimoji <= -100;
}
void Shoujo_do_wish(void *this) {
    if( this == NULL ) {
        return;
    }
    printf("wish\n");
    return;
}
void Shoujo_despair(void *this) {
    if( this == NULL ) {
        return;
    }
    ((Shoujo*)this)->kimoji = 0;
    return;
}

Mahoushoujo *Mahoushoujo_ctor(Mahoushoujo *this, const char *name, const char *wish, Skill skill) {
    if( this == NULL || name == NULL || skill == NULL ) {
        return NULL;
    }
    Shoujo_ctor( &(this->base), name, wish );
    ((Entity*)this)->hp *= 3;
    this->atk = 100;
    this->is_dead = Entity_is_dead;
}
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