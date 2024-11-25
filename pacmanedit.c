#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "pacman.h"

// Game state
TileType board[BOARD_ROWS][BOARD_COLS]; // Game board

// Pacman and Ghost objects
Pacman pacman;
Ghost ghosts[MAX_LIVES];

// Function to initialize the game
void initializeGame() {
    // Initialize the board with empty tiles
    for (int i = 0; i < BOARD_ROWS; i++) {
        for (int j = 0; j < BOARD_COLS; j++) {
            board[i][j] = EMPTY; // Default to empty
        }
    }

    // Set up Pacman's initial position
    pacman.x = BOARD_COLS / 2;
    pacman.y = BOARD_ROWS - 2;
    pacman.dx = 0;
    pacman.dy = -1;  // Moving upwards

    // Set up ghosts' initial positions
    for (int i = 0; i < MAX_LIVES; i++) {
        ghosts[i].x = (i + 1) * 2;
        ghosts[i].y = 1;
        ghosts[i].dx = 1;
        ghosts[i].dy = 0;  // Moving right
        ghosts[i].is_vulnerable = 0;  // Initially not vulnerable
    }

    Points = 0;
    Lives = 3;
}

// Load a level into the game (stub function, to be implemented)
void loadLevel(int level) {
    // For now, just print which level is being loaded
    printf("Loading level %d...\n", level);
    // You could load specific level configurations from a file here
}

// Render the game board
void renderBoard() {
    for (int i = 0; i < BOARD_ROWS; i++) {
        for (int j = 0; j < BOARD_COLS; j++) {
            // Render different tiles based on board contents
            switch (board[i][j]) {
                case EMPTY: printf(" "); break;
                case WALL: printf("#"); break;
                case DOT: printf("."); break;
                case ENERGIZER: printf("O"); break;
                case GHOST: printf("G"); break;
                case PACMAN: printf("P"); break;
            }
        }
        printf("\n");
    }
}

// Update game state (move Pacman and ghosts, check collisions)
void updateGame() {
    movePacman();
    moveGhosts();
    checkCollisions();
}

// Handle user input for Pacman's movement
void handleInput(char input) {
    switch (input) {
        case 'w': pacman.dx = 0; pacman.dy = -1; break;  // Move up
        case 'a': pacman.dx = -1; pacman.dy = 0; break;  // Move left
        case 's': pacman.dx = 0; pacman.dy = 1; break;   // Move down
        case 'd': pacman.dx = 1; pacman.dy = 0; break;   // Move right
        default: break;
    }
}

// Move Pacman on the board
void movePacman() {
    pacman.x += pacman.dx;
    pacman.y += pacman.dy;

    // Boundary check
    if (pacman.x < 0) pacman.x = 0;
    if (pacman.x >= BOARD_COLS) pacman.x = BOARD_COLS - 1;
    if (pacman.y < 0) pacman.y = 0;
    if (pacman.y >= BOARD_ROWS) pacman.y = BOARD_ROWS - 1;
}

// Move ghosts on the board
void moveGhosts() {
    for (int i = 0; i < MAX_LIVES; i++) {
        ghosts[i].x += ghosts[i].dx;
        ghosts[i].y += ghosts[i].dy;

        // Boundary check
        if (ghosts[i].x < 0 || ghosts[i].x >= BOARD_COLS) {
            ghosts[i].dx *= -1;  // Change direction
        }
        if (ghosts[i].y < 0 || ghosts[i].y >= BOARD_ROWS) {
            ghosts[i].dy *= -1;  // Change direction
        }
    }
}

// Check for collisions with walls, ghosts, or dots
void checkCollisions() {
    // Example: Check if Pacman collides with a ghost
    for (int i = 0; i < MAX_LIVES; i++) {
        if (pacman.x == ghosts[i].x && pacman.y == ghosts[i].y) {
            Lives--;
            if (Lives <= 0) {
                gameOver();
            } else {
                resetGame();
            }
        }
    }
}

// Reset game state for next life
void resetGame() {
    pacman.x = BOARD_COLS / 2;
    pacman.y = BOARD_ROWS - 2;
    pacman.dx = 0;
    pacman.dy = -1;

    // Reset ghosts' positions
    for (int i = 0; i < MAX_LIVES; i++) {
        ghosts[i].x = (i + 1) * 2;
        ghosts[i].y = 1;
    }
}

// Game over logic
void gameOver() {
    printf("Game Over! You scored %d points.\n", Points);
    exit(0);
}

// Check if the player has won
int checkWinCondition() {
    // Simple win condition: if all dots are eaten (just an example)
    // You can add a win condition depending on the game rules
    return Points >= 1000;
}

// Main game loop
int main() {
    char input;

    initializeGame();

    // Load level 1 for now
    loadLevel(1);

    while (Lives > 0) {
        renderBoard();
        usleep(SpeedOfGame * 1000);  // Delay to control game speed

        // Handle user input (for testing purposes, read character from stdin)
        if (scanf("%c", &input)) {
            handleInput(input);
        }

        updateGame();
        if (checkWinCondition()) {
            printf("You win! You scored %d points.\n", Points);
            break;
        }
    }

    return 0;
}
