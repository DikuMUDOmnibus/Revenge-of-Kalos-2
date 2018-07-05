//By xkilla.

#if defined(macintosh)
#include <types.h>
#else
#include <sys/types.h>
#endif
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include "merc.h"

void auction_channel( char * msg );

void do_auction( CHAR_DATA *ch, char * argument )
{
    long questpoints =0;
    OBJ_DATA *	obj;
    char arg1[MAX_INPUT_LENGTH], buf[MAX_STRING_LENGTH];

    argument = one_argument( argument, arg1 );

    if ( ch == NULL || IS_NPC(ch) )
	return;

    if ( arg1[0] == '\0')
    {
	if ( IS_SET(ch->deaf,COMM_NOAUCTION) )
	{
	    REMOVE_BIT(ch->deaf,COMM_NOAUCTION );
	    send_to_char("Auction channel is now ON.\n\r",ch);
	    return;
	}

	SET_BIT(ch->deaf,COMM_NOAUCTION);
	send_to_char("Auction channel is now OFF.\n\r",ch);
	return;
    }

    if ( !str_cmp( arg1, "bid" ) )
    {
	long bid;
        obj = auction_info.item;

        if ( !obj )
        {
            send_to_char("#PT#phere is nothing up for auction right now.\n\r",ch);
            return;
        }

	if ( argument[0] == '\0' )
	{
	    send_to_char("#PY#pou must enter an amount to bid.\n\r",ch);
	    return;
	}

	bid = atol( argument );

	if ( bid <= auction_info.current_bid )
	{
	    sprintf(buf, "#PY#pou must bid above the current bid of %ld qps.\n\r",
		auction_info.current_bid );
	    return;
	}

	if ( bid < MINIMUM_BID )
	{
	    sprintf( buf, "#PT#phe minimum bid is #3%d #pqps.\n\r",MINIMUM_BID);
	    send_to_char(buf,ch);
	    return;
	}

	if ( (ch->pcdata->quest) < bid )
	{
	    send_to_char("You can't cover that bid.\n\r",ch);
	    return;
	}

	sprintf(buf, "%ld qps has been offered for %s.\n\r",
	    bid, auction_info.item->short_descr);
	auction_channel( buf );

	if ( auction_info.high_bidder != NULL )
	{
	    auction_info.high_bidder->pcdata->quest += auction_info.qps_held;
	}

	questpoints = UMIN( ch->pcdata->quest, bid );

	if ( questpoints < bid )
	{
	   questpoints = bid;
	}

	ch->pcdata->quest -= questpoints;

	auction_info.qps_held	= questpoints;
	auction_info.high_bidder	= ch;
	auction_info.current_bid	= bid;
	auction_info.status	 	= 0;

	return;	
    }

    if ( !str_cmp( arg1, "info" ) )
    {
        obj = auction_info.item;
 
        if ( !obj )
        {
            send_to_char("#PT#phere is nothing up for auction right now.\n\r",ch);
            return;
        }

	else
	{
         sprintf(buf,"#5QOwner: (%s) #3%s  #2Bid: %ld #4Status: %ld#n \n\r", obj->questowner, obj->short_descr,
auction_info.current_bid, auction_info.status );
         send_to_char(buf, ch );
         return;
	}

    return;
    }

    if ( auction_info.item != NULL )
    {
	send_to_char("There is already another item up for bid.\n\r",ch);
	return;
    }

        if ( ( obj = get_obj_carry( ch, arg1 ) ) == NULL )
        {
            send_to_char( "You do not have that item.\n\r", ch );
            return;
        }
 

    if ( IS_OBJ_STAT( obj, ITEM_NODROP ) )
    {
	send_to_char("You can't let go of that item.\n\r",ch);
	return;
    }

    auction_info.owner		= ch;
    auction_info.item		= obj;
    auction_info.current_bid	= 0;
    auction_info.status		= 0;

    sprintf(buf,"#PN#pow taking bids on #3%s.\n\r", obj->short_descr );
    auction_channel( buf );

    obj_from_char( obj );

    return;

}

void auction_update( )
{
    char buf[MAX_STRING_LENGTH], temp[MAX_STRING_LENGTH],
	temp1[MAX_STRING_LENGTH];

    if ( auction_info.item == NULL )
	return;

    auction_info.status++;

    if ( auction_info.status == AUCTION_LENGTH )
    {
	sprintf(buf,"#3%s #PS#pOLD to #3%s #pfor #3%ld #pqps.\n\r",
	    capitalize(auction_info.item->short_descr),
	    auction_info.high_bidder->name,
	    auction_info.current_bid );
	auction_channel( buf );

	auction_info.owner->pcdata->quest += auction_info.qps_held;

	sprintf(temp1, "%ld qps ", auction_info.qps_held );
	sprintf(buf, "You receive %s qps.\n\r",
		auction_info.qps_held > 0 ? temp1 : "",
		(auction_info.qps_held > 0));
	send_to_char( buf, auction_info.owner );
		
	obj_to_char( auction_info.item, auction_info.high_bidder );

	sprintf(buf, "%s appears in your hands.\n\r",
		capitalize(auction_info.item->short_descr) );
	send_to_char( buf, auction_info.high_bidder );
	
	auction_info.item		= NULL;
	auction_info.owner		= NULL;
	auction_info.high_bidder	= NULL;
	auction_info.current_bid	= 0;
	auction_info.status		= 0;
	auction_info.qps_held		= 0;

	return;
    }

    if ( auction_info.status == AUCTION_LENGTH - 1 )
    {
	sprintf(buf, "#3%s #P- #pgoing twice at #3%ld #pqps.\n\r",
		capitalize(auction_info.item->short_descr),
		auction_info.current_bid );
	auction_channel( buf );
	return;
    }

    if ( auction_info.status == AUCTION_LENGTH - 2 )
    {
	if ( auction_info.current_bid == 0 )
	{
	    sprintf(buf, "#pNo bids on #3%s#p - item removed.\n\r",
		auction_info.item->short_descr);
	    auction_channel( buf );

	    obj_to_char( auction_info.item, auction_info.owner );

	sprintf(buf, "#3%s #pis returned to you.\n\r",
		capitalize(auction_info.item->short_descr) );
	send_to_char( buf, auction_info.owner );
	
	    auction_info.item           = NULL;
	    auction_info.owner          = NULL;
	    auction_info.current_bid    = 0;
	    auction_info.status         = 0;

	    return;
	}

        sprintf(buf, "#3%s #P- #pgoing once at #3%ld #pqps.\n\r",
                capitalize(auction_info.item->short_descr),
                auction_info.current_bid );
        auction_channel( buf );
        return;
    }

    return;

}

void auction_channel( char * msg )
{
    char buf[MAX_STRING_LENGTH];
    DESCRIPTOR_DATA *d;

    sprintf(buf, "\n\r#P[#pAUCTION#P] #3%s", msg ); /* Add color if you wish */

      for ( d = descriptor_list; d != NULL; d = d->next )
      {
	CHAR_DATA *victim;

	victim = d->original ? d->original : d->character;

	if ( d->connected == CON_PLAYING &&
	     !IS_SET(victim->deaf,COMM_NOAUCTION))
	      {
		send_to_char( buf, victim );
	      }
      }

    return;
}

