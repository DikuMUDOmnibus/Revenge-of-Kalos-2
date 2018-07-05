#include "var.h"

#define IS_DPOWER(ch, sn)       (IS_SET((ch)->xkilla->drows, (sn)))     

/* Drow Powers */
#define DROW_FOUREYES               (A)
#define DROW_TOUGHEN		    (B)
#define DROW_OFFENSE		    (C)

/* Abc Order */
/* Commands */
DECLARE_DO_FUN( do_foureyes	);
DECLARE_DO_FUN( do_infect       );
DECLARE_DO_FUN( do_inherit      );
DECLARE_DO_FUN( do_toughen	);
DECLARE_DO_FUN( do_webtalk	);
/* End */
