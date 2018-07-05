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

void do_enroll( CHAR_DATA *ch, char *argument )
{

    CHAR_DATA *victim;
    char buf[MAX_STRING_LENGTH];
    char arg[MAX_INPUT_LENGTH];
    argument = one_argument( argument, arg );

    if (IS_NPC(ch)) return;


    if (!IS_CLASS(ch, CLASS_SHATAN))
    {
	send_to_char("Huh?\n\r",ch);
	return;
    }
    if ( arg[0] == '\0' )
    {
	send_to_char( "Enroll who in the ways of the devils.\n\r", ch );
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
    if ( ch == victim )
    {
	send_to_char( "You already follow the all mighty satan.\n\r", ch );
	return;
    }

    if (IS_CLASS(victim, CLASS_MAGE))

    {
	send_to_char( "You are unnable to transform a mage.\n\r", ch );
	return;
    }


    if ( IS_CLASS(victim, CLASS_HIGHLANDER) )
    {
	send_to_char( "You are unnable to transform a highlander.\n\r", ch );
	return;
    }

    if (victim->max_hit < 5001)
         {

act("$n tried to enroll you in the arts of the shatan, but you do not have the required 5,000 hitpoints.", ch, NULL, victim, TO_VICT);
act("$N does not have the 5,000 uired hp to enroll in the ranks of the shatan.", ch, NULL, victim, TO_CHAR);
         return;
         }

           
act("You begin to inform $N in the way of the Shatan.", ch, NULL, victim, TO_CHAR);
act("$n has enrolled $N into the ranks of the Shatan.", ch, NULL, victim, TO_NOTVICT);
act("$n begins to chant as your body begins to transform into a follower of the shatan.", ch, NULL, victim, TO_VICT);
victim->class=CLASS_SHATAN;
victim->pcdata->powers[SHATAN_POWER] = 0;
victim->special=0;
if (IS_CLASS(victim, CLASS_VAMPIRE)) do_mortalvamp(victim,"");
REMOVE_BIT(victim->act, PLR_HOLYLIGHT);
REMOVE_BIT(victim->act, PLR_WIZINVIS);
REMOVE_BIT(victim->special, SPC_SIRE);
REMOVE_BIT(victim->special, SPC_ANARCH);
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

void do_warps( CHAR_DATA *ch, char *argument )
{
    char buf[MAX_INPUT_LENGTH];

if (IS_NPC(ch)) return;   
if (!IS_CLASS(ch, CLASS_SHATAN)) 
    { 
    send_to_char("Huh?\n\r",ch); 
    return;
   }
   send_to_char("#2-=#0(#6**#0)#2=- #6Attained Warps#2-=#0(#6**#0)#2=-#n\n\r",ch);
   sprintf(buf, (".%s."), ch->pcdata->warp);
   send_to_char(buf, ch);     
if (IS_SET(ch->pcdata->warp, WARP_CBODY      )) send_to_char("Your body is
protected by a
indestructable crystal shell.\n\r",ch);
if (IS_SET(ch->pcdata->warp, WARP_SBODY      )) send_to_char("Your skin is as hard as
steel.\n\r",ch);
if (IS_SET(ch->pcdata->warp, WARP_STRONGARMS )) send_to_char("Your arms are incredibly
strong.\n\r",ch);
if (IS_SET(ch->pcdata->warp, WARP_STRONGLEGS )) send_to_char("Your legs are incredibly
strong.\n\r",ch);
if (IS_SET(ch->pcdata->warp, WARP_VENOMTONG  )) send_to_char("Your tongue is long and
venomous.\n\r",ch);
if (IS_SET(ch->pcdata->warp, WARP_SPIKETAIL  )) send_to_char("Your tail fires deadly
spikes during combat.\n\r",ch);
if (IS_SET(ch->pcdata->warp, WARP_BADBREATH  )) send_to_char("Your breath is putrid and
deadly.\n\r",ch);
if (IS_SET(ch->pcdata->warp, WARP_QUICKNESS  )) send_to_char("You have incredible
speed.\n\r",ch);
if (IS_SET(ch->pcdata->warp, WARP_STAMINA    )) send_to_char("You have increased stamina,reducing the damage you take.\n\r",ch);
if (IS_SET(ch->pcdata->warp, WARP_HUNT       )) send_to_char("Your heightened senses 
enable you to hunt people.\n\r",ch);
if (IS_SET(ch->pcdata->warp, WARP_DEVOUR     )) send_to_char("You have the ability to
devour your opponents, sending them into the pits of Hell.\n\r",ch);
if (IS_SET(ch->pcdata->warp, WARP_TERROR     )) send_to_char("Your features are so horrid 
that they may stun those who look at you.\n\r",ch);
if (IS_SET(ch->pcdata->warp, WARP_REGENERATE )) send_to_char("Your body has the ability to 
regenerate incredibly fast.\n\r",ch);
if (IS_SET(ch->pcdata->warp, WARP_STEED      )) send_to_char("Your mounts transform into
hideous shatans.\n\r",ch);
if (IS_SET(ch->pcdata->warp, WARP_WEAPON     )) send_to_char("You have the power to
transform into a deadly battle axe.\n\r",ch);
if (IS_SET(ch->pcdata->warp, WARP_INFIRMITY  )) send_to_char("Your body has been afflicted
by a terrible infirmity.\n\r",ch);
if (IS_SET(ch->pcdata->warp, WARP_GBODY      )) send_to_char("Your skin is made of a
fragile glass.\n\r",ch);
if (IS_SET(ch->pcdata->warp, WARP_SCARED     )) send_to_char("You are incredibly scared of
combat.\n\r",ch);
if (IS_SET(ch->pcdata->warp, WARP_MAGMA      )) send_to_char("Your body is composed of
deadly magma.\n\r",ch);
if (IS_SET(ch->pcdata->warp, WARP_WEAK       )) send_to_char("Your muscles are severely
weakened.\n\r",ch);
if (IS_SET(ch->pcdata->warp, WARP_SLOW       )) send_to_char("Your body moves very
slowly.\n\r",ch);
if (IS_SET(ch->pcdata->warp, WARP_VULNER     )) send_to_char("Your skin is very vulnerable
to magic.\n\r",ch);
if (IS_SET(ch->pcdata->warp, WARP_SHARDS     )) send_to_char("Your skin is covered with
shards of ice.\n\r",ch);
if (IS_SET(ch->pcdata->warp, WARP_WINGS      )) send_to_char("A pair of leathery wings
protrude from your back.\n\r",ch);
if (IS_SET(ch->pcdata->warp, WARP_CLUMSY     )) send_to_char("You are incredibly clumsy,
enabling you to be disarmed.\n\r",ch);
if (IS_SET(ch->pcdata->warp, WARP_STUPID     )) send_to_char("Your intelligence is
extremely low, preventing you from casting spells.\n\r",ch);
if (IS_SET(ch->pcdata->warp, WARP_FORK       )) send_to_char("You have a fork stuck in
your nose.\n\r",ch);
if (IS_SET(ch->pcdata->warp, WARP_KNIFE      )) send_to_char("You have a knife hanging out
of your ear.\n\r",ch);
if (IS_SET(ch->pcdata->warp, WARP_SALADBOWL  )) send_to_char("Your head is made out of a
salad bowl.\n\r",ch);
if (ch->pcdata->warp < 1) send_to_char("You haven't obtained any warp powers.\n\r",ch);
return;
}

void do_redeem( CHAR_DATA *ch, char *argument )
{
    int warpnum = number_range(1,19);
    int newwarp = 0;
    if (IS_NPC(ch)) return;

    if (!IS_CLASS(ch, CLASS_SHATAN))
    {
    send_to_char("Huh?\n\r", ch);
    return;
    }

if (ch->pcdata->stats[SHATAN_CURRENT] < 20000 )
{
send_to_char("You need 20000 shatan points to redeem warps!\n\r",ch);
return;
}

{
if (warpnum == 1) newwarp = WARP_CBODY;
else if (warpnum == 2) newwarp = WARP_SBODY;
else if (warpnum == 3) newwarp = WARP_STRONGARMS;
else if (warpnum == 4) newwarp = WARP_STRONGLEGS;
else if (warpnum == 5) newwarp = WARP_VENOMTONG;
else if (warpnum == 6) newwarp = WARP_SPIKETAIL;
else if (warpnum == 7) newwarp = WARP_BADBREATH;
else if (warpnum == 8) newwarp = WARP_QUICKNESS;
else if (warpnum == 9) newwarp = WARP_STAMINA;
else if (warpnum == 11) newwarp = WARP_HUNT;
else if (warpnum == 12) newwarp = WARP_DEVOUR;
else if (warpnum == 13) newwarp = WARP_TERROR;
else if (warpnum == 14) newwarp = WARP_REGENERATE;
else if (warpnum == 15) newwarp = WARP_STEED;
else if (warpnum == 16) newwarp = WARP_WEAPON;
else if (warpnum == 17) newwarp = WARP_SHARDS;
else if (warpnum == 18) newwarp = WARP_WINGS;
else if (warpnum == 19) newwarp = WARP_MAGMA;
  }
if (ch->pcdata->warp == 12877823) newwarp = 0;


if (IS_SET(ch->pcdata->warp, newwarp) && ch->pcdata->warp != 12877823)
{
do_redeem(ch,"");
return;
}

 {
if (IS_SET(ch->pcdata->warp, WARP_INFIRMITY))
	{
           REMOVE_BIT(ch->pcdata->warp, WARP_INFIRMITY);
           SET_BIT(ch->pcdata->warp, newwarp);
	   ch->pcdata->stats[SHATAN_CURRENT] -= 10000;
	   send_to_char("You pray to Satan and a warp is cleansed.\n\r",ch);
    	   save_char_obj(ch);
    	   return;
	}

else if (IS_SET(ch->pcdata->warp, WARP_GBODY))
{
  REMOVE_BIT(ch->pcdata->warp, WARP_GBODY);
  SET_BIT(ch->pcdata->warp, newwarp);
  ch->pcdata->stats[SHATAN_CURRENT] -= 10000;
  send_to_char("You pray to Satan and a warp is cleansed.\n\r",ch);
  save_char_obj(ch);
  return;
}
else if (IS_SET(ch->pcdata->warp, WARP_SCARED))
{
REMOVE_BIT(ch->pcdata->warp, WARP_SCARED);
SET_BIT(ch->pcdata->warp, newwarp);
ch->pcdata->stats[SHATAN_CURRENT] -= 10000;
send_to_char("You pray to Satan and a warp is cleansed.\n\r",ch);
save_char_obj(ch);
return;
}
else if (IS_SET(ch->pcdata->warp, WARP_WEAK))
{
REMOVE_BIT(ch->pcdata->warp, WARP_WEAK);
SET_BIT(ch->pcdata->warp, newwarp);
ch->pcdata->stats[SHATAN_CURRENT] -= 10000;
send_to_char("You pray to Satan and a warp is cleansed.\n\r",ch);
save_char_obj(ch);
return;
}
else if (IS_SET(ch->pcdata->warp, WARP_SLOW))
{
REMOVE_BIT(ch->pcdata->warp, WARP_SLOW);
SET_BIT(ch->pcdata->warp, newwarp);
ch->pcdata->stats[SHATAN_CURRENT] -= 10000;
send_to_char("You pray to Satan and a warp is cleansed.\n\r",ch);
save_char_obj(ch);
return;
}
else if (IS_SET(ch->pcdata->warp, WARP_VULNER))
{
REMOVE_BIT(ch->pcdata->warp, WARP_VULNER);
SET_BIT(ch->pcdata->warp, newwarp);
ch->pcdata->stats[SHATAN_CURRENT] -= 10000;
send_to_char("You pray to Satan and a warp is cleansed.\n\r",ch);
save_char_obj(ch);
return;
}
else if (IS_SET(ch->pcdata->warp, WARP_CLUMSY))
{
REMOVE_BIT(ch->pcdata->warp, WARP_CLUMSY);
SET_BIT(ch->pcdata->warp, newwarp);
ch->pcdata->stats[SHATAN_CURRENT] -= 10000;
send_to_char("You pray to Satan and a warp is cleansed.\n\r",ch);
save_char_obj(ch);
return;
}
else if (IS_SET(ch->pcdata->warp, WARP_STUPID))
{
REMOVE_BIT(ch->pcdata->warp, WARP_STUPID);
SET_BIT(ch->pcdata->warp, newwarp);
ch->pcdata->stats[SHATAN_CURRENT] -= 10000;
send_to_char("You pray to Satan and a warp is cleansed.\n\r",ch);
save_char_obj(ch);
return;
}
else if (IS_SET(ch->pcdata->warp, WARP_SPOON))
{
REMOVE_BIT(ch->pcdata->warp, WARP_SPOON);
SET_BIT(ch->pcdata->warp, newwarp);
ch->pcdata->stats[SHATAN_CURRENT] -= 10000;
send_to_char("You pray to Satan and a warp is cleansed.\n\r",ch);
save_char_obj(ch);
return;
}
else if (IS_SET(ch->pcdata->warp, WARP_FORK))
{
REMOVE_BIT(ch->pcdata->warp, WARP_FORK);
SET_BIT(ch->pcdata->warp, newwarp);
ch->pcdata->stats[SHATAN_CURRENT] -= 10000;
send_to_char("You pray to Satan and a warp is cleansed.\n\r",ch);
save_char_obj(ch);
return;
}
else if (IS_SET(ch->pcdata->warp, WARP_KNIFE))
{
REMOVE_BIT(ch->pcdata->warp, WARP_KNIFE);
SET_BIT(ch->pcdata->warp, newwarp);
ch->pcdata->stats[SHATAN_CURRENT] -= 10000;
send_to_char("You pray to Satan and a warp is cleansed.\n\r",ch);
save_char_obj(ch);
return;
}

    else send_to_char("You have no evil warps to redeem!\n\r",ch);
    }   


return;
}

void do_obtain( CHAR_DATA *ch, char *argument )
{
    int       newwarp = 0;
    int       warpnum = number_range(1,30);

    if (IS_NPC(ch)) return;

        if ( !IS_CLASS(ch, CLASS_SHATAN))
        {
        send_to_char("Huh?\n\r", ch);
        return;
        }

    if (ch->pcdata->stats[SHATAN_CURRENT] < 15000)
    {
        send_to_char("You need 15000 shatan points to obtain a new warp!\n\r",ch);
        return;
    }

        if (ch->pcdata->warpcount >= 5)
        {
            send_to_char("You have already obtained as many warps as
possible.\n\r",ch);
            return;
        }

             if (warpnum == 1) newwarp = WARP_CBODY;
        else if (warpnum == 2) newwarp = WARP_SBODY;
        else if (warpnum == 3) newwarp = WARP_STRONGARMS;
        else if (warpnum == 4) newwarp = WARP_STRONGLEGS;
        else if (warpnum == 5) newwarp = WARP_VENOMTONG;
        else if (warpnum == 6) newwarp = WARP_SPIKETAIL;
        else if (warpnum == 7) newwarp = WARP_BADBREATH;
        else if (warpnum == 8) newwarp = WARP_QUICKNESS;
        else if (warpnum == 9) newwarp = WARP_STAMINA;
        else if (warpnum == 11) newwarp = WARP_HUNT;
        else if (warpnum == 12) newwarp = WARP_DEVOUR;
        else if (warpnum == 13) newwarp = WARP_TERROR;
        else if (warpnum == 14) newwarp = WARP_REGENERATE;
        else if (warpnum == 15) newwarp = WARP_STEED;
        else if (warpnum == 16) newwarp = WARP_WEAPON;
        else if (warpnum == 17) newwarp = WARP_INFIRMITY;
        else if (warpnum == 18) newwarp = WARP_GBODY;
        else if (warpnum == 19) newwarp = WARP_SCARED;
        else if (warpnum == 20) newwarp = WARP_MAGMA;
        else if (warpnum == 21) newwarp = WARP_WEAK;
        else if (warpnum == 22) newwarp = WARP_SLOW;
        else if (warpnum == 23) newwarp = WARP_VULNER;
        else if (warpnum == 24) newwarp = WARP_SHARDS;
        else if (warpnum == 25) newwarp = WARP_WINGS;
        else if (warpnum == 26) newwarp = WARP_CLUMSY;
        else if (warpnum == 27) newwarp = WARP_STUPID;
        else if (warpnum == 28) newwarp = WARP_SPOON;
        else if (warpnum == 29) newwarp = WARP_FORK;
        else if (warpnum == 30) newwarp = WARP_KNIFE;

    if (IS_SET(ch->pcdata->warp, newwarp))
    {
      do_obtain(ch,"");
        return;
    }

    SET_BIT(ch->pcdata->warp, newwarp);
    ch->pcdata->stats[SHATAN_CURRENT] -= 15000;
    ch->pcdata->warpcount += 1;
    send_to_char("You have obtained a new warp!\n\r",ch);
    save_char_obj(ch);
    return;
}



void do_legions( CHAR_DATA *ch, char *argument )
{
    char buf[MAX_STRING_LENGTH];
    char arg[MAX_INPUT_LENGTH];
    char lord[MAX_INPUT_LENGTH];
    CHAR_DATA *gch;

    one_argument( argument, arg );

    if (IS_NPC(ch)) return;
    if (!IS_CLASS(ch, CLASS_SHATAN))
    {
    send_to_char("Huh?\n\r",ch);
    return;
    }

    if (IS_CLASS(ch, CLASS_SHATAN)) strcpy(lord,ch->name);
        else strcpy(lord,ch->lord);
    sprintf( buf, "The followers of %s:\n\r", lord );
    send_to_char( buf, ch );
send_to_char("#G[    #gName    #G] [ #gHits #G] [ #gMana #G] [ #gMove #G][#gPower#G]\n\r",ch);
for ( gch = char_list; gch != NULL; gch = gch->next )
{
if ( IS_NPC(gch) ) continue;
if ( !IS_CLASS(gch, CLASS_SHATAN))
    continue;

if ( !str_cmp(ch->clan,gch->clan) )
  {
    sprintf( buf,
    "#8[#1%-12s#8] [#1%-6d#8] [#1%-6d#8] [#1%-6d#8] [#1%7d#8]\n\r",
       capitalize( gch->name ),
       gch->hit,gch->mana,gch->move,
       gch->pcdata->stats[SHATAN_CURRENT]);
       send_to_char( buf, ch );
   }
}
   return;
}

void do_leech(CHAR_DATA *ch, char *argument)
{
    CHAR_DATA *victim = NULL;
    char buf[MAX_STRING_LENGTH];

     if (!IS_CLASS(ch,CLASS_SHATAN))
     {
	send_to_char("Huh?\n\r",ch);
        return;
    }
    
     if (argument[0] == '\0')
    {
	send_to_char("Who's life do you wish to leech off of?\n\r", ch);
	return;
    }

    if ((victim = get_char_room(ch, argument)) == NULL)
    {
	    send_to_char("They aren't here.\n\r", ch);
	    return;
    }

      if (is_safe(ch, victim)) return;

	WAIT_STATE(ch, 10);

	act("$n stares intently at $N.", ch, NULL, victim, TO_NOTVICT);
	act("You stare intently at $N.", ch, NULL, victim, TO_CHAR);
	act("$n stares intently at you.", ch, NULL, victim, TO_VICT);

      if (victim->hit >= 300)
      {
	  sh_int power;
	  sh_int dam;
	  power = 100;
	  dam = dice(power, power + 2);
	  if (dam > 300) dam = 300 + (dam / 10);
	  if (dam < 0) dam = 0;
          if (dam > ch->max_hit) dam = (ch->max_hit / 2);
	  if (dam > 1500) dam = 1500;
	  victim->hit -= dam;
	  ch->hit += dam;
	  if (ch->hit >= ch->max_hit + 250)
		ch->hit = ch->max_hit + 250;
	  sprintf(buf,"#1You absorb %d hitpoints.#n\n\r",dam);
	  send_to_char(buf,ch);
	  sprintf(buf,"#1%s absorbed %d of your hitpoints!#n\n\r",ch->name,dam);
	  send_to_char(buf,victim);
	  }
      else send_to_char("Nothing seemed to happen.\n\r",ch);
	return;

}

