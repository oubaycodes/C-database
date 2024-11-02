#include <stdio.h>
#include <libmongoc-1.0/mongoc.h>
#include <libbson-1.0/bson.h>
#include "credentials.c"

int main()
{

    mongoc_client_t *client = NULL;
    bson_error_t error = {0};
    mongoc_server_api_t *api = NULL;
    mongoc_database_t *database = NULL;
    bson_t *command = NULL;
    bson_t reply = BSON_INITIALIZER;
    int rc = 0;
    bool ok = true;
    // get credentials
    credential_init();
    char *apiKey = getApiKey();
    printf("%s\n", apiKey);
    // mongoc_init();

    // client = mongoc_client_new();
    return 0;
}
