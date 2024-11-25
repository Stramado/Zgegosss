#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curses.h>
#include <time.h>
#include <sys/timeb.h>

// Constants
#define MIN_SCREEN_WIDTH 29
#define MIN_SCREEN_HEIGHT 32
#define MAX_ROWS 29
#define MAX_COLS 28
#define MAX_LEVELS 10

// Enum for game elements
typedef enum {
    EMPTY = 0,
    WALL,
    PELLET,
    POWERUP,
    GHOST_ZONE,
    GHOST1,
    GHOST2,
    GHOST3,
    GHOST4,
    PACMAN
} TileType;

// Directions
typedef enum {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    NONE
} Direction;

// Structure for game state
typedef struct {
    int pacman_x, pacman_y;
    int ghost_x[4], ghost_y[4];
    int ghost_dir[4];
    int level[MAX_ROWS][MAX_COLS];
    int level_num;
    int lives;
    int score;
    int pellets_left;
    int is_invincible;
    int invincibility_timer;
} GameState;

// Global Variables
WINDOW *game_win, *status_win;

// Function Prototypes
void init_game(GameState *state, const char *level_file);
void init_curses();
void cleanup();
void check_screen_size();
void load_level(GameState *state, const char *level_file);
void draw_game(const GameState *state);
void draw_status(const GameState *state);
void move_pacman(GameState *state, Direction dir);
void move_ghosts(GameState *state);
void check_collisions(GameState *state);
void delay();
void intro_screen();
void exit_game(const char *message);

int main(int argc, char *argv[]) {
    GameState state = {0};
    const char *level_file = argc > 1 ? argv[1] : "default_level.txt";

    srand((unsigned)time(NULL));
    init_curses();
    check_screen_size();

    if (argc == 1) {
        intro_screen();
    }

    init_game(&state, level_file);

    while (state.lives >= 0 && state.pellets_left > 0) {
        int ch = getch();
        Direction dir = NONE;

        switch (ch) {
            case KEY_UP: case 'w': dir = UP; break;
            case KEY_DOWN: case 's': dir = DOWN; break;
            case KEY_LEFT: case 'a': dir = LEFT; break;
            case KEY_RIGHT: case 'd': dir = RIGHT; break;
            case 'q': exit_game("Goodbye!"); break;
        }

        move_pacman(&state, dir);
        move_ghosts(&state);
        check_collisions(&state);

        draw_game(&state);
        draw_status(&state);

        delay();
    }

    exit_game(state.lives < 0 ? "Game Over" : "You Win!");
}

void init_game(GameState *state, const char *level_file) {
    state->lives = 3;
    state->score = 0;
    state->is_invincible = 0;
    state->invincibility_timer = 0;

    load_level(state, level_file);

    game_win = newwin(MAX_ROWS, MAX_COLS, 1, 1);
    status_win = newwin(3, MAX_COLS, MAX_ROWS + 1, 1);

    draw_game(state);
    draw_status(state);
}

