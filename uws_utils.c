#include <fcntl.h>
#include <math.h>
#include <time.h>
#include <zlib.h>
#include "uws_utils.h"
int wildcmp(const char* wild, const char* string){
    const char* cp = NULL, *mp = NULL;
    while((*string) && (*wild != '*'))
    {
        if((*wild != *string) && (*wild != '?')) 
        {
            return 0;
        }
        wild++;
        string++;
    }
    while(*string)
    {
        if(*wild == '*')
        {
            if(!*++wild){
                return 1;
            }
            mp = wild;
            cp = string + 1;
        } 
        else if((*wild == *string) || (*wild == '?'))
        {
            wild++;
            string++;
        } else {
            wild = mp;
            string = cp++;
        }
    }
    while(*wild == '*')
    {
        wild++;
    }
    return !*wild;
}
void setnonblocking(int sock)
{
    int opts = fcntl(sock, F_GETFL);
    if (opts < 0) exit_err("fcntl(F_GETFL)");

    opts = (opts | O_NONBLOCK);
    if (fcntl(sock, F_SETFL, opts) < 0) exit_err("fcntl(F_SETFL)");
    return;
}
char* strdup(const char *s){
    char *r;
    if(s == 0 || *s == 0)
        return NULL;
    r = malloc(strlen(s) + 1);
    strcpy(r, s);
    return r;
}
char *strlcat(const char *s1, const char *s2) {
    char *new_str = (char*) calloc(strlen(s1) + strlen(s2) + 1, sizeof(char));
    strcpy(new_str, s1);
    strcat(new_str, s2);
    return new_str;
}
char *itoa(const size_t data) {
    size_t length = (size_t) pow(data, 0.1) + 2;
    char *str = (char*) calloc(length, sizeof(char));
    sprintf(str, "%u", data);
    return str;
}
char* get_time_string() {
    struct tm *cur_time;
    char* buff = (char*) malloc(sizeof(char) * 40);
    time_t tt;
    time(&tt);
    cur_time = localtime(&tt);
    strftime(buff, 40, "%a, %e %b %Y %T %Z", cur_time);
    return buff;
}
int in_int_array(int array[], int needle, int length) {
    int i;
    for(i = 0; i < length; i++) {
        if(array[i] == needle) {
            return i;
        }
    }
    return -1;
}

int gzcompress(char **zdata, size_t *nzdata, char *data, size_t ndata)
{
    z_stream c_stream;
    int err = 0;
    if(data && ndata > 0)
    {
        c_stream.zalloc = Z_NULL;
        c_stream.zfree = Z_NULL;
        c_stream.opaque = Z_NULL;
        c_stream.next_in  = data;
        c_stream.avail_in  = ndata;
        if(
           deflateInit2(&c_stream, Z_DEFAULT_COMPRESSION, Z_DEFLATED, 16 + MAX_WBITS, MAX_MEM_LEVEL, Z_DEFAULT_STRATEGY) != Z_OK

            ) 
            return -1;
        *nzdata = deflateBound(&c_stream, ndata);
        *zdata = (char*) calloc(*nzdata + 1, sizeof(char));

        c_stream.next_out = *zdata;
        c_stream.avail_out  = *nzdata;
        if(Z_STREAM_END != deflate(&c_stream, Z_FINISH)) 
            return -1;
        if(deflateEnd(&c_stream) != Z_OK) return -1;
        return 0;
    }
    return -1;
}
int deflatecompress(char **zdata, size_t *nzdata, char *data, size_t ndata) {
    z_stream c_stream;
    int err = 0;
    if(data && ndata > 0)
    {
        c_stream.zalloc = Z_NULL;
        c_stream.zfree = Z_NULL;
        c_stream.opaque = Z_NULL;
        c_stream.next_in  = data;
        c_stream.avail_in  = ndata;
        if(
           deflateInit(&c_stream, Z_DEFAULT_COMPRESSION) != Z_OK

            ) 
            return -1;
        *nzdata = deflateBound(&c_stream, ndata);
        *zdata = (char*) calloc(*nzdata + 1, sizeof(char));

        c_stream.next_out = *zdata;
        c_stream.avail_out  = *nzdata;
        if(Z_STREAM_END != deflate(&c_stream, Z_FINISH)) 
            return -1;
        if(deflateEnd(&c_stream) != Z_OK) return -1;
        return 0;
    }
    return -1;
}
int in_str_array(char **array, char *needle) {
    int i = 0;
    while(array[i] != NULL) {
        if(strcmp(array[i], needle) == 0) {
            return i;
        }
        i++;
    }
    return -1;
}
