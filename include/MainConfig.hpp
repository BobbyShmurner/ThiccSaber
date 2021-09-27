#pragma once

#include "config-utils/shared/config-utils.hpp"

DECLARE_CONFIG(MainConfig,
    CONFIG_VALUE(ChangeNoteSizes, bool, "ChangeNoteSizes", true);
    CONFIG_VALUE(ChangeBombSizes, bool, "ChangeBombSizes", true);

    CONFIG_VALUE(Width, float, "Width", 1);
    CONFIG_VALUE(Height, float, "Height", 1);
    CONFIG_VALUE(Depth, float, "Depth", 1);

    CONFIG_INIT_FUNCTION(
        CONFIG_INIT_VALUE(ChangeNoteSizes);
        CONFIG_INIT_VALUE(ChangeBombSizes);
        
        CONFIG_INIT_VALUE(Width);
        CONFIG_INIT_VALUE(Height);
        CONFIG_INIT_VALUE(Depth);
    )
)