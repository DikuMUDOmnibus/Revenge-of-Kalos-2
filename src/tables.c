#include "include.h"

const struct flag_type area_flags[] =
{
    {	"none",			AREA_NONE,		FALSE	},
    {	"changed",		AREA_CHANGED,		TRUE	},
    {	"added",		AREA_ADDED,		TRUE	},
    {	"loading",		AREA_LOADING,		FALSE	},
    {	NULL,			0,			0	}
};



const struct flag_type sex_flags[] =
{
    {	"male",			SEX_MALE,		TRUE	},
    {	"female",		SEX_FEMALE,		TRUE	},
    {	"neutral",		SEX_NEUTRAL,		TRUE	},
    {   "random",               3,                      TRUE    },   /* ROM */
    {	"none",			SEX_NEUTRAL,		TRUE	},
    {	NULL,			0,			0	}
};


const struct flag_type exit_flags[] =
{
    {   "door",			EX_ISDOOR,		TRUE    },
    {	"closed",		EX_CLOSED,		TRUE	},
    {	"locked",		EX_LOCKED,		TRUE	},
    {	"pickproof",		EX_PICKPROOF,		TRUE	},
//    {   "nopass",		EX_NOPASS,		TRUE	},
//    {   "easy",			EX_EASY,		TRUE	},
//    {   "hard",			EX_HARD,		TRUE	},
//    {	"infuriating",		EX_INFURIATING,		TRUE	},
//   {	"noclose",		EX_NOCLOSE,		TRUE	},
//   {	"nolock",		EX_NOLOCK,		TRUE	},
    {	NULL,			0,			0	}
};



const struct flag_type door_resets[] =
{
    {	"open and unlocked",	0,		TRUE	},
    {	"closed and unlocked",	1,		TRUE	},
    {	"closed and locked",	2,		TRUE	},
    {	NULL,			0,		0	}
};



const struct flag_type room_flags[] =
{
    {	"dark",			ROOM_DARK,		TRUE	},
    {	"no_mob",		ROOM_NO_MOB,		TRUE	},
    {	"indoors",		ROOM_INDOORS,		TRUE	},
    {	"private",		ROOM_PRIVATE,		TRUE    },
    {	"safe",			ROOM_SAFE,		TRUE	},
    {	"solitary",		ROOM_SOLITARY,		TRUE	},
    {	"pet_shop",		ROOM_PET_SHOP,		TRUE	},
    {	"no_recall",		ROOM_NO_RECALL,		TRUE	},
//    {	"imp_only",		ROOM_IMP_ONLY,		TRUE    },
//    {	"gods_only",	        ROOM_GODS_ONLY,		TRUE    },
//    {	"heroes_only",		ROOM_HEROES_ONLY,	TRUE	},
//    {	"newbies_only",		ROOM_NEWBIES_ONLY,	TRUE	},
//    {	"law",			ROOM_LAW,		TRUE	},
//    {   "nowhere",		ROOM_NOWHERE,		TRUE	},
    {	NULL,			0,			0	}
};



const struct flag_type sector_flags[] =
{
    {	"inside",	SECT_INSIDE,		TRUE	},
    {	"city",		SECT_CITY,		TRUE	},
    {	"field",	SECT_FIELD,		TRUE	},
    {	"forest",	SECT_FOREST,		TRUE	},
    {	"hills",	SECT_HILLS,		TRUE	},
    {	"mountain",	SECT_MOUNTAIN,		TRUE	},
    {	"swim",		SECT_WATER_SWIM,	TRUE	},
    {	"noswim",	SECT_WATER_NOSWIM,	TRUE	},
    {   "unused",	SECT_UNUSED,		TRUE	},
    {	"air",		SECT_AIR,		TRUE	},
    {	"desert",	SECT_DESERT,		TRUE	},
    {	NULL,		0,			0	}
};



