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

void do_upgrade( CHAR_DATA *ch, char *argument )
{
    char arg1[MAX_INPUT_LENGTH];
    char arg2[MAX_INPUT_LENGTH];
    char buf[MAX_STRING_LENGTH];

    argument = one_argument( argument, arg1 );
    argument = one_argument( argument, arg2 );

    if (IS_NPC(ch)) return;

    if (!IS_CLASS(ch, CLASS_NINJA))
    {
	send_to_char("Huh?\n\r",ch);
	return;
    }

    if (arg1[0] == '\0' && arg2[0] == '\0')
    {
	sprintf(buf,"Upgradeable:  Optical (%d), Tactical (%d), Combat (%d), Ballistics (%d).\n\r",
	ch->pcdata->powers[NPOWER_OPTICAL], ch->pcdata->powers[NPOWER_TACTICAL],
	ch->pcdata->powers[NPOWER_COMBAT], ch->pcdata->powers[NPOWER_BALLISTICS]);
	send_to_char(buf,ch);
	return;
    }
    if (arg2[0] == '\0')
    {
	if (!str_cmp(arg1,"optical"))
	{
	    send_to_char("Optical Upgrades - Gives you sight in the field.\n\r",ch);
	    if (ch->pcdata->powers[NPOWER_OPTICAL] < 1) 
		send_to_char("You have none of the Optical Upgrades, Soldier.\n\r",ch);
	    if (ch->pcdata->powers[NPOWER_OPTICAL] > 0) 
		send_to_char("Satellite (scry) Our satellites home in on enemies, giving you their position.\n\r",ch);
	    if (ch->pcdata->powers[NPOWER_OPTICAL] > 1) 
		send_to_char("Bodyscan (readaura) Use your pulse sensors to memorize your opponent's body.\n\r",ch);
	    if (ch->pcdata->powers[NPOWER_OPTICAL] > 2) 
		send_to_char("Camouflage (hide) Using holograms you hide yourself from all but your ilk.\n\r",ch);
	    if (ch->pcdata->powers[NPOWER_OPTICAL] > 3) 
		send_to_char("Lightfoot (automatic) Your light feet make you untrackable, a powerful tool.\n\r",ch);
		if (ch->pcdata->powers[NPOWER_OPTICAL] > 4)
		send_to_char("MaximaSight (truesight) Your eyes get fully upgraded seeing all.\n\r", ch);
		if (ch->pcdata->powers[NPOWER_OPTICAL] > 5)
		send_to_char("Roomsweep (knockout) You fly around the room knocking out everybody.\n\r", ch);
                if (ch->pcdata->powers[NPOWER_OPTICAL] > 6)
                send_to_char("Eyebeam (eyebeam) Send a light shot of laser to opponents hand, cutting it off.\n\r", ch);
	    return;
	}
	else if (!str_cmp(arg1,"tactical"))
	{
	    send_to_char("Tactical Upgrades - Your ready, your opponent isn't.\n\r",ch);
	    if (ch->pcdata->powers[NPOWER_TACTICAL] < 1) 
		send_to_char("You have none of the Tactical Upgrades.\n\r",ch);
	    if (ch->pcdata->powers[NPOWER_TACTICAL] > 0) 
		send_to_char("Metal Plating: Your upgraded skin is very tough.\n\r",ch);
	    if (ch->pcdata->powers[NPOWER_TACTICAL] > 1) 
		send_to_char("Strength: Your muscles are hardened with Titanium, making you super-human.\n\r",ch);
	    if (ch->pcdata->powers[NPOWER_TACTICAL] > 2) 
		send_to_char("Speed: Your reflexes are better, you attack more.\n\r",ch);
	    if (ch->pcdata->powers[NPOWER_TACTICAL] > 3) 
		send_to_char("Hunt: You hunt others much faster.\n\r",ch);
		if (ch->pcdata->powers[NPOWER_TACTICAL] > 4)
		send_to_char("Flash: You move faster than immortals, godlike even.\n\r", ch);
                if (ch->pcdata->powers[NPOWER_TACTICAL] > 5)
                send_to_char("Ncreate: You can make Cybernetic Ninja equipment.\n\r", ch);
	    return;
	}
	else if (!str_cmp(arg1,"Combat"))
	{
	    send_to_char("Combat Upgrades - Your cybernetic enhancements to help you in battle.\n\r",ch);
	    if (ch->pcdata->powers[NPOWER_COMBAT] < 1) 
		send_to_char("You have none of the COmbatical Upgrades.\n\r",ch);
	    if (ch->pcdata->powers[NPOWER_COMBAT] > 0) 
		send_to_char("PowerFists (pfist) Your hands are now able weapons in combat. You ARE the weapon.\n\r",ch);
	    if (ch->pcdata->powers[NPOWER_COMBAT] > 1) 
		send_to_char("WaveBlend (wblend) You twist reality so none can see you short of the Magi.\n\r",ch);
	    if (ch->pcdata->powers[NPOWER_COMBAT] > 2) 
		send_to_char("Air Rip (arip) You rip the fibers of air, leaving an escape route that never fails.\n\r",ch);
	    if (ch->pcdata->powers[NPOWER_COMBAT] > 3) 
		send_to_char("Eyeblast (automatic) You shoot a blast of energy at your foe every round.\n\r",ch);
		if (ch->pcdata->powers[NPOWER_COMBAT] > 4)
		send_to_char("ArmsOfSpeed (auto) Your arms move faster than thought, allowing for great parry.\n\r",ch);
	    return;
	}
	sprintf(buf,"Principles: Optical (%d), Tactical (%d), Combat (%d), Ballistics (%d).\n\r",
	ch->pcdata->powers[NPOWER_OPTICAL], ch->pcdata->powers[NPOWER_TACTICAL],
	ch->pcdata->powers[NPOWER_COMBAT]);
	send_to_char(buf,ch);
	return;
    }
    if (!str_cmp(arg2,"buy"))
    {
	int improve;
	int cost;
	int max;

	     if (!str_cmp(arg1,"optical"   )) {improve = NPOWER_OPTICAL;   max=6;}
	else if (!str_cmp(arg1,"tactical"   )) {improve = NPOWER_TACTICAL;   max=5;}
	else if (!str_cmp(arg1,"combat"   )) {improve = NPOWER_COMBAT;   max=5;}
	else
	{
	    send_to_char("Upgrades: Optical, Combat, Tactical, Ballistics.\n\r",ch);
	    return;
	}							
	cost = (ch->pcdata->powers[improve]+1) * 15;
	arg1[0] = UPPER(arg1[0]);
	if ( ch->pcdata->powers[improve] >= max )
	{
	    sprintf(buf,"You have already reaped the profits of your %s Upgrade.\n\r", arg1);
	    send_to_char(buf,ch);
	    return;
	}
	if ( cost > ch->practice )
	{
	    sprintf(buf,"It costs you %d primal to improve your %s principle.\n\r", cost, arg1);
	    send_to_char(buf,ch);
	    return;
	}
	ch->pcdata->powers[improve] += 1;
	ch->practice -= cost;
	sprintf(buf,"You improve your ability in the %s principle.\n\r", arg1);
	send_to_char(buf,ch);
    }
    else send_to_char("To improve a principle, type: Principle <principle type> improve.\n\r",ch);
	return;
}

