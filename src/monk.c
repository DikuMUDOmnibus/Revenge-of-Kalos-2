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

void do_stab( CHAR_DATA *ch, char *argument )
{
    CHAR_DATA *victim;
    char      arg [MAX_INPUT_LENGTH];

    argument = one_argument( argument, arg );

    if (IS_NPC(ch)) return;

    if (!IS_CLASS(ch, CLASS_REVNANT) )
    {
        send_to_char("Huh?\n\r",ch);
	return;
    }

    if ( arg[0] == '\0' )
    {
        send_to_char( "Whom do you wish to curse to undead existance?\n\r", ch );
	return;
    }
    
    if ( ( victim = get_char_room( ch, arg ) ) == NULL )
    {
	send_to_char( "They aren't here.\n\r", ch );
	return;
    }

    if ( IS_NPC(victim) )
    {
	send_to_char( "Not on NPC's.\n\r", ch );
	return;
    }

    if ( IS_IMMORTAL(victim) )
    {
        send_to_char( "They exist outside the world of life and death.\n\r", ch );
	return;
    }

    if ( ch == victim )
    {
        send_to_char( "You cannot grant yourself live after death.\n\r", ch );
	return;
    }

    if (IS_CLASS(victim, CLASS_REVNANT))
    {
        send_to_char( "They have already risen from their death.\n\r", ch );
	return;
    }

    if ( victim->level != LEVEL_AVATAR && !IS_IMMORTAL(victim) )
    {
        send_to_char( "Only Avatars can rise from the dead.\n\r", ch );
	return;
    }

    if (IS_CLASS(victim, CLASS_VAMPIRE) || IS_SET(victim->pcdata->stats[UNI_AFF], VAM_MORTAL))
    {
        send_to_char( "You cannot grant a Vampire revnant life.\n\r", ch );
	return;
    }

    if (IS_CLASS(victim, CLASS_WEREWOLF))
    {
        send_to_char( "You cannot grant a Werewolf revnant life.\n\r", ch );
	return;
    }

    if (IS_CLASS(victim, CLASS_DEMON) || IS_SET(victim->special, SPC_CHAMPION))
    {
        send_to_char( "You cannot grant a Demon revnant life.\n\r", ch );
	return;
    }

    if (IS_CLASS(victim, CLASS_HIGHLANDER))
    {
        send_to_char( "You cannot grant a Highlander revnant life.\n\r", ch );
	return;
    }  

	if (IS_CLASS(victim, CLASS_NINJA))
	{
        send_to_char( "You cannot grant a Ninja revnant life.\n\r", ch );
	return;
	}

    if (!IS_IMMUNE(victim,IMM_VAMPIRE))
    {
        send_to_char( "They are unwilling to pass to the other side.\n\r", ch );
	return;
    }

    if (ch->exp < 1000000)
    {
        send_to_char("You cannot afford the #31,000,000#8 exp required to give them eternal life.\n\r",ch);
	return;
    }

    if (victim->exp < 1000000)
    {
        send_to_char("They cannot afford the #31,000,000#8 exp required to rise from their death.\n\r",ch);
	return;
    }

    ch->exp -= 1000000;
    victim->exp -= 1000000;

    act("You deal $N a fatal blow and watch as his spirit begins to form.", ch, NULL, victim, TO_CHAR);
    act("$n stabs $N killing him in cold blood.", ch, NULL, victim, TO_NOTVICT);
    act("$n fatally stabs you in the heart with a Revnant claw.", ch, NULL, victim, TO_VICT);
    victim->level = LEVEL_REVNANT;
    victim->trust = LEVEL_REVNANT;
    send_to_char( "You rise from your death and stand before your grave.\n\r", victim );
    free_string(victim->lord);
    free_string(victim->clan);
    victim->clan=str_dup(ch->clan);
    victim->lord = str_dup(ch->name);
    victim->class    = CLASS_REVNANT;
    victim->pcdata->stats[UNI_GEN] = ch->pcdata->stats[UNI_GEN]+1;
    save_char_obj(ch);
    save_char_obj(victim);
    return;
}