const struct flag_type type_flags[] =
{
    {	"light",		ITEM_LIGHT,		TRUE	},
    {	"scroll",		ITEM_SCROLL,		TRUE	},
    {	"wand",			ITEM_WAND,		TRUE	},
    {	"staff",		ITEM_STAFF,		TRUE	},
    {	"weapon",		ITEM_WEAPON,		TRUE	},
    {	"treasure",		ITEM_TREASURE,		TRUE	},
    {	"armor",		ITEM_ARMOR,		TRUE	},
    {	"potion",		ITEM_POTION,		TRUE	},
    {	"furniture",		ITEM_FURNITURE,		TRUE	},
    {	"trash",		ITEM_TRASH,		TRUE	},
    {	"container",		ITEM_CONTAINER,		TRUE	},
    {	"drinkcontainer",	ITEM_DRINK_CON,		TRUE	},
    {	"key",			ITEM_KEY,		TRUE	},
    {	"food",			ITEM_FOOD,		TRUE	},
    {	"money",		ITEM_MONEY,		TRUE	},
    {	"boat",			ITEM_BOAT,		TRUE	},
    {	"npccorpse",		ITEM_CORPSE_NPC,	TRUE	},
    {	"pc corpse",		ITEM_CORPSE_PC,		FALSE	},
    {	"fountain",		ITEM_FOUNTAIN,		TRUE	},
    {	"pill",			ITEM_PILL,		TRUE	},
//   {	"protect",		ITEM_PROTECT,		TRUE	},
//   {	"map",			ITEM_MAP,		TRUE	},
    {   "portal",		ITEM_PORTAL,		TRUE	},
//   {   "warpstone",		ITEM_WARP_STONE,	TRUE	},
//   {	"roomkey",		ITEM_ROOM_KEY,		TRUE	},
//   { 	"gem",			ITEM_GEM,		TRUE	},
//   {	"jewelry",		ITEM_JEWELRY,		TRUE	},
//   {	"jukebox",		ITEM_JUKEBOX,		TRUE	},
    {	NULL,			0,			0	}
};


const struct flag_type extra_flags[] =
{
    {	"glow",			ITEM_GLOW,		TRUE	},
    {	"hum",			ITEM_HUM,		TRUE	},
//    {	"dark",			ITEM_DARK,		TRUE	},
//    {	"lock",			ITEM_LOCK,		TRUE	},
//    {	"evil",			ITEM_EVIL,		TRUE	},
    {	"invis",		ITEM_INVIS,		TRUE	},
    {	"magic",		ITEM_MAGIC,		TRUE	},
    {	"nodrop",		ITEM_NODROP,		TRUE	},
    {	"bless",		ITEM_BLESS,		TRUE	},
    {	"antigood",		ITEM_ANTI_GOOD,		TRUE	},
    {	"antievil",		ITEM_ANTI_EVIL,		TRUE	},
    {	"antineutral",		ITEM_ANTI_NEUTRAL,	TRUE	},
    {	"noremove",		ITEM_NOREMOVE,		TRUE	},
    {	"inventory",		ITEM_INVENTORY,		TRUE	},
//    {	"nopurge",		ITEM_NOPURGE,		TRUE	},
//    {	"rotdeath",		ITEM_ROT_DEATH,		TRUE	},
 //   {	"visdeath",		ITEM_VIS_DEATH,		TRUE	},
//    {   "nonmetal",		ITEM_NONMETAL,		TRUE	},
//    {	"meltdrop",		ITEM_MELT_DROP,		TRUE	},
//    {	"hadtimer",		ITEM_HAD_TIMER,		TRUE	},
//    {	"sellextract",		ITEM_SELL_EXTRACT,	TRUE	},
//    {	"burnproof",		ITEM_BURN_PROOF,	TRUE	},
//    {	"nouncurse",		ITEM_NOUNCURSE,		TRUE	},
    {	NULL,			0,			0	}
};



const struct flag_type wear_flags[] =
{
    {	"take",			ITEM_TAKE,		TRUE	},
    {	"finger",		ITEM_WEAR_FINGER,	TRUE	},
    {	"neck",			ITEM_WEAR_NECK,		TRUE	},
    {	"body",			ITEM_WEAR_BODY,		TRUE	},
    {	"head",			ITEM_WEAR_HEAD,		TRUE	},
    {	"legs",			ITEM_WEAR_LEGS,		TRUE	},
    {	"feet",			ITEM_WEAR_FEET,		TRUE	},
    {	"hands",		ITEM_WEAR_HANDS,	TRUE	},
    {	"arms",			ITEM_WEAR_ARMS,		TRUE	},
    {	"shield",		ITEM_WEAR_SHIELD,	TRUE	},
    {	"about",		ITEM_WEAR_ABOUT,	TRUE	},
    {	"waist",		ITEM_WEAR_WAIST,	TRUE	},
    {	"wrist",		ITEM_WEAR_WRIST,	TRUE	},
    {	"wield",		ITEM_WIELD,		TRUE	},
    {	"hold",			ITEM_HOLD,		TRUE	},
//    {   "nosac",		ITEM_NO_SAC,		TRUE	},
//    {	"wearfloat",		ITEM_WEAR_FLOAT,	TRUE	},
//    {   "twohands",            ITEM_TWO_HANDS,         TRUE    },
    {	NULL,			0,			0	}
};

