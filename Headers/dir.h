#ifdef DIR_H

int getLastSlash() {
    int lastSlash = 0;

    for (int j = 0; j <= sizeof(__FILE__); j++) {
        if (__FILE__[j] == '/') {
            lastSlash = j;
        }
    }

    return lastSlash;
}

char *getDir() {
    char *new__FILE__ = malloc(sizeof(__FILE__));

    for (int i = 0; i <= getLastSlash(); i++) {
        new__FILE__[i] = __FILE__[i];
    }

    return new__FILE__;
}

#endif