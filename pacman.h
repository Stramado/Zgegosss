#ifndef PACMAN_H
#define PACMAN_H

// Define the default data directory and levels file location
#ifndef DATAROOTDIR
#define DATAROOTDIR "/usr/local/share"
#endif

#define LEVELS_FILE DATAROOTDIR "/pacman/Levels/level__.dat"

// Constants
#define MAX_LIVES 5  // Maximum lives a player can have
#define MAX_LEVELS 10 // Maximum number of levels
#define BOARD_ROWS 31 // Number of rows in the board
#define BOARD_COLS 28 // Number of columns in the board

// Initial game variables
char LevelFile[] = LEVELS_FILE; // Location of default levels
int FreeLife = 1000;            // Points for a free life
int Points = 0;                 // Initial points
int Lives = 3;                  // Initial lives
int HowSlow = 3;                // Speed modifier for vulnerable ghosts
int SpeedOfGame = 175;          // Delay in milliseconds for game speed

// Enumerations
typedef enum {
    EMPTY,
    WALL,
    DOT,
    ENERGIZER,
    GHOST,
    PACMAN
} TileType;

// Structures
typedef struct {
    int x, y;           // Position on the board
    int dx, dy;         // Direction of movement
    int is_vulnerable;  // Is the ghost vulnerable
} Ghost;

typedef struct {
    int x, y;  // Position on the board
    int dx, dy; // Direction of movement
} Pacman;

// Function prototypes
void initializeGame();
void loadLevel(int level);
void renderBoard();
void updateGame();
void handleInput(char input);
void movePacman();
void moveGhosts();
void checkCollisions();
void resetGame();
void gameOver();
int checkWinCondition();

#endif // PACMAN_H