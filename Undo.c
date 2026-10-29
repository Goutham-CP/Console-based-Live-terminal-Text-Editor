#include"Header.h"




void Undo(){

     if(UndoHead->operation =='c'){

           if((UndoHead->line1)>editor.tail->linenumber){
              return;
           }

            int record_line;
            PastePos = UndoHead->Oldpos;
            editor.cursor = UndoHead->line_specific;

            if(UndoHead->fulllinecut==1){

              if(UndoHead->UndoCopyHead == UndoHead->UndoCopyTail){

           if(UndoHead->linecut==4){
              PastePos = 0;
            }

             rec = 1;
             editor.cursorPos = PastePos;//
            paste(UndoHead->UndoCopyHead , UndoHead->UndoCopyTail);
            rec = 0;

            }else if(UndoHead->UndoCopyHead != UndoHead->UndoCopyTail){

                if(UndoHead->linecut==5){
                  editor.cursor = UndoHead->line_specific;
                  PastePos = 0;

            }else if(UndoHead->linecut==6){

                editor.cursor = UndoHead->line_specific;
                PastePos = 0;

            }else if(UndoHead->linecut==7){

                     editor.cursor = UndoHead->line_specific;
                     PastePos = 0;

            }else if(UndoHead->linecut==8){

                  editor.cursor = UndoHead->line_specific;
                  PastePos = 0;
            }

               rec = 1;
               editor.cursorPos = PastePos;//
               paste(UndoHead->UndoCopyHead , UndoHead->UndoCopyTail);
               record_line = UndoHead->line_specific->linenumber;
               Node *iterate = UndoHead->line_specific;
               rec = 0;
            }

            }else if(UndoHead->fulllinecut !=1){

              if(UndoHead->UndoCopyHead!=UndoHead->UndoCopyTail){

              if(UndoHead->linecut==9){

               Node *temp = UndoHead->UndoCopyHead;
               char *tempdup = strdup(temp->line);
               char *dup = strdup(editor.cursor->line);
              int shift = PastePos - 0;
              int len = strlen(dup);
              editor.cursor->line[PastePos] = '\0';
              editor.cursor->line = realloc(editor.cursor->line , strlen(editor.cursor->line) + strlen(tempdup)+1);
              strcat(editor.cursor->line , tempdup);
              UndoHead->line_specific = editor.cursor;
                Node *new = malloc(sizeof(Node));
              new->linenumber = editor.cursor->linenumber + 1;
              new->line = strdup("");
              Node *t = editor.cursor->next;
              editor.cursor->next = NULL;

              if(t!=NULL){
              t->previous = NULL;
              }

              new->previous = editor.cursor;
              editor.cursor->next = new;
              new->next = t;
              if(t!=NULL){
              t->previous = new;
              }

              if(t!=NULL){
              if(t->next==NULL){
                editor.tail = t;
              }
            }

              int i = new->linenumber+1;

              while(t!=NULL){
                   t->linenumber = i;
                   i++;
                   t = t->next;
              }

              if(t==NULL){
                editor.tail = new;
              }

               free(tempdup);

                  //OldEndLine
                 printf("\033[%d;1H", editor.cursor->linenumber);
                printf("\033[K");

               // Refresh current line (truncated + appended)
            printf("\033[%d;1H", editor.cursor->linenumber);
            printf("\033[K");
            printf("%s", editor.cursor->line);
                editor.cursor = new;
                PastePos = 0;

            }else if(UndoHead->linecut==10){

               Node *temp = UndoHead->UndoCopyHead;
               char *tempdup = strdup(temp->line);
               char *dup = strdup(editor.cursor->line);
              int shift = PastePos - 0;
              int len = strlen(dup);

              for(int i=0;i<=(len - shift);i++){
                  dup[i] = dup[i+shift];
              }

               //  printf("3.....\n");
              editor.cursor->line[PastePos] = '\0';
              editor.cursor->line = realloc(editor.cursor->line , strlen(editor.cursor->line) + strlen(tempdup)+1);
              strcat(editor.cursor->line , tempdup);
              UndoHead->line_specific = editor.cursor;
              Node *new = malloc(sizeof(Node));
              new->linenumber = editor.cursor->linenumber + 1;
              new->line = strdup("");
              new->previous = editor.cursor;
              editor.cursor->next = new;
              new->next = NULL;

                printf("\033[%d;1H", editor.cursor->linenumber);
                printf("\033[K");


               // Refresh current line (truncated + appended)
            printf("\033[%d;1H", editor.cursor->linenumber);
            printf("\033[K");
            printf("%s", editor.cursor->line);
              editor.cursor = new;
              PastePos = 0;

            }else if(UndoHead->linecut==11){

                   Node *temp =  UndoHead->UndoCopyTail;
                   Node *new = malloc(sizeof(Node));
                   new->linenumber = editor.head->linenumber + 1;
                   new->line = realloc(new->line , strlen(editor.head->line) + strlen(temp->line) + 1);
                   strcpy(new->line , UndoHead->UndoCopyTail->line);
                   strcat(new->line , editor.head->line);
                   editor.head->line[0] = '\0';
                   Node *t = editor.head->next;
                    editor.head->next = new;
                       new->previous = editor.head;

                   if(t!=NULL){
                       t->previous = NULL;
                       new->next = t;
                       t->previous = new;
                   }

                   while(t!=NULL){
                    t->linenumber+=1;
                    t = t->next;
                   }

                   editor.cursor = editor.head;
                   PastePos = 0;

            }else if(UndoHead->linecut==12){

                   Node *temp =  UndoHead->UndoCopyTail;
                   Node *new = malloc(sizeof(Node));
                   new->linenumber = editor.cursor->linenumber + 1;
                   new->line = realloc(new->line , strlen(editor.cursor->line) + strlen(temp->line) + 1);
                   strcpy(new->line , UndoHead->UndoCopyTail->line);
                   strcat(new->line , editor.cursor->line);
                   editor.cursor->line[0] = '\0';
                   Node *t = editor.cursor->next;
                    editor.cursor->next = new;
                       new->previous = editor.cursor;
                        new->next = t;

                   if(t!=NULL){
                       t->previous = NULL;
                       t->previous = new;
                   }

                   while(t!=NULL){
                    t->linenumber+=1;
                    t = t->next;
                   }

                   PastePos = 0;

            }else if(UndoHead->linecut==13){

                      Node *temp =  UndoHead->UndoCopyTail;
                      Node *t = UndoHead->UndoCopyHead;
                     Node *n = editor.cursor->next;
                   Node *new = malloc(sizeof(Node));
                  char *dup = strdup(editor.cursor->line);
                  int shift = UndoHead->Oldpos;
                  int  l = strlen(editor.cursor->line);

                  for(int i=0;i<=(l-shift);i++){
                    dup[i] = dup[i+shift];
                  }

                  editor.cursor->line[UndoHead->Oldpos] = '\0';
                  editor.cursor->line = realloc(editor.cursor->line , strlen(editor.cursor->line) + strlen(t->line) + 1);
                  strcat(editor.cursor->line , t->line);
                   UndoHead->line_specific = editor.cursor;
                   new->linenumber = editor.cursor->linenumber + 1;
                   new->line = realloc(new->line , strlen(dup) + strlen(temp->line) + 1);
                   strcpy(new->line , UndoHead->UndoCopyTail->line);
                   strcat(new->line , dup);
                   free(dup);
                   Node * new_mid = malloc(sizeof(Node));
                   new_mid->linenumber = editor.cursor->linenumber + 1;
                   new_mid->previous = editor.cursor;
                   editor.cursor->next = new_mid;
                   new_mid->next = new;
                   new_mid->line = strdup("");
                   new->previous = new_mid;
                    new->next = n;

                   if(n!=NULL){
                        n->previous = new;
                   }
                   while(n!=NULL){
                    n->linenumber+=1;
                    n = n->next;
                   }

                   printf("\033[%d;1H", editor.cursor->linenumber);  // Move cursor to start of that line
                   printf("\033[K");                  // Clear from cursor to end of line
                   printf("\033[%d;1H", editor.cursor->linenumber);  // Move cursor again
                   printf("%s", editor.cursor->line);             // Print updated text
                   fflush(stdout);                    // Force immediate display
                   editor.cursor = new_mid;
                   PastePos = 0;

            }else if(UndoHead->linecut==14){

               Node *temp = UndoHead->UndoCopyHead;
               Node *t = editor.cursor->next;
               char *tempdup = strdup(temp->line);
               char *dup = strdup(editor.cursor->line);
              int shift = PastePos - 0;
              int len = strlen(dup);
              editor.cursor->line[PastePos] = '\0';
              editor.cursor->line = realloc(editor.cursor->line , strlen(editor.cursor->line) + strlen(tempdup)+1);
              strcat(editor.cursor->line , tempdup);
              UndoHead->line_specific = editor.cursor;
               Node *new = malloc(sizeof(Node));
              new->linenumber = editor.cursor->linenumber + 1;
              new->line = strdup("");
              new->previous = editor.cursor;
              editor.cursor->next = new;
              new->next = NULL;

              if(t!=NULL){
                  new->next = t;
                  t->previous = new;
              }

              while(t!=NULL){
                t->linenumber+=1;
                t= t->next;
              }

              UndoHead->line_specific = editor.cursor;

                printf("\033[%d;1H", editor.cursor->linenumber);
                printf("\033[K");

               // Refresh current line (truncated + appended)
            printf("\033[%d;1H", editor.cursor->linenumber);
            printf("\033[K");
            printf("%s", editor.cursor->line);
              editor.cursor = new;
              PastePos = 0;

            }else if(UndoHead->linecut==15){

                   Node *temp =  UndoHead->UndoCopyTail;
                      Node *t = UndoHead->UndoCopyHead;
                     Node *n = editor.cursor->next;
                   Node *new = malloc(sizeof(Node));
                  char *dup = strdup(editor.cursor->line);
                  int shift = UndoHead->Oldpos;
                  int  l = strlen(editor.cursor->line);

                  for(int i=0;i<=(l-shift);i++){
                    dup[i] = dup[i+shift];
                  }

                  editor.cursor->line[UndoHead->Oldpos] = '\0';
                  editor.cursor->line = realloc(editor.cursor->line , strlen(editor.cursor->line) + strlen(t->line) + 1);
                  strcat(editor.cursor->line , t->line);
                   UndoHead->line_specific = editor.cursor;
                   new->linenumber = editor.cursor->linenumber + 1;
                   new->line = realloc(new->line , strlen(dup) + strlen(temp->line) + 1);
                   strcpy(new->line , UndoHead->UndoCopyTail->line);
                   strcat(new->line , dup);
                   free(dup);

                   Node * new_mid = malloc(sizeof(Node));
                   new_mid->linenumber = editor.cursor->linenumber + 1;
                   new_mid->previous = editor.cursor;
                   editor.cursor->next = new_mid;
                   new_mid->next = new;
                   new_mid->line = strdup("");
                   new->previous = new_mid;
                    new->next = n;

                   if(n!=NULL){
                        n->previous = new;
                   }
                   while(n!=NULL){
                    n->linenumber+=1;
                    n = n->next;
                   }

                   printf("\033[%d;1H", editor.cursor->linenumber);  // Move cursor to start of that line
                   printf("\033[K");                  // Clear from cursor to end of line
                   printf("\033[%d;1H", editor.cursor->linenumber);  // Move cursor again
                   printf("%s", editor.cursor->line);             // Print updated text
                   fflush(stdout);                    // Force immediate display
                   editor.cursor = new_mid;
                   PastePos = 0;

            }else if(UndoHead->linecut==16){

                  Node *temp =  UndoHead->UndoCopyTail;
                      Node *t = UndoHead->UndoCopyHead;
                     Node *n = editor.cursor->next;

                   Node *new = malloc(sizeof(Node));
                  char *dup = strdup(editor.cursor->line);
                  int shift = UndoHead->Oldpos;
                  int  l = strlen(editor.cursor->line);
                  for(int i=0;i<=(l-shift);i++){
                    dup[i] = dup[i+shift];
                  }

                  editor.cursor->line[UndoHead->Oldpos] = '\0';
                  editor.cursor->line = realloc(editor.cursor->line , strlen(editor.cursor->line) + strlen(t->line) + 1);
                  strcat(editor.cursor->line , t->line);
                   UndoHead->line_specific = editor.cursor;
                   new->linenumber = editor.cursor->linenumber + 1;
                   new->line = realloc(new->line , strlen(dup) + strlen(temp->line) + 1);
                   strcpy(new->line , UndoHead->UndoCopyTail->line);
                   strcat(new->line , dup);
                   free(dup);

                   Node * new_mid = malloc(sizeof(Node));
                   new_mid->linenumber = editor.cursor->linenumber + 1;
                   new_mid->previous = editor.cursor;
                   editor.cursor->next = new_mid;
                   new_mid->next = new;
                   new_mid->line = strdup("");
                   new->previous = new_mid;
                    new->next = n;

                   if(n!=NULL){
                        n->previous = new;
                   }
                   while(n!=NULL){
                    n->linenumber+=1;
                    n = n->next;
                   }

                   printf("\033[%d;1H", editor.cursor->linenumber);  // Move cursor to start of that line
                   printf("\033[K");                  // Clear from cursor to end of line
                   printf("\033[%d;1H", editor.cursor->linenumber);  // Move cursor again
                   printf("%s", editor.cursor->line);             // Print updated text
                   fflush(stdout);                    // Force immediate display
                   editor.cursor = new_mid;
                   PastePos = 0;

            }else if(UndoHead->linecut==17){

               Node *temp = UndoHead->UndoCopyHead;
               Node *t = editor.cursor->next;
               char *tempdup = strdup(temp->line);
               char *dup = strdup(editor.cursor->line);
              int shift = PastePos - 0;
              int len = strlen(dup);
              editor.cursor->line[PastePos] = '\0';
              editor.cursor->line = realloc(editor.cursor->line , strlen(editor.cursor->line) + strlen(tempdup)+1);
              strcat(editor.cursor->line , tempdup);
              UndoHead->line_specific = editor.cursor;
               Node *new = malloc(sizeof(Node));
              new->linenumber = editor.cursor->linenumber + 1;
              new->line = strdup("");
              new->previous = editor.cursor;
              editor.cursor->next = new;
              new->next = NULL;

              if(t!=NULL){
                  new->next = t;
                  t->previous = new;
              }

              while(t!=NULL){
                t->linenumber+=1;
                t= t->next;
              }

              UndoHead->line_specific = editor.cursor;

                printf("\033[%d;1H", editor.cursor->linenumber);
                printf("\033[K");

               // Refresh current line (truncated + appended)
            printf("\033[%d;1H", editor.cursor->linenumber);
            printf("\033[K");
            printf("%s", editor.cursor->line);
              editor.cursor = new;
              PastePos = 0;

            }

                rec = 1;
                editor.cursorPos = PastePos;//
                paste(UndoHead->UndoCopyHead , UndoHead->UndoCopyTail);
                record_line = UndoHead->line_specific->linenumber;

               Node *iterate = UndoHead->line_specific;
                      rec = 0;

                       if(UndoHead->linecut==13){
                  editor.cursor = UndoHead->specific_end;
                  editor.cursorPos = UndoHead->cutend;
                }

                    if(UndoHead->linecut==15){
                  editor.cursor = UndoHead->specific_end;
                  editor.cursorPos = UndoHead->cutend;
                }

               } else if(UndoHead->UndoCopyHead==UndoHead->UndoCopyTail){

                      rec = 1;
                      editor.cursorPos = PastePos;//
                      paste(UndoHead->UndoCopyHead , UndoHead->UndoCopyTail);
                      rec = 0;
              }

            }


             Update_Table_Undo();


     }else if(UndoHead->operation == 'p'){

           if((UndoHead->line1)>editor.tail->linenumber || UndoHead->line2>editor.tail->linenumber){
              return;
           }

            startcursor = UndoHead->line_specific;
            endcursor = UndoHead->specific_end;
            startPos = UndoHead -> pastestart;
            endPos = UndoHead->pasteend;
            editor.cursor = startcursor;


           pasteUndo = 1;

            if(UndoHead->linecut==1){

              int l = strlen(endcursor->line);
              char *dup = strdup(endcursor->line);
              endcursor->line = realloc(endcursor->line , strlen(endcursor->line)+2);
              endcursor->line[0] = ' ';
              endcursor->line[1] = '\0';
              strcat(endcursor->line , dup);
              free(dup);
            }

           if(UndoHead->UndoCopyHead==NULL){
           Undo_copy();
           }
           editor.cursorPos = startPos;//
            cut();

           Node *t = editor.cursor;
           pasteUndo = 0;
           Node *temp = UndoHead->UndoCopyHead;


           if(UndoHead->linecut==1){
               UndoHead->UndoCopyTail->line[0] = '\0';
           }

             Update_Table_Undo();

     }else if(UndoHead->operation=='i'){

            if((UndoHead->line1)>editor.tail->linenumber){
              return;
           }

            editor.cursor = UndoHead->line_specific;
            editor.cursorPos = UndoHead->Oldpos;
            BackSpace();

            Update_Table_Undo();

     }else if(UndoHead->operation=='e'){

          if((UndoHead->line1+1)>editor.tail->linenumber){
              return;
           }

           editor.cursor = UndoHead->line_specific;
           editor.cursorPos = UndoHead->Oldpos;
           BackSpace();
           UndoHead->line_specific = editor.cursor;
           UndoHead->Oldpos = editor.cursorPos;
           Update_Table_Undo();

     }else if(UndoHead->operation=='b'){

        if(UndoHead->backspchar=='\0'){
           if((UndoHead->line1)>editor.tail->linenumber){
              return;
           }
        }else if(UndoHead->backspchar!='\0'){
           if((UndoHead->line1)>editor.tail->linenumber){
              return;
           }
        }

       int tt = 0;
           editor.cursor = UndoHead->line_specific; //
           editor.cursorPos = UndoHead->Oldpos; //
           char ch = UndoHead->backspchar;
           if(ch=='\0'){
            rec=1;
             EnterKey();
             UndoHead->line_specific = editor.cursor;
              UndoHead->Oldpos = editor.cursorPos;
             rec = 0;

        Update_Table_Undo();

           }else if(ch !='\0'){
             InsertCharAtPosition(editor.cursorPos, ch);
              UndoHead->line_specific = editor.cursor;
              UndoHead->Oldpos = editor.cursorPos;
                Update_Table_Undo();
           }
     }

    UndoHead->Undo_Redo = 1;
   delete_first_Undo();
}



