/*Xkilla made this alien class*/
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
 
/*
 * Local functions.
 */


//Autoconsuming in fight.c
void do_autoconsume(CHAR_DATA *ch,char *argument)
{

        if (!IS_CLASS(ch, CLASS_ALIEN))
        {
        send_to_char("Huh?\n\r", ch );
        return;
	}

	if (!IS_SET(ch->xkilla->plr, PLR_AUTOCONSUME))
	{
	SET_BIT(ch->xkilla->plr, PLR_AUTOCONSUME);
	send_to_char("Autoconsuming On.", ch);
	}

	else
	{
	REMOVE_BIT(ch->xkilla->plr, PLR_AUTOCONSUME);
	send_to_char("Autoconsuming Off.", ch);
	}

}



void do_alienpowers(CHAR_DATA *ch,char *argument)
{
        char buf[MAX_STRING_LENGTH];
 
        if (IS_NPC(ch)) return;
 
        if (!IS_CLASS(ch, CLASS_ALIEN))  {
        send_to_char("Huh?\n\r", ch );
        return;}
 
        send_to_char("#2#u////////////#n#CA#clien #RP#rowers#2#u\\\\\\\\\\\\\\\\\\\\\\\\#n#3\n\r", ch );

        if (IS_ALIPOWER( ch, ALI_PYRO))
        send_to_char("#3You have the power Pyrokinesis, which gives a extra attack between rounds..\n\r", ch );
 
        if (IS_ALIPOWER( ch, ALI_SPEED))
        send_to_char("#3You have the power Speed, which gives you super attacks and a little bit more parry and dodge..\n\r", ch );

        if (IS_ALIPOWER( ch, ALI_TOUGH))
        send_to_char("#3You have the power Toughness, which gives you super tough skin..\n\r", ch );

        if (IS_ALIPOWER( ch, ALI_BEAM))
        send_to_char("#3You have the power Beam, which gives allows you to goto players with beam on..\n\r", ch );

        if (IS_ALIPOWER( ch, ALI_SPACEEYES))
        send_to_char("#3You have the power Spaceeyes, which gives you the ability to see anything..\n\r", ch );

        if (IS_ALIPOWER( ch, ALI_BIOMORPH))
        send_to_char("#3You have the power Biomorph, which lets you morph from a human to a #GA#glien#3..\n\r", ch );

        if (IS_ALIPOWER( ch, ALI_PROBE))
        send_to_char("#3You have the power Probe, which allows you to consider anyone..\n\r", ch );

        if (IS_ALIPOWER( ch, ALI_RADAR))
        send_to_char("#3You have the power Radar, which lets you track down your enemies and friends..\n\r", ch );

        send_to_char("\n\r", ch);
 
	sprintf(buf, "#0Generation : %d            #n             \n\r", ch->pcdata->stats[UNI_GEN]);
	send_to_char( buf, ch );
 
        if (IS_SET(ch->special, SPC_PRINCE))
        send_to_char("#2You are a Alien Stalker.\n\r", ch );
 
        sprintf( buf, "#0You have %d #GP#glanet#0 points!.#n\n\r",
        ch->pcdata->stats[ALIEN_PLANET] );
        send_to_char( buf, ch );
 
        send_to_char("\n\r", ch );
 
        return;
}
 

void do_brood( CHAR_DATA *ch, char *argument )
{
    CHAR_DATA *victim;
    char      arg1 [MAX_INPUT_LENGTH];
    char      arg2 [MAX_INPUT_LENGTH];
 
        int i;
 
    argument = one_argument( argument, arg1 );
    argument = one_argument( argument, arg2 );
 
    if ( IS_NPC(ch) ) return;
 
    if ( arg1[0] == '\0' || arg2[0] == '\0' )
    {
        send_to_char( "Syntax: brood <char> <brood>.\n\r", ch );
        return;
    }
 
    if ( ( victim = get_char_world( ch, arg1 ) ) == NULL )
    {
        send_to_char( "That player is not here.\n\r", ch);
        return;
    }
 
    if ( !str_cmp( arg2, ""       ) )
    {
    victim->brood = 0;
    send_to_char("You are now a !\n\r", victim);
    }
    else
    {
    send_to_char( "Syntax: brood <char> <brood>.\n\r", ch );
        return;
    }
    send_to_char("Brood Set.\n\r",ch);
    return;
}

