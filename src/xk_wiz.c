/***************************************************
*						   *
*		Coded by Xkilla                    *
*		         			   *
*						   *
*						   *
*						   *
*						   *
*						   *
*						   *
*						   *
****************************************************/


#include "include.h"


void    do_rand_typo    args( ( CHAR_DATA *ch ) );


#define MAX_QUOTES 5
/*Fixed Generation*/
void do_generation( CHAR_DATA *ch, char *argument )
{
    CHAR_DATA *victim;
    int gen;
    char      arg1 [MAX_INPUT_LENGTH];
    char      arg2 [MAX_INPUT_LENGTH];
    char      buf  [MIL];
    argument = one_argument( argument, arg1 );
    argument = one_argument( argument, arg2 );
 
    if ( IS_NPC(ch) ) return;
 
    if ( arg1[0] == '\0' || arg2[0] == '\0' )
    {
        send_to_char( "Syntax: generation <char> <generation>.\n\r", ch );
    send_to_char("Generation 1 is a Master <Class> and 2 is clan leader.\n\r", ch);
        return;
    }
 
    if ( ( victim = get_char_world( ch, arg1 ) ) == NULL )
    {
        send_to_char( "That player is not here.\n\r", ch);
        return;
    }
 
    gen = is_number( arg2 ) ? atoi( arg2 ) : -1;
    if (gen <1 || gen >7)
    {
        send_to_char("Invalid Generation.\n\r",ch);
        return;
    }
    else
    {
        victim->pcdata->stats[UNI_GEN] = gen;
        sprintf(buf,"You are now generation %d.\n\r",gen);
        send_to_char(buf,victim);
    }
    return;
    } 
/* Newclass Command */
void do_newclass( CHAR_DATA *ch, char *argument )
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
	send_to_char( "Syntax: newclass <char> <class>.\n\r", ch );
	send_to_char("     New Classes:\n\r", ch );
    send_to_char("None, ", ch);
    send_to_char("Alien, ", ch);
    send_to_char("Ninja, ", ch);
    send_to_char("Highlander, ", ch);
    send_to_char("Drow ", ch);
	return;
    }
    
    if ( ( victim = get_char_world( ch, arg1 ) ) == NULL )
    {
	send_to_char( "That player is not here.\n\r", ch);
	return;
    }



         if ( !str_cmp( arg2, "none"       ) ) 
    {
    victim->class = 0;
    if (!IS_IMMORTAL(ch))
    {
	victim->trust = 0;
	victim->level = 2;
    }
    send_to_char("You are classless now!\n\r", victim);
    }
    else if ( !str_cmp( arg2, "alien"	))
    {
    if (!IS_IMMORTAL(ch))
    {
        victim->trust = 0;
        victim->level = 3;
    }
	victim->class = CLASS_ALIEN;
	send_to_char("You are now a alien!\n\r", victim);
    }
    else if ( !str_cmp( arg2, "drow"       ) ) 
    {
    if (!IS_IMMORTAL(ch))
    {
        victim->trust = 0;
        victim->level = 3;
    }
    victim->class = CLASS_DROWNEW;
    send_to_char("You are now a drow!\n\r", victim);
    }
    else if ( !str_cmp( arg2, "highlander"       ) )
    {
    if (!IS_IMMORTAL(ch))
    {
        victim->trust = 0;
        victim->level = 3;
    }
    victim->class = CLASS_HIGHLANDER;
    send_to_char("You are now a highlander!\n\r", victim);
    }
    else if ( !str_cmp( arg2, "ninja"       ) )
    {
    if (!IS_IMMORTAL(ch))
    {
        victim->trust = 0;
        victim->level = 3;
    }
    victim->class = CLASS_NINJA;
    send_to_char("You are now a ninja!\n\r", victim);
    }
    else
    {
    send_to_char( "Syntax: newclass <char> <class>.\n\r", ch );
    send_to_char("     New Classes:\n\r", ch );
    send_to_char("None, ", ch);
    send_to_char("Alien, ", ch);
    send_to_char("Ninja, ", ch);
    send_to_char("Highlander, ", ch);
    send_to_char("Drow", ch);
	return;
    }
    send_to_char("Class Set.\n\r",ch);
    return;
}




/* Snippet by Xkilla */
/* New Score */
/* Important things to remember
* 
*65 characters 
*coded by Xkilla
*/

