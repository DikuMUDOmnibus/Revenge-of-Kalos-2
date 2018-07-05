/* Hydra class made by Arcane from the
   ideas of smoo, still needs to be
   fixed in fight.c(done).
--------------------------------------
   fight.c put in by Smoo, regen put
   in by Smoo, reach put in by Smoo
*/
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

void do_hydras( CHAR_DATA *ch, char *argument )
{
    char buf[MAX_STRING_LENGTH];
    char arg[MAX_INPUT_LENGTH];
    char lord[MAX_INPUT_LENGTH];
    CHAR_DATA *gch;

    one_argument( argument, arg );

    if (IS_NPC(ch)) return;
    if (!IS_CLASS(ch, CLASS_HYDRA))
    {
    send_to_char("Huh?\n\r",ch);
    return;
    }


send_to_char("The following hydra's roam the land.\n\r",ch);
send_to_char("#G[    #gName    #G] [ #gHits #G] [ #gMana #G] [ #gMove #G] [#gExp#G]\n\r",ch);
for ( gch = char_list; gch != NULL; gch = gch->next )
{
if ( IS_NPC(gch) ) continue;
if ( !IS_CLASS(gch, CLASS_HYDRA))
    continue;
if ( !str_cmp(ch->clan,gch->clan) )
{
    sprintf( buf,
    "#8[#3%-12s#8] [#3%-6d#8] [#3%-6d#8] [#3%-6d#8] [#3%7d#8]\n\r",
       capitalize( gch->name ),
       gch->hit,gch->mana,gch->move,
       gch->exp);
       send_to_char( buf, ch );
   }
   }
   return;
}


void do_hinfo( CHAR_DATA *ch, char *argument )
{
char buf[MAX_STRING_LENGTH];

if (IS_NPC(ch)) return;

    if (!IS_CLASS(ch, CLASS_HYDRA))
    {
        send_to_char("Huh?\n\r",ch);
        return;
    }

sprintf(buf,"Heads (%d). Powers (%d). Accuracy (%d). Twirl (%d).  \n\r",
ch->pcdata->powers[DISC_HYDRA_HEADS],ch->pcdata->powers[DISC_HYDRA_POWER],ch->pcdata->powers[DISC_HYDRA_ACCUR],ch->pcdata->powers[DISC_HYDRA_TWIRL]);
send_to_char(buf,ch);
return;
}