int delete_first_Undo()
{
    if(UndoHead==NULL){
        return FAILURE;
    }
    UndoAction *temp=UndoHead;
    UndoHead=UndoHead->next;
    temp->next = NULL;
    if(RedoHead==NULL){
        RedoHead = temp;
        temp->next = NULL;
    }else{
      UndoAction *t = RedoHead;
      RedoHead = temp;
      temp->next = t;
    }
  //  free(temp);
}



int delete_first_Redo()
{
    if(RedoHead==NULL){
        return FAILURE;
    }
    RedoHead->Undo_Redo = 0;
    UndoAction *temp=RedoHead;
    RedoHead=RedoHead->next;
    temp->next = NULL;
    if(UndoHead==NULL){
        UndoHead = temp;
        temp->next = NULL;
    }else{
      UndoAction *t = UndoHead;
      UndoHead = temp;
      temp->next = t;
    }
  //  free(temp);
}



void Undo_copy(){

     if(startcursor!=endcursor && startPos==0 && ((( strlen(startcursor->line)==0 || strlen(startcursor->line)>0)) && ((endPos>=strlen(endcursor->line)-1 && strlen(endcursor->line)!=0) )|| (endPos==0 && strlen(endcursor->line)==0))){  // scaenario for cut multiple line whose cursor pos is 0 in startcursor and last character in end character

        Node *temp = startcursor;
        int i = startcursor->linenumber;

        while(i<=endcursor->linenumber){
           insert_Last_Copy_Undo(temp);
             temp = temp->next;
             i+=1;
        }

    }else if(startcursor==endcursor && startPos==0 && endPos>=strlen(startcursor->line)-1 ){

             insert_Last_Copy_Undo(startcursor);

    }else if(startcursor==endcursor && startPos==0 && endPos<strlen(editor.cursor->line)-1 && (startPos !=endPos)){

           if(startPos==0 && endPos<strlen(endcursor->line)-1){
            char *dup = strdup(startcursor->line);
              startcursor->line[endPos+1] = '\0';
              insert_Last_Copy_Undo(startcursor);
              startcursor->line = realloc(startcursor->line , strlen(dup)+1);
              strcpy(startcursor->line,dup);
              free(dup);
           }

      }else if( startcursor==endcursor && (startPos>0 && startPos<strlen(endcursor->line)-1)  && (endPos>=strlen(endcursor->line)-1) ){

                 char *dup = strdup(startcursor->line);
                   int shift  = startPos - 0;
                   int l = strlen(startcursor->line);
         for(int i=0;i<=( l- shift);i++){
               startcursor->line[i] = startcursor->line[i+shift];
         }


              insert_Last_Copy_Undo(startcursor);
              startcursor->line = realloc(startcursor->line , strlen(dup)+1);
              strcpy(startcursor->line,dup);
              free(dup);

           } else if(startcursor==endcursor && (startPos>0 && startPos<strlen(startcursor->line)-1) && (endPos>0 && endPos<strlen(startcursor->line)-1)){

                     char *dup = strdup(startcursor->line);
                   int shift  = startPos - 0;
                   startcursor->line[endPos+1] = '\0';
                   int l = strlen(startcursor->line);

         for(int i=0;i<=( l- shift);i++){
               startcursor->line[i] = startcursor->line[i+shift];
         }

              insert_Last_Copy_Undo(startcursor);
              startcursor->line = realloc(startcursor->line , strlen(dup)+1);
              strcpy(startcursor->line,dup);
              free(dup);

          } else if(startcursor != endcursor && startPos==0 && endPos<strlen(endcursor->line)-1){

          char *dup = strdup(endcursor->line);
          endcursor->line[endPos+1]='\0';
           Node *temp = startcursor;
        int i = startcursor->linenumber;

        while(i<=endcursor->linenumber){
            insert_Last_Copy_Undo(temp);
             temp = temp->next;
             i+=1;
        }

        endcursor->line = realloc(endcursor->line,strlen(dup)+1);
        strcpy(endcursor->line , dup);
        free(dup);

      } else if(startcursor != endcursor && (startPos>0 && startPos<strlen(startcursor->line)) && endPos>=strlen(endcursor->line)-1){

        char *dup1 = strdup(startcursor->line);
        int shift = startPos - 0 ;
        int len = strlen(startcursor->line);

        for(int i=0;i<=(len-shift);i++){
            startcursor->line[i] = startcursor->line[i+shift];
        }

             Node *temp = startcursor;
             int i = startcursor->linenumber;

        while(i<=endcursor->linenumber){
             insert_Last_Copy_Undo(temp);
             temp = temp->next;
             i+=1;
        }

      startcursor->line = realloc(startcursor->line,strlen(dup1)+1);
        strcpy(startcursor->line,dup1);
        free(dup1);

   }else if(startcursor !=endcursor && (startPos>0 && startPos<=strlen(startcursor->line)-1) && (endPos>=0 && endPos<strlen(endcursor->line)-1) ){

        char *dup1 = strdup(startcursor->line);
        char *dup2 = strdup(endcursor->line);

        int shift = startPos - 0 ;
        int len = strlen(startcursor->line);

        for(int i=0;i<=(len-shift);i++){
            startcursor->line[i] = startcursor->line[i+shift];
        }

         endcursor->line[endPos+1]='\0';

             Node *temp = startcursor;
        int i = startcursor->linenumber;

        while(i<=endcursor->linenumber){
             insert_Last_Copy_Undo(temp);
             temp = temp->next;
             i+=1;
        }

        startcursor->line = realloc(startcursor->line,strlen(dup1)+1);
        endcursor->line = realloc(endcursor->line,strlen(dup2)+1);
        strcpy(startcursor->line,dup1);
        strcpy(endcursor->line, dup2);
        free(dup1);
        free(dup2);

      }else if(startcursor != endcursor && (startPos>0 && startPos<=strlen(startcursor->line)-1) && endPos==0 && strlen(endcursor->line)==0){

             char *dup1 = strdup(startcursor->line);
             char *dup2 = strdup(endcursor->line);
             int shift = startPos - 0 ;
             int len = strlen(startcursor->line);

        for(int i=0;i<=(len-shift);i++){
            startcursor->line[i] = startcursor->line[i+shift];
        }

        Node *temp = startcursor;
        int i = startcursor->linenumber;


        while(i<=endcursor->linenumber){
             insert_Last_Copy_Undo(temp);
             temp = temp->next;
             i+=1;
        }

          startcursor->line = realloc(startcursor->line,strlen(dup1)+1);
          strcpy(startcursor->line,dup1);
           free(dup1);

      }else if(startcursor!=endcursor && (startPos==strlen(startcursor->line) && strlen(startcursor->line)!=0) && (((endPos==0  && strlen(endcursor->line)!=0)))){

             char *dup1 = strdup(startcursor->line);
             char *dup2 = strdup(endcursor->line);
            int shift = startPos - 0 ;
            int len = strlen(startcursor->line);

        for(int i=0;i<=(len-shift);i++){
            startcursor->line[i] = startcursor->line[i+shift];
        }

        Node *temp = startcursor;
        int i = startcursor->linenumber;
        endcursor->line[1] = '\0';

        while(i<=endcursor->linenumber){
             insert_Last_Copy_Undo(temp);
             temp = temp->next;
             i+=1;
        }

          startcursor->line = realloc(startcursor->line,strlen(dup1)+1);
          strcpy(startcursor->line,dup1);
          strcpy(endcursor->line,dup2);
           free(dup1);

      }else if(startcursor!=endcursor && ((startPos==strlen(startcursor->line) && strlen(startcursor->line)!=0) && (endPos>0 && endPos<strlen(endcursor->line) && strlen(endcursor->line)!=0))){

             char *dup1 = strdup(startcursor->line);
             char *dup2 = strdup(endcursor->line);
             int shift = startPos - 0 ;
             int len = strlen(startcursor->line);

        for(int i=0;i<=(len-shift);i++){
            startcursor->line[i] = startcursor->line[i+shift];
        }

         Node *temp = startcursor;
        int i = startcursor->linenumber;
        endcursor->line[endPos+1] = '\0';

        while(i<=endcursor->linenumber){
             insert_Last_Copy_Undo(temp);
             temp = temp->next;
             i+=1;
        }

          startcursor->line = realloc(startcursor->line,strlen(dup1)+1);
          strcpy(startcursor->line,dup1);
          strcpy(endcursor->line,dup2);
           free(dup1);
           free(dup2);

      }else if(startcursor!=endcursor && ((startPos==strlen(startcursor->line) && strlen(startcursor->line) !=0) && (endPos==0 && strlen(endcursor->line)==0))){

             char *dup1 = strdup(startcursor->line);
             char *dup2 = strdup(endcursor->line);
             int len = strlen(startcursor->line);
            startcursor->line[0] = startcursor->line[len];
            Node *temp = startcursor;
            int i = startcursor->linenumber;

        while(i<=endcursor->linenumber){
             insert_Last_Copy_Undo(temp);
             temp = temp->next;
             i+=1;
        }

          startcursor->line = realloc(startcursor->line,strlen(dup1)+1);
          strcpy(startcursor->line,dup1);
           free(dup1);

      }else if(startcursor!=endcursor && ((startPos==strlen(startcursor->line) && strlen(startcursor->line)!=0) && (endPos>0 && endPos==strlen(endcursor->line) && strlen(endcursor->line)!=0))){

             char *dup1 = strdup(startcursor->line);
             char *dup2 = strdup(endcursor->line);
             int shift = startPos - 0 ;
             int len = strlen(startcursor->line);

        for(int i=0;i<=(len-shift);i++){
            startcursor->line[i] = startcursor->line[i+shift];
        }

         Node *temp = startcursor;
        int i = startcursor->linenumber;

        while(i<=endcursor->linenumber){
             insert_Last_Copy_Undo(temp);
             temp = temp->next;
             i+=1;
        }

          startcursor->line = realloc(startcursor->line,strlen(dup1)+1);
          strcpy(startcursor->line,dup1);
           free(dup1);
           free(dup2);

      }

    }



    int insert_Last_Copy_Undo( Node *temp){

  if(UndoHead->UndoCopyHead==NULL){
        Node *new = malloc(sizeof(Node));
        new->previous = NULL;
        new->line = strdup(temp->line);
        new->linenumber = 1;
        new->next=NULL;
        UndoHead->UndoCopyHead = new;
        UndoHead->UndoCopyTail=new;
        return SUCCESS;
  }


  if(UndoHead->UndoCopyHead==UndoHead->UndoCopyTail){

     Node *new = malloc(sizeof(Node));
        new->previous = NULL;
       new->line = strdup(temp->line);
        new->next=NULL;
        UndoHead->UndoCopyHead->next = new;
        new->previous = UndoHead->UndoCopyHead;
        new->linenumber = UndoHead->UndoCopyTail->linenumber+1;
         UndoHead->UndoCopyTail=new;
        return SUCCESS;
  }

   if( UndoHead->UndoCopyHead!= UndoHead->UndoCopyTail){

       Node *new = malloc(sizeof(Node));
       new->previous=NULL;
        new->line = strdup(temp->line);
       new->next=NULL;

        UndoHead->UndoCopyTail->next = new;
       new->previous =  UndoHead->UndoCopyTail;
       new->linenumber =  UndoHead->UndoCopyTail->linenumber+1;
        UndoHead->UndoCopyTail=new;
       return SUCCESS;
   }

}




