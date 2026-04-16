#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/**
 * URL参数解析器
 * 输入：包含http/https超链接的字符串
 * 输出：解析出所有的key-value键值对，每行显示一个
 */

int parse_url(const char* url) {
    int err = 0;
    const char *query_start = strchr(url, '?');

    if (query_start == NULL) {
        err = 1;
        goto exit;
    }

    query_start++;

    size_t len = strlen(query_start);
    char *query = (char*)malloc(len + 1);
    strcpy(query, query_start);

    char *token = strtok(query, "&");

    while (token != NULL) {
        char *eq = strchr(token, '=');
        if (eq != NULL) {
            *eq = '\0';
            printf("key = %s, value = %s\n", token, eq + 1);
        }
        token = strtok(NULL, "&");
    }

    free(query);

exit:
    return err;
}

int main() {
    const char* test_url = "https://cn.bing.com/search?name=John&age=30&city=New+York";

    printf("Parsing URL: %s\n", test_url);
    printf("Parameters:\n");

    parse_url(test_url);

    return 0;
}