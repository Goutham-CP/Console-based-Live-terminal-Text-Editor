#include"Header.h"



void MoveCursorRight(){

   if(strlen(editor.cursor->line) > 0 && editor.cursorPos < strlen(editor.cursor->line)){

      editor.cursorPos+=1;

   }else if(editor.cursorPos==0 && strlen(editor.cursor->line)==0){

       if(editor.cursor->next !=NULL){

            editor.cursor = editor.cursor->next;
            editor.cursorPos = 0;

       }

   }else if(editor.cursorPos==strlen(editor.cursor->line)){

            if(editor.cursor->next!=NULL){

               editor.cursor = editor.cursor->next;
               editor.cursorPos = 0;
            }
 }

}


void MoveCursorLeft(){

    if(editor.cursorPos==0 && editor.cursor!=editor.head){

       editor.cursor = editor.cursor->previous;
       editor.cursorPos = strlen(editor.cursor->line);

   }else if(editor.cursorPos>0){

         editor.cursorPos -=1;

    }

}

void MoveCursorUp() {
    if (editor.cursor && editor.cursor->previous != NULL) {
        int oldPos = editor.cursorPos;
        editor.cursor = editor.cursor->previous;
        int len = strlen(editor.cursor->line);
        editor.cursorPos = (len >= oldPos) ? oldPos : len;
    }
}

void MoveCursorDown() {
    if (editor.cursor && editor.cursor->next != NULL) {
        int oldPos = editor.cursorPos;
        editor.cursor = editor.cursor->next;
        int len = strlen(editor.cursor->line);
        editor.cursorPos = (len >= oldPos) ? oldPos : len;
    }
}


void RefreshLine() {
   /* printf("\033[%d;1H", editor.cursor->linenumber);
    printf("%s", editor.cursor->line);
    fflush(stdout);*/
     printf("\033[%d;1H", editor.cursor->linenumber);

    // Clear the line completely
    printf("\033[K");

    // Print updated text
    printf("%s", editor.cursor->line);
    fflush(stdout);
}

void MoveCursorVisual() {
    printf("\033[%d;%dH", editor.cursor->linenumber, editor.cursorPos+1);
    fflush(stdout);
}


void RefreshFrom(Node *start) {
    Node *t = start;
    while (t != NULL) {
        printf("\033[%d;1H", t->linenumber); // move to line start
        printf("\033[K");                    // clear line
        printf("%s", t->line);               // print buffer
        t = t->next;
    }
    fflush(stdout);
}