/*
 * Used when adding an affect to tell where it goes.
 * See addaffect and delaffect in act_olc.c
 */
const struct flag_type apply_flags[] =
{
    {	"none",			APPLY_NONE,		TRUE	},
    {	"strength",		APPLY_STR,		TRUE	},
    {	"dexterity",		APPLY_DEX,		TRUE	},
    {	"intelligence",		APPLY_INT,		TRUE	},
    {	"wisdom",		APPLY_WIS,		TRUE	},
    {	"constitution",		APPLY_CON,		TRUE	},
    {	"sex",			APPLY_SEX,		TRUE	},
    {	"class",		APPLY_CLASS,		TRUE	},
    {	"level",		APPLY_LEVEL,		TRUE	},
    {	"age",			APPLY_AGE,		TRUE	},
    {	"height",		APPLY_HEIGHT,		TRUE	},
    {	"weight",		APPLY_WEIGHT,		TRUE	},
    {	"mana",			APPLY_MANA,		TRUE	},
    {	"hp",			APPLY_HIT,		TRUE	},
    {	"move",			APPLY_MOVE,		TRUE	},
    {	"gold",			APPLY_GOLD,		TRUE	},
    {	"experience",		APPLY_EXP,		TRUE	},
    {	"ac",			APPLY_AC,		TRUE	},
    {	"hitroll",		APPLY_HITROLL,		TRUE	},
    {	"damroll",		APPLY_DAMROLL,		TRUE	},
//    {	"saves",		APPLY_SAVES,		TRUE	},
    {	"savingpara",		APPLY_SAVING_PARA,	TRUE	},
    {	"savingrod",		APPLY_SAVING_ROD,	TRUE	},
    {	"savingpetri",		APPLY_SAVING_PETRI,	TRUE	},
    {	"savingbreath",		APPLY_SAVING_BREATH,	TRUE	},
    {	"savingspell",		APPLY_SAVING_SPELL,	TRUE	},
//    {	"spellaffect",		APPLY_SPELL_AFFECT,	FALSE	},
    {	NULL,			0,			0	}
};



/*
 * What is seen.
 */
const struct flag_type wear_loc_strings[] =
{
    {	"in the inventory",	WEAR_NONE,	TRUE	},
    {	"as a light",		WEAR_LIGHT,	TRUE	},
    {	"on the left finger",	WEAR_FINGER_L,	TRUE	},
    {	"on the right finger",	WEAR_FINGER_R,	TRUE	},
    {	"around the neck (1)",	WEAR_NECK_1,	TRUE	},
    {	"around the neck (2)",	WEAR_NECK_2,	TRUE	},
    {	"on the body",		WEAR_BODY,	TRUE	},
    {	"over the head",	WEAR_HEAD,	TRUE	},
    {	"on the legs",		WEAR_LEGS,	TRUE	},
    {	"on the feet",		WEAR_FEET,	TRUE	},
    {	"on the hands",		WEAR_HANDS,	TRUE	},
    {	"on the arms",		WEAR_ARMS,	TRUE	},
    {	"as a shield",		WEAR_SHIELD,	TRUE	},
    {	"about the shoulders",	WEAR_ABOUT,	TRUE	},
    {	"around the waist",	WEAR_WAIST,	TRUE	},
    {	"on the left wrist",	WEAR_WRIST_L,	TRUE	},
    {	"on the right wrist",	WEAR_WRIST_R,	TRUE	},
    {	"wielded",		WEAR_WIELD,	TRUE	},
    {	"held in the hands",	WEAR_HOLD,	TRUE	},
//    {	"floating nearby",	WEAR_FLOAT,	TRUE	},
    {	NULL,			0	      , 0	}
};