void do_mourn( CHAR_DATA *ch, char *argument )
{
    char arg1 [MAX_INPUT_LENGTH];
    char buf[MAX_STRING_LENGTH];
    int improve;
    improve = PMONK; 
    
    argument = one_argument( argument, arg1 );
    
    if (IS_NPC(ch)) return;

    if (!IS_CLASS(ch, CLASS_REVNANT))
    {
	send_to_char("Huh?\n\r",ch);
	return;
    }

    if (arg1[0] == '\0')
    {
	    send_to_char("     Your undead powers are:\n\r",ch);
	    send_to_char("- Remember to put single quotes ( ' ) around the power.\n\r", ch);
            if ( ch->pcdata->powers[PMONK] == 0 ) 
	    {
		send_to_char("#lImmortal Eyes.\n\r", ch);
		send_to_char("#lSpying crow\n\r", ch);
		send_to_char("#lCold hands  #1or  #lIron fists\n\r", ch);
		send_to_char("#lSkin of the Grave\n\r", ch);	    
	    	send_to_char("#lGrave travel   #1or   #lMysterious shroud\n\r", ch);
		send_to_char("#lLimbo Scythe   #1or   #lChilling scream\n\r", ch);
	    }
            if ( ch->pcdata->powers[PMONK] == 1 )
   	    {
	        send_to_char("#4Immortal eyes\n\r", ch);
		send_to_char("#lSpying crow\n\r", ch);
		send_to_char("#lCold hands  #1or  #lIron fists\n\r", ch);
		send_to_char("#lSkin of the Grave\n\r", ch);	    
	    	send_to_char("#lGrave travel   #1or   #lMysterious shroud\n\r", ch);
		send_to_char("#lLimbo Scythe   #1or   #lChilling scream\n\r", ch);
	    }
            if ( ch->pcdata->powers[PMONK] == 2 )
            {
                send_to_char("#4Immortal eyes\n\r", ch);
		send_to_char("#4Spying crow\n\r", ch);
		send_to_char("#lCold hands  #1or  #lIron fists\n\r", ch);
		send_to_char("#lSkin of the Grave\n\r", ch);
		send_to_char("#lGrave travel   #1or   #lMysterious shroud\n\r", ch);
		send_to_char("#lLimbo Scythe   #1or   #lChilling scream\n\r", ch);
            }
            if ( ch->pcdata->powers[PMONK] == 3 )
	    {
        	send_to_char("#4Immortal eyes\n\r", ch);
		send_to_char("#4Spying crow\n\r", ch);
		send_to_char("#4Cold Hands\n\r", ch);
		send_to_char("#lSkin of the Grave\n\r", ch);
		send_to_char("#lGrave travel   #1or   #lMysterious shroud\n\r", ch);
		send_to_char("#lLimbo Scythe   #1or   #lChilling scream\n\r", ch);
	    }
            if ( ch->pcdata->powers[PMONK] == 4 )
	    {
        	send_to_char("#4Immortal eyes\n\r", ch);
		send_to_char("#4Spying crow\n\r", ch);
		send_to_char("#4Iron Fists\n\r", ch);
		send_to_char("#lSkin of the Grave\n\r", ch);
		send_to_char("#lGrave travel   #1or   #lMysterious shroud\n\r", ch);
		send_to_char("#lLimbo Scythe   #1or   #lChilling scream\n\r", ch);
	    }
            if ( ch->pcdata->powers[PMONK] == 5 )
	    {
		send_to_char("#4Immortal eyes\n\r", ch);
		send_to_char("#4Spying crow\n\r", ch);
		send_to_char("#4Cold Hands\n\r", ch);
		send_to_char("#4Skin of the Grave\n\r", ch);
		send_to_char("#lGrave travel   #1or   #lMysterious shroud\n\r", ch);
		send_to_char("#lLimbo Scythe   #1or   #lChilling scream\n\r", ch);
	    }
            if ( ch->pcdata->powers[PMONK] == 6 )
	    {
		send_to_char("#4Immortal eyes\n\r", ch);
		send_to_char("#4Spying crow\n\r", ch);
		send_to_char("#4Iron fists\n\r", ch);
		send_to_char("#4Skin of the Grave\n\r", ch);
		send_to_char("#lGrave travel   #1or   #lMysterious shroud\n\r", ch);
		send_to_char("#lLimbo Scythe   #1or   #lChilling scream\n\r", ch);
	    }
            if ( ch->pcdata->powers[PMONK] == 7 )
	    {
		send_to_char("#4Immortal eyes\n\r", ch);
		send_to_char("#4Spying crow\n\r", ch);
		send_to_char("#4Cold Hands\n\r", ch);
		send_to_char("#4Skin of the Grave\n\r", ch);
		send_to_char("#4Grave travel\n\r", ch);
		send_to_char("#lLimbo Scythe   #1or   #lChilling scream\n\r", ch);
	    }
            if ( ch->pcdata->powers[PMONK] == 8 )
	    {
		send_to_char("#4Immortal eyes\n\r", ch);
		send_to_char("#4Spying crow\n\r", ch);
		send_to_char("#4Iron fists\n\r", ch);
		send_to_char("#4Skin of the Grave\n\r", ch);
		send_to_char("#4Grave travel\n\r", ch);
		send_to_char("#lLimbo Scythe   #1or   #lChilling scream\n\r", ch);
	    }
            if ( ch->pcdata->powers[PMONK] == 9 )
	    {
		send_to_char("#4Immortal eyes\n\r", ch);
		send_to_char("#4Spying crow\n\r", ch);
		send_to_char("#4Cold hands\n\r", ch);
		send_to_char("#4Skin of the Grave\n\r", ch);
		send_to_char("#4Mysterious shroud\n\r", ch);
		send_to_char("#lLimbo Scythe   #1or   #lChilling scream\n\r", ch);
	    }
            if ( ch->pcdata->powers[PMONK] == 10 )
	    {
		send_to_char("#4Immortal eyes\n\r", ch);
		send_to_char("#4Spying crow\n\r", ch);
		send_to_char("#4Iron fists\n\r", ch);
		send_to_char("#4Skin of the Grave\n\r", ch);
		send_to_char("#4Mysterious shroud\n\r", ch);
		send_to_char("#lLimbo Scythe   #1or   #lChilling scream\n\r", ch);
	    }
            if ( ch->pcdata->powers[PMONK] == 11 )
	    {
		send_to_char("#4Immortal eyes\n\r", ch);
		send_to_char("#4Spying crow\n\r", ch);
		send_to_char("#4Cold Hands\n\r", ch);
		send_to_char("#4Skin of the Grave\n\r", ch);
		send_to_char("#4Grave Travel\n\r", ch);
		send_to_char("#4Limbo Scythe\n\r", ch);
	    }
            if ( ch->pcdata->powers[PMONK] == 12 )
	    {
		send_to_char("#4Immortal eyes\n\r", ch);
		send_to_char("#4Spying crow\n\r", ch);
		send_to_char("#4Iron fists\n\r", ch);
		send_to_char("#4Skin of the Grave\n\r", ch);
		send_to_char("#4Grave Travel\n\r", ch);
		send_to_char("#4Limbo Scythe\n\r", ch);
	    }
            if ( ch->pcdata->powers[PMONK] == 13 )
	    {
		send_to_char("#4Immortal eyes\n\r", ch);
		send_to_char("#4Spying crow\n\r", ch);
		send_to_char("#4Cold Hands\n\r", ch);
		send_to_char("#4Skin of the Grave\n\r", ch);
		send_to_char("#4Mysterious shroud\n\r", ch);
		send_to_char("#4Limbo Scythe\n\r", ch);
	    }
            if ( ch->pcdata->powers[PMONK] == 14 )
	    {
		send_to_char("#4Immortal eyes\n\r", ch);
		send_to_char("#4Spying crow\n\r", ch);
		send_to_char("#4Iron fists\n\r", ch);
		send_to_char("#4Skin of the Grave\n\r", ch);
		send_to_char("#4Mysterious shroud\n\r", ch);
		send_to_char("#4Limbo Scythe\n\r", ch);
	    }
            if ( ch->pcdata->powers[PMONK] == 15 )
	    {
		send_to_char("#4Immortal eyes\n\r", ch);
		send_to_char("#4Spying crow\n\r", ch);
		send_to_char("#4Cold hands\n\r", ch);
		send_to_char("#4Skin of the Grave\n\r", ch);
		send_to_char("#4Grave travel\n\r", ch);
		send_to_char("#4Chilling Scream\n\r", ch);
	    }
            if ( ch->pcdata->powers[PMONK] == 16 )
	    {
		send_to_char("#4Immortal eyes\n\r", ch);
		send_to_char("#4Spying crow\n\r", ch);
		send_to_char("#4Iron fists\n\r", ch);
		send_to_char("#4Skin of the Grave\n\r", ch);
		send_to_char("#4Grave travel\n\r", ch);
		send_to_char("#4Chilling scream\n\r", ch);
	    }
            if ( ch->pcdata->powers[PMONK] == 17 )
	    {
		send_to_char("#4Immortal eyes\n\r", ch);
		send_to_char("#4Spying crow\n\r", ch);
		send_to_char("#4Cold hands\n\r", ch);
		send_to_char("#4Skin of the Grave\n\r", ch);
		send_to_char("#4Mysterious shroud\n\r", ch);
		send_to_char("#4Chilling scream\n\r", ch);
	    }
            if ( ch->pcdata->powers[PMONK] == 18 )
	    {
		send_to_char("#4Immortal eyes\n\r", ch);
		send_to_char("#4Spying crow\n\r", ch);
		send_to_char("#4Iron fists\n\r", ch);
		send_to_char("#4Skin of the Grave\n\r", ch);
		send_to_char("#4Mysterious shroud\n\r", ch);
		send_to_char("#4Chilling scream\n\r", ch);
	    }
	    return;
    }


	if (!str_cmp(arg1,"immortal eyes")) 
    {
    	if ( ch->pcdata->powers[PMONK] > 0 )
    		send_to_char("#6Immortal eyes are your spoil already.\n\r", ch);
    	else if ( ch->practice < 10)
    		send_to_char("The price has not been set.\n\r", ch);
    	else
    	{
    		ch->pcdata->powers[improve] += 1;
    		ch->practice -= 10;
    		send_to_char("#6Your eyes become undead.\n\r", ch);
    	}
    	return;
    }
    else if (!str_cmp(arg1,"spying crow"))
    {
    	if ( ch->pcdata->powers[PMONK] > 1 )
    		send_to_char("#6You already have a loyal crow.\n\r", ch);
    	else if ( ch->pcdata->powers[PMONK] < 1 )
    		send_to_char("#6You lack the previous powers to be able to control a crow.\n\r", ch);
    	else if ( ch->practice < 20)
    		send_to_char("The price has not been set.\n\r", ch);
    	else
    	{
    		ch->pcdata->powers[improve] += 1;
    		ch->practice -= 20;
    		send_to_char("#6A crow comes and lands beside you.\n\r", ch);
    	}
    	return;
    }
    else if (!str_cmp(arg1,"cold hands"))
    {
        if ( ch->pcdata->powers[PMONK] == 3 || ch->pcdata->powers[PMONK] == 5
           || ch->pcdata->powers[PMONK] == 7 || ch->pcdata->powers[PMONK] == 9
           || ch->pcdata->powers[PMONK] == 11 || ch->pcdata->powers[PMONK] == 15
           || ch->pcdata->powers[PMONK] == 13 || ch->pcdata->powers[PMONK] == 17)
    		send_to_char("Your hands are already deadly cold.\n\r", ch);
        else if ( ch->pcdata->powers[PMONK] == 4 || ch->pcdata->powers[PMONK] == 6
           || ch->pcdata->powers[PMONK] == 8 || ch->pcdata->powers[PMONK] == 10
           || ch->pcdata->powers[PMONK] == 12 || ch->pcdata->powers[PMONK] == 14
           || ch->pcdata->powers[PMONK] == 16 || ch->pcdata->powers[PMONK] == 18)
		send_to_char("You have already chosen Iron fists.. You cannot get cold hands.\n\r", ch);
	else if ( ch->pcdata->powers[PMONK] < 2 )
    		send_to_char("#6You need your previous powers before you can obtain this one.\n\r", ch);
    	else if ( ch->practice < 30)
    		send_to_char("You don't have the #330#8 required primal.\n\r", ch);
    	else
    	{
    		ch->pcdata->powers[improve] += 1;
    		ch->practice -= 30;
    		send_to_char("#6Your hands become deadly cold.\n\r", ch);
    	}
    	return;
    }
    else if (!str_cmp(arg1,"iron fists"))
    {
        if ( ch->pcdata->powers[PMONK] == 4 || ch->pcdata->powers[PMONK] == 6
           || ch->pcdata->powers[PMONK] == 8 || ch->pcdata->powers[PMONK] == 10
           || ch->pcdata->powers[PMONK] == 12 || ch->pcdata->powers[PMONK] == 14
           || ch->pcdata->powers[PMONK] == 16 || ch->pcdata->powers[PMONK] == 18)
		send_to_char("You hands are already solid iron.\n\r", ch);    	
        else if ( ch->pcdata->powers[PMONK] == 3 || ch->pcdata->powers[PMONK] == 5
           || ch->pcdata->powers[PMONK] == 7 || ch->pcdata->powers[PMONK] == 9
           || ch->pcdata->powers[PMONK] == 11 || ch->pcdata->powers[PMONK] == 13
           || ch->pcdata->powers[PMONK] == 15 || ch->pcdata->powers[PMONK] == 17)
    		send_to_char("Your hands are already deadly cold, you cannot get iron fists.\n\r", ch);    	
	else if ( ch->pcdata->powers[PMONK] < 4 )
    		send_to_char("#6You need your previous powers before you can obtain this one.\n\r", ch);
    	else if ( ch->practice < 40)
    		send_to_char("You don't have the #340#8 required primal.\n\r", ch);
    	else
    	{
    		ch->pcdata->powers[improve] += 2;
    		ch->practice -= 40;
    		send_to_char("#6Your hands fuse into solid iron.\n\r", ch);
    	}
    	return;
    }
    else if (!str_cmp(arg1,"skin of the grave"))
    {
    	if ( ch->pcdata->powers[PMONK] > 4 )
    		send_to_char("#6Your skin is already hardened by the grave.\n\r", ch);
    	else if ( ch->pcdata->powers[PMONK] < 3 )
    		send_to_char("#6You need your previous powers before you can obtain this one.\n\r", ch);
    	else if ( ch->practice < 50)
    		send_to_char("You don't have the #350#8 required primal.\n\r", ch);
    	else
    	{
    		ch->pcdata->powers[improve] += 2;
    		ch->practice -= 50;
    		send_to_char("#6The dirt of your grave hardens your skin.\n\r", ch);
    	}
    	return;
    }
    else if (!str_cmp(arg1,"grave travel"))
    {
        if ( ch->pcdata->powers[PMONK] == 7 || ch->pcdata->powers[PMONK] == 8
          || ch->pcdata->powers[PMONK] == 11 || ch->pcdata->powers[PMONK] == 12
          || ch->pcdata->powers[PMONK] == 15 || ch->pcdata->powers[PMONK] == 16)
		send_to_char("#6You can already emerge from the ground in any place.\n\r", ch);
        else if ( ch->pcdata->powers[PMONK] == 9 || ch->pcdata->powers[PMONK] == 10
          || ch->pcdata->powers[PMONK] == 13 || ch->pcdata->powers[PMONK] == 14
          || ch->pcdata->powers[PMONK] == 17 || ch->pcdata->powers[PMONK] == 18)
		send_to_char("#6Your shroud prevents you from learning this power.\n\r", ch);
    	else if ( ch->pcdata->powers[PMONK] < 5 )
    		send_to_char("#6You need your previous powers before you can obtain this one.\n\r", ch);
    	else if ( ch->practice < 60)
    		send_to_char("You don't have the #360#8 required primal.\n\r", ch);
    	else
    	{
    		ch->pcdata->powers[improve] += 2;
    		ch->practice -= 60;
    		send_to_char("#6You gain the power to travel through your grave.\n\r", ch);
    	}
    	return;
    }
    else if (!str_cmp(arg1,"mysterious shroud"))
    {
        if ( ch->pcdata->powers[PMONK] == 9 || ch->pcdata->powers[PMONK] == 10
          || ch->pcdata->powers[PMONK] == 13 || ch->pcdata->powers[PMONK] == 14
          || ch->pcdata->powers[PMONK] == 17 || ch->pcdata->powers[PMONK] == 18)
    		send_to_char("#6You already have a shroud around your spirit.\n\r", ch);
        else if ( ch->pcdata->powers[PMONK] == 7 || ch->pcdata->powers[PMONK] == 8
          || ch->pcdata->powers[PMONK] == 11 || ch->pcdata->powers[PMONK] == 12
          || ch->pcdata->powers[PMONK] == 15 || ch->pcdata->powers[PMONK] == 16)
		send_to_char("#6You cannot possess a shroud when your a grave traveler.\n\r", ch);
    	else if ( ch->pcdata->powers[PMONK] < 5 )
    		send_to_char("#6You need your previous powers before you can obtain this one.\n\r", ch);
    	else if ( ch->practice < 70)
    		send_to_char("You don't have the #370#8 required primal.\n\r", ch);
    	else
    	{
    		ch->pcdata->powers[improve] += 4;
    		ch->practice -= 70;
    		send_to_char("#8You feel your shroud form around you.\n\r", ch);
    	}
    	return;
    }
    else if (!str_cmp(arg1,"limbo scythe"))
    {
        if ( ch->pcdata->powers[PMONK] == 11 || ch->pcdata->powers[PMONK] == 12
          || ch->pcdata->powers[PMONK] == 13 || ch->pcdata->powers[PMONK] == 14 )
    		send_to_char("#6You can already call upon your scythe.\n\r", ch);
        else if ( ch->pcdata->powers[PMONK] == 15 || ch->pcdata->powers[PMONK] == 16
          || ch->pcdata->powers[PMONK] == 17 || ch->pcdata->powers[PMONK] == 18 )
		send_to_char("#6Your chilling shreak prevents you from holding weapons.\n\r", ch);
    	else if ( ch->pcdata->powers[PMONK] < 7 )
    		send_to_char("#6You need your previous powers before you can obtain this one.\n\r", ch);
    	else if ( ch->practice < 80)
    		send_to_char("You don't have the #380#8 required primal.\n\r", ch);
    	else
    	{
    		ch->pcdata->powers[improve] += 4;
    		ch->practice -= 80;
    		send_to_char("#6You receive a Limbo Scythe to command.\n\r", ch);
    	}
    	return;
    }
    else if (!str_cmp(arg1,"chilling scream"))
    {
        if ( ch->pcdata->powers[PMONK] == 15 || ch->pcdata->powers[PMONK] == 17
          || ch->pcdata->powers[PMONK] == 16 || ch->pcdata->powers[PMONK] == 18 )
    		send_to_char("#6Your voice already holds that power.\n\r", ch);
        else if ( ch->pcdata->powers[PMONK] == 11 || ch->pcdata->powers[PMONK] == 12
          || ch->pcdata->powers[PMONK] == 13 || ch->pcdata->powers[PMONK] == 14 )
		send_to_char("#6You cannot shreak with the ability to hold a weapon.\n\r", ch);
    	else if ( ch->pcdata->powers[PMONK] < 7 )
    		send_to_char("#6You need your previous power before you can obtain this one.\n\r", ch);
    	else if ( ch->practice < 90)
    		send_to_char("You don't have the #390#8 required primal.\n\r", ch);
    	else
    	{
    		ch->pcdata->powers[improve] += 8;
    		ch->practice -= 90;
    		send_to_char("#6Your voice assumes a greater power.\n\r", ch);
    	}
    	return;
    }
	sprintf(buf,"#1Mantras Learned#5 (%d).\n\r", ch->pcdata->powers[PMONK]);
	send_to_char(buf,ch);

	return;
}

