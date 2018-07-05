/* Angel newbreed class by The One and Only Zaphonite */
/* And xkilla*/
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
#include "angel.h"
#include "player.h"

/*
 * Local Functions
 */

 void do_angelgift( CHAR_DATA *ch, char *argument)
 {
     CHAR_DATA *victim;
     char     arg1 [MAX_INPUT_LENGTH];
     char     arg2 [MAX_INPUT_LENGTH];
     int      gift = 0;
     int      cost = 0;

     smash_tilde(argument);
     argument = one_argument( argument, arg1 );
     argument = one_argument( argument, arg2 );

     if (IS_NPC(ch)) return;

     if (!IS_CLASS(ch, CLASS_ANGEL))
     {
       send_to_char("Huh?\n\r",ch);
       return;
     }

     if ( arg1[0] == '\0' || arg2[0] == '\0' )
     {
       send_to_char("Syntax: angelgift (person) (gift)\n\r",ch);
       send_to_char("Wings  [2000]     Toughness [9000]     GodStrength [9000]  \n\r",ch);
       send_to_char("Scry   [7500]     ReadAura  [7500]     GodlySight  [7500]  \n\r",ch);
       send_to_char("Speed  [9000]     Halo      [15000]    MultiArm    [50000] \n\r",ch);
       send_to_char("Prince [   0]     Trueform  [50000]    Etherform   [25000] \n\r",ch);
       send_to_char("Shield [15000]                                             \n\r",ch);
       send_to_char("Godly Gifts:                                               \n\r",ch);
       send_to_char("Wraith of God [75000]                                      \n\r",ch);
       return;
     }

     if ( ( victim = get_char_room( ch, arg1) ) == NULL )
     {
       send_to_char( "They aren't here.\n\r",ch);
       return;
     }

     if ( IS_NPC(victim) )
     {
       send_to_char("Not on NPC's.\n\r",ch);
       return;
     }
    if (!str_cmp(arg2,"prince"))
    {
        if (victim == ch)
        {
            send_to_char("Not on yourself!\n\r",ch);
            return;
        }
        if (ch->pcdata->stats[UNI_GEN] > 2)
        {
            send_to_char("Only an Archangel has the power to make princes.\n\r",ch);
            return;
        }
        if (IS_SET(victim->special,SPC_PRINCE))
        {
            send_to_char("You have lost your princehood!\n\r",victim);
            send_to_char("You remove their princehood.\n\r",ch);
            REMOVE_BIT(victim->special, SPC_PRINCE);
        }
        else
        {
            send_to_char("You have been made a prince!\n\r",victim);
            send_to_char("You make them a prince.\n\r",ch);
            SET_BIT(victim->special, SPC_PRINCE);
        }
        save_char_obj(victim);
        return;
    }

     if (!str_cmp(arg2,"wings"))
     {gift = ANG_WINGS; cost = 2000;}
     else if (!str_cmp(arg2,"toughness"))
     {gift = ANG_TOUGHNESS; cost = 9000;}
     else if (!str_cmp(arg2,"godstrength"))
     {gift = ANG_STRENGTH; cost = 9000;}
     else if (!str_cmp(arg2,"godlysight"))
     {gift = ANG_GODLYSIGHT; cost = 7500;}
     else if (!str_cmp(arg2,"scry"))
     {gift = ANG_SCRY; cost = 7500;}
     else if (!str_cmp(arg2,"readaura"))
     {gift = ANG_READAURA; cost = 7500;}
     else if (!str_cmp(arg2,"speed"))
     {gift = ANG_SPEED; cost = 9000;}
     else if (!str_cmp(arg2,"halo"))
     {gift = ANG_HALO; cost = 15000;}
     else if (!str_cmp(arg2,"multiarm"))
     {gift = ANG_MULTIARM; cost = 50000;}
     else if (!str_cmp(arg2,"wraith of god"))
     {gift = ANG_WRAITH_OF_GOD; cost = 75000;}
     else if (!str_cmp(arg2,"trueform"))
     {gift = ANG_TRUEFORM; cost = 50000;}
     else if (!str_cmp(arg2,"shield"))
     {gift = ANG_SHIELD_OF_GOD; cost = 15000;}
     else if (!str_cmp(arg2,"etherform"))
     {gift = ANG_ETHERFORM; cost = 25000;}
     else
     {
       send_to_char("Syntax: angelgift (person) (gift)\n\r",ch);
       send_to_char("Wings  [2000]     Toughness [9000]     GodStrength [9000]  \n\r",ch);
       send_to_char("Scry   [7500]     ReadAura  [7500]     GodlySight  [7500]  \n\r",ch);
       send_to_char("Speed  [9000]     Halo      [15000]    MultiArm    [50000] \n\r",ch);
       send_to_char("Prince [   0]     Trueform  [50000]    Etherform   [25000] \n\r",ch);
       send_to_char("Shield [15000]                                             \n\r",ch);
       send_to_char("Godly Gifts:                                               \n\r",ch);
       send_to_char("Wraith of God [75000]                                      \n\r",ch);
       return;
     }
     if (IS_ANGPOWER(victim, gift))
     {
       send_to_char("God has already given them that gift.\n\r",ch);
       return;
     }

     if (ch->pcdata->stats[ANGEL_TOTAL] < cost ||
         ch->pcdata->stats[ANGEL_CURRENT] < cost)
     {
       send_to_char("You don't have enough angel points to gift that.\n\r",ch);
       return;
     }
     SET_BIT(victim->pcdata->powers[APOWER_FLAGS], gift);
     ch->pcdata->stats[ANGEL_TOTAL]     -= cost;
     ch->pcdata->stats[ANGEL_CURRENT]   -= cost;
     if (victim != ch) send_to_char("You have been granted a gift from god.\n\r",ch);
     send_to_char("Ok.\n\r",ch);
     save_char_obj(victim);
     return;
 }

 void do_angelwings( CHAR_DATA *ch, char *argument )
 {
     char arg [MAX_INPUT_LENGTH];

     argument = one_argument( argument, arg );

     if (IS_NPC(ch)) return;

     if (!IS_CLASS(ch, CLASS_ANGEL))
     {
       send_to_char("Huh?\n\r",ch);
       return;
     }

     if (!IS_ANGPOWER( ch, ANG_WINGS))
     {
       send_to_char("God hasn't given you your wings.\n\r",ch);
       return;
     }

     if (arg[0] != '\0')
 {
     {
       send_to_char("You need your wings out first.\n\r",ch);
       return;
     }
       if (!str_cmp(arg,"spread") || !str_cmp(arg,"s"))
       {
         if (IS_ANGAFF(ch,ANG_SPREAD) )
         {
           send_to_char("Your wings are already spread.\n\r",ch);
           return;
         }
         send_to_char("You spread your wings and start flying.\n\r",ch);
         act("$n spreads %s wings and starts to fly.\n\r",ch,NULL,NULL,TO_ROOM);
         SET_BIT(ch->pcdata->powers[APOWER_CURRENT], ANG_SPREAD);
         return;
       }
       else if (!str_cmp(arg,"unspread") || !str_cmp(arg,"u"))
       {
         if (!IS_ANGAFF(ch,ANG_SPREAD) )
         {
           send_to_char("Your wings aren't spread.\n\r",ch);
           return;
         }
         send_to_char("Your wings close up behind your back.\n\r",ch);
         act("$n's wings close up behind %s back.",ch, NULL,NULL, TO_ROOM);
         REMOVE_BIT(ch->pcdata->powers[APOWER_CURRENT], ANG_SPREAD);
         return;
       }
       else
       {
         send_to_char("Do you want to SPREAD or CLOSE your wings?\n\r",ch);
         return;
       }
    }
   
      if (IS_ANGAFF(ch,ANG_WINGS) )
        {
         if (IS_ANGAFF(ch,ANG_SPREAD) )
         {
           send_to_char("Your wings close up behind your back.\n\r",ch);
           act("$n's wings close up behind %s back.\n\r",ch,NULL,NULL,TO_ROOM);
           REMOVE_BIT(ch->pcdata->powers[APOWER_CURRENT], ANG_SPREAD);
         }
         send_to_char("Your wings dissapear behind your back.\n\r",ch);
         act("$n's wings disappear behind %s back.",ch,NULL,NULL, TO_ROOM);
         REMOVE_BIT(ch->pcdata->powers[APOWER_CURRENT], ANG_WINGS);
         return;
       }
       send_to_char("Wings grow from your back.\n\r",ch);
       act("Wings grow from behind $n's back.",ch,NULL,NULL,TO_ROOM);
       SET_BIT(ch->pcdata->powers[APOWER_CURRENT], ANG_WINGS);
       return;
     }


