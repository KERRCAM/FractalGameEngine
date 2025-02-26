
struct vector2D {
    int x;
    int y;
} vector2D;

struct player {
    float x;
    float y;
    float width;
    float height;
} player;

void player_init();

struct vector2D playerMovement(struct player *player);