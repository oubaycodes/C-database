#include "deps/dotenv-c/dotenv.c"

void credential_init()
{
    env_load(".", true);
}

char *getApiKey()
{
    char *apiKey = getenv("CLIENT");
    return apiKey;
}