void do_michi(  CHAR_DATA *ch, char *argument  )
{
    if (IS_NPC(ch)) return;
	
	if (!IS_CLASS(ch, CLASS_NINJA) )
	{
		send_to_char("Huh?\n\r", ch);
		return;
	}

  if ( IS_CLASS(ch, CLASS_NINJA) )
  {
	
	if ( ch->pcdata->stats[UNI_RAGE] >= 50 )
	{
	    send_to_char("But you are already in the state of Michi.\n\r",ch);
	    return;
	}
	if ( ch->move < 1000 )
	{
		send_to_char("But you don't have enough move to perform the michi.\n\r", ch);
		return;
	} 
	
	send_to_char("You are gifted positive energy while performing the michi.\n\r",ch);
	act("$n is gifted positives energy while performing the michi.",ch,NULL,NULL,TO_ROOM);
	ch->pcdata->stats[UNI_RAGE] += 200;
	ch->move -= 1000; 
	WAIT_STATE(ch,12);
	return;
  }
	else
    send_to_char("But you are already in the state of Michi.\n\r",ch);
    return;
}

void do_discipline( CHAR_DATA *ch, char *argument )
{
    CHAR_DATA *victim;
    char      arg [MAX_INPUT_LENGTH];

    argument = one_argument( argument, arg );

    if (IS_NPC(ch)) return;
	
	if (!IS_CLASS(ch, CLASS_NINJA) )
	{
		send_to_char("Huh?\n\r", ch);
		return;
	}
	    
    if (IS_CLASS(ch, CLASS_NINJA) && !IS_SET(ch->special, SPC_PRINCE)
        && ch->pcdata->stats[UNI_GEN] != 1
        && ch->pcdata->stats[UNI_GEN] != 2 )
    {
	send_to_char("You do not have disciplining abilities.\n\r",ch);
	return;
    }
    
    if ( arg[0] == '\0' )
    {
	send_to_char( "Discipline whom?\n\r", ch );
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
	send_to_char( "Not on Immortals's.\n\r", ch );
	return;
    }

    if ( ch == victim )
    {
	send_to_char( "You cannot discipline yourself.\n\r", ch );
	return;
    }

    if ( victim->class != 0)
    {
        send_to_char("They are already classed.\n\r",ch);
        return;
    }

    if (!IS_IMMUNE(victim,IMM_VAMPIRE))
    {
	send_to_char( "You cannot discipline an unwilling person.\n\r", ch );
	return;
    }

    if (ch->exp < 100000)
    {
	send_to_char("You cannot afford the 100000 exp required to discipline them.\n\r",ch);
	return;
    }

    if (victim->exp < 100000)
    {
	send_to_char("They cannot afford the 100000 exp required to be disciplined from you.\n\r",ch);
	return;
    }

    ch->exp -= 100000;
    victim->exp -= 100000;

    act("You teach $N the ways of the ninja.", ch, NULL, victim, TO_CHAR);
    act("$n teaches $N the ways of the ninja.", ch, NULL, victim, TO_NOTVICT);
    act("$n teaches you the way of the ninja.", ch, NULL, victim, TO_VICT);
    victim->class    = CLASS_NINJA;
    victim->level = LEVEL_ARCHMAGE;
    if (victim->trust > 6)
    victim->trust = victim->trust;
    else
    victim->trust = LEVEL_ARCHMAGE;
    
    send_to_char( "You are now a ninja.\n\r", victim );
    free_string(victim->lord);
    victim->lord = str_dup(ch->name);
	free_string(victim->clan);
    victim->clan=str_dup(ch->clan);
    victim->pcdata->stats[UNI_GEN] = ch->pcdata->stats[UNI_GEN] + 1;
    save_char_obj(ch);
    save_char_obj(victim);
    return;
}