void do_immortaleyes( CHAR_DATA *ch, char *argument )
{
    if ( IS_NPC(ch) )
	return;
  
        if ( !IS_CLASS(ch, CLASS_REVNANT) )
  	{
  	send_to_char("Huh?\n\r", ch);
  	return;
  	}
  	
  	if ( ch->pcdata->powers[PMONK] < 1 )
  	{
  	  send_to_char("#6You do not have undead eyes yet.\n\r", ch);
  	  return;
  	}
  
    if ( IS_SET(ch->act, PLR_HOLYLIGHT) || IS_AFFECTED(ch,AFF_SHADOWSIGHT) ||
IS_AFFECTED(ch,AFF_DETECT_INVIS) || IS_AFFECTED(ch,AFF_DETECT_HIDDEN) || IS_AFFECTED(ch,AFF_INFRARED) )
    {
	REMOVE_BIT(ch->act, PLR_HOLYLIGHT);
	REMOVE_BIT(ch->affected_by, AFF_SHADOWSIGHT);
	REMOVE_BIT(ch->affected_by, AFF_DETECT_INVIS);
	REMOVE_BIT(ch->affected_by, AFF_DETECT_HIDDEN);
	REMOVE_BIT(ch->affected_by, AFF_INFRARED);
	send_to_char( "You look through your old human eyes again.\n\r", ch );
    }
    else
    {
	send_to_char( "You begin to see with your undead vision.\n\r", ch );
	SET_BIT(ch->act, PLR_HOLYLIGHT);
	SET_BIT(ch->affected_by, AFF_SHADOWSIGHT);
	SET_BIT(ch->affected_by, AFF_DETECT_INVIS);
    	SET_BIT(ch->affected_by, AFF_DETECT_HIDDEN);
	SET_BIT(ch->affected_by, AFF_INFRARED);
    }
    return;
}


