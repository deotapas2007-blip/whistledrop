# WhistleDrop

### Anonymous Reporting System in C

WhistleDrop is a simple C-based anonymous reporting system designed around the idea of allowing users to submit reports without revealing their identity.

The project focuses on implementing the core backend logic using beginner-friendly C concepts.

## Features

- Anonymous report submission
- Report categories
- Automatically generated case codes
- Case status tracking
- Moderator login
- View submitted reports
- Update report status
- Add status updates
- Persistent file storage
- Basic input validation

## How It Works

### Reporter

1. Submit an anonymous report
2. Select a category
3. Enter the report description
4. Receive a unique case code
5. Use the case code to check the report status

### Moderator

1. Login using the moderator PIN
2. View reports
3. Change report status
4. Add updates for the reporter

## Report Status Flow

SUBMITTED → UNDER_REVIEW → RESOLVED / DISMISSED

## Technologies

- C
- C Standard Library
- Structures
- Arrays
- Functions
- File Handling

## How to Run

Compile the program:

```bash
gcc main.c -o whistledrop