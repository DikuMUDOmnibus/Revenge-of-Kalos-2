#include "var.h"

#define IS_ALIPOWER(ch, sn)     (IS_SET((ch)->xkilla->aliens, (sn)))
/*
#define IS_ALIAFF(ch, sn)       (IS_SET((ch)->xkilla->aliens[ALPOWER_CURRENT], (sn)))
*/

#define ALIEN_PLANET                  (DC)
#define ALIEN_TOTAL                   (DT)
 
#define ALPOWER_FLAGS                  0
#define ALPOWER_CURRENT                0
/* Alien Powers */
#define ALI_SPEED		(A)
#define ALI_TOUGH		(B)
#define ALI_PROBE		(C)
#define ALI_BEAM		(D)
#define ALI_RADAR		(E)
#define ALI_PYRO		(F)
#define ALI_BIOMORPH		(G)
#define ALI_SPACEEYES           (H)

/* Abc Order */
/* Commands */
DECLARE_DO_FUN( do_abduct	);
DECLARE_DO_FUN( do_aclass       );
DECLARE_DO_FUN( do_aliencreate	);
DECLARE_DO_FUN( do_alienpowers	);
DECLARE_DO_FUN( do_aliens	);
DECLARE_DO_FUN( do_autoconsume	);
DECLARE_DO_FUN( do_beam		);
DECLARE_DO_FUN( do_biomorph	);
DECLARE_DO_FUN( do_brood	);
DECLARE_DO_FUN( do_consume	);
DECLARE_DO_FUN( do_planet	);
DECLARE_DO_FUN( do_prince	);
DECLARE_DO_FUN( do_probe	);
DECLARE_DO_FUN( do_ptoken	);
DECLARE_DO_FUN( do_pyrokinesis	);
DECLARE_DO_FUN( do_radar	);
DECLARE_DO_FUN( do_space	);
DECLARE_DO_FUN( do_spaceeyes    );
/* End */