void do_gain( CHAR_DATA *ch, char *argument )
{
    char arg1 [MAX_INPUT_LENGTH];
    char buf[MAX_STRING_LENGTH]; 
    int       reqexp = 0;
    argument = one_argument( argument, arg1 );

    if (IS_NPC(ch)) return;

    if (!IS_CLASS(ch, CLASS_HYDRA))
    {
	send_to_char("Huh?\n\r",ch);
	return;
    }

    if (arg1[0] == '\0')
    {
		send_to_char("\n#uType one of the following\n\r",ch);
                send_to_char("#3Syntax is: #8gain head\n\r", ch);
                send_to_char("#3Syntax is: #8gain twirl\n\r", ch);
                send_to_char("#3Syntax is: #8gain accuracy\n\r", ch);
 return;
    }

       if (!str_cmp(arg1,"accuracy"))
    {
      
      if (ch->pcdata->powers[DISC_HYDRA_ACCUR] == 1) reqexp = 250000;
      if (ch->pcdata->powers[DISC_HYDRA_ACCUR] == 2) reqexp = 250000;
      if (ch->pcdata->powers[DISC_HYDRA_ACCUR] == 3) reqexp = 250000;
      if (ch->pcdata->powers[DISC_HYDRA_ACCUR] == 4) reqexp = 250000;
      if (ch->pcdata->powers[DISC_HYDRA_ACCUR] == 5) reqexp = 250000;
      if (ch->pcdata->powers[DISC_HYDRA_ACCUR] == 6) reqexp = 250000;

      if ( ch->pcdata->powers[DISC_HYDRA_ACCUR] > 6 )
        {
                send_to_char("#6You already have maximum accuracy.\n\r", ch);
                return;
        }
 
   if ( ch->exp < reqexp)
        {
 sprintf(buf,"You don't have the required (%d) exp\n\r",reqexp);
 send_to_char(buf,ch);
        return;
        }
 
   ch->pcdata->powers[DISC_HYDRA_ACCUR] += 1;
                ch->exp -= reqexp;
                send_to_char("#6You improve your #3accuracy.\n\r", ch);
        return;
}


	if (!str_cmp(arg1,"head")) 
    {
    	
      if (ch->pcdata->powers[DISC_HYDRA_HEADS] == 1) reqexp = 100000;
      if (ch->pcdata->powers[DISC_HYDRA_HEADS] == 2) reqexp = 200000;
      if (ch->pcdata->powers[DISC_HYDRA_HEADS] == 3) reqexp = 400000;
      if (ch->pcdata->powers[DISC_HYDRA_HEADS] == 4) reqexp = 800000;
      if (ch->pcdata->powers[DISC_HYDRA_HEADS] == 5) reqexp = 1600000;
      if (ch->pcdata->powers[DISC_HYDRA_HEADS] == 6) reqexp = 1600000;
      if (ch->pcdata->powers[DISC_HYDRA_HEADS] == 7) reqexp = 2500000;
      if (ch->pcdata->powers[DISC_HYDRA_HEADS] == 8) reqexp = 2500000;
      if (ch->pcdata->powers[DISC_HYDRA_HEADS] == 9) reqexp = 2500000;
      if (ch->pcdata->powers[DISC_HYDRA_HEADS] == 10) reqexp = 3500000;
      if (ch->pcdata->powers[DISC_HYDRA_HEADS] == 11) reqexp = 3500000;
      if (ch->pcdata->powers[DISC_HYDRA_HEADS] == 12) reqexp = 3500000;
      if (ch->pcdata->powers[DISC_HYDRA_HEADS] == 13) reqexp = 3500000;
      if (ch->pcdata->powers[DISC_HYDRA_HEADS] == 14) reqexp = 3800000;
      if (ch->pcdata->powers[DISC_HYDRA_HEADS] == 15) reqexp = 3800000;
      if (ch->pcdata->powers[DISC_HYDRA_HEADS] == 16) reqexp = 4000000;
      if (ch->pcdata->powers[DISC_HYDRA_HEADS] == 17) reqexp = 4000000;
      if (ch->pcdata->powers[DISC_HYDRA_HEADS] == 18) reqexp = 4300000;
      if (ch->pcdata->powers[DISC_HYDRA_HEADS] == 19) reqexp = 10000000;

 
     if ( ch->pcdata->powers[DISC_HYDRA_HEADS] > 19 )
	{
    		send_to_char("#6You already have maximum heads.\n\r", ch);
		return;
	}

      if ( ch->exp < reqexp)
	{
 sprintf(buf,"You don't have the required (%d) exp\n\r",reqexp);	
 send_to_char(buf,ch);
	return;
    	}
      else {
	
    	      ch->pcdata->powers[DISC_HYDRA_HEADS] += 1;
    		ch->exp -= reqexp;
    		send_to_char("#6You gain another #3Head.\n\r", ch);
              if (!IS_IMMORTAL(ch)) {
             sprintf(buf, "%s has gained another head!", ch->name);
             do_info(ch, buf); }
	      }
}
	if (!str_cmp(arg1,"twirl")) {
        if (ch->pcdata->powers[DISC_HYDRA_TWIRL]==0) reqexp=450000;
        else if (ch->pcdata->powers[DISC_HYDRA_TWIRL]==1) reqexp=550000;
        else if (ch->pcdata->powers[DISC_HYDRA_TWIRL]==2) reqexp=650000;
        else if (ch->pcdata->powers[DISC_HYDRA_TWIRL]==3) reqexp=1000000;
        else if (ch->pcdata->powers[DISC_HYDRA_TWIRL]==4) reqexp=1450000;
        else if (ch->pcdata->powers[DISC_HYDRA_TWIRL]==5) reqexp=1900000;
        else if (ch->pcdata->powers[DISC_HYDRA_TWIRL]==6) reqexp=2500000;
        else {
          send_to_char("You already have the maximum number twirl points!\n\r", ch);
          return;
        }
        if (ch->exp < reqexp) {
          sprintf(buf, "You don't have enough exp for that! You need %d exp.\n\r", reqexp);
          send_to_char(buf, ch);
          return;
          }
        else {
        ch->pcdata->powers[DISC_HYDRA_TWIRL] += 1;
        send_to_char("You gain some twirly points!\n\r", ch);
        ch->exp -= reqexp;
        }
        }

}


