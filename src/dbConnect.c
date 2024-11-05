#include <stdio.h>
#include <libmongoc-1.0/mongoc.h>
#include <libbson-1.0/bson.h>
#include "credentials.c"

// global vars
int connectDatabase(mongoc_client_t **client)
{
    mongoc_server_api_t *api = NULL;
    mongoc_database_t *database = NULL;
    bson_error_t error = {0};
    bson_t *command = NULL;
    bson_t reply = BSON_INITIALIZER;
    int rc = 0;
    bool ok = true;

    // get credentials
    credential_init();
    char *apiKey = getApiKey();
    mongoc_init();

    *client = mongoc_client_new(apiKey);
    if (!client)
    {
        fprintf(stderr, "Failed to create a Mongodb client. \n");
        rc = 1;
        goto cleanup;
    }
    api = mongoc_server_api_new(MONGOC_SERVER_API_V1);
    if (!api)
    {
        fprintf(stderr, "Failed to create a MongoDB server api");
        rc = 1;
        goto cleanup;
    }
    ok = mongoc_client_set_server_api(*client, api, &error);
    if (!ok)
    {
        fprintf(stderr, "error \n%s", error.message);
        rc = 1;
        goto cleanup;
    }
    char *clientName = getClient();
    database = mongoc_client_get_database(*client, clientName);
    if (!database)
    {
        fprintf(stderr, "Failed to get a MongoDB database handle.\n");
        rc = 1;
        goto cleanup;
    }
    command = BCON_NEW("ping", BCON_INT32(1));
    ok = mongoc_database_command_simple(database, command, NULL, &reply, &error);
    if (!ok)
    {
        fprintf(stderr, "error \n%s", error.message);
        rc = 1;
        goto cleanup;
    }
    bson_destroy(&reply);
    printf("Pinged your deployment. You successfully connected to MongoDB!\n");

cleanup:
    bson_destroy(command);
    mongoc_server_api_destroy(api);
    mongoc_database_destroy(database);
    mongoc_cleanup();

    return rc;
}