const struct flag_type wear_loc_flags[] =
{
    {	"none",		WEAR_NONE,	TRUE	},
    {	"light",	WEAR_LIGHT,	TRUE	},
    {	"lfinger",	WEAR_FINGER_L,	TRUE	},
    {	"rfinger",	WEAR_FINGER_R,	TRUE	},
    {	"neck1",	WEAR_NECK_1,	TRUE	},
    {	"neck2",	WEAR_NECK_2,	TRUE	},
    {	"body",		WEAR_BODY,	TRUE	},
    {	"head",		WEAR_HEAD,	TRUE	},
    {	"legs",		WEAR_LEGS,	TRUE	},
    {	"feet",		WEAR_FEET,	TRUE	},
    {	"hands",	WEAR_HANDS,	TRUE	},
    {	"arms",		WEAR_ARMS,	TRUE	},
    {	"shield",	WEAR_SHIELD,	TRUE	},
    {	"about",	WEAR_ABOUT,	TRUE	},
    {	"waist",	WEAR_WAIST,	TRUE	},
    {	"lwrist",	WEAR_WRIST_L,	TRUE	},
    {	"rwrist",	WEAR_WRIST_R,	TRUE	},
    {	"wielded",	WEAR_WIELD,	TRUE	},
    {	"hold",		WEAR_HOLD,	TRUE	},
//    {	"floating",	WEAR_FLOAT,	TRUE	},
    {	NULL,		0,		0	}
};
const 	struct flag_type weapon_flags[]=
{
    { 	"hit",		0,		TRUE	},  /*  0 */
    {	"slice", 	1,		TRUE	},	
    {   "stab",		2,		TRUE	},
    {	"slash",	3,		TRUE	},
    {	"whip",		4,		TRUE	},
    {   "claw",		5,		TRUE	},  /*  5 */
    {	"blast",	6,		TRUE	},
    {   "pound",	7,		TRUE	},
    {	"crush",	8,		TRUE	},
    {   "grep",		9,		TRUE	},
    {	"bite",		10,		TRUE	},  /* 10 */
    {   "pierce",	11,		TRUE	},
    {   "suction",	12,		TRUE	},
    {	"beating",	13,		TRUE	},
    {   "digestion",	14,		TRUE	},
    {	"charge",	15,		TRUE	},  /* 15 */
    { 	"slap",		16,		TRUE	},
    {	"punch",	17,		TRUE	},
    {	"wrath",	18,		TRUE	},
    {	"magic",	19,		TRUE	},
    {   "divinepower",	20,		TRUE	},  /* 20 */
    {	"cleave",	21,		TRUE	},
    {	"scratch",	22,		TRUE	},
    {   "peckpierce",	23,		TRUE	},
    {   "peckbash",	24,		TRUE	},
    {   "chop",		25,		TRUE	},  /* 25 */
    {   "sting",	26,		TRUE	},
    {   "smash",	27,		TRUE	},
    {   "shockingbite",28,		TRUE	},
    {	"flamingbite", 29,		TRUE	},
    {	"freezingbite", 30,		TRUE	},  /* 30 */
    {	"acidicbite", 	31,		TRUE	},
    {	"chomp",	32,		TRUE	},
    {  	"lifedrain",	33,		TRUE	},
    {   "thrust",	34,		TRUE	},
    {   "slime",	35,		TRUE	},
    {	"shock",	36,		TRUE	},
    {   "thwack",	37,		TRUE	},
    {   "flame",	38,		TRUE	},
    {   "chill",	39,		TRUE	},
    {   NULL,		0,		0	}
};

const struct flag_type container_flags[] =
{
    {	"closeable",		1,		TRUE	},
    {	"pickproof",		2,		TRUE	},
    {	"closed",		4,		TRUE	},
    {	"locked",		8,		TRUE	},
    {	"puton",		16,		TRUE	},
    {	NULL,			0,		0	}
};

/*****************************************************************************
                      ROM - specific tables:
 ****************************************************************************/



/*
const struct flag_type ac_type[] =
{
    {   "pierce",        AC_PIERCE,            TRUE    },
    {   "bash",          AC_BASH,              TRUE    },
    {   "slash",         AC_SLASH,             TRUE    },
    {   "exotic",        AC_EXOTIC,            TRUE    },
    {   NULL,              0,                    0       }
};
*/
/*
const struct flag_type size_flags[] =
{
    {   "tiny",          SIZE_TINY,            TRUE    },
    {   "small",         SIZE_SMALL,           TRUE    },
    {   "medium",        SIZE_MEDIUM,          TRUE    },
    {   "large",         SIZE_LARGE,           TRUE    },
    {   "huge",          SIZE_HUGE,            TRUE    },
    {   "giant",         SIZE_GIANT,           TRUE    },
    {   NULL,              0,                    0       },
};
*/