void do_mclan( CHAR_DATA *ch, char *argument )
{
    char buf[MAX_STRING_LENGTH];
    CHAR_DATA *gch;

    if (IS_NPC(ch)) return;
    if (!IS_CLASS(ch, CLASS_REVNANT) )
    {
	send_to_char("Huh?\n\r",ch);
	return;
    }

    if (strlen(ch->clan) < 2)
    {
	send_to_char("You are an outcast!\n\r",ch);
	return;
    }

    sprintf( buf, "%s Monks:\n\r", ch->clan );
    send_to_char( buf, ch );
    send_to_char("[      Name      ] [ Hits  % ] [ Mana  % ] [ Move  % ]\n\r", ch );
    for ( gch = char_list; gch != NULL; gch = gch->next )
    {
	if ( IS_NPC(gch) ) continue;
        if ( !IS_CLASS(gch, CLASS_REVNANT) ) continue;
	if ( !str_cmp(ch->clan,gch->clan) )
	{
	    sprintf( buf,
	    "[%-16s] [%-6d%3d] [%-6d%3d] [%-6d%3d]\n\r",
		capitalize( gch->name ),
		gch->hit,  (gch->hit  * 100 / gch->max_hit ),
		gch->mana, (gch->mana * 100 / gch->max_mana),
		gch->move, (gch->move * 100 / gch->max_move) );
		send_to_char( buf, ch );
	}
    }
    return;
}

