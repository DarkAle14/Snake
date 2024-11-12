#include <graphics.h>  // Libreria grafica per il rendering del gioco
#include <stdio.h>     // Libreria standard per input/output
#include <stdlib.h>    // Libreria standard per funzioni di utilità
#include <time.h>      // Libreria per la gestione del tempo

#define BLOCK_SIZE 20  // Dimensione di ciascun blocco del serpente

// Enum per rappresentare le direzioni del movimento del serpente
typedef enum { STOP = 0, LEFT, RIGHT, UP, DOWN } Direction;
Direction dir;  // Variabile che contiene la direzione corrente del serpente

// Variabili globali
int snakeX[100], snakeY[100];  // Posizioni dei segmenti del serpente (fino a 100 blocchi)
int fruitX, fruitY;            // Coordinate del frutto
int length = 1;                // Lunghezza iniziale del serpente
int score = 0;                 // Punteggio del giocatore
int gameOver = 0;              // Stato del gioco (0 = in corso, 1 = terminato)
int snakeColor = GREEN;        // Colore iniziale del serpente
int fruitColor = RED;          // Colore del frutto (rosso)
int WIDTH = 640;              // Larghezza della finestra di gioco
int HEIGHT = 480;             // Altezza della finestra di gioco
int mapSizeChoice;            // Scelta della dimensione della mappa

// Funzione per selezionare il colore del serpente
void SelectSnakeColor(int *snakeColor) {
    int key;
    while (1) {
        cleardevice();  // Pulisce la schermata
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);  // Imposta il font di testo

        // Mostra le opzioni per selezionare il colore
        outtextxy(100, 50, "Seleziona il colore del serpente:");
        outtextxy(100, 70, "1 - Verde");
        outtextxy(100, 90, "2 - Rosso");
        outtextxy(100, 110, "3 - Blu");
        outtextxy(100, 130, "4 - Giallo");
        outtextxy(100, 150, "5 - Bianco");

        key = getch();  // Legge il tasto premuto dall'utente
        switch (key) {
            case '1':
                *snakeColor = GREEN;  // Imposta il colore del serpente a verde
                return;
            case '2':
                *snakeColor = RED;    // Imposta il colore del serpente a rosso
                return;
            case '3':
                *snakeColor = BLUE;   // Imposta il colore del serpente a blu
                return;
            case '4':
                *snakeColor = YELLOW; // Imposta il colore del serpente a giallo
                return;
            case '5':
                *snakeColor = WHITE;  // Imposta il colore del serpente a bianco
                return;
            case 'x':
                gameOver = 1;  // Termina il gioco se l'utente preme 'x'
                return;
        }
    }
}

// Funzione per selezionare la dimensione della mappa
void SelectMapSize() {
    int key;
    while (1) {
        cleardevice();  // Pulisce la schermata
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);  // Imposta il font di testo

        // Mostra le opzioni per selezionare la dimensione della mappa
        outtextxy(100, 50, "Seleziona la dimensione della mappa:");
        outtextxy(100, 70, "1 - Media (640x480)");
        outtextxy(100, 90, "2 - Grande (800x600)");

        key = getch();  // Legge il tasto premuto dall'utente
        switch (key) {
            case '1':
                WIDTH = 640;     // Imposta la larghezza a 640
                HEIGHT = 480;    // Imposta l'altezza a 480
                mapSizeChoice = 1;
                return;
            case '2':
                WIDTH = 800;     // Imposta la larghezza a 800
                HEIGHT = 600;    // Imposta l'altezza a 600
                mapSizeChoice = 2;
                return;
            case 'x':
                gameOver = 1;    // Termina il gioco se l'utente preme 'x'
                return;
        }
    }
}

// Funzione per configurare lo stato iniziale del gioco
void Setup() {
    dir = STOP;  // Inizialmente il serpente è fermo
    length = 1;  // Reset della lunghezza del serpente
    score = 0;   // Reset del punteggio
    snakeX[0] = WIDTH / (2 * BLOCK_SIZE) * BLOCK_SIZE;  // Posizione iniziale centrata
    snakeY[0] = HEIGHT / (2 * BLOCK_SIZE) * BLOCK_SIZE;
    srand(time(0));  // Inizializza il generatore di numeri casuali
    fruitX = (rand() % (WIDTH / BLOCK_SIZE)) * BLOCK_SIZE; // Posizione casuale del frutto
    fruitY = (rand() % (HEIGHT / BLOCK_SIZE)) * BLOCK_SIZE;
}

