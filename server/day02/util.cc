#include <cstdlib>
#include <cstdio>

void errif(bool condition, const char* err_message){
    if (condition){
        perror(err_message);
        exit(EXIT_FAILURE);
    }
}
