# 📒 Address Book Management System

A **menu-driven Address Book Management System developed in C** for managing contacts through a terminal-based interface.

The project demonstrates practical implementation of **C programming, structures, pointers, dynamic memory allocation, file handling, input validation, searching, sorting, and modular programming**.

Contact information is stored in a CSV file, allowing contacts to be loaded when the application starts and saved for future use.

---

## 🚀 Features

* ➕ Create new contacts
* 🔍 Search contacts by:

  * Name
  * Phone number
  * Email
* ✏️ Edit existing contacts
* 👀 View all contacts in a formatted table
* 🗑️ Delete contacts with confirmation
* 💾 Save contacts to a CSV file
* 📂 Load contacts from the CSV file at startup
* 🔤 Sort contacts alphabetically
* ✅ Validate name, phone number, and email
* 🚫 Detect duplicate phone numbers
* 🚫 Detect duplicate email addresses
* 🎨 Colored terminal output using ANSI escape sequences

---

## 🛠️ Technologies Used

### Language

* C

### Core Concepts

* Structures
* Arrays
* Pointers
* Dynamic Memory Allocation
* Functions
* Header Files
* Modular Programming
* File Handling
* String Manipulation
* Character Handling
* Searching
* Sorting
* Input Validation
* Data Persistence

### Standard Libraries

```c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
```

---

## 📂 Project Structure

```text
Address-Book/
│
├── main.c
├── Options.c
├── Contact.h
├── File.c
├── File_handler.h
├── Database.csv
└── README.md
```

### File Description

| File             | Description                                                                          |
| ---------------- | ------------------------------------------------------------------------------------ |
| `main.c`         | Contains the main function and menu-driven program flow                              |
| `Options.c`      | Implements contact operations, validation, searching, editing, deletion, and sorting |
| `Contact.h`      | Defines structures, constants, and function declarations                             |
| `File.c`         | Handles loading and saving contacts                                                  |
| `File_handler.h` | Contains file-handling function declarations                                         |
| `Database.csv`   | Stores contact information                                                           |
| `README.md`      | Project documentation                                                                |

---

## 🧱 Data Structures

### Contact

The `Contact` structure stores the information of an individual contact:

```c
typedef struct
{
    char phone[14];
    char name[40];
    char mail[40];
} Contact;
```

### AddressBook

The `AddressBook` structure maintains the contact list and the current number of contacts:

```c
typedef struct
{
    Contact Contacts[MAX_COUNT];
    int ContactCount;
} AddressBook;
```

The current implementation supports a maximum of **100 contacts**.

---

## 📋 Application Menu

```text
========================================
           ADDRESS BOOK MENU
========================================

1. Create Contact
2. Edit Contact
3. Search Contact
4. View Contact List
5. Save Contact
6. Delete Contact
7. Exit Menu

Enter Your Option:
```

The application loads the existing contacts before entering the main menu loop.

---

## ➕ Create Contact

The application allows users to create a new contact by entering:

* Name
* Phone number
* Email address

The entered information is validated before being stored. The application also checks for duplicate phone numbers and email addresses.

After successfully creating a contact, the contact list is sorted.

---

## 🔍 Search Contact

Contacts can be searched using:

```text
1. Name
2. Phone
3. Mail
```

The application searches the corresponding field and displays matching contacts.

The search functionality is also used when selecting contacts for editing.

---

## ✏️ Edit Contact

Existing contacts can be modified after searching for the required contact.

Available options:

```text
1. Name
2. Phone
3. Email
```

Updated phone numbers and email addresses are validated and checked for duplicates before being stored.

---

## 👀 View Contacts

All contacts are displayed using a formatted table:

```text
+-----+----------------------+----------------+-----------------------------+
| S.No| Name                 | Phone          | Email                       |
+-----+----------------------+----------------+-----------------------------+
| 1   | John Doe             | 9876543210     | john@example.com            |
| 2   | Alex Smith           | 9123456789     | alex@example.com            |
+-----+----------------------+----------------+-----------------------------+
```

The implementation uses formatted terminal output to organize the contact information into columns.

---

## 🗑️ Delete Contact

The deletion process requires the user to:

1. View the contact list.
2. Select a contact using its serial number.
3. Confirm the selected serial number.
4. Delete the contact.
5. Shift the remaining contacts.
6. Update the contact count.

---

## ✅ Input Validation

The project implements separate validation functions for contact information.

### Name Validation

The name is validated for the expected character format and requires the first character to be uppercase.

### Phone Validation

The application supports 10-digit phone numbers and phone numbers with a country code.

Example:

```text
9876543210
+919876543210
```

The implementation checks the length, characters, and starting digits.

### Email Validation

The email validation checks for:

* Alphabetic starting character
* `@`
* `.`
* Valid characters
* Single `@`
* Single `.`
* Characters between `@` and `.`

---

## 🚫 Duplicate Detection

Duplicate phone numbers and email addresses are prevented using the `duplicate()` function.

```c
int duplicate(char *buff, int type, AddressBook *addressBook);
```

---

## 🔤 Sorting

Contacts are sorted alphabetically based on the first character of their names.

```c
void sort_contact(AddressBook *addressBook);
```

The sorting function is called after creating a contact.

---

## 💾 File Handling

The application uses `Database.csv` for persistent storage.

### Loading Contacts

When the application starts, `load_contact()` opens the database file and loads the stored contacts into the `AddressBook`.

```c
FILE *ptr = fopen("Database.csv", "r");
```

### Saving Contacts

The `save_contact()` function writes the contact count and contact information to the CSV file.

```c
FILE *ptr = fopen("Database.csv", "w");
```

Data is stored in the format:

```text
Name,Phone,Email
```

---

## 🔄 Program Flow

```text
                    ┌──────────────┐
                    │    START     │
                    └──────┬───────┘
                           │
                           ▼
                ┌────────────────────┐
                │ Load Database.csv  │
                └─────────┬──────────┘
                          │
                          ▼
                 ┌─────────────────┐
                 │   Display Menu  │
                 └────────┬────────┘
                          │
          ┌───────────────┼────────────────┐
          │               │                │
          ▼               ▼                ▼
       Create           Search            Edit
          │               │                │
          └───────────────┼────────────────┘
                          │
          ┌───────────────┼────────────────┐
          │               │                │
          ▼               ▼                ▼
        View             Save            Delete
          │               │                │
          └───────────────┼────────────────┘
                          │
                          ▼
                   ┌─────────────┐
                   │ Option = 7? │
                   └──────┬──────┘
                          │
                     Yes  │  No
                          │
                    ┌─────▼─────┐
                    │    END    │
                    └───────────┘
```

---

## 🔨 Compilation

Compile using GCC:

```bash
gcc main.c Options.c File.c -o addressbook
```

For compilation with warnings enabled:

```bash
gcc -Wall -Wextra main.c Options.c File.c -o addressbook
```

---

## ▶️ Running the Program

### Linux / macOS

```bash
./addressbook
```

### Windows

```bash
addressbook.exe
```

Make sure `Database.csv` is present in the application's working directory to load previously saved contacts.

---

## 🎯 Learning Objectives

This project was developed to strengthen practical understanding of:

* C programming
* Structures and pointers
* Dynamic memory allocation
* File I/O
* Modular programming
* String manipulation
* Input validation
* Searching and sorting
* Memory management
* Menu-driven application design

---

## 🚧 Future Improvements

* [ ] Add case-insensitive searching
* [ ] Support partial/substring searches
* [ ] Improve sorting using complete string comparison
* [ ] Improve email validation
* [ ] Improve CSV parsing
* [ ] Add import/export functionality
* [ ] Improve error handling

---

# 👨‍💻 About Me

## JITHIN P

**Electronics and Communication Engineering Graduate | Embedded Systems & Firmware**

I am an **Electronics and Communication Engineering graduate** with skills in **Embedded Systems, Firmware Development, C/C++, Data Structures & Algorithms, and Linux Internals**.

I focus on building strong foundations in programming and system-level development, with an emphasis on writing efficient and reliable software.

### 💻 Technical Skills

* **C Programming**
* **C++**
* **Data Structures & Algorithms (DSA)**
* **Embedded Systems**
* **Firmware Development**
* **Linux Internals**

---

## 🔗 Connect With Me

* **LinkedIn:** `https://www.linkedin.com/in/jithinjith/`
* **GitHub:** `https://www.github.com/JITH1`
