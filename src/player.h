/***************************************************************************
 *  Original Diku Mud copyright (C) 1990, 1991 by Sebastian Hammer,        *
 *  Michael Seifert, Hans Henrik St{rfeldt, Tom Madsen, and Katja Nyboe.   *
 *                                                                         *
 *  Merc Diku Mud improvments copyright (C) 1992, 1993 by Michael          *
 *  Chastain, Michael Quan, and Mitchell Tse.                              *
 *                                                                         *
 *  In order to use any part of this Merc Diku Mud, you must comply with   *
 *  both the original Diku license in 'license.doc' as well the Merc       *
 *  license in 'license.txt'.  In particular, you may not remove either of *
 *  these copyright notices.                                               *
 *                                                                         *
 *  Much time and thought has gone into this software and you are          *
 *  benefitting.  We hope that you share your changes too.  What goes      *
 *  around, comes around.                                                  *
 ***************************************************************************/

/* Special Bits */

#define SPC_CHAMPION	1 /* PLR_CHAMPION 4 */
#define SPC_DEMON_LORD	2 /* OLD_DEMON Flag */
#define SPC_WOLFMAN	4 /* old PLR_WOLFMAN */
#define SPC_PRINCE      8 /* old EXTRA_PRINCE */
#define SPC_SIRE	16 /* Old EXTRA_SIRE */
#define SPC_ANARCH      32 /* old extra_anarch */
#define SPC_INCONNU     64 /* old extra_inconnu */
#define SPC_ROGUE      128
/* Class Bits */
#define CLASS_DEMON	 1 /* PLR_DEMON 2 */
#define CLASS_MAGE	 2 
#define CLASS_WEREWOLF	 4 /* PLR_WEREWOLF */
#define CLASS_VAMPIRE	 8 
#define CLASS_HIGHLANDER 16 /* EXTRA_HIGHLANDER */
#define CLASS_DROWNEW	 32
#define CLASS_NINJA      64
#define CLASS_PALADIN   128
#define CLASS_REVNANT      256
#define CLASS_ANGEL     512
#define CLASS_DRAGON   1024
#define CLASS_ALIEN    2048
#define CLASS_DEALER   4096
#define CLASS_HYDRA    8192
#define CLASS_SHATAN   16384
#define CLASS_ILLUSIONIST 32768

/* Shatan Powers */
#define SHATAN_POWER	   0
#define SHATAN_CURRENT     1 /* POWER_CURRENT 0*/
#define SHATAN_TOTAL       9 /* POWER_TOTAL   1*/

/* Power Bits for Monks */
#define MPOWER_POWER              2 /* Monk Power */
#define PMONK     0

/* Powers/Principles for Ninjas */
#define NPOWER_OPTICAL	      1
#define NPOWER_TACTICAL	      2
#define NPOWER_COMBAT	      4
#define NPOWER_BALLISTICS           8

/* Paladin Bits */
/* Stats */
#define PALADIN_CURRENT		      8	/* POWER_CURRENT 0*/
#define PALADIN_TOTAL		      9	/* POWER_TOTAL   1*/
#define PALADIN_POWER		     10 /* TOTAL ARMOUR BOUNS */

/* Powers */
#define PPOWER_FLAGS		      0 /* C_POWERS  1 */
#define PPOWER_CURRENT		      1 /* C_CURRENT 2 */

#define PALADIN_SCRY              1
#define PALADIN_CHARGE            2
#define PALADIN_SPEED             4
#define PALADIN_TOUGHNESS         8
#define PALADIN_HOLYBLESS        16
#define PALADIN_JOUST            32
#define PALADIN_HEAL             64

/* 
 * Bits For Highlanders
 */
#define HPOWER_WPNSKILL 0

/*
 * Bits for Hydra's
 */
#define DISC_HYDRA_POWER	0
#define DISC_HYDRA_HEADS	1
#define DISC_HYDRA_ACCUR	2
#define DISC_HYDRA_TWIRL	4
#define DISC_HYDRA_REGEN      8

