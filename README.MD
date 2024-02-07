# Quicknote

## Learning Objectives
I am doing this project to learn how to do the following things in C:
- Read a file
- Edit a file
- Write a file
- Use input arguments
- Use input flags
- Safely handle user input

## Behavior
1. As a user, I want to be able to create notes quickly.
- When the user enters `-c` followed by text
- then the text is saved to a <number of unamed files + 1>.txt in notes

2. As a user, I want to be able to create named notes.
- When the user enters `-c` followed by text followed by `-n` followed by the name of the note
- then the text is saved to a <note name>.txt in notes

3. As a user, I want to be able to read the notes I have created
- When the user enters `-r` followed by the name of a note
- then the note that is in the file `notes/<note name>.txt` is shown

4. As a user, I want to be able to search the notes I have created
- When the user enters `-s` followed by text
- then the user is shown all the notes that contain that text and their names

5. As a user, I want to be able to edit the notes I have created
- When the user enters `-e` followed by the name of a note
- then the user can edit the text of a note

6. As a user, I want to know the options I have.
- When the user enters `--help` or `-h`
- then the different available commands are shown.