void do_kakusu( CHAR_DATA *ch, char *argument )
{
    if (IS_NPC(ch)) return;
	
	if (!IS_CLASS(ch, CLASS_NINJA) )
	{
		send_to_char("Huh?\n\r", ch);
		return;
	}
	
	if (IS_CLASS(ch, CLASS_NINJA) && ch->pcdata->powers[NPOWER_OPTICAL] < 3 )
	{
	  send_to_char("You have not Upgraded your Optics to the Third Level.\n\r", ch);
	  return;
	}
	
	if (ch->move < 500)
	{
		send_to_char("You don't have 500 move to activate your power.\n\r", ch);
		return;
	} 

    if ( IS_SET(ch->act, PLR_WIZINVIS) )
    {
	REMOVE_BIT(ch->act, PLR_WIZINVIS);
	act( "$n appears from the shadows.", ch, NULL, NULL, TO_ROOM );
	send_to_char( "You appear from the shadows.\n\r", ch );
    }
    else
    {
	act( "$n disappears into the shadows.", ch, NULL, NULL, TO_ROOM );
	send_to_char( "You disappear into the shadows.\n\r", ch );
	SET_BIT(ch->act, PLR_WIZINVIS);
	ch->move -= 500; 
    }
    return;
}

void do_kanzuite( CHAR_DATA *ch, char *argument )
{
    if (IS_NPC(ch)) return;
	
	if (!IS_CLASS(ch, CLASS_NINJA) )
	{
		send_to_char("Huh?\n\r", ch);
		return;
	}
	
    if (IS_CLASS(ch, CLASS_NINJA) && ch->pcdata->powers[NPOWER_OPTICAL] < 5 )
	{
	  send_to_char("You have not learned the Optics Upgrade to 5.\n\r", ch);
	  return;
	}
	
	else if (ch->move < 500)
	{
		send_to_char("You don't have 500 move to increase your awareness.\n\r", ch);
		return;
	} 

    if ( IS_SET(ch->act, PLR_HOLYLIGHT) )
    {
	REMOVE_BIT(ch->act, PLR_HOLYLIGHT);
	send_to_char( "You're senses return to normal.\n\r", ch );
    }
    else
    {
	SET_BIT(ch->act, PLR_HOLYLIGHT);
	send_to_char( "You're senses increase into incredible proportions.\n\r", ch );
	ch->move -= 500; 
    }

    return;
}

