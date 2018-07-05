#include "include.h"

//Ftag section
#define FTAG_MIN_VNUM		30500
#define FTAG_MAX_VNUM		30524

DECLARE_DO_FUN( do_transfer );

void do_doubleexp( CHAR_DATA *ch, char *argument )
{
        char  buf[MAX_STRING_LENGTH],arg[MAX_INPUT_LENGTH];
 
    DESCRIPTOR_DATA *d;
 
if (!ch->desc || *argument == '\0')
{
  send_to_char("Syntax: doubleexp  on/off!\n\r",ch);
  return;
}
 
   if ( strcmp(argument,"on")== 0 )
      {
        dxp_info.dxp = 1;
        sprintf(buf, "Double exp has been activated by %s.\n\r", ch->name);
        do_info(ch, buf);
        return;
      }
 
   else if ( strcmp(argument,"off")== 0 )
      {
        sprintf(buf,"Double exp has been deactivated by %s.\n\r", ch->name);
        do_info(ch, buf);
        dxp_info.dxp = 0;
        return;
      }
   else
      {
        send_to_char("The Commands are On and Off",ch);
        return;
      }
}
void do_favplace( CHAR_DATA *ch, char *argument )
{
    char buf[MAX_STRING_LENGTH];
    CHAR_DATA *victim;
    CHAR_DATA *mount;
    ROOM_INDEX_DATA *location;
 
if (IS_SET(ch->act,PLR_CHALLENGER) || IS_SET(ch->act,PLR_CHALLENGED))
{
send_to_char("You cannot go to your favorite place during the Arena!",ch);
return;
}
    act( "$n's body flickers with red energy.", ch, NULL, NULL, TO_ROOM );
    act( "Your body flickers with red energy.", ch, NULL, NULL, TO_CHAR );
 
    if ( ( location = get_room_index( ch->xkilla->favorite ) ) == NULL )
    {
        send_to_char( "You have no favorite place.\n\r", ch );
        return;
    }
 
    if ( ch->in_room == location )
        return;
 
    if ( IS_SET(ch->in_room->room_flags, ROOM_NO_RECALL)
    ||   IS_AFFECTED(ch, AFF_CURSE) )
    {
        send_to_char( "You are unable to go to your favorite place.\n\r", ch );
        return;
    }
 
    if ( ( victim = ch->fighting ) != NULL )
    {
        if ( number_bits( 1 ) == 0 )
        {
            WAIT_STATE( ch, 4 );
            sprintf( buf, "You failed!\n\r" );
            send_to_char( buf, ch );
            return;
        }
        sprintf( buf, "You run to your favorite place in combat!\n\r");
        send_to_char( buf, ch );
        stop_fighting( ch, TRUE );
    }
 
    act( "$n disappears.", ch, NULL, NULL, TO_ROOM );
    char_from_room( ch );
    char_to_room( ch, location );
    act( "$n appears in the room.", ch, NULL, NULL, TO_ROOM );
    do_look( ch, "auto" );
    if ( ( mount = ch->mount ) == NULL ) return;
    char_from_room( mount );
    char_to_room( mount, ch->in_room );
    return;
}

void do_favorite( CHAR_DATA *ch, char *argument )
{
    char arg [MAX_INPUT_LENGTH];
 
    argument = one_argument( argument, arg );
 
    if ( IS_NPC(ch) ) return;
 
    if ( arg[0] == '\0' || str_cmp(arg,"here") )
    {
        send_to_char( "If you want to make this your favorite place type, 'favorite here'.\n\r", ch );
        return;
    }
 
    if ( ch->in_room->vnum == ch->xkilla->favorite )
    {
        send_to_char( "But this is already your favorite place.\n\r", ch );
        return;
    }
 
    if ( IS_SET(ch->in_room->room_flags, ROOM_NO_RECALL) ||
         IS_SET(ch->in_room->room_flags, ROOM_SAFE) )
    {
        send_to_char( "You are unable to make this room your favorite place.\n\r", ch );
        return;
    }
 
    ch->xkilla->favorite = ch->in_room->vnum;
    send_to_char( "This room is now your favorite place.\n\r", ch );
 
    return;
}


void do_mystic( CHAR_DATA *ch, char *argument )
{
    char buf[MAX_STRING_LENGTH];
    OBJ_DATA *obj;
    OBJ_DATA *in_obj;
    bool found;
 
    if (IS_NPC(ch)) {send_to_char("Not while switched.\n\r",ch); return;}
 
    found = FALSE;
        send_to_char("The Mystic items found in the land of kalos are: \n\r",ch);
 
    for ( obj = object_list; obj != NULL; obj = obj->next )
    {
        if ( !IS_SET(obj->quest, QUEST_MYSTIC) ) continue;
 
        found = TRUE;
        for ( in_obj = obj; in_obj->in_obj != NULL; in_obj = in_obj->in_obj )
            ;
        if ( in_obj->carried_by != NULL )
        {
            sprintf( buf, "%s created by %s and carried by %s.\n\r",
                obj->short_descr, obj->questmaker,
                PERS(in_obj->carried_by, ch) );
        }
        else
        {
            sprintf( buf, "%s created by %s and in %s.\n\r",
                obj->short_descr, obj->questmaker,
                in_obj->in_room == NULL ? "somewhere" : in_obj->in_room->name );
        }
 
        buf[0] = UPPER(buf[0]);
        send_to_char( buf, ch );
    }
 
    if ( !found )
        send_to_char( "There are no mystics in the game.\n\r", ch );
 
    return;
}

void do_red( CHAR_DATA *ch, char *argument )
{
    DESCRIPTOR_DATA *d;
    char buf [MAX_STRING_LENGTH];

#ifdef DEBUG
        Debug ("do_red");
#endif

    if ( argument[0] == '\0' )
    {
	send_to_char( "Syntax:  red <message>\n\r", ch );
	return;
    }

    if (!IS_IMMORTAL(ch) && !IS_SET(ch->tag_flags,TAG_PLAYING))
    {
	send_to_char( "You must be a freeze tag player to use this channel.\n\r", ch );
	return;
    }

    if (IS_SET(ch->tag_flags,TAG_RED) || IS_IMMORTAL(ch) )
    {
	sprintf(buf,"#1{RED}#4 %s#n: %s\n\r",ch->name,argument);
	send_to_char(buf, ch);
    }
    else	
    {
	send_to_char( "You aren't on the red team.\n\r",ch);
	return;
    }

    for ( d = descriptor_list; d != NULL; d = d->next )
    {
	if ( (d->connected == CON_PLAYING)
      && (IS_SET(d->character->tag_flags,TAG_RED) || IS_IMMORTAL(d->character)) && d->character != ch) 
	{
	  send_to_char(buf, d->character);
	}
    }
}

void do_blue( CHAR_DATA *ch, char *argument )
{
    DESCRIPTOR_DATA *d;
    char buf [MAX_STRING_LENGTH];

#ifdef DEBUG
        Debug ("do_blue");
#endif

    if ( argument[0] == '\0' )
    {
	send_to_char( "Syntax:  blue <message>\n\r", ch );
	return;
    }

    if (!IS_IMMORTAL(ch) && !IS_SET(ch->tag_flags,TAG_PLAYING))
    {
	send_to_char( "You must be a freeze tag player to use this channel.\n\r", ch );
	return;
    }

    if (IS_SET(ch->tag_flags,TAG_BLUE) || IS_IMMORTAL(ch) )
    {
	sprintf(buf,"#4{BLUE}#1 %s#n: %s\n\r",ch->name,argument);
	send_to_char(buf, ch);
    }
    else	
    {
	send_to_char( "You aren't on the blue team.\n\r",ch);
	return;
    }

    for ( d = descriptor_list; d != NULL; d = d->next )
    {
	if ( (d->connected == CON_PLAYING)
      && (IS_SET(d->character->tag_flags,TAG_BLUE) || IS_IMMORTAL(d->character)) && d->character != ch ) 
	{
	  send_to_char(buf, d->character);
	}
    }
}

