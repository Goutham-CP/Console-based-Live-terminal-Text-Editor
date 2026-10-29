#include"Header.h"


void EnterKey(){

   if(editor.cursorPos==0){

       if(strlen(editor.cursor->line)==0){

       if(editor.cursor->next==NULL){
             insert_last(NULL);
             editor.cursor = editor.tail;
             editor.cursorPos = strlen(editor.cursor->line);

        }else if(editor.cursor->next !=NULL){

               insertLineBetween(NULL); // in that function I will update curser as new node
                editor.cursorPos = 0;//strlen(editor.cursor->line);
                RefreshFrom(editor.cursor);
               // if I insert line between 1 and 2 and remaining should increment by 1 2 to 3 .....
         }
     }else if(strlen(editor.cursor->line)!=0){

             char *tempBuffer = malloc(strlen(editor.cursor->line)+1);
             strcpy(tempBuffer , editor.cursor->line);
             editor.cursor->line[0] = '\0';

             if(editor.cursor->next ==NULL){
                  printf("\033[%d;1H", editor.cursor->linenumber);
                    printf("\033[K");
                   printf("%s", editor.cursor->line);

                  insert_last(tempBuffer);
                     editor.cursor = editor.tail;
                     editor.cursorPos = 0;//strlen(editor.cursor->line);
                      RefreshFrom(editor.cursor);

             }else if(editor.cursor->next !=NULL){
                   printf("\033[%d;1H", editor.cursor->linenumber);
                    printf("\033[K");
                   printf("%s", editor.cursor->line);

                    fflush(stdout);
                   insertLineBetween(tempBuffer);    // in that function I will update curser as new node
                      editor.cursorPos = 0;//strlen(editor.cursor->line);
                       RefreshFrom(editor.cursor);
                   free(tempBuffer);
              }
        }
    }else if(editor.cursorPos==strlen(editor.cursor->line)){

            if(editor.cursor->next==NULL){
                   insert_last(NULL);
                     editor.cursor = editor.tail;
                     editor.cursorPos = 0;//strlen(editor.cursor->line);

            }else if(editor.cursor->next !=NULL){
                    insertLineBetween(NULL);  // in that function I will update curser as new node
                      editor.cursorPos = 0;//strlen(editor.cursor->line);
                       RefreshFrom(editor.cursor);
            }
   }else if(editor.cursorPos>0 && editor.cursorPos<strlen(editor.cursor->line)){

                int diff = strlen(editor.cursor->line)-editor.cursorPos + 1;
                char *tempBuffer = malloc(diff);
                strcpy(tempBuffer, editor.cursor->line + editor.cursorPos);
                editor.cursor->line[editor.cursorPos] = '\0';
                printf("\033[%d;1H", editor.cursor->linenumber); // move to line start
                printf("\033[K");                                // clear line
                printf("%s", editor.cursor->line);               // print truncated text
                fflush(stdout);

                if(editor.cursor->next==NULL){

                     insert_last(tempBuffer);
                     editor.cursor = editor.tail;
                     if(rec==1){
                        UndoAction *t = UndoHead;

                        while(t != NULL){
                         if(t->line_specific == UndoHead->Freeaddr){
                              t->line_specific = editor.tail;
                         }

                         t = t->next;
                        }

                     }

                     editor.cursorPos = 0;//strlen(editor.cursor->line);

                }else if(editor.cursor->next!=NULL){

                         insertLineBetween(tempBuffer); // in that function I will update curser as new node

                          if(rec==1){
                        UndoAction *t = UndoHead;
                        if(t->backspchar=='\0'){
                         t->Oldpos = 0;
                        }
                        while(t != NULL){
                         if(t->line_specific == UndoHead->Freeaddr){
                              t->line_specific = editor.cursor;
                         }
                         t = t->next;
                        }
                        t = RedoHead;

                     }
                            editor.cursorPos = 0;//strlen(editor.cursor->line);
                            RefreshFrom(editor.cursor);
                 }

                  free(tempBuffer);
      }

  }



  void BackSpace(){


      if(editor.cursorPos==0){

           if(editor.cursor->previous!=NULL){

              if(editor.cursor->previous==editor.head && editor.cursor->next==NULL && strlen(editor.cursor->previous->line)==0){
                 char *dup = strdup(editor.cursor->line);
                 strcpy(editor.head->line , dup);
                 free(dup);
                 editor.cursor->line[0] = '\0';
                 Node *temp = editor.cursor;
                 temp->previous = NULL;
                 editor.head->next = NULL;
                 editor.tail = editor.head;
                 editor.cursor = editor.head;
                 free(temp);

                   printf("\033[1;1H");

                   printf("\033[J");

                   Node *t = editor.head;
                 while (t != NULL) {
                      printf("\033[%d;1H", t->linenumber); // move to line start
                      printf("\033[K");                    // clear line
                      printf("%s", t->line);               // print buffer
                      t = t->next;
                  }
                   fflush(stdout);
                   return;
              }


               int record = strlen(editor.cursor->previous->line);
               editor.cursor->previous->line = realloc(editor.cursor->previous->line,strlen(editor.cursor->previous->line) + strlen(editor.cursor->line) + 1);
               editor.cursorPos = strlen(editor.cursor->previous->line);
               strcat(editor.cursor->previous->line,editor.cursor->line);
               editor.cursor->line[0] = '\0';

               if(editor.cursor->next == NULL){
                 //   printf("\n\n\n\n\n\n\n\n\n\n\n here....\n");
                    editor.cursor = editor.cursor->previous;
                    delete_last();
                    editor.cursorPos = record;//

                 // Redraw merged line
                    printf("\033[%d;1H", editor.cursor->linenumber);
                    printf("\033[K");
                    printf("%s", editor.cursor->line);

                // Clear the old deleted line visually
                    printf("\033[%d;1H", editor.cursor->linenumber + 1);
                    printf("\033[K");

                    fflush(stdout);

               }else if(editor.cursor->next != NULL){

                   deleteMiddle();
                   editor.cursorPos = record;//
                 // Redraw merged line
                printf("\033[%d;1H", editor.cursor->linenumber);
                printf("\033[K");
                printf("%s", editor.cursor->line);

                // Redraw subsequent lines
               Node *t = editor.cursor->next;
               while (t != NULL) {
                   printf("\033[%d;1H", t->linenumber);
                   printf("\033[K");
                   printf("%s", t->line);
                   t = t->next;
               }

               // Clear one extra line (deleted line’s old text)
               printf("\033[%d;1H", editor.tail->linenumber + 1);
               // printf("\033[%d;1H", editor.cursor->linenumber + 2); // note: +2 here
                printf("\033[K");
                fflush(stdout);
             }
        }

      }else if(editor.cursorPos==strlen(editor.cursor->line)){
           editor.cursor->line[strlen(editor.cursor->line)-1] = '\0';
           editor.cursorPos-=1;

    }else if(editor.cursorPos>0 && editor.cursorPos<strlen(editor.cursor->line)){
          ShiftcharFromPosition(editor.cursorPos-1);
    }

}