void do_newscore( CHAR_DATA *ch, char *argument )
{
    char buf[MAX_STRING_LENGTH];
    char xkilla1[MAX_STRING_LENGTH];
    char xkilla2[MAX_STRING_LENGTH];
    int a_c = char_ac(ch);
    if ( IS_NPC(ch) ) return;
send_to_char("#6_________________________________________________________________#n\n\r \n\r", ch);
 
 
        sprintf( buf, "#1Your name is %s , #2and you are trusted at level %d.    #n", ch->name, get_trust( ch ) );
        send_to_char( buf, ch );

send_to_char("\n\r#6-----------------------------------------------------------------#n\n\r \n\r", ch);

sprintf( buf,
        "#4%d/%d hp#2  %d/%d mana#3  %d/%d movement#7  %d primal#n\n\r",
        ch->hit,  ch->max_hit,
        ch->mana, ch->max_mana,
        ch->move, ch->max_move,
        ch->practice );
    send_to_char( buf, ch );


send_to_char("#6_________________________________________________________________#n\n\r \n\r", ch);

sprintf( buf,
"#0Str: %d  Int: %d  Wis: %d  Dex: %d  Con: %d.#n\n\r",
        get_curr_str(ch),
        get_curr_int(ch),
        get_curr_wis(ch),
        get_curr_dex(ch),
        get_curr_con(ch) );
    send_to_char( buf, ch );
if ( ch->level >= 0 )
    {
        sprintf( buf, "#2Alignment: %d.  \n\r", ch->alignment );
        send_to_char( buf, ch );
    }


send_to_char("#6_________________________________________________________________#n\n\r \n\r", ch);
 
sprintf( buf, "#1Hitroll: %d. #2 Damroll: %d. #3 Damcap: %d. #4   Ac: %d.#n \n\r ",
char_hitroll(ch), char_damroll(ch), ch->damcap[0], a_c );
    send_to_char( buf, ch );

 
send_to_char("#6_________________________________________________________________#n\n\r \n\r", ch);

if ( !IS_NPC(ch) )
    {
        if      (ch->pkill  == 0) sprintf(xkilla1,"0");
        else if (ch->pkill  == 1) sprintf(xkilla1,"%d",ch->pkill);
        else                      sprintf(xkilla1,"%d",ch->pkill);
        if      (ch->pdeath == 0) sprintf(xkilla2,"0");
        else if (ch->pdeath == 1) sprintf(xkilla2,"%d",ch->pdeath);
        else                      sprintf(xkilla2,"%d",ch->pdeath);
        sprintf( buf, "#2Pkills: %s Pdeaths: %s ", xkilla1, xkilla2);
        send_to_char( buf, ch );
        if      (ch->mkill  == 0) sprintf(xkilla1,"0");
        else if (ch->mkill  == 1) sprintf(xkilla1,"%d",ch->mkill);
        else                      sprintf(xkilla1,"%d",ch->mkill);
        if      (ch->mdeath == 0) sprintf(xkilla2,"0");
        else if (ch->mdeath == 1) sprintf(xkilla2,"%d",ch->mdeath);
        else                      sprintf(xkilla2,"%d",ch->mdeath);
        sprintf( buf, "#2Mkills: %s Mdeaths: %s\n\r", xkilla1,
xkilla2);
        send_to_char( buf, ch );
    }


if ( !IS_NPC(ch) && ch->level >= 0 )
    {
        sprintf( buf, "#1Status: %d Hours Total: %d #n\n\r ", ch->race,
(get_age(ch) - 17) * 2 );
        send_to_char( buf, ch );
    }

send_to_char("#6_________________________________________________________________#n\n\r \n\r", ch);


sprintf( buf, "#4Total Quest Points: %d Quests Completed: %d QPs:  %d \n\rExp: %d#n \n\r", 
ch->pcdata->score[SCORE_QUEST] , ch->pcdata->score[SCORE_NUM_QUEST] , ch->pcdata->quest, ch->exp);
    send_to_char( buf, ch );

    if (!IS_NPC(ch) && IS_CLASS(ch, CLASS_ALIEN)) {
        sprintf( buf, "#2You have %d planet points!#n\n\r",
        ch->pcdata->stats[ALIEN_PLANET] );
        send_to_char( buf, ch ); }
    else if (!IS_NPC(ch) && IS_CLASS(ch, CLASS_DROWNEW)) {
        sprintf( buf, "#2Your drow skill is at %d!#n\n\r",
        ch->xkilla->dskills );
        send_to_char( buf, ch ); }

send_to_char("#6_________________________________________________________________#n\n\r \n\r", ch);


 
}


