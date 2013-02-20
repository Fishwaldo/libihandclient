#ifndef WIN32_SUPPORT_H
#define WIN32_SUPPORT_H
#ifdef WIN32
const char *strcasestr(const char *s, const char *pattern);
char *strdup(char *str);
int strncasecmp(const char *str1, const char *str2, int n);
int strcasecmp(const char *str1, const char *str2);
#endif
#endif