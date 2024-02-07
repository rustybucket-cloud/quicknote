#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
	if (argc == 1) {
		printf("No action supplied. Enter --help to see options.\n");
		return -1;
	}

	if (strcmp(argv[1], "-c") == 0) {
		printf("Create Note\n");
	} else if (strcmp(argv[1], "-r") == 0) {
		printf("Read Note\n");
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
