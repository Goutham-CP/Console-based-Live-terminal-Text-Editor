/* =============================================================================
 *  Project : Console Text Editor
 *  Title   : Text Editing with Undo/Redo, Cut/Copy/Paste using Linked Lists
 *  Author  : Goutham C P (26001_059)
 *  Date    : 27-October-2026
 *
 *  Overview:
 *    The Console Text Editor project implements a terminal-based text editor
 *    in C language. It provides essential editing capabilities such as
 *    insert, delete, enter, backspace, cut, copy, paste, and advanced
 *    undo/redo functionality and save to a File while exiting. The editor uses a doubly linked list to
 *    represent text lines and stacks to manage undo/redo operations.
 *
 *  Supported Operations:
 *      - Insert/Delete   : Character-level editing within a line.
 *      - Enter           : Splits a line at the cursor position.
 *      - Backspace       : Deletes characters or merges lines.
 *      - Cut/Copy/Paste  : Supports single-line, multi-line, and word-level operations.
 *      - Undo/Redo       : Reverses or replays editing actions including complex sequences.
 *      - Cursor Movement : Navigate across lines and positions.
 *      - Display Update  : Refreshes terminal view using ANSI escape sequences.
 *
 *  Note :  Single‑character cut, copy, and paste operations are not supported.
 *          For individual single characters, use the Backspace key to remove them and
 *          simply type to insert new ones
 *
 *          Validation checks for cut and copy operation:
 *           - If startcursor and endcursor are the same line and startPos > endPos → invalid selection, skip cut.
 *           - If endcursor line number < startcursor line number → backward selection, skip cut.
 *
 *
 * Keys Used:
 *      - Enter Key       : Splits the current line at cursor position.
 *      - Backspace Key   : Deletes character or merges lines when at position 0.
 *      - Ctrl + C        : Copy operation.
 *                          • First press → Marks/selects the text or line(s).
 *                          • Second press → Performs the actual copy into clipboard.
 *      - Ctrl + X        : Cut operation.
 *                          • First press → Marks/selects the text or line(s).
 *                          • Second press → Performs the actual cut and moves data into clipboard.
 *      - Ctrl + Y        : Paste clipboard content at cursor position.
 *      - Ctrl + Z        : Undo last operation.
 *      - Ctrl + R        : Redo last undone operation.
 *      - Arrow Keys      : Move cursor left, right, up, and down.
 *      - Esc + any Key   : Exit editor safely
 *      - Ctrl + B        : Cancel cut/copy selection.
 *                          • Used when user mistakenly presses Ctrl+C or Ctrl+X (first press).
 *                          • Cancels the pending selection before the second press executes copy/cut.
 *
 *  Features:
 *      - Handles multi-line editing with linked list buffer.
 *      - Robust undo/redo across mixed operations (Enter + Backspace + Paste).
 *      - Clipboard management for cut/copy/paste.
 *      - Optimized traversal for faster runtime.
 *      - Menu-driven interaction for editing operations.
 *
 * Freeing Nodes & File Saving:
 *      - All dynamically allocated nodes (text lines, clipboard buffers, undo/redo stacks)
 *        are freed before program exit to prevent memory leaks.
 *      - Cut/Copy temporary linked lists are released after paste or cancel operations.
 *      - Undo/Redo stacks are cleared once their operations are completed.
 *
 * File Saving:          Save current buffer to a file.
 *                          • Prompts for filename if not already set(If characters apart from alpha numeric,'_','-' other characters  will be filtered automatically and ignored).
 *                          • Appends ".txt" automatically if missing.
 *                          • Handles overwrite confirmation if file already exists.
 *                          • Ensures last line is saved without trailing newline.
 *      - Proper error handling for invalid filenames or failed file operations.
 *      - All opened files are closed safely after saving.
 *
 *  Data Structures:
 *      - Node        : Doubly linked list node storing line content and pointers.
 *      - TextEditor  : Structure maintaining head, tail, cursor, and positions.
 *      - Action/Undo : Stacks for recording operations to support undo/redo.
 *      - Cut/Copy    : Temporary linked list for clipboard storage.
 *
 *  Internal Logic:
 *      - Uses linked lists for dynamic text buffer growth.
 *      - Maintains cursor position and line numbers consistently.
 *      - Stack-based undo/redo ensures reliable state restoration.
 *      - ANSI terminal control for repainting and cursor placement.
 *
 *  Usage:
 *      ./editor
 *      (Editor runs in console with menu-driven options for editing)
 *
 *  Examples:
 *      - Insert text and split lines using Enter.
 *      - Cut multiple lines and paste at a new position.
 *      - Undo a backspace followed by redo to restore text.
 *
 *  Notes:
 *      - Handles tricky edge cases like merging lines at 0th position.
 *      - Undo/Redo stack updated for every operation.
 *      - Cursor position restored correctly after paste and cut operations.
 *
 *  Special Cases:
 *      - Continuous undo after mixed operations (Enter + Backspace) restores
 *        text buffer reliably.
 *      - Redo after undo maintains cursor and line consistency.
 *      - Cut/Copy/Paste operations handle both single-line and multi-line cases.
 * =============================================================================
 */


