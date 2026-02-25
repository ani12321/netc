#include "strutils.h"

/* return a new string with every instance of ch replaced by repl */
char *replace(const char *s, char ch, const char *repl) {
    int count = 0;
    const char *t;
    for(t=s; *t; t++)
        count += (*t == ch);

    size_t rlen = strlen(repl);
    char *res = malloc(strlen(s) + (rlen-1)*count + 1);
    char *ptr = res;
    for(t=s; *t; t++) {
        if(*t == ch) {
            memcpy(ptr, repl, rlen);
            ptr += rlen;
        } else {
            *ptr++ = *t;
        }
    }
    *ptr = 0;
    return res;
}

char *push_str(char *s, char *ch)
{
    int len = strlen(s);
    s = (char*)realloc(s, len + strlen(ch) + 1);
    for(int i=0; i<(int)strlen(ch); i++)
        s[len + i] = ch[i];
    s[len + strlen(ch)] = '\0';
    return s;
}