const struct flag_type weapon_class[] =
{
    {   "exotic",        0,                    TRUE    },
    {   "sword",         1,                    TRUE    },
    {   "dagger",        2,                    TRUE    },
    {   "spear",         3,                    TRUE    },
    {   "mace",          4,                    TRUE    },
    {   "axe",           5,                    TRUE    },
    {   "flail",         6,                    TRUE    },
    {   "whip",          7,                    TRUE    },
    {   "polearm",       7,                    TRUE    },
    {   NULL,              0,                    0       }
};


/*
const struct flag_type weapon_type2[] =
{
    {   "none",		 0,			TRUE   },
    {   "flaming",       WEAPON_FLAMING,       TRUE    },
    {   "frost",         WEAPON_FROST,         TRUE    },
    {   "vampiric",      WEAPON_VAMPIRIC,      TRUE    },
    {   "sharp",         WEAPON_SHARP,         TRUE    },
    {   "vorpal",        WEAPON_VORPAL,        TRUE    },
    {   "twohands",     WEAPON_TWO_HANDS,     TRUE    },
    {	"shocking",	 WEAPON_SHOCKING,      TRUE    },
    {	"poison",	WEAPON_POISON,		TRUE	},
    {   NULL,              0,                    0       }
};
*/

/*
const struct flag_type res_flags[] =
{
    {	"summon",	 RES_SUMMON,		TRUE	},
    {   "charm",         RES_CHARM,            TRUE    },
    {   "magic",         RES_MAGIC,            TRUE    },
    {   "weapon",        RES_WEAPON,           TRUE    },
    {   "bash",          RES_BASH,             TRUE    },
    {   "pierce",        RES_PIERCE,           TRUE    },
    {   "slash",         RES_SLASH,            TRUE    },
    {   "fire",          RES_FIRE,             TRUE    },
    {   "cold",          RES_COLD,             TRUE    },
    {   "lightning",     RES_LIGHTNING,        TRUE    },
    {   "acid",          RES_ACID,             TRUE    },
    {   "poison",        RES_POISON,           TRUE    },
    {   "negative",      RES_NEGATIVE,         TRUE    },
    {   "holy",          RES_HOLY,             TRUE    },
    {   "energy",        RES_ENERGY,           TRUE    },
    {   "mental",        RES_MENTAL,           TRUE    },
    {   "disease",       RES_DISEASE,          TRUE    },
    {   "drowning",      RES_DROWNING,         TRUE    },
    {   "light",         RES_LIGHT,            TRUE    },
    {	"sound",	RES_SOUND,		TRUE	},
    {	"wood",		RES_WOOD,		TRUE	},
    {	"iron",		RES_IRON,		TRUE	},
    {   NULL,          0,            0    }
};
*/
/*
const struct flag_type vuln_flags[] =
{
    {	"summon",	 VULN_SUMMON,		TRUE	},
    {	"charm",	VULN_CHARM,		TRUE	},
    {   "magic",         VULN_MAGIC,           TRUE    },
    {   "weapon",        VULN_WEAPON,          TRUE    },
    {   "bash",          VULN_BASH,            TRUE    },
    {   "pierce",        VULN_PIERCE,          TRUE    },
   {   "slash",         VULN_SLASH,           TRUE    },
  {   "fire",          VULN_FIRE,            TRUE    },
    {   "cold",          VULN_COLD,            TRUE    },
    {   "lightning",     VULN_LIGHTNING,       TRUE    },
    {   "acid",          VULN_ACID,            TRUE    },
    {   "poison",        VULN_POISON,          TRUE    },
    {   "negative",      VULN_NEGATIVE,        TRUE    },
    {   "holy",          VULN_HOLY,            TRUE    },
    {   "energy",        VULN_ENERGY,          TRUE    },
    {   "mental",        VULN_MENTAL,          TRUE    },
    {   "disease",       VULN_DISEASE,         TRUE    },
    {   "drowning",      VULN_DROWNING,        TRUE    },
    {   "light",         VULN_LIGHT,           TRUE    },
    {	"sound",	 VULN_SOUND,		TRUE	},
    {   "wood",          VULN_WOOD,            TRUE    },
   {   "iron",          VULN_IRON,            TRUE    },
    {   NULL,              0,                    0       }
};
*/

const struct flag_type material_type[] =    /* not yet implemented */
{
    {   "none",          0,            TRUE    },
    {   NULL,              0,            0       }
};


