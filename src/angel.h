#include "var.h"

#define IS_ANGPOWER(ch, sn)     (IS_SET((ch)->pcdata->powers[APOWER_FLAGS], (sn)))
#define IS_ANGAFF(ch, sn)       (IS_SET((ch)->pcdata->powers[APOWER_CURRENT], (sn)))

#define ANGEL_CURRENT                 (DC)
#define ANGEL_TOTAL                   (DT)
#define ANGEL_POWER		      (DB)
 
#define APOWER_FLAGS                  0
#define APOWER_CURRENT                (A)
/* Angel Powers */
#define ANG_SPREAD                     0
 
#define ANG_WINGS                     (A)
#define ANG_TOUGHNESS                 (B)
#define ANG_STRENGTH                  (C)
#define ANG_GODLYSIGHT                (D)
#define ANG_SCRY                      (E)
#define ANG_READAURA                  (F)
#define ANG_SPEED                     (G)
#define ANG_HALO                      (H)
#define ANG_MULTIARM                  (I)
#define ANG_PROTECTION_OF_GOD         (J)
#define ANG_WRAITH_OF_GOD             (K)
#define ANG_TRUEFORM                  (L)
#define ANG_SHIELD_OF_GOD             (M)
#define ANG_ETHERFORM                 (N)
