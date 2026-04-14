// gcc -o astar astar.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ROWS 5
#define COLS 5
#define INF 999999999

int grid[ROWS][COLS] = {
    {0,0,0,0,0},
    {0,1,1,0,0},
    {0,0,1,0,0},
    {0,0,0,1,0},
    {0,0,0,0,0}
};

int abs_val(int x) { return x < 0 ? -x : x; }
int heuristic(int r1, int c1, int r2, int c2) { return abs_val(r1-r2) + abs_val(c1-c2); }

int main(void) {
    int total = ROWS * COLS;
    int g_score[total], f_score[total], came_from[total];
    int closed[total];
    memset(closed, 0, sizeof(closed));
    for (int i = 0; i < total; i++) { g_score[i] = INF; f_score[i] = INF; came_from[i] = -1; }

    int sr = 0, sc = 0, er = 4, ec = 4;
    int start_key = sr * COLS + sc;
    g_score[start_key] = 0;
    f_score[start_key] = heuristic(sr, sc, er, ec);

    int open_list[total];
    int open_len = 0;
    open_list[open_len++] = start_key;

    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    int path_r[total], path_c[total], path_len = 0;
    int found = 0;

    while (open_len > 0) {
        int best_idx = 0;
        for (int i = 1; i < open_len; i++) {
            if (f_score[open_list[i]] < f_score[open_list[best_idx]]) best_idx = i;
        }
        int current = open_list[best_idx];
        // Remove from open list
        for (int i = best_idx; i < open_len - 1; i++) open_list[i] = open_list[i+1];
        open_len--;

        int cr = current / COLS, cc = current % COLS;
        if (cr == er && cc == ec) {
            // Reconstruct path
            int c = current;
            int tmp_r[total], tmp_c[total];
            int tlen = 0;
            while (c != -1) {
                tmp_r[tlen] = c / COLS;
                tmp_c[tlen] = c % COLS;
                tlen++;
                c = came_from[c];
            }
            for (int i = tlen - 1; i >= 0; i--) {
                path_r[path_len] = tmp_r[i];
                path_c[path_len] = tmp_c[i];
                path_len++;
            }
            found = 1;
            break;
        }

        closed[current] = 1;

        for (int d = 0; d < 4; d++) {
            int nr = cr + dr[d], nc = cc + dc[d];
            if (nr < 0 || nr >= ROWS || nc < 0 || nc >= COLS) continue;
            if (grid[nr][nc] == 1) continue;
            int nkey = nr * COLS + nc;
            if (closed[nkey]) continue;
            int tentative_g = g_score[current] + 1;
            if (tentative_g < g_score[nkey]) {
                came_from[nkey] = current;
                g_score[nkey] = tentative_g;
                f_score[nkey] = tentative_g + heuristic(nr, nc, er, ec);
                // Add to open if not there
                int in_open = 0;
                for (int i = 0; i < open_len; i++) if (open_list[i] == nkey) { in_open = 1; break; }
                if (!in_open) open_list[open_len++] = nkey;
            }
        }
    }

    printf("path length: %d\n", path_len);
    printf("path:");
    for (int i = 0; i < path_len; i++) {
        printf(" (%d,%d)", path_r[i], path_c[i]);
    }
    printf("\n");
    return 0;
}