const struct flag_type position_flags[] =
{
    {   "dead",           POS_DEAD,            FALSE   },
    {   "mortal",         POS_MORTAL,          FALSE   },
    {   "incap",          POS_INCAP,           FALSE   },
    {   "stunned",        POS_STUNNED,         FALSE   },
    {   "sleeping",       POS_SLEEPING,        TRUE    },
    {   "resting",        POS_RESTING,         TRUE    },
    {   "sitting",        POS_SITTING,         TRUE    },
    {   "fighting",       POS_FIGHTING,        FALSE   },
    {   "standing",       POS_STANDING,        TRUE    },
    {   NULL,              0,                    0       }
};
/*
const struct flag_type portal_flags[]=
{
    {   "normal_exit",	  GATE_NORMAL_EXIT,	TRUE	},
    {	"no_curse",	  GATE_NOCURSE,		TRUE	},
    {   "go_with",	  GATE_GOWITH,		TRUE	},
    {   "buggy",	  GATE_BUGGY,		TRUE	},
    {	"random",	  GATE_RANDOM,		TRUE	},
    {   NULL,		  0,			0	}
};
*/
/*
const struct flag_type furniture_flags[]=
{
    {	"none",		  0,			TRUE	},
    {   "stand_at",	  STAND_AT,		TRUE	},
    {	"stand_on",	  STAND_ON,		TRUE	},
    {	"stand_in",	  STAND_IN,		TRUE	},
    {	"sit_at",	  SIT_AT,		TRUE	},
    {	"sit_on",	  SIT_ON,		TRUE	},
    {	"sit_in",	  SIT_IN,		TRUE	},
    {	"rest_at",	  REST_AT,		TRUE	},
    {	"rest_on",	  REST_ON,		TRUE	},
    {	"rest_in",	  REST_IN,		TRUE	},
    {	"sleep_at",	  SLEEP_AT,		TRUE	},
    {	"sleep_on",	  SLEEP_ON,		TRUE	},
    {	"sleep_in",	  SLEEP_IN,		TRUE	},
    {	"put_at",	  PUT_AT,		TRUE	},
    {	"put_on",	  PUT_ON,		TRUE	},
    {	"put_in",	  PUT_IN,		TRUE	},
    {	"put_inside",	  PUT_INSIDE,		TRUE	},
    {	NULL,		  0,			0	}
};

*/

const struct flag_type act_flags[] =
{
    {   "npc",                  A,      FALSE   },
    {   "sentinel",             B,      TRUE    },
    {   "scavenger",            C,      TRUE    },
    {   "aggressive",           F,      TRUE    },
    {   "stay_area",            G,      TRUE    },
    {   "wimpy",                H,      TRUE    },
    {   "pet",                  I,      TRUE    },
    {   "train",                J,      TRUE    },
    {   "practice",             K,      TRUE    },
    {   "undead",               O,      TRUE    },
    {   "cleric",               Q,      TRUE    },
    {   "mage",                 R,      TRUE    },
    {   "thief",                S,      TRUE    },
    {   "warrior",              T,      TRUE    },
    {   "noalign",              U,      TRUE    },
    {   "nopurge",              V,      TRUE    },
    {   "outdoors",             W,      TRUE    },
    {   "indoors",              Y,      TRUE    },
    {   NULL,                   0,      FALSE   }
};


const struct flag_type affect_flags[] =
{
    {   "blind",                A,      TRUE    },
    {   "invisible",            B,      TRUE    },
    {   "detect_evil",          C,      TRUE    },
    {   "detect_invis",         D,      TRUE    },
    {   "detect_magic",         E,      TRUE    },
    {   "detect_hidden",        F,      TRUE    },
    {   "detect_good",          G,      TRUE    },
    {   "sanctuary",            H,      TRUE    },
    {   "faerie_fire",          I,      TRUE    },
    {   "infrared",             J,      TRUE    },
    {   "curse",                K,      TRUE    },
    {   "poison",               M,      TRUE    },
    {   "protect_evil",         N,      TRUE    },
    {   "protect_good",         O,      TRUE    },
    {   "sneak",                P,      TRUE    },
    {   "hide",                 Q,      TRUE    },
    {   "sleep",                R,      TRUE    },
    {   "charm",                S,      TRUE    },
    {   "flying",               T,      TRUE    },
    {   "pass_door",            U,      TRUE    },
    {   "haste",                V,      TRUE    },
    {   "calm",                 W,      TRUE    },
    {   "plague",               X,      TRUE    },
    {   "weaken",               Y,      TRUE    },
    {   "dark_vision",          Z,      TRUE    },
    {   NULL,                   0,      0       }
};