void check_team_frozen ( CHAR_DATA *ch )
{
    DESCRIPTOR_DATA *d;

#ifdef DEBUG
        Debug ("check_team_frozen");
#endif

    if (IS_SET(ch->tag_flags,TAG_BLUE))
    {
	for ( d = descriptor_list; d != NULL; d = d->next )
	{
	  if ( (d->connected == CON_PLAYING)
        &&   IS_SET(d->character->tag_flags,TAG_PLAYING)
        &&   IS_SET(d->character->tag_flags,TAG_BLUE)
	  &&   !IS_NPC(d->character)
        &&   !IS_SET(d->character->tag_flags,TAG_FROZEN)) 
	  {
	    return;
	  }
	}
	do_info(ch,"The #1RED#n team has won FREEZE TAG!!!");
    return;
    }

    if (IS_SET(ch->tag_flags,TAG_RED))
    {
	for ( d = descriptor_list; d != NULL; d = d->next )
	{
	  if ( (d->connected == CON_PLAYING)
        &&   IS_SET(d->character->tag_flags,TAG_PLAYING)
        &&   IS_SET(d->character->tag_flags,TAG_RED)
	  &&   !IS_NPC(d->character)
        &&   !IS_SET(d->character->tag_flags,TAG_FROZEN)) 
	  {
	    return;
	  }
	}
	do_info(ch,"The #4BLUE#n team has won FREEZE TAG!!!");
    return;
    }
}

void do_ftag( CHAR_DATA *ch, char *argument )
{
    DESCRIPTOR_DATA *d;
    char arg1 [MAX_INPUT_LENGTH];
    char arg2 [MAX_INPUT_LENGTH];
    char buf [MAX_STRING_LENGTH];
    CHAR_DATA *victim;
    bool fRed = FALSE;

#ifdef DEBUG
        Debug ("do_ftag");
#endif

    argument = one_argument( argument, arg1 );

    if ( arg1[0] == '\0' )
    {
	send_to_char( "Syntax:  ftag reset\n\r", ch );
	send_to_char( "         ftag start\n\r", ch );
	send_to_char( "         ftag auto (splits everyone in room onto teams)\n\r", ch );
	send_to_char( "         ftag red <player>\n\r", ch );
	send_to_char( "         ftag blue <player>\n\r", ch );
	return;
    }

    if ( !str_cmp( arg1, "reset" ) )
    {
	for ( d = descriptor_list; d != NULL; d = d->next )
	{
	  if (d->connected != CON_PLAYING)
	    continue;

	  if ( IS_SET(d->character->tag_flags,TAG_PLAYING))
	  {
	    REMOVE_BIT(d->character->tag_flags,TAG_PLAYING);
	    if (!IS_NPC(d->character))
	    {
		sprintf(buf,"%s %d",d->character->name,ROOM_VNUM_TEMPLE);
		do_transfer(ch,buf);
	    }
	  }
	  if ( IS_SET(d->character->tag_flags,TAG_FROZEN))
	    REMOVE_BIT(d->character->tag_flags,TAG_FROZEN);
	  if ( IS_SET(d->character->tag_flags,TAG_RED))
	    REMOVE_BIT(d->character->tag_flags,TAG_RED);
	  if ( IS_SET(d->character->tag_flags,TAG_BLUE))
	    REMOVE_BIT(d->character->tag_flags,TAG_BLUE);
        send_to_char( "Freeze tag has been stopped!\n\r", d->character );
	}
	send_to_char( "All players reset.\n\r", ch );
	return;
    }

    if ( !str_cmp( arg1, "start" ) )
    {
	for ( d = descriptor_list; d != NULL; d = d->next )
	{
	  if (d->connected != CON_PLAYING)
	    continue;

	  if ( IS_SET(d->character->tag_flags,TAG_PLAYING)
		 && !IS_NPC(d->character))
	  {
	    sprintf(buf,"%s %d",d->character->name,
		number_range(FTAG_MIN_VNUM,FTAG_MAX_VNUM));
	    REMOVE_BIT(d->character->tag_flags,TAG_FROZEN);
	    do_transfer(ch,buf);
	    send_to_char( "Freeze Tag has started!\n\r", d->character );
	  }
	}
	send_to_char( "You have started a game of Freeze Tag.\n\r", ch );
	return;
    }

    if ( !str_cmp( arg1, "auto" ) )
    {
	for ( victim = ch->in_room->people; victim != NULL; 
			victim = victim->next_in_room )
	{
	  if ( victim == ch || IS_NPC(victim))
	    continue;

	  if ((fRed = !fRed))
	  {
	    sprintf(buf,"red %s",victim->name);
	  }
	  else
	  {
	    sprintf(buf,"blue %s",victim->name);
	  }

	  do_ftag(ch,buf);
	}
	return;
    }

    argument = one_argument( argument, arg2 );
    if ( arg2[0] == '\0' ||
	   (str_cmp( arg1, "red" ) &&
	    str_cmp( arg1, "blue" )))
    {
	send_to_char( "Syntax:  ftag reset\n\r", ch );
	send_to_char( "         ftag start\n\r", ch );
	send_to_char( "         ftag auto (splits everyone in room onto teams)\n\r", ch );
	send_to_char( "         ftag red <player>\n\r", ch );
	send_to_char( "         ftag blue <player>\n\r", ch );
	return;
    }

    if ( ( victim = get_char_room( ch, arg2 ) ) == NULL )
    {
	send_to_char( "They aren't here.\n\r", ch );
	return;
    }

    if ( !str_cmp( arg1, "red" ) )
    {
	SET_BIT(victim->tag_flags,TAG_PLAYING);
	REMOVE_BIT(victim->tag_flags,TAG_FROZEN);
	SET_BIT(victim->tag_flags,TAG_RED);
	REMOVE_BIT(victim->tag_flags,TAG_BLUE);
	act( "You are on the #1RED#n team!", ch, NULL, victim, TO_VICT );
	act( "$N is on the #1RED#n team!",   ch, NULL, victim, TO_NOTVICT );
	act( "$N is on the #1RED#n team!",   ch, NULL, victim, TO_CHAR    );
    }
    else
    if ( !str_cmp( arg1, "blue" ) )
    {
	SET_BIT(victim->tag_flags,TAG_PLAYING);
	REMOVE_BIT(victim->tag_flags,TAG_FROZEN);
	SET_BIT(victim->tag_flags,TAG_BLUE);
	REMOVE_BIT(victim->tag_flags,TAG_RED);
	act( "You are on the #4BLUE#n team!", ch, NULL, victim, TO_VICT );
	act( "$N is on the #4BLUE#n team!",   ch, NULL, victim, TO_NOTVICT );
	act( "$N is on the #4BLUE#n team!",   ch, NULL, victim, TO_CHAR    );
    }

    return;
}

void do_ztag( CHAR_DATA *ch, char *argument )
{
    char arg [MAX_INPUT_LENGTH];
    CHAR_DATA *victim;

#ifdef DEBUG
        Debug ("do_tag");
#endif

    argument = one_argument( argument, arg );

    if (!IS_SET(ch->tag_flags,TAG_PLAYING))
    {
	send_to_char( "You're not playing freeze tag.\n\r", ch );
	return;
    }

    if ( arg[0] == '\0' )
    {
	send_to_char( "Tag whom?\n\r", ch );
	return;
    }

    if ( ( victim = get_char_room( ch, arg ) ) == NULL )
    {
	send_to_char( "They aren't here.\n\r", ch );
	return;
    }

    if ( victim == ch )
    {
	send_to_char( "You tag yourself.  How amusing.\n\r", ch );
	return;
    }

    if (!IS_SET(victim->tag_flags,TAG_PLAYING))
    {
	send_to_char( "They're not playing freeze tag.\n\r", ch );
	return;
    }

    if (IS_SET(ch->tag_flags,TAG_FROZEN))
    {
	send_to_char( "You can't tag, you're frozen!\n\r", ch );
	return;
    }

    act( "$n tags you.", ch, NULL, victim, TO_VICT );
    act( "$n tags $N.",  ch, NULL, victim, TO_NOTVICT );
    act( "You tag $N.",  ch, NULL, victim, TO_CHAR    );

    if ((IS_SET(ch->tag_flags,TAG_RED) &&
         IS_SET(victim->tag_flags,TAG_RED))
	||(IS_SET(ch->tag_flags,TAG_BLUE) &&
         IS_SET(victim->tag_flags,TAG_BLUE)))
    {
	if (IS_SET(victim->tag_flags,TAG_FROZEN))
	{
	  REMOVE_BIT(victim->tag_flags,TAG_FROZEN);
	  act( "You are no longer frozen!", ch, NULL, victim, TO_VICT );
	  act( "$N is no longer frozen!",   ch, NULL, victim, TO_NOTVICT );
	  act( "$N is no longer frozen!",   ch, NULL, victim, TO_CHAR    );
	}
	else
	{
	  act( "$N is not frozen!",   ch, NULL, victim, TO_CHAR    );
	}
    }
    else
    {
	if (IS_SET(victim->tag_flags,TAG_FROZEN))
	{
	  act( "$N is already frozen!",   ch, NULL, victim, TO_CHAR    );
	}
	else
	{
	  SET_BIT(victim->tag_flags,TAG_FROZEN);
	  act( "You are frozen!", ch, NULL, victim, TO_VICT );
	  act( "$N is frozen!",   ch, NULL, victim, TO_NOTVICT );
	  act( "$N is frozen!",   ch, NULL, victim, TO_CHAR    );
	  check_team_frozen( victim );
	}
    }

    return;
}