void do_transform( CHAR_DATA *ch, char *argument )
{

    CHAR_DATA *victim;
    char buf[MAX_STRING_LENGTH];
    char      arg [MAX_INPUT_LENGTH];
    argument = one_argument( argument, arg );

    if (IS_NPC(ch)) return;
 if (!IS_CLASS(ch, CLASS_HYDRA))
    {
        send_to_char("Huh?\n\r",ch);
        return;
    }

if (ch->pcdata->powers[DISC_HYDRA_POWER] < 7)

	{
        send_to_char("You don't have the power to transform someone.\n\r",ch);
	return;   
     }


    if (ch->pcdata->powers[DISC_HYDRA_HEADS] < 19)
    {
	send_to_char("You don't feel you are good enough to acuratly transform
him.\n\r",ch);
	return;
    }

    if ( arg[0] == '\0' )

    {
	send_to_char( "Transform Who?\n\r", ch );
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

 if ( victim->level != LEVEL_AVATAR && !IS_IMMORTAL(victim) )
 {
 send_to_char( "You can only guide avatars.\n\r", ch );
 return;
 }


    if ( ch == victim )

    {
	send_to_char( "You are already in a beast-like form, oh..just wanted to
comit beastiality, I see..\n\r", ch );
	return;
    }



    if (IS_CLASS(victim, CLASS_MAGE))

    {
	send_to_char( "You are unnable to transform a mage.\n\r", ch );
	return;
    }



    if (IS_CLASS(victim, CLASS_DEMON) || IS_SET(victim->special, SPC_CHAMPION))
    {
	send_to_char("They seem a bit too demonic for you to transform 
them.\n\r",ch);
	return;
    }



    if ( IS_CLASS(victim, CLASS_HIGHLANDER) )

    {
	send_to_char( "You are unnable to transform a highlander.\n\r", ch );
	return;
    }

    if (victim->exp <= 999999)
         {
act("$n tried to transform you in to a hydra, but you refuse knowing that",
ch,NULL,victim,TO_VICT);
act("you are not strong enough to choose the paths of the hydra's.", ch, NULL,
victim, TO_VICT);              
act("(note. 1 million minimum exp required.", ch, NULL, victim, TO_VICT);

              act("$N does not have the 1mil required exp to become a hydra.", ch,
NULL, victim, TO_CHAR);
              return;
           }

        if (IS_IMMUNE(victim,IMM_DEMON))
	{
        send_to_char ("They are immune to transformations.\n\r",ch);
        sprintf(buf, "%s just tried to transform you into a hydra, but you are 
immune. Type ready if you want to become one.", ch->name);
        send_to_char (buf, victim);
	return;
           }
           

    act("You let $n drink some of your hydra blood, and he quickly transforms.",
ch, NULL, victim, TO_CHAR);
    act("$N takes a sip of $n's hydra blood, and he transforms into another
fearsome beast.", ch, NULL, victim, TO_NOTVICT);
    act("You drink $n's blood in a long ritual, and you transform into a fearsome
HYDRA.", ch, NULL, victim, TO_VICT);
        sprintf(buf, "%s now walks amoung the fearsome HYDRAS.", victim->name);
        do_info(ch,buf);
if (IS_CLASS(victim, CLASS_VAMPIRE)) do_mortalvamp(victim,"");
    REMOVE_BIT(victim->act, PLR_HOLYLIGHT);
    REMOVE_BIT(victim->act, PLR_WIZINVIS);
    REMOVE_BIT(victim->special, SPC_SIRE);
    REMOVE_BIT(victim->special, SPC_ANARCH);
    victim->class=CLASS_HYDRA;
    victim->pcdata->powers[DISC_HYDRA_HEADS] = 1;
    victim->pcdata->powers[DISC_HYDRA_ACCUR] = 1;
    victim->pcdata->powers[DISC_HYDRA_TWIRL] = 0;
    victim->pcdata->powers[DISC_HYDRA_POWER] = 0;
    victim->special=0;
    victim->pcdata->stats[UNI_RAGE] = 0;
    SET_BIT(victim->act, PLR_HOLYLIGHT);
    free_string(victim->morph);
    victim->clan=str_dup("");
    free_string(victim->clan);
    victim->clan=str_dup("");
    free_string(victim->lord);
    save_char_obj(ch);
    save_char_obj(victim);
    return;
}

void do_ready( CHAR_DATA *ch, char *argument )

{
    char      arg [MAX_INPUT_LENGTH];
    argument = one_argument( argument, arg );
    if (IS_NPC(ch)) return;
    if (IS_IMMUNE(ch, IMM_DEMON))
    {

send_to_char("You are ready for the transformation in to a gruesome Hydra.\n\r",ch);
	REMOVE_BIT(ch->immune, IMM_DEMON);
	return;
    }

    send_to_char("Your body settles because it is no longer preparing for the 
transformation.\n\r",ch);
    SET_BIT(ch->immune, IMM_DEMON);
    return;

}


void do_powers( CHAR_DATA *ch, char *argument )
{
    char arg1 [MAX_INPUT_LENGTH];
    char buf[MAX_STRING_LENGTH];
    int improve;
    improve = PMONK; 
    
    argument = one_argument( argument, arg1 );
    
    if (IS_NPC(ch)) return;

    if (!IS_CLASS(ch, CLASS_HYDRA))
    {
	send_to_char("Huh?\n\r",ch);
	return;
    }

    if (arg1[0] == '\0')
    {
	    send_to_char("     Powers.\n\r",ch);
	    send_to_char("   Type: #3powers #7<power name>\n\r",ch);
	    if ( ch->pcdata->powers[DISC_HYDRA_POWER] < 1 ) send_to_char("#1A#3ware\n\r", ch);
	    if ( ch->pcdata->powers[DISC_HYDRA_POWER] < 2 )
send_to_char("#1R#3each\n\r", ch);
	    if ( ch->pcdata->powers[DISC_HYDRA_POWER] < 3 ) send_to_char("#1F#3luxsion\n\r", ch);
	    if ( ch->pcdata->powers[DISC_HYDRA_POWER] < 4 ) send_to_char("#1S#3phere of Diamonds\n\r", ch);
	    if ( ch->pcdata->powers[DISC_HYDRA_POWER] < 5 ) send_to_char("#1I#3nterference\n\r", ch);
	    if ( ch->pcdata->powers[DISC_HYDRA_POWER] < 6 ) send_to_char("#1R#3egenerate\n\r", ch);
	    if ( ch->pcdata->powers[DISC_HYDRA_POWER] < 7 ) send_to_char("#1T#3ransform\n\r", ch);
		return;
    }


	if (!str_cmp(arg1,"aware")) 
    {
    	if ( ch->pcdata->powers[DISC_HYDRA_POWER] > 1 )
    		send_to_char("#6You already have the #3Aware Power.\n\r", ch);
    	else if ( ch->practice < 10)
    		send_to_char("You don't have the #310#8 required primal.\n\r", ch);
    	else
    	{
            ch->pcdata->powers[DISC_HYDRA_POWER] += 1;
    		ch->practice -= 10;
    	SET_BIT(ch->pcdata->stats[UNI_AFF], VAM_NIGHTSIGHT);
	SET_BIT(ch->affected_by, AFF_SHADOWSIGHT);
	    send_to_char("#6You master the #3Aware Power.\n\r", ch);
    	}
    	return;
    }
    else if (!str_cmp(arg1,"reach"))
    {
    	if ( ch->pcdata->powers[DISC_HYDRA_POWER] > 1 )
    		send_to_char("#6You already have the #3Reach Power.\n\r",
ch);
    	else if ( ch->pcdata->powers[DISC_HYDRA_POWER] < 1 )
    		send_to_char("#6You need all the powers before this one to receive this power.\n\r", ch);
    	else if ( ch->practice < 20)
    		send_to_char("You don't have the #320#8 required primal.\n\r", ch);
    	else
    	{
            ch->pcdata->powers[DISC_HYDRA_POWER] += 1;
    		ch->practice -= 20;
    		send_to_char("#6You master the #3Reach Power.\n\r", ch);
    	}
    	return;
    }
    else if (!str_cmp(arg1,"fluxsion"))
    {
    	if ( ch->pcdata->powers[DISC_HYDRA_POWER] > 2 )
    		send_to_char("#6You already have the #3Fluxion Power.\n\r", ch);
    	else if ( ch->pcdata->powers[DISC_HYDRA_POWER] < 2 )
    		send_to_char("#6You need all the powers before this one to receive this power.\n\r", ch);
    	else if ( ch->practice < 30)
    		send_to_char("You don't have the #330#8 required primal.\n\r", ch);
    	else
    	{
            ch->pcdata->powers[DISC_HYDRA_POWER] += 1;
    		ch->practice -= 30;
    		send_to_char("#6You master the #3Fluxion Power.\n\r", ch);
    	}
    	return;
    }
    else if (!str_cmp(arg1,"sphereofdiamonds"))
    {
    	if ( ch->pcdata->powers[DISC_HYDRA_POWER] > 3 )
    		send_to_char("#6You already have the #3Sphere of diamonds
power.\n\r", ch);
    	else if ( ch->pcdata->powers[DISC_HYDRA_POWER] < 3 )
    		send_to_char("#6You need all the powers before this one to receive this power.\n\r", ch);
    	else if ( ch->practice < 40)
    		send_to_char("You don't have the #340#8 required primal.\n\r", ch);
    	else
    	{
            ch->pcdata->powers[DISC_HYDRA_POWER] += 1;
    		ch->practice -= 40;
    		send_to_char("#6You master the #3Sphere of Diamonds Power.\n\r", ch);
    	}
    	return;
    }
    else if (!str_cmp(arg1,"interference"))
    {
    	if ( ch->pcdata->powers[DISC_HYDRA_POWER] > 4 )
    		send_to_char("#6You already have the #Interference.\n\r", ch);
    	else if ( ch->pcdata->powers[DISC_HYDRA_POWER] < 4 )
    		send_to_char("#6You need all the powers before this one to receive
this power.\n\r", ch);
    	else if ( ch->practice < 50)
    		send_to_char("You don't have the #350#8 required primal.\n\r", ch);
    	else
    	{
            ch->pcdata->powers[DISC_HYDRA_POWER] += 1;
   		ch->practice -= 50;
    		send_to_char("#6You master the #3Interference power.\n\r", ch);
    	}
    	return;
    }
    else if (!str_cmp(arg1,"regenerate"))
    {
    	if ( ch->pcdata->powers[DISC_HYDRA_POWER] > 5 )
    		send_to_char("#6You already have the #3Regenerate Power.\n\r", ch);
    	else if ( ch->pcdata->powers[DISC_HYDRA_POWER] < 5 )
    		send_to_char("#6You need all the powers before this one to receive this power.\n\r", ch);
    	else if ( ch->practice < 60)
    		send_to_char("You don't have the #360#8 required primal.\n\r", ch);
    	else
    	{
            ch->pcdata->powers[DISC_HYDRA_POWER] += 1;
    		ch->practice -= 60;
    		send_to_char("#6You master the #3Regenerate power.\n\r", ch);
    	}
    	return;
    }
    else if (!str_cmp(arg1,"transform"))
    {
    	if ( ch->pcdata->powers[DISC_HYDRA_POWER] > 6 )
    		send_to_char("#6You already have the #3Transform power.\n\r", ch);
    	else if ( ch->pcdata->powers[DISC_HYDRA_POWER] < 6 )
    		send_to_char("#6You need all the powers before this one to receive this power.\n\r", ch);
    	else if ( ch->practice < 70)
    		send_to_char("You don't have the #370#8 required primal.\n\r", ch);
    	else
    	{
            ch->pcdata->powers[DISC_HYDRA_POWER] += 1;
    		ch->practice -= 70;
    		send_to_char("#8You master the #3Transform power.\n\r", ch);
    	}
    	return;
    }
	sprintf(buf,"Powers Learned
(%d).\n\r",ch->pcdata->powers[DISC_HYDRA_POWER]);
	send_to_char(buf,ch);

	return;
}

void hydra_regen (CHAR_DATA *ch)
{
  if (!IS_CLASS(ch, CLASS_HYDRA)) {
     send_to_char("Your not a hydra!\n\r", ch);
     return;
      }
  if (ch->pcdata->powers[DISC_HYDRA_REGEN] == 2) {
      ch->pcdata->powers[DISC_HYDRA_REGEN] = 1;
      send_to_char("Regen toggled off.\n\r", ch);
      return;
       }
  if (ch->pcdata->powers[DISC_HYDRA_REGEN] > 2) {
      ch->pcdata->powers[DISC_HYDRA_REGEN] = 2;
      send_to_char("Regen toggled on.\n\r", ch);
      return;
       }
  if (ch->pcdata->powers[DISC_HYDRA_REGEN] < 2) {
      ch->pcdata->powers[DISC_HYDRA_REGEN] = 2; 
      send_to_char("Regen toggled on.\n\r", ch);
      return;
       }
return;
}

void do_reach( CHAR_DATA *ch, char *argument)
{
    CHAR_DATA *victim;
    char buf[MAX_STRING_LENGTH];
    char arg[MAX_INPUT_LENGTH];
    argument = one_argument(argument, arg);

    if ( IS_NPC(ch) )
	return;

    if (!IS_CLASS(ch, CLASS_HYDRA) && !IS_CLASS(ch, CLASS_VAMPIRE))
	{
         send_to_char("Huh?\n\r",ch);
	   return;
	}
if (IS_CLASS(ch, CLASS_VAMPIRE) && ch->pcdata->condition[COND_THIRST] <
15) {
    send_to_char("You do not have enough blood to go that far..", ch);
    return;
    }

if (ch->pcdata->powers[DISC_HYDRA_POWER] < 3 && !IS_CLASS(ch,
CLASS_VAMPIRE))
	{
	   send_to_char("You need the reach power to reach..\n\r",ch);
	   return;
	}


    if ( arg[0] == '\0' )
    {
	if (IS_CLASS(ch, CLASS_HYDRA)) 
send_to_char( "Who do you want to extend your heads to?\n\r", ch);
        else
send_to_char( "Send a stream of blood to who?\n\r", ch);
	return;
  
    }

    if ( ( victim = get_char_world( ch, arg ) ) == NULL )
    {
	send_to_char( "They aren't here.\n\r", ch );
	return;
    }
 
	if  (!IS_NPC(victim) && IS_IMMUNE(victim, IMM_SUMMON) && !IS_IMMUNE(victim, IMM_TRANSPORT))
	{
        if (IS_CLASS(ch, CLASS_HYDRA))
	send_to_char("After all your searching, you couldn't find them.\n\r",ch);
        else
        send_to_char("#rYour blood couldn't find a path to them..\n\r", ch);
	return;
}

 if (ch == victim)
    {
        if (IS_CLASS(ch, CLASS_HYDRA))
        send_to_char("You hug yourself with your many heads.\n\r",ch);
        else
        send_to_char("Hey ..! That was a quick ride!\n\r", ch);
	  return;
    }

    if (victim->in_room->vnum == ch->in_room->vnum)
    {
	  send_to_char("After much searching, you realise that he's already here!\n\r",ch);
        return;
    }

    char_from_room(ch);
    char_to_room(ch,victim->in_room);
    if (IS_NPC(victim))
    {
    if (IS_CLASS(ch, CLASS_HYDRA))
    sprintf(buf,"You extend your heads in all dirrections to find %s!\n\r",victim->name);
    else
sprintf(buf,"You blead out a river of blood going in the dirrection of %s\n\r", victim->name);
    send_to_char(buf, ch);
    }

    if (!IS_NPC(victim))
    {
    if (IS_CLASS(ch, CLASS_HYDRA))
    sprintf(buf,"You extend your heads in all dirrections to find %s!\n\r",victim->name);
    else
sprintf(buf,"You blead out a river of blood going in the dirrection of %s", victim->name);
    send_to_char(buf, ch);
    }
    if (IS_CLASS(ch, CLASS_VAMPIRE)) {
    sprintf(buf, "You ride down the river and get to %s.\n\r", victim->name);
    send_to_char(buf, ch);}
    if (IS_CLASS(ch, CLASS_HYDRA)) {
    act("$n runs into the room looking for someone in particular.",ch,NULL,NULL,TO_NOTVICT);
    act("A large head runs in and pulls $n in through his neck.",ch,NULL,victim,TO_VICT);
    }
    else
    {
    act("A large river of blood spills into the room, followed by $n", ch, NULL, victim, TO_VICT);
    act("A large river of blood spills into the room, followed by $n", ch, NULL, victim, TO_NOTVICT);
    }
    do_look(ch, "auto");
    if (IS_CLASS(ch, CLASS_VAMPIRE))
    gain_condition( ch, COND_THIRST, -15 );
    WAIT_STATE(ch, 12);
    return;
}