void do_godlysight( CHAR_DATA *ch, char *argument )
{
  if ( IS_NPC(ch) )
  return;

  if (!IS_CLASS(ch, CLASS_ANGEL) )
  {
    send_to_char("Huh?\n\r",ch);
    return;
  }

  if (!IS_ANGPOWER(ch, ANG_GODLYSIGHT) )
  {
    send_to_char("God has not gifted you his sight.\n\r",ch);
    return;
  }

  if (IS_SET(ch->act, PLR_HOLYLIGHT) )
  {
    REMOVE_BIT(ch->act, PLR_HOLYLIGHT);
    send_to_char("God stops assisting you with sight.\n\r",ch);
  }
  else
  {
    send_to_char("God answers your wishes and gives you his sight.\n\r",ch);
    SET_BIT(ch->act, PLR_HOLYLIGHT);
  }
  return;
}

void do_etherform( CHAR_DATA *ch, char *argument )
{
  if (IS_NPC(ch))
  return;

  if (!IS_CLASS(ch, CLASS_ANGEL))
  {
    send_to_char("Huh?\n\r",ch);
    return;
  }

  if (!IS_ANGPOWER(ch, ANG_ETHERFORM) )
  {
    send_to_char("God has not given you the power to turn ethereal.\n\r",ch);
    return;
  }

  if (IS_AFFECTED(ch, AFF_ETHEREAL) )
  {
    REMOVE_BIT(ch->affected_by, AFF_ETHEREAL);
    send_to_char("You shift back into the normal plane of existance.\n\r",ch);
  }
  else
  {
    send_to_char("You shift into the plane of angelic existance.\n\r",ch);
    SET_BIT(ch->affected_by, AFF_ETHEREAL);
  }
  return;
}