void do_ptoken( CHAR_DATA *ch, char *argument )
{
    char arg1[MAX_INPUT_LENGTH];
    char arg2[MAX_INPUT_LENGTH];
    char buf[MAX_STRING_LENGTH];
    OBJ_INDEX_DATA *pObjIndex;
    OBJ_DATA *obj;
    CHAR_DATA *victim;
    int value;
 
    argument = one_argument( argument, arg1 );
    argument = one_argument( argument, arg2 );

    if (IS_NPC(ch)) return;
 
    if (!IS_CLASS(ch, CLASS_ALIEN))
    {
            send_to_char("Huh?\n\r",ch);
            return;
    }
 
    if ( arg1[0] == '\0' || !is_number( arg1 ) )
    {
        send_to_char("Please specify a value for the planet token.\n\r",ch);
        return;
    }
    else
    {
        value = atoi( arg1 );
        if ( value < 1 || value > 10000 )
        {
            send_to_char( "Planet tokens should have a value between 1 and 10000.\n\r", ch );
            return;
        }
        else if ( value > ch->pcdata->stats[ALIEN_PLANET] && !IS_IMMORTAL(ch) )
        {
            sprintf(buf,"You only have %d planet points left to put into tokens.\n\r",ch->pcdata->stats[ALIEN_PLANET]);
            send_to_char( buf, ch );
            return;
        }
    }
 
    victim = get_char_room( ch, arg2 );
 
    if ( ( pObjIndex = get_obj_index( OBJ_VNUM_PROTOPLASM ) ) == NULL )
    {
        send_to_char( "Error...missing object, please inform Xkilla.\n\r", ch );
        return;
    }
 
    ch->pcdata->stats[ALIEN_PLANET] -= value;
    if (ch->pcdata->stats[ALIEN_PLANET] < 0)
      ch->pcdata->stats[ALIEN_PLANET] = 0;
    obj = create_object( pObjIndex, value );
    obj->value[0] = value;
    obj->level = 1;
    obj->cost = value*1000;
    obj->item_type = ITEM_PTOKEN;
    obj_to_char(obj,ch);
    if (obj->questmaker != NULL) free_string(obj->questmaker);
    obj->questmaker = str_dup(ch->name);
    free_string( obj->name );
    obj->name = str_dup( "planet token" );
    sprintf(buf,"#2a #1%d#2 point p#glanet #Lt#loken#n",value);
    free_string( obj->short_descr );
    obj->short_descr = str_dup( buf );
    sprintf(buf,"#2A #1%d #2point p#glanet #Lt#loken #2lies on the floor.#n",value);
    free_string( obj->description );
    obj->description = str_dup( buf );
    if (victim != NULL && victim != ch)
    {
        act( "You pull $p out of $N's hair .", ch, obj, victim, TO_CHAR );
        act( "$n pulls $p out of $s hair.", ch, obj, victim, TO_NOTVICT );
        act( "$n pulls $p out of $N's hair.", ch, obj, victim, TO_VICT );
    }
    else
    {
        act( "You create $p.", ch, obj, NULL, TO_CHAR );
        act( "$n creates $p.", ch, obj, NULL, TO_ROOM );
    }
    return;
}

void do_aliencreate( CHAR_DATA *ch, char *argument )
{
    OBJ_INDEX_DATA *pObjIndex;
    OBJ_DATA *obj;
    char arg[MAX_INPUT_LENGTH];
    int vnum = 0;
 
    argument = one_argument( argument, arg );
 
    if (IS_NPC(ch)) return;
 
    if (!IS_CLASS(ch, CLASS_ALIEN))
    {
            send_to_char("Huh?\n\r",ch);
            return;
    }
 
    if (arg[0] == '\0')
    {
        send_to_char("Choices:\n\r",ch);
        send_to_char("#3S#oword#7 of the #GA#gliens#n\n\r",ch);
        send_to_char("#3G#orepper#7 of the #GA#gliens#n\n\r",ch); 
        return;
    }
    if      (!str_cmp(arg,"sword"     )) vnum = 10751;
    else if (!str_cmp(arg,"grepper"   )) vnum = 10752;  
    else
    {
        send_to_char("That is an invalid type.\n\r", ch );
        return;
    }
    if ( ch->pcdata->stats[ALIEN_PLANET] < 150000)
    {
        send_to_char("You need 150,000 planet points.",ch);
        return;
    }
    if ( vnum == 0 || (pObjIndex = get_obj_index( vnum )) == NULL)
    {
        send_to_char("Missing object, please inform Xkilla.\n\r",ch);
        return;
    }
    ch->pcdata->stats[ALIEN_PLANET] -= 150000;
    obj = create_object(pObjIndex, 50);
    obj_to_char(obj, ch);
    act("A small UFO drops the $p in your hands.",ch,obj,NULL,TO_CHAR);
    act("A small UFO drops the $p in $n's hands.",ch,obj,NULL,TO_ROOM);
    return;
}

