#include <iostream>
#include <cstring>

const size_t BUFF_SIZE = 1024;

FILE *file;
char buff[BUFF_SIZE];
int ptr, size;

int get_char() {
    if (ptr == size) {
        size = fread(buff, sizeof(char), BUFF_SIZE, file);
    }
    if (size == 0) {
        return -1;
    } else {
        return buff[ptr++];
    }
}

int new_pi(size_t *pi, char *s, char symbol, size_t last_pi) {
    size_t i = last_pi;
    while (i > 0 && symbol != s[i]) {
        i = pi[i - 1];
    }
    if (symbol == s[i]) {
        i++;
    }
    return i;
}

bool check_file(size_t *pi, char *s, size_t n) {
    size_t last_pi = 0;
    int symbol;
    while ((symbol = get_char()) != -1) {
        if ((last_pi = new_pi(pi, s, (char)symbol, last_pi)) == n) {
            return true;
        }
    }
    return false;
}

int main(int argc, char* argv[]) {
    size_t n = strlen(argv[1]), *pi = (size_t *)malloc(n * sizeof(size_t));
    pi[0] = 0;
    for (size_t i = 1; i < n; i++) {
        pi[i] = new_pi(pi, argv[1], argv[1][i], pi[i - 1]);
    }
    file = fopen(argv[2], "r");
    std::cout << check_file(pi, argv[1], n) << std::endl;
    fclose(file);

    return 0;
}
