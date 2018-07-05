/* Vampire commands being added by Smoo 
   find your own damn place to add things for vamps
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

void do_vampcreate( CHAR_DATA *ch, char *argument )
{
    OBJ_INDEX_DATA *pObjIndex;
    OBJ_DATA *obj;
    char arg[MAX_INPUT_LENGTH];
    int vnum = 0;
    int maxd = 0;
    int mind = 0;

    argument = one_argument( argument, arg );

    if (IS_NPC(ch)) return;    
    if (!IS_CLASS(ch, CLASS_VAMPIRE))
    {
            send_to_char("Huh?\n\r",ch);
            return;
    }

    if (arg[0] == '\0')
    {
        send_to_char("Please specify which piece of vampire armor you wish to make\n\r", ch);
        send_to_char("You may make a ring, breastplate, belt, scimitar, or hook.\n\r", ch);
        send_to_char("The cost is 80 primal.\n\r",ch);
        return;
    }

    if ( ch->practice < 80 )
    {
        send_to_char("It costs 80 points of primal to create vampire equipment.\n\r", ch);
        return;           
    }
    if      (!str_cmp(arg,"ring"     )) vnum = 100601;
    else if (!str_cmp(arg,"breastplate"   )) vnum = 100602;
    else if (!str_cmp(arg,"belt")) vnum = 100605;
    else if (!str_cmp(arg,"scimitar"    )) {vnum = 100603;mind = 25;maxd = 45;}
    else if (!str_cmp(arg,"hook" )) {vnum = 100604;mind = 35;maxd = 45;}
    else
    {
        send_to_char("Please specify which piece of vampire armor you wish to make.", ch);
        send_to_char("You may make a ring, breastplate, belt, scimitar, or hook.\n\r", ch);
        send_to_char("The cost is 80 primal.\n\r",ch);
      return;
    }

    if ( vnum == 0 || (pObjIndex = get_obj_index( vnum )) == NULL)
    {
        send_to_char("Missing object, please inform a God.\n\r",ch);
        return;
    }
        ch->practice -= 80;
    obj = create_object(pObjIndex, 50);
    obj_to_char(obj, ch);
    SET_BIT(obj->spectype, SITEM_VAMPIRE);  
    SET_BIT(obj->quest, QUEST_RELIC);
    if (mind != 0) obj->value[1] = mind;
    if (maxd != 0) obj->value[2] = maxd;
    act("$p fades into your hands.",ch,obj,NULL,TO_CHAR);
    act("$p fades into $n's hands.",ch,obj,NULL,TO_ROOM);
    return;
}

/*blood river is in hydra.c, because its sharing the same command
 (void do_reach)
*/