/*
void do_autostance(CHAR_DATA *ch, char *argument ) {
 
        char    arg     [MAX_INPUT_LENGTH];
 
        argument = one_argument(argument,arg);
 
        if (IS_NPC(ch)) return;
 

        if (!str_cmp(arg,"none")) {
        send_to_char("You no longer autostance.\n\r", ch );
        ch->pcdata->autostance = STANCE_NONE;}
        else if (!str_cmp(arg, "crane")) {
        send_to_char("You now autostance into the crane stance.\n\r",ch );
        ch->pcdata->autostance = STANCE_CRANE;}
        else if (!str_cmp(arg, "crab")) {
        send_to_char("You now autostance into the crab stance.\n\r", ch );
        ch->pcdata->autostance = STANCE_CRAB;}
        else if (!str_cmp(arg, "bull")) {
        send_to_char("You now autostance into the bull stance.\n\r", ch );
ch->pcdata->autostance = STANCE_BULL;}
        else if (!str_cmp(arg, "viper")) {
        send_to_char("You now autostance into the viper stance.\n\r", ch
);
        ch->pcdata->autostance = STANCE_VIPER;}
        else if (!str_cmp(arg, "mongoose")) {
        send_to_char("You now autostance into the mongoose stance.\n\r",
ch);
        ch->pcdata->autostance = STANCE_MONGOOSE;}
        else if (!str_cmp(arg, "mantis")
        && ch->stance[STANCE_CRANE] >= 200
        && ch->stance[STANCE_VIPER] >= 200) {
        send_to_char("You now autostance into the mantis stance.\n\r",
ch);
        ch->pcdata->autostance = STANCE_MANTIS;}
        else if (!str_cmp(arg, "monkey")
        && ch->stance[STANCE_CRANE] >= 200
        && ch->stance[STANCE_MONGOOSE] >= 200) {
        send_to_char("You now autostance into the monkey stance.\n\r",
ch);
ch->pcdata->autostance = STANCE_MONKEY;}
        else if (!str_cmp(arg, "swallow")
        && ch->stance[STANCE_CRAB] >= 200
        && ch->stance[STANCE_MONGOOSE] >= 200) {
        send_to_char("You now autostance into the swallow stance.\n\r",
ch);
        ch->pcdata->autostance = STANCE_SWALLOW;}
        else if (!str_cmp(arg, "tiger")
        && ch->stance[STANCE_BULL] >= 200
        && ch->stance[STANCE_VIPER] >= 200) {
        send_to_char("You now autostance into the tiger stance.\n\r", ch);
        ch->pcdata->autostance = STANCE_TIGER;}
        else if (!str_cmp(arg, "dragon")
        && ch->stance[STANCE_CRAB] >= 200
        && ch->stance[STANCE_BULL] >= 200) {
        send_to_char("You now autostance into the dragon stance.\n\r",
ch);
        ch->pcdata->autostance = STANCE_DRAGON;}
        else send_to_char("You can't set your autostance to that!\n\r",ch);
}
 
void autodrop(CHAR_DATA *ch) {
 
        int st;
        char buf [MAX_INPUT_LENGTH];
        char buf2 [MAX_INPUT_LENGTH];
        char stancename [10];
 
        if (IS_NPC(ch)) return;
 
        st = ch->pcdata->autostance;
        if (st == STANCE_VIPER) sprintf(stancename,"viper");
        else if (st == STANCE_CRANE) sprintf(stancename,"crane");
        else if (st == STANCE_CRAB) sprintf(stancename,"crab");
        else if (st == STANCE_MONGOOSE) sprintf(stancename,"mongoose");
        else if (st == STANCE_BULL) sprintf(stancename,"bull");
        else if (st == STANCE_MANTIS) sprintf(stancename,"mantis");
        else if (st == STANCE_DRAGON) sprintf(stancename,"dragon");
        else if (st == STANCE_TIGER) sprintf(stancename,"tiger");
        else if (st == STANCE_MONKEY) sprintf(stancename,"monkey");
        else if (st == STANCE_SWALLOW) sprintf(stancename,"swallow");
        else return;
 
        if (ch->stance[0] < 1) {
        ch->pcdata->autostance = st;
 
        sprintf(buf, "You autodrop into the %s stance.", stancename);
        act(buf, ch, NULL, NULL, TO_CHAR);
        sprintf(buf2, "$n autodrops into the %s stance.", stancename);
        act(buf2, ch, NULL, NULL, TO_ROOM);
}
}
*/