void do_wraithofgod( CHAR_DATA *ch, char *argument)
{
  char arg[MAX_INPUT_LENGTH];
  CHAR_DATA *victim;
  int dam;

  one_argument( argument, arg );

  if (IS_NPC(ch))
  return;

  if (!IS_CLASS(ch, CLASS_ANGEL))
  {
    send_to_char("Huh?\n\r",ch);
    return;
  }

  if ( arg[0] == '\0' )
  {
    send_to_char("Bestow the Wraith of god against whom?\n\r",ch);
    return;
  }

  if ( ( victim = get_char_room( ch, arg ) ) == NULL )
  {
    send_to_char("You can't seem to find them here.\n\r",ch);
    return;
  }

  if ( victim == ch )
  {
    send_to_char("God does not approve of suicide.\n\r",ch);
    return;
  }

  if ( !IS_ANGPOWER(ch, ANG_WRAITH_OF_GOD))
  {
    send_to_char("You don't have the Wraith of God to assist you.\n\r",ch);
    return;
  }
  
  if ( is_safe( ch, victim ))
  return;

  if ( IS_CLASS(victim, CLASS_ANGEL))
  {
    send_to_char("You cannot summon the Wraith of God on another angel!\n\r",ch);
    return;
  }

  if ( IS_GOOD(victim))
 {
      dam = number_range(2500, 7500);
     if ( dam <= 7500 )
    {
     act("The Wraith of God strikes $N!!!!", ch, NULL, victim, TO_CHAR);
      act("The Wraith of God strikes you!!!", ch, NULL, victim, TO_VICT);
      act("The Wraith of God strikes $N!!!!", ch, NULL, victim, TO_NOTVICT);
 SET_BIT(victim->affected_by, AFF_CURSE);
      SET_BIT(victim->affected_by, AFF_FAERIE_FIRE);
      }
 }
  if ( IS_EVIL(victim))
  {
      dam = number_range(7501,15000);

      if ( dam <= 7500 )
      {
      act("The Wraith of God strikes $N!!!!", ch, NULL, victim, TO_CHAR);
      act("The Wraith of God strikes you!!!", ch, NULL, victim, TO_VICT);
      act("The Wraith of God strikes $N!!!!", ch, NULL, victim, TO_NOTVICT);
      SET_BIT(victim->affected_by, AFF_CURSE);
      SET_BIT(victim->affected_by, AFF_FAERIE_FIRE);
      }
  }
  else
  {
      dam = number_range(7501, 12000);

      if ( dam >= 7501);
      {
      act("The Wraith of God strikes $N!!!!", ch, NULL, victim, TO_CHAR);
      act("The Wraith of God strikes you!!!", ch, NULL, victim, TO_VICT);
      act("The Wraith of God strikes $N!!!!", ch, NULL, victim, TO_NOTVICT);
      SET_BIT(victim->affected_by, AFF_CURSE);
      SET_BIT(victim->affected_by, AFF_FAERIE_FIRE);
      }
  }
  REMOVE_BIT(ch->pcdata->powers[APOWER_FLAGS], ANG_WRAITH_OF_GOD);

  victim->hit -= dam;
  update_pos(victim);
  return;
}
/*
void do_protect( CHAR_DATA *ch, char *argument )
{
  if (IS_NPC(ch))
  return;

  if (!IS_CLASS(ch, CLASS_ANGEL))
  {
    send_to_char("Huh?\n\r",ch);
    return;
  }

  if (!IS_ANGPOWER(ch, ANG_PROTECTION_OF_GOD))
  {
    send_to_char("God has not given you the gift of his protection.\n\r",ch);
    return;
  }

  if ( IS_AFFECTED(ch, AFF_ANGELPROTECT))
  {
    REMOVE_BIT(ch->affected_by, AFF_ANGELPROTECT);
    send_to_char("God stops protecting you from attacks.\n\r",ch);
  }
  else
  {
    send_to_char("God starts protecting you from attacks.\n\r",ch);
    SET_BIT(ch->affected_by, AFF_ANGELPROTECT);
  }
  return;
}
*/