void do_consume( CHAR_DATA *ch, char *argument )
{
    OBJ_DATA *corpse;
    OBJ_DATA *c_next;
    OBJ_DATA *obj;
    OBJ_DATA *obj_next;
	char arg[MAX_INPUT_LENGTH];
	char buf[MAX_INPUT_LENGTH];
	int points;

	one_argument( argument, arg );

    if( !IS_CLASS(ch, CLASS_ALIEN)) return;
    for ( corpse = ch->in_room->contents; corpse != NULL; corpse = c_next )
    {
	c_next = corpse->next_content;
	if ( corpse->item_type != ITEM_CORPSE_NPC && corpse->item_type != ITEM_CORPSE_PC)
	    continue;
	points = number_range( 5, 50 * 10 );
	ch->pcdata->stats[ALIEN_PLANET] += points;
	act( "$n savagely devours a corpse.", ch, NULL, NULL, TO_ROOM );
	sprintf( buf, "You gain %d planet points for consuming a corpse.\n\r", points );
	send_to_char( buf, ch );
	for ( obj = corpse->contains; obj; obj = obj_next )
	{
	    obj_next = obj->next_content;
	    obj_from_obj( obj );
	    obj_to_room( obj, ch->in_room );
	}

	if (corpse != NULL) extract_obj( corpse );
    }
	return;
}