#include "Header.h"
TextEditor editor;
Node *startcursor = NULL;
Node *endcursor = NULL;
Node *copyHead = NULL;
Node *copyTail = NULL;
char cutActive = 0;
char copyActive = 0;
int tot = 0;
int PastePos;
int startPos;
int endPos;
char rec=0;
char redo = 0;
char HashTableFlag = 0;
int st;
int hash_st;
char begin_new_status = 0;
char pasteFlag=0;
char pasteUndo = 0;
char pasteRedoFlag = 0;
 int cut_st=0;

 int paste_st=0;
 int enter_st = 1;
 int back_st = 1;
 char back = 0;

UndoAction **address;
UndoAction **cutAddress;
UndoAction **pasteAddress;

 ChainNode **UndoRedo_Table;
 ChainNode **UndoRedo_Backspace;


 ChainNode **enterAddress;

UndoAction *UndoHead = NULL;
UndoAction *RedoHead = NULL;


struct termios orig_termios;

void disableRawMode() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
    // restore default Ctrl+C behavior if you want after exit
    struct sigaction sa;
    sa.sa_handler = SIG_DFL;
    sigaction(SIGINT, &sa, NULL);
}

void enableRawMode() {
    tcgetattr(STDIN_FILENO, &orig_termios);
    atexit(disableRawMode);

    struct termios raw = orig_termios;
    raw.c_lflag &= ~(ICANON | ECHO | ISIG);   // disable canonical & echo
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);

    // ignore Ctrl+C termination
    struct sigaction sa;
    sa.sa_handler = SIG_IGN;
    sigaction(SIGINT, &sa, NULL);
}

int getch(void) {
    return getchar(); // now just read, since raw mode is permanent
}


void InsertCharAtPosition( int position, char ch) {
    int len = strlen(editor.cursor->line);
    editor.cursor->line = realloc(editor.cursor->line, len + 2);
    for (int i = len; i >= position; i--) {
        editor.cursor->line[i+1] = editor.cursor->line[i];
    }
    editor.cursor->line[position] = ch;
     editor.cursor->line[len + 1] = '\0';
    editor.cursorPos++;

}