void init_curses() {
    initscr();
    start_color();
    curs_set(0);
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    cbreak();
    noecho();

    init_pair(WALL, COLOR_WHITE, COLOR_WHITE);
    init_pair(PELLET, COLOR_YELLOW, COLOR_BLACK);
    init_pair(POWERUP, COLOR_BLUE, COLOR_BLACK);
    init_pair(GHOST1, COLOR_RED, COLOR_BLACK);
    init_pair(GHOST2, COLOR_CYAN, COLOR_BLACK);
    init_pair(GHOST3, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(GHOST4, COLOR_YELLOW, COLOR_BLACK);
    init_pair(PACMAN, COLOR_YELLOW, COLOR_BLACK);
}

void cleanup() {
    endwin();
}

void check_screen_size() {
    int height, width;
    getmaxyx(stdscr, height, width);

    if (width < MIN_SCREEN_WIDTH || height < MIN_SCREEN_HEIGHT) {
        cleanup();
        fprintf(stderr, "Screen size must be at least %dx%d. Resize and try again.\n",
                MIN_SCREEN_WIDTH, MIN_SCREEN_HEIGHT);
        exit(EXIT_FAILURE);
    }
}

void load_level(GameState *state, const char *level_file) {
    FILE *file = fopen(level_file, "r");
    if (!file) {
        cleanup();
        fprintf(stderr, "Error: Unable to open level file: %s\n", level_file);
        exit(EXIT_FAILURE);
    }

    state->pellets_left = 0;
    for (int row = 0; row < MAX_ROWS; row++) {
        for (int col = 0; col < MAX_COLS; col++) {
            fscanf(file, "%d", &state->level[row][col]);

            if (state->level[row][col] == PELLET) {
                state->pellets_left++;
            } else if (state->level[row][col] == PACMAN) {
                state->pacman_x = row;
                state->pacman_y = col;
                state->level[row][col] = EMPTY;
            } else if (state->level[row][col] >= GHOST1 && state->level[row][col] <= GHOST4) {
                int ghost_idx = state->level[row][col] - GHOST1;
                state->ghost_x[ghost_idx] = row;
                state->ghost_y[ghost_idx] = col;
                state->ghost_dir[ghost_idx] = rand() % 4;
                state->level[row][col] = EMPTY;
            }
        }
    }

    fscanf(file, "%d", &state->level_num);
    fclose(file);
}

void draw_game(const GameState *state) {
    for (int row = 0; row < MAX_ROWS; row++) {
        for (int col = 0; col < MAX_COLS; col++) {
            int tile = state->level[row][col];
            int color = COLOR_PAIR(tile);

            wattron(game_win, color);
            mvwaddch(game_win, row, col, tile == WALL ? '#' : ' ');
            wattroff(game_win, color);
        }
    }

    // Draw Pacman
    wattron(game_win, COLOR_PAIR(PACMAN));
    mvwaddch(game_win, state->pacman_x, state->pacman_y, 'C');
    wattroff(game_win, COLOR_PAIR(PACMAN));

    // Draw Ghosts
    for (int i = 0; i < 4; i++) {
        wattron(game_win, COLOR_PAIR(GHOST1 + i));
        mvwaddch(game_win, state->ghost_x[i], state->ghost_y[i], 'G');
        wattroff(game_win, COLOR_PAIR(GHOST1 + i));
    }

    wrefresh(game_win);
}

void draw_status(const GameState *state) {
    mvwprintw(status_win, 1, 1, "Lives: %d  Score: %d  Level: %d", state->lives, state->score, state->level_num);
    wrefresh(status_win);
}

void move_pacman(GameState *state, Direction dir) {
    int dx = 0, dy = 0;

    switch (dir) {
        case UP: dx = -1; break;
        case DOWN: dx = 1; break;
        case LEFT: dy = -1; break;
        case RIGHT: dy = 1; break;
        default: return;
    }

    int new_x = state->pacman_x + dx;
    int new_y = state->pacman_y + dy;

    if (state->level[new_x][new_y] != WALL) {
        state->pacman_x = new_x;
        state->pacman_y = new_y;

        if (state->level[new_x][new_y] == PELLET) {
            state->score += 10;
            state->pellets_left--;
            state->level[new_x][new_y] = EMPTY;
        } else if (state->level[new_x][new_y] == POWERUP) {
            state->score += 50;
            state->is_invincible = 1;
            state->invincibility_timer = 50;
            state->level[new_x][new_y] = EMPTY;
        }
    }
}

void move_ghosts(GameState *state) {
    for (int i = 0; i < 4; i++) {
        int dx = 0, dy = 0;
        switch (state->ghost_dir[i]) {
            case UP: dx = -1; break;
            case DOWN: dx = 1; break;
            case LEFT: dy = -1; break;
            case RIGHT: dy = 1; break;
            default: continue;
        }

        int new_x = state->ghost_x[i] + dx;
        int new_y = state->ghost_y[i] + dy;

        if (state->level[new_x][new_y] != WALL) {
            state->ghost_x[i] = new_x;
            state->ghost_y[i] = new_y;
        } else {
            state->ghost_dir[i] = rand() % 4;
        }
    }
}

void check_collisions(GameState *state) {
    for (int i = 0; i < 4; i++) {
        if (state->pacman_x == state->ghost_x[i] && state->pacman_y == state->ghost_y[i]) {
            if (state->is_invincible) {
                state->score += 200;
                state->ghost_x[i] = rand() % MAX_ROWS;
                state->ghost_y[i] = rand() % MAX_COLS;
            } else {
                state->lives--;
                state->pacman_x = 1;
                state->pacman_y = 1;
            }
        }
    }

    if (state->invincibility_timer > 0) {
        state->invincibility_timer--;
        if (state->invincibility_timer == 0) {
            state->is_invincible = 0;
        }
    }
}

void delay() {
    struct timespec ts = {.tv_sec = 0, .tv_nsec = 100000000L};
    nanosleep(&ts, NULL);
}

void intro_screen() {
    mvprintw(LINES / 2, (COLS - 20) / 2, "Welcome to PACMAN!");
    mvprintw(LINES / 2 + 1, (COLS - 25) / 2, "Press any key to start...");
    refresh();
    getch();
}

void exit_game(const char *message) {
    cleanup();
    printf("%s\n", message);
    exit(EXIT_SUCCESS);
}
