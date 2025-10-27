#include <ncurses.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_TEXT_SIZE 1024
#define MENU_WIDTH 60
#define MENU_HEIGHT 20

void init_ncurses() {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(1);
    
    if (has_colors()) {
        start_color();
        init_pair(1, COLOR_CYAN, COLOR_BLACK);
        init_pair(2, COLOR_GREEN, COLOR_BLACK);
        init_pair(3, COLOR_YELLOW, COLOR_BLACK);
        init_pair(4, COLOR_RED, COLOR_BLACK);
    }
}

void caesar_encrypt(char *text, int shift, char *result) {
    int i;
    for (i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            char base = isupper(text[i]) ? 'A' : 'a';
            result[i] = ((text[i] - base + shift) % 26 + 26) % 26 + base;
        } else {
            result[i] = text[i];
        }
    }
    result[i] = '\0';
}

void caesar_decrypt(char *text, int shift, char *result) {
    caesar_encrypt(text, -shift, result);
}

void draw_border(WINDOW *win) {
    box(win, 0, 0);
}

void draw_title(WINDOW *win) {
    attron(COLOR_PAIR(1) | A_BOLD);
    mvwprintw(win, 1, 2, "=== Text Encryption/Decryption Tool ===");
    attroff(COLOR_PAIR(1) | A_BOLD);
}

int get_menu_choice(WINDOW *win) {
    int choice = 0;
    int key;
    
    while (1) {
        werase(win);
        draw_border(win);
        draw_title(win);
        
        attron(COLOR_PAIR(2));
        mvwprintw(win, 3, 2, "Please select an option:");
        attroff(COLOR_PAIR(2));
        
        if (choice == 0) attron(A_REVERSE);
        mvwprintw(win, 5, 4, "1. Encrypt Text");
        if (choice == 0) attroff(A_REVERSE);
        
        if (choice == 1) attron(A_REVERSE);
        mvwprintw(win, 6, 4, "2. Decrypt Text");
        if (choice == 1) attroff(A_REVERSE);
        
        if (choice == 2) attron(A_REVERSE);
        mvwprintw(win, 7, 4, "3. Exit");
        if (choice == 2) attroff(A_REVERSE);
        
        attron(COLOR_PAIR(3));
        mvwprintw(win, 9, 2, "Use Arrow Keys to navigate, Enter to select");
        attroff(COLOR_PAIR(3));
        
        wrefresh(win);
        
        key = wgetch(win);
        
        switch (key) {
            case KEY_UP:
                choice = (choice - 1 + 3) % 3;
                break;
            case KEY_DOWN:
                choice = (choice + 1) % 3;
                break;
            case '\n':
            case KEY_ENTER:
                return choice + 1;
        }
    }
}

void get_text_input(WINDOW *win, char *buffer, int max_len, const char *prompt) {
    werase(win);
    draw_border(win);
    draw_title(win);
    
    attron(COLOR_PAIR(2));
    mvwprintw(win, 3, 2, "%s", prompt);
    attroff(COLOR_PAIR(2));
    
    mvwprintw(win, 5, 2, "Text: ");
    wrefresh(win);
    
    echo();
    curs_set(1);
    wgetnstr(win, buffer, max_len - 1);
    noecho();
    curs_set(0);
}

int get_shift_value(WINDOW *win) {
    char shift_str[10];
    
    werase(win);
    draw_border(win);
    draw_title(win);
    
    attron(COLOR_PAIR(2));
    mvwprintw(win, 3, 2, "Enter shift value (1-25):");
    attroff(COLOR_PAIR(2));
    
    mvwprintw(win, 5, 2, "Shift: ");
    wrefresh(win);
    
    echo();
    curs_set(1);
    wgetnstr(win, shift_str, 9);
    noecho();
    curs_set(0);
    
    int shift = atoi(shift_str);
    if (shift < 1 || shift > 25) {
        shift = 3; // Default shift
    }
    
    return shift;
}

void display_result(WINDOW *win, const char *result, const char *operation) {
    werase(win);
    draw_border(win);
    draw_title(win);
    
    attron(COLOR_PAIR(2) | A_BOLD);
    mvwprintw(win, 3, 2, "Result (%s):", operation);
    attroff(COLOR_PAIR(2) | A_BOLD);
    
    attron(COLOR_PAIR(3));
    mvwprintw(win, 5, 2, "%s", result);
    attroff(COLOR_PAIR(3));
    
    attron(COLOR_PAIR(4));
    mvwprintw(win, MENU_HEIGHT - 2, 2, "Press any key to continue...");
    attroff(COLOR_PAIR(4));
    
    wrefresh(win);
    wgetch(win);
}

void process_encryption(WINDOW *win) {
    char input_text[MAX_TEXT_SIZE];
    char output_text[MAX_TEXT_SIZE];
    int shift;
    
    get_text_input(win, input_text, MAX_TEXT_SIZE, "Enter text to encrypt:");
    shift = get_shift_value(win);
    caesar_encrypt(input_text, shift, output_text);
    display_result(win, output_text, "Encrypted");
}

void process_decryption(WINDOW *win) {
    char input_text[MAX_TEXT_SIZE];
    char output_text[MAX_TEXT_SIZE];
    int shift;
    
    get_text_input(win, input_text, MAX_TEXT_SIZE, "Enter text to decrypt:");
    shift = get_shift_value(win);
    caesar_decrypt(input_text, shift, output_text);
    display_result(win, output_text, "Decrypted");
}

int main() {
    WINDOW *menu_win;
    int choice;
    
    init_ncurses();
    
    int start_y = (LINES - MENU_HEIGHT) / 2;
    int start_x = (COLS - MENU_WIDTH) / 2;
    
    menu_win = newwin(MENU_HEIGHT, MENU_WIDTH, start_y, start_x);
    keypad(menu_win, TRUE);
    
    while (1) {
        choice = get_menu_choice(menu_win);
        
        switch (choice) {
            case 1:
                process_encryption(menu_win);
                break;
            case 2:
                process_decryption(menu_win);
                break;
            case 3:
                delwin(menu_win);
                endwin();
                return 0;
        }
    }
    
    return 0;
}