void do_level( CHAR_DATA *ch, char *argument )
{
    char arg       [MAX_INPUT_LENGTH];
    char buf[MAX_STRING_LENGTH];
    char skill  [20];
    one_argument( argument, arg );
    if (IS_NPC(ch)) return;
 
 
send_to_char(
 
"#7------------------------------------------------------------------------------\n\r",ch);
send_to_char(
 " #6                         -= Skill =-           \n\r",ch);
send_to_char(
 
"#7------------------------------------------------------------------------------\n\r",ch);
send_to_char(
 "   #6                         Weapon\n\r",ch);
sprintf( buf,
"#1Unarm: %-3d Slice: %-3d Stab: %-3d Slash: %-3d Whip  : %-3d Claw: %-3d Blast: %-3d\n\r",
 
ch->wpn[0],ch->wpn[1],ch->wpn[2],ch->wpn[3],ch->wpn[4],ch->wpn[5],ch->wpn[6]);
send_to_char(buf,ch);
sprintf( buf,
"#1Pound: %-3d Crush: %-3d Grep: %-3d  Bite: %-3d Pierce: %-3d Suck: %-3d\n\r",
ch->wpn[7],ch->wpn[8],ch->wpn[9],ch->wpn[10],
ch->wpn[11],ch->wpn[12]);
send_to_char(buf,ch);
send_to_char(
 
"#7------------------------------------------------------------------------------\n\r",ch);
send_to_char(
 "    #6                  Basic Stances\n\r",ch);
sprintf( buf,
"#0Viper : %-3d Crane: %-3d Crab  : %-3d Mongoose: %-3d Bull: %-3d\n\r",
ch->stance[1],ch->stance[2],ch->stance[3],ch->stance[4],ch->stance[5]);
send_to_char(buf,ch);
send_to_char(
 
"#7------------------------------------------------------------------------------\n\r",ch);
send_to_char(
"       #6            Advanced Stances\n\r",ch);
sprintf( buf,
"#2Mantis: %-3d Dragon: %-3d Tiger: %-3d Monkey: %-3d Swallow : %-3d\n\r",
ch->stance[6],ch->stance[7],ch->stance[8],ch->stance[9],ch->stance[10]);
send_to_char(buf,ch);
send_to_char(
 
"#7------------------------------------------------------------------------------\n\r",ch);
send_to_char(
 "        #6                    Magic\n\r",ch);
sprintf( buf,
"#5Purple: %-3d  #1Red: %-3d #4 Blue: %-3d #2 Green: %-3d  #3Yellow: %-3d\n\r",ch->spl[0],
ch->spl[1],ch->spl[2],ch->spl[3],ch->spl[4]);
send_to_char(buf,ch);
send_to_char(
 
"#7------------------------------------------------------------------------------#n\n\r",ch);
        if ( IS_SET(ch->special, SPC_PRINCE) )
          send_to_char("#0You are a prince!        #n             \n\r", ch);
 
    sprintf(skill, "#0Generation : %d            #n             \n\r", ch->pcdata->stats[UNI_GEN]);
    send_to_char( skill, ch );
    sprintf(skill, "#0Recall Room : %d         #n             \n\r",ch->home);
    send_to_char( skill, ch );
    if ( IS_CLASS(ch, CLASS_NINJA) )
     send_to_char("#0You are a ninja!        #n               \n\r", ch);
    else if ( IS_CLASS(ch, CLASS_DROWNEW) )
     send_to_char("#0You are a drow!        #n               \n\r", ch);
    else if ( IS_CLASS(ch, CLASS_DEMON) )
     send_to_char("#0You are a demon!        #n               \n\r", ch);
    else if ( IS_CLASS(ch, CLASS_MAGE) )
     send_to_char("#0You are a mage!       #n                 \n\r", ch);
     else if ( IS_CLASS(ch, CLASS_WEREWOLF) )
     send_to_char("#0You are a werewolf! #n                   \n\r", ch);
     else if ( IS_CLASS(ch, CLASS_VAMPIRE) )
     send_to_char("#0You are a vampire!         #n            \n\r", ch);
 
 
return;
}



