
struct vector2D {
    int x;
    int y;
};

struct player {
    float x;
    float y;
    float width;
    float height;
} player;

struct player player_init();

struct vector2D playerMovement(struct player *player);