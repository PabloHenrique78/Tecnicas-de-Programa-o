#include <stdio.h>
#include <stdbool.h>

void inicializa(char tabuleiro[6][7]) {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 7; j++) {
            tabuleiro[i][j] = ' ';
        }
    }
}

void printa(char tabuleiro[6][7]) {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 7; j++) {
            printf("| %c ", tabuleiro[i][j]);
        }
        printf("|\n");
    }
    for (int j = 0; j < 7; j++) {
        printf("----");
    }
    printf("-\n");
    for (int j = 0; j < 7; j++) {
        printf("  %d ", j + 1);
    }
    printf("\n");
}

bool coloca_moeda(char tabuleiro[6][7], int coluna, char moeda) {
    if (coluna < 0 || coluna >= 7) {
        return false;
    }
    for (int i = 6 - 1; i >= 0; i--) {
        if (tabuleiro[i][coluna] == ' ') {
            tabuleiro[i][coluna] = moeda;
            return true;
        }
    }
    return false;
}

bool verifica(char tabuleiro[6][7], int linha, int coluna, int dlinha, int dcoluna, char moeda) {
    int contador = 0;
    for (int i = 0; i < 4; i++) {
        int r = linha + i * dlinha;
        int c = coluna + i * dcoluna;
        if (r >= 0 && r < 6 && c >= 0 && c < 7 && tabuleiro[r][c] == moeda) {
            contador++;
        } else {
            return false;
        }
    }
    return contador == 4;
}

bool vitoria(char tabuleiro[6][7], char moeda) {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 7; j++) {
            if (tabuleiro[i][j] == moeda) {
                if (verifica(tabuleiro, i, j, 1, 0, moeda) || 
                    verifica(tabuleiro, i, j, 0, 1, moeda) || 
                    verifica(tabuleiro, i, j, 1, 1, moeda) || 
                    verifica(tabuleiro, i, j, 1, -1, moeda)) {
                    return true;
                }
            }
        }
    }
    return false;
}

int main() {
    char tabuleiro[6][7];
    inicializa(tabuleiro);
    char players[2] = {'X', 'O'};
    int player_atual = 0;
    int mov = 0;
    bool jogo_terminado = false;

    while (!jogo_terminado) {
        printa(tabuleiro);
        printf("Jogador %d (%c), escolha uma coluna (1-7): ", player_atual + 1, players[player_atual]);
        int coluna;
        scanf("%d", &coluna);
        coluna--; 

        if (coloca_moeda(tabuleiro, coluna, players[player_atual])) {
            mov++;
            if (vitoria(tabuleiro, players[player_atual])) {
                printa(tabuleiro);
                printf("Jogador %d (%c) ganhou!\n", player_atual + 1, players[player_atual]);
                jogo_terminado = true;
            } else {
                player_atual = (player_atual + 1) % 2;
            }
        } else {
            printf("Movimento proibido. Tente de novo.\n");
        }

        if (mov == 6 * 7 && !jogo_terminado) {
            printa(tabuleiro);
            printf("O jogo terminou em empate!\n");
            jogo_terminado = true;
        }
    }

    return 0;
}
