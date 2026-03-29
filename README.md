# ⏳ Time Travelling File System

A command-line based file system that supports **versioning, snapshots, and rollback functionality**, allowing users to "travel back in time" across file states.

---

## 🚀 Getting Started

### ▶️ Run the Program
- Open `compile.bat` to start the system  
- Close the `.bat` file window to exit the program  


- or install the requirements.txt and `streamlit run app.py`

---

## ⚠️ General Rules

- All commands must be entered in **UPPERCASE**
- If a file does not exist → `NO SUCH FILE EXISTS`
- Invalid commands → an error message is displayed

---

## 📂 File Operations

### 📄 CREATE
```
CREATE FILENAME
```
- Creates a new file  
- ❌ Error if file already exists  

---

### ✏️ INSERT
```
INSERT FILENAME CONTENT
```
- Inserts content into a file  
- ❌ Error if file does not exist  

---

### 📖 READ
```
READ FILENAME
```
- Displays file content  
- ❌ Error if file does not exist  

---

### 🔄 UPDATE
```
UPDATE FILENAME CONTENT
```
- Replaces existing content with new content  
- ❌ Error if file does not exist  

---

## 🧠 Version Control Features

### 📸 SNAPSHOT
```
SNAPSHOT FILENAME MESSAGE
```
- Creates an immutable version of the file  
- Stores a custom message with the snapshot  
- ❌ Error if file does not exist  

---

### ⏪ ROLLBACK
```
ROLLBACK FILENAME [VERSION]
```
- Rolls back to a previous version  

Behavior:
- If no version is provided → rolls back to previous version  
- If current version is root → ❌ error  
- If specified version does not exist → ❌ error  

---

### 📜 HISTORY
```
HISTORY FILENAME
```
- Displays all snapshot versions (including root)  
- ❌ Error if file does not exist  

---

## 📊 File Insights

### 🕒 RECENT FILES
```
RECENT FILES [N]
```
- Displays recently modified files  

Behavior:
- No `N` → shows all files  
- `N > total files` → shows warning + all files  
- `N ≤ 0` → ❌ error  
- `RECENT` alone → prints all files  

---

### 🌳 BIGGEST TREES
```
BIGGEST TREES [N]
```
- Displays files with the highest number of snapshots  

Behavior:
- No `N` → shows all files sorted by snapshot count  
- `N > total files` → shows warning + all files  
- `N ≤ 0` → ❌ error  
- `BIGGEST` alone → prints all files  

---

## 🧩 Summary

This system provides:
- File creation and editing  
- Snapshot-based version control  
- Rollback functionality  
- File history tracking  
- Analytical commands for file activity  

---

## ⚡ Notes

- Commands are **case-sensitive (UPPERCASE only)**  
- Error handling is implemented for invalid inputs and edge cases  