//End

void tag_channel( char * msg );

void tag_channel( char * msg )
{
    char buf[MAX_STRING_LENGTH];
    DESCRIPTOR_DATA *d;

    sprintf(buf, "#5(Tag) #o%s#n", msg );

      for ( d = descriptor_list; d != NULL; d = d->next )
      {
	CHAR_DATA *victim;

	victim = d->original ? d->original : d->character;

	if ( d->connected == CON_PLAYING &&
	     !IS_SET(victim->deaf, CHANNEL_TAG))
	      {
		send_to_char( buf, victim );
	      }
      }

    return;
}

void do_stag( CHAR_DATA *ch, char *argument )
{
	char  buf[MAX_STRING_LENGTH],arg[MAX_INPUT_LENGTH];

    DESCRIPTOR_DATA *d;

if (!ch->desc || *argument == '\0')
{
  send_to_char("Syntax: stag  on/off!\n\r",ch);
  return;
}

   if ( strcmp(argument,"on")== 0 )
      {
        tag_info.tag = TAG_OPENED;
        tag_info.status = 0;
        sprintf(buf, "A game of tag has been started, tag join to enter.\n\r");
        tag_channel( buf );
        return;
      }

   else if ( strcmp(argument,"off")== 0 )
      {
        sprintf(buf,"Tag has now ended.\n\r");
        tag_channel( buf );

       tag_info.status = 10;
       tag_info.tag = TAG_STARTED;

      for ( d = descriptor_list; d != NULL; d = d->next )
      {
        CHAR_DATA *victim;
 
        victim = d->original ? d->original : d->character;
 
        if ( !IS_SET(victim->xkilla->plr, PLR_INTAG)== 0)
              {
                REMOVE_BIT(victim->xkilla->plr, PLR_INTAG);
                sprintf(buf, "Thank you for playing Tag.\n\r");
                send_to_char( buf, victim );
                char_from_room(victim);
                char_to_room(victim,get_room_index(3002));
              }
       }

       return;
      }
   else
      {
	send_to_char("The Commands are On and Off",ch);
	return;
      }
}

void tag_update( )
{
    char buf[MAX_STRING_LENGTH], temp[MAX_STRING_LENGTH],
        temp1[MAX_STRING_LENGTH];
    DESCRIPTOR_DATA *d; 
	int vict_room;

 vict_room = number_range(3002, 3002);

    tag_info.status++;
 
    if ( tag_info.status == TAG_LENGTH )
    {
        sprintf(buf,"Tag has now ended.\n\r");
        tag_channel( buf );
                sprintf(buf, "Thank you for playing Tag.\n\r");

       tag_info.tag = TAG_STARTED;

      for ( d = descriptor_list; d != NULL; d = d->next )
      {
        CHAR_DATA *victim;
 
        victim = d->original ? d->original : d->character;
 
        if ( !IS_SET(victim->xkilla->plr, PLR_INTAG)== 0)
              {
		REMOVE_BIT(victim->xkilla->plr, PLR_INTAG);
                send_to_char( buf, victim );
        	char_from_room(victim);
	        char_to_room(victim,get_room_index(vict_room));
              }
       }
        return;
    }
 
    if ( tag_info.status == TAG_LENGTH - 1 )
    {
        sprintf(buf, "Tag ending in a minute.\n\r");
        tag_channel( buf );
        return;
    }
 
    if ( tag_info.status == TAG_LENGTH - 2 )
    {
        sprintf(buf, "Tag ending in 2 minutes.\n\r");
        tag_channel( buf );
        return;
    }

    if ( tag_info.status == TAG_LENGTH - 9 )
    {
        sprintf(buf, "Tag has now started.\n\r");
        tag_channel( buf );
        return;
    }
 
    return;
 
}

void do_jog( CHAR_DATA *ch, char *argument )
{
char buf[MAX_INPUT_LENGTH],arg[MAX_INPUT_LENGTH];
char *p;
bool dFound = FALSE;

if (!ch->desc || *argument == '\0')
{
  send_to_char("You run in place!\n\r",ch);
  return;
}

buf[0] = '\0';

while (*argument != '\0')
{
  argument = one_argument(argument,arg);
  strcat(buf,arg);
}

for( p = buf + strlen(buf)-1; p >= buf; p--)
{
  if (!isdigit(*p))
  {
    switch( *p )
    {
      case 'n':
      case 's':
      case 'e':
      case 'w':
      case 'u':
      case 'd': dFound = TRUE;
                break;

      case 'o': break;

      default: send_to_char("Invalid direction!\n\r",ch);
               return;
    }
  }
  else if (!dFound) *p = '\0';
}

if (!dFound)
{
  send_to_char("No directions specified!\n\r",ch); 
  return;
}

ch->desc->run_buf = str_dup( buf );
ch->desc->run_head = ch->desc->run_buf;
send_to_char("You start running...\n\r",ch);
return;
}

//sigh defining this after making it was the hard part.
void do_pretitle( CHAR_DATA *ch, char *argument )
{
    CHAR_DATA *victim;
    char      arg [MAX_INPUT_LENGTH];
    argument = one_argument( argument, arg );
    if ( IS_NPC(ch) ) return;
 
    if ( arg[0] == '\0' )
    {
    send_to_char( "Who`s pretitle do you wish to change?\n\r", ch );
        return;
    }
 
    if ( ( victim = get_char_room( ch, arg ) ) == NULL )
    {
        send_to_char( "They aren`t here.\n\r", ch );
        return;
    }
    if ( IS_NPC(victim) ) return;
 
    if ( strlen(argument) < 0 || strlen(argument) > 25 )
    {
        send_to_char( "Pretitle name should be between 0 and 25 letters long.\n\r", ch );
        send_to_char( "Leave a blank to remove pretitle.\n\r", ch);
        return;
    }

    free_string( victim->pcdata->pretit );
    victim->pcdata->pretit = str_dup( argument );
        send_to_char("Pretitle set.\n\r", ch);
        send_to_char("Pretitle set.\n\r", victim);
    return;
}


/* Local functions... */
void do_notag(CHAR_DATA *ch, char *argument);
void game_in_play(CHAR_DATA *ch, char *name);

