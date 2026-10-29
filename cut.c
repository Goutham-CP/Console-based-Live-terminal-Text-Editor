#include"Header.h"



void cut(){


    if(startcursor!=endcursor && startPos==0 && ((( strlen(startcursor->line)==0 || strlen(startcursor->line)>0)) && ((endPos>=strlen(endcursor->line)-1 && strlen(endcursor->line)!=0) )|| (endPos==0 && strlen(endcursor->line)==0))){  // scaenario for cut multiple line whose cursor pos is 0 in startcursor and last character in end character

       if(rec==1){
       UndoHead->fulllinecut = 1;

       }
       if(startcursor->previous !=NULL && endcursor->next !=NULL){

            Node *t1 = startcursor->next;//
            Node *t2 = endcursor->next;
            startcursor->next = t2;
            t1->previous = NULL;
            t2->previous = NULL;
            t2->previous = startcursor;

            Node *temp = t1;
           // startcursor->previous = NULL;
           startcursor->line[0]='\0';
            endcursor->next = NULL;
            int diff = endcursor->linenumber - startcursor->linenumber;//+1
            char x = startcursor->linenumber;
            char y = endcursor->linenumber;

            UndoAction *endcoll = address[endcursor->linenumber-1];
            Node * tp = endcursor;//temp;


             while (temp != NULL) {
                Node *next = temp->next;
                free(temp);
                temp = next;
             }

             editor.cursor = startcursor;//t2
             editor.cursorPos = 0;
             if(rec==1){
              UndoHead->linecut = 5;
              UndoHead->line_specific = editor.cursor;
              UndoHead->specific_end = editor.cursor;
            }

              if(redo==1){
                    RedoHead->line_specific = editor.cursor;
                    RedoHead->specific_end = editor.cursor;
                  }

          // startcursor = NULL;
          // endcursor = NULL;

            while(t2!=NULL){
             t2->linenumber-=diff;
             t2 = t2->next;
           }

          temp = t2;

          while (temp != NULL) {
             printf("\033[%d;1H", temp->linenumber);
             printf("\033[K");              // clear line
             printf("%s", temp->line);      // print buffer
             temp = temp->next;
           }


         // Finally clear everything below the new tail
          printf("\033[%d;1H", editor.tail->linenumber + 1);
          printf("\033[J");   // clears from here to end of screen
          fflush(stdout);

       if(pasteUndo==1){

                        UndoHead->line_specific = editor.cursor;//editor.cursor->previous
                        UndoHead->pastestart = editor.cursorPos;//PastePos;
                        UndoHead->pasteend = 0;
                        UndoHead->pasteappend = 0;


                  }

         //   editor.cursor= editor.cursor->previous;


       }else if(startcursor->previous !=NULL && endcursor->next==NULL){


                  startcursor->line[0] = '\0';
                  editor.tail = startcursor;
                  editor.cursor = editor.tail;
                  editor.cursorPos = 0;
                  Node *temp = startcursor->next;
                  startcursor->next = NULL;
                 temp->previous = NULL; //

                 if(rec==1){
                  UndoHead->linecut = 6;
                 }


                  while(temp !=NULL){
                    Node *next = temp->next;
                    free(temp);
                    temp = next;
                  }

                  if(rec==1){

                    UndoHead->line_specific = editor.cursor;
                    UndoHead->specific_end  = editor.cursor;

                  }

                    if(redo==1){

                    RedoHead->line_specific = editor.cursor;
                    RedoHead->specific_end = editor.cursor;

                  }
                    if(pasteUndo==1){

                        UndoHead->line_specific = editor.cursor;
                        UndoHead->pastestart = editor.cursorPos;//PastePos;
                        UndoHead->pasteend = 0;
                        UndoHead->pasteappend = 0;


                  }

                    // Clear current line (since you emptied it)
                   printf("\033[%d;1H", editor.tail->linenumber);
                   printf("\033[K");

                  // Clear everything below tail
                   printf("\033[%d;1H", editor.tail->linenumber + 1);
                   printf("\033[J");
                   fflush(stdout);




       }else if(startcursor==editor.head && endcursor->next!=NULL){

                  Node *temp = startcursor->next;
                  temp->previous = NULL;
                  Node *t2 = endcursor->next;
                  endcursor->next = NULL;
                  startcursor->next = t2;
                  t2->previous = startcursor;
                  startcursor->line[0] = '\0';


                   if(rec==1){
                UndoHead->linecut = 7;

              }
                  while(temp!=NULL){
                     Node *next = temp->next;
                    free(temp);
                    temp = next;
                  }
                  editor.cursor = editor.head;
                  editor.cursorPos = 0;
                  temp = editor.head;
                  int i = 1;
                  while(temp!=NULL){
                    temp->linenumber = i;
                    i+=1;
                    temp = temp->next;
                  }

                    if(pasteUndo==1){

                        UndoHead->line_specific = editor.cursor;
                        UndoHead->pastestart = editor.cursorPos;//PastePos;
                        UndoHead->pasteend = 0;
                        UndoHead->pasteappend = 0;


                  }

                   if(rec==1){
                    UndoHead->line_specific = editor.cursor;
                    UndoHead->specific_end  = editor.cursor;
                  }

                    if(redo==1){
                    RedoHead->line_specific = editor.cursor;
                    RedoHead->specific_end = editor.cursor;
                  }

                  temp = editor.head;
                  while (temp != NULL) {
                    printf("\033[%d;1H", temp->linenumber);
                    printf("\033[K");          // clear line
                    printf("%s", temp->line);  // print buffer content
                    temp = temp->next;
                 }

              // clear everything below new tail
                  printf("\033[%d;1H", editor.tail->linenumber + 1);
                  printf("\033[J");
                  fflush(stdout);



                }else if(startcursor->previous==NULL && endcursor->next==NULL){

                  Node *temp = editor.head->next;
                  editor.head->next = NULL;
                  temp->previous = NULL;//


                    if(rec==1){

                UndoHead->linecut = 8;

          }
                  while(temp!=NULL){
                     Node *next = temp->next;
                    free(temp);
                    temp = next;
                  }



                    editor.tail = editor.head;
                    editor.head->line[0] = '\0';
                    editor.cursor = editor.head;
                    editor.cursorPos = 0;

                     if(pasteUndo==1){

                        UndoHead->line_specific = editor.cursor;
                        UndoHead->pastestart = editor.cursorPos;//PastePos;
                        UndoHead->pasteend = 0;
                        UndoHead->pasteappend = 0;


                  }

                     if(rec==1){
                    UndoHead->line_specific = editor.cursor;
                    UndoHead->specific_end  = editor.cursor;
                  }

                    if(redo==1){
                    RedoHead->line_specific = editor.cursor;
                    RedoHead->specific_end = editor.cursor;
                  }
                    // Clear current line (head)
                    printf("\033[%d;1H", editor.head->linenumber);
                    printf("\033[K");   // clear line
                   // optional: reprint head->line if you want to show empty string
                   printf("%s", editor.head->line);
                   // Clear everything below head
                   printf("\033[%d;1H", editor.head->linenumber + 1);
                   printf("\033[J");   // clear rest of screen
                   fflush(stdout);


       }



    }else if(startcursor==endcursor && startPos==0 && endPos>=strlen(endcursor->line)-1 && strlen(endcursor->line)!=0 ){

          UndoHead->fulllinecut = 1;

           if(startcursor==editor.head && editor.head==editor.tail){
            editor.head->line[0] = '\0';
            editor.cursor = editor.head;
            editor.cursorPos = 0;

            if(rec==1){
              UndoHead->linecut = 4;
              UndoHead->line_specific = editor.cursor;
              UndoHead->specific_end = editor.cursor;  //UndoHead->specific_end
            }

            if(redo==1){

              RedoHead->line_specific = editor.cursor;
              RedoHead->specific_end = editor.cursor;
            }

            printf("\033[%d;1H", editor.head->linenumber);
            printf("\033[K");   // clear the line
            printf("%s", editor.head->line);   // print empty string (optional)

              // Clear everything below
            printf("\033[%d;1H", editor.head->linenumber + 1);
            printf("\033[J");   // wipe rest of screen
            fflush(stdout);

             if(pasteUndo==1){

                        UndoHead->line_specific = editor.cursor;
                        UndoHead->pastestart = editor.cursorPos;//PastePos;
                        UndoHead->pasteend = 0;
                        UndoHead->pasteappend = 0;


                  }
           }else if(startcursor==editor.head && editor.head !=editor.tail){

                 editor.head->line[0] = '\0';

                 if(rec==1){
                   UndoHead->Freeaddr = editor.head->next;
                 }
                  if(redo==1){
                  RedoHead->Freeaddr = editor.head->next;
                  }

                  editor.cursor = editor.head;

                  if(rec==1){
              UndoHead->linecut = 4;
              UndoHead->line_specific = editor.cursor;
              UndoHead->specific_end = editor.cursor;  //UndoHead->specific_end
            }

                    if(redo==1){
              RedoHead->line_specific = editor.cursor;
              RedoHead->specific_end = editor.cursor;
            }
                  editor.cursorPos = 0;
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

                   if(pasteUndo==1){

                        UndoHead->line_specific = editor.cursor;
                        UndoHead->pastestart = editor.cursorPos;//PastePos;
                        UndoHead->pasteend = 0;
                        UndoHead->pasteappend = 0;


                  }

                   return;

           }else if(startcursor==editor.tail && editor.head !=editor.tail){

                 editor.tail->line[0] = '\0';


                 // editor.tail->line[0] = '\0';
                  editor.cursor = editor.tail;
                  editor.cursorPos = 0;
                  if(rec==1){
                    UndoHead->linecut = 4;
                    UndoHead->line_specific = editor.cursor;
                    UndoHead->specific_end = editor.cursor;
                  }

                  if(redo==1){
                    RedoHead->line_specific = editor.cursor;
                    RedoHead->specific_end = editor.cursor;
                  }

                  printf("\033[%d;1H", editor.tail->linenumber);
                  printf("\033[K");   // clear the line
                  printf("%s", editor.tail->line);   // prints empty string (optional)

                 // Clear everything below tail
                 printf("\033[%d;1H", editor.tail->linenumber + 1);
                 printf("\033[J");   // wipe rest of screen
                 fflush(stdout);
                 if(pasteUndo==1){

                        UndoHead->line_specific = editor.cursor;
                        UndoHead->pastestart = editor.cursorPos;//PastePos;
                        UndoHead->pasteend = 0;
                        UndoHead->pasteappend = 0;


                  }


           }else if(startcursor !=editor.head && startcursor !=editor.tail){
                if(rec==1){
                UndoHead->linecut = 4;
                }

                 editor.cursor->line[0] = '\0';
                 editor.cursorPos = 0;


                    if(pasteUndo==1){

                        UndoHead->line_specific = editor.cursor;
                        UndoHead->pastestart = editor.cursorPos;//PastePos;
                        UndoHead->pasteend = 0;
                        UndoHead->pasteappend = 0;


                  }

                     if(rec==1){
                    UndoHead->line_specific = editor.cursor;
                    UndoHead->specific_end = editor.cursor;
                  }

                  if(redo==1){
                    RedoHead->line_specific = editor.cursor;
                    RedoHead->specific_end = editor.cursor;
                  }

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
                //RefreshFrom(editor.cursor);
                fflush(stdout);

     }


    }else if(startcursor==endcursor && startPos==0 && endPos<strlen(editor.cursor->line)-1){

         int shift  = endPos - startPos +1;
         int l = strlen(startcursor->line);
         for(int i=0;i<= (l - shift);i++){

               startcursor->line[i] = startcursor->line[i+shift];

         }

          if(rec==1){
              UndoHead->linecut = 1;
          }
      editor.cursor = startcursor;
      editor.cursorPos = 0;

      printf("\033[%d;1H", editor.cursor->linenumber);  // move to start of line
      printf("\033[K");                                 // clear the line
      printf("%s", editor.cursor->line);                // print updated text
      // Finally, move cursor to correct position (0th here)
      printf("\033[%d;%dH", editor.cursor->linenumber, editor.cursorPos + 1);
      fflush(stdout);

                  if(rec==1){
                    UndoHead->line_specific = editor.cursor;
                    UndoHead->specific_end  = editor.cursor;
                  }

                    if(redo==1){
                    RedoHead->line_specific = editor.cursor;
                    RedoHead->specific_end = editor.cursor;
                  }

       if(pasteUndo==1){

                        UndoHead->line_specific = editor.cursor;
                        UndoHead->pastestart = editor.cursorPos;//PastePos;
                        UndoHead->pasteend = 0;
                        UndoHead->pasteappend = 0;


                  }

    }else if(startcursor==endcursor && startPos>0 && endPos<strlen(editor.cursor->line)-1){

           int shift  = endPos - startPos +1;
           int l = strlen(startcursor->line);
             for(int i=startPos;i<=(l - shift);i++){

               startcursor->line[i] = startcursor->line[i+shift];

         }

          if(rec==1){
              UndoHead->linecut = 2;
          }

      editor.cursor = startcursor;
      editor.cursorPos = startPos;

      // Refresh the current line
      printf("\033[%d;1H", editor.cursor->linenumber);  // move to start of line
      printf("\033[K");                                 // clear the line
      printf("%s", editor.cursor->line);                // print updated text

      // Finally, move cursor to correct position (startPos in this case)
     printf("\033[%d;%dH", editor.cursor->linenumber, editor.cursorPos + 1);
     fflush(stdout);

                  if(rec==1){
                  UndoHead->line_specific = editor.cursor;
                  UndoHead->specific_end  = editor.cursor;
                  }

                    if(redo==1){
                    RedoHead->line_specific = editor.cursor;
                    RedoHead->specific_end = editor.cursor;
                  }

     if(pasteUndo==1){

                        UndoHead->line_specific = editor.cursor;
                        UndoHead->pastestart = editor.cursorPos;//PastePos;
                        UndoHead->pasteend = 0;
                        UndoHead->pasteappend = 0;


                  }

    }else if(startcursor==endcursor && startPos>0 && endPos<=strlen(editor.cursor->line)){

          if(rec==1){
            UndoHead->linecut = 3;
          }

             startcursor->line[startPos] = '\0';

             editor.cursor = startcursor;
             editor.cursorPos = startPos;   // cursor stays where the cut begins

            // Refresh the current line
             printf("\033[%d;1H", editor.cursor->linenumber);  // move to start of line
             printf("\033[K");                                 // clear the line
             printf("%s", editor.cursor->line);                // print truncated text

            // Finally, move cursor to correct position (startPos)
             printf("\033[%d;%dH", editor.cursor->linenumber, editor.cursorPos + 1);

             fflush(stdout);

                  if(rec==1){
                    UndoHead->line_specific = editor.cursor;
                    UndoHead->specific_end  = editor.cursor;
                  }

                    if(redo==1){
                    RedoHead->line_specific = editor.cursor;
                    RedoHead->specific_end = editor.cursor;
                  }

             if(pasteUndo==1){

                        UndoHead->line_specific = editor.cursor;
                        UndoHead->pastestart = editor.cursorPos;//PastePos;
                        UndoHead->pasteend = 0;
                        UndoHead->pasteappend = 0;


                  }


    }else if(startcursor!=endcursor && (startPos>0 && startPos<strlen(startcursor->line)) && endPos>=strlen(endcursor->line)-1){

          if(endcursor!=editor.tail){
              Node *temp = startcursor->next;
              startcursor->next = NULL;
              Node *coll = endcursor->next;

              temp->previous = NULL;

             int OldEndLine = endcursor->next->linenumber;
              endcursor->next = NULL;
              startcursor->line[startPos] = '\0';

              startcursor->next = coll;
              coll->previous = startcursor;
               for (int j = startcursor->linenumber + 1; j <= editor.tail->linenumber; j++) {   //OldEndLine
                 printf("\033[%d;1H", j);
                printf("\033[K");
               }

                if(rec==1){

                UndoHead->linecut = 9;

          }

                while (temp != NULL) {
                  Node *next = temp->next;  // save next before free
                  free(temp);
                  temp = next;              // move forward safely
                }

                editor.cursor = startcursor;
                editor.cursorPos = startPos;

                 if(rec==1){
                    UndoHead->line_specific = editor.cursor;
                    UndoHead->specific_end  = editor.cursor;
                  }

                    if(redo==1){
                    RedoHead->line_specific = editor.cursor;
                    RedoHead->specific_end = editor.cursor;
                  }

                  int  i = startcursor->linenumber+1;

                  while(coll!=NULL){
                      coll->linenumber = i;
                      i++;
                      if(coll->next==NULL){
                        editor.tail = coll;
                        break;
                       }
                       coll = coll->next;

                  }

 // Refresh current line (truncated + appended)
    printf("\033[%d;1H", startcursor->linenumber);
    printf("\033[K");
    printf("%s", startcursor->line);

    // Redraw subsequent lines
    Node *q = startcursor->next;
    while (q != NULL) {
        printf("\033[%d;1H", q->linenumber);
        printf("\033[K");
        printf("%s", q->line);
        q = q->next;
    }

    // Clear one extra line after the new tail (safety wipe)
    printf("\033[%d;1H", i);
    printf("\033[K");
    i=i-1;
    // Buffer shrank → clear leftover lines
    for (int j = i; j <= OldEndLine; j++) {
        printf("\033[%d;1H", j);
        printf("\033[K");
    }


    printf("\033[%d;%dH", startcursor->linenumber, startPos + 1);

    fflush(stdout);
    if(pasteUndo==1){

                        UndoHead->line_specific = editor.cursor;
                        UndoHead->pastestart = editor.cursorPos;//PastePos;
                        UndoHead->pasteend = 0;
                        UndoHead->pasteappend = 0;


                  }



          }else if(endcursor==editor.tail){

               startcursor->line[startPos] = '\0';
               Node *temp = startcursor->next;
               startcursor->next = NULL;
               temp->previous = NULL;
               editor.tail = startcursor;

                if(rec==1){
                UndoHead->linecut = 10;
          }
               while(temp!=NULL){
                  Node *next = temp->next;
                  free(temp);
                  temp = next;
               }

               editor.cursorPos = startPos;
               editor.cursor = startcursor;


               if(rec==1){
                    UndoHead->line_specific = editor.cursor;
                    UndoHead->specific_end  = editor.cursor;
                  }

                    if(redo==1){
                    RedoHead->line_specific = editor.cursor;
                    RedoHead->specific_end = editor.cursor;
                  }

               // Refresh current line (truncated)
printf("\033[%d;1H", startcursor->linenumber);
printf("\033[K");
printf("%s", startcursor->line);

// Clear everything below tail
printf("\033[%d;1H", startcursor->linenumber + 1);
printf("\033[J");   // clears to bottom of screen

// Place cursor back at correct position
printf("\033[%d;%dH", startcursor->linenumber, startPos + 1);

fflush(stdout);
 if(pasteUndo==1){

                        UndoHead->line_specific = editor.cursor;
                        UndoHead->pastestart = editor.cursorPos;//PastePos;
                        UndoHead->pasteend = 0;
                        UndoHead->pasteappend = 0;


                  }

          }


      }else if(startcursor != endcursor && startPos==0  && endPos<strlen(endcursor->line)-1){

          if(startcursor==editor.head){

                Node *coll = endcursor->next;
               endcursor->next = NULL;
               if(coll!=NULL){
                coll->previous = NULL;
               }

              int len = strlen(endcursor->line);
               int shift = endPos - 0 + 1;

               for(int i=0;i<=len-shift;i++){
                  endcursor->line[i] = endcursor->line[i+shift];
               }


               Node *temp = startcursor->next;
               temp->previous =NULL;
               startcursor->next = NULL;
               Node *t = endcursor;

                if(rec==1){
                UndoHead->linecut = 11;
          }

              char *dup = strdup(t->line);
              startcursor->line[0] = '\0';
              startcursor->line =  realloc(startcursor->line, strlen(dup) + 1);
             strcpy(startcursor->line, dup);
             free(dup);

               startcursor->linenumber = 1;

              for (int j = editor.head->linenumber + 1; j <= editor.tail->linenumber; j++) {
                printf("\033[%d;1H", j);
                printf("\033[K");
              }

               while(temp !=NULL){
                Node *next = temp->next;
                free(temp);
                temp = next;
               }


               if(coll==NULL){

                  editor.cursor = editor.head;
                  editor.cursorPos = 0;
                  editor.tail = editor.head;  //t

printf("\033[%d;1H", editor.head->linenumber);
printf(".....10....\n");
printf("\033[K");
printf("%s", editor.head->line);
//printf(".....11....\n");

// Clear everything below (since no nodes remain)
printf("\033[%d;1H", editor.head->linenumber + 1);
printf("\033[J");
//printf(".....12....\n");
// Cursor at start of new head line
printf("\033[%d;%dH", editor.head->linenumber, 1);
fflush(stdout);

              }else if(coll!=NULL){
                editor.head->next = coll;
                coll->previous = editor.head;
                 editor.cursor = editor.head;
                  editor.cursorPos = 0;
                 int i=2;
                  while(coll!=NULL){
                    coll->linenumber = i;
                    i++;
                    coll = coll->next;
                  }

    printf("\033[%d;1H", editor.head->linenumber);
    printf("\033[K");
    printf("%s", editor.head->line);
    //printf("next is %s\n",editor.head->next->line);

    // Redraw subsequent lines
    Node *q = editor.head->next;
    while (q != NULL) {
        printf("\033[%d;1H", q->linenumber);
        printf("\033[K");
        printf("%s", q->line);
        q = q->next;
    }


    // Place cursor at start of new head line
    editor.cursor = editor.head;
    editor.cursorPos = 0;
     if(rec==1){
                    UndoHead->line_specific = editor.cursor;
                    UndoHead->specific_end  = editor.cursor;
                  }

                    if(redo==1){
                    RedoHead->line_specific = editor.cursor;
                    RedoHead->specific_end = editor.cursor;
                  }
    printf("\033[%d;%dH", editor.head->linenumber, 1);

    fflush(stdout);

              }

              if(pasteUndo==1){

                        UndoHead->line_specific = editor.cursor;
                        UndoHead->pastestart = editor.cursorPos;//PastePos;
                        UndoHead->pasteend = 0;
                        UndoHead->pasteappend = 0;


                  }

    }else if(startcursor !=editor.head){

              Node *coll = endcursor->next;
               endcursor->next = NULL;
               if(coll!=NULL){
                coll->previous = NULL;
               }


             int len = strlen(endcursor->line);
              int shift = endPos - 0 + 1;
               for(int i=0;i<=len-shift;i++){
                  endcursor->line[i] = endcursor->line[i+shift];
               }

               Node *temp = startcursor->next;
               temp->previous =NULL;
               startcursor->next = NULL;
               Node *t = endcursor;

                 if(rec==1){
                UndoHead->linecut = 12;
          }

              char *dup = strdup(t->line);
              startcursor->line[0] = '\0';
              startcursor->line =  realloc(startcursor->line, strlen(dup) + 1);
             strcpy(startcursor->line, dup);
             free(dup);

              for (int j = startcursor->linenumber+1; j <= editor.tail->linenumber; j++) {
                printf("\033[%d;1H", j);
                printf("\033[K");
              }

               while(temp !=NULL){
                Node *next = temp->next;
                free(temp);
                temp = next;
               }


               if(coll==NULL){

                  editor.cursor = startcursor;
                  editor.cursorPos = 0;
                  editor.tail = startcursor;



printf("\033[%d;1H", startcursor->linenumber);

printf("\033[K");
printf("%s", startcursor->line);


// Clear everything below (since no nodes remain)
printf("\033[%d;1H", startcursor->linenumber + 1);
printf("\033[J");

// Cursor at start of new head line
printf("\033[%d;%dH", startcursor->linenumber, 1);
fflush(stdout);

              }else if(coll!=NULL){

                startcursor->next = coll;
                coll->previous = startcursor;
                 editor.cursor = startcursor;
                  editor.cursorPos = 0;
                 int i=startcursor->linenumber + 1;
                  while(coll!=NULL){
                    coll->linenumber = i;
                    i++;
                    coll = coll->next;
                  }

  // Redraw startcursor line
printf("\033[%d;1H", startcursor->linenumber);
printf("\033[K");
printf("%s", startcursor->line);

// Redraw subsequent lines
Node *q = startcursor->next;
while (q != NULL) {
    printf("\033[%d;1H", q->linenumber);
    printf("\033[K");
    printf("%s", q->line);
    q = q->next;
}

// Place cursor back at startcursor
printf("\033[%d;%dH", startcursor->linenumber, editor.cursorPos + 1);
fflush(stdout);

              }

                if(pasteUndo==1){

                        UndoHead->line_specific = editor.cursor;
                        UndoHead->pastestart = editor.cursorPos;//PastePos;
                        UndoHead->pasteend = 0;
                        UndoHead->pasteappend = 0;


                  }
                 if(rec==1){
                    UndoHead->line_specific = editor.cursor;
                    UndoHead->specific_end  = editor.cursor;
                  }

                    if(redo==1){
                    RedoHead->line_specific = editor.cursor;
                    RedoHead->specific_end = editor.cursor;
                  }

        }


      }else if(startcursor !=endcursor && (startPos>0 && startPos<=strlen(startcursor->line)-1) && ((endPos>=0 && endPos<strlen(endcursor->line)-1 && strlen(endcursor->line)!=0 )) ){

            Node *coll= endcursor->next;
            endcursor->next = NULL;
           Node *c = endcursor;
            if(coll!=NULL){
              coll->previous = NULL;
            }

            int len = strlen(endcursor->line);
               int shift = endPos - 0 + 1;
               for(int i=0;i<=len-shift;i++){

                  endcursor->line[i] = endcursor->line[i+shift];
               }
               startcursor->line[startPos]='\0';
               startcursor->line = realloc(startcursor->line , strlen(startcursor->line)+1);

               Node *temp = startcursor->next;
               temp->previous = NULL;
               startcursor->next = NULL;
               char *dup = strdup(endcursor->line);
               startcursor->line = realloc(startcursor->line ,  strlen(startcursor->line) + strlen(dup) + 1);
               strcat(startcursor->line , dup);
               free(dup);

                for (int j = startcursor->linenumber + 1; j <= editor.tail->linenumber; j++) {
                printf("\033[%d;1H", j);
                printf("\033[K");
              }


              if(rec==1){
                UndoHead->linecut = 13;
          }


              while(temp !=NULL){
                Node *next = temp->next;
                free(temp);
                temp = next;
              }

              if(coll==NULL){
                editor.tail = startcursor;
                editor.cursorPos = startPos;
                editor.cursor = startcursor;

                // Redraw startcursor line
                printf("\033[%d;1H", startcursor->linenumber);
                printf("\033[K");
                printf("%s", startcursor->line);

               // Clear everything below since tail is now here
               printf("\033[%d;1H", startcursor->linenumber + 1);
               printf("\033[J");

              // Place cursor back at startPos in startcursor
              printf("\033[%d;%dH", startcursor->linenumber, startPos + 1);
              fflush(stdout);

              }else if(coll !=NULL){

                    int i = startcursor->linenumber + 1;
                    startcursor->next = coll;
                    coll->previous = startcursor;
                    editor.cursor = startcursor;
                    editor.cursorPos = startPos;

                    Node *t = coll;

                    while(t!=NULL){

                      t->linenumber = i;
                      i+=1;
                      t=t->next;
                    }
                    i=i-1;


                   printf("\033[%d;1H", startcursor->linenumber);
                   printf("\033[K");
                   printf("%s", startcursor->line);

                   // Redraw subsequent lines
                   Node *q = startcursor->next;

                   while (q != NULL) {

                     printf("\033[%d;1H", q->linenumber);
                     printf("\033[K");
                     printf("%s", q->line);
                     q = q->next;
                  }



                  // Place cursor back at startPos in startcursor
                  printf("\033[%d;%dH", startcursor->linenumber, startPos + 1);
                  fflush(stdout);


              }


              if(pasteUndo==1){

                        UndoHead->line_specific = editor.cursor;
                        UndoHead->pastestart = editor.cursorPos;//PastePos;
                        UndoHead->pasteend = 0;
                        UndoHead->pasteappend = 0;


                  }

                   if(rec==1){
                    UndoHead->line_specific = editor.cursor;
                    UndoHead->specific_end  = editor.cursor;
                  }

                    if(redo==1){
                    RedoHead->line_specific = editor.cursor;
                    RedoHead->specific_end = editor.cursor;
                  }


      }else if(startcursor != endcursor && (startPos>0 && startPos<=strlen(startcursor->line)-1) && (endPos==0 && strlen(endcursor->line)==0)){

                   startcursor->line[startPos] = '\0';
                   int c = endcursor->linenumber;
                   Node *coll = endcursor->next;
                   if(coll!=NULL){
                    coll->previous = NULL;
                   }
                   endcursor->next = NULL;

                    for (int j = startcursor->linenumber + 1; j <= editor.tail->linenumber; j++) {   //OldEndLine
                 printf("\033[%d;1H", j);
                printf("\033[K");
               }

                   Node *temp = startcursor->next;
                   temp->previous = NULL;
                   startcursor->next = NULL;

                    if(rec==1){
                UndoHead->linecut = 14;
          }

                   while(temp !=NULL){
                    Node *next = temp->next;
                    free(temp);
                    temp = next;
                   }

                   if(coll==NULL){
                    editor.tail = startcursor;
                    editor.cursor = startcursor;
                    editor.cursorPos = startPos;

                    printf("\033[%d;1H", startcursor->linenumber);
                    printf("\033[K");
                    printf("%s", startcursor->line);

                    // Place cursor back at correct position
                    printf("\033[%d;%dH", editor.cursor->linenumber, editor.cursorPos + 1);

                    fflush(stdout);


                   }else if(coll !=NULL){

                       int  i =startcursor->linenumber+1;
                       coll->previous = startcursor;
                       startcursor->next = coll;

                       while(coll!=NULL){

                          coll->linenumber = i;
                          i++;
                          if(coll->next==NULL){
                            editor.tail = coll;
                          }
                           coll = coll->next;
                       }

                    editor.cursor = startcursor;
                    editor.cursorPos = startPos;
                       // Refresh current line (truncated + appended)
printf("\033[%d;1H", startcursor->linenumber);
printf("\033[K");
printf("%s", startcursor->line);

// Redraw all subsequent lines
Node *iter = startcursor->next;
while (iter != NULL) {
    printf("\033[%d;1H", iter->linenumber);
    printf("\033[K");
    printf("%s", iter->line);
    iter = iter->next;
}

// Clear one extra line after the new tail (safety wipe)
printf("\033[%d;1H", editor.tail->linenumber + 1);
printf("\033[K");

// If buffer shrank, clear leftover phantom lines
/*for (int j = editor.tail->linenumber + 2; j <= OldEndLine; j++) {
    printf("\033[%d;1H", j);
    printf("\033[K");
}*/

// Place cursor back at correct position
printf("\033[%d;%dH", editor.cursor->linenumber, editor.cursorPos + 1);

fflush(stdout);


                   }


                  if(rec==1){
                    UndoHead->line_specific = editor.cursor;
                    UndoHead->specific_end  = editor.cursor;
                  }

                    if(redo==1){
                    RedoHead->line_specific = editor.cursor;
                    RedoHead->specific_end = editor.cursor;
                  }

                  if(pasteUndo==1){

                        UndoHead->line_specific = editor.cursor;
                        UndoHead->pastestart = editor.cursorPos;//PastePos;
                        UndoHead->pasteend = 0;
                        UndoHead->pasteappend = 0;


                  }

      }else if(startcursor!=endcursor && (startPos==strlen(startcursor->line) && strlen(startcursor->line)!=0) && (((endPos==0  && strlen(endcursor->line)!=0)))){

                Node *coll= endcursor->next;
            endcursor->next = NULL;
           Node *c = endcursor;
            if(coll!=NULL){
              coll->previous = NULL;
            }

            int len = strlen(endcursor->line);
               int shift = endPos - 0 + 1;

               for(int i=0;i<=len-shift;i++){
                  endcursor->line[i] = endcursor->line[i+shift];
               }
               startcursor->line[startPos]='\0';
               startcursor->line = realloc(startcursor->line , strlen(startcursor->line)+1);
               Node *temp = startcursor->next;
               temp->previous = NULL;
               startcursor->next = NULL;
               char *dup = strdup(endcursor->line);
               startcursor->line = realloc(startcursor->line ,  strlen(startcursor->line) + strlen(dup) + 1);
               strcat(startcursor->line , dup);
               free(dup);

                for (int j = startcursor->linenumber + 1; j <= editor.tail->linenumber; j++) {
                printf("\033[%d;1H", j);
                printf("\033[K");
              }


              if(rec==1){
                UndoHead->linecut = 15;
          }


              while(temp !=NULL){
                Node *next = temp->next;
                free(temp);
                temp = next;
              }

              if(coll==NULL){
                editor.tail = startcursor;
                editor.cursorPos = startPos;
                editor.cursor = startcursor;

                // Redraw startcursor line
                printf("\033[%d;1H", startcursor->linenumber);
                printf("\033[K");
                printf("%s", startcursor->line);

               // Clear everything below since tail is now here
               printf("\033[%d;1H", startcursor->linenumber + 1);
               printf("\033[J");

              // Place cursor back at startPos in startcursor
              printf("\033[%d;%dH", startcursor->linenumber, startPos + 1);
              fflush(stdout);


              }else if(coll !=NULL){

                    int i = startcursor->linenumber + 1;
                    startcursor->next = coll;
                    coll->previous = startcursor;
                    editor.cursor = startcursor;
                    editor.cursorPos = startPos;

                    Node *t = coll;

                    while(t!=NULL){

                      t->linenumber = i;
                      i+=1;
                      t=t->next;
                    }
                    i=i-1;


                   printf("\033[%d;1H", startcursor->linenumber);
                   printf("\033[K");
                   printf("%s", startcursor->line);

                   // Redraw subsequent lines
                   Node *q = startcursor->next;

                   while (q != NULL) {

                     printf("\033[%d;1H", q->linenumber);
                     printf("\033[K");
                     printf("%s", q->line);
                     q = q->next;
                  }

                   if(rec==1){
                    UndoHead->line_specific = editor.cursor;
                    UndoHead->specific_end  = editor.cursor;
                  }

                    if(redo==1){
                    RedoHead->line_specific = editor.cursor;
                    RedoHead->specific_end = editor.cursor;
                  }

                  // Place cursor back at startPos in startcursor
                  printf("\033[%d;%dH", startcursor->linenumber, startPos + 1);
                  fflush(stdout);
              }

              if(pasteUndo==1){

                        UndoHead->line_specific = editor.cursor;
                        UndoHead->pastestart = editor.cursorPos;//PastePos;
                        UndoHead->pasteend = 0;
                        UndoHead->pasteappend = 0;


                  }




      }else if(startcursor!=endcursor && (startPos==strlen(startcursor->line) && strlen(startcursor->line)!=0) && (((endPos>0  &&endPos<=strlen(endcursor->line)-1 && strlen(endcursor->line)!=0)))){

              Node *coll= endcursor->next;
            endcursor->next = NULL;
           Node *c = endcursor;
            if(coll!=NULL){
              coll->previous = NULL;
            }

            int len = strlen(endcursor->line);
               int shift = endPos - 0 + 1;

               for(int i=0;i<=len-shift;i++){
                  endcursor->line[i] = endcursor->line[i+shift];
               }
               startcursor->line[startPos]='\0';
               startcursor->line = realloc(startcursor->line , strlen(startcursor->line)+1);

               Node *temp = startcursor->next;
               temp->previous = NULL;
               startcursor->next = NULL;
               char *dup = strdup(endcursor->line);
               startcursor->line = realloc(startcursor->line ,  strlen(startcursor->line) + strlen(dup) + 1);
               strcat(startcursor->line , dup);
               free(dup);

                for (int j = startcursor->linenumber + 1; j <= editor.tail->linenumber; j++) {
                printf("\033[%d;1H", j);
                printf("\033[K");
              }

              if(rec==1){
                UndoHead->linecut = 16;
          }


              while(temp !=NULL){
                Node *next = temp->next;
                free(temp);
                temp = next;
              }

              if(coll==NULL){
                editor.tail = startcursor;
                editor.cursorPos = startPos;
                editor.cursor = startcursor;

                // Redraw startcursor line
                printf("\033[%d;1H", startcursor->linenumber);
                printf("\033[K");
                printf("%s", startcursor->line);

               // Clear everything below since tail is now here
               printf("\033[%d;1H", startcursor->linenumber + 1);
               printf("\033[J");

              // Place cursor back at startPos in startcursor
              printf("\033[%d;%dH", startcursor->linenumber, startPos + 1);
              fflush(stdout);


              }else if(coll !=NULL){

                    int i = startcursor->linenumber + 1;
                    startcursor->next = coll;
                    coll->previous = startcursor;
                    editor.cursor = startcursor;
                    editor.cursorPos = startPos;

                    Node *t = coll;

                    while(t!=NULL){

                      t->linenumber = i;
                      i+=1;
                      t=t->next;
                    }
                    i=i-1;


                   printf("\033[%d;1H", startcursor->linenumber);
                   printf("\033[K");
                   printf("%s", startcursor->line);

                   // Redraw subsequent lines
                   Node *q = startcursor->next;

                   while (q != NULL) {

                     printf("\033[%d;1H", q->linenumber);
                     printf("\033[K");
                     printf("%s", q->line);
                     q = q->next;
                  }

                  if(pasteUndo==1){

                        UndoHead->line_specific = editor.cursor;
                        UndoHead->pastestart = editor.cursorPos;//PastePos;
                        UndoHead->pasteend = 0;
                        UndoHead->pasteappend = 0;


                  }

                   if(rec==1){
                    UndoHead->line_specific = editor.cursor;
                    UndoHead->specific_end  = editor.cursor;
                  }

                    if(redo==1){
                    RedoHead->line_specific = editor.cursor;
                    RedoHead->specific_end = editor.cursor;
                  }

                  // Place cursor back at startPos in startcursor
                  printf("\033[%d;%dH", startcursor->linenumber, startPos + 1);
                  fflush(stdout);


              }

      }else if(startcursor != endcursor && ( startPos==strlen(startcursor->line) && strlen(startcursor->line)>0) && (endPos==0 && strlen(endcursor->line)==0)){

                   startcursor->line[startPos] = '\0';
                   int c = endcursor->linenumber;
                   Node *coll = endcursor->next;
                   if(coll!=NULL){
                    coll->previous = NULL;
                   }
                   endcursor->next = NULL;

                    for (int j = startcursor->linenumber + 1; j <= editor.tail->linenumber; j++) {   //OldEndLine
                 printf("\033[%d;1H", j);
                printf("\033[K");
               }

                   Node *temp = startcursor->next;
                   temp->previous = NULL;
                   startcursor->next = NULL;

                    if(rec==1){

                UndoHead->linecut = 17;
          }

                   while(temp !=NULL){
                    Node *next = temp->next;
                    free(temp);
                    temp = next;
                   }

                   if(coll==NULL){
                    editor.tail = startcursor;
                    editor.cursor = startcursor;
                    editor.cursorPos = startPos;

                    printf("\033[%d;1H", startcursor->linenumber);
                    printf("\033[K");
                    printf("%s", startcursor->line);

                    // Place cursor back at correct position
                    printf("\033[%d;%dH", editor.cursor->linenumber, editor.cursorPos + 1);

                    fflush(stdout);


                   }else if(coll !=NULL){

                       int  i =startcursor->linenumber+1;
                       coll->previous = startcursor;
                       startcursor->next = coll;

                       while(coll!=NULL){

                          coll->linenumber = i;
                          i++;
                          if(coll->next==NULL){
                            editor.tail = coll;
                          }
                           coll = coll->next;
                       }

                    editor.cursor = startcursor;
                    editor.cursorPos = startPos;
                       // Refresh current line (truncated + appended)
printf("\033[%d;1H", startcursor->linenumber);
printf("\033[K");
printf("%s", startcursor->line);

// Redraw all subsequent lines
Node *iter = startcursor->next;
while (iter != NULL) {
    printf("\033[%d;1H", iter->linenumber);
    printf("\033[K");
    printf("%s", iter->line);
    iter = iter->next;
}

// Clear one extra line after the new tail (safety wipe)
printf("\033[%d;1H", editor.tail->linenumber + 1);
printf("\033[K");

// Place cursor back at correct position
printf("\033[%d;%dH", editor.cursor->linenumber, editor.cursorPos + 1);

fflush(stdout);

                   }
                   if(pasteUndo==1){
                         UndoHead->line_specific = editor.cursor;
                        UndoHead->pastestart = editor.cursorPos;//PastePos;
                        UndoHead->pasteend = 0;
                        UndoHead->pasteappend = 0;
                  }

                  if(rec==1){
                    UndoHead->line_specific = editor.cursor;
                    UndoHead->specific_end  = editor.cursor;
                  }

                    if(redo==1){
                    RedoHead->line_specific = editor.cursor;
                    RedoHead->specific_end = editor.cursor;
                  }


      }else if((startPos==strlen(startcursor->line) && strlen(startcursor->line)!=0) && (endPos>=strlen(endcursor->line)-1 && strlen(endcursor->line)!=0)){  // scaenario for cut multiple line whose cursor pos is 0 in startcursor and last character in end character

       if(rec==1){
       UndoHead->fulllinecut = 1;

       }
       if(startcursor->previous !=NULL && endcursor->next !=NULL){
            Node *t2 = endcursor->next;
            Node *temp = startcursor->next;
            temp->previous = NULL;
            endcursor->next = NULL;
            startcursor->next = t2;
            int diff = startcursor->linenumber +1;

            UndoAction *endcoll = address[endcursor->linenumber-1];

             while (temp != NULL) {
                Node *next = temp->next;
                free(temp);
                temp = next;
             }

             editor.cursor = startcursor;
             editor.cursorPos = strlen(startcursor->line);
             if(rec==1){
              UndoHead->linecut = 20;
              UndoHead->line_specific = editor.cursor;
              UndoHead->specific_end = editor.cursor;
            }

              if(redo==1){
                    RedoHead->line_specific = editor.cursor;
                    RedoHead->specific_end = editor.cursor;
                  }

          // startcursor = NULL;
          // endcursor = NULL;
          t2->previous = startcursor;
            while(t2!=NULL){
             t2->linenumber=diff;
             t2 = t2->next;
             diff+=1;
           }

          temp = t2;

          while (temp != NULL) {
             printf("\033[%d;1H", temp->linenumber);
             printf("\033[K");              // clear line
             printf("%s", temp->line);      // print buffer
             temp = temp->next;
           }

         // Finally clear everything below the new tail
          printf("\033[%d;1H", editor.tail->linenumber + 1);
          printf("\033[J");   // clears from here to end of screen
          fflush(stdout);

            if(pasteUndo==1){
                        UndoHead->line_specific = editor.cursor;
                        UndoHead->pastestart = editor.cursorPos;//PastePos;
                        UndoHead->pasteend = 0;
                        UndoHead->pasteappend = 0;
                  }

       }else if(startcursor->previous !=NULL && endcursor->next==NULL){

                  editor.tail = startcursor;
                  editor.cursor = editor.tail;
                  editor.cursorPos = strlen(startcursor->line);
                  Node *temp = startcursor->next;
                  startcursor->next = NULL;
                 temp->previous = NULL; //

                    Node * tp = endcursor;//temp;

            if(rec==1){
                UndoHead->linecut = 21;
          }

                  while(temp !=NULL){
                    Node *next = temp->next;
                    free(temp);
                    temp = next;
                  }

                  if(rec==1){

                    UndoHead->line_specific = editor.cursor;
                    UndoHead->specific_end  = editor.cursor;
                  }

                    if(redo==1){

                    RedoHead->line_specific = editor.cursor;
                    RedoHead->specific_end = editor.cursor;
                  }

                   if(pasteUndo==1){

                        UndoHead->line_specific = editor.cursor;
                        UndoHead->pastestart = editor.cursorPos;//PastePos;
                        UndoHead->pasteend = 0;
                        UndoHead->pasteappend = 0;
                  }

                    // Clear current line (since you emptied it)
                   printf("\033[%d;1H", editor.tail->linenumber);
                   printf("\033[K");

                  // Clear everything below tail
                   printf("\033[%d;1H", editor.tail->linenumber + 1);
                   printf("\033[J");
                   fflush(stdout);

       }else if(startcursor==editor.head && endcursor->next!=NULL){

                  Node *t = endcursor->next;
                  endcursor->next = NULL;
                  editor.head->previous = NULL;
                  Node *temp = startcursor->next;
                  startcursor->next = NULL;
                  temp->previous = NULL;

                  startcursor->next = t;
                  t->previous = startcursor;

                   if(rec==1){

                UndoHead->linecut = 19;
          }

                  while(temp!=NULL){
                     Node *next = temp->next;
                    free(temp);
                    temp = next;
                  }
                  editor.cursor = editor.head;
                  editor.cursorPos = strlen(editor.head->line);
                  temp = editor.head;
                  int i = 1;
                  while(temp!=NULL){
                    temp->linenumber = i;
                    i+=1;
                    temp = temp->next;
                  }

                   if(rec==1){
                    UndoHead->line_specific = editor.cursor;
                    UndoHead->specific_end  = editor.cursor;
                  }

                    if(redo==1){
                    RedoHead->line_specific = editor.cursor;
                    RedoHead->specific_end = editor.cursor;
                  }

                  temp = editor.head;
                  while (temp != NULL) {
                    printf("\033[%d;1H", temp->linenumber);
                    printf("\033[K");          // clear line
                    printf("%s", temp->line);  // print buffer content
                    temp = temp->next;
                 }

              // clear everything below new tail
                  printf("\033[%d;1H", editor.tail->linenumber + 1);
                  printf("\033[J");
                  fflush(stdout);

                   if(pasteUndo==1){
                        UndoHead->line_specific = editor.cursor;
                        UndoHead->pastestart = editor.cursorPos;//PastePos;
                        UndoHead->pasteend = 0;
                        UndoHead->pasteappend = 0;
                  }

                }else if(startcursor->previous==NULL && endcursor->next==NULL){
                 // printf("\n\n\n\n\n\n\n\n\n\n4....\n");
                  Node *temp = editor.head->next;
                  editor.head->next = NULL;
                  temp->previous = NULL;//

                    if(rec==1){
                UndoHead->linecut = 18;
          }
                  while(temp!=NULL){
                     Node *next = temp->next;
                    free(temp);
                    temp = next;
                  }


                    editor.tail = editor.head;
                    editor.cursor = editor.head;
                    editor.cursorPos = strlen(editor.head->line);

                     if(pasteUndo==1){
                        UndoHead->line_specific = editor.cursor;
                        UndoHead->pastestart = editor.cursorPos;//PastePos;
                        UndoHead->pasteend = 0;
                        UndoHead->pasteappend = 0;
                  }

                     if(rec==1){
                    UndoHead->line_specific = editor.cursor;
                    UndoHead->specific_end  = editor.cursor;
                  }

                    if(redo==1){
                    RedoHead->line_specific = editor.cursor;
                    RedoHead->specific_end = editor.cursor;
                  }
                    // Clear current line (head)
                    printf("\033[%d;1H", editor.head->linenumber);
                    printf("\033[K");   // clear line
                   // optional: reprint head->line if you want to show empty string
                   printf("%s", editor.head->line);
                   // Clear everything below head
                   printf("\033[%d;1H", editor.head->linenumber + 1);
                   printf("\033[J");   // clear rest of screen
                   fflush(stdout);

       }

    }

    }
