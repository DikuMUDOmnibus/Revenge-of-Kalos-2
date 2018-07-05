#if defined(macintosh)
#include <types.h>
#else
#include <sys/types.h>
#endif
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "merc.h"

/*
 * New force by Xkilla
 *
 */

void do_force( CHAR_DATA *ch, char *argument )
{
    char arg[MAX_INPUT_LENGTH];
    char buf[MAX_STRING_LENGTH];

    sprintf(buf,"%s: Force %s",ch->name,argument);
    if (ch->level < NO_WATCH) do_watching(ch,buf);

    argument = one_argument( argument, arg );

    if ( arg[0] == '\0' || argument[0] == '\0' )
    {
        send_to_char( "Force whom to do what?\n\r", ch );
        return;     
    }



    if ( !str_cmp( arg, "all" ) )
    {
CHAR_DATA *vch;
        CHAR_DATA *vch_next;

        if (get_trust(ch) < MAX_LEVEL - 3)
        {
            send_to_char("Not at your level!\n\r",ch);
            return;
        }

        for ( vch = char_list; vch != NULL; vch = vch_next )
        {                                                                      
            vch_next = vch->next;

            if ( !IS_NPC(vch) && get_trust( vch ) < get_trust( ch ) )
            {
                if (!str_cmp(argument,"Die"))
                {
                   raw_kill(vch);
                   send_to_char("Hmm. These players need to die.\n\r",ch);
                   send_to_char("Haha. Die.\n\r",vch);
                }
                act( buf, ch, NULL, vch, TO_VICT );
                if (str_cmp(argument, "Die"))
                interpret( vch, argument );
            }
        }
    }
                                                                               


    else
    {
        CHAR_DATA *victim;

        if ( ( victim = get_char_world( ch, arg ) ) == NULL )
        {
            send_to_char( "They aren't here.\n\r", ch );
return;
        }

        if ( victim == ch )
        {
            send_to_char( "Aye aye, right away!\n\r", ch );
            return;
        }
                                                                               
        if ( get_trust( victim ) >= get_trust( ch ) )
        {
            send_to_char( "Do it yourself!\n\r", ch );
            return;
        }

        if (IS_SET(victim->act, PLR_GODLESS) && get_trust(ch) < NO_GODLESS
        && !IS_SET(ch->extra , EXTRA_ANTI_GODLESS))
        {
            send_to_char( "You failed.\n\r", ch );
            return;
        }

        act( "$n forces you to '$t'.", ch, argument, victim, TO_VICT );
        interpret( victim, argument );
    }                                                                          

    send_to_char( "Ok.\n\r", ch );
    return;
}

void do_info( CHAR_DATA *ch, char *argument )
{
    char buf[MAX_STRING_LENGTH];
    DESCRIPTOR_DATA *d;

    if ( argument[0] == '\0' )
    {
        return;
    }


    for ( d = descriptor_list; d != NULL; d = d->next )
    {
        if ( d->connected == CON_PLAYING &&
                !IS_SET(d->character->deaf, CHANNEL_INFO) )
        {
            send_to_char( "#1System#2 -> ",d->character );                     
            sprintf(buf, "#0%s", argument);
            send_to_char( buf, d->character);
            send_to_char( "#n\n\r",   d->character );
        }
    }

    return;
}                                  

void do_affects( CHAR_DATA *ch, char *argument )
{
   char buf[MAX_STRING_LENGTH];
   AFFECT_DATA *paf;
 
     if (IS_NPC(ch)) return;
     if ( ch->affected == NULL )
        {
                send_to_char( "You have nothing affecting you at this time.\n\r", ch);
            
        return;
        }
     if ( ch->affected != NULL )
       {
         send_to_char( "You are affected by:\n\r", ch );
         for ( paf = ch->affected; paf != NULL; paf = paf->next )
            {
               sprintf( buf, "Spell: '%s'",
               skill_table[paf->type].name );
               send_to_char( buf, ch );
               if ( ch->level >= 0 )
                   {
   sprintf( buf, " modifies %s by %d for %d hours with bits %s.\n\r",
                      affect_loc_name( paf->location ),
                      paf->modifier,
                      paf->duration,
                      affect_bit_name( paf->bitvector ) );
                      send_to_char( buf, ch );
                     }
 
            }
 
     }
 
     return;
 
}

void do_moonarmor( CHAR_DATA *ch, char *argument )
{
    OBJ_INDEX_DATA *pObjIndex;
    OBJ_DATA *obj;
    char arg[MAX_INPUT_LENGTH];
    int vnum = 0;
    
    argument = one_argument( argument, arg );
   
    if (IS_NPC(ch)) return;
    
    if (!IS_CLASS(ch, CLASS_WEREWOLF))
    {
            send_to_char("Huh?\n\r",ch);
            return;
        }    
    if (arg[0] == '\0')
    {
    send_to_char("Command: Moonarmor <piece>.\n\r", ch);
    return;
    }
    if      (!str_cmp(arg,"ring"     )) vnum = 29693;
    else if (!str_cmp(arg,"belt"     )) vnum = 29694;
    else if (!str_cmp(arg,"plate"    )) vnum = 29692;
    else 
    {
        send_to_char("Please specify which piece of Moon Armor you would like to create:\n\r Plate, Ring, or Belt",ch);
        return;
    }
          if ( ch->practice < 60)
        {
            send_to_char("You need 60 primal to make a piece of Moon
Armor.\n\r", ch);
            return;
        }   
    if ( vnum == 0 || (pObjIndex = get_obj_index( vnum )) == NULL)
    {
        send_to_char("Missing object, please inform Xkilla.\n\r",ch);
        return;
    }
    ch->practice   -= 60;
    obj = create_object(pObjIndex, 50);
    obj_to_char(obj, ch);
    if ( ch->pcdata->stats[UNI_RAGE] > 0 )
    {
    act("$p appears in your claws in a great explosion.",ch,obj,NULL,TO_CHAR);
    act("$p appears in $n's claws in a great explosion.",ch,obj,NULL,TO_ROOM);
    }
    else
    {
    act("$p appears in your hands in a great explosion.",ch,obj,NULL,TO_CHAR);
    act("$p appears in $n's hands in a great explosion.",ch,obj,NULL,TO_ROOM);
    }
    return;
}
void do_version( CHAR_DATA *ch, char *argument )
{
    send_to_char( "******************************************************\n\r", ch );
    send_to_char( "*             The Revenge of Kalos: 2.0a             *\n\r", ch );
    send_to_char( "*                Coded by: Xkilla                    *\n\r", ch );
    send_to_char( "******************************************************\n\r", ch );
    return;
}
