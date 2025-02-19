#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COLS 1024
#define INITIAL_MAX_LINES 1000

void load_file(const char *filename, char ***lines, int *line_count, int *max_lines);
void display_window(WINDOW *win, char **lines, int start_line, int total_lines, int offset);
void free_lines(char **lines, int line_count);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];
    char **lines = malloc(INITIAL_MAX_LINES * sizeof(char *));
    int line_count = 0, max_lines = INITIAL_MAX_LINES;
    int start_line = 0, offset = 0;

    load_file(filename, &lines, &line_count, &max_lines);

    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    int height = LINES - 4;
    int width = COLS - 4;
    int start_y = 2, start_x = 2;

    WINDOW *win = newwin(height, width, start_y, start_x);
    box(win, 0, 0);

    int ch;
    while (1) {
        mvprintw(0, (COLS - strlen(filename) - 8) / 2, "[ File: %s ]", filename);
        display_window(win, lines, start_line, line_count, offset);
        mvprintw(LINES - 2, (COLS - 30) / 2, "[ Lines: %d/%d | Offset: %d ]", start_line + 1, line_count, offset);
        refresh();

        ch = getch();
        switch (ch) {
            case ' ':
            case KEY_NPAGE:
                if (start_line + height - 2 < line_count)
                    start_line += height - 2;
                else
                    start_line = line_count - height + 2;
                break;
            case KEY_PPAGE:
                start_line = (start_line - (height - 2) > 0) ? start_line - (height - 2) : 0;
                break;
            case KEY_RIGHT:
                offset++;
                break;
            case KEY_LEFT:
                if (offset > 0) offset--;
                break;
            case KEY_UP:
                if (start_line > 0) start_line--;
                break;
            case KEY_DOWN:
                if (start_line + 1 < line_count) start_line++;
                break;
            case 27:
                free_lines(lines, line_count);
                endwin();
                return 0;
        }
    }

    free_lines(lines, line_count);
    endwin();
    return 0;
}

void load_file(const char *filename, char ***lines, int *line_count, int *max_lines) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("fopen");
        exit(1);
    }

    char buffer[MAX_COLS];
    while (fgets(buffer, sizeof(buffer), file)) {
        if (*line_count >= *max_lines) {
            *max_lines *= 2;
            *lines = realloc(*lines, (*max_lines) * sizeof(char *));
            if (!*lines) {
                perror("realloc");
                exit(1);
            }
        }

        buffer[strcspn(buffer, "\r\n")] = '\0';
        (*lines)[*line_count] = strdup(buffer);
        (*line_count)++;
    }
    fclose(file);
}

void display_window(WINDOW *win, char **lines, int start_line, int total_lines, int offset) {
    werase(win);
    box(win, 0, 0);

    for (int i = 1; i < getmaxy(win) - 1; i++) {
        if (start_line + i - 1 < total_lines) {
            int len = strlen(lines[start_line + i - 1]);
            int visible_offset = offset < len ? offset : len;
            mvwprintw(win, i, 2, "%3d | %s", start_line + i, lines[start_line + i - 1] + visible_offset);
        }
    }

    wrefresh(win);
}

void free_lines(char **lines, int line_count) {
    for (int i = 0; i < line_count; i++) free(lines[i]);
    free(lines);
}
