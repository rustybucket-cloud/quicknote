#include <stdio.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024

int read_note(char *note_name) {
	char file_name[200] = "./notes/";
	strcat(file_name, note_name);
	strcat(file_name, ".txt");

	FILE *file = fopen(file_name, "r");
	if (file == NULL) {
		fprintf(stderr, "Note does not exist\n");
		return -1;
	}

	char file_content[MAX_LINE_LENGTH];
	while(fgets(file_content, MAX_LINE_LENGTH, file)) {
		printf("%s", file_content);
	}

	fclose(file);

	return 0;
}

int main(int argc, char *argv[]) {
	if (argc == 1) {
		printf("No action supplied. Enter --help to see options.\n");
		return -1;
	}

	if (strcmp(argv[1], "-c") == 0) {
		printf("Create Note\n");
	} else if (strcmp(argv[1], "-r") == 0) {
		if (read_note(argv[2]) != 0) return -1;
	} else if (strcmp(argv[1], "-e") == 0) {
		printf("Edit Note\n");
	} else if (strcmp(argv[1], "-s") == 0) {
		printf("Search Notes\n");
	} else if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
		printf("Help menu\n");
	} else {
		printf("Invalid action supplied. Enter --help to see options.\n");
		return -1;
	}

	return 0;
}
