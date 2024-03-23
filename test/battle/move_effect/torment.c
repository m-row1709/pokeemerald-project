#include "global.h"
#include "test/battle.h"

ASSUMPTIONS
{
    ASSUME(gMovesInfo[MOVE_TORMENT].effect == EFFECT_TORMENT);
}

SINGLE_BATTLE_TEST("Torment prevents consecutive move uses")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET) { Moves(MOVE_SWORDS_DANCE, MOVE_CELEBRATE); }
    } WHEN {
        TURN { MOVE(player, MOVE_TORMENT); MOVE(opponent, MOVE_SWORDS_DANCE); }
        TURN { MOVE(opponent, MOVE_SWORDS_DANCE, allowed: FALSE); MOVE(opponent, MOVE_CELEBRATE); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_TORMENT, player);
        MESSAGE("Foe Wobbuffet was subjected to torment!");
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SWORDS_DANCE, opponent);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_CELEBRATE, opponent);
    }
}

SINGLE_BATTLE_TEST("Torment forces Struggle if the only move is prevented")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET) { Moves(MOVE_SWORDS_DANCE); }
    } WHEN {
        TURN { MOVE(player, MOVE_TORMENT); MOVE(opponent, MOVE_SWORDS_DANCE); }
        TURN { MOVE(opponent, MOVE_SWORDS_DANCE, allowed: FALSE); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SWORDS_DANCE, opponent);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_STRUGGLE, opponent);
    }
}

SINGLE_BATTLE_TEST("Torment allows non-consecutive move uses")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_TORMENT); MOVE(opponent, MOVE_SWORDS_DANCE); }
        TURN { MOVE(opponent, MOVE_CELEBRATE); }
        TURN { MOVE(opponent, MOVE_SWORDS_DANCE); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SWORDS_DANCE, opponent);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_CELEBRATE, opponent);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SWORDS_DANCE, opponent);
    }
}
