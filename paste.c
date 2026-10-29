#include"Header.h"



void paste(Node *copyHead,Node *copyTail){

     if(copyHead==NULL && copyTail==NULL){
        return;
     }

      if(copyHead !=copyTail ){

        if( rec==1 && (UndoHead->linecut==9 || UndoHead->linecut==10 || UndoHead->linecut==14 || UndoHead->linecut==17)){

            copyHead = copyHead->next;
        }

        if(rec==1 && (UndoHead->linecut==11 || UndoHead->linecut==12)){
            copyTail = copyTail->previous;

        }

        if( rec==1 && UndoHead->linecut==13){
            copyHead = copyHead->next;
            copyTail = copyTail->previous;
        }

         if( rec==1 && UndoHead->linecut==15){
            copyHead = copyHead->next;
            copyTail = copyTail->previous;
        }

         if(rec==1 && UndoHead->linecut==16){
            copyHead = copyHead->next;
            copyTail = copyTail->previous;
        }

         if(PastePos > 0 && PastePos<=strlen(editor.cursor->line)-1){

              if(pasteFlag==1){
                UndoHead->line_specific = editor.cursor;
                UndoHead->pastestart = editor.cursorPos;

              }

              if(pasteRedoFlag==1){
                RedoHead->line_specific = editor.cursor;
                RedoHead->pastestart = editor.cursorPos;
              }
               Node *nxt = editor.cursor->next;

               if(nxt!=NULL){
               nxt->previous = NULL;
               }
               editor.cursor->next = NULL;

               Node *temp = copyHead;


               char *dup  = strdup(editor.cursor->line);
               char *tempdup = strdup(temp->line);

            // clear display cursor to tail ligic
             for (int j = editor.cursor->linenumber + 1; j <= editor.tail->linenumber; j++) {   //OldEndLine
                 printf("\033[%d;1H", j);
                printf("\033[K");
               }

              int shift = PastePos - 0;
              int len = strlen(dup);

              for(int i=0;i<=(len - shift);i++){
                  dup[i] = dup[i+shift];
              }

              editor.cursor->line[PastePos] = '\0';
              editor.cursor->line = realloc(editor.cursor->line , strlen(editor.cursor->line) + strlen(tempdup)+1);
              strcat(editor.cursor->line , tempdup);


              Node *coll = temp->next;
             Node *prev = editor.cursor;
             int i = editor.cursor->linenumber + 1;
              while(coll!=NULL){

                 Node *new = malloc(sizeof(Node));
                 new->linenumber = i;
                 new->line = malloc(strlen(coll->line)+1);
                 strcpy(new->line , coll->line);
                 prev->next = new;
                 new->previous = prev;

                 if(prev==editor.cursor){
                  editor.cursor->next = new;
                 }

                 new->next = NULL;
                   if(coll==copyTail){
                     new->line = realloc(new->line , strlen(new->line) + strlen(dup) + 1);
                     strcat(new->line, dup);
                     new->next = nxt;
                     prev = new;

                     if(nxt==NULL){
                        editor.tail = new;
                     }
                     break;
                  }
                 prev = new;
                 coll = coll->next;
                 i++;
              }

               if(rec==1){
                UndoAction *start = address[endcursor->linenumber]->next->next;
                Node *it;
              }


               if(nxt!=NULL){
                  nxt->previous = prev;
                  int i = prev->linenumber + 1;
                  temp = nxt;

                  while(temp !=NULL){
                     nxt->linenumber = i;
                     i++;
                     if(nxt->next==NULL){
                        editor.tail = nxt;
                        break;
                     }
                     nxt = nxt->next;
                  }

               }

              free(dup);
              free(tempdup);


// Refresh current line (truncated + appended)
printf("\033[%d;1H", editor.cursor->linenumber);
printf("\033[K");
printf("%s", editor.cursor->line);

// Redraw all subsequent lines
Node *iter = editor.cursor->next;
while (iter != NULL) {
    printf("\033[%d;1H", iter->linenumber);
    printf("\033[K");
    printf("%s", iter->line);
    iter = iter->next;
}

// Clear one extra line after the new tail (safety wipe)
printf("\033[%d;1H", editor.tail->linenumber + 1);
printf("\033[K");

  editor.cursor = prev;


  int ln = strlen(copyTail->line);
  editor.cursorPos = ln - 1;

    if(pasteFlag==1){
               if(ln==0){
                    editor.cursorPos = ln;
                   UndoHead->specific_end = editor.cursor;//
                    UndoHead->pasteend = editor.cursorPos;//strlen(editor.cursor->line);
                }else{

                UndoHead->specific_end = editor.cursor;
                UndoHead->pasteend = editor.cursorPos;
                }

                UndoHead->line2 = editor.cursor->linenumber;

              }

    if(pasteRedoFlag==1){

                if(ln==0){
                    editor.cursorPos = ln;
                 RedoHead->specific_end = editor.cursor;//
                    UndoHead->pasteend = editor.cursorPos;//strlen(editor.cursor->line);
                }else{
                RedoHead->specific_end = editor.cursor;
                RedoHead->pasteend = editor.cursorPos;
                }
              }

// If buffer shrank, clear leftover phantom lines
/*for (int j = editor.tail->linenumber + 2; j <= OldEndLine; j++) {
    printf("\033[%d;1H", j);
    printf("\033[K");
}*/

// Place cursor back at correct position
printf("\033[%d;%dH", editor.cursor->linenumber, PastePos + 1);

fflush(stdout);

         }else if(PastePos==0 && strlen(editor.cursor->line)==0){
              Node *temp = editor.cursor->next ;
              editor.cursor->next = NULL;
              if(temp!=NULL){
              temp->previous  = NULL;
              }

               for (int j = editor.cursor->linenumber + 1; j <= editor.tail->linenumber; j++) {   //OldEndLine
                 printf("\033[%d;1H", j);
                printf("\033[K");
               }

              Node *prev = editor.cursor;
              Node *coll = copyHead;
              char * dup_begin = strdup(coll->line);
              editor.cursor->line = realloc(editor.cursor->line , strlen(dup_begin)+1);
              strcpy(editor.cursor->line , dup_begin);
              if(pasteFlag==1){

               UndoHead->linecut = 25;
                UndoHead->line_specific = editor.cursor;
                UndoHead->pastestart = editor.cursorPos;

              }

              if(pasteRedoFlag==1){
                RedoHead->line_specific = editor.cursor;
                RedoHead->pastestart = editor.cursorPos;
              }
            // Node *prev = editor.cursor;
             int i = prev->linenumber+1;
              coll = coll->next;
              UndoAction *start;

              Node *it;

              while(coll !=NULL){

                  Node *new = malloc(sizeof(Node));
                 new->linenumber = i;
                 new->line = strdup(coll->line);
                 prev->next = new;
                 new->previous = prev;
                 prev = new;
                  i++;

                 if(coll->next==NULL){
                  break;
                 }
                 coll = coll->next;

               }

               if((rec==1 && UndoHead->linecut==11) || (rec==1 && UndoHead->linecut==12) ){
                prev = prev->previous;
               }

               if(rec==1 && UndoHead->linecut==13){
                prev = prev->previous;
               }

               if(rec==1 && UndoHead->linecut==15){
                prev = prev->previous;
               }

                if(rec==1 && UndoHead->linecut==16){
                prev = prev->previous;
               }


                 if(rec==1){

                    if(UndoHead->linecut==5){
                    UndoHead->line_specific = editor.cursor;
                    UndoHead->specific_end = prev;
                }else if(UndoHead->linecut==6){
                         UndoHead->line_specific = editor.cursor;
                         UndoHead->specific_end = prev;

                }else if(UndoHead->linecut==7){
                       UndoHead->line_specific = editor.cursor;
                       UndoHead->specific_end = prev;

                }else if(UndoHead->linecut==8){
                        UndoHead->line_specific = editor.cursor;
                        UndoHead->specific_end = prev;
                }

                }

                    i = prev->linenumber+1;
                  if(temp!= NULL){

                          prev->next = temp;
                          temp->previous = prev;
                          while(temp!=NULL){
                              temp->linenumber = i;
                              i++;
                              if(temp->next == NULL){
                                 editor.tail = temp;
                              }
                              temp = temp->next;
                          }
                  }else if(temp==NULL){
                     prev->next = NULL;
                     editor.tail = prev;
                  }
            free(dup_begin);

            if(rec==1){

             if(UndoHead->linecut==9){

                    UndoHead->specific_end = prev;

                }else if(UndoHead->linecut==10){

                      UndoHead->specific_end = prev;

                }else if(UndoHead->linecut==11){

                             UndoHead->line_specific = editor.cursor;
                             UndoHead->specific_end = prev->next;

                }else if(UndoHead->linecut==12){

                             UndoHead->line_specific = editor.cursor;
                             UndoHead->specific_end = prev->next;

                }else if(UndoHead->linecut==13){

                    UndoHead->specific_end = prev->next;

                }else if(UndoHead->linecut==14){

                    UndoHead->specific_end = prev;

                }else if(UndoHead->linecut==15){

                    UndoHead->specific_end = prev->next;

                }else if(UndoHead->linecut==16){

                    UndoHead->specific_end = prev->next;

                }else if(UndoHead->linecut==17){

                    UndoHead->specific_end = prev;

                }

                }

            // Refresh current line (truncated + appended)
printf("\033[%d;1H", editor.cursor->linenumber);
printf("\033[K");
printf("%s", editor.cursor->line);

// Redraw all subsequent lines
Node *iter = editor.cursor->next;
while (iter != NULL) {
    printf("\033[%d;1H", iter->linenumber);
    printf("\033[K");
    printf("%s", iter->line);
    iter = iter->next;
}

// Clear one extra line after the new tail (safety wipe)
printf("\033[%d;1H", editor.tail->linenumber + 1);
printf("\033[K");

editor.cursor = prev;
editor.cursorPos = strlen(prev->line) - 1;

if(editor.cursorPos<0){
    editor.cursorPos = 0;
}

  if(pasteFlag==1){

                UndoHead->specific_end = editor.cursor;
                UndoHead->pasteend = editor.cursorPos;
                UndoHead->line2 = editor.cursor->linenumber;
              }

              if(pasteRedoFlag==1){
                RedoHead->specific_end = editor.cursor;
                RedoHead->pasteend = editor.cursorPos;
              }

// Place cursor back at correct position
printf("\033[%d;%dH", editor.cursor->linenumber, PastePos + 1);

fflush(stdout);



         }else if(PastePos== 0  && strlen(editor.cursor->line)!=0){

             if(pasteFlag==1){

                UndoHead->line_specific = editor.cursor;
                UndoHead->pastestart = editor.cursorPos;
              }

              if(pasteRedoFlag==1){
                RedoHead->line_specific = editor.cursor;
                RedoHead->pastestart = editor.cursorPos;
              }

             char *dup = strdup(editor.cursor->line);
              Node *temp = editor.cursor->next ;
              editor.cursor->next = NULL;
              if(temp!=NULL){
              temp->previous  = NULL;
              }

               for (int j = editor.cursor->linenumber + 1; j <= editor.tail->linenumber; j++) {   //OldEndLine
                 printf("\033[%d;1H", j);
                printf("\033[K");
               }

              Node *prev = editor.cursor;
              Node *coll = copyHead;
              char * dup_begin = strdup(coll->line);
              editor.cursor->line = realloc(editor.cursor->line , strlen(dup_begin)+1);
              strcpy(editor.cursor->line , dup_begin);

             int i = prev->linenumber+1;
              coll = coll->next;
              Node * collr;

              while(coll !=NULL){

                  Node *new = malloc(sizeof(Node));
                 new->linenumber = i;
                 new->line = strdup(coll->line);
                 prev->next = new;
                 new->previous = prev;
                 prev = new;

                  i++;
                 if(coll->next==NULL){
                 new->line = realloc(new->line , strlen(new->line) + strlen(dup) + 1);
                 strcat(new->line , dup);
                 collr = new;
                  break;
                 }
                 coll = coll->next;
               }
                    i = prev->linenumber+1;
                  if(temp!= NULL){

                          prev->next = temp;
                          temp->previous = prev;
                          while(temp!=NULL){
                              temp->linenumber = i;
                              i++;
                              if(temp->next == NULL){
                                 editor.tail = temp;
                              }
                              temp = temp->next;
                          }
                  }else if(temp==NULL){
                     editor.tail = prev;
                     prev->next = NULL;
                  }
            free(dup_begin);

            // Refresh current line (truncated + appended)
printf("\033[%d;1H", editor.cursor->linenumber);
printf("\033[K");
printf("%s", editor.cursor->line);

// Redraw all subsequent lines
Node *iter = editor.cursor->next;
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


editor.cursor = collr;
editor.cursorPos = strlen(copyTail->line)-1;
if(editor.cursorPos<0){
    editor.cursorPos = 0;
}

 if(pasteFlag==1){

                UndoHead->specific_end = editor.cursor;
                UndoHead->pasteend = editor.cursorPos;
                 UndoHead->line2 = editor.cursor->linenumber;
              }

    if(pasteRedoFlag==1){

                RedoHead->specific_end = editor.cursor;
                RedoHead->pasteend = editor.cursorPos;

              }

// Place cursor back at correct position
printf("\033[%d;%dH", editor.cursor->linenumber, PastePos + 1);

fflush(stdout);

   }else if(PastePos!=0 && PastePos==strlen(editor.cursor->line)){


    if(rec==1){

      if(UndoHead->linecut==18){
          UndoHead->line_specific = editor.cursor;
      }else if(UndoHead->linecut==19){
         UndoHead->line_specific = editor.cursor;
      }else if(UndoHead->linecut==20){
         UndoHead->line_specific = editor.cursor;
      }else if(UndoHead->linecut==21){
         UndoHead->line_specific = editor.cursor;
      }

    }

             if(pasteFlag==1){
                UndoHead->line_specific = editor.cursor;
                UndoHead->pastestart = editor.cursorPos;

              }

              if(pasteRedoFlag==1){
                RedoHead->line_specific = editor.cursor;
                RedoHead->pastestart = editor.cursorPos;
              }
              UndoHead->pasteappend = 1;

              Node *temp = editor.cursor->next ;
              editor.cursor->next = NULL;
              if(temp!=NULL){
              temp->previous  = NULL;
              }

               for (int j = editor.cursor->linenumber + 1; j <= editor.tail->linenumber; j++) {   //OldEndLine
                 printf("\033[%d;1H", j);
                printf("\033[K");
               }

              Node *prev = editor.cursor;
              Node *coll = copyHead;
              char * dup_begin = strdup(coll->line);
              editor.cursor->line = realloc(editor.cursor->line , strlen(editor.cursor->line) + strlen(dup_begin)+1);
              strcat(editor.cursor->line , dup_begin);

             int i = prev->linenumber+1;
              coll = coll->next;

              while(coll !=NULL){

                  Node *new = malloc(sizeof(Node));
                 new->linenumber = i;
                 new->line = strdup(coll->line);
                 prev->next = new;
                 new->previous = prev;
                 prev = new;

                  i++;
                 if(coll->next==NULL){
                  break;
                 }
                 coll = coll->next;

               }
                    i = prev->linenumber+1;
                  if(temp!= NULL){

                          prev->next = temp;
                          temp->previous = prev;
                          while(temp!=NULL){
                              temp->linenumber = i;
                              i++;
                              if(temp->next == NULL){
                                 editor.tail = temp;
                              }
                              temp = temp->next;
                          }
                  }else if(temp==NULL){
                     editor.tail = prev;
                     prev->next = NULL;
                  }
            free(dup_begin);

         if(rec==1){
            if(UndoHead->linecut==18 || UndoHead->linecut==21){

                    UndoHead->specific_end = prev;

            }else if(UndoHead->linecut==19 || UndoHead->linecut==20){

                    UndoHead->specific_end = prev;
            }
        }


            // Refresh current line (truncated + appended)
printf("\033[%d;1H", editor.cursor->linenumber);
printf("\033[K");
printf("%s", editor.cursor->line);

// Redraw all subsequent lines
Node *iter = editor.cursor->next;
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
 
editor.cursor = prev;
editor.cursorPos = strlen(copyTail->line)-1;

if(editor.cursorPos<0){
    editor.cursorPos = 0;
}

// Place cursor back at correct position
printf("\033[%d;%dH", editor.cursor->linenumber, PastePos + 1);

fflush(stdout);

if(pasteFlag==1){
                UndoHead->specific_end = editor.cursor;
                UndoHead->pasteend = editor.cursorPos;
                UndoHead->line2 = editor.cursor->linenumber;
              }

              if(pasteRedoFlag==1){
                RedoHead->specific_end = editor.cursor;
                RedoHead->pasteend = editor.cursorPos;
              }

   }


      }else if(copyHead==copyTail){

           if(PastePos==0 && strlen(editor.cursor->line)!=0){

            if(pasteFlag==1){
                UndoHead->line_specific = editor.cursor;
                UndoHead->pastestart = editor.cursorPos;
              }

              if(pasteRedoFlag==1){
                RedoHead->line_specific = editor.cursor;
                RedoHead->pastestart = editor.cursorPos;
              }


            for (int j = editor.cursor->linenumber + 1; j <= editor.tail->linenumber; j++) {   //OldEndLine
                 printf("\033[%d;1H", j);
                printf("\033[K");
               }

              int shift = strlen(copyHead->line);
               char *dup = strdup(copyHead->line);
               int l = strlen(dup);
               editor.cursor->line = realloc(editor.cursor->line , strlen(copyHead->line) + strlen(editor.cursor->line + 1));
                dup =  realloc(dup , strlen(dup) + strlen(editor.cursor->line + 1));
                strcat(dup , editor.cursor->line);
                strcpy(editor.cursor->line , dup);
                free(dup);

                 if(rec==1){
                    UndoHead->line_specific = editor.cursor;
                    UndoHead->specific_end = editor.cursor;
                 }

                           // Refresh current line (truncated + appended)
printf("\033[%d;1H", editor.cursor->linenumber);
printf("\033[K");
printf("%s", editor.cursor->line);

// Redraw all subsequent lines
Node *iter = editor.cursor->next;
while (iter != NULL) {
    printf("\033[%d;1H", iter->linenumber);
    printf("\033[K");
    printf("%s", iter->line);
    iter = iter->next;
}

// Clear one extra line after the new tail (safety wipe)
printf("\033[%d;1H", editor.tail->linenumber + 1);
printf("\033[K");
editor.cursorPos =l-1;

// If buffer shrank, clear leftover phantom lines
/*for (int j = editor.tail->linenumber + 2; j <= OldEndLine; j++) {
    printf("\033[%d;1H", j);
    printf("\033[K");
}*/

// Place cursor back at correct position
printf("\033[%d;%dH", editor.cursor->linenumber, PastePos + 1);

fflush(stdout);

  if(pasteFlag==1){

                UndoHead->specific_end = editor.cursor;
                UndoHead->pasteend = editor.cursorPos;
                UndoHead->line2 = editor.cursor->linenumber;

              }

              if(pasteRedoFlag==1){
                RedoHead->specific_end = editor.cursor;
                RedoHead->pasteend = editor.cursorPos;
              }

           }else if(PastePos==0 && strlen(editor.cursor->line)==0){

          if(pasteFlag==1){

                 if(editor.cursor==editor.head && editor.head!=editor.tail){
                UndoHead->linecut = 30;
               }else if(editor.cursor==editor.tail && editor.head!=editor.tail){
                UndoHead->linecut = 31;
               }else if(editor.cursor!=editor.tail && editor.cursor!=editor.head){
                UndoHead->linecut = 32;
               }else if(editor.cursor==editor.head && editor.tail==editor.head){
                UndoHead->linecut = 33;
               }
                UndoHead->line_specific = editor.cursor;
                UndoHead->pastestart = editor.cursorPos;
              }

              if(pasteRedoFlag==1){
                RedoHead->line_specific = editor.cursor;
                RedoHead->pastestart = editor.cursorPos;
              }

            for (int j = editor.cursor->linenumber + 1; j <= editor.tail->linenumber; j++) {   //OldEndLine
                 printf("\033[%d;1H", j);
                printf("\033[K");
               }

                 editor.cursor->line = realloc(editor.cursor->line , strlen(copyHead->line)+1);

                 char *dup = strdup(copyHead->line);
                 int l = strlen(dup);
                 strcpy(editor.cursor->line , dup);

                 if(rec==1){
                    UndoHead->line_specific = editor.cursor;
                    UndoHead->specific_end = editor.cursor;
                 }
                free(dup);

                           // Refresh current line (truncated + appended)
printf("\033[%d;1H", editor.cursor->linenumber);
printf("\033[K");
printf("%s", editor.cursor->line);

// Redraw all subsequent lines
Node *iter = editor.cursor->next;
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
 editor.cursorPos =l-1;

// Place cursor back at correct position
printf("\033[%d;%dH", editor.cursor->linenumber, PastePos + 1);

fflush(stdout);
if(pasteFlag==1){
                UndoHead->specific_end = editor.cursor;
                UndoHead->pasteend = editor.cursorPos;
                 UndoHead->line2 = editor.cursor->linenumber;
              }

              if(pasteRedoFlag==1){
                RedoHead->specific_end = editor.cursor;
                RedoHead->pasteend = editor.cursorPos;

              }

           }else if(PastePos>0 && PastePos<=strlen(editor.cursor->line)-1){

             if(pasteFlag==1){
                UndoHead->line_specific = editor.cursor;
                UndoHead->pastestart = editor.cursorPos;
              }

              if(pasteRedoFlag==1){
                RedoHead->line_specific = editor.cursor;
                RedoHead->pastestart = editor.cursorPos;
              }

              for (int j = editor.cursor->linenumber + 1; j <= editor.tail->linenumber; j++) {   //OldEndLine
                 printf("\033[%d;1H", j);
                printf("\033[K");
               }

            int shift = strlen(copyHead->line);
            int l = strlen(editor.cursor->line);
            editor.cursor->line = realloc(editor.cursor->line , strlen(editor.cursor->line) + strlen(copyHead->line) + 1 );

            for(int i=l;i>=PastePos;i--){
               editor.cursor->line[i+shift] = editor.cursor->line[i];

            }

            for(int i = PastePos ; i<=PastePos + shift - 1;i++){
                   editor.cursor->line[i] = copyHead->line[i-PastePos];

            }



                                       // Refresh current line (truncated + appended)
printf("\033[%d;1H", editor.cursor->linenumber);
printf("\033[K");
printf("%s", editor.cursor->line);

// Redraw all subsequent lines
Node *iter = editor.cursor->next;
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
editor.cursorPos = PastePos + strlen(copyHead->line) - 1;

// Place cursor back at correct position
printf("\033[%d;%dH", editor.cursor->linenumber, PastePos + 1);

fflush(stdout);

            if(rec==1){
                    UndoHead->line_specific = editor.cursor;
                    UndoHead->specific_end = editor.cursor;
                 }

 if(pasteFlag==1){
                UndoHead->specific_end = editor.cursor;
                UndoHead->pasteend = editor.cursorPos;
                UndoHead->line2 = editor.cursor->linenumber;
              }

              if(pasteRedoFlag==1){
                RedoHead->specific_end = editor.cursor;
                RedoHead->pasteend = editor.cursorPos;
              }

           }else if(PastePos==strlen(editor.cursor->line) && strlen(editor.cursor->line)>0){

                      if(pasteFlag==1){
                UndoHead->line_specific = editor.cursor;
                UndoHead->pastestart = editor.cursorPos;
              }

              if(pasteRedoFlag==1){
                RedoHead->line_specific = editor.cursor;
                RedoHead->pasteend = editor.cursorPos;
              }

                     for (int j = editor.cursor->linenumber + 1; j <= editor.tail->linenumber; j++) {   //OldEndLine
                 printf("\033[%d;1H", j);
                printf("\033[K");
               }

                    editor.cursor->line = realloc(editor.cursor->line , strlen(editor.cursor->line) + strlen(copyHead->line) + 1);
                    strcat(editor.cursor->line , copyHead->line);

          // Refresh current line (truncated + appended)
printf("\033[%d;1H", editor.cursor->linenumber);
printf("\033[K");
printf("%s", editor.cursor->line);

// Redraw all subsequent lines
Node *iter = editor.cursor->next;
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
editor.cursorPos = strlen(editor.cursor->line)-1;

// Place cursor back at correct position
printf("\033[%d;%dH", editor.cursor->linenumber, PastePos + 1);

fflush(stdout);

                 if(rec==1){
                    UndoHead->line_specific = editor.cursor;
                    UndoHead->specific_end = editor.cursor;
                 }

     if(pasteFlag==1){
                UndoHead->specific_end = editor.cursor;
                UndoHead->pasteend = editor.cursorPos;
                UndoHead->line2 = editor.cursor->linenumber;
              }

              if(pasteRedoFlag==1){
                RedoHead->specific_end = editor.cursor;
                RedoHead->pasteend = editor.cursorPos;
              }

           }


      }

}
