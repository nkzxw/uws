#ifndef __UWS_UTILS_H__
#define __UWS_UTILS_H__
#include "uws.h"
#include <pcre.h>

typedef struct{
    char *src;
    pcre *re;
} regex_map_t;


int wildcmp(const char*, const char*);
void setnonblocking(int sock);
char* strlcat(const char *s1, const char *s2);
char *itoa(const size_t data);
char* get_time_string(time_t *tt);
time_t parse_time_string(char *);
int in_int_array(int array[], int needle, int length);
int gzcompress(char **zdata, size_t *nzdata, char *data, size_t ndata);
int deflatecompress(char **zdata, size_t *nzdata, char *data, size_t ndata);
int in_str_array(char **array, char *needle);
char *get_file_time(const char *path);
bool is_expire(char *time1, char *time2);
int writen(int fd, void *buff, size_t len);
int readn(int fd, void *buff, size_t len);
inline char * nullstring(char *str);
void append_mem_t(memory_t *smem, void *start, size_t len);
inline void  free_mem_t(memory_t *smem);
char* str_replace(char *haystack, char *search, char *replace);
char* preg_replace(char *src, const char *pattern, const char *replace);
bool preg_match(char *src, const char *pattern);
char* base64(char *input);
pcre* get_pcre(const char *src);
inline char * uws_strdup(const char *s);
int lockfile(int fd);
#endif