void do_newbiepack( CHAR_DATA *ch, char *argument )
{
 
        char buf[MAX_STRING_LENGTH];
 
        if (IS_SET(ch->newbits,NEWBIE_PACK))
        {
        send_to_char("Due to abuse you now may only create 1 newbie pack\n\r",ch);
        return;
        }

        else if (ch->level >= 4)
        {
        send_to_char("You must be a mortal or avatar to create a newbie pack!\n\r",ch);
        return;
}
 
        else if (ch->level == 1)
        {
        ch->level = 7;
        ch->trust =  7;
        do_oload(ch,"3032");
        do_oload(ch,"30333");
        do_oload(ch,"30334");
        do_oload(ch,"30335");
        do_oload(ch,"30336");
        do_oload(ch,"30337");
        do_oload(ch,"30338");
        do_oload(ch,"30339");
        do_oload(ch,"30339");
        do_oload(ch,"30340");
        do_oload(ch,"30340");
        do_oload(ch,"30341");
        do_oload(ch,"30342");
        do_oload(ch,"30342");
        do_oload(ch,"30343");
        do_oload(ch,"30343");
        do_oload(ch,"30344");
        do_oload(ch,"2622");
        do_oload(ch,"2204");
        ch->level = 1;
        ch->trust = 0;
        do_open(ch,"pack");
        sprintf(buf,"all pack");
        do_put(ch,buf);
        send_to_char("You now have a newbie pack!\n\r", ch);
        SET_BIT(ch->newbits,NEWBIE_PACK);
        }
ch->level = 1;
ch->trust = 0;
return;
}



void do_afk( CHAR_DATA *ch, char *argument )
{
    char buf[MAX_STRING_LENGTH];
 
        if ( IS_NPC(ch) )
        return;
 
        if (IS_SET(ch->extra, EXTRA_AFK))
        {
        free_string( ch->pcdata->title);
        ch->pcdata->title = str_dup( ch->short_descr );
        free_string( ch->short_descr );
        ch->short_descr = NULL;
        send_to_char( "You are no longer AFK.\n\r", ch );
        sprintf(buf,"#i#1%s#n#2 is no longer #1A#2F#3K#4!#n",ch->name);
        do_info(ch,buf);
        REMOVE_BIT(ch->extra,EXTRA_AFK);
        return;
        }
 
        else if (!IS_SET(ch->extra,EXTRA_AFK))
        {
        free_string( ch->short_descr );
        ch->short_descr = str_dup( ch->pcdata->title );
        free_string( ch->pcdata->title );
        ch->pcdata->title = str_dup("#n(#1AFK#n)");
        send_to_char( "You are now AFK.\n\r", ch );
        sprintf(buf,"#i#1%s#n#2 is now #1A#2F#3K#4!#n",ch->name);
        do_info(ch,buf);
        SET_BIT(ch->extra,EXTRA_AFK);
        WAIT_STATE(ch, 25);
        return;
        }
 
else
return;
 
}


struct quote_type
{
    char *      text;        /* Declare the Quote table... */
    char *      author;
};
 
const struct quote_type quote_table [MAX_QUOTES] =
  {
    { "Extraordinary Claims require Extraordinary evidence.", "Carl Sagan" }, /* Quote No 1 */
    { "Eagles may soar high and free, but tigers never get sucked into jet engines...",
      "Anon" },
    { "The mud says,'Good bye.' in it's best AOL voice.", "#4Xkilla#n" },
    { "Bye!", "Xkilla" }, /* Thats 4 quotes! */
    { "My thy blade stay sharp and thy heart forever dark!", "#3KaVir#n" },
  };
 
void do_rand_quote( CHAR_DATA *ch )
{
    char buf[MAX_STRING_LENGTH];
    int number;

    number = number_range( 1, MAX_QUOTES) - 1;
 
    sprintf ( buf, "\n\r#4%s\n\r - #1%s#n\n\r",
       quote_table[number].text,
       quote_table[number].author);           /* NB Yellow quote, Red author */
    send_to_char ( buf, ch );
    return;
}
const char *typo_table [14] =
{
   "Uhh, invalid command maybe!",
   "What is that suppose to be!",
   "What is your problem!",
   "What ever you say!",
   "#1Info#2->#4 You can't type!",
   "You're very dumb aren't you!",
   "What!!",
   "AAAAGGGGGGGHHHHHHHHH!!!!!",
   "Chance of that working next time is 2%",
   "Chance of that working next time is 95%",
   "Chance of that working next time is 0%",
   "NOT EVEN #2XKILLA#4 WOULD TYPE THAT!!!!",
   "NOT EVEN BELTAINE WOULD TYPE THAT!!!!",
   "Master I don't think he can type master"
};
 
void do_rand_typo(CHAR_DATA *ch)
{
  char buf[MAX_STRING_LENGTH];
  int number;
 
  number = number_range(1, 13);
 
  sprintf(buf, "#1%s\n\r", typo_table[number]);
  send_to_char(buf, ch);
  return;
}



