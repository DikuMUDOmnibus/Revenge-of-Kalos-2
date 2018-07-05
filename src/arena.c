#if defined(macintosh)
#include <types.h>
#else
#include <sys/types.h>
#include <sys/time.h>
#endif
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include "merc.h"

int	arena;
int	TOTAL_BID;
/*=======================================================================*
 * function: do_challenge                                                *
 * purpose: sends initial arena match query                              *
 * written by: Doug Araya (whiplash@tft.nacs.net) 6-10-96                *
 *=======================================================================*/

void do_aclaim( CHAR_DATA *ch, char *argument )
{
 if(ch->gladiator == NULL)
 {
 send_to_char("You did not bid.",ch);
 return;
 }

if (arena == FIGHT_BUSY)
{
send_to_char("Wait until the arena is over.",ch);
return;
}

/*
if(ch->gladiator == )
{
        ch->gladiator = 0;
        ch->pcdata->quest += ch->pcdata->plr_wager;
        send_to_char("You claim your winning bets",ch);
	return;
}
*/

send_to_char("You did not bid on the winner.",ch);
return;
}

void do_cleararena( CHAR_DATA *ch, char *argument )
{
arena = FIGHT_OPEN;
return;
}
void do_removearena( CHAR_DATA *ch, char *argument )
{
    char arg[MAX_INPUT_LENGTH];
    char buf[MAX_STRING_LENGTH];
    CHAR_DATA *victim;

    one_argument( argument, arg );
    if ( arg[0] == '\0' )
    {
    send_to_char( "Clear who's arena flags?\n\r", ch );
    send_to_char( "#3Syntax:#8 removearena <player>\n\r", ch );
    return;
    }

    if ( ( victim = get_char_world( ch, arg ) ) == NULL )
    {
   send_to_char( "They aren't here.\n\r", ch );
   return;
    }

    arena = FIGHT_OPEN;

if (IS_SET(victim->act,PLR_CHALLENGER) || IS_SET(victim->act,PLR_CHALLENGED))
{
victim->challenged = NULL;
victim->challenger = NULL;
REMOVE_BIT(victim->act,PLR_CHALLENGER);
REMOVE_BIT(victim->act,PLR_CHALLENGED);
send_to_char("You have been cleared from the arena.",victim);
send_to_char("Ok.",ch);
return;
}
send_to_char("They have no active arena flags.",ch);
return;
}


void do_lockarena( CHAR_DATA *ch, char *argument )
{
    CHAR_DATA *victim;
    char      arg1[MAX_INPUT_LENGTH];

    argument = one_argument( argument, arg1 );

    if (!IS_IMMORTAL(ch)) return;

    if ( arg1[0] == '\0' )
    {
	send_to_char( "syntax: lockarena ON or OFF\n\r", ch );
	return;
    }

	if (!str_cmp(arg1,"ON")) 
	{
	arena = FIGHT_LOCK;
	send_to_char("The arena is now locked.",ch);
	return;
	}

        else if (!str_cmp(arg1,"OFF"))
	{
	arena = FIGHT_OPEN;
	send_to_char("The Arena is now open.",ch);
	return;
	}
return;
}