void do_trueform( CHAR_DATA *ch, char *argument )
{
    char buf [MAX_STRING_LENGTH];
        
    if (IS_NPC(ch)) return;
        
    if (!IS_CLASS(ch, CLASS_ANGEL))
    {
        send_to_char("Huh?\n\r",ch);
        return;
    }
     
    if (!IS_ANGPOWER( ch, ANG_TRUEFORM) && IS_CLASS(ch,CLASS_ANGEL))
    {
        send_to_char("You are not gifted in trueform.\n\r",ch);
        return;
    }   
        if (ch->mounted == IS_RIDING) do_dismount(ch,"");
      
        if ( IS_SET(ch->polyaff, POLY_ANGELFORM) )
    {
        act( "You change back into human form.", ch, NULL, NULL, TO_CHAR );
        act( "$n changes back into human form.", ch, NULL, NULL, TO_ROOM );
        REMOVE_BIT(ch->affected_by, AFF_POLYMORPH);
        REMOVE_BIT(ch->polyaff, POLY_ANGELFORM);
        REMOVE_BIT(ch->pcdata->stats[UNI_AFF], VAM_CHANGED);
        clear_stats(ch);
        free_string( ch->morph );
        ch->morph = str_dup( "" );  
       return; 
 }   
  else if ( !IS_SET(ch->polyaff, POLY_ANGELFORM) )
    {
        act( "You are struck by holy light and turn into a true angel.", ch, NULL, NULL, TO_CHAR );
        act( "$n is struck by holy light and turns into a true angel.", ch, NULL, NULL, TO_ROOM );
        SET_BIT(ch->polyaff, POLY_ANGELFORM);
        SET_BIT(ch->affected_by, AFF_POLYMORPH);
        SET_BIT(ch->pcdata->stats[UNI_AFF], VAM_CHANGED);
        sprintf(buf, "%s the radiant angel", ch->name);
        free_string( ch->morph );
        ch->morph = str_dup( buf );
      ch->damroll = ch->damroll + 200;
      ch->hitroll = ch->hitroll + 200;
        return;
    }
    else
        send_to_char( "ANGELFORM: The Power to show your true self.\n\r", ch );
    return;
}

