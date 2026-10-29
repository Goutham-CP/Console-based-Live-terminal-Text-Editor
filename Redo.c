#include"Header.h"



void Redo(){

    if(RedoHead->operation=='i'){


       if(RedoHead->line1 > editor.tail->linenumber){
        return;
       }

         char ch = RedoHead->backspchar;
         editor.cursor = RedoHead->line_specific;//
          editor.cursorPos = RedoHead->Oldpos-1;
          InsertCharAtPosition(editor.cursorPos, ch);
          Update_Table_Redo();
          delete_first_Redo();

    }else if(RedoHead->operation=='b'){

       if(RedoHead->backspchar=='\0'){
           if((RedoHead->line1+1)>editor.tail->linenumber){
              return;
           }
        }else if(RedoHead->backspchar !='\0'){
            if(RedoHead->line1 > editor.tail->linenumber){
               return;
       }
        }
       redo = 1;
        editor.cursor = RedoHead->line_specific;
        editor.cursorPos = RedoHead->Oldpos;
        BackSpace();
        RedoHead->line_specific = editor.cursor;
        RedoHead->Oldpos = editor.cursorPos;
       Update_Table_Redo();
        delete_first_Redo();
        redo = 0;

    }else if(RedoHead->operation=='e'){


       if((RedoHead->line1)>editor.tail->linenumber){
              return;
           }

       editor.cursor = RedoHead->line_specific;

        editor.cursorPos = RedoHead->Oldpos;
        if(RedoHead->line1==1){
            editor.cursor = editor.head;
        }

        EnterKey();

              tot = 0;
              int local = 0;

        RedoHead->line_specific = editor.cursor;
        RedoHead->Oldpos = editor.cursorPos;

        Update_Table_Redo();
         delete_first_Redo();


  }else if(RedoHead->operation=='c'){

           if(((RedoHead->line1)>editor.tail->linenumber) || ((RedoHead->line2)>editor.tail->linenumber)){
              return;
           }
         redo = 1;
         startcursor = RedoHead->line_specific;
         endcursor = RedoHead->specific_end;
         startPos = RedoHead->Oldpos;
         endPos = RedoHead->cutend;
         if(startcursor==endcursor){
            editor.cursor = startcursor;
         }
        editor.cursorPos = startPos;//
        cut();
        Update_Table_Redo();
        redo = 0;
        delete_first_Redo();
    }else if(RedoHead->operation=='p'){

        if((RedoHead->line1)>editor.tail->linenumber){
              return;
           }

          pasteRedoFlag = 1;
          editor.cursor = RedoHead->line_specific;
          PastePos = RedoHead->pastestart;
          editor.cursorPos = PastePos;
          paste(RedoHead->UndoCopyHead, RedoHead->UndoCopyTail);
          pasteRedoFlag = 0;
          Update_Table_Redo();
          delete_first_Redo();
    }


}