void do_achallenge(CHAR_DATA *ch, char *argument)
{
  CHAR_DATA *victim; 
  char buf[MAX_STRING_LENGTH]; 
  DESCRIPTOR_DATA *d;

/* == First make all invalid checks == */
 if(IS_NPC(ch))
  return; 

if (ch->race < 5)
{
	send_to_char("You need a minimum of 5 status",ch);
	return;
}

 if( arena == FIGHT_START )
  {
  send_to_char("Sorry, some one else has already started a challenge, please try later.\n\r",ch);
  return;
  }

 if( arena == FIGHT_BUSY )
  {
  send_to_char("Sorry, there is a fight in progress, please wait a few moments.\n\r",ch);
  return; 
  }

 if(arena == FIGHT_LOCK )
  {
  send_to_char("Sorry, the arena is currently locked from use.\n\r",ch);
  return;
  }

 if(IS_SET(ch->act,PLR_CHALLENGED))
  {
  send_to_char("You have already been challenged, either AGREE or DECLINE first.\n\r",ch);
  return; 
  }

 if(ch->hit < ch->max_hit)
  {
  send_to_char("You must be fully healed to fight in the arena.\n\r",ch);
  return;
  }

 if(argument[0] == '\0')
  {
  send_to_char("You must specify whom you wish to challenge.\n\r",ch);
  return;
  }

 if((victim = get_char_world(ch,argument)) == NULL)
  {
  send_to_char("They are not playing.\n\r",ch);
  return;
  }

 if(IS_NPC(victim) || IS_IMMORTAL(victim) || victim == ch )
  {
  send_to_char("You cannot challenge NPC's or yourself.\n\r",ch);
  return;
  }

 if(IS_SET(victim->act,PLR_CHALLENGER))
  {
  send_to_char("They have already challenged someone else.\n\r",ch);
  return;
  }

 if(victim->fighting != NULL )
  {
  send_to_char("That person is engaged in battle right now.\n\r",ch); 
  return; 
  }

 if(victim->hit < victim->max_hit)
  {
  send_to_char("That player is not healthy enough to fight right now.\n\r",ch);
  return;
  }

 if ( victim->desc == NULL )
  {
  send_to_char("That player is linkdead at the moment, try them later.\n\r",ch);
   return;
  }


 
/* == Now for the challenge == */

ch->challenged = victim;
SET_BIT(ch->act,PLR_CHALLENGER);

victim->challenger = ch;
SET_BIT(victim->act,PLR_CHALLENGED);

arena = FIGHT_START;

send_to_char("Challenge has been sent\n\r",ch);
act("$n has challenged you to a death match.",ch,NULL,victim,TO_VICT);
sprintf(buf,"#8[#CArena#8] #3%s #8has challenged #3%s #8to a death duel.\n\r",
        ch->name, victim->name);
for ( d = descriptor_list; d; d = d->next )
 {
   if( d->connected == CON_PLAYING)
    {

       send_to_char( buf, d->character );
    }
  }

send_to_char("#3.#o_________(Kalos Arena)_________#3.\n\r",victim);
sprintf(buf,"#8|#C %s vs %s                   #8|\n\r",ch->name,victim->name);
send_to_char(buf,victim);
send_to_char("#8|#C                               #8|\n\r",victim);
send_to_char("#8|#C Type:                         #8|\n\r",victim);
sprintf(buf,"#8|#C AAGREE %s to accept.       #8|\n\r",ch->name);
send_to_char(buf,victim);
sprintf(buf,"#8|#C ADECLINE %s to refuse.      #8|\n\r",ch->name);
send_to_char(buf,victim);
send_to_char("#8|#C                               #8|\n\r",victim);
send_to_char("#8|#C                               #8|\n\r",victim);
send_to_char("#3.#o________________________________#3.\n\r",victim);

 return;
}



/*=======================================================================*
 * function: do_accept                                                   *
 * purpose: to accept the arena match, and move the players to the arena *
 * written by: Doug Araya (whiplash@tft.nacs.net) 6-10-96                *
 *=======================================================================*/

