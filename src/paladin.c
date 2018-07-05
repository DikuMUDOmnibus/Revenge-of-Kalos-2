/***************************************************************************
 *  Original Diku Mud copyright (C) 1990, 1991 by Sebastian Hammer,        *
 *  Michael Seifert, Hans Henrik St{rfeldt, Tom Madsen, and Katja Nyboe.   *
 *                                                                         *
 *  Merc Diku Mud improvments copyright (C) 1992, 1993 by Michael          *
 *  Chastain, Michael Quan, and Mitchell Tse.                              *
 *                                                                         *
 *  In order to use any part of this Merc Diku Mud, you must comply with   *
 *  both the original Diku license in 'license.doc' as well the Merc       *
 *  license in 'license.txt'.  In particular, you may not remove either of *
 *  these copyright notices.                                               *
 *                                                                         *
 *  Much time and thought has gone into this software and you are          *
 *  benefitting.  We hope that you share your changes too.  What goes      *
 *  around, comes around.                                                  *
 ***************************************************************************/

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
  
void do_aura( CHAR_DATA *ch, char *argument )
{
    char      arg1 [MAX_INPUT_LENGTH];
    int       aura = 0;
    int       cost = 0;

    smash_tilde(argument);
    argument = one_argument( argument, arg1 );

    if (IS_NPC(ch)) return;

	if (!IS_CLASS(ch, CLASS_PALADIN))
	{
	send_to_char( "Huh?\n\r", ch);
	return;
	}
	
	if ( arg1[0] == '\0' )
    {
	send_to_char( "Syntax: Aura <power>\n\r", ch );
	send_to_char("Scry (2000), Charge (3000), HolyBless (5000), Joust (2000),\n\r",ch);
	send_to_char("SpeedBlows (4000), HolyToughness (4000).\n\r", ch);
	return;
    }
    
    
    if (!str_cmp(arg1,"scry")) 
	{aura = PALADIN_SCRY; cost = 0;}
    else if (!str_cmp(arg1,"charge")) 
	{aura = PALADIN_CHARGE; cost = 0;}
    else if (!str_cmp(arg1,"speedblows")) 
	{aura = PALADIN_SPEED; cost = 0;}
	else if (!str_cmp(arg1,"holytoughness")) 
	{aura = PALADIN_TOUGHNESS; cost = 0;}
    else if (!str_cmp(arg1,"holybless")) 
	{aura = PALADIN_HOLYBLESS; cost = 0;}
	else if (!str_cmp(arg1, "joust"))
	{aura = PALADIN_JOUST; cost = 0;}
    else
    {
	send_to_char( "Syntax: Aura <power>\n\r", ch );
	send_to_char("Scry (2000), Charge (3000), HolyBless (5000), Joust (2000),\n\r",ch);
	send_to_char("SpeedBlows (4000), HolyToughness (4000).\n\r", ch);
	return;
    }
	
	if (IS_PPOWER(ch, aura))
    {
	send_to_char("You already have that power.\n\r",ch);
	return;
    }
    if (ch->pcdata->stats[PALADIN_TOTAL] < cost || 
	ch->pcdata->stats[PALADIN_CURRENT] < cost)
    {
	send_to_char("You have insufficient aura points to give yourself that power.\n\r",ch);
	return;
    }
    SET_BIT(ch->pcdata->powers[PPOWER_FLAGS], aura);
    ch->pcdata->stats[PALADIN_TOTAL]   -= cost;
    ch->pcdata->stats[PALADIN_CURRENT] -= cost;
    send_to_char( "Ok.\n\r", ch);
    save_char_obj(ch);
    return;
}

/* Paladin Clan List - Loki */
void do_pclan( CHAR_DATA *ch, char *argument )
{
    char buf[MAX_STRING_LENGTH];
    char arg[MAX_INPUT_LENGTH];
    CHAR_DATA *gch;

    one_argument( argument, arg );

    if (IS_NPC(ch)) return;
    if (!IS_CLASS(ch, CLASS_PALADIN))
    {
	send_to_char("Huh?\n\r",ch);
	return;
    }

    send_to_char("(:     Name     :) (:Hits  %:) (:Mana  %:) (:Move  %:) (: Exp :)\n\r", ch );
    for ( gch = char_list; gch != NULL; gch = gch->next )
    {
	if ( IS_NPC(gch) ) continue;
	if ( !IS_CLASS(gch, CLASS_PALADIN) ) continue;
	if ( strlen(gch->clan) > 16) continue; 
	if ( gch->clan != NULL/* && strlen(gch->clan) > 1*/ )
	{ /* (:%7d:) */
	    sprintf( buf,
	    "(%-16s) (%-6d%3d) (%-6d%3d) (%-6d%3d) (%7d)\n\r",
	    capitalize( gch->name ),
		gch->hit,  (gch->hit  * 100 / gch->max_hit ),
		gch->mana, (gch->mana * 100 / gch->max_mana),
		gch->move, (gch->move * 100 / gch->max_move),
		gch->exp);
		send_to_char( buf, ch );
	}
    }
    return;
}

    
        
