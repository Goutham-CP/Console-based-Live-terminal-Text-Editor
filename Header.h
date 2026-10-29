#ifndef HEADER_H
#define HEADER_H
#include <stdio.h>   // printf, getline, etc.
#include <stdlib.h>  // malloc, free, realloc
#include <string.h>
#include <termios.h>
#include<ctype.h>
#include <unistd.h>
#include<signal.h>



typedef struct Node {
   int linenumber;
   char *line;
   struct Node *previous;
   struct Node *next;
}Node;


typedef struct {
    Node *head;       // Pointer to the first line
    Node *tail;       // Pointer to the last line
    Node *cursor;     // Pointer to the current line
    int cursorLine;   // Line number of the cursor
    int cursorPos;    // Column position of the cursor
} TextEditor;



typedef struct Undo{
    char operation;  // Operation type ("insert" or "delete")
    Node *UndoCopyHead;
    Node *UndoCopyTail;
    Node *line_specific;
    Node *specific_end;
    int Oldpos;
    int pastestart;
    int pasteend;
    int fulllinecut;
    int pasteappend;
    struct Undo *next;
    char backspchar;
    Node *Freeaddr;
    Node *ref;
    int cutend;
    char linecut;
    int line1;
    int line2;
    char Undo_Redo;
} UndoAction;



typedef struct UndoRedo{

   UndoAction *addr;
   struct UndoRedo *next;
    struct UndoRedo *tail;

}ChainNode;

extern Node *startcursor;
extern Node *endcursor;
extern int startPos;
extern int endPos;
extern Node *copyHead;
extern Node *copyTail;
extern UndoAction *UndoHead;
extern UndoAction *RedoHead;
extern char copyActive;
extern int PastePos;
extern char rec;
extern int tot;
extern char redo;
extern UndoAction **address;
extern UndoAction **cutAddress;
extern UndoAction **pasteAddress;
extern ChainNode **enterAddress;
extern int enter_st;
extern ChainNode **UndoRedo_Backspace;

extern ChainNode **UndoRedo_Table;

extern int st;
extern char begin_new_status;
extern char pasteFlag;
extern char pasteUndo;
extern char pasteRedoFlag;
extern int cut_st;
extern int paste_st;
extern int hash_st;
extern int back_st;
extern char back;

#define SUCCESS 1
#define FAILURE 0

void EnterKey();
void BackSpace();
int insert_last( char *data);
int insertLineBetween(char *data);
int delete_first();
int deleteMiddle();
int ShiftcharFromPosition(int position);
int delete_last();
int delete_first_Undo();
int delete_first_Redo();

int getch(void);


void MoveCursorRight();
void MoveCursorLeft();
void MoveCursorUp();
void MoveCursorDown();


void InsertCharAtPosition( int position, char ch);

void RefreshLine();
void MoveCursorVisual();
void RefreshFrom(Node *start);



void cut();
void placeCursor();
void paste(Node *copyHead,Node *copyTail);


void copy();
 void  CheckAndFree_OldCopy();
 int insert_Last_Copy( Node *temp);

void Undo();
  void Undo_copy();
  int insert_Last_Copy_Undo( Node *temp);
  void Redo();

  void Redo_Paste(int linenumber, Node *tem);
  void Undo_Paste(int linenumber,Node *tem);


  int free_line();
  int delete_UndoStack();
  int delete_UndoNodes();
  int delete_RedoStack();
  int Delete_copyNodes_Undo(Node **UndoCopyHead, Node **UndoCopyTail);
  int delete_RedoNodes();
  int Delete_copyNodes_Redo(Node **UndoCopyHead, Node **UndoCopyTail);
  int Free_insertHashTable();
  int Free_BackSpaceTable();
  int Free_EnterTable();
  int Free_CutTable();
  int Free_PasteTable();
  int free_CopyNodes_Main();

  int  Save_To_File();
  int Update_Table_Undo();
  int Update_Table_Redo();

extern TextEditor editor;


#endif