// ====== MAIN ======
int main() {
    // Init one line for demo
    system("clear");
     enableRawMode();
    editor.head = malloc(sizeof(Node));
    editor.head->line = strdup("");
    editor.head->linenumber = 1;
    editor.head->previous = editor.head->next = NULL;
    editor.cursor = editor.head;
    editor.tail = editor.head;
    editor.cursorPos = 0;

     st = 1;
     hash_st = 1;
     HashTableFlag = 1;
    address = malloc(st*sizeof(UndoAction *));
    UndoRedo_Table = malloc(1*sizeof(ChainNode *));
    ChainNode *new =  malloc(sizeof(ChainNode));
    new->next= NULL;
    new->tail = NULL;
    new->addr = NULL;
    UndoRedo_Table[0] = new;

     UndoRedo_Backspace =  malloc(1*sizeof(ChainNode *));
      ChainNode *new_back =  malloc(sizeof(ChainNode));
    new_back->next= NULL;
    new_back->tail = NULL;
    new_back->addr = NULL;
    UndoRedo_Backspace[0] = new_back;

     enterAddress =  malloc(1*sizeof(ChainNode *));
      ChainNode *new_enter =  malloc(sizeof(ChainNode));
    new_enter->next= NULL;
    new_enter->tail = NULL;
    new_enter->addr = NULL;
    enterAddress[0] = new_enter;


    // Main editor loop
    while (1) {
       // printf("...\n");
        char ch = getch();
        //  printf("ch = %d\n", ch);

        if (isprint(ch)) {
            char state = 0;

         UndoAction *new = malloc(sizeof( UndoAction));
            new->backspchar = ch;
            InsertCharAtPosition(editor.cursorPos, ch);
            RefreshLine();
            MoveCursorVisual();


              if(UndoHead==NULL){

        new->operation = 'i';
        new->next = NULL;
        new->UndoCopyHead = NULL;
        new->UndoCopyTail = NULL;
        new->line_specific = editor.cursor;
        new->specific_end = NULL;
        new->Oldpos = editor.cursorPos;
        new->pastestart = 0;
        new->pasteend = 0;
        new->pasteappend = 0;
        UndoHead = new;
        state = 1;

        }else if(UndoHead !=NULL){
              new->operation = 'i';
        new->next = NULL;
        new->UndoCopyHead = NULL;
        new->UndoCopyTail = NULL;
        new->line_specific = editor.cursor;
        new->specific_end = NULL;
        new->Oldpos = editor.cursorPos;
        new->pastestart = 0;
        new->pasteend = 0;
        new->pasteappend = 0;

        UndoAction *temp = UndoHead;
        new->next = temp;
        UndoHead = new;

        }


        new->line1 = editor.cursor->linenumber;
        new->ref = NULL;
         if(HashTableFlag==1){

            if(state==1){

               address = malloc(st*sizeof(UndoAction *));
               address[st-1] = UndoHead;
               st++;
               state = 0;
            }else{
       if(new->line_specific==address[st-2]->line_specific){
          st = st-1;

        address[st-1]=UndoHead;
        st++;
       }else{
            address = realloc(address,st*sizeof(UndoAction *));
        address[st-1]=UndoHead;
        st++;
       }


       }


        HashTableFlag = 0;
        }

         if((new->line1)<=hash_st){

           if(UndoRedo_Table[new->line1-1]->tail == NULL){

                     ChainNode *n = malloc(sizeof(ChainNode));
                    n->tail = NULL;
                    n->addr = UndoHead;
                    n->next = NULL;
                    UndoRedo_Table[new->line1-1]->tail = n;
                      UndoRedo_Table[new->line1-1]->next = n;

            }else{

          ChainNode *n = malloc(sizeof(ChainNode));
          n->tail = NULL;
          n->addr = UndoHead;
          n->next = NULL;
          UndoRedo_Table[new->line1-1]->tail->next =n;
          UndoRedo_Table[new->line1-1]->tail = n;

        }

      }else{

              ChainNode *n;
            for(int i= hash_st+1;i<=new->line1;i++){
             hash_st++;
            UndoRedo_Table = realloc(UndoRedo_Table,(hash_st+1) *sizeof(ChainNode *));
              n = malloc(sizeof(ChainNode));
          n->tail = NULL;
          n->addr = NULL;
          n->next = NULL;
           UndoRedo_Table[i-1] = n;
          }

          ChainNode *n1 = malloc(sizeof(ChainNode));
          n1->tail = NULL;
          n1->addr = UndoHead;
          n1->next = NULL;
          UndoRedo_Table[new->line1-1]->tail = n1;
          UndoRedo_Table[new->line1-1]->next = n1;

            }



           UndoHead->Undo_Redo = 0;

        }
        else if (ch == 127) { // Backspace

              UndoAction *new = malloc(sizeof(UndoAction));

               if(UndoHead==NULL){
                      UndoHead = new;

               }else if(UndoHead!=NULL){

                    UndoAction *temp = UndoHead;
                    new->next = temp;
                    UndoHead = new;
            }


               if(editor.cursorPos==0){
                     new->backspchar = '\0';


               }else{
                new->backspchar = editor.cursor->line[editor.cursorPos - 1];

               }

                BackSpace();
                RefreshLine();
                MoveCursorVisual();
                new->line1 = editor.cursor->linenumber;


     if(new->backspchar=='\0' && editor.cursor!=editor.tail){
      back++;
     }

        new->operation = 'b';
      //  new->next = NULL;
        new->UndoCopyHead = NULL;
        new->UndoCopyTail = NULL;
        new->line_specific = editor.cursor;
        new->specific_end = NULL;
        new->Oldpos = editor.cursorPos;
        new->pastestart = 0;
        new->pasteend = 0;
        new->pasteappend = 0;
        new->Undo_Redo = 0;




            if((new->line1)<=back_st) {


         if(UndoRedo_Backspace[new->line1-1]->tail == NULL){

                     ChainNode *n = malloc(sizeof(ChainNode));
                    n->tail = NULL;
                    n->addr = UndoHead;
                    n->next = NULL;
                    UndoRedo_Backspace[new->line1-1]->tail = n;
                      UndoRedo_Backspace[new->line1-1]->next = n;

            }else{

          ChainNode *n = malloc(sizeof(ChainNode));
          n->tail = NULL;
          n->addr = UndoHead;
          n->next = NULL;
          UndoRedo_Backspace[new->line1-1]->tail->next =n;
          UndoRedo_Backspace[new->line1-1]->tail = n;

        }

      }else{

              ChainNode *n;
            for(int i= back_st+1;i<=new->line1;i++){
             back_st++;
            UndoRedo_Backspace = realloc(UndoRedo_Backspace,(back_st+1) *sizeof(ChainNode *));
              n = malloc(sizeof(ChainNode));
          n->tail = NULL;
          n->addr = NULL;
          n->next = NULL;
           UndoRedo_Backspace[i-1] = n;
          }

          ChainNode *n1 = malloc(sizeof(ChainNode));
          n1->tail = NULL;
          n1->addr = UndoHead;
          n1->next = NULL;
          UndoRedo_Backspace[new->line1-1]->tail = n1;
          UndoRedo_Backspace[new->line1-1]->next = n1;

            }


        }
        else if (ch == '\n') { // Enter
            int c = editor.cursor->linenumber;
            char First_line_new = 0;
            Node *collect = editor.cursor;

            printf("\n");
            EnterKey();
            RefreshLine();
            MoveCursorVisual();

            UndoAction *new = malloc(sizeof(UndoAction));
            new->line1 = c;
   //    printf("\n\n\n\n\n\n\n\n\n\n aft main ent beff.... cursor and cursorPos %d ,",editor.cursor->linenumber);
          if(UndoHead==NULL){
             new->operation = 'e';
        new->next = NULL;
        new->UndoCopyHead = NULL;
        new->UndoCopyTail = NULL;
        new->line_specific = editor.cursor;//editor.cursor;
        new->specific_end = NULL;
        new->Oldpos = editor.cursorPos;
        new->pastestart = 0;
        new->pasteend = 0;
        new->pasteappend = 0;
        UndoHead = new;
         First_line_new = 1;
         begin_new_status = 1;

        }else if(UndoHead !=NULL){
              new->operation = 'e';
        new->next = NULL;
        new->UndoCopyHead = NULL;
        new->UndoCopyTail = NULL;
        new->line_specific = editor.cursor;
        new->specific_end = NULL;
        new->Oldpos = editor.cursorPos;
        new->pastestart = 0;
        new->pasteend = 0;
        new->pasteappend = 0;

        UndoAction *temp = UndoHead;
        new->next = temp;
        UndoHead = new;

        }
        new->ref = NULL;

        HashTableFlag = 1;

        if(First_line_new ==1){
            st = 2;
            address = malloc(st*sizeof(UndoAction *));
            address[0]=NULL;
            address[1] = UndoHead;
            st++;

            First_line_new = 0;
        }else   {                    //if(c==st)

             address = realloc(address,st*sizeof(UndoAction *));
            address[st-1] = UndoHead;
            st++;

        }




         hash_st++;
            UndoRedo_Table = realloc(UndoRedo_Table , hash_st*sizeof(ChainNode *));
            ChainNode *n1 =  malloc(sizeof(ChainNode));
            n1->next= NULL;
            n1->tail = NULL;
            n1->addr = NULL;
            UndoRedo_Table[hash_st-1] = n1;






            if((new->line1)<=enter_st){

            if(enterAddress[new->line1-1]->tail == NULL){

                     ChainNode *n = malloc(sizeof(ChainNode));
                    n->tail = NULL;
                    n->addr = UndoHead;
                    n->next = NULL;
                    enterAddress[new->line1-1]->tail = n;
                      enterAddress[new->line1-1]->next = n;

            }else{

          ChainNode *n = malloc(sizeof(ChainNode));
          n->tail = NULL;
          n->addr = UndoHead;
          n->next = NULL;
          enterAddress[new->line1-1]->tail->next =n;
          enterAddress[new->line1-1]->tail = n;

        }

            }else{

              ChainNode *n;
            for(int i= enter_st+1;i<=new->line1;i++){
             enter_st++;
            enterAddress = realloc(enterAddress,(enter_st+1) *sizeof(ChainNode *));
              n = malloc(sizeof(ChainNode));
          n->tail = NULL;
          n->addr = NULL;
          n->next = NULL;
           enterAddress[i-1] = n;
          }

          ChainNode *n1 = malloc(sizeof(ChainNode));
          n1->tail = NULL;
          n1->addr = UndoHead;
          n1->next = NULL;
          enterAddress[new->line1-1]->tail = n1;
          enterAddress[new->line1-1]->next = n1;

            }

            back_st++;
             UndoRedo_Backspace =  realloc(UndoRedo_Backspace , back_st*sizeof(ChainNode *));
      ChainNode *new_back =  malloc(sizeof(ChainNode));
    new_back->next= NULL;
    new_back->tail = NULL;
    new_back->addr = NULL;
    UndoRedo_Backspace[back_st-1] = new_back;
     new->Undo_Redo = 0;

        }
        else if (ch == 27) { // ESC or Ctrl+C (ASCII 27 or 3)

            int next = getchar();
              if (next == '[') {
        switch(getchar()) {
            case 'A': MoveCursorUp(); break;
            case 'B': MoveCursorDown(); break;
            case 'C': MoveCursorRight(); break;
            case 'D': MoveCursorLeft(); break;
        }
        MoveCursorVisual(); // redraw cursor
    }else{
        system("clear");
        disableRawMode();
         Save_To_File();
        printf("Exiting\n");
        free_line();
        free_CopyNodes_Main();
        delete_UndoStack();
        delete_RedoStack();
        Free_insertHashTable();
        Free_BackSpaceTable();
        Free_EnterTable();
        Free_CutTable();
        Free_PasteTable();
         printf(" Exited successfully\n");
        exit(0);
        break;
    }

        }else if (ch == 24) { // Ctrl+X (ASCII 24)
    if (cutActive == 0) {
        // First press: mark start
        cutActive = 1;
        startcursor = editor.cursor;
        startPos = editor.cursorPos;
        // optional: show feedback
       // printf("\033[H\n");
    } else {
        // Second press: mark end and cut
         endcursor = editor.cursor;
        endPos = editor.cursorPos;

        if(startcursor==endcursor && startPos > endPos){
          cutActive = 0;
          continue;
        }

        if(endcursor->linenumber<startcursor->linenumber){
          cutActive = 0;
          continue;
        }

        if(startcursor==endcursor && startPos==strlen(endcursor->line)-1 && endPos==strlen(endcursor->line)){
          cutActive = 0;
          continue;
        }

        if(startcursor==endcursor && startPos==strlen(endcursor->line) && endPos==strlen(endcursor->line)){
          cutActive = 0;
          continue;
        }

        if(startcursor==endcursor && startPos==endPos){
          cutActive = 0;
          continue;
        }
        UndoAction *new = malloc(sizeof(UndoAction));

        if(UndoHead==NULL){

        new->operation = 'c';
        new->next = NULL;
        new->UndoCopyHead = NULL;
        new->UndoCopyTail = NULL;
        new->line_specific = startcursor;
        new->specific_end = endcursor; // NULL
        new->Oldpos = startPos;
        new->pastestart = 0;
        new->pasteend = 0;
        new->pasteappend = 0;
        new->cutend = endPos;
        UndoHead = new;

        }else if(UndoHead !=NULL){
              new->operation = 'c';
        new->next = NULL;
        new->UndoCopyHead = NULL;
        new->UndoCopyTail = NULL;
        new->line_specific = startcursor;
        new->specific_end = endcursor;
        new->Oldpos = startPos;
        new->pastestart = 0;
        new->pasteend = 0;
        new->pasteappend = 0;
        new->cutend = endPos;

        UndoAction *temp = UndoHead;
        new->next = temp;
        UndoHead = new;

        }

         new->ref = NULL;
         new->line1 = startcursor->linenumber;
         new->line2 = endcursor->linenumber;

        Undo_copy();
        rec = 1;

        cut();   // perform cut
        rec = 0;
        new->line_specific = editor.cursor;
        cutActive = 0;       // reset
       if(cut_st==0){
        cutAddress= malloc((cut_st+1)*sizeof(UndoAction *));
       }else{
        cutAddress = realloc(cutAddress,(cut_st+1)*sizeof(UndoAction *));
       }
       cutAddress[cut_st]= UndoHead;
       cut_st++;
        new->Undo_Redo = 0;

        RefreshFrom(editor.cursor);
        MoveCursorVisual();

    }
}else if (ch == 3) { // Ctrl+C (ASCII 3)

    if (copyActive == 0) {
        // First press: mark start
        copyActive = 1;
        startcursor = editor.cursor;
        startPos = editor.cursorPos;

        // optional feedback

    } else {
        // Second press: mark end and perform copy

        endcursor = editor.cursor;
        endPos = editor.cursorPos;

         if(startcursor==endcursor && startPos > endPos){
          copyActive = 0;
          continue;
        }

        if(endcursor->linenumber<startcursor->linenumber){
          copyActive = 0;
          continue;
        }

         if(startcursor==endcursor && startPos==strlen(endcursor->line)-1 && endPos==strlen(endcursor->line)){
          copyActive = 0;
          continue;
        }

        if(startcursor==endcursor && startPos==strlen(endcursor->line) && endPos==strlen(endcursor->line)){
          copyActive = 0;
          continue;
        }

        if(startcursor==endcursor && startPos==endPos){
          copyActive = 0;
          continue;
        }
          CheckAndFree_OldCopy();

        copy();   // perform copy (fill clipboard)

        copyActive = 0;       // reset flag
        // optional feedback

    }
}
        else if (ch == 'h') { // Example: left arrow substitute
            MoveCursorLeft();
            MoveCursorVisual();
        }
        else if (ch == 'l') { // Example: right arrow substitute
            MoveCursorRight();
            MoveCursorVisual();
        }else if(ch==25){

            if(copyHead==NULL && copyTail==NULL ){
              continue;
            }

             PastePos = editor.cursorPos;

             UndoAction *new = malloc(sizeof(UndoAction));
        if(UndoHead==NULL){

        new->operation = 'p';
        new->next = NULL;
        new->UndoCopyHead = NULL;
        new->UndoCopyTail = NULL;
        new->line_specific = editor.cursor;
        new->Oldpos = 0;
        new->pastestart = PastePos;
        new->pasteend = 0;
        new->pasteappend = 0;
        UndoHead = new;

        }else if(UndoHead !=NULL){
              new->operation = 'p';
        new->next = NULL;
        new->UndoCopyHead = NULL;
        new->UndoCopyTail = NULL;
        new->line_specific = editor.cursor;
        new->Oldpos = 0;
        new->pastestart = PastePos;
        new->pasteend = 0;
        new->pasteappend = 0;

        UndoAction *temp = UndoHead;
        new->next = temp;
        UndoHead = new;

        }

             pasteFlag = 1;
             if(copyHead !=copyTail && strlen(copyTail->line)==0){
                new->linecut = 1;
             }
             new->line1 = editor.cursor->linenumber;
             paste(copyHead,copyTail);
             RefreshFrom(editor.cursor);
             MoveCursorVisual();
             pasteFlag = 0;
             new->specific_end = editor.cursor;
             new->pasteend = editor.cursorPos;
             Node *temp = editor.head;

               if(paste_st==0){
        pasteAddress= malloc((paste_st+1)*sizeof(UndoAction *));
       }else{
        pasteAddress = realloc(pasteAddress,(paste_st+1)*sizeof(UndoAction *));
       }
       pasteAddress[paste_st]= UndoHead;
       paste_st++;
        new->Undo_Redo = 0;


        }else if(ch==26){

              if(UndoHead!=NULL){
                Undo();
                RefreshFrom(editor.cursor);
                MoveCursorVisual();
              }

        }else if(ch==18){

            if(RedoHead!=NULL){
            Redo();
            RefreshFrom(editor.cursor);
            MoveCursorVisual();
            }


        }else if (ch == 2) { // Ctrl+B (ASCII 2)
           if (cutActive == 1) {
           cutActive = 0;   // cancel cut mode

        }

         if (copyActive == 1) {
           copyActive = 0;   // cancel copy mode

        }
}
    }

    return 0;
}