void Redo_Paste(int linenumber,Node *tem){


 ChainNode *t;
  if(linenumber<=hash_st){

   ChainNode *temp = UndoRedo_Table[linenumber-1]->next;


             int tt = 0;

           while(temp!=NULL){

                if(temp->addr!=NULL && temp->addr->Undo_Redo==1 && temp->addr!=RedoHead){
                  tt+=1;
                  temp->addr->line_specific = tem;
                }

           temp = temp->next;

           }
        }

         if(back_st>0){
          if((linenumber-1>=0) && linenumber-1<=(back_st-1)){
            t = UndoRedo_Backspace[linenumber - 1]->next;

           int local = 0;
            while(t!=NULL){

               if(t->addr->Undo_Redo==1 && t->addr->backspchar!='\0' && t->addr!=RedoHead){
                   local++;
                   t->addr->line_specific = tem;
               }
              t = t->next;
            }
        }

            if((linenumber-2>=0) && linenumber-2<=(back_st-1))   {
            t = UndoRedo_Backspace[linenumber - 2]->next;

            while(t!=NULL){

               if(t->addr->Undo_Redo==1 && t->addr->backspchar=='\0' && t->addr!=RedoHead){
                   t->addr->line_specific = tem;
               }
              t = t->next;

            }
        }
        }

            if(linenumber<=enter_st){

                t = enterAddress[linenumber - 1]->next;

            while(t!=NULL){

               if(t->addr->Undo_Redo==1 && t->addr!=RedoHead){    //&& t->addr->backspchar=='\0'
                   t->addr->line_specific = tem;
               }
              t = t->next;

            }

          }

          if(cut_st>0){

              for(int i=0;i<(cut_st/2);i++){

                 if(cutAddress[i]->line1==linenumber && cutAddress[i]->Undo_Redo==1 && cutAddress[i]!=RedoHead){
                     cutAddress[i]->line_specific = tem;
                 }

                 if(cutAddress[i]->line2==linenumber && cutAddress[i]->Undo_Redo==1 && cutAddress[i]!=RedoHead){
                     cutAddress[i]->specific_end = tem;
                 }

                  if(cutAddress[cut_st-1-i]->line1==linenumber  && cutAddress[cut_st-1-i]->Undo_Redo==1 && cutAddress[cut_st-1-i]!=RedoHead){
                     cutAddress[cut_st-1-i]->line_specific = tem;
                 }

                 if(cutAddress[cut_st-1-i]->line2==linenumber && cutAddress[cut_st-1-i]->Undo_Redo==1 && cutAddress[cut_st-1-i]!=RedoHead){
                     cutAddress[cut_st-1-i]->specific_end = tem;
                 }

              }

              if(cut_st % 2 == 1) {
                 int mid = cut_st/2;

            if(cutAddress[mid]->line1 == linenumber && cutAddress[mid]->Undo_Redo == 1 && cutAddress[mid]!=RedoHead) {
                 cutAddress[mid]->line_specific = tem;
           }

          if(cutAddress[mid]->line2 == linenumber  && cutAddress[mid]->Undo_Redo == 1 && cutAddress[mid]!=RedoHead) {
        cutAddress[mid]->specific_end = tem;
        }
    }
            }

              if(paste_st>0){
               for(int i=0;i<(paste_st/2);i++){

                 if(pasteAddress[i]->line1==linenumber && pasteAddress[i]->Undo_Redo==1 && pasteAddress[i]!=RedoHead){
                     pasteAddress[i]->line_specific = tem;
                 }

                 if(pasteAddress[paste_st-1-i]->line1==linenumber && pasteAddress[paste_st-1-i]->Undo_Redo==1 && pasteAddress[paste_st-1-i]!=RedoHead){
                     pasteAddress[paste_st-1-i]->line_specific = tem;
                 }

              }

                  if(paste_st % 2 == 1) {
                 int mid = paste_st/2;

            if(pasteAddress[mid]->line1 == linenumber && pasteAddress[mid]->Undo_Redo == 1 && pasteAddress[mid]!=RedoHead) {
                 pasteAddress[mid]->line_specific = tem;
           }

    }
            }

}

int Update_Table_Redo(){


  if(editor.head==NULL && editor.tail==NULL){
      return FAILURE;
    }

    Node *p1 = editor.head;
    Node *p2 = editor.tail;
    int local = 0;

    while(p1 != p2){

       if(p1->next == p2 && p2->previous == p1){

      Redo_Paste(p1->linenumber,p1);
      Redo_Paste(p2->linenumber,p2);
        p1 = NULL;
        p2 = NULL;

      break;
      }

      Redo_Paste(p1->linenumber,p1);
      Redo_Paste(p2->linenumber,p2);
       p1 = p1->next;
       p2 = p2->previous;
    }

  if((p1 == p2) && (p1!=NULL && p2!=NULL)){
    Redo_Paste(p1->linenumber,p1);
  }

  return SUCCESS;

}