#if defined(macintosh)
#include <types.h>
#else
#include <sys/types.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "player.h"
#include "rok.h"


/************* NOT FINISHED ******************/
cheerios

/* Mummies?
   Ideas Only:
1. low offense, high defense. (parry/dodge)
2. better fighting ability in desert area...
3. rot. -???
4. Ra.  - offense power.
-5. engulf. - uses sand to attack, only in desert..
-6. wrap. - damage command.
-7. creep. - hide?
8. protection - damage protection. (25%)
-9. resurrect - regen.
10. shadowplane - can enter/leave shadowplane
11. life of the immortals - damage resistance (again) (50%)
12. Stealth/Speed

more to come... (hopefully)

*/

/*
void do_mummygain(CHAR_DATA *ch, char *argument)
{
}
*/

/*
void do_mummify(CHAR_DATA *ch, char *argument)
{
    CHAR_DATA *victim;
    char arg[MAX_STRING_LENGTH];
    char buf[MAX_STRING_LENGTH];

    argument = one_argument (argument, arg);

    if (( victim = get_char_room(ch, arg)) == NULL)
    {
	send_to_char("They are not here.\r\n", ch);
	return;
    }

    if (victim->class != 0)
    {
	send_to_char("But they are already classed.\r\n", ch);
	return;
    }

    act("You place your hands upon $N and chants some ancient words.", ch,
NULL, victim, TO_CHAR);
    act("$N's flesh begins to crisp, slowly rotting, until bones are
left.", ch, NULL, victim, TO_CHAR);
    act("Mum
    victim->class = CLASS_MUMMY;

    save_char_obj(ch);
    save_char_obj(victim);
    return;
}
*/
void do_resurrect(CHAR_DATA *ch, char *argument)
{
    if (!IS_CLASS(ch, CLASS_MUMMY) || IS_NPC(ch))
    {
	send_to_char("Huh?\r\n", ch);
	return;
    }
    werewolf_regen(ch);
    reg_mend(ch);
    if (ch->hit < ch->max_hit || ch->mana < ch->max_mana ||
		ch->move < ch->max_move)
	send_to_char("You body slowly resurrects.\r\n", ch);
    return;
}

void do_creep(CHAR_DATA *ch, char *argument)
{
    if (!IS_CLASS(ch, CLASS_MUMMY) || IS_NPC(ch))
    {
	send_to_char("Huh?\r\n", ch);
	return;
    }
    if (IS_SET(ch->act, PLR_WIZINVIS))
    {
	REMOVE_BIT(ch->act, PLR_WIZINVIS);
	send_to_char("You will no longer creep in silence.\r\n", ch);
	return;
    }
    else
    {
	SET_BIT(ch->act, PLR_WIZINVIS);
	send_to_char("You will now creep in silence.\r\n", ch);
	return;
    }
    return;
}

void do_engulf(CHAR_DATA *ch, char *argument)
{
    int dam = 0;
    CHAR_DATA *victim;

    if (!IS_CLASS(ch, CLASS_MUMMY) || IS_NPC(ch))
    {
	send_to_char("Huh?\r\n", ch);
	return;
    }
    if (ch->fighting == NULL)
    {
	send_to_char("But you are not fighting.\r\n", ch);
	return;
    }

    if (ch->in_room->sector_type != SECT_DESERT)
    {
	send_to_char("Only in the desert will you be able to engulf.\r\n", ch);
	return;
    }

    victim = ch->fighting;

    dam = number_range( 10, 20);
    dam += char_damroll(ch);
    dam += get_age(ch);
//  dam += ch->pcdata->stats[MUMMY_AGE];

    if (IS_AFFECTED(victim, AFF_SANCTUARY) )
	dam *= 0.5;

    act("A sandstorm rises, engulfing $N.", ch, victim, NULL, TO_CHAR);
    act("A sandstorm creeps towards, engulfing you into the center.", ch, NULL, victim, TO_VICT);
    act("A sandstorm appears out of nowhere, engulfing $N into it.", ch, NULL, victim, TO_ROOM);

    hurt_person(ch, victim, dam);
    return;
}


void do_wrap(CHAR_DATA *ch, char *argument)
{
    int dam = 0;
    CHAR_DATA *victim;

    if (!IS_CLASS(ch, CLASS_MUMMY) || IS_NPC(ch))
    {
	send_to_char("But you have no wrappings.\r\n", ch);
	return;
    }

    if (ch->fighting == NULL)
    {
	send_to_char("You are not fighting.\r\n", ch);
	return;
    }

    victim = ch->fighting;

    dam = number_range( 10, 20);
    dam += char_damroll(ch);
    dam += get_age(ch);
//  dam += ch->pcdata->stats[MUMMY_AGE];

    if (IS_AFFECTED(victim, AFF_SANCTUARY ) )
	dam *= 0.5;

    hurt_person(ch, victim, dam);
   
    send_to_char("You let your wrappings fly, striking your opponent\r\n", ch);
    act("You hear a painful cry as $n's wrapping strikes $N", ch, victim, NULL, TO_ROOM);
    act("You tried to dodge $n's wrappings, but failed.", ch, NULL, NULL, TO_VICT);
    return;
}