void do_tag( CHAR_DATA *ch, char *argument )
 {

   CHAR_DATA *victim;
   char      name[MAX_STRING_LENGTH];
   char      buf[MAX_STRING_LENGTH];
 int char_room;
 int vict_room; 

 char_room = number_range(100302,100359);     
 vict_room = number_range(100302,100359);  

   name[0]='\0';
   game_in_play(ch, name);

   if (IS_NPC(ch))
      return;

   if ( argument[0] == '\0' )
      {
      send_to_char("Who do you want to tag?\n\r", ch);
      return;
      }

   if ( strcmp(argument,"show")==0 )
      {
      if ( name[0] == '\0' )
         {
	 send_to_char("There is no game of tag in progress, why not start one!\n\r", ch);
 	 return;
	 }
      else
	 {
	 sprintf(buf, "%s is currently IT!\n\r", name);
	 send_to_char(buf, ch);
	 return;
	 }
      }

   if ( strcmp(argument,"join")== 0 )
      {
     if ( tag_info.tag = TAG_OPENED )
	{
        sprintf(buf, "%s has just joined Tag.\n\r", ch->name);
        tag_channel( buf );
        SET_BIT(ch->xkilla->plr, PLR_INTAG);
        send_to_char("You enter tag.\n\r",ch);
        char_from_room(ch);
        char_to_room(ch,get_room_index(char_room));
        return;
	}
     else if ( tag_info.tag = TAG_STARTED )
         {
         sprintf(buf, "No tag game in progress.\n\r");
         send_to_char(buf, ch);
         return;
         }
     else if (IS_SET(ch->act, PLR_NOTAG ))
	{
	send_to_char("You cannot join tag with notag on",ch);
	return;
	}
     else if (IS_SET(ch->xkilla->plr,PLR_INTAG))
	{
	send_to_char("You cannot join tag 2x!",ch);
	return;
	}
      else
         {
	send_to_char("Bug- Tell Xkilla.", ch);
        return;
         }
      }

    victim = get_char_world(ch,argument);
		 
    if ( victim == NULL )
       {
       send_to_char( "They aren't playing!\n\r", ch);
       return;
       }

     if ( IS_NPC(victim) )
        {
        send_to_char("Sorry! NPC's can't play tag!\n\r", ch);
	return;
        }


     if (IS_SET(victim->act, PLR_NOTAG) )
        {
        send_to_char("They don't want to play tag... Spoil sports!\n\r", ch);
        return;
        }

     if ( (name[0] == '\0' ) ) /* No Game in progress... */
        {
        if ( ch->name == victim->name ) /* Player tags self... */
           {
	   send_to_char("Why tag yourself!\n\r", ch);
	   return;
	   }
        else /* Player tags someone else... */
	   {
	   if ((ch->in_room->vnum == victim->in_room->vnum) && ( ch->in_room->vnum >= 100301 && victim->in_room->vnum <= 100361 )) 
              {
	      SET_BIT(victim->act, PLR_TAG );
			
	      sprintf(buf, "%s tags you!'\n\r", ch->name);
	      send_to_char(buf, victim);
			
	      sprintf(buf, "You tag %s!'\n\r", victim->name);
	      send_to_char(buf, ch);

        sprintf(buf,"#oTag game started, %s has tagged %s.#n", ch->name, victim->name);
        tag_channel(buf);			

	      return;
              }
 	   else 
	      {
	      send_to_char("You are not in the tag arena...\n\r", ch);
	      return;
	      }
			   
	    }
          }
       else /* There is a game in play... */
	  {
	  if (!IS_SET(ch->act, PLR_TAG) ) /* The player calling tag isn't IT */
	     {
	     sprintf(buf, "There is already a game in play, and %s is IT!\n\r", name);
	     send_to_char(buf, ch);
	     return;
	     }
	   else /* The player calling tag is IT */
             {
	      if (ch->name == victim->name ) /* Player tags self... */
	         {
		 send_to_char("Tagging yourself won't get you anywhere!\n\r", ch);
		 return;
	         }
	      else /* Player Tags someone else... */
	         {
	         if ((ch->in_room->vnum == victim->in_room->vnum) && ( ch->in_room->vnum >= 100301 && victim->in_room->vnum <= 100361 ))
		    {
		    SET_BIT(victim->act, PLR_TAG );
		    REMOVE_BIT(ch->act, PLR_TAG );

		    sprintf(buf, "%s tags you!'\n\r", ch->name);
		    send_to_char(buf, victim);
		    sprintf(buf, "You tag %s!'\n\r", victim->name);
		    send_to_char(buf, ch);
        sprintf(buf,"#o%s has just tagged %s.#n", ch->name, victim->name);
        tag_channel(buf);
send_to_char("\n\rYou were tagged.\n\r",victim);
char_from_room(victim);
char_to_room(victim,get_room_index(100301));
		    return;
		    } 
		 else
		    {
		    send_to_char("You are not in the tag arena...\n\r", ch);
		    return;
		    }
		 } /* End of Player Tags someone else... */ 
	      } /* End of Player calling tag is IT */
	   } /* End of there is a game in play */
	} /* End of do_tag */
		
/********************************************************************/

void do_notag(CHAR_DATA *ch, char *argument) /*Removes a players TAG flag if set... */
{
        if (IS_SET (ch->act, PLR_NOTAG ) )
           {
           send_to_char("You now allow people to tag you. (YAY!)\n\r", ch);
           REMOVE_BIT( ch->act, PLR_NOTAG );
           return;
           }
        if (IS_SET(ch->xkilla->plr, PLR_INTAG ))
        {
        send_to_char("You cannot notag while you are in Tag.",ch);
        return;
        }
        else
           {
           send_to_char("You nolonger let people tag you... (Spoil Sport!)\n\r", ch);
           SET_BIT( ch->act, PLR_NOTAG );
           return;
           }
}

/********************************************************************/

void game_in_play(CHAR_DATA *ch, char *name)
{
	CHAR_DATA       *on_it;
	DESCRIPTOR_DATA	*d;

	for ( d = descriptor_list; d; d = d->next )
	  {
	  if ( d->connected == CON_PLAYING && IS_SET(d->character->act, PLR_TAG) )
		  {
		  on_it = d->character;
		  strcpy(name, d->character->name);
		  }
	  }
	 return;
}


void do_selfrestore( CHAR_DATA *ch, char *argument )
{
    if (IS_NPC(ch)) return;
    if (ch->in_room == NULL || ch->in_room->vnum != 3002)
    {
        send_to_char("You can only get a restore at the Chamber of  Light.\n\rFor 100,000xp.\n\r",ch);
        return;
    }
        if ( ch->exp < 100000)
        {
            send_to_char("You need 100,000 xp to restore self.\n\r", ch);
            return;
        }
    ch->exp   -= 100000;
do_restore(ch,"self");
    send_to_char("God answers you, you are restored.\n\r",ch);
    return;
}

void do_gemote( CHAR_DATA *ch, char *argument )
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
            send_to_char( "#2[#4Gemote#2] ", d->character );
            sprintf(buf, "#0%s #1%s#n", ch->name, argument);
            send_to_char( buf, d->character);
            send_to_char( "#n\n\r",   d->character );
        }
    }
 
    return;
}

void do_numlock( CHAR_DATA *ch, char *argument )
{
           char       buf  [ MAX_STRING_LENGTH ];
           char       arg1 [ MAX_INPUT_LENGTH  ];
    extern int        numlock;
           int        temp;
 
 
 
    one_argument( argument, arg1 );
 
    temp = atoi( arg1 );
 
    if ( arg1[0] == '\0' ) 
    {
        sprintf( buf, "Current numlock setting is:  %d.\n\r", numlock );
        send_to_char( buf, ch );
        return;
    }
 
    if ( ( temp < 0 ) || ( temp > 11 ) )
    {
        sprintf( buf, "Level must be between 0 and 11.\n\r" );
        send_to_char( buf, ch );
        return;
    }
 
    numlock = temp;
 
    if ( numlock != 0 )
    {
        sprintf( buf, "Game numlocked to levels %d and below.\n\r", numlock );
        send_to_char( buf, ch );
    }
    else

        send_to_char( "Game now open to all levels.\n\r", ch );
 
    return;
 
}

void do_newlock( CHAR_DATA *ch, char *argument )
{
	   extern int        numlock;
           char       buf [ MAX_STRING_LENGTH ];
 
 
    if ( numlock != 0 && get_trust( ch ) < MAX_LEVEL )
    {
        send_to_char( "You may not change the current numlock setting\n\r",
                     ch );
        sprintf( buf, "Game numlocked to levels %d and below.\n\r", numlock );
        send_to_char( buf, ch );
        return;
    }
 
    if ( numlock != 0 )
    {
        sprintf( buf, "Game numlocked to levels %d and below.\n\r", numlock );
        send_to_char( buf, ch );
        send_to_char( "Changing to: ", ch );
    }
 
    numlock = 1;
    send_to_char( "Game locked to new characters.\n\r", ch );
    return;
 
}