void do_angellist( CHAR_DATA *ch, char *argument )
{
    char buf[MAX_STRING_LENGTH];
    char arg[MAX_INPUT_LENGTH];
    char lord[MAX_INPUT_LENGTH];
    CHAR_DATA *gch;

    one_argument( argument, arg );

    if (IS_NPC(ch)) return;
    if (!IS_CLASS(ch, CLASS_ANGEL) )
    {
        send_to_char("Huh?\n\r",ch);
        return;
    }

    if (IS_CLASS(ch, CLASS_ANGEL)) strcpy(lord,ch->name);
        else strcpy(lord,ch->lord);
    sprintf( buf, "The Angels of %s:\n\r", lord );
    send_to_char( buf, ch );
    send_to_char("[      Name      ] [ Hits ] [ Mana ] [ Move ] [  Exp  ] [   Angel   Points   ]\n\r", ch );
    for ( gch = char_list; gch != NULL; gch = gch->next )
    {
        if ( IS_NPC(gch) ) continue;
        if ( !IS_CLASS(gch, CLASS_ANGEL)) 
            continue;
        if ( !str_cmp(ch->clan,gch->clan) )
        {
            sprintf( buf,
            "[%-16s] [%-6d] [%-6d] [%-6d] [%7d] [ %-9d%9d ]\n\r",
                capitalize( gch->name ),
                gch->hit,gch->mana,gch->move,
                gch->exp, gch->pcdata->stats[ANGEL_CURRENT], gch->pcdata->stats[ANGEL_TOTAL]);
                send_to_char( buf, ch );
        }
    }
    return;
}

void do_multiarm( CHAR_DATA *ch, char *argument )
{
    CHAR_DATA *victim;
    int dam = number_range(100,200) + char_damroll(ch);
  
    if (dam < 10) dam = 10;
        
if ( IS_NPC(ch) ) return;
        
  if (!IS_ANGPOWER( ch, ANG_MULTIARM) && IS_CLASS(ch,CLASS_ANGEL))    {
send_to_char("God hasn't given you the gift of multiarm.\n\r",ch);
return;
    }
    if ( !IS_CLASS(ch, CLASS_ANGEL) )   
    {
    send_to_char("Huh?\n\r", ch);
        return;
        }
        
    if ( ( victim = ch->fighting ) == NULL )
    {
        send_to_char( "You aren't fighting anyone.\n\r", ch );
        return;
    }
        
        if (is_safe(ch, victim)) return;
        
            special_move(ch,victim);
            special_move(ch,victim);
            special_move(ch,victim);
            special_move(ch,victim);
    }

void do_purify( CHAR_DATA *ch, char *argument )
{
    CHAR_DATA *victim;
    char      arg [MAX_INPUT_LENGTH];

    argument = one_argument( argument, arg );

    if (IS_NPC(ch)) return;

    if (!IS_CLASS(ch, CLASS_ANGEL))
    {
        send_to_char("Huh?\n\r",ch);
        return;
    }

    if (ch->pcdata->stats[UNI_GEN] > 2 && !IS_SET(ch->special, SPC_PRINCE))
    {
        send_to_char("You are not able to purify.\n\r",ch);
        return;
    }

    if ( arg[0] == '\0' )
    {
        send_to_char( "Purify whom?\n\r", ch );
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
        send_to_char( "You cannot purify with yourself.\n\r", ch );
        return;
    }

    if ( victim->class != 0)
    {
	send_to_char("They are already classed.\n\r",ch);
	return;
    }
    if ( victim->level != LEVEL_AVATAR && !IS_IMMORTAL(victim) )
    {
        send_to_char( "You can only purify avatars.\n\r", ch );
        return;
    }

        if (!IS_GOOD(victim)) {
        send_to_char("They must be good!\n\r", ch );
                return;}

    act("You make $N an angel!", ch, NULL, victim, TO_CHAR);
    act("$n makes $N an angel!", ch, NULL, victim, TO_NOTVICT);
    act("$n makes you an angel!", ch, NULL, victim, TO_VICT);
    victim->class=0;
    victim->class=CLASS_ANGEL;

    if (IS_CLASS(victim, CLASS_VAMPIRE)) do_mortalvamp(victim,"");
    REMOVE_BIT(victim->act, PLR_HOLYLIGHT);
    REMOVE_BIT(victim->act, PLR_WIZINVIS);
    REMOVE_BIT(victim->special, SPC_SIRE);
    REMOVE_BIT(victim->special, SPC_ANARCH);
    victim->pcdata->stats[UNI_RAGE] = 0;
    free_string(victim->lord);
    victim->clan=str_dup(ch->clan); 
    if (IS_CLASS(ch,CLASS_ANGEL)) victim->lord=str_dup(ch->name);
    else victim->lord=str_dup(ch->lord);

    save_char_obj(ch);
    save_char_obj(victim);
    return;
}

