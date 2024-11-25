#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h> // Pour usleep

#define WIDTH 10
#define HEIGHT 20
#define EMPTY ' '
#define BLOCK '#'

// Définition des formes des blocs
int tetrominos[7][4][4] = {
    {{1, 1, 1, 1}}, // I
    {{1, 1}, {1, 1}}, // O
    {{0, 1, 0}, {1, 1, 1}}, // T
    {{1, 0, 0}, {1, 1, 1}}, // L
    {{0, 0, 1}, {1, 1, 1}}, // J
    {{1, 1, 0}, {0, 1, 1}}, // S
    {{0, 1, 1}, {1, 1, 0}} // Z
};

// Structure représentant une pièce
typedef struct {
    int x, y;  // Position de la pièce
    int shape[4][4]; // Forme de la pièce
} Tetromino;

// Plateau de jeu
char board[HEIGHT][WIDTH];

// Fonction pour initialiser le plateau
void initBoard() {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            board[i][j] = EMPTY;
        }
    }
}

// Fonction pour afficher le plateau
void renderBoard() {
    system("clear");  // Effacer l'écran pour rafraîchir l'affichage (utiliser "cls" sur Windows)
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            printf("%c", board[i][j]);
        }
        printf("\n");
    }
}

// Fonction pour vérifier si une position est valide
int isValidMove(Tetromino* piece) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (piece->shape[i][j]) {
                int newX = piece->x + j;
                int newY = piece->y + i;
                if (newX < 0 || newX >= WIDTH || newY >= HEIGHT || (newY >= 0 && board[newY][newX] != EMPTY)) {
                    return 0;
                }
            }
        }
    }
    return 1;
}

// Fonction pour placer une pièce sur le plateau
void placePiece(Tetromino* piece) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (piece->shape[i][j]) {
                board[piece->y + i][piece->x + j] = BLOCK;
            }
        }
    }
}

// Fonction pour faire tourner une pièce
void rotatePiece(Tetromino* piece) {
    int temp[4][4];
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            temp[j][3 - i] = piece->shape[i][j];
        }
    }
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            piece->shape[i][j] = temp[i][j];
        }
    }
}

// Fonction pour effacer les lignes complètes
void clearLines() {
    for (int i = HEIGHT - 1; i >= 0; i--) {
        int isFull = 1;
        for (int j = 0; j < WIDTH; j++) {
            if (board[i][j] == EMPTY) {
                isFull = 0;
                break;
            }
        }
        if (isFull) {
            for (int k = i; k > 0; k--) {
                for (int j = 0; j < WIDTH; j++) {
                    board[k][j] = board[k - 1][j];
                }
            }
            for (int j = 0; j < WIDTH; j++) {
                board[0][j] = EMPTY;
            }
        }
    }
}

// Fonction pour générer une nouvelle pièce
Tetromino generatePiece() {
    Tetromino piece;
    int index = rand() % 7;
    piece.x = WIDTH / 2 - 2;  // Position initiale de la pièce
    piece.y = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            piece.shape[i][j] = tetrominos[index][i][j];
        }
    }
    return piece;
}

// Fonction pour gérer l'entrée du joueur
void handleInput(Tetromino* piece) {
    char input;
    if (scanf("%c", &input)) {
        if (input == 'a') {
            piece->x--;
            if (!isValidMove(piece)) piece->x++;
        }
        if (input == 'd') {
            piece->x++;
            if (!isValidMove(piece)) piece->x--;
        }
        if (input == 's') {
            piece->y++;
            if (!isValidMove(piece)) {
                piece->y--;
                placePiece(piece);
                clearLines();
                *piece = generatePiece();
            }
        }
        if (input == 'w') {
            rotatePiece(piece);
            if (!isValidMove(piece)) rotatePiece(piece); // Annuler la rotation si elle est invalide
        }
    }
}

// Fonction principale pour gérer le jeu
void playGame() {
    Tetromino currentPiece = generatePiece();
    initBoard();
    
    while (1) {
        renderBoard();
        handleInput(&currentPiece);
        usleep(500000);  // Pause de 0.5 seconde pour ralentir la vitesse du jeu
    }
}

int main() {
    srand(time(NULL));
    playGame();
    return 0;
}
