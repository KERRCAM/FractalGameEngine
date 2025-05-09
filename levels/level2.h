#include "../src/include/constants.h"

int sectors[MAX_SECTORS][7] = {
    {0, 80, 0, 0, 1, 1825.000000, 1441.000000},
    {0, 80, 0, 0, 1, 3875.000000, 1200.000000},
    {0, 80, 0, 0, 1, 6115.000000, 1443.000000},
    {0, 80, 0, 0, 1, 6025.000000, 2650.000000},
    {0, 80, 0, 0, 1, 3968.000000, 3431.000000},
    {0, 80, 0, 0, 1, 1612.000000, 3243.000000},
    {-1, 80, 0, 0, 0, 0.000000, 0.000000},
    {-1, 80, 0, 0, 0, 0.000000, 0.000000},
    {-1, 80, 0, 0, 0, 0.000000, 0.000000},
    {-1, 80, 0, 0, 0, 0.000000, 0.000000},
    {-1, 80, 0, 0, 0, 0.000000, 0.000000},
    {-1, 80, 0, 0, 0, 0.000000, 0.000000},
};

int walls[MAX_SECTORS][MAX_WALLS][6] = {
    {
    {1475, 100, 125, 100, 2, 1},
    {125, 100, 125, 1175, 6, 1},
    {125, 1175, 575, 1175, 8, 1},
    {925, 1175, 1500, 1175, 9, 1},
    {1500, 1175, 1500, 750, 2, 1},
    {1500, 450, 1475, 100, 3, 1},
    {-1, -1, -1, -1, 0, 0},
    {-1, -1, -1, -1, 0, 0},
    {-1, -1, -1, -1, 0, 0},
    {-1, -1, -1, -1, 0, 0},
    {-1, -1, -1, -1, 0, 0},
    {-1, -1, -1, -1, 0, 0},
    },

    {
    {2375, 450, 1500, 450, 8, 1},
    {1500, 750, 2375, 750, 9, 1},
    {-1, -1, -1, -1, 0, 0},
    {-1, -1, -1, -1, 0, 0},
    {-1, -1, -1, -1, 0, 0},
    {-1, -1, -1, -1, 0, 0},
    {-1, -1, -1, -1, 0, 0},
    {-1, -1, -1, -1, 0, 0},
    {-1, -1, -1, -1, 0, 0},
    {-1, -1, -1, -1, 0, 0},
    {-1, -1, -1, -1, 0, 0},
    {-1, -1, -1, -1, 0, 0},
    },

    {
    {2375, 750, 2500, 1250, 2, 1},
    {2500, 1250, 2850, 1250, 6, 1},
    {3175, 1250, 3450, 1250, 8, 1},
    {3450, 1250, 3600, 775, 8, 1},
    {3600, 775, 3600, 450, 9, 1},
    {3600, 450, 3450, 100, 2, 1},
    {3450, 100, 2475, 100, 3, 1},
    {2475, 100, 2375, 450, 2, 1},
    {-1, -1, -1, -1, 0, 0},
    {-1, -1, -1, -1, 0, 0},
    {-1, -1, -1, -1, 0, 0},
    {-1, -1, -1, -1, 0, 0},
    },

    {
    {2850, 1250, 2850, 1400, 2, 1},
    {3175, 1400, 3175, 1250, 2, 1},
    {-1, -1, -1, -1, 0, 0},
    {-1, -1, -1, -1, 0, 0},
    {-1, -1, -1, -1, 0, 0},
    {-1, -1, -1, -1, 0, 0},
    {-1, -1, -1, -1, 0, 0},
    {-1, -1, -1, -1, 0, 0},
    {-1, -1, -1, -1, 0, 0},
    {-1, -1, -1, -1, 0, 0},
    {-1, -1, -1, -1, 0, 0},
    {-1, -1, -1, -1, 0, 0},
    },

    {
    {3650, 2075, 3650, 1400, 8, 1},
    {3650, 1400, 3175, 1400, 2, 1},
    {2850, 1400, 1650, 1175, 9, 1},
    {1650, 1175, 1475, 1400, 6, 1},
    {1475, 1400, 975, 1400, 8, 1},
    {975, 1400, 975, 1625, 9, 1},
    {975, 1900, 975, 2075, 3, 1},
    {975, 2075, 1450, 2075, 2, 1},
    {1450, 2075, 1650, 1875, 6, 1},
    {1650, 1875, 2100, 1875, 8, 1},
    {2100, 1875, 2250, 2075, 9, 1},
    {2250, 2075, 3650, 2075, 6, 1},
    },

    {
    {575, 1175, 575, 1925, 7, 1},
    {575, 1925, 975, 1900, 8, 1},
    {975, 1625, 925, 1625, 2, 1},
    {925, 1625, 925, 1175, 0, 1},
    {-1, -1, -1, -1, 0, 0},
    {-1, -1, -1, -1, 0, 0},
    {-1, -1, -1, -1, 0, 0},
    {-1, -1, -1, -1, 0, 0},
    {-1, -1, -1, -1, 0, 0},
    {-1, -1, -1, -1, 0, 0},
    {-1, -1, -1, -1, 0, 0},
    {-1, -1, -1, -1, 0, 0},
    },

    {
    {-1, -1, -1, -1, 0, 0},
    {-1, -1, -1, -1, 0, 0},
    {-1, -1, -1, -1, 0, 0},
    {-1, -1, -1, -1, 0, 0},
    {-1, -1, -1, -1, 0, 0},
    {-1, -1, -1, -1, 0, 0},
    {-1, -1, -1, -1, 0, 0},
    {-1, -1, -1, -1, 0, 0},
    {-1, -1, -1, -1, 0, 0},
    {-1, -1, -1, -1, 0, 0},
    {-1, -1, -1, -1, 0, 0},
    {-1, -1, -1, -1, 0, 0},
    },

    {
    {-1, -1, -1, -1, 0, 0},
    {-1, -1, -1, -1, 0, 0},
    {-1, -1, -1, -1, 0, 0},
    {-1, -1, -1, -1, 0, 0},
    {-1, -1, -1, -1, 0, 0},
    {-1, -1, -1, -1, 0, 0},
    {-1, -1, -1, -1, 0, 0},
    {-1, -1, -1, -1, 0, 0},
    {-1, -1, -1, -1, 0, 0},
    {-1, -1, -1, -1, 0, 0},
    {-1, -1, -1, -1, 0, 0},
    {-1, -1, -1, -1, 0, 0},
    },

    {
    {-1, -1, -1, -1, 0, 0},
    {-1, -1, -1, -1, 0, 0},
    {-1, -1, -1, -1, 0, 0},
    {-1, -1, -1, -1, 0, 0},
    {-1, -1, -1, -1, 0, 0},
    {-1, -1, -1, -1, 0, 0},
    {-1, -1, -1, -1, 0, 0},
    {-1, -1, -1, -1, 0, 0},
    {-1, -1, -1, -1, 0, 0},
    {-1, -1, -1, -1, 0, 0},
    {-1, -1, -1, -1, 0, 0},
    {-1, -1, -1, -1, 0, 0},
    },

    {
    {-1, -1, -1, -1, 0, 0},
    {-1, -1, -1, -1, 0, 0},
    {-1, -1, -1, -1, 0, 0},
    {-1, -1, -1, -1, 0, 0},
    {-1, -1, -1, -1, 0, 0},
    {-1, -1, -1, -1, 0, 0},
    {-1, -1, -1, -1, 0, 0},
    {-1, -1, -1, -1, 0, 0},
    {-1, -1, -1, -1, 0, 0},
    {-1, -1, -1, -1, 0, 0},
    {-1, -1, -1, -1, 0, 0},
    {-1, -1, -1, -1, 0, 0},
    },

    {
    {-1, -1, -1, -1, 0, 0},
    {-1, -1, -1, -1, 0, 0},
    {-1, -1, -1, -1, 0, 0},
    {-1, -1, -1, -1, 0, 0},
    {-1, -1, -1, -1, 0, 0},
    {-1, -1, -1, -1, 0, 0},
    {-1, -1, -1, -1, 0, 0},
    {-1, -1, -1, -1, 0, 0},
    {-1, -1, -1, -1, 0, 0},
    {-1, -1, -1, -1, 0, 0},
    {-1, -1, -1, -1, 0, 0},
    {-1, -1, -1, -1, 0, 0},
    },

    {
    {-1, -1, -1, -1, 0, 0},
    {-1, -1, -1, -1, 0, 0},
    {-1, -1, -1, -1, 0, 0},
    {-1, -1, -1, -1, 0, 0},
    {-1, -1, -1, -1, 0, 0},
    {-1, -1, -1, -1, 0, 0},
    {-1, -1, -1, -1, 0, 0},
    {-1, -1, -1, -1, 0, 0},
    {-1, -1, -1, -1, 0, 0},
    {-1, -1, -1, -1, 0, 0},
    {-1, -1, -1, -1, 0, 0},
    {-1, -1, -1, -1, 0, 0},
    },

};
