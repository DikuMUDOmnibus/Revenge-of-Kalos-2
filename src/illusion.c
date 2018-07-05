/*
 *Illusionists ala Smoo
 *
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


void do_morph(CHAR_DATA *ch, char *argument)
{
    char arg [MAX_INPUT_LENGTH];
    char buf [MAX_STRING_LENGTH];
    char buf2 [MAX_STRING_LENGTH];
    char buf3 [MAX_STRING_LENGTH];
    argument = one_argument( argument, arg );
 {
    if (!IS_CLASS(ch, CLASS_ILLUSIONIST)) {
     send_to_char("Huh?\n\r", ch);
     return;
    }
   if (arg[0] == '\0' && IS_POLYAFF(ch, POLY_ILLUSION)) {
     free_string(ch->morph);
     ch->max_mana -= 1500;
     ch->max_hit -= 1000;
     ch->morph = str_dup("");       REMOVE_BIT(ch->polyaff, POLY_ILLUSION);
     send_to_char ("#LThe illusion fades..#n\n\r", ch);
     return;
     }
   if (arg[0] != '\0' && !IS_POLYAFF(ch, POLY_ILLUSION)) {
     sprintf(buf, "%s%ls", ch->name, arg);
        SET_BIT(ch->polyaff, POLY_ILLUSION);
     sprintf(buf2, "$n breaths in and when he blows out, he distorts into %ls", buf);
     act(buf2, ch, NULL, NULL, TO_ROOM);
     sprintf(buf3, "You breath imagine being %ls", buf);
     act(buf3, ch, NULL, NULL, TO_CHAR);
     ch->morph = str_dup(buf);
     ch->max_mana += 1500;
     ch->max_hit += 1000;
     return;
     }
    {
    send_to_char("BUG: Infrom Smoo. (ref 1101)", ch);
    return;
    }
}
}    