void Undo_Paste(int linenumber,Node *tem){
//  printf("\n\n\n\n\n\n\n\n\n\n\nUndo....line number %d\n",linenumber);

 ChainNode *t;
  if(linenumber<=hash_st){

   ChainNode *temp = UndoRedo_Table[linenumber-1]->next;

             int tt = 0;
           while(temp!=NULL){

                if(temp->addr!=NULL && temp->addr->Undo_Redo==0  && temp->addr!=UndoHead){
                  tt+=1;
                  temp->addr->line_specific = tem;
                }

           temp = temp->next;

           }
        }

         if(back_st>0){

          if((linenumber-1>=0) && linenumber-1<=(back_st-1)){
            t = UndoRedo_Backspace[linenumber - 1]->next;

            while(t!=NULL){
               if(t->addr->Undo_Redo==0 && t->addr->backspchar!='\0'  && t->addr!=UndoHead){
                   t->addr->line_specific = tem;
               }

               if(t->addr->Undo_Redo==0 && t->addr->backspchar=='\0'  && t->addr!=UndoHead){
                   t->addr->line_specific = tem;
               }
              t = t->next;
            }

        }

        }
    //    printf("\n\n\n\n\n\n\n\n\n\n\nback over %d\n",linenumber);

            if(linenumber>1 && ((linenumber-2>=0) && (linenumber-2)<=enter_st-1)){

                t = enterAddress[linenumber - 2]->next;

            while(t!=NULL){

               if(t->addr->Undo_Redo==0  &&  t->addr!=UndoHead){    //&& t->addr->backspchar=='\0'
                   t->addr->line_specific = tem;
               }
              t = t->next;
            }

          }

    // printf("\n\n\n\n\n\n\n\n\n\n\nenter over %d\n",linenumber);
          if(cut_st>0){

              for(int i=0;i<(cut_st/2);i++){

                 if(cutAddress[i]->line1==linenumber && cutAddress[i]->Undo_Redo==0  && cutAddress[i]!=UndoHead){
                     cutAddress[i]->line_specific = tem;
                 }

                 if(cutAddress[i]->line2==linenumber && cutAddress[i]->Undo_Redo==0 && cutAddress[i]!=UndoHead){
                     cutAddress[i]->specific_end = tem;
                 }

                  if(cutAddress[cut_st-1-i]->line1==linenumber  && cutAddress[cut_st-1-i]->Undo_Redo==0 && cutAddress[cut_st-i-1]!=UndoHead){
                     cutAddress[cut_st-1-i]->line_specific = tem;
                 }

                 if(cutAddress[cut_st-1-i]->line2==linenumber && cutAddress[cut_st-1-i]->Undo_Redo==0 && cutAddress[cut_st-i-1]!=UndoHead){
                     cutAddress[cut_st-1-i]->specific_end = tem;
                 }

              }

              if(cut_st % 2 == 1) {
                 int mid = cut_st/2;

            if(cutAddress[mid]->line1 == linenumber && cutAddress[mid]->Undo_Redo == 0 && cutAddress[mid]!=UndoHead) {
                 cutAddress[mid]->line_specific = tem;
           }

          if(cutAddress[mid]->line2 == linenumber  && cutAddress[mid]->Undo_Redo == 0 && cutAddress[mid]!=UndoHead) {
        cutAddress[mid]->specific_end = tem;
        }
    }
            }


              if(paste_st>0){

               for(int i=0;i<(paste_st/2);i++){

                 if(pasteAddress[i]->line1==linenumber && pasteAddress[i]->Undo_Redo==0 && pasteAddress[i]!=UndoHead){
                     pasteAddress[i]->line_specific = tem;
                 }

                  if(pasteAddress[i]->line2 == linenumber && pasteAddress[i]->Undo_Redo == 0 && pasteAddress[i]!=UndoHead) {
                 pasteAddress[i]->specific_end = tem;
                 }

                 if(pasteAddress[paste_st-1-i]->line1==linenumber && pasteAddress[paste_st-1-i]->Undo_Redo==0 && pasteAddress[paste_st-1-i]!=UndoHead){
                     pasteAddress[paste_st-1-i]->line_specific = tem;
                 }

                 if(pasteAddress[paste_st-1-i]->line2 == linenumber  && pasteAddress[paste_st-i-1]->Undo_Redo == 0 && pasteAddress[paste_st-1-i]!=UndoHead) {
                   pasteAddress[paste_st-i-1]->specific_end = tem;
                }

              }

                  if(paste_st % 2 == 1) {
                 int mid = paste_st/2;

            if(pasteAddress[mid]->line1 == linenumber && pasteAddress[mid]->Undo_Redo == 0 && pasteAddress[mid]!=UndoHead) {
                 pasteAddress[mid]->line_specific = tem;
           }

          if(pasteAddress[mid]->line2 == linenumber  && pasteAddress[mid]->Undo_Redo == 0 && pasteAddress[mid]!=UndoHead) {
                pasteAddress[mid]->specific_end = tem;
        }
    }
            }

}



int Update_Table_Undo(){


  if(editor.head==NULL && editor.tail==NULL){
      return FAILURE;
    }

    Node *p1 = editor.head;
    Node *p2 = editor.tail;

    while(p1 != p2){

       if(p1->next == p2 && p2->previous == p1){
      Undo_Paste(p1->linenumber,p1);
      Undo_Paste(p2->linenumber,p2);
        p1 = NULL;
        p2 = NULL;
      break;

      }

      Undo_Paste(p1->linenumber,p1);
      Undo_Paste(p2->linenumber,p2);
       p1 = p1->next;
       p2 = p2->previous;

    }

  if((p1 == p2) && (p1!=NULL && p2!=NULL)){
    Undo_Paste(p1->linenumber,p1);
  }
  return SUCCESS;
}