void do_mienaku( CHAR_DATA *ch, char *argument )
{
    ROOM_INDEX_DATA *was_in;
    ROOM_INDEX_DATA *now_in;
    CHAR_DATA *victim;
    int attempt;


	if (IS_CLASS(ch, CLASS_NINJA) && ch->pcdata->powers[NPOWER_COMBAT] < 3 )
	{
	send_to_char("You have not learned the Combat Ugrade to 3.\n\r", ch);
	return;
	}
	else if (!IS_CLASS(ch, CLASS_NINJA) )
	{
	send_to_char("Huh?\n\r", ch);
	return;
	}
	
	if ( IS_NPC(ch) ) return;

    if ( ( victim = ch->fighting ) == NULL )
    {
	if ( ch->position == POS_FIGHTING )
	    ch->position = POS_STANDING;
	send_to_char( "You aren't fighting anyone.\n\r", ch );
	return;
    }
	if(ch->move <= 0)
	{
	   send_to_char("You can't find the energy to leave.\n\r",ch);
	   return;
	}
	if (ch->move < 200)
	{
	send_to_char("You don't have enough movement points to flee.\n\r", ch);
	return;
	} 
    if (IS_AFFECTED(ch, AFF_WEBBED))
    {
	send_to_char("You are unable to move with all this sticky webbing on.\n\r",ch);
	return;
    }
  
    was_in = ch->in_room;
    
{
	EXIT_DATA *pexit;
	int door;

for ( attempt =  0; attempt < 6; attempt++ ) 
	{
	door = number_door( );
	if ( ( pexit = was_in->exit[door] ) == 0
	||   pexit->to_room == NULL
	||   IS_SET(pexit->exit_info, EX_CLOSED)
	|| ( IS_NPC(ch)
	&&   IS_SET(pexit->to_room->room_flags, ROOM_NO_MOB) ) )
	      continue;


	move_char( ch, door );
	if ( ( now_in = ch->in_room ) == was_in )
	      continue;

/* Use escape instead of flee so people know it's the ninja power */
	ch->in_room = was_in;
	act( "$n has escaped!", ch, NULL, NULL, TO_ROOM );
	ch->in_room = now_in;
	
	if ( !IS_NPC(ch) )
	    send_to_char( "You escape from combat!\n\r", ch ); 

/* No blinding thing - Loki	
	if (victim->in_room == ch->in_room)
    {
    	SET_BIT(victim->extra,BLINDFOLDED);
    	act("You start to move at super speeds and blind $N.",ch,NULL,victim,TO_CHAR);
    	act("$n starts to move at super speeds and blinds $N.",ch,NULL,victim,TO_ROOM);
    	act("$n starts to move at super speeds and blinds you.",ch,NULL,victim,TO_VICT);
    	
    	return;
    }
*/    
    ch->move -= 200;
	stop_fighting( ch, TRUE );
	return;
   }
   
}
send_to_char( "You fail to escape!\n\r", ch );
    return;
}