// Funzione per disegnare la grafica del gioco
void Draw() {
    cleardevice();  // Pulisce la schermata
    
    // Disegna il frutto
    setfillstyle(SOLID_FILL, fruitColor);
    bar(fruitX, fruitY, fruitX + BLOCK_SIZE, fruitY + BLOCK_SIZE);

    // Disegna il serpente
    setfillstyle(SOLID_FILL, snakeColor);
    for (int i = 0; i < length; i++) {
        bar(snakeX[i], snakeY[i], snakeX[i] + BLOCK_SIZE, snakeY[i] + BLOCK_SIZE);
    }

    // Mostra il punteggio
    char scoreText[20];
    sprintf(scoreText, "Score: %d", score);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    outtextxy(10, 10, scoreText);  // Visualizza il punteggio
}

// Funzione per gestire l'input dell'utente
void Input() {
    if (kbhit()) {  // Controlla se un tasto è stato premuto
        switch (getch()) {  // Legge il tasto premuto
            case 'a':
                if (dir != RIGHT) dir = LEFT;  // Cambia la direzione a sinistra
                break;
            case 'd':
                if (dir != LEFT) dir = RIGHT;  // Cambia la direzione a destra
                break;
            case 'w':
                if (dir != DOWN) dir = UP;     // Cambia la direzione in alto
                break;
            case 's':
                if (dir != UP) dir = DOWN;     // Cambia la direzione in basso
                break;
            case 'x':
                gameOver = 1;  // Termina il gioco
                break;
        }
    }
}

// Funzione per gestire la logica del gioco
void Logic() {
    // Aggiorna la posizione del corpo del serpente
    for (int i = length; i > 0; i--) {
        snakeX[i] = snakeX[i - 1];
        snakeY[i] = snakeY[i - 1];
    }

    // Movimento della testa del serpente
    switch (dir) {
        case LEFT:
            snakeX[0] -= BLOCK_SIZE;
            break;
        case RIGHT:
            snakeX[0] += BLOCK_SIZE;
            break;
        case UP:
            snakeY[0] -= BLOCK_SIZE;
            break;
        case DOWN:
            snakeY[0] += BLOCK_SIZE;
            break;
        default:
            break;
    }

    // Controllo delle collisioni con i bordi della finestra
    if (snakeX[0] < 0 || snakeX[0] >= WIDTH || snakeY[0] < 0 || snakeY[0] >= HEIGHT) {
        gameOver = 1;
    }

    // Controllo delle collisioni con il corpo del serpente
    for (int i = 1; i < length; i++) {
        if (snakeX[0] == snakeX[i] && snakeY[0] == snakeY[i]) {
            gameOver = 1;
        }
    }

    // Gestione della raccolta del frutto
    if (snakeX[0] == fruitX && snakeY[0] == fruitY) {
        score += 10;  // Aumenta il punteggio
        length++;     // Allunga il serpente
        fruitX = (rand() % (WIDTH / BLOCK_SIZE)) * BLOCK_SIZE;  // Genera nuova posizione per il frutto
        fruitY = (rand() % (HEIGHT / BLOCK_SIZE)) * BLOCK_SIZE;
    }
}

// Funzione principale del gioco
int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");  // Inizializza la finestra grafica
    int restartGame = 0;

    while (1) {  // Ciclo principale del programma
        if (!restartGame) {
            SelectSnakeColor(&snakeColor); // Seleziona il colore del serpente
            SelectMapSize(); // Seleziona la dimensione della mappa
        }

        initwindow(WIDTH, HEIGHT, "Snake Game in C");  // Crea la finestra di gioco
        Setup();  // Configura il gioco
        gameOver = 0;

        // Ciclo principale del gioco
        while (!gameOver) {
            Draw();   // Disegna l'interfaccia
            Input();  // Gestisce l'input
            Logic();  // Gestisce la logica del gioco
            delay(100);  // Ritardo per controllare la velocità
        }

        // Messaggio di fine partita
        cleardevice();  // Pulisce la schermata
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);  // Imposta il font di testo
        outtextxy(WIDTH / 2 - 50, HEIGHT / 2 - 30, "Game Over!");
        outtextxy(WIDTH / 3 - 100, HEIGHT / 2, "Premi R per riavviare e X per uscire.");

        char choice;
        while (1) {
            choice = getch();  // Legge il tasto premuto
            if (choice == 'r') {
                restartGame = 1;  // Riavvia il gioco
                break;
            } else if (choice == 'x') {
                closegraph();  // Chiude la finestra grafica
                return 0;      // Esce dal programma
            }
        }
        closegraph();  // Chiude la finestra grafica prima di riavviare o uscire
    }
}