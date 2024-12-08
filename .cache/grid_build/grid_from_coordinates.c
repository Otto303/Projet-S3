#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <ctype.h>

// Function to trim spaces and invisible characters from a string
void trim_whitespace(char *str) {
    char *end;

    // Trim leading spaces
    while (isspace((unsigned char)*str)) str++;

    // If all spaces, return an empty string
    if (*str == 0) return;

    // Trim trailing spaces
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) end--;

    // Write new null terminator
    *(end + 1) = '\0';
}

// Function to check if a string ends with a specific suffix (case-insensitive)
int ends_with(const char *str, const char *suffix) {
    size_t str_len = strlen(str);
    size_t suffix_len = strlen(suffix);
    if (str_len < suffix_len) return 0;

    const char *end = str + str_len - suffix_len;
    while (*suffix) {
        if (tolower(*end++) != tolower(*suffix++)) return 0;
    }
    return 1;
}

int parse_coordinates(const char *filename, int *x, int *y) {
    const char *prefix = "letter";
    const char *suffix = ".bmp";

    // Vérifiez si le fichier commence par "letter_" et se termine par ".bmp"
    size_t filename_len = strlen(filename);
    size_t prefix_len = strlen(prefix);
    size_t suffix_len = strlen(suffix);

    if (filename_len > prefix_len + suffix_len &&
        strncmp(filename, prefix, prefix_len) == 0 &&
        strcmp(filename + filename_len - suffix_len, suffix) == 0) {

        // Cherchez les underscores
        const char *underscore1 = strchr(filename + prefix_len, '_');
        if (!underscore1) {
            printf("First underscore not found in: '%s'\n", filename);
            return 0; // Échec du parsing
        }

        const char *underscore2 = strchr(underscore1 + 1, '_');
        if (!underscore2) {
            printf("Second underscore not found in: '%s'\n", filename);
            return 0; // Échec du parsing
        }

        // Convertissez les parties entre les underscores et après le second underscore
        char x_str[16], y_str[16];
        strncpy(x_str, underscore1 + 1, underscore2 - underscore1 - 1);
        x_str[underscore2 - underscore1 - 1] = '\0';
        strncpy(y_str, underscore2 + 1, filename + filename_len - suffix_len - (underscore2 + 1));
        y_str[filename + filename_len - suffix_len - (underscore2 + 1)] = '\0';

        *x = atoi(x_str);
        *y = atoi(y_str);

        // Debugging output
        printf("Parsed successfully: %s -> x=%d, y=%d\n", filename, *x, *y);
        return 1; // Parsing réussi
    } else {
        printf("Filename does not match prefix/suffix: '%s'\n", filename);
    }
    return 0; // Échec du parsing
}

int main() {
    const char *input_folder = "../image_save/lettres";
    const char *output_file = "to_solver.txt";

    // Open the directory
    DIR *dir = opendir(input_folder);
    if (dir == NULL) {
        perror("Error: Unable to open directory");
        return EXIT_FAILURE;
    }

    // Open or create the output file, truncating it if it already exists
    FILE *output = fopen(output_file, "w");
    if (output == NULL) {
        perror("Error: Unable to create or open output file");
        closedir(dir);
        return EXIT_FAILURE;
    }

    struct dirent *entry;
    int files_processed = 0;

    while ((entry = readdir(dir)) != NULL) {
        // Skip special files "." and ".."
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        char filename[256];
        strncpy(filename, entry->d_name, sizeof(filename) - 1);
        filename[sizeof(filename) - 1] = '\0';

        // Clean and trim filename
        trim_whitespace(filename);
        printf("Processing file: '%s'\n", filename); // Debugging output

        int x, y;
        if (parse_coordinates(filename, &x, &y)) {
            // Write the coordinates to the output file
            fprintf(output, "%d %d\n", x, y);
            files_processed++;
        } else {
            printf("Invalid file: '%s'\n", filename); // Debugging output
        }
    }

    // Close the directory and output file
    closedir(dir);
    fclose(output);

    // Summary
    if (files_processed > 0) {
        printf("Successfully wrote %d coordinates to %s\n", files_processed, output_file);
    } else {
        printf("No valid files found in directory %s\n", input_folder);
    }

    return EXIT_SUCCESS;
}
