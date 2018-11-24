#include <stddef.h>
#include <SDL2/SDL.h>

enum {
    Hades_MaxTitleLength = 1000, /** Maximum buffer length for a game title */
    Hades_MaxTextureCount = 200,
    Hades_MaxSpriteBuckets = 149
};

typedef struct Hades_Game Hades_Game;
typedef struct Hades_Sprite_ Hades_Sprite_;
typedef int Hades_Sprite; /** Front-end sprite */
const Hades_Sprite Hades_NullSprite;    /** null sprite */

// --- Sprite ---

/** defined in "hades_structure.h"
 * Hades_Sprite_
 *  used for rendering a texture
 *  back-end sprite data structure
 *
 * Fields
 *       id - used for hashing into sprite map
 *  texture - index of texture
 *      src - where on the texture to copy
 *      dst - where to render sprite
 *     next - pointer to next sprite in bucket
 */
struct Hades_Sprite_ {
    Hades_Sprite id;
    int texture;
    SDL_Rect* src, * dst;
    Hades_Sprite_* next;
};

/** Defined in "hades_structure.h"
 *  Hades_Game
 *
 * Used to run a game
 *
 *  Fields
 *
 *             char title[] - title of the game window
 *      SDL_Rect screen_dim - dimensions of the game window
 *       SDL_Window* window - points to the game window
 *   SDL_Renderer* renderer - points to the renderer
 */
struct Hades_Game {
    char title[Hades_MaxTitleLength];
    SDL_Rect screen_dim;

    SDL_Window* window;
    SDL_Renderer* renderer;

    size_t current_id;

    SDL_Texture* textures[Hades_MaxTextureCount];
    size_t texture_count;

    Hades_Sprite_* sprites[Hades_MaxSpriteBuckets];
    size_t sprite_count;

    void (*Start)(Hades_Game*);
};

