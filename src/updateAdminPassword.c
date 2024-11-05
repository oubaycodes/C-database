#include "./../deps/dotenv-c/dotenv.h"
#include <libmongoc-1.0/mongoc.h>
#include <libbson-1.0/bson.h>
#include <stdio.h>
void updateAdminPassword(mongoc_client_t *client)
{
    bson_error_t error;
    mongoc_collection_t *collection;
    bson_t *filter = bson_new();
    mongoc_cursor_t *cursor;
    bson_t const *doc;
    char *str;

    if (!client)
    {
        fprintf(stderr, "Client problem\n");
        goto cleanup;
    }

    collection = mongoc_client_get_collection(client, "main", "admin password");
    cursor = mongoc_collection_find_with_opts(collection, filter, NULL, NULL);

    bson_iter_t iter;
    // data vars
    char const *user;
    char const *password;

    while (mongoc_cursor_next(cursor, &doc))
    {
        u_int8_t const *data = bson_get_data(doc);

        if (bson_iter_init_find(&iter, doc, "user") && BSON_ITER_HOLDS_UTF8(&iter))
        {
            user = bson_iter_utf8(&iter, NULL);
        }
        else
        {
            fprintf(stderr, "no field 'user' found on document\n");
            goto cleanup;
        }

        if (bson_iter_init_find(&iter, doc, "password") && BSON_ITER_HOLDS_UTF8(&iter))
        {
            password = bson_iter_utf8(&iter, NULL);
        }
        else
        {
            fprintf(stderr, "no field 'password' found on document\n");
            goto cleanup;
        }
    }
    if (mongoc_cursor_error(cursor, &error))
    {
        fprintf(stderr, "an error has occurred with the document\n");
        goto cleanup;
    }
    // logic
    printf("%s\n", user);
    printf("%s\n", password);

cleanup:
    mongoc_cursor_destroy(cursor);
    bson_destroy(filter);
    mongoc_collection_destroy(collection);
    mongoc_cleanup();
}