#pragma once

#include "quantum.h"

/* key matrix size */
#define MATRIX_ROWS 2
#define MATRIX_COLS 3

#define LAYOUT(K00, K01, K02, K10, K11, K12)
    {
        {K00, K01, K02},
        {K10, K11, K12 }
    }
