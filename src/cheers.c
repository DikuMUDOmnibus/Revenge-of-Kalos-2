#include "include.h"


const char * weap_type	[MAX_WEAPTYPE] =
{
    "hit", "slice", "stab", "slash", "whip", "claw", "blast", "pound",
"crush", "grep", "bite", "pierce", "suck"
};

/*
void do_areastat(CHAR_DATA *ch, char *argument)
{
    AREA_DATA *pArea;

    if ( IS_NPC(ch) || !ch->in_room)
	return;
       
}
*/

void do_color(CHAR_DATA *ch, char *argument)
{
    if (IS_NPC(ch))
	return;
    if (IS_SET(ch->act, PLR_ANSI))
    {
	REMOVE_BIT(ch->act, PLR_ANSI);
	send_to_char("You color is off.\r\n", ch);
    }
    else
    {
	SET_BIT(ch->act, PLR_ANSI);
	send_to_char("You color is on.\r\n", ch);
    }
    return;
}
void do_hguide(CHAR_DATA *ch, char *argument)
{
    CHAR_DATA *victim;
    char arg[MIL];

    argument = one_argument(argument, arg);

    if (IS_NPC(ch) || !IS_CLASS(ch, CLASS_HIGHLANDER))
    {
	send_to_char("Huh?\r\n", ch);
	return;
    }
    if (arg[0] == '\0')
    {
	send_to_char("Hguide <person>\r\n", ch);
	return;
    }
    if (ch->wpn[1] < 1000)
    {
	send_to_char("You are not skilled enough to guide others.\r\n", ch);
	return;
    }
    if ( (victim = get_char_room(ch, arg) ) == NULL)
    {
	send_to_char("But they are not here!\r\n", ch);
	return;
    }

    if (victim == ch)
    {
	send_to_char("You cannot class yourself.\r\n", ch);
	return;
    }

    if (victim->level != LEVEL_AVATAR)
    {
	send_to_char("Only on avatars.\r\n", ch);
	return;
    }
    if (victim->class != 0)
    {
	send_to_char("They are already classed.\r\n", ch);
	return;
    }

    if (victim->exp < 500000)
    {
	send_to_char("They do not have the 500,000 exp to be classed.\r\n", ch);
	send_to_char("You do not have 500,000 exp to be classed.\r\n", victim);
	return;
    }
    victim->exp -= 500000;
    victim->class = CLASS_HIGHLANDER;

    send_to_char("They are now a highlander.\r\n", ch);
    send_to_char("You are now a highlander.\r\n", victim);
    save_char_obj(ch);
    save_char_obj(victim);
    return;
}