void do_aagree(CHAR_DATA *ch, char *argument)
{
 float odd1, odd2;
 float lvl1, lvl2;
 DESCRIPTOR_DATA *d;
 CHAR_DATA *victim; 
 char buf1[MAX_STRING_LENGTH]; 
 char buf2[MAX_STRING_LENGTH];
 char buf3[MAX_STRING_LENGTH];
 int char_room; 
 int vict_room; 

 /*== the room VNUM's for our arena.are ==*/
 /* we use 1051 thru 1066 for a 4x4 arena */
 char_room = number_range(50,68);
 vict_room = number_range(50,68);


/* == first make all invalid checks == */
 if(IS_NPC(ch))
 return;
 if( !IS_SET(ch->act,PLR_CHALLENGED) )
  {
  send_to_char("You have not been challenged.\n\r",ch);
  return;
  }
 if( arena == FIGHT_BUSY )
  {
  send_to_char("Sorry, there is a fight in progress, please wait a few moments.\n\r",ch);
  return;
  }

 if(arena == FIGHT_LOCK )
  {
  send_to_char("Sorry, the arena is currently locked from use.\n\r",ch);
  return;
  }

 if(argument[0]=='\0')

  {
  send_to_char("You must specify whose challenge you wish to accept.\n\r",ch);
  return;
  }

 if((victim = get_char_world(ch,argument)) == NULL)
  {
  send_to_char("They aren't logged in!\n\r",ch);
  return;
  }

 if(victim == ch)
  {
  send_to_char("You haven't challenged yourself!\n\r",ch);
  return;
  }



 if(!IS_SET(victim->act,PLR_CHALLENGER) || victim != ch->challenger )
  {
  send_to_char("That player hasn't challenged you!\n\r",ch); 
  return; 
  }

/* == now get to business == */
send_to_char("You have accepted the challenge!\n\r",ch);
act("$n accepts your challenge!",ch,NULL,victim,TO_VICT);
/* == announce the upcoming event == */

lvl1 = ch->hit;
lvl2 = victim->hit;
odd1 = ( lvl1 / lvl2 );
odd2 = ( lvl2 / lvl1 );
sprintf(buf1,"#1[#3A#orena#1] #3%s #g(#3%d wins#g) (#3%d losses#3) #oOdds:%f\n\r",
victim->name,victim->pcdata->awins,victim->pcdata->alosses, odd1 );

sprintf(buf2,"#1[#3A#orena#1] #3%s #g(#3%d wins#g) (#3%d losses#3) #oOdds:%f\n\r", 
ch->name,ch->pcdata->awins,ch->pcdata->alosses, odd2 ); 

strcpy(buf3,"#r[#1A#3rena#r] #7To wager on the fight, type: #3qbet (amount)
(player name)\n\r");

for ( d = descriptor_list; d; d = d->next )
  {
     if( d->connected == CON_PLAYING)
     {
        send_to_char( buf1, d->character );
        send_to_char( buf2, d->character );
        send_to_char( buf3, d->character );
        d->character->gladiator = NULL;
     }
  }

/* == now move them both to an arena for the fun == */
send_to_char("You make your way into the arena.\n\r",ch);
char_from_room(ch); 
char_to_room(ch,get_room_index(char_room));
do_look(ch, "auto");
// SET_BIT(ch->act,PLR_SILENCE);
// SET_BIT(ch->act,PLR_NO_TELL);

send_to_char("You make your way to the arena.\n\r",victim);
char_from_room(victim); 
char_to_room(victim,get_room_index(vict_room)); 
do_look(victim, "auto");
// SET_BIT(victim->act,PLR_SILENCE);

// SET_BIT(victim->act,PLR_NO_TELL);
arena  = FIGHT_BUSY; 
return; 
}


/*=======================================================================*
 * function: do_decline                                                  *
 * purpose: to chicken out from a sent arena challenge                   *
 * written by: Doug Araya (whiplash@tft.nacs.net) 6-10-96                *
 *=======================================================================*/

void do_adecline(CHAR_DATA *ch, char *argument )

{
  CHAR_DATA *victim; 
  char buf[MAX_STRING_LENGTH];
  DESCRIPTOR_DATA *d;

/*== make all invalid checks == */

  if(IS_NPC(ch))
   return;

 if( !IS_SET(ch->act,PLR_CHALLENGED) )
  {
  send_to_char("You have not been challenged.\n\r",ch);
  return;
  }

	 if(argument[0]=='\0')
  {
  send_to_char("You must specify whose challenge you wish to decline.\n\r",ch);
  return;
  }

  

 if((victim = get_char_world(ch,argument)) == NULL)
  {
  send_to_char("They aren't logged in!\n\r",ch);
  return;
  }



 if(!IS_SET(victim->act,PLR_CHALLENGER) || victim != ch->challenger )
  {
  send_to_char("That player hasn't challenged you.\n\r",ch);
  return;
  }

 if(victim == ch)
 return; 



/*== now actually decline == */
victim->challenged = NULL;
REMOVE_BIT(victim->act,PLR_CHALLENGER); 
ch->challenger = NULL;
REMOVE_BIT(ch->act,PLR_CHALLENGED);
arena = FIGHT_OPEN;
send_to_char("Challenge declined!\n\r",ch);
act("$n has declined your challenge.",ch,NULL,victim,TO_VICT);
sprintf(buf,"[Arena] %s has declined %s's challenge.\n\r",
ch->name, victim->name);

 for ( d = descriptor_list; d; d = d->next )
  {
     if( d->connected == CON_PLAYING)
     {
	ADD_COLOUR(ch,buf,L_RED);
        send_to_char( buf, d->character );
     }
  }
return;
}



/*======================================================================*
 * function: do_bet                                                     *
 * purpose: to allow players to wager on the outcome of arena battles   *
 * written by: Doug Araya (whiplash@tft.nacs.net) 6-10-96               *
 *======================================================================*/

void do_qbet(CHAR_DATA *ch, char *argument)

 {
 char arg[MAX_INPUT_LENGTH]; 
 char buf[MAX_STRING_LENGTH]; 
 CHAR_DATA *fighter; 
 int wager; 

 argument = one_argument(argument, arg); 
 if(argument[0] == '\0' || !is_number(arg))
  {
  send_to_char("Syntax: #8QBET #g[#rqps amount] #B[#3player]\n\r",ch); 

  return;

  }

 if(ch->gladiator != NULL)
  {
  send_to_char("You have already placed a bet on this fight.\n\r",ch);
  return;
  }

/*== disable the actual fighters from betting ==*/
 if(IS_SET(ch->act,PLR_CHALLENGER) || IS_SET(ch->act,PLR_CHALLENGED))
  {
  send_to_char("You can't bet on this battle.\n\r",ch); 
  return; 
  }


 fighter = get_char_world(ch,argument);


/*== make sure the choice is valid ==*/
 if( fighter == NULL )
  {
  send_to_char("That player is not logged in.\n\r",ch);
  return;
  }

 if( IS_NPC(fighter) )
  {
  send_to_char("Why bet on a mob? They aren't fighting...\n\r",ch);
  return;

  }
 if( !IS_SET(fighter->in_room->room_flags,ROOM_ARENA) )
  {
  send_to_char("That player is not in the arena.\n\r",ch); 
  return; 
  }

/*== do away with the negative number trickery ==*/
 if(!str_prefix("-",arg))
  {
  send_to_char("Error: Invalid argument!\n\r",ch); 
  return; 
  }
 wager   = atoi(arg);
 if(wager > 200 || wager < 1)

  {
  send_to_char("Wager range is between 1 and 200\n\r",ch);
  return; 
  }



/*== make sure they have the cash ==*/
 if(wager >  ch->pcdata->quest)
  {
  send_to_char("You don't have that much qps to wager!\n\r",ch); 
  return; 
  }


/*== now set the info ==*/
ch->gladiator = fighter;
ch->pcdata->plr_wager = wager;
sprintf(buf,"You have placed a %d qps wager on %s\n\r",
wager,fighter->name);
send_to_char(buf,ch);
TOTAL_BID = TOTAL_BID + wager;
 sprintf(buf,"#3%s #rhas placed #1%d #ron #3%s!",ch->name,wager,fighter->name);
 do_info(ch,buf);
 sprintf(buf,"#1T#rotal bids for this duel:#3%d",TOTAL_BID);
 do_info(ch,buf);
 sprintf(buf,"#3%s #rhas placed #1%d #rquest points you.",ch->name,wager);
 send_to_char(buf,ch);
return; 
}

void do_expbet(CHAR_DATA *ch, char *argument)

 {
 char arg[MAX_INPUT_LENGTH]; 
 char buf[MAX_STRING_LENGTH]; 
 CHAR_DATA *fighter; 
 int wager; 

 argument = one_argument(argument, arg); 
 if(argument[0] == '\0' || !is_number(arg))
  {
  send_to_char("Syntax: BET [amount] [player]\n\r",ch); 

  return;

  }

 if(ch->gladiator != NULL)
  {
  send_to_char("You have already placed a bet on this fight.\n\r",ch);
  return;
  }

/*== disable the actual fighters from betting ==*/
 if(IS_SET(ch->act,PLR_CHALLENGER) || IS_SET(ch->act,PLR_CHALLENGED))
  {
  send_to_char("You can't bet on this battle.\n\r",ch); 
  return; 
  }


 fighter = get_char_world(ch,argument);


/*== make sure the choice is valid ==*/
 if( fighter == NULL )
  {
  send_to_char("That player is not logged in.\n\r",ch);
  return;
  }

 if( IS_NPC(fighter) )
  {
  send_to_char("Why bet on a mob? They aren't fighting...\n\r",ch);
  return;

  }
 if( !IS_SET(fighter->in_room->room_flags,ROOM_ARENA) )
  {
  send_to_char("That player is not in the arena.\n\r",ch); 
  return; 
  }

/*== do away with the negative number trickery ==*/
 if(!str_prefix("-",arg))
  {
  send_to_char("Error: Invalid argument!\n\r",ch); 
  return; 
  }
 wager   = atoi(arg);
 if(wager > 250000 || wager < 1)

  {
  send_to_char("Wager range is between 1 and 250000 exp\n\r",ch);
  return; 
  }



/*== make sure they have the cash ==*/
 if(wager > ch->exp)
  {
  send_to_char("You don't have that much exp to wager!\n\r",ch); 
  return; 
  }


/*== now set the info ==*/
ch->gladiator = fighter;
ch->pcdata->plr_wager = wager;
sprintf(buf,"You have placed a %d exp wager on %s\n\r",
wager,fighter->pcdata->switchname);
send_to_char(buf,ch);
return; 
}





	
