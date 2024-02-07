#include <stdio.h>
#include <string.h>
#include <dirent.h>

#define MAX_LINE_LENGTH 1024

char* generate_file_name(char *file_name, char *note_name) {
	strcat(file_name, "./notes/");
	strcat(file_name, note_name);
	strcat(file_name, ".txt");
	return file_name;
}

int read_note(char *note_name) {
	char file_name[200] = "";
	generate_file_name(file_name, note_name);

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

int create_note(char *note_name, char *note_content) {
	FILE *file;
	char file_name[200] = "";
	generate_file_name(file_name, note_name);

	file = fopen(file_name, "w");
	if (file == NULL) {
		fprintf(stderr, "Error creating note\n");
		return -1;
	}

	fprintf(file, note_content);

	fclose(file);
	
	return 0;
}

int handle_create(int argc, char *argv[]) {
	if (argc == 2) {
		fprintf(stderr, "Must include file content\n");
		return -1;
	}
	if (argc == 3) {
		DIR *d;
		struct dirent *dir;
	d = opendir("./notes");
		int file_count = 0;
		if (d) {
			while((dir = readdir(d)) != NULL) {
				file_count++;	
			}
		}
		char note_name[100] = "";
		snprintf(note_name, 100, "%d", file_count);
		return create_note(note_name, argv[2]);
	} 
	if (strcmp(argv[3], "-n") == 0) {
		return create_note(argv[4], argv[2]);
	}
	return 0;
}

int main(int argc, char *argv[]) {
	if (argc == 1) {
		printf("No action supplied. Enter --help to see options.\n");
		return -1;
	}

	if (strcmp(argv[1], "-c") == 0) {
		return handle_create(argc, argv);
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
