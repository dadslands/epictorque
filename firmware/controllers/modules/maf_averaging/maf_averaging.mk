MODULES_INC += $(PROJECT_DIR)/controllers/modules/maf_averaging
MODULES_CPPSRC += $(PROJECT_DIR)/controllers/modules/maf_averaging/maf_averaging.cpp
MODULES_INCLUDE += \#include "maf_averaging.h"\n
MODULES_LIST += MafAveragingModule,

DDEFS += -DMODULE_MAF_AVERAGING
# DDEFS += -DMAP_MODULE_LOGGING