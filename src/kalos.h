/***************************************************************************
 *  Stuff coded for  RoK started on 7/8/99                                 *
 *  Much time and thought has gone into this software and you are          *
 *  benefitting.  We hope that you share your changes too.  What goes      *
 *  around, comes around.                                                  *
 ***************************************************************************/

// Arcane Shortcuts
void    stc             args( ( const char *txt, CHAR_DATA *ch ) );




//Struct Types
typedef struct  tag_data            TAG_DATA;
typedef struct  dxp_data	    DXP_DATA;


//Random Defining
#define TAG_LENGTH 10
#define PLR_INTAG   1
#define PLR_AUTOCONSUME 2
#define PLR_AUTOTICK    4
#define PLR_TOUGHEN	8

//Broods
#define BROOD_PUTNAMEHERE	1



//Structures
struct tag_data
{
	int		tag;
        sh_int          status;
};

struct dxp_data
{
	sh_int		dxp;
};

struct  xkilla
{
     XKILLA *           next;
	int		plr;
	int		aliens;
	int		drows;
	int		favorite;
	sh_int		dskills;
};

/* Shatan WARPS*/

#define WARP_CBODY				1
#define WARP_SBODY				2
#define WARP_STRONGARMS				4
#define WARP_STRONGLEGS				8
#define WARP_VENOMTONG				16
#define WARP_SPIKETAIL				32
#define WARP_BADBREATH				64
#define WARP_QUICKNESS				128
#define WARP_STAMINA				256
#define WARP_HUNT				512
#define WARP_DEVOUR				1024
#define WARP_TERROR				2048
#define WARP_REGENERATE				4096
#define WARP_STEED				8192
#define WARP_WEAPON				16384
#define WARP_INFIRMITY				32768
#define WARP_GBODY				65536
#define WARP_SCARED				131072
#define WARP_MAGMA				262144
#define WARP_WEAK				524288
#define WARP_SLOW				1048576
#define WARP_VULNER				2097152
#define WARP_SHARDS				4194304
#define WARP_WINGS				8388608
#define WARP_CLUMSY				16777216
#define WARP_STUPID				33554432
#define WARP_SPOON				67108864
#define WARP_FORK				134217728
#define WARP_KNIFE				268435456
#define WARP_SALADBOWL				536870912



/* Status of TAG */

#define TAG_CLOSED                    0
#define TAG_OPENED                    1
#define TAG_STARTED		      2

#define TAG_PLAYING		(A)
#define TAG_FROZEN		(B)
#define TAG_RED			(C)
#define TAG_BLUE		(D)



//Global Variables
extern          TAG_DATA            tag_info;
extern		DXP_DATA	    dxp_info;

//xkaff


//Time
#define PULSE_TAG             (60 * PULSE_PER_SECOND)

//Prototypes







//  Commands //

DECLARE_DO_FUN( do_stag		);
DECLARE_DO_FUN( do_ftag );
DECLARE_DO_FUN( do_tag );
DECLARE_DO_FUN( do_red );
DECLARE_DO_FUN( do_blue );
DECLARE_DO_FUN( do_ztag );
DECLARE_DO_FUN( do_shadowdrain );
DECLARE_DO_FUN( do_mystic	);

//Shatan Commands //
DECLARE_DO_FUN( do_mutter	);
DECLARE_DO_FUN( do_legions	);
DECLARE_DO_FUN( do_enroll        );
DECLARE_DO_FUN( do_obtain        );
DECLARE_DO_FUN( do_redeem        );
DECLARE_DO_FUN( do_warps         );
DECLARE_DO_FUN( do_leech	);
//HYDRA commands
DECLARE_DO_FUN( do_hydra_regen	);
DECLARE_DO_FUN( do_reach	);
//New vampire commands
DECLARE_DO_FUN( do_vampcreate	);
//illusionist commands
DECLARE_DO_FUN( do_morph	);
// Spells and shit
DECLARE_SPELL_FUN(      spell_limbo_scythe      );