void do_nobeep( CHAR_DATA *ch, char *argument )
{
    if ( IS_NPC(ch) ) return;
    if (IS_SET(ch->act, XKAFF_NOBEEP)) do_config(ch,"-nobeep");
    else do_config(ch,"+nobeep");
    return;
}

void do_makesave( CHAR_DATA *ch, char *argument )
{
    CHAR_DATA *victim;
    char arg[MAX_INPUT_LENGTH];
    char buf[MAX_STRING_LENGTH];
 
    if ( IS_NPC( ch ) )
        return;
 
    argument = one_argument( argument, arg );
 
    if ( arg[0] == '\0' )
    {
        send_to_char( "Make who save?\n\r", ch );
        return;
    }
 
    if ( !( victim = get_char_world( ch, arg ) ) )
    {
        send_to_char( "They are not here.\n\r", ch );
        return;
    }
 
        if ( victim->level == 1 )
        {
	victim->level = 2;
    sprintf( buf, "%s has given you early permission to save.\n\r", ch->name );
    send_to_char( buf, victim );
    send_to_char( "Done...\n\r", ch);
    do_save(victim,"");
        return;
	}
    else
    send_to_char("They are not level 1.\n\r", ch) ;
 
    return;
 
}

void do_beep( CHAR_DATA *ch, char *argument )
{
    CHAR_DATA *victim;
    char arg[MAX_INPUT_LENGTH];
    char buf[MAX_STRING_LENGTH];

    if ( IS_NPC( ch ) )
        return;

    argument = one_argument( argument, arg );
    
    if ( arg[0] == '\0' )
    {
	send_to_char( "Beep who?\n\r", ch );
        return;
    }

    if ( !( victim = get_char_world( ch, arg ) ) )
    {
	send_to_char( "They are not here.\n\r", ch );
	return;
    }

    if ( IS_NPC( victim ) && IS_SET(ch->act, XKAFF_NOBEEP) )
    {
	send_to_char( "They are not beepable.\n\r", ch );
	return;
    }

    sprintf( buf, "You beep %s.\n\r", victim->name );
    send_to_char( buf, ch );
    
    sprintf( buf, "\a\a%s has beeped you.\n\r", ch->name );
    send_to_char( buf, victim );

    return;

}


int scan_room (CHAR_DATA *ch, const ROOM_INDEX_DATA *room,char *buf)
{
    CHAR_DATA *target = room->people;
    int number_found = 0;
 
    while (target != NULL) /* repeat as long more peple in the room */
    {
        if (can_see(ch,target)) /* */
        {
            strcat (buf, " - ");
            strcat (buf, IS_NPC(target) ? target->short_descr :
target->name);
            strcat (buf, "\n\r");
            number_found++;
        }
        target = target->next_in_room;
    }
 
    return number_found;
}
 
 
void do_scan (CHAR_DATA *ch, char *argument)
{
    EXIT_DATA * pexit;
    ROOM_INDEX_DATA * room;
    extern char * const dir_name[];
    char buf[MAX_STRING_LENGTH];
    int dir;
    int distance;
 
    sprintf (buf, "#7Right here you see:\n\r");
    if (scan_room(ch,ch->in_room,buf) == 0)
        strcat (buf, "None\n\r");
    send_to_char (buf,ch);
 
    for (dir = 0; dir < 6; dir++) /* look in every direction */
    {
        room = ch->in_room; /* starting point */
 
        for (distance = 1 ; distance < 4; distance++)
        {
            pexit = room->exit[dir]; /* find the door to the next room */
            if ((pexit == NULL) || (pexit->to_room == NULL) || (IS_SET(pexit->exit_info, EX_CLOSED)))
                break; /* exit not there OR points to nothing OR is closed */
 
            /* char can see the room */
            sprintf (buf, "#7[ %d | %s #7]\n\r", distance, dir_name[dir]);
            if (scan_room(ch,pexit->to_room,buf))
                send_to_char (buf,ch);
 
            room = pexit->to_room; /* go to the next room */
        } /* for distance */
    } /* for dir */
}