void do_prince( CHAR_DATA *ch, char *argument )
{
    CHAR_DATA *victim;
    char      arg1 [MAX_INPUT_LENGTH];
    argument = one_argument( argument, arg1 );
 
    if ( IS_NPC(ch) ) return;

    if (!IS_CLASS(ch, CLASS_ALIEN))
    {
        send_to_char("Huh?\n\r",ch);
        return;
    }
 
    if ( arg1[0] == '\0' )
    {
        send_to_char( "Syntax is: prince <target>\n\r", ch );
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
 
    if (!IS_CLASS(victim, CLASS_ALIEN))
    {
        send_to_char("They are not alien.\n\r",ch);
        return;
    }

	if (ch->pcdata->stats[UNI_GEN] == 2)
	{
        if (IS_SET(victim->special,SPC_PRINCE))
        {
            send_to_char("You have lost your stalker abilities!\n\r",victim);
            send_to_char("You remove their stalker abilities.\n\r",ch);
            REMOVE_BIT(victim->special, SPC_PRINCE);
        }
        else
        {
            send_to_char("You have been made a stalker!\n\r",victim);
            send_to_char("You make them a stalker.\n\r",ch);
            SET_BIT(victim->special, SPC_PRINCE);
        }
        save_char_obj(victim);
        return;
	}
	else
	{
	send_to_char("You have to be gen 2.", ch);
	}
}


void do_pyrokinesis( CHAR_DATA *ch, char *argument )
{
    char arg[MAX_INPUT_LENGTH];
    CHAR_DATA *victim;
    OBJ_DATA *obj;
 
    one_argument( argument, arg );
 
        if (IS_NPC(ch)) return;
 
     if (!IS_CLASS(ch, CLASS_ALIEN))
     {
       send_to_char("Huh?\n\r",ch);
       return;
     }

     if (!IS_ALIPOWER( ch, ALI_PYRO))
     {
       send_to_char("You do not have the planet Pyrokinesis yet.\n\r",ch);
       return;
     }

    if ( ( victim = get_char_room( ch, arg ) ) == NULL )
    {
        if (ch->fighting == NULL) {
        send_to_char( "They aren't here.\n\r", ch );
        return;}
        else victim = ch->fighting;
    }
 
    if ( victim == ch )
    {
        send_to_char( "How can you Pyrokinesis yourself?\n\r", ch );
        return;
    }
 
    if ( is_safe( ch, victim ) )
      return;

    check_killer( ch, victim );
        if (number_percent() > 10)
        multi_hit( ch, victim, gsn_pyro );
    else
        damage( ch, victim, 0, gsn_pyro );
 
    WAIT_STATE( ch, 8 );
    return;
}


void do_probe( CHAR_DATA *ch, char *argument )
{
    CHAR_DATA *victim;
    OBJ_DATA  *obj;
    char      arg [MAX_INPUT_LENGTH];
    char      buf [MAX_INPUT_LENGTH];

    argument = one_argument( argument, arg );

    if (IS_NPC(ch)) return;

     if (!IS_CLASS(ch, CLASS_ALIEN))
     {
       send_to_char("Huh?\n\r",ch);
       return;
     }
 
     if (!IS_ALIPOWER( ch, ALI_PROBE))
     {
       send_to_char("You do not have the planet Probe yet.\n\r",ch);
       return;
     }

    if ( arg[0] == '\0' )
    {
	send_to_char( "Probe what?\n\r", ch );
	return;
    }

    if ( ( victim = get_char_room( ch, arg ) ) == NULL )
    {
        if ( ( obj = get_obj_carry( ch, arg ) ) == NULL )
	{
	    send_to_char( "Probe what?\n\r", ch );
	    return;
	}
	    ch->pcdata->condition[COND_THIRST] -= number_range(40,50);
	act("$n examines $p intently.",ch,obj,NULL,TO_ROOM);
	spell_identify( skill_lookup( "identify" ), ch->level, ch, obj );
	return;
    }

    act("$n probes $N.",ch,NULL,victim,TO_NOTVICT);
    act("$n probes you.",ch,NULL,victim,TO_VICT);
    if (IS_NPC(victim)) sprintf(buf, "%s is an NPC.\n\r",victim->short_descr);
    else 
    {
	if      (victim->level == 12) sprintf(buf, "%s is an Implementor.\n\r", victim->name);
	else if (victim->level == 11) sprintf(buf, "%s is a High Judge.\n\r", victim->name);
	else if (victim->level == 10) sprintf(buf, "%s is a Judge.\n\r", victim->name);
	else if (victim->level == 9 ) sprintf(buf, "%s is an Enforcer.\n\r", victim->name);
	else if (victim->level == 8 ) sprintf(buf, "%s is a Quest Maker.\n\r", victim->name);
	else if (victim->level == 7 ) sprintf(buf, "%s is a Builder.\n\r", victim->name);
	else if (victim->level >= 3 ) sprintf(buf, "%s is an Avatar.\n\r", victim->name);
	else sprintf(buf, "%s is a Mortal.\n\r", victim->name);
    }
    send_to_char(buf,ch);
    if (!IS_NPC(victim))
    {
	sprintf(buf,"Str:%d, Int:%d, Wis:%d, Dex:%d,
Con:%d.\n\r",get_curr_str(victim),get_curr_int(victim),get_curr_wis(victim),get_curr_dex(victim),get_curr_con(victim));
	send_to_char(buf,ch);
    }
    sprintf(buf,"Hp:%d/%d, Mana:%d/%d,
Move:%d/%d.\n\r",victim->hit,victim->max_hit,victim->mana,victim->max_mana,victim->move,victim->max_move);
    send_to_char(buf,ch);
    if (!IS_NPC(victim)) sprintf(buf,"Hitroll:%d, Damroll:%d,
AC:%d.\n\r",char_hitroll(victim),char_damroll(victim),char_ac(victim));
    else sprintf(buf,"AC:%d.\n\r",char_ac(victim));
    send_to_char(buf,ch);
    if (!IS_NPC(victim))
    {
	sprintf(buf,"Status:%d, ",victim->race);
	send_to_char(buf,ch);
	if (IS_CLASS(victim, CLASS_VAMPIRE))    
	{
	    sprintf(buf,"Blood:%d, ",victim->pcdata->condition[COND_THIRST]);
	    send_to_char(buf,ch);
	}
    }
    sprintf(buf,"Alignment:%d.\n\r",victim->alignment);
    send_to_char(buf,ch);
    if (!IS_NPC(victim) && IS_EXTRA(victim, EXTRA_PREGNANT))
	act("$N is pregnant.",ch,NULL,victim,TO_CHAR);
    if (!IS_NPC(victim) && IS_CLASS(victim, CLASS_VAMPIRE))    
    {
	send_to_char("Disciplines:",ch);
	if (IS_VAMPAFF(victim, VAM_PROTEAN)) send_to_char(" Protean",ch);
	if (IS_VAMPAFF(victim, VAM_VICISSITUDE)) send_to_char(" vicissitude",ch);
	if (IS_VAMPAFF(victim, VAM_CELERITY)) send_to_char(" Celerity",ch);
	if (IS_VAMPAFF(victim, VAM_FORTITUDE)) send_to_char(" Fortitude",ch);
	if (IS_VAMPAFF(victim, VAM_POTENCE)) send_to_char(" Potence",ch);
	if (IS_VAMPAFF(victim, VAM_OBFUSCATE)) send_to_char(" Obfuscate",ch);
	if (IS_VAMPAFF(victim, VAM_OBTENEBRATION)) send_to_char(" Obtenebration",ch);
	if (IS_VAMPAFF(victim, VAM_SERPENTIS)) send_to_char(" Serpentis",ch);
	if (IS_VAMPAFF(victim, VAM_AUSPEX)) send_to_char(" Auspex",ch);
	if (IS_VAMPAFF(victim, VAM_DOMINATE)) send_to_char(" Dominate",ch);
	if (IS_VAMPAFF(victim, VAM_PRESENCE)) send_to_char(" Presence",ch);
	send_to_char(".\n\r",ch);
    }
    return;
}


void do_radar( CHAR_DATA *ch, char *argument )
{
    CHAR_DATA *victim;
    ROOM_INDEX_DATA *chroom;
    ROOM_INDEX_DATA *victimroom;
    char      arg [MAX_INPUT_LENGTH];

    argument = one_argument( argument, arg );

    if (IS_NPC(ch)) return;

    if (!IS_CLASS(ch, CLASS_ALIEN))
     {
       send_to_char("Huh?\n\r",ch);
       return;
     }
 
     if (!IS_ALIPOWER( ch, ALI_RADAR))
     {
       send_to_char("You do not have the planet Radar yet.\n\r",ch);
       return;
     }

    if ( arg[0] == '\0' )
    {
	send_to_char( "Use radar on whom?\n\r", ch );
	return;
    }

    if ( ( victim = get_char_world( ch, arg ) ) == NULL )
    {
	send_to_char( "They aren't here.\n\r", ch );
	return;
    }

    chroom = ch->in_room;
    victimroom = victim->in_room;

    char_from_room(ch);
    char_to_room(ch,victimroom);
    if (IS_AFFECTED(ch, AFF_SHADOWPLANE) && (!IS_AFFECTED(victim,
AFF_SHADOWPLANE)))
    {
	REMOVE_BIT(ch->affected_by, AFF_SHADOWPLANE);
	do_look(ch,"auto");
	SET_BIT(ch->affected_by, AFF_SHADOWPLANE);
    }
    else if (!IS_AFFECTED(ch, AFF_SHADOWPLANE) && (IS_AFFECTED(victim, AFF_SHADOWPLANE)))
    {
	SET_BIT(ch->affected_by, AFF_SHADOWPLANE);
	do_look(ch,"auto");
	REMOVE_BIT(ch->affected_by, AFF_SHADOWPLANE);
    }
    else
	do_look(ch,"auto");
    char_from_room(ch);
    char_to_room(ch,chroom);
    return;
}


void do_abduct( CHAR_DATA *ch, char *argument )
{
    char      arg [MAX_INPUT_LENGTH];
    argument = one_argument( argument, arg );
 
    if (IS_NPC(ch)) return;

    if (!IS_IMMUNE(ch, IMM_ALIEN))
    {
        send_to_char("You will now allow aliens to abduct you.\n\r",ch);
        SET_BIT(ch->immune, IMM_ALIEN);
        return;
 
    }
    send_to_char("You will no longer allow aliens to abduct you.\n\r",ch);
    REMOVE_BIT(ch->immune, IMM_ALIEN);
    return;
}

void do_planet( CHAR_DATA *ch, char *argument )
{
    CHAR_DATA *victim;
    char      arg1 [MAX_INPUT_LENGTH];
    char      arg2 [MAX_INPUT_LENGTH];
    int       planet = 0;
    int       cost = 0;

    smash_tilde(argument);
    argument = one_argument( argument, arg1 );
    argument = one_argument( argument, arg2 );

    if (IS_NPC(ch)) return;

    if (!IS_CLASS(ch, CLASS_ALIEN))
    {
	    send_to_char("Huh?\n\r",ch);
	    return;
    }

    if ( arg1[0] == '\0' || arg2[0] == '\0' )
    {
	send_to_char( "#u#2Syntax: Planet <person> <planet>              #n\n\r", ch );
	send_to_char( "#u#1| Toughness     [10000] | Speed       [15000] |#n\n\r", ch );
        send_to_char( "#u#1| Beam          [17500] | Probe       [20000] |#n\n\r", ch );        
        send_to_char( "#u#1| Radar         [25000] | Pyrokinesis [22500] |#n\n\r", ch );        
	send_to_char( "#u#1| Biomorph      [40000] | SpaceEyes   [20000] |#n\n\r", ch );
	return;
    }

    if ( ( victim = get_char_world( ch, arg1 ) ) == NULL )
    {
	send_to_char( "Nobody by that name.\n\r", ch );
	return;
    }
	if (str_cmp(victim->clan,ch->clan) && ch->pcdata->stats[UNI_GEN] >1) {
		send_to_char("Only on your clan!.\n\r", ch );
		return;}

    if ( IS_NPC(victim) )
    {
	send_to_char( "Not on NPC's.\n\r", ch );
	return;
    }

    if ( victim->level != LEVEL_AVATAR)
    {
	send_to_char( "Only on an avatar.\n\r", ch );
	return;
    }

    if ( victim->class != CLASS_ALIEN)
    {
	send_to_char( "Only on Aliens.\n\r", ch);
	return;
    }

    if (!str_cmp(arg2,"toughness")) 
	{planet = ALI_TOUGH; cost = 10000;}
    else if (!str_cmp(arg2,"speed"))
	{planet = ALI_SPEED; cost= 15000;}
    else if (!str_cmp(arg2,"beam"))
        {planet = ALI_BEAM; cost= 17500;}
    else if (!str_cmp(arg2,"probe"))
        {planet = ALI_PROBE; cost= 20000;}
    else if (!str_cmp(arg2,"radar"))
        {planet = ALI_RADAR; cost= 25000;}
    else if (!str_cmp(arg2,"pyrokinesis"))
	{planet = ALI_PYRO; cost= 22500;}
    else if (!str_cmp(arg2,"biomorph"))
        {planet = ALI_BIOMORPH; cost= 40000;}
    else if (!str_cmp(arg2, "spaceeyes"))
        {planet = ALI_SPACEEYES; cost= 20000;}
    else
    {
	send_to_char( "#u#2Please select a power from:                   #n\n\r",ch);
        send_to_char( "#u#1| Toughness     [10000] | Speed       [15000] |#n\n\r", ch );
        send_to_char( "#u#1| Beam          [17500] | Probe       [20000] |#n\n\r", ch );
        send_to_char( "#u#1| Radar         [25000] | Pyrokinesis [22500] |#n\n\r", ch );
        send_to_char( "#u#1| Biomorph      [40000] | SpaceEyes   [20000] |#n\n\r", ch );
	return;
    }
     if (IS_ALIPOWER(victim, planet))
    {
	send_to_char("They have already got that planet.\n\r",ch);
	return;
    }
    if (ch->pcdata->stats[ALIEN_PLANET] < cost) 
    {
	send_to_char("You have to little power to give that planet.\n\r",ch);
	return;
    }
 
    SET_BIT(victim->xkilla->aliens, planet);
    ch->pcdata->stats[ALIEN_PLANET] -= cost;
    if (victim != ch) send_to_char("You have been given a planet power from your leader!\n\r",victim);
    send_to_char("Ok.\n\r",ch);
    if (victim != ch) save_char_obj(ch);
    save_char_obj(victim);
    return; 
}


void do_aclass( CHAR_DATA *ch, char *argument )
{
    char      buf [MAX_INPUT_LENGTH];
    CHAR_DATA *victim;
    char      arg [MAX_INPUT_LENGTH];

    argument = one_argument( argument, arg );

    if (IS_NPC(ch)) return;

    if (!IS_CLASS(ch, CLASS_ALIEN) || ch->pcdata->stats[UNI_GEN] > 3) 
    {
	send_to_char("Huh?\n\r",ch);
	return;
    }

    if ( arg[0] == '\0' )
    {
	send_to_char( "Class whom Alien?\n\r", ch );
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
	send_to_char("Not on yourself.\n\r", ch );
	return;
    }

        if (victim->class != 0) {
        send_to_char("They already have a class.\n\r", ch );
        return;}

    if ( victim->level != LEVEL_AVATAR && !IS_IMMORTAL(victim) )
    {
	send_to_char( "Only on avatars.\n\r", ch );
	return;
    }

    if (!IS_IMMUNE(victim,IMM_ALIEN))
    {
	send_to_char( "Not on an unwilling person.\n\r", ch);
	return;
    }

    if (ch->exp < 10000)
    {
	send_to_char("You cannot afford the 10,000 exp.\n\r",ch);
	return;
    }

    ch->exp = ch->exp - 10000;
    act("You make $N a alien!", ch, NULL, victim, TO_CHAR);
    act("$n makes $N a alien!", ch, NULL, victim, TO_NOTVICT);
    act("$n makes you a alien!", ch, NULL, victim, TO_VICT);
    victim->class=0;
    victim->class=CLASS_ALIEN;
    victim->special=0;

    if (IS_CLASS(victim, CLASS_VAMPIRE)) do_mortalvamp(victim,"");
    REMOVE_BIT(victim->act, PLR_HOLYLIGHT);
    REMOVE_BIT(victim->act, PLR_WIZINVIS);
    REMOVE_BIT(victim->special, SPC_SIRE);
    REMOVE_BIT(victim->special, SPC_ANARCH);
    victim->pcdata->stats[UNI_RAGE] = 0;
    victim->pcdata->stats[UNI_GEN] = ch->pcdata->stats[UNI_GEN] + 1;
	victim->special = 0;
    free_string(victim->morph);
    victim->morph=str_dup("");
                free_string(victim->clan);
            victim->clan=str_dup(ch->clan);

    free_string(victim->lord);
    if (ch->pcdata->stats[UNI_GEN] == 1)
        victim->lord=str_dup(ch->name);
    else
    {
        sprintf(buf,"%s %s",ch->lord,ch->name);
        victim->lord=str_dup(buf);
    }
 
    save_char_obj(ch);
    save_char_obj(victim);
    return;
}

void do_aliens( CHAR_DATA *ch, char *argument )
{
    char buf[MAX_STRING_LENGTH];
    char arg[MAX_INPUT_LENGTH];
    CHAR_DATA *gch;

    one_argument( argument, arg );

    if (IS_NPC(ch)) return;
    if (!IS_CLASS(ch, CLASS_ALIEN))
    {
	send_to_char("Huh?\n\r",ch);
	return;
    }

    sprintf( buf, "The aliens:\n\r" );
    send_to_char( buf, ch );
    send_to_char("#2[      Name      ] [ Hits ] [ Mana ] [ Move ] [  Exp  ] [   Power   ]#n\n\r", ch );
    for ( gch = char_list; gch != NULL; gch = gch->next )
    {
        if ( IS_NPC(gch) ) continue;
        if ( !IS_CLASS(gch, CLASS_ALIEN))
            continue;
        {
            sprintf( buf,
            "#0[%-16s] [%-6d] [%-6d] [%-6d] [%7d] [ %-9d ]#n\n\r",
                capitalize( gch->name ),
                gch->hit,gch->mana,gch->move,
                gch->exp, gch->pcdata->stats[ALIEN_PLANET]);
                send_to_char( buf, ch );
        }
    }
    return;
}

void do_beam(CHAR_DATA *ch, char *argument)
{
    CHAR_DATA *victim;
    char       arg [MAX_INPUT_LENGTH];

    one_argument( argument, arg );

    if (IS_NPC(ch)) return;


     if (!IS_CLASS(ch, CLASS_ALIEN))
     {
       send_to_char("Huh?\n\r",ch);
       return;
     }
 
     if (!IS_ALIPOWER( ch, ALI_BEAM))
     {
       send_to_char("You do not have the planet Beam yet.\n\r",ch);
       return;
     }

    if ( arg[0] == '\0')
    {
        send_to_char( "Send a beam to who?\n\r", ch );
        return;
    }
    
    if ( (victim = get_char_world( ch, arg ) ) == NULL )
    {
    send_to_char("They arent here.\n\r",ch);
    return;
}
   if ( (victim == ch))
    {
        send_to_char( "Not on your self.\n\r", ch );
        return;
    }
    if ( (victim->in_room == NULL))
    {
        send_to_char( "They are in no room.\n\r", ch );
        return;
    }


    if (!IS_SET(victim->immune, IMM_ALIEN)) 
    {
        send_to_char( "They don't want you to abduct them.\n\r", ch );
        return;
    }

    if ( (victim->in_room->vnum == ch->in_room->vnum))
    {
        send_to_char( "They are already here.\n\r", ch );
        return;
    }

        do_say(ch, "Beaming\a\a. \a\a. \a\a. \a\a. \a\a. \a\a. \a\a. \a\a.");  
	do_say(ch, "Done. . . . . . . .");  
	send_to_char("You enter the beam.\n\r",ch);
        char_from_room(ch);
        char_to_room(ch, get_room_index(victim->in_room->vnum));
        do_look(ch,"auto");
        WAIT_STATE( ch, 16 );
        act( "You float down infront $N in a beam of red light.", ch, NULL, victim, TO_CHAR);
    act( "$n floats down infront of you in a beam of red light.", ch, NULL, victim, TO_VICT);
    act( "$n floats down infront of $N in a beam of red light.", ch, NULL, victim, TO_NOTVICT);
     return;
}


void do_biomorph( CHAR_DATA *ch, char *argument )
{
    char buf [MAX_STRING_LENGTH];
 
    if (IS_NPC(ch)) return;
 
    if (!IS_CLASS(ch, CLASS_ALIEN))
    {
        send_to_char("Huh?\n\r",ch);
        return;
    }
 
    if (!IS_ALIPOWER( ch, ALI_BIOMORPH))
    {
        send_to_char("You do not have the planet Biomorph.\n\r",ch);
        return;
    }
        if (ch->mounted == IS_RIDING) do_dismount(ch,"");
 
        if ( IS_SET(ch->polyaff, POLY_BIOMORPH) )
    {
        act( "You change back into human form.", ch, NULL, NULL, TO_CHAR );
        act( "$n changes back into human form.", ch, NULL, NULL, TO_ROOM );
        REMOVE_BIT(ch->affected_by, AFF_POLYMORPH);
        REMOVE_BIT(ch->polyaff, POLY_BIOMORPH);
        REMOVE_BIT(ch->pcdata->stats[UNI_AFF], VAM_CHANGED);
        clear_stats(ch);
        free_string( ch->morph );
        ch->morph = str_dup( "" );
       return;
 }
  else if ( !IS_SET(ch->polyaff, POLY_ANGELFORM) )
    {
        act( "You are struck by lightning you transform into a alien.", ch, NULL, NULL, TO_CHAR );
        act( "$n is struck by lightning and turns into a alien.", ch, NULL, NULL, TO_ROOM );
        SET_BIT(ch->polyaff, POLY_BIOMORPH);
        SET_BIT(ch->affected_by, AFF_POLYMORPH);
        SET_BIT(ch->pcdata->stats[UNI_AFF], VAM_CHANGED);
        sprintf(buf, "#3%s #7the #GA#glien#n", ch->name);
        free_string( ch->morph );
        ch->morph = str_dup( buf );
      ch->damroll = ch->damroll + 200;
      ch->hitroll = ch->hitroll + 200;
    return;
    }
    else
        send_to_char( "BIOMORPH: The Power to show your true self.\n\r", ch );
    return;
}


void do_spaceeyes( CHAR_DATA *ch, char *argument)
{
     if ( IS_NPC(ch))
         return;

         if ( !IS_CLASS(ch, CLASS_ALIEN) )
         {
              send_to_char("Huh?\n\r",ch );
              return;
         }

         if (!IS_ALIPOWER( ch, ALI_SPACEEYES))
         {
                 send_to_char("You don't have planet SpaceEyes!\n\r",ch );
                 return;
         }

    if ( IS_SET(ch->act, PLR_HOLYLIGHT))
    {
        REMOVE_BIT(ch->act, PLR_HOLYLIGHT);
        send_to_char("Your eyes degrade back to regular vision.\n\r",ch );
    }
    else
    {
        send_to_char("Your eyes begin to see everything.\n\r",ch );
        SET_BIT(ch->act, PLR_HOLYLIGHT);
    }
    return;
}
