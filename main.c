#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 1024

void generate_file_name(char *file_name, char *note_name) {
	strcat(file_name, "./notes/");
	strcat(file_name, note_name);
	strcat(file_name, ".txt");
}

int handle_read(int argc, char *argv[]) {
	if (argc < 2) {
		return -1;
	}

	char note_name[100] = "";
	strcat(note_name, argv[2]);

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
		if (d == NULL) {
			return -1;
		}

		int file_count = 0;
		while((dir = readdir(d)) != NULL) {
			file_count++;	
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

int handle_search(int argc, char *argv[]) {
	if (argc == 2) {
		fprintf(stderr, "Invalid search\n");
		return -1;
	}

	char search[MAX_LINE_LENGTH] = "";
	strcat(search, argv[2]);
	
	DIR *d;
	struct dirent *dir;
	d = opendir("./notes");
	while((dir = readdir(d)) != NULL) {
		if (strcmp(dir->d_name, ".") == 0 || strcmp(dir->d_name, "..") == 0) continue;
		char file_name[100] = "./notes/";
		strcat(file_name, dir->d_name);
		FILE *file;
		file = fopen(file_name, "r");
		if (file == NULL) {
			fprintf(stderr, "Unable to search files");
			return -1;
		}

		char line[MAX_LINE_LENGTH] = "";
		while(fgets(line, MAX_LINE_LENGTH, file)) {
			if (strstr(line, search) != NULL) {
				printf("%s: %s\n", dir->d_name, line);
			}
		}
		fclose(file);
	}
	closedir(d);

	return 0;
}

int handle_edit(int argc, char *argv[]) {
	char note_name[100] = "";
	strcat(note_name, argv[2]);

	char file_name[100] = "";
	generate_file_name(file_name, note_name);

	FILE *file = fopen(file_name, "r+");
	if (file == NULL) {
		fprintf(stderr, "File not found.");
		return -1;
	}

	int file_content_size = MAX_LINE_LENGTH * 5;
	char* file_content = (char*)malloc(sizeof(char) * file_content_size);
	char line[MAX_LINE_LENGTH] = "";
	while(fgets(line, MAX_LINE_LENGTH, file)) {
		if (strlen(line) + strlen(file_content) > file_content_size) {
			file_content_size = file_content_size * 2;
			file_content = (char*)realloc(file_content, sizeof(char) * file_content_size);
		}
		strcat(file_content, line);
	}

	printf("Current note:\n%s\n", file_content);
	free(file_content);

	char input[MAX_LINE_LENGTH] = "";
	fgets(input, sizeof(input), stdin);

	create_note(note_name, input);

	return 0;
}

enum ACTION {
	CREATE,
	READ,
	EDIT,
	SEARCH,
	HELP,
	INVALID_ACTION,
};

enum ACTION get_action_from_flag(char *flag) {
	if (strcmp(flag, "-c") == 0 || strcmp(flag, "--create") == 0) {
		return CREATE;
	} else if (strcmp(flag, "-r") == 0 || strcmp(flag, "--read") == 0) {
		return READ;
	} else if (strcmp(flag, "-e") == 0 || strcmp(flag, "--edit") == 0) {
		return EDIT;
	} else if (strcmp(flag, "-s") == 0 || strcmp(flag, "--search") == 0) {
		return SEARCH;
	} else if (strcmp(flag, "-h") == 0 || strcmp(flag, "--help") == 0) {
		return HELP;
	} 
	return INVALID_ACTION;
}

int main(int argc, char *argv[]) {
	if (argc == 1) {
		printf("No action supplied. Enter --help to see options.\n");
		return -1;
	}

	switch(get_action_from_flag(argv[1])) {
		case CREATE:
			return handle_create(argc, argv);
		case READ:
			return handle_read(argc, argv);
		case EDIT:
			return handle_edit(argc, argv);
		case SEARCH:
			return handle_search(argc, argv);
		case HELP:
			printf("Help menu\n");
			return 0;
		case INVALID_ACTION:
			printf("Invalid action supplied. Enter --help to see options.\n");
			return -1;
	}

	return 0;
}