void do_gsocial(CHAR_DATA *ch, char *argument)
{
    char command[MAX_INPUT_LENGTH];
    CHAR_DATA *victim;
    int cmd;
    bool found;
    char arg[MAX_INPUT_LENGTH];
    DESCRIPTOR_DATA *d;
    char buf[MAX_STRING_LENGTH];
    int counter;
    int count;
    char buf2[MAX_STRING_LENGTH];

    argument = one_argument(argument,command);

    if (command[0] == '\0')
    {
        send_to_char("What do you wish to gocial?\n\r",ch);
        return;
    }

    found = FALSE;
    for (cmd = 0; social_table[cmd].name[0] != '\0'; cmd++)
    {
        if (command[0] == social_table[cmd].name[0]
        && !str_prefix( command,social_table[cmd].name ) )
        {
            found = TRUE;
            break;
        }
    }

    if (!found)
    {
        send_to_char("What kind of social is that?!?!\n\r",ch);
        return;
    }


    if ( !IS_NPC(ch) && IS_SET(ch->deaf, CHANNEL_GSOCIAL))
    {
        send_to_char("But you have the gsocial channel turned off!\n\r",ch);
        return;
    }

    if ( !IS_NPC(ch) && IS_SET(ch->act, PLR_SILENCE))
    {
        send_to_char("The gods have revoked your channel priviliges.\n\r",ch);
        return;
    }

    switch (ch->position)
    {
    case POS_DEAD:
        send_to_char("Lie still; you are DEAD!\n\r",ch);
        return;
    case POS_INCAP:
    case POS_MORTAL:
        send_to_char("You are hurt far too bad for that.\n\r",ch);
        return;
    case POS_STUNNED:
        send_to_char("You are too stunned for that.\n\r",ch);
        return;
    }

    one_argument(argument,arg);
    victim = NULL;
    if (arg[0] == '\0')
    {
        sprintf(buf, "#2[#1Social#2]#n#0 %s#n", social_table[cmd].char_no_arg );
        act3(buf,ch,NULL,NULL,TO_CHAR,POS_DEAD);
        sprintf(buf, "#2[#1Social#2]#n#0 %s#n", social_table[cmd].others_no_arg );
        for (d = descriptor_list; d != NULL; d = d->next)
        {
            CHAR_DATA *vch;
            vch = d->original ? d->original : d->character;
            if (d->connected == CON_PLAYING &&
                d->character != ch &&
                !IS_SET(vch->deaf, CHANNEL_GSOCIAL))
            {
                act3(buf,ch,NULL,vch,TO_VICT,POS_DEAD);
            }
        }
    }
    else if ((victim = get_char_world(ch,arg)) == NULL)
    {
        send_to_char("They aren't here.\n\r",ch);
        return;
    }
    else if (victim == ch)
    {
        sprintf(buf,"#2[#1Social#2]#n#0 %s#n", social_table[cmd].char_auto);
        act3(buf,ch,NULL,NULL,TO_CHAR,POS_DEAD);
        sprintf(buf,"#2[#1Social#2]#n#0 %s#n", social_table[cmd].others_auto);
        for (d = descriptor_list; d != NULL; d = d->next)
        {
            CHAR_DATA *vch;
            vch = d->original ? d->original : d->character;
            if (d->connected == CON_PLAYING &&
                d->character != ch &&
                !IS_SET(vch->deaf, CHANNEL_GSOCIAL))
            {
                act3(buf,ch,NULL,vch,TO_VICT,POS_DEAD);
            }
        }
    }
    else
    {
        sprintf(buf,"#2[#1Social#2]#n#0 %s#n", social_table[cmd].char_found);
        act3(buf,ch,NULL,victim,TO_CHAR,POS_DEAD);
        sprintf(buf,"#2[#1Social#2]#n#0 %s#n", social_table[cmd].vict_found);
        act3(buf,ch,NULL,victim,TO_VICT,POS_DEAD);
        
        sprintf(buf,"#2[#1Social#2]#n#0 %s#n", social_table[cmd].others_found);
        for (counter = 0; buf[counter+1] != '\0'; counter++)
        {
            if (buf[counter] == '$' && buf[counter + 1] == 'N')
            {
                strcpy(buf2,buf);
                buf2[counter] = '\0';
                strcat(buf2,victim->name);
                for (count = 0; buf[count] != '\0'; count++)
                {
                    buf[count] = buf[count+counter+2];
                }
                strcat(buf2,buf);
                strcpy(buf,buf2);

            }
            else if (buf[counter] == '$' && buf[counter + 1] == 'E')
            {
                switch (victim->sex)
                {
                default:
                    strcpy(buf2,buf);
                    buf2[counter] = '\0';
                    strcat(buf2,"it");
                    for (count = 0; buf[count] != '\0'; count ++)
                    {
                        buf[count] = buf[count+counter+2];
                    }
                    strcat(buf2,buf);
                    strcpy(buf,buf2);
                    break;
                case 1:
                    strcpy(buf2,buf);
                    buf2[counter] = '\0';
                    strcat(buf2,"it");
                    for (count = 0; buf[count] != '\0'; count++)
                    {
                        buf[count] = buf[count+counter+2];
                    }
                    strcat(buf2,buf);
                    strcpy(buf,buf2);
                    break;
                case 2:
                    strcpy(buf2,buf);
                    buf2[counter] = '\0';
                    strcat(buf2,"it");
                    for (count = 0; buf[count] != '\0'; count++)
                    {
                        buf[count] = buf[count+counter+2];
                    }
                    strcat(buf2,buf);
                    strcpy(buf,buf2);
                    break;
                }
            }
            else if (buf[counter] == '$' && buf[counter + 1] == 'M')
            {
                buf[counter] = '%';
                buf[counter + 1] = 's';
                switch (victim->sex)
                {
                default:
                    strcpy(buf2,buf);
                    buf2[counter] = '\0';
                    strcat(buf2,"it");
                    for (count = 0; buf[count] != '\0'; count++)
                    {
                        buf[count] = buf[count+counter+2];
                    }
                    strcat(buf2,buf);
                    strcpy(buf,buf2);
                    break;
                case 1:
                    strcpy(buf2,buf);
                    buf2[counter] = '\0';
                    strcat(buf2,"him");
                    for (count = 0; buf[count] != '\0'; count++)
                    {
                        buf[count] = buf[count+counter+2];
                    }
                    strcat(buf2,buf);
                    strcpy(buf,buf2);
                    break;
                case 2:
                    strcpy(buf2,buf);
                    buf2[counter] = '\0';
                    strcat(buf2,"her");
                    for (count = 0; buf[count] != '\0'; count++);
                    {
                        buf[count] = buf[count+counter+2];
                    }
                    strcat(buf2,buf);
                    strcpy(buf,buf2);
                    break;
                }
            }
            else if (buf[counter] == '$' && buf[counter + 1] == 'S')
            {
                switch (victim->sex)
                {
                default:
                strcpy(buf2,buf);
                buf2[counter] = '\0';
                strcat(buf2,"its");
                for (count = 0;buf[count] != '\0'; count++)
                {
                    buf[count] = buf[count+counter+2];
                }
                strcat(buf2,buf);
                strcpy(buf,buf2);
                break;
                case 1:
                    strcpy(buf2,buf);
                    buf2[counter] = '\0';
                    strcat(buf2,"his");
                    for (count = 0; buf[count] != '\0'; count++)
                    {
                        buf[count] = buf[count+counter+2];
                    }
                    strcat(buf2,buf);
                    strcpy(buf,buf2);
                    break;
                case 2:
                    strcpy(buf2,buf);
                    buf2[counter] = '\0';
                    strcat(buf2,"hers");
                    for (count = 0; buf[count] != '\0'; count++)
                    {
                        buf[count] = buf[count+counter+2];
                    }
                    strcat(buf2,buf);
                    strcpy(buf,buf2);
                    break;
                }
            }

        }
        for (d=descriptor_list; d != NULL; d = d->next)
        {
            CHAR_DATA *vch;
            vch = d->original ? d->original : d->character;
            if (d->connected == CON_PLAYING &&
                d->character != ch &&
                d->character != victim &&
                !IS_SET(vch->deaf, CHANNEL_GSOCIAL))
            {
                act3(buf,ch,NULL,vch,TO_VICT,POS_DEAD);
            }
        }
    }
    return;
}


bool free_helps( CHAR_DATA *ch, char *arg )
{
    char buf[MAX_STRING_LENGTH];
    HELP_DATA *h, *h_next;
    HELP_DATA *prev = NULL;
    bool found = FALSE;

    prev = help_first;
    for ( h = help_first; h; h = h_next )
    {
	h_next = h->next;

        if ( !str_cmp( h->keyword, arg ) )
        {
            free_string( h->keyword );
            free_string( h->text );
            if ( h == help_first )
                help_first = h->next;
            else
            prev->next = h->next;
            if ( h == help_last )
               help_last = prev;
            free_mem( h, sizeof(*h) );
            found = TRUE;
        }
        prev = h;
    }

//    if ( !found )
//    {
//        sprintf( buf, "Help entry %s not found.\n\r", arg );
//        send_to_char( buf, ch );
//        return FALSE;
//    }

    return TRUE;
}


bool read_entry( CHAR_DATA *ch, FILE *fp, char *filename, char *arg )
{
    char buf[MAX_STRING_LENGTH];
    HELP_DATA *new;
    HELP_DATA *debug;
    char *test_keyword = 0;
    char *test_text = 0;
    int test_level = 0;

    if ( fread_letter( fp ) != '#' )
    {
        sprintf( buf, "read_entry: # not in %s.\n\r", filename );
        send_to_char( buf, ch );
        return FALSE;
    }

    fread_word( fp ); /* read the word HELPS */

    new          = alloc_mem( sizeof(*new) );
    new->next    = NULL;

    for ( ; ; )
    {
        test_level   = fread_number( fp );
        test_keyword = fread_string( fp );

        if ( !str_cmp( test_keyword, "$" )) /* end of file */
        {
            free_string( test_keyword );
            free_string( test_text );
            free_mem( new, sizeof(*new) );
            return FALSE;
        }

        test_text    = fread_string( fp );

        if ( !str_cmp( test_keyword, arg ))  /* match */
        {
            new->keyword = test_keyword;
            new->level   = test_level;
            new->text    = test_text;

            debug = help_last;
            if ( help_last ) 
                help_last->next = new;
            help_last = new;
            
            sprintf( buf, "entry %s updated.\n\r", new->keyword );
            send_to_char( buf, ch );
            return TRUE;
        }
        else
        {
            free_string( test_keyword );
            free_string( test_text );
        }
    }

    return FALSE;
}


void do_loadhelp( CHAR_DATA *ch, char *argument )
{
    char arg[MAX_INPUT_LENGTH];
    char buf[MAX_STRING_LENGTH];
    FILE *fp;
    bool found = FALSE;
    int i;

    /* in order of 'importance' */
    char *helpfile[1] = {
        "../area/help.are",
        };

    argument = one_argument( argument, arg );

    if ( arg[0] == '\0' )
    {
        send_to_char( "Usage: reload <help-keyword>\n\r", ch );
        return;
    }

    /* remove help entry from the list */
    if ( !free_helps( ch, arg ))
        return;

    /* here we go */
    fclose( fpReserve );
    for ( i = 0; i < 2; i++ )
    {
        if ( ( fp = fopen( helpfile[i], "r" ) ) == NULL )
        {
            sprintf( buf, "do_loadhelp: helpfile does not exist.\n\r" );
            send_to_char( buf, ch );
        }
        else
        {
            if ( ( found = read_entry( ch, fp, helpfile[i], arg ) ) == TRUE )
            {
                fclose( fp );
                break;
            }
            fclose( fp );
        }
    }
    fpReserve = fopen( NULL_FILE, "r" );
    return;
}


void do_prefi (CHAR_DATA *ch, char *argument)
{
    send_to_char("You cannot abbreviate the prefix command.\r\n",ch);
    return;
}