void do_target( CHAR_DATA *ch, char *argument )
{
    CHAR_DATA *victim;
    char      arg1 [MAX_INPUT_LENGTH];
    char      arg2 [MAX_INPUT_LENGTH];
    argument = one_argument( argument, arg1 );
    argument = one_argument( argument, arg2 );

    if (IS_NPC(ch)) return;
	
	if (!IS_CLASS(ch, CLASS_NINJA) )
	{
		send_to_char("Huh?\n\r", ch);
		return;
	}
	    
    if ( arg1[0] == '\0' || arg2[0] == '\0' )
    {
	send_to_char( "Syntax is: target <person> <prince/outcast/induct>\n\r", ch );
	return;
    }

    if ( ( victim = get_char_room( ch, arg1 ) ) == NULL )
    {
	send_to_char( "They aren't here.\n\r", ch );
	return;
    }

    if ( IS_NPC(victim) )
    {
	send_to_char( "Not on NPC's.\n\r", ch );
	return;
    }

    if ( ch == victim )
    {
	send_to_char( "Not on yourself!\n\r", ch );
	return;
    }

    if ( !IS_CLASS(victim,CLASS_NINJA) )
    {
	send_to_char( "But they are not a ninja!\n\r", ch );
	return;
    }

    if ( str_cmp(victim->clan,ch->clan) && str_cmp(arg2,"induct") )
    {
	send_to_char( "You can only grant your target to someone in your clan.\n\r", ch );
	return;
    }

    if ( ch->pcdata->stats[UNI_GEN] >= victim->pcdata->stats[UNI_GEN] )
    {
	send_to_char( "You can only grant your target to someone of a lower generation.\n\r", ch );
	return;
    }

    if ( !str_cmp(arg2,"prince") && ch->pcdata->stats[UNI_GEN] == 2)
    {
	if (IS_SET(victim->special,SPC_PRINCE)) 
	{
	act("You remove $N's disciplining privilages!",ch,NULL,victim,TO_CHAR);
	act("$n removes $N's disciplining privilages!",ch,NULL,victim,TO_NOTVICT);
	act("$n removes your disciplining privilages!",ch,NULL,victim,TO_VICT);
	REMOVE_BIT(victim->special,SPC_PRINCE);
	return;
	}
	act("You make $N a discipliner!",ch,NULL,victim,TO_CHAR);
	act("$n has made $N a discipliner!",ch,NULL,victim,TO_NOTVICT);
	act("$n has made you a discipliner!",ch,NULL,victim,TO_VICT);
	SET_BIT(victim->special,SPC_PRINCE);
	return;
    }
/* Clan Leader Outcasts Someone */
    else if ( !str_cmp(arg2,"outcast") && victim->pcdata->stats[UNI_GEN] > 2 && 
	ch->pcdata->stats[UNI_GEN] == 2)
    {
	act("You make $N a Ninja Outcast!",ch,NULL,victim,TO_CHAR);
	act("$n has made $N a Ninja Outcast!",ch,NULL,victim,TO_NOTVICT);
	act("$n has made you a Ninja Outcast!",ch,NULL,victim,TO_VICT);
	free_string(victim->clan);
	victim->clan = str_dup( "" );
	return;
    }
/* Prince outcasts a non-prince */
    else if ( !str_cmp(arg2,"outcast") && victim->pcdata->stats[UNI_GEN] > 2 && 
	!IS_SET(victim->special, SPC_PRINCE) && IS_SET(ch->special,SPC_PRINCE))
    {
	act("You make $N a Ninja Outcast!",ch,NULL,victim,TO_CHAR);
	act("$n has made $N a Ninja Outcast!",ch,NULL,victim,TO_NOTVICT);
	act("$n has made you a Ninja Outcast!",ch,NULL,victim,TO_VICT);
	free_string(victim->clan);
	victim->clan = str_dup( "" );
	return;
    }
/* Leader Inducts */
    else if ( !str_cmp(arg2,"induct") && victim->pcdata->stats[UNI_GEN] > 2 && 
	ch->pcdata->stats[UNI_GEN] == 2 && strlen(victim->clan) < 2)
    {
	if (IS_SET(victim->special, SPC_ROGUE))
	{
	    send_to_char("You cannot induct an Rogue!\n\r",ch);
	    return;
	} 
	act("You induct $N into your clan!",ch,NULL,victim,TO_CHAR);
	act("$n inducts $N into $s clan!",ch,NULL,victim,TO_NOTVICT);
	act("$n inducts you into $s clan!",ch,NULL,victim,TO_VICT);
	free_string(victim->clan);
	victim->clan = str_dup( ch->clan );
	return;
    }
/* Prince Inducts */
    else if ( !str_cmp(arg2,"induct") && victim->pcdata->stats[UNI_GEN] > 2 && 
	!IS_SET(victim->special, SPC_PRINCE) && IS_SET(ch->special,SPC_PRINCE) &&
	strlen(victim->clan) < 2)
    {
	if (IS_SET(victim->special, SPC_ROGUE))
	{
	    send_to_char("You cannot induct an Rogue!\n\r",ch);
	    return;
	}
	act("You induct $N into your clan!",ch,NULL,victim,TO_CHAR);
	act("$n inducts $N into $s clan!",ch,NULL,victim,TO_NOTVICT);
	act("$n inducts you into $s clan!",ch,NULL,victim,TO_VICT);
	free_string(victim->clan);
	victim->clan = str_dup( ch->clan );
	return;
    }
/* Clan Leader inducts a person */
    else if ( !str_cmp(arg2,"induct") && victim->pcdata->stats[UNI_GEN] > 2 && 
	ch->pcdata->stats[UNI_GEN] == 2 && strlen(victim->clan) < 2)
    {
	act("You induct $N into your clan!",ch,NULL,victim,TO_CHAR);
	act("$n inducts $N into $s clan!",ch,NULL,victim,TO_NOTVICT);
	act("$n inducts you into $s clan!",ch,NULL,victim,TO_VICT);
	free_string(victim->clan);
	victim->clan = str_dup( ch->clan );
	return;
    }
/* Prince inducts a person */
    else if ( !str_cmp(arg2,"induct") && victim->pcdata->stats[UNI_GEN] > 2 && 
	!IS_SET(victim->special, SPC_PRINCE) && IS_SET(ch->special,SPC_PRINCE) &&
	strlen(victim->clan) < 2)
    {
	act("You induct $N into your clan!",ch,NULL,victim,TO_CHAR);
	act("$n inducts $N into $s clan!",ch,NULL,victim,TO_NOTVICT);
	act("$n inducts you into $s clan!",ch,NULL,victim,TO_VICT);
	free_string(victim->clan);
	victim->clan = str_dup( ch->clan );
	return;
    }
    else send_to_char( "You are unable to grant that sort of favour.\n\r", ch );
    return;
}

