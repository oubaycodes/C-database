#include "dbConnect.c"
#include <libmongoc-1.0/mongoc.h>
#include "updateAdminPassword.c"
#include "interface.c"
int main()
{
    mongoc_client_t *client = NULL;

    initTerminalInterface();
    // connectDatabase(&client);
    // updateAdminPassword(client);
    // mongoc_client_destroy(client);
}