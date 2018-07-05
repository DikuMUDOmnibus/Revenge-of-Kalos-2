/* New Drows by Xkilla */
#if defined(macintosh)        
#include <types.h>
#else
#include <sys/types.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "merc.h"
#include "player.h"

/*
 * Local functions.
 */
void do_pledge( CHAR_DATA *ch, char *argument )
{
    char      arg [MAX_INPUT_LENGTH];
    argument = one_argument( argument, arg );
 
    if (IS_NPC(ch)) return;

    if (!IS_IMMUNE(ch, IMM_DROW))
    {
        send_to_char("You pledge yourself to the way of the Drow.\n\r",ch);
        SET_BIT(ch->immune, IMM_DROW);
        return;

    }
    send_to_char("You no longer pledge to the way of the Drow.\n\r",ch);
    REMOVE_BIT(ch->immune, IMM_DROW);
    return;
}

void do_inherit( CHAR_DATA *ch, char *argument )
{
    CHAR_DATA *victim;
    char      arg1 [MAX_INPUT_LENGTH];
    char      arg2 [MAX_INPUT_LENGTH];
    int       inherit = 0;
    int       cost = 0;

    smash_tilde(argument);
    argument = one_argument( argument, arg1 );
    argument = one_argument( argument, arg2 );

    if (IS_NPC(ch)) return;

    if (!IS_CLASS(ch, CLASS_DROWNEW))
    {
	    send_to_char("Huh?\n\r",ch);
	    return;
    }

    if ( arg1[0] == '\0' || arg2[0] == '\0' )
    {
	send_to_char( "Syntax: Inherit <person> <power>\n\r", ch );
	send_to_char("Foureyes - 1,000,000 exp.\n\r",ch);
	send_to_char("Toughen  - 10,000,000 exp.\n\r",ch);
        send_to_char("Offense  - 10,000,000 exp.\n\r",ch);   
	return;

    }

    if ( ( victim = get_char_world( ch, arg1 ) ) == NULL )
    {
	send_to_char( "Nobody by that name.\n\r", ch );
	return;
    }
	if (str_cmp(victim->clan,ch->clan) && ch->pcdata->stats[UNI_GEN] >1) {
		send_to_char("Only on your clan!.\n\r", ch );
		return;}

    if ( IS_NPC(victim) )
    {
	send_to_char( "Not on NPC's.\n\r", ch );
	return;
    }

    if ( victim->level != LEVEL_AVATAR)
    {
	send_to_char( "Only on an avatar.\n\r", ch );
	return;
    }

    if (!str_cmp(arg2,"foureyes")) 
	{inherit = DROW_FOUREYES; cost = 1000000;}
    else if (!str_cmp(arg2,"toughen"))
	{inherit = DROW_TOUGHEN;  cost = 10000000;}
    else if (!str_cmp(arg2,"offense"))
        {inherit = DROW_OFFENSE;  cost = 10000000;}
    else
    {
	send_to_char( "Syntax: Inherit <person> <power>\n\r", ch );
        send_to_char("Foureyes  - 1,000,000 exp.\n\r",ch);
        send_to_char("Toughen  - 10,000,000 exp.\n\r",ch);
        send_to_char("Offense  - 10,000,000 exp.\n\r",ch);
	send_to_char("\n\r",ch);
	return;
    }

    if (IS_SET(victim->xkilla->drows, inherit))
    {
	send_to_char("They have already got that power.\n\r",ch);
	return;
    }
    if (ch->exp < cost) 
    {
	send_to_char("You have insufficient power to grant that gift.\n\r",ch);
	return;
    }
    SET_BIT(victim->xkilla->drows, inherit);
    ch->exp -= cost;
    if (victim != ch) send_to_char("You have inherited a power.\n\r",victim);
    send_to_char("Ok.\n\r",ch);
    if (victim != ch) save_char_obj(ch);
    save_char_obj(victim);
    return; 
}


void do_infect(CHAR_DATA *ch, char *argument)
{
    CHAR_DATA *victim;
    char arg[MIL];

    argument = one_argument(argument, arg);

    if (IS_NPC(ch) || !IS_CLASS(ch, CLASS_DROWNEW) || ch->pcdata->stats[UNI_GEN]>2)
    {
	send_to_char("Huh?\r\n", ch);
	return;
    }
    if (arg[0] == '\0')
    {
	send_to_char("Infect who??\n\r", ch);
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

    if (!IS_IMMUNE(victim,IMM_DROW))
    {
        send_to_char( "They have not commited themself to the way of the Drow.\n\r", ch);
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
    victim->class = CLASS_DROWNEW;

    send_to_char("They are now a drow.\r\n", ch);
    send_to_char("You are now a drow.\r\n", victim);
    save_char_obj(ch);
    save_char_obj(victim);
    return;
}



void do_webtalk( CHAR_DATA *ch, char *argument )
{
    if (IS_NPC(ch) || (!IS_IMMORTAL(ch) && !IS_CLASS(ch,CLASS_DROWNEW)))
    {
        send_to_char("Huh?\n\r",ch);
        return;
    }
    talk_channel( ch, argument, CHANNEL_WEBTALK, "webtalk" );
    return;
}
void do_toughen( CHAR_DATA *ch, char *argument)
{
    if ( IS_NPC(ch) )
        return;
 
        if (!IS_CLASS(ch, CLASS_DROWNEW)) {
                send_to_char("Huh?\n\r", ch );
                return;}
 
        if (!IS_SET(ch->xkilla->drows, DROW_TOUGHEN))
        {
        send_to_char("You have not inherited the ability to toughen up.\n\r", ch );
        return;
        }
 
        if (IS_SET(ch->xkilla->plr, PLR_TOUGHEN))
        {
        REMOVE_BIT(ch->xkilla->plr, PLR_TOUGHEN);
        send_to_char( "You start to weaken yourself, and start to feel weak.\n\r", ch );
        }
        else
        {
        SET_BIT(ch->xkilla->plr, PLR_TOUGHEN);
        send_to_char( "You start to feel stronger as you toughen up..\n\r", ch );
        }
        return;
}
void do_foureyes( CHAR_DATA *ch, char *argument) 
{
    if ( IS_NPC(ch) )
        return;

        if (!IS_CLASS(ch, CLASS_DROWNEW)) {
                send_to_char("Huh?\n\r", ch );
                return;}

        if (!IS_SET(ch->xkilla->drows, DROW_FOUREYES)) 
	{
        send_to_char("You have not inherited the ability to use your four eyes yet.\n\r", ch ); 
        return;
	}

        if (IS_SET(ch->act, PLR_HOLYLIGHT)) 
	{
        REMOVE_BIT(ch->act, PLR_HOLYLIGHT);
        send_to_char( "Your four eyes suddenly start to fade away.\n\r", ch );
	}
        else 
	{
        SET_BIT(ch->act, PLR_HOLYLIGHT);
        send_to_char( "Four eyes emerge from your head in a instant.\n\r", ch );
        }
        return;                                                                       
}