void do_mysteriousshroud( CHAR_DATA *ch, char *argument )
{
    if (IS_NPC(ch)) return;
	
        if (!IS_CLASS(ch, CLASS_REVNANT) )
	{
		send_to_char("Huh?\n\r", ch);
		return;
	}
	
        if (IS_CLASS(ch, CLASS_REVNANT) && ch->pcdata->powers[PMONK] < 3 )
	{
	  send_to_char("A shroud has not been weaved around you yet.\n\r", ch);
	  return;
	}

    if ( IS_SET(ch->act, PLR_WIZINVIS) )
    {
	REMOVE_BIT(ch->act, PLR_WIZINVIS);
	send_to_char( "You remove your shroud.\n\r", ch );
	act( "$n fades into view as you get a chill.", ch, NULL, NULL, TO_ROOM );
    }
    else
    {
	send_to_char( "You pull your shroud over yourself.\n\r", ch );
	act( "You feel warmer as the form of $n fades to nothing.", ch, NULL, NULL, TO_ROOM );
	SET_BIT(ch->act, PLR_WIZINVIS);
	ch->move -= 500; 
    }
    return;
}

void do_gravetravel( CHAR_DATA *ch, char *argument )
{
	char arg[MAX_INPUT_LENGTH];
    CHAR_DATA *victim;
    CHAR_DATA *mount;

	one_argument( argument, arg );

        if ( !IS_CLASS(ch, CLASS_REVNANT) )
	{
		send_to_char("Huh?\n\r", ch);
		return;
	}

        if (IS_CLASS(ch, CLASS_REVNANT) && ch->pcdata->powers[PMONK] < 9 )
	{
	  send_to_char("You don't have the ability to grave travel.\n\r", ch);
	  return;
	}

    if ( arg[0] == '\0' )
    {
	send_to_char( "Grave travel to Whom?\n\r", ch );
	return;
    }
    
    if ( ch->position == POS_FIGHTING )
    {
	send_to_char( "No way! You are fighting.\n\r", ch );
	return;
    }

    if ( ( victim = get_char_world( ch, arg ) ) == NULL )
    {
	send_to_char( "Nobody by that name.\n\r", ch );
	return;
    }

	if ( ch->move < 500 )
	{
	send_to_char( "You don't have the required 500 move.\n\r", ch);
	return;
	}

	
    act( "You dig into your grave.", ch, NULL, NULL, TO_CHAR );
	act( "$n digs into his grave.", ch, NULL, NULL, TO_ROOM );
	char_from_room( ch );
	char_to_room( ch, get_room_index(victim->in_room->vnum) );
    act( "You emerge from the dirt infront of $N", ch, NULL, victim, TO_CHAR );
	act( "$n emerges from the dirt before $N.", ch, NULL, victim, TO_ROOM );	
	ch->move -= 500;

    do_look( ch, "auto" );
    if ( (mount = victim->mount) == NULL ) return;
    char_from_room( mount );
    char_to_room( mount, get_room_index(victim->in_room->vnum) );
    do_look( mount, "auto" );
    return;
}


