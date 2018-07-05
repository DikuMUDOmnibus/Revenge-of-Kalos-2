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


void do_updatetick( CHAR_DATA *ch, char *argument )
{
char buf[MAX_STRING_LENGTH];

arena = FIGHT_OPEN;
area_update     ( );
weather_update  ( );
char_update     ( );
mobile_update   ( );
obj_update      ( );
quest_update    ( );
tag_update      ( );
/*too spammy considering mobs don't repop every time
sprintf(buf,"Tickers have been reseted by %s",ch->name);
do_info(ch,buf);
*/
return;
}

//By Russ Taylor of ROM
void do_delete( CHAR_DATA *ch, char *argument)
{
   char strsave[MAX_INPUT_LENGTH];


   if (IS_NPC(ch))
        return;

   if (ch->pcdata->confirm_delete)
   {
        if (argument[0] != '\0')
        {
            send_to_char("Delete status removed.\n\r",ch);
            ch->pcdata->confirm_delete = FALSE;
            return;
        }
        else
        {
            sprintf( strsave, "%s%s", PLAYER_DIR, capitalize( ch->name ) );
           // wiznet("$N turns $Mself into line noise.",ch,NULL,0,0,0);
            stop_fighting(ch,TRUE);
            do_quit(ch,"");
          unlink(strsave);
            return;
        }
    }
     
 /*    
    if (argument[0] != '\0')
    {
        send_to_char("Just type delete. No argument.\n\r",ch);
        return;
    }
  */
    if (strcmp( crypt(argument, ch->pcdata->pwd), ch->pcdata->pwd) )
    {
	send_to_char("Syntax: delete <password>\r\n", ch);
	send_to_char("This will delete your character!\r\n", ch);
	return;
    }

send_to_char("Type delete again to confirm this command.\n\r",ch);
    send_to_char("WARNING: this command is irreversible.\n\r",ch);
    send_to_char("Typing delete with an argument will undo delete status.\n\r",
        ch);
    ch->pcdata->confirm_delete = TRUE;
    //wiznet("$N is contemplating deletion.",ch,NULL,0,0,get_trust(ch));
}


void do_bonus( CHAR_DATA *ch, char *argument)
{
         CHAR_DATA *victim;
         char       buf  [ MAX_STRING_LENGTH ];
         char       arg1 [ MAX_INPUT_LENGTH ];
         char       arg2 [ MAX_INPUT_LENGTH ];
         int      value;

         argument = one_argument( argument, arg1 );
         argument = one_argument( argument, arg2 );

         if ( arg1[0] == '\0' || arg2[0] == '\0' || !is_number( arg2 ) )
         {
        send_to_char( "syntax: bonus <char> <Exp>.\n\r", ch );
        return;

         }
         if (( victim = get_char_world ( ch, arg1 ) ) == NULL )
         {
                send_to_char("That Player is not here.\n\r", ch);
                return;
         }

         if ( IS_NPC( victim ) )
         {
        send_to_char( "Not on NPC's.\n\r", ch );
        return;
         }

         if ( ch == victim )
         {
        send_to_char( "You may not bonus yourself.\n\r", ch );
        return;
         }

         if (IS_IMMORTAL(victim) || victim->level >= LEVEL_IMMORTAL)
         {
         send_to_char("You can't bonus immortals fool.\n\r", ch);
         return;
         }

         value = atoi( arg2 );
         if ( value < -250000 || value > 250000 )
         {
        send_to_char( "Value range is -250000 to 250000.\n\r", ch );
        return;
         }

         if ( value == 0 )
         {
        send_to_char( "{wThere is no point in giving 0 experience.{x\n\r", ch );
        return;
}
         sprintf( buf,"{wYou have bonused %s a whopping %d experience
points.{x\n\r",
                        victim->exp += value);
                        send_to_char(buf, ch);

         if ( value > 0 )
         {
                sprintf( buf,"{wYou have been bonused %d experience
points.{x\n\r", value );
                send_to_char( buf, victim );
         }

         else
         {
                sprintf( buf,"{wYou have been penalized %d experience
points.{x\n\r", value );
                send_to_char( buf, victim );
         }

         return;
}

void do_timers( CHAR_DATA *ch, char *argument )
{
 char buf[MAX_STRING_LENGTH];
if (ch->fight_timer > 0)
{
 sprintf(buf,"Your fightimer is as: (%d).\n\r",ch->fight_timer);
 send_to_char(buf,ch);
return;
}
send_to_char("You are not affected by any timers.",ch);

return;
}

void do_findexp( CHAR_DATA *ch, char *argument )
{
    char arg1 [MAX_INPUT_LENGTH];
    char arg2 [MAX_INPUT_LENGTH];
    char buf[MAX_STRING_LENGTH];
int starthp;
int targethp;
int needexp;
argument = one_argument( argument, arg1 );
argument = one_argument( argument, arg2 );


    if ( arg1[0] == '\0' || arg2[0] == '\0' )
    {
	send_to_char( "Syntax: findexp <starthp> <targethp>\n\r",	ch );
	return;
    }


starthp = atoi( arg1 );
targethp = atoi( arg2 );


	while (starthp < targethp)
	{

		starthp = starthp + 1;
		needexp = needexp + starthp;
	}

    sprintf(buf,"You need %d exp %d and %d.",needexp,starthp, targethp);
    send_to_char(buf,ch);
    return;
}