/*
 * Bits for Illusionists
 */
#define ILLU_POWER_AWARE 	0
#define ILLU_POWER_CREATE	1
#define ILLU_POWER_MORPH	2
#define ILLU_POWER_ATTACK	4

/* 
 * Bits For Mages
 */
#define MPOWER_RUNE0	0
#define MPOWER_RUNE1	1
#define MPOWER_RUNE2	2
#define MPOWER_RUNE3	3
#define MPOWER_RUNE4	4

/*
 * Bits for Werewolves 
 */
/* Stats */

#define UNI_GEN        	0 /* vampgen */
#define UNI_AFF		1 /* vampaff */
#define UNI_CURRENT	2 /* vamppass */
#define UNI_RAGE	3 /* ch->wolf = how big rage they are in*/
#define UNI_FORM0      	4/* wolfform[0] */
#define UNI_FORM1      	5 /* wolfform[1] */

#define	WOLF_POLYAFF	6

/* 
 * Powers 
 * Totems for werewolves.
 */

#define WPOWER_TIGER	      11	
#define WPOWER_MANTIS	      0
#define WPOWER_BEAR	      1
#define WPOWER_LYNX	      2
#define WPOWER_GAIA	      12
#define WPOWER_BOAR	      3
#define WPOWER_OWL	      4
#define WPOWER_SPIDER	      5
#define WPOWER_WOLF	      6
#define WPOWER_HAWK	      7
#define WPOWER_SILVER	     10


#define MOOGLE_DANCES 8
/*
 * Bits for Demonic Champions.
 */

/*Stats*/

#define DEMON_CURRENT		      8	/* POWER_CURRENT 0*/
#define DEMON_TOTAL		      9	/* POWER_TOTAL   1*/
#define DEMON_POWER		     10 /* TOTAL ARMOUR BOUNS */
#define NINJA_KI               8   /* Ninja Ki is 8 */

/*Powers*/
#define DPOWER_FLAGS		      0 /* C_POWERS  1 */
#define DPOWER_CURRENT		      1 /* C_CURRENT 2 */
#define DPOWER_HEAD		      2 /* C_HEAD    3 */
#define DPOWER_TAIL		      3 /* C_TAIL    4 */
#define DPOWER_OBJ_VNUM		      4 /* DISC[10]  5 */

#define DEM_UNFOLDED		      1

#define DEM_FANGS		      1
#define DEM_CLAWS		      2
#define DEM_HORNS		      4
#define DEM_TAIL		      8
#define DEM_HOOVES		     16
#define DEM_EYES		     32
#define DEM_WINGS		     64
#define DEM_MIGHT		    128
#define DEM_TOUGH		    256
#define DEM_SPEED		    512
#define DEM_TRAVEL		   1024
#define DEM_SCRY		   2048
#define DEM_SHADOWSIGHT		   4096
/* Object Powers */
#define DEM_MOVE		   8192   /* 1 Can roll as an object */
#define DEM_LEAP		   16384   /* 2 Can leap out of someone's hands */
#define DEM_MAGIC		   32768   /* 4 Can cast spells as an object */
#define DEM_LIFESPAN		  65536   /* 8 Can change lifespan */
/* New Powers */ 
#define DEM_DEMONFORM            131072
#define DEM_DRAIN		 262144
#define DEM_FIRE		 524288

#define HEAD_NORMAL		      0
#define HEAD_WOLF		      1
#define HEAD_EAGLE		      2
#define HEAD_LION		      4
#define HEAD_SNAKE		      8

#define TAIL_NONE		      0
#define TAIL_POISONOUS		      1
#define TAIL_SCORPION		      2



/* Moogle Dances */

#define DANCE_SONG 	1
#define DANCE_SUITE	2
#define DANCE_ARIA	4
#define DANCE_SONATA	8
#define DANCE_BLUES	16
#define DANCE_RONDO	32
#define DANCE_REQUIEM	64
#define DANCE_JAZZ	128

