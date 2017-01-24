#include <stdio.h>
#include <dlfcn.h>
#include <stdlib.h>
#include <memory.h>
#include <stdbool.h>

#include "types.h"

int main() {
    char* error_message;
    bool run = true;

    while(run) {
        char* plugin_path;
        size_t _ = 0;

        printf("Enter plugin path(leave empty to quit): ");
        ssize_t plugin_path_len = getline(&plugin_path, &_, stdin);

        if(strlen(plugin_path) > 1) {
            plugin_path[plugin_path_len - 1] = '\0';

            // Load plugin
            void* plugin = dlopen(plugin_path, RTLD_LAZY);
            error_message = dlerror();
            if(!plugin || error_message) {
                printf("%s\n", error_message);
                continue;
            }

            // Load plugin function
            Function* functions = dlsym(plugin, "functions");
            int* functions_count = dlsym(plugin, "functions_count");
            error_message = dlerror();
            if(error_message) {
                printf("%s\n", error_message);
                continue;
            }

            // List function
            for(int i = 0; i < *functions_count; ++i)
                printf("plugin '%s' has '%s' function\n", plugin_path, functions[i].name);

            // Call function
            for(int i = 0; i < *functions_count; ++i) {
                int nprint = functions[i].func("Plugin says: ");
                printf("Plugin returns: %d\n", nprint);
            }

            // Resource cleanup
            free(plugin_path), plugin_path = NULL;
            dlclose(plugin), plugin = NULL;
        } else {
            run = false;
        }
    }
    return EXIT_SUCCESS;
}