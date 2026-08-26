# 📇 Address Book — Contact Management System

A terminal-based **Contact Management System** written in **C**, featuring persistent file storage, structured input validation, and a modular multi-file architecture. Built to manage, search, and organize contacts with a clean CLI experience. 📖

---

## 📋 Overview

This project implements a full-featured address book application with create, edit, search, view, delete, and persistent save/load functionality — backed by a CSV-based storage layer and a menu-driven interface with color-coded terminal feedback. 🖥️

---

## ✨ Features

- ➕ **Create Contact** — add new entries with format-validated name, phone, and email fields
- ✏️ **Edit Contact** — search-then-select workflow to update any existing field
- 🔍 **Search Contact** — lookup by name, phone, or email with match count and result listing
- 📜 **View Contact List** — formatted, tabular display of all saved contacts
- ❌ **Delete Contact** — confirmation-guarded contact removal
- 💾 **Persistent Storage** — contacts saved to and loaded from a CSV file (`Database.csv`) between sessions
- 🔤 **Alphabetical Sorting** — contact list kept in sorted order
- 🎨 **Color-Coded CLI Feedback** — ANSI escape codes for success (green), error (red), and prompt (yellow) messages
- 🛡️ **Input Validation** — dedicated validators for name, phone (with/without country code), and email formatting
- 🚫 **Duplicate Detection** — prevents duplicate phone numbers or email addresses on create/edit

---

## 🔧 Core Techniques Highlighted

- 📦 **Modular architecture** — data model, persistence layer, and business logic are split across separate translation units (`Contact.h`, `File.c`, `Options.c`), each compiled independently and linked via header contracts
- 🧱 **Struct-based data modeling** — `Contact` records are packed into a fixed-size array inside `AddressBook`, giving O(1) indexed access and predictable, contiguous memory layout with no per-record heap allocation
- 🔀 **In-place array compaction on delete** — removing a contact shifts every subsequent struct in the array one position backward in memory to close the gap, preserving contiguity without ever resizing or reallocating the underlying array
- 🔃 **In-place sorting via field-wise memory swaps** — the contact list is reordered by repeatedly scanning for the correct next entry and swapping name fields directly in memory through a temporary buffer, avoiding any auxiliary array or extra struct copies
- 🧠 **Dynamic memory allocation for transient state** — `malloc`/`free` is used to allocate a scratch array sized to the current contact count, used to track matched search-result indices only for the duration of the edit workflow, then explicitly freed
- 📂 **Structured binary-adjacent file I/O** — `fscanf`/`fprintf` read and write struct fields directly against a CSV layout, mapping file bytes to struct members field-by-field rather than parsing free-form text
- 🧵 **Fixed-width buffer string handling** — all string fields are bounded fixed-size char arrays; every `scanf`/`strcpy` call is width-limited (e.g. `%39[^\n]`) to prevent buffer overrun into adjacent struct memory
- 🔠 **Byte-level character classification** — validation walks each input buffer one byte at a time using `<ctype.h>` predicates (`isalpha`, `isdigit`, `isupper`, `isalnum`) to enforce format rules without any string-matching or regex
- 🧭 **State-carrying search → edit pipeline** — a shared match-index buffer produced during search is reused by the edit path, letting a multi-step user flow operate on the same in-memory result set instead of re-scanning
- ⚙️ **Enum-driven control flow** — `SUCCESS`/`FAILURE` return codes propagate through every layer, giving a single consistent contract for error handling across the entire call chain

---

## 📁 Repository Structure

```
Address-Book/
├── main.c            # Menu-driven entry point and program loop
├── Contact.h          # Core data structures, macros, and function declarations
├── Options.c          # Contact operations: create, edit, search, delete, view, validation, sort
├── File.c             # CSV-based persistence layer (load/save)
├── File_handler.h      # File I/O function declarations
```

---

## 🛠️ Building & Running

```bash
gcc main.c Options.c File.c -o address_book
./address_book
```

On first run, if `Database.csv` doesn't exist, the program reports a load failure — create your first contact and save to generate it.

---

## 🎯 Menu Options

```
1. Create Contact
2. Edit Contact
3. Search Contact
4. View Contact List
5. Save Contact
6. Delete Contact
7. Exit Menu
```

---

## 🚀 Possible Extensions

- 🔄 Replace linear array storage with a dynamic/linked-list structure for unbounded contact counts
- 🔐 Add contact categories/tags and favorites
- 📤 Export/import contacts in vCard format
- 🧪 Add unit tests for the validation layer

---

## 👤 About Me

**JITHIN P**
🎓 Electronics and Communication Engineering graduate
📍 Bengaluru, India

**Skilled in:**
- 🔩 Embedded Systems & Bare-Metal Coding
- 💻 Firmware Development
- 🧮 Data Structures & Algorithms (DSA)
- ⚡ C++
- 🔧 C Programming
- 🐧 Linux Internals
- 📡 Protocols: CAN, SPI, I2C, UART

### 🔗 Connect with me

[![GitHub](https://img.shields.io/badge/GitHub-JITH1-181717?style=for-the-badge&logo=github&logoColor=white)](https://github.com/JITH1)
[![LinkedIn](https://img.shields.io/badge/LinkedIn-Connect-0A66C2?style=for-the-badge&logo=linkedin&logoColor=white)](https://www.linkedin.com/in/jithinjith)
