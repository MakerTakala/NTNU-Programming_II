#include "madoka.h"
#include <stdio.h>
#include <string.h>


Entity *Entity_ctor(Entity *this) {
    this->hp = 100;
    this->is_dead = Entity_is_dead;
    return this;
}
void Entity_dtor(Entity *this) {
    return;
}
int Entity_is_dead(void *this){
    return ((Entity*)this)->hp <= 0;
}

Shoujo *Shoujo_ctor(Shoujo *this, const char *name, const char *wish) {
    Entity_ctor( &(this->base) );
    this->name = malloc(strlen(name) + 1);
    strcpy( this->name, name );
    this->wish = malloc(strlen(wish) + 1);
    strcpy( this->wish, wish );
    this->kimoji = 100;
    this->is_dead = Entity_is_dead;
    this->is_despair = Shoujo_is_despair;
    this->do_wish = Shoujo_do_wish;
    this->despair = Shoujo_despair;
    return this;
}
void Shoujo_dtor(Shoujo *this) {
    free( this->name );
    free( this->wish );
    Entity_dtor( &(this->base) );
    return;
}
int Shoujo_is_despair(void *this) {
    return ((Shoujo*)this)->kimoji <= -100;
}
void Shoujo_do_wish(void *this) {
    printf("%s\n", ((Shoujo*)this)->wish );
    return;
}
void Shoujo_despair(void *this) {
    ((Entity*)this)->hp = 0;
    return;
}

Mahoushoujo *Mahoushoujo_ctor(Mahoushoujo *this, const char *name, const char *wish, Skill skill) {
    Shoujo_ctor( &(this->base), name, wish );
    this->base.base.hp *= 3;
    this->atk = 100;
    this->is_dead = Entity_is_dead;
    this->do_wish = Mahoushoujo_do_wish;
    this->base.despair = Mahoushoujo_despair;
    this->attack = Mahoushoujo_attack;
    this->skill = skill;
    return this;
}
void Mahoushoujo_dtor(Mahoushoujo *this){
    Shoujo_dtor( &(this->base) );
    return;
}
void Mahoushoujo_do_wish(void *this) {
    Shoujo_do_wish(this);
    printf("But nothing is good.\n");
    ((Shoujo*)this)->kimoji -= 10;
    return;
}
void Mahoushoujo_attack(Mahoushoujo *this, Entity *enemy) {
    enemy->hp -= (this->atk);
    return;
}
void Mahoushoujo_despair(void *this) {
    printf("Watashii de, hondo baga\n");
    return;
}

Majo *Majo_ctor(Majo *this, const char *name, const char *wish) {
    Shoujo_ctor( &(this->base), name, wish );
    this->base.base.hp *= 50;
    ((Shoujo*)this)->despair = Majo_despair;
    this->atk = 10;
    this->is_dead = Entity_is_dead;
    this->attack = Majo_attack;
    this->kekkai = Majo_kekkai;
    return this;
}
void Majo_dtor(Majo *this) {
    Shoujo_dtor( &(this->base) );
    return;
}
void Majo_attack(Majo *this, Entity *enemy) {
    enemy->hp -= (this->atk);
    return;
}
void Majo_kekkai(Majo *this, Shoujo *sj) {
    sj->kimoji -= 100;
    return;
}
void Majo_despair(void *this) {
    return;
}

Majo *mhsj_to_mj(Mahoushoujo *mhsj) {
    Majo *mj = malloc( sizeof(Majo) );
    mj = Majo_ctor( mj, mhsj->base.name, mhsj->base.wish );
    Mahoushoujo_dtor(mhsj);
    return mj;
}

void Madoka_skill(void *this, void *target) {
    printf("Madoka become god, end.\n");
    exit(0);
    return;
}
void Homura_skill(void *this, void *target) {
    if( ((Entity*)this)->hp < 50 ) {
        printf("This round is hopeless, Homura go to next round.\n");
        exit(0);
    }
    return;
}
void Sayaka_skill(void *this, void *target) {
    ((Entity*)this)->hp += 30;
    ((Shoujo*)this)->kimoji -= 30;
    return;
}
void Kyoko_skill(void *this, void *target) {
    if( ((Shoujo*)target)->name == "Sayaka" ) {
        ((Entity*)this)->hp = 0;
        ((Entity*)target)->hp = 0;
    }
    return;
}