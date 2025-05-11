#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <str.h>
#include <arr.h>
#include <map.h>
#include <OS/utils.h>

char *BANNER = "\x1b[32m╔══════════════════════════════════════════╗\x1b[0m\r\n"
               "\x1b[32m║            NCA | discord.gg/nca          ║\x1b[0m\r\n"
               "\x1b[32m║                 Geo Locator              ║\x1b[0m\r\n"
               "\x1b[32m╚══════════════════════════════════════════╝\x1b[0m\r\n";

int arr_contains(char **arr, const char *q) {
    if(!arr || !q)
        return -1;

    for(int i = 0; arr[i] != NULL; i++) {
        if(!strcmp(arr[i], q))
            return i;
    }

    return -1;
}

int main(int argc, char *argv[]) {
    printf(BANNER);
    if(argc < 2) {
        printf("[ x ] Error, Invalid arguments provided....!\nUsage: %s <host/ip>...!", argv[0]);
        return 1;
    }

    char *IP = argv[1];
    char *_cmd = CreateString((char *[]){"curl -s 'https://freeipapi.com/api/json/", IP, "'", NULL});
    char *resp = ExecuteCmd(_cmd);

    free(_cmd);
    Map json = Decode_OneLine_JSON(resp);

    char *keys[] = {
        "ipVersion", "ipAddress", "longitude", "latitude", "countryName", "countryCode", "timeZone",
        "zipCode", "cityName", "regionName", "isProxy", "continent", "continentCode", "language", NULL
    };

    for(int i = 0; i < json.idx; i++) {
        char *key = ((jKey *)json.arr[i])->key;
        char *value = ((jKey *)json.arr[i])->value;

        if(arr_contains(keys, key) > -1) {
            printf("\x1b[32m%s\x1b[0m -> \x1b[31m%s\x1b[0m\n", key, value);
        }
    }

    json.Destruct(&json);
    free(resp);
    return 0;
}