void do_shadowdrain(CHAR_DATA *ch, char *argument )
{

 CHAR_DATA *victim;
 char buf[MAX_STRING_LENGTH];
 char arg [MAX_INPUT_LENGTH];
 argument = one_argument( argument, arg );

   if (IS_NPC(ch)) return;

 if ( !IS_CLASS(ch, CLASS_REVNANT))
        {
        send_to_char("Huh?\n\r", ch);
        return;
        }
    
        if ( arg[0] == '\0' )
        {
            send_to_char( "Shadowdrain the essence of who?\n\r", ch );
            return;
        }
 
        
        if ( ( victim = get_char_room( ch, arg ) ) == NULL )
        {
            send_to_char( "They aren't here.\n\r", ch );
            return;
        }


    if ( ( victim = get_char_room( ch, arg ) ) == NULL )
    {
	send_to_char( "They aren't here.\n\r", ch );
	return;
    }


    if ( IS_NPC(victim) )
    {
	send_to_char( "Not on NPC's.\n\r", ch );
	return;
    }

if ( IS_IMMORTAL(victim) )
        {
            send_to_char("You power is not that great.\n\r", ch);
            return;
        }


if (IS_AFFECTED(victim,AFF_SHADOWPLANE) )
   {
 do_shadowplane(victim,"");
 send_to_char("You feel your life force being drained away.. and can",victim);
 send_to_char("no longer maintain your presence in the shadowplane.",victim);
 victim->hit = victim->hit / 2;
 victim->move = victim->move / 2;
 sprintf(buf,"You call upon the powers of the fallen to remove %s from the
 shadow.",victim->name);
 send_to_char(buf,ch);
 return;
   }

 send_to_char("They are not affected by any powers of the dark",ch);
 return;
}

void do_limboscythe( CHAR_DATA *ch, char *argument ) 
{
    CHAR_DATA *victim;
    char arg [MAX_INPUT_LENGTH];
    int sn;
    int level;
    int spelltype;

    argument = one_argument( argument, arg );
    if (IS_NPC(ch)) return;

    if (IS_IMMORTAL(victim) )
    {
	send_to_char("You wish you had that power\n\r",ch);
	return;    

    if (!IS_CLASS(ch, CLASS_REVNANT)) 
    {
        send_to_char("Huh?\n\r",ch);
        return;
    }

    if (ch->pcdata->powers[PMONK] < 11 || ch->pcdata->powers[PMONK] > 14)
    {
	send_to_char("You do not have this power",ch);
	return;
    }
 
    if ( arg[0] == '\0' )
    {
    	send_to_char("Call the limbo scythe against whom?\n\r", ch);
    	return;
    }

    if ( ( victim = get_char_room( ch, arg ) ) == NULL )
	if ((victim = ch->fighting) == NULL)
    {
        send_to_char( "They aren't here.\n\r", ch );
        return;
    }
	if (ch->mana < 100) {
		send_to_char("You don't have enough mana.\n\r", ch);
		return;}

    if ( ( sn = skill_lookup( "limbo scythe" ) ) < 0 ) return;
    spelltype = skill_table[sn].target;
    level = ch->spl[spelltype] * 1.0;
	level = level * 1.0;
	act("You concentrate your power on $N.",ch,NULL,victim,TO_CHAR);
	act("$n concentrates $s power on you.",ch,NULL,victim,TO_VICT);
    (*skill_table[sn].spell_fun) ( sn, level, ch, victim );
    WAIT_STATE( ch, 10 );
	ch->mana = ch->mana - 100;
    return;
}
}
void do_scream (CHAR_DATA *ch, char *argument)
{
    CHAR_DATA *victim;
    OBJ_DATA *obj;
    char buf[MAX_INPUT_LENGTH];

    if (IS_NPC(ch)) return;

    if (!IS_CLASS(ch, CLASS_REVNANT))
    {
	send_to_char("Huh?\n\r", ch);
	return;
    }

    if (IS_IMMORTAL(victim))
    {
	send_to_char("You wish you had that sort of power\n\r", ch);
	return;
    }

    if ( ( (obj = get_eq_char( victim, WEAR_WIELD ) ) == NULL) || obj->item_type != ITEM_WEAPON )
    {
    if ( ( (obj = get_eq_char( victim, WEAR_HOLD ) ) == NULL) || obj->item_type != ITEM_WEAPON )
    return;
    }

    sprintf(buf,"$n screams horribly and you drop your weapons!");
    ADD_COLOUR(ch,buf,WHITE);
    act( buf, ch, NULL, victim, TO_VICT    );
    sprintf(buf,"Your chilling scream is directed at $N!");
    ADD_COLOUR(ch,buf,WHITE);
    act( buf,  ch, NULL, victim, TO_CHAR    );
    sprintf(buf,"$n screams at $N, who drops his weapons in terror.");
    ADD_COLOUR(ch,buf,WHITE);
    act( buf,  ch, NULL, victim, TO_NOTVICT );

    obj_from_char( obj );

    if ( IS_NPC(victim) )
	obj_to_char( obj, victim );
    else
	obj_to_room( obj, victim->in_room );

    return;
}	