char * plr_bit_name( int arg )
{
    static char buf[512];

    buf[0] = '\0';

    if ( arg & PLR_IS_NPC       ) strcat( buf, " npc"           );
    if ( arg & PLR_AUTOEXIT     ) strcat( buf, " autoexit"      );
    if ( arg & PLR_AUTOLOOT     ) strcat( buf, " autoloot"      );
    if ( arg & PLR_AUTOSAC      ) strcat( buf, " autosac"       );
    if ( arg & PLR_BLANK        ) strcat( buf, " blank"         );
    if ( arg & PLR_BRIEF        ) strcat( buf, " brief"         );
    if ( arg & PLR_COMBINE      ) strcat( buf, " combine"       );
    if ( arg & PLR_PROMPT       ) strcat( buf, " prompt"        );
    if ( arg & PLR_TELNET_GA    ) strcat( buf, " telnet_ga"     );
    if ( arg & PLR_HOLYLIGHT    ) strcat( buf, " holylight"     );
    if ( arg & PLR_WIZINVIS     ) strcat( buf, " wizinvis"      );
    if ( arg & PLR_INCOG        ) strcat( buf, " incog"         );
    if ( arg & PLR_SILENCE      ) strcat( buf, " silenced"      );
    if ( arg & PLR_NO_TELL      ) strcat( buf, " no_tell"       );
    if ( arg & PLR_LOG          ) strcat( buf, " log"           );
    if ( arg & PLR_FREEZE       ) strcat( buf, " freeze"        );
    if ( arg & PLR_GODLESS      ) strcat( buf, " godless"       );
    return ( buf[0] != '\0' ) ? buf+1 : "none";
}

char * extra_plr_bit_name( int arg )
{
    static char buf[512];
    
    buf[0] = '\0';
    
    if ( arg & EXTRA_TRUSTED            ) strcat( buf, " q_trusted" );
    if ( arg & EXTRA_NEWPASS            ) strcat( buf, " newpass" );
    if ( arg & EXTRA_OSWITCH            ) strcat( buf, " oswitch" );
    if ( arg & EXTRA_SWITCH             ) strcat( buf, " switch" );
    if ( arg & EXTRA_FAKE_CON           ) strcat( buf, " fake_con" );
    if ( arg & TIED_UP                  ) strcat( buf, " tied_up" );
    if ( arg & GAGGED                   ) strcat( buf, " gagged" );
    if ( arg & BLINDFOLDED              ) strcat( buf, " blindfolded" );
    if ( arg & EXTRA_DONE               ) strcat( buf, " non_virgin" );
    if ( arg & EXTRA_EXP                ) strcat( buf, " got_exp" );
    if ( arg & EXTRA_PREGNANT           ) strcat( buf, " pregnant" );
    if ( arg & EXTRA_LABOUR             ) strcat( buf, " labour" );
    if ( arg & EXTRA_BORN               ) strcat( buf, " born" );
    if ( arg & EXTRA_PROMPT             ) strcat( buf, " prompt" );
    if ( arg & EXTRA_MARRIED            ) strcat( buf, " married" );
    if ( arg & EXTRA_CALL_ALL           ) strcat( buf, " call_all" );
    return ( buf[0] != '\0' ) ? buf+1 : "none";
}
   char * get_position_name( int arg )
{
    switch( arg )
    {
        case 0: return "dead";
        case 1: return "mortal";
        case 2: return "incap";
        case 3: return "stunned";
        case 4: return "sleeping";
        case 5: return "meditating";
        case 6: return "sitting";
        case 7: return "resting";
        case 8: return "fighting";
        case 9: return "standing";
    }
    bug( "Get_position_name: unknown type %d.", arg );
    return "(unknown)";
}

/*
 * Itemaffect bit names :)
 */
char * itemaffect_bit_name( int arg )
{
    static char buf[512];
    
    buf[0] = '\0';

    if ( arg & ITEMA_SHOCKSHIELD        ) strcat( buf, " Shockshield"  ); 
    if ( arg & ITEMA_FIRESHIELD         ) strcat( buf, " Fireshield"    );
    if ( arg & ITEMA_ICESHIELD          ) strcat( buf, " Iceshield"     );
    if ( arg & ITEMA_ACIDSHIELD         ) strcat( buf, " Acidshield"    );
    if ( arg & ITEMA_DBPASS             ) strcat( buf, " Pass Door"     );
    if ( arg & ITEMA_CHAOSSHIELD        ) strcat( buf, " Chaoshield"    );
    if ( arg & ITEMA_ARTIFACT           ) strcat( buf, " Artifact"      );
    if ( arg & ITEMA_MYSTIC           ) strcat( buf, " Mystic"      ); 
    if ( arg & ITEMA_REGENERATE         ) strcat( buf, " Regeneration"  );
    if ( arg & ITEMA_SPEED              ) strcat( buf, " Speed"         );
    if ( arg & ITEMA_VORPAL             ) strcat( buf, " Vorpal"        );
    if ( arg & ITEMA_PEACE              ) strcat( buf, " Peace"         );
    if ( arg & ITEMA_RIGHT_SILVER       ) strcat( buf, " Right Silver"  );
    if ( arg & ITEMA_LEFT_SILVER        ) strcat( buf, " Left Silver"   );
    if ( arg & ITEMA_REFLECT            ) strcat( buf, " Darkshield"    );
    if ( arg & ITEMA_RESISTANCE         ) strcat( buf, " Resistance"    );
    if ( arg & ITEMA_VISION             ) strcat( buf, " Vision"        );
    if ( arg & ITEMA_STALKER            ) strcat( buf, " Stalker"       );
    if ( arg & ITEMA_VANISH             ) strcat( buf, " Vanish"        );
    if ( arg & ITEMA_RAGER              ) strcat( buf, " Rager"         );
    return ( buf[0] != '\0' ) ? buf+1 : "none";
}


void do_pstat ( CHAR_DATA *ch, char *argument )
{
    char        arg[MAX_INPUT_LENGTH];
    char        buf[MAX_STRING_LENGTH];
    CHAR_DATA   *victim;
        
    argument = one_argument( argument, arg );
  
    if ( arg[0] == '\0' )
    {
        send_to_char("Pstat whom?\n\r", ch );
        return;
    }
 
    if ( ( victim = get_char_world( ch, arg ) ) == NULL )
    {
       send_to_char("They aren't here.\n\r", ch );
        return;
    }
    
    if ( !IS_NPC( victim ) && IS_SET( victim->act, PLR_GODLESS ) &&
         get_trust( ch ) < NO_GODLESS )
    {
        send_to_char( "You failed.\n\r", ch );
        return;
    }
        
    sprintf( buf, "Name : %s.\n\r",
        IS_NPC( victim )        ? victim->short_descr : victim->name );
  send_to_char( buf, ch );
    sprintf( buf, "Sex : %s. Room : %d. Align : %d. Primal : %d. Quest : %d.\n\r",
        victim->sex == SEX_MALE         ? "Male"        :
      victim->sex == SEX_FEMALE       ? "Female"      : "None",
        victim->in_room == NULL         ? 0             : victim->in_room->vnum,
        victim->alignment,
        victim->practice,
        IS_NPC( victim )                ? 0             : victim->pcdata->quest
        );
    send_to_char( buf, ch );
        
    sprintf( buf, "Level : %d. Trust : %d. Gold : %d. Exp : %d.\n\r",
        victim->level,
        victim->trust,
        victim->gold,
        victim->exp );
   send_to_char( buf, ch );
    
    sprintf( buf, "Hit : %d. Dam : %d. AC : %d. Position : %s\n\r",
       char_hitroll( victim ),
        char_damroll( victim ),
        char_ac( victim ),
        capitalize( get_position_name( victim->position ) ));
    send_to_char( buf, ch );
          
    sprintf( buf, "HP %d/%d. Mana %d/%d. Move %d/%d.\n\r",
        victim->hit, victim->max_hit,
        victim->mana, victim->max_mana,
        victim->move, victim->max_move );
    send_to_char( buf, ch );
        
    sprintf( buf, "Str: %d.  Int: %d.  Wis: %d.  Dex: %d.  Con: %d.\n\r",
      get_curr_str(victim),
        get_curr_int(victim),
        get_curr_wis(victim),
        get_curr_dex(victim), 
        get_curr_con(victim) );
    send_to_char( buf, ch );
        
    sprintf( buf, "Fighting : %s. (%d)\n\r",
        victim->fighting ? victim->fighting->name  : "(None)",
        victim->fighting ? victim->fighting->level : 0 ); 
   send_to_char( buf, ch );
        
    sprintf( buf, "Pkill : %d. Pdeath : %d. Mkill : %d. Mdeath : %d.\n\r",
        IS_NPC( victim ) ? 0 : victim->pkill,
        IS_NPC( victim ) ? 0 : victim->pdeath,
        IS_NPC( victim ) ? 0 : victim->mkill,
       IS_NPC( victim ) ? 0 : victim->mdeath );
    send_to_char( buf, ch ); 
        
    sprintf( buf, "TotExp  : %12d. TotMobLev  : %10d. TotQuestPoints : %10d.\n\r",
        IS_NPC( victim ) ? 0 : victim->pcdata->score[SCORE_TOTAL_XP],
        IS_NPC( victim ) ? 0 : victim->pcdata->score[SCORE_TOTAL_LEVEL],
        IS_NPC( victim ) ? 0 : victim->pcdata->score[SCORE_QUEST] );
    send_to_char( buf, ch );
        
    sprintf( buf, "HighExp : %12d. HighMobLev : %10d. Tot#Quests     : %10d.\n\r",
      IS_NPC( victim ) ? 0 : victim->pcdata->score[SCORE_HIGH_XP],
        IS_NPC( victim ) ? 0 : victim->pcdata->score[SCORE_HIGH_LEVEL],
        IS_NPC( victim ) ? 0 : victim->pcdata->score[SCORE_NUM_QUEST] );  
    send_to_char( buf, ch );
        
    if ( !IS_NPC( victim ) )
   {
        sprintf( buf, "Unarmed : %4d.", victim->wpn[0] );
        send_to_char( buf, ch );
        sprintf( buf, " Slice   : %4d.", victim->wpn[1] );
        send_to_char( buf, ch );
        sprintf( buf, " Stab    : %4d.", victim->wpn[2] );
        send_to_char( buf, ch );
        sprintf( buf, " Slash   : %4d.", victim->wpn[3] );
        send_to_char( buf, ch );
        sprintf( buf, " Whip    : %4d.\n\r", victim->wpn[4] );
        send_to_char( buf, ch );
        sprintf( buf, "Claw    : %4d.", victim->wpn[5] );
        send_to_char( buf, ch );
        sprintf( buf, " Blast   : %4d.", victim->wpn[6] );
        send_to_char( buf, ch );
        sprintf( buf, " Pound   : %4d.", victim->wpn[7] );
send_to_char( buf, ch );
        sprintf( buf, " Crush   : %4d.", victim->wpn[8] );
        send_to_char( buf, ch );
        sprintf( buf, " Grep    : %4d.\n\r", victim->wpn[9] );
        send_to_char( buf, ch );
        sprintf( buf, "Bite    : %4d.", victim->wpn[10] );
     send_to_char( buf, ch );   
        sprintf( buf, " Pierce  : %4d.", victim->wpn[11] );
        send_to_char( buf, ch );
        sprintf( buf, " Suck    : %4d.\n\r",victim->wpn[12] );
        send_to_char( buf, ch );
        
        sprintf( buf, "%-8s : %3d. %-8s : %3d. %-8s : %3d. %-8s : %3d. %-8s : %3d.\n\r",
            "Purple",   victim->spl[PURPLE_MAGIC],
            "Red",      victim->spl[RED_MAGIC],
            "Blue",     victim->spl[BLUE_MAGIC],
           "Green",    victim->spl[GREEN_MAGIC],
            "Yellow",   victim->spl[YELLOW_MAGIC] );
        send_to_char( buf, ch );
        sprintf( buf, "%-8s : %3d. %-8s : %3d. %-8s : %3d. %-8s : %3d. %-8s : %3d.\n\r",
            "Viper",    victim->stance[STANCE_VIPER],
            "Crane",    victim->stance[STANCE_CRANE],
            "Crab",     victim->stance[STANCE_CRAB],
            "Mongoose", victim->stance[STANCE_MONGOOSE],   
            "Bull",     victim->stance[STANCE_BULL] );
        send_to_char( buf, ch );
        
        sprintf( buf, "%-8s : %3d. %-8s : %3d. %-8s : %3d. %-8s : %-3d. %-8s : %3d.\n\r",
            "Mantis",   victim->stance[STANCE_MANTIS],
            "Dragon",   victim->stance[STANCE_DRAGON],
            "Tiger",    victim->stance[STANCE_TIGER],
            "Monkey",   victim->stance[STANCE_MONKEY],
           "Swallow",  victim->stance[STANCE_SWALLOW] );
        send_to_char( buf, ch );
        
	sprintf( buf, "Act         : %s\n\r", plr_bit_name(victim->act ));
    	send_to_char( buf, ch );
	sprintf( buf, "Extra       : %s\n\r",
        victim->extra <= 0 ? "(None)" : extra_plr_bit_name( victim->extra ) );
    	send_to_char( buf, ch );
	sprintf( buf, "ItemAff     : %s\n\r",
        victim->itemaffect <= 0 ? "(None)" : itemaffect_bit_name(victim->itemaffect ) );
    	send_to_char( buf, ch );
            
              sprintf( buf, "Affected by : %s.\n\r",  
        affect_bit_name( victim->affected_by ) );
    	send_to_char( buf, ch );
            
    return;
}       
}