void do_nclan( CHAR_DATA *ch, char *argument )
{
    char buf[MAX_STRING_LENGTH];
    char arg[MAX_INPUT_LENGTH];
    CHAR_DATA *gch;

    one_argument( argument, arg );

    if (IS_NPC(ch)) return;
    if (!IS_CLASS(ch, CLASS_NINJA) )
    {
	send_to_char("Huh?\n\r",ch);
	return;
    }

    if (strlen(ch->clan) < 2)
    {
	send_to_char("But you don't belong to any clan!\n\r",ch);
	return;
    }

    sprintf( buf, "%s clan:\n\r", ch->clan );
    send_to_char( buf, ch );
    send_to_char("[      Name      ] [ Gen ] [ Hits  % ] [ Mana  % ] [ Move  % ]\n\r", ch );
    for ( gch = char_list; gch != NULL; gch = gch->next )
    {
	if ( IS_NPC(gch) ) continue;
	if ( !IS_CLASS(gch, CLASS_NINJA) ) continue;
	if ( !str_cmp(ch->clan,gch->clan) )
	{
	    sprintf( buf,
	    "[%-16s] [  %d  ] [%-6d%3d] [%-6d%3d] [%-6d%3d]\n\r",
		capitalize( gch->name ),
		gch->pcdata->stats[UNI_GEN],
		gch->hit,  (gch->hit  * 100 / gch->max_hit ),
		gch->mana, (gch->mana * 100 / gch->max_mana),
		gch->move, (gch->move * 100 / gch->max_move) );
		send_to_char( buf, ch );
	}
    }
    return;
}