int Save_To_File(){

    char choice;
    char Input;
    char Not_Exist = 0;
    printf("Do You want to save to file (Y/y) OR (N/n) : ");
    scanf(" %c", &choice);

    while(choice !='Y' && choice !='y' && choice!='N' && choice !='n'){

      fflush(stdin);
      printf("Print the valid Option, (Y/y) OR (N/n) ");
      scanf(" %c",&choice);
    }
if (choice == 'n' || choice == 'N') {
    printf("Save cancelled.\n");
    return FAILURE;
}
   getchar();
  char *filename = NULL;
  ssize_t len = 0;
   printf("Enter the file name to save : ");


    getline(&filename,&len,stdin);

    filename[strcspn(filename , "\n")] = '\0';

    int l = strlen(filename);

    int j=0;

    for(int i=0;i<l;i++){

        if (isalnum(filename[i]) || filename[i] == '_' || filename[i] == '-') {
            filename[j++] = filename[i];
        }

    }

    filename[j] = '\0';




    filename = realloc(filename , strlen(filename) + 4);

    strcat(filename , ".txt");

    FILE *fp = fopen(filename,"r");

    if(fp!=NULL){

       fseek(fp,0,SEEK_END);
       long size = ftell(fp);


       if(size>0){


         printf("File %s already exists (%ld bytes). Overwrite?(y/Y)/(n/N): ",filename,size);
         scanf(" %c",&Input);

           while(Input !='Y' && Input !='y' && Input!='N' && Input !='n'){
             fflush(stdin);
             printf("Enter the valid Option, (Y/y) OR (N/n) ");
             scanf(" %c",&Input);
          }

       }
    }else if(fp==NULL){
      Not_Exist = 1;
    }


  if((Input =='Y' || Input=='y') || (Not_Exist==1)){

    Not_Exist = 0;
    fp = fopen(filename, "w");
    if(fp==NULL){

     perror("Error operning file");
     return FAILURE;

    }

   Node *temp = editor.head;
   while(temp!=NULL){
     if(temp->line!=NULL){
      if(temp->next!=NULL){
      fprintf(fp,"%s\n",temp->line);
      }else{
        fprintf(fp,"%s",temp->line);
      }
     }
    temp = temp->next;
   }
   printf("Contents saved in File successfully\n");
   fclose(fp);
  }
   return SUCCESS;

}