void do_prefix (CHAR_DATA *ch, char *argument)
{
    char buf[MAX_INPUT_LENGTH];

    if (argument[0] == '\0')
    {
        if (ch->prefix[0] == '\0')
        {
            send_to_char("You have no prefix to clear.\r\n",ch);
            return;
        }                                                                      
        send_to_char("Prefix removed.\r\n",ch);
        free_string(ch->prefix);
        ch->prefix = str_dup("");
        return;
    }

    if (ch->prefix[0] != '\0')
    {
        sprintf(buf,"Prefix changed to %s.\r\n",argument);
        free_string(ch->prefix);
    }
    else
    {
        sprintf(buf,"Prefix set to %s.\r\n",argument);
    }
                                 
    ch->prefix = str_dup(argument);
    return;
}                        

char *const pos_table[]=
{
"dead", "mortal", "incap", "stun", "sleep", "rest", "sit", "fight", "stand",
NULL
};

char *const eq_table[]=
{
"light", "finger_l", "finger_r", "neck_1", "neck_2", "torso", "head",
"legs","feet", "hands", "arms", "shield", "body", "waist", "wrist_l",
"wrist_r","wield", "hold", "float", NULL
};

void do_retribution( CHAR_DATA *ch, char *argument )
{
    char buf[MAX_STRING_LENGTH];

    if ( IS_NPC(ch) )
        return;

    if ( argument[0] != '\0' )
    {
	buf[0] = '\0';
	smash_tilde( argument );

    	if (argument[0] == '-')
    	{
            int len;
            bool found = FALSE;
 
            if (ch->pcdata->smite == NULL || ch->pcdata->smite[0] == '\0')
            {
                send_to_char("No lines left to remove.\n\r",ch);
                return;
            }
	
            strcpy(buf,ch->pcdata->smite);
 
            for (len = strlen(buf); len > 0; len--)
            {
                if (buf[len] == '\r')
                {
                    if (!found)  /* back it up */
                    {
                        if (len > 0)
                            len--;
                        found = TRUE;
                    }
                    else /* found the second one */
                    {
                        buf[len + 1] = '\0';
                        free_string(ch->pcdata->smite);
                        ch->pcdata->smite = str_dup(buf);
                        send_to_char( "Your divine fury takes the form of:\n\r", ch );
                        send_to_char( ch->pcdata->smite ? ch->pcdata->smite : 
			    "(None).\n\r", ch );
                        return;
                    }
                }
            }
            buf[0] = '\0';
            free_string(ch->pcdata->smite);
            ch->pcdata->smite = str_dup(buf);
            send_to_char("Mortals no longer need fear your mark upon them.\n\r",ch);
	    return;
        }
	if ( argument[0] == '+' )
	{
            if ( ch->pcdata->smite != NULL )
                strcat( buf, ch->pcdata->smite );
	    argument++;
	    while ( isspace(*argument) )
		argument++;
	}

        if ( strlen(buf) >= 1024)
	{
            send_to_char( "Your fury is great indeed, too great.  Use less lines.\n\r", ch );
	    return;
	}

	strcat( buf, argument );
	strcat( buf, "\n\r" );
        free_string( ch->pcdata->smite );
        ch->pcdata->smite = str_dup( buf );
    }

    send_to_char( "Your divine fury takes the form of:\n\r", ch );
    send_to_char( ch->pcdata->smite ? ch->pcdata->smite : "(None).\n\r", ch );
    return;
}


void do_smite( CHAR_DATA *ch, char *argument )
{
    char arg1 [MAX_INPUT_LENGTH];  /* Lot of arguments */
    char arg2 [MAX_INPUT_LENGTH];
    char arg3 [MAX_INPUT_LENGTH];
    char arg4 [MAX_INPUT_LENGTH];
    char arg5 [MAX_INPUT_LENGTH];
    char arg6 [MAX_INPUT_LENGTH];
    char buf[MAX_INPUT_LENGTH];
    CHAR_DATA *victim;
    OBJ_DATA *SmittenEQ;
    const int MAX_SMITE_FRACTION = 95;  /* You can change this if you want */
    int hp_percent = 0;
    int mana_percent = 0;
    int move_percent = 0;
    int pos = 0;
    int eq = 0;

    argument = one_argument( argument, arg1 );  /* Combine the arguments */
    argument = one_argument( argument, arg2 );
    argument = one_argument( argument, arg3 );
    argument = one_argument( argument, arg4 );
    argument = one_argument( argument, arg5 );
    argument = one_argument( argument, arg6 );

    if ( IS_NPC(ch) )  /* NPCs may get to be smited, but switch immortals can't */
        return;

    if ( arg1[0] == '\0' )
    {
	send_to_char( "Syntax:\n\r",ch);
        send_to_char( "Smite <victim> <hp> <mana> <move> <position> <equipment>\n\r",ch);
	return;
    }

    if ( ( victim = get_char_world( ch, arg1 ) ) == NULL )
    {
        send_to_char( "They are saved only through their abscence.\n\r",ch);
	return;
    }

    if (!IS_NPC(victim) && victim->level >= get_trust(ch))
    {
        send_to_char("Your reach exceeds your grasp.\n\r",ch);
        return;
    }

    if ( arg2[0] != '\0' )
        hp_percent = atoi( arg2 );
    else
        hp_percent = 50;

    if ( hp_percent > MAX_SMITE_FRACTION || hp_percent < 0 )
    {
        send_to_char("Hp percent must be between 0 and 95.\n\r", ch );
        return;
    }
 
    if ( arg3[0] != '\0' )
        mana_percent = atoi( arg3 );
    else
        mana_percent = 0;

    if ( mana_percent > MAX_SMITE_FRACTION || mana_percent < 0 )
    {
        send_to_char("Mana percent must be between 0 and 95.\n\r", ch );
        return;
    }
    
    if ( arg4[0] != '\0' )
        move_percent = atoi( arg4 );
    else
        move_percent = 0;

    if ( move_percent > MAX_SMITE_FRACTION || move_percent < 0 )
    {
        send_to_char("Move percent must be between 0 and 95.\n\r", ch );
        return;
    }
    
    /* Customize stuff by alignment */

    if (ch->alignment > 300)
    {                                                                     
        act3("Your actions have brought the holy power of $n upon you!",ch,NULL,victim,TO_VICT,POS_DEAD);
        act3("$N has brought the holy power of $n upon themselves!",ch,NULL,victim,TO_NOTVICT,POS_DEAD);                                              
    }
    if (ch->alignment > -301 && ch->alignment < 301)
    {
        act3("Your actions have called the divine fury of $n upon you!",ch,NULL,victim,TO_VICT,POS_DEAD);
        act3("$N has called the divine fury of $n upon themselves!",ch,NULL,victim,TO_NOTVICT,POS_DEAD);
    }
    if (ch->alignment < -300)
    {
        act3("You are struck down by the infernal power of $n!!",ch,NULL,victim,TO_VICT,POS_DEAD);
        act3("The hellspawned, infernal power of $n has struck down $N!!",ch,NULL,victim,TO_NOTVICT,POS_DEAD);
    }

    /* This is where the thing we did in retribution is used */

    if ( ch->pcdata->smite[0] != '\0' )
    {
        send_to_char( ch->pcdata->smite, victim );
    }

    /* If it REALLY hurt */

    if ( hp_percent > 75 && victim->hit > victim->max_hit / 4 )
        send_to_char( "{RThat really did HURT!{x\n\r", victim );

    /* Let's see if equipment needs to be 'blown away' */

    for ( eq = 0; eq_table[eq] != NULL; eq++ )
    {
        if ( !str_prefix( eq_table[eq], arg6 ) )
        {
            if ( ( SmittenEQ = get_eq_char( victim, eq ) ) != NULL )
            {
                sprintf( buf, "$n's %s is blown away!", SmittenEQ->short_descr);
                act( buf, victim, NULL, NULL, TO_ROOM);
                sprintf( buf, "Your %s is blown away!\n\r", SmittenEQ->short_descr);
                send_to_char( buf, victim );

                unequip_char( victim, SmittenEQ );
                obj_from_char( SmittenEQ );
                obj_to_room( SmittenEQ, victim->in_room );
            }
            break;
        }
    }

    /* Let's see what position to put the victim in */

    for ( pos = 0; pos_table[pos] != NULL; pos++ )
    {
        if ( !str_prefix( pos_table[pos], arg5 ) )
        {
            victim->position = pos;                 /* This only works because of the way the pos_table is arranged. */
            if ( victim->position == POS_FIGHTING ) 
                victim->position = POS_STANDING;     /* POS_FIGHTING is bad */

            if ( victim->position < POS_STUNNED )
                victim->position = POS_STUNNED;

            if ( victim->position == POS_STUNNED )
            {
                act( "$n is stunned, but will probably recover.",victim, NULL, NULL, TO_ROOM );
                send_to_char("You are stunned, but will probably recover.\n\r",victim );
            }    

            if ( victim->position == POS_RESTING || victim->position == POS_SITTING )
            {
                act("$n is knocked onto $s butt!", victim, NULL, NULL, TO_ROOM );
                send_to_char("You are knocked onto your butt!\n\r", victim );
            }
            break;
        }
    }

    /* Calculate total hp loss */
    victim->hit -= ( ( victim->hit * hp_percent ) / 100 );
    if ( victim->hit < 1 )
        victim->hit = 1;

    /* Calculate total mana loss */
    victim->mana -= ( ( victim->mana * mana_percent ) / 100 );
    if ( victim->mana < 1 )
       victim->mana = 1;

    /* Calculate total move loss */
    victim->move -= ( ( victim->move * move_percent ) / 100 );
    if ( victim->move < 1 )
        victim->move = 1;

    send_to_char("Your will is done, your power felt.\n\r",ch);
    return;
}


/*Compiled*/

void do_secset(CHAR_DATA *ch, char *argument)    {	CHAR_DATA *victim;
char arg1[MAX_STRING_LENGTH];	char arg2[MAX_STRING_LENGTH];	char
buf[MAX_STRING_LENGTH];	int seclevel;	argument = one_argument(argument,
arg1);	if (arg1[0] == '\0')	{		send_to_char("Set who's
Security?\n\r", ch);		return;	}	if ((victim =
get_char_world(ch, arg1)) == NULL)	{
send_to_char("They're not here.\n\r", ch);		return;	}	if
( IS_NPC( victim ) )    {		send_to_char( "You may change an
NPC's security.\n\r", ch );		return;    }    if ( victim->level
> ch->level )    {    	send_to_char("You may not alter someones who is a
higher level thanyou.\n\r", ch);		return;	}	argument =
one_argument(argument, arg2);	if (arg2[0] == '\0')	{
send_to_char("Set their security to what level?\n\r", ch);
return;	}	seclevel = atoi(arg2);	if( (seclevel <= 0) || (seclevel >
9) )	{		send_to_char("Security range is from 1 to 9.\n\r",
ch);		return;	}	victim->pcdata->security = seclevel;
send_to_char("Changed players security level.\n\r", ch);
sprintf(buf, "%s just raised your security to level %d",
ch->name,seclevel);	send_to_char(buf, victim);	return;}

void do_bounty( CHAR_DATA *ch, char *argument )
{
    char arg1 [MAX_INPUT_LENGTH];
    char arg2 [MAX_INPUT_LENGTH];
    char buf[MAX_STRING_LENGTH];
    CHAR_DATA *victim;
 
    argument = one_argument( argument, arg1 );
    argument = one_argument( argument, arg2 );
 
 
        if ( arg1[0] == '\0' || arg2[0] == '\0' )
        {
             send_to_char( "Place a bounty on who's head?\n\rSyntax:  Bounty <victim> <amount>\n\r", ch );
             return;
        }
 
        if ( ( victim = get_char_world( ch, arg1 ) ) == NULL)
        {
           send_to_char( "They are currently not logged in!", ch );
		return;
        }
 
      if (IS_NPC(victim))
      {
        send_to_char( "You cannot put a bounty on NPCs!", ch );
        return;
      }
 
      if (victim->pcdata->bounty > 0)
      {
        send_to_char( "They already have a bounty on their head.",ch);
        return;
      }
 
      if (victim->level >= 7)
      {
        send_to_char( "You can't put a bounty on an immortal.",ch);
        return;
}
 
        if ( is_number( arg2 ) )
        {
        int amount;
        amount   = atoi(arg2);
        if (ch->pcdata->quest < amount)
        {
                send_to_char( "You don't have that many QPs!", ch );
                return;
        }
        ch->pcdata->quest -= amount;
        victim->pcdata->bounty +=amount;
        sprintf( buf, "You have placed a %d QP bounty on %s.\n\r",
        amount,victim->name );
        send_to_char(buf,ch);
        sprintf(buf, "%s now has a bounty of %d QPs on their head.\n\r", victim->name, amount);
	do_info(ch, buf);
        return;
        }
}
 
 
 
void do_undeny( CHAR_DATA *ch, char *argument )
{
    char arg[MAX_INPUT_LENGTH];
    char buf[MAX_STRING_LENGTH];
        char *oldname;
        CHAR_DATA *victim;
        DESCRIPTOR_DATA *d;
        ROOM_INDEX_DATA *in_room;
 
    sprintf(buf,"%s: Undeny %s",ch->name,argument);
    if (ch->level < NO_WATCH) do_watching(ch,buf);
 
    one_argument( argument, arg );
 
    if ( arg[0] == '\0' )
    {
        send_to_char( "Undeny whom?", ch );
        return;
    }
 
        if ((victim = get_char_world(ch, arg)) != NULL) {
        send_to_char("They are already online.\n\r", ch );
        return;}
 
    if (!char_exists(FALSE,arg))
    {
        send_to_char( "They aren't here.\n\r", ch );
        return;
    }
        oldname = str_dup(ch->name);
d = ch->desc;
        do_autosave(ch,"");
        in_room = ch->in_room;
        extract_char(ch, TRUE);
        d->character = NULL;
        load_char_obj(d, arg);
        ch = d->character;
        ch->next = char_list;
        char_list = ch;
        char_to_room(ch,in_room);
 
    if ( IS_SET(ch->act, PLR_DENY) )
    {
        REMOVE_BIT(ch->act, PLR_DENY);
        send_to_char( "DENY removed.\n\r", ch );
    } else {
        send_to_char("They are not DENIED.\n\r", ch ); }
 
        d = ch->desc;
        do_autosave(ch,"");
        in_room = ch->in_room;
        extract_char(ch, TRUE);
        d->character = NULL;
        load_char_obj(d, oldname);
        ch = d->character;
        ch->next = char_list;
        char_list = ch;
        char_to_room(ch,in_room);
 
    return;
}
 
/*by xkilla*/
void do_addlag(CHAR_DATA *ch, char *argument)
{
        CHAR_DATA *victim;
        char arg1[MAX_STRING_LENGTH];
int x;
 
        argument = one_argument(argument, arg1);
 
        if (arg1[0] == '\0')
        {
                send_to_char("Addlag to who?", ch);
                return;
        }
 
        if ((victim = get_char_world(ch, arg1)) == NULL)
        {
                send_to_char("They're not here.", ch);
                return;
        }
 
 
        if ((x = atoi(argument)) <= 0)
        {
                send_to_char("That makes a LOT of sense, ya lag yourself *DUH*.", ch);
                return;
        }
 
        if (x > 100000)
        {
                send_to_char("There's a limit to cruel and unusual punishment", ch);
                return;
        }
 
        send_to_char("Somebody REALLY dosen't like you", victim);
        WAIT_STATE(victim, x);
        send_to_char("That ought to show that nerdy bitch...", ch);
        return;
}


void do_autotick(CHAR_DATA *ch,char *argument)
{
        if (!IS_SET(ch->xkilla->plr, PLR_AUTOTICK))
        {
        SET_BIT(ch->xkilla->plr, PLR_AUTOTICK);
        send_to_char("#2Autotick message: Enabled.#n", ch);
        }

        else
        {
        REMOVE_BIT(ch->xkilla->plr, PLR_AUTOTICK);
        send_to_char("#2Autotick message: Disabled.#n", ch);
        }

}