void do_rogue( CHAR_DATA *ch, char *argument )
{
    char      arg [MAX_INPUT_LENGTH];
    char      buf [MAX_INPUT_LENGTH];

    argument = one_argument( argument, arg );

    if (IS_NPC(ch)) return;

    if (!IS_CLASS(ch, CLASS_NINJA) )
    {
	send_to_char("Huh?\n\r",ch);
	return;
    }

    if (strlen(ch->clan) > 1)
    {
	send_to_char("But you are already in a clan!\n\r",ch);
	return;
    }

    if ( IS_SET(ch->special, SPC_ROGUE) )
    {
	send_to_char("You are no longer a Rogue.\n\r",ch);
	sprintf(buf,"%s is no longer a Rogue!",ch->name);
	do_info(ch,buf);
	REMOVE_BIT(ch->special, SPC_ROGUE);
	return;
    }
    send_to_char("You are now a Rogue.\n\r",ch);
    sprintf(buf,"%s is now a Rogue!",ch->name);
    do_info(ch,buf);
    SET_BIT(ch->special, SPC_ROGUE);
    return;
}

void do_bomuzite( CHAR_DATA *ch, char *argument )
{
    CHAR_DATA *victim;
    char      arg1 [MAX_INPUT_LENGTH];
    argument = one_argument( argument, arg1 );
        
    if (IS_NPC(ch)) return;
	
	if (!IS_CLASS(ch, CLASS_NINJA))
	{
		send_to_char("Huh?\n\r", ch);
		return;
	}
	else if ( ch->pcdata->powers[NPOWER_OPTICAL] < 6 )
	{
	    send_to_char("You have not learned the Optics Upgrade to 6.\n\r", ch);
	    return;
	}
	
    if ( arg1[0] == '\0' )
    {
	send_to_char( "Bomb who?\n\r", ch );
	return;
    }

    if ( ( victim = get_char_room( ch, arg1 ) ) == NULL )
    {
	send_to_char( "They aren't here.\n\r", ch );
	return;
    }

    if ( ch == victim )
    {
	send_to_char( "Not on yourself!\n\r", ch );
	return;
    }
	
    if ( ch->position == POS_FIGHTING )
    {
	send_to_char( "Not while fighting!\n\r", ch );
	return;
    }
    
	if (ch->move < 500)
	{
	send_to_char("You don't have enough movement points.\n\r", ch);
	return;
	}     
	  
    if ( victim->in_room == ch->in_room )
	{
	act("You toss your bomb onto the floor and put $N to sleep.",ch,NULL,victim,TO_CHAR);
	act("$n tosses a bomb onto the floor.  You feel sleepy.",ch,NULL,victim,TO_VICT);
	victim->position = POS_SLEEPING;
	ch->move -= 500;
	return;
	}
	
	return;
}

void do_ninjaarmor( CHAR_DATA *ch, char *argument )
{
    OBJ_INDEX_DATA *pObjIndex;
    OBJ_DATA *obj;
    char arg[MAX_INPUT_LENGTH];
    int vnum = 0;

    argument = one_argument( argument, arg );

    if (IS_NPC(ch)) return;

    if (!IS_CLASS(ch, CLASS_NINJA))
    {
	    send_to_char("Huh?\n\r",ch);
	    return;
    }

    if (arg[0] == '\0')
    {
	send_to_char("Please specify which piece of ninja armor you wish to make: Cloak Mask Dagger.\n\r",ch);
	return;
    }

    if ( ch->practice < 70 )
    {
        send_to_char("It costs 70 points of primal to create ninja equipment.\n\r",ch);
        return;
    }
    if      (!str_cmp(arg,"cloak"     )) vnum = 10006;
    else if (!str_cmp(arg,"mask"   )) vnum = 10005;
    else if (!str_cmp(arg,"dagger"    )) vnum = 8134;
    else
    {
	send_to_char("Please specify which piece of ninja armor you wish to make: Cloak Mask Dagger.\n\r",ch);
	return;
    }
    
    if ( vnum == 0 || (pObjIndex = get_obj_index( vnum )) == NULL)
    {
	send_to_char("Missing object, please inform a God.\n\r",ch);
	return;
    }
	ch->practice -= 100;
    obj = create_object(pObjIndex, 50);
    obj_to_char(obj, ch);
    act("$p appears in your hands.",ch,obj,NULL,TO_CHAR);
    act("$p appears in $n's hands.",ch,obj,NULL,TO_ROOM);
    return;
}
