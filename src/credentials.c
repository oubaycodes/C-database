#include "./../deps/dotenv-c/dotenv.c"

void credential_init()
{
    env_load(".", true);
}

char *getApiKey()
{
    char *apiKey = getenv("CONNECTION_STRING");
    return apiKey;
}
char *getClient()
{
    char *client = getenv("CLIENT");
    return client;
}