
#include"Header.h"


int insert_last( char *data){

  if(editor.head==NULL){

        Node *new = malloc(sizeof(Node));
        new->previous = NULL;

        if(data==NULL){
            size_t len = 0;
            new->line = strdup("");

        }else{
        new->line = strdup(data);
        }
        new->linenumber = 1;
        new->next=NULL;
        editor.head = new;
        editor.tail=new;
        return SUCCESS;
  }


  if(editor.head==editor.tail){

     Node *new = malloc(sizeof(Node));
        new->previous = NULL;

         if(data==NULL){
            size_t len = 0;
            new->line = strdup("");

        }else{
       new->line = strdup(data);
        }

        new->next=NULL;
        editor.head->next = new;
        new->previous = editor.head;
        new->linenumber = editor.tail->linenumber+1;
        editor.tail=new;
        return SUCCESS;

  }





   if(editor.head!=editor.tail){

       Node *new = malloc(sizeof(Node));
       new->previous=NULL;

        if(data==NULL){
            size_t len = 0;
            new->line = strdup("");

        }else{
        new->line = strdup(data);
        }

       new->next=NULL;

       editor.tail->next = new;
       new->previous = editor.tail;
       new->linenumber = editor.tail->linenumber+1;
       editor.tail=new;
       return SUCCESS;
   }

}





int insertLineBetween(char *data){

  Node *t1 = editor.cursor;
  Node *t2 = editor.cursor->next;

  Node *new = malloc(sizeof(Node));
  new->previous=NULL;
  new->next = NULL;

  if(data==NULL){
            size_t len = 0;
            new->line = strdup("");
        }else{
        new->line = strdup(data);
        }
      new->previous = t1;
      new->next = t2;
      t1->next = new;
      t2->previous = new;
     new->linenumber = (t1->linenumber)+1;
      editor.cursor = new;
      editor.cursorPos = strlen(new->line);
      editor.cursorLine = new->linenumber;

     while(t2!=NULL){

        t2->linenumber+=1;
        t2 = t2->next;
     }


}


int delete_first()
{
    if(editor.head==NULL){
        return FAILURE;
    }

    if(editor.head==editor.tail){

        Node *temp = editor.head;
         editor.head->line[0] = '\0';
        Node *traverse = editor.head;
        editor.cursorPos = 0;
        editor.cursorLine = 0;
        return SUCCESS;
    }


    Node *temp  = editor.head;
    editor.head = editor.head->next;
    editor.head->previous = NULL;
    free(temp);
       Node *traverse = editor.head;
       editor.cursor = editor.head;
       editor.cursorPos = 0;
        while(traverse!=NULL){
           traverse->linenumber-=1;
           traverse = traverse->next;
        }
    return SUCCESS;
}


int deleteMiddle(){

     Node *t1 = editor.cursor->previous;
     Node *t2 = editor.cursor->next;
    Node *current = editor.cursor;
     current->previous =NULL;
     current->next = NULL;
     if(redo==1){
      RedoHead->Freeaddr = current;
     }else{
      UndoHead->Freeaddr = current;
     }
     free(current);
     t1->next = t2;
     t2->previous = t1;
     editor.cursor = t1;

     while(t2!=NULL){
        t2->linenumber -=1;
        if(t2->next == NULL){
          editor.tail = t2;
        }
        t2 = t2->next;
    }
}

int ShiftcharFromPosition(int position){

       int l = strlen(editor.cursor->line);

       if (position < 0 || position >= l) {
        return FAILURE;
       }

         for(int i=position;i<l;i++){
                editor.cursor->line[i] = editor.cursor->line[i+1];
          }
             editor.cursor->line[l-1] = '\0';
             editor.cursorPos-=1;
             return SUCCESS;
}



int delete_last()
{
    if(editor.head==NULL)
    {
        return FAILURE;
    }
    if(editor.head==editor.tail)
    {

         editor.head->line[0] = '\0';
        editor.cursor = editor.head;
        editor.cursorPos = 0;
        editor.cursorLine = 0;
        return SUCCESS;
    }

        Node *temp = editor.tail;
        editor.tail = temp->previous;
        editor.tail->next = NULL;
        temp->previous = NULL;
        editor.cursor = editor.tail;
        if(redo==1){
          RedoHead->Freeaddr = temp;
        }else{
        UndoHead->Freeaddr = temp;
        }
        free(temp);
        return SUCCESS;
}



int free_line(){

      if(editor.head==NULL){
        return FAILURE;
    }

    Node *p1 = editor.head;
    Node *p2 = editor.tail;

    while(editor.head != editor.tail){

      if(p1->next == editor.tail && p2->previous == editor.head){
           p1->next->previous = NULL;
       p1->next = NULL;
       p2->previous = NULL;

       if(p1->line !=NULL){
        free(p1->line);
       }

       if(p2->line!=NULL){
        free(p2->line);
       }

       free(p1);
       free(p2);

       editor.tail = NULL;
       editor.head = NULL;

      break;


      }

      editor.head = p1->next;
      editor.tail = p2->previous;

       p1->next->previous = NULL;
       p1->next = NULL;

       p2->previous->next = NULL;
       p2->previous = NULL;

       if(p1->line !=NULL){
        free(p1->line);
       }

       if(p2->line!=NULL){
        free(p2->line);
       }

       free(p1);
       free(p2);

       p1 = editor.head;
       p2 = editor.tail;

    }


   if((editor.head==editor.tail) && (editor.head !=NULL && editor.tail!=NULL)){
    Node *t = editor.head;
     if (t->line != NULL) {
        free(t->line);
    }
    free(t);
   }
    editor.head =  NULL;
    editor.tail = NULL;


  return SUCCESS;
}





int free_CopyNodes_Main(){

  if(copyHead==NULL && copyTail==NULL){
      return FAILURE;
    }

    Node *p1 = copyHead;
    Node *p2 = copyTail;

    while(copyHead != copyTail){

       if(p1->next == copyTail && p2->previous == copyHead){
       p1->next->previous = NULL;
       p1->next = NULL;
       p2->previous = NULL;

       if(p1->line !=NULL){
        free(p1->line);
       }

       if(p2->line!=NULL){
        free(p2->line);
       }

       free(p1);
       free(p2);
       copyTail = NULL;
       copyHead = NULL;
      break;

      }

      copyHead = p1->next;
      copyTail = p2->previous;
       p1->next->previous = NULL;
       p1->next = NULL;
       p2->previous->next = NULL;
       p2->previous = NULL;

       if(p1->line !=NULL){
        free(p1->line);
       }

       if(p2->line!=NULL){
        free(p2->line);
       }

       free(p1);
       free(p2);

       p1 = copyHead;
       p2 = copyTail;
    }

  if((copyHead == copyTail) && (copyHead!=NULL && copyTail!=NULL)){

    Node *t = copyHead;

    if(t->line!=NULL){
      free(t->line);
    }
    free(t);
  }
  copyHead =  NULL;
  copyTail = NULL;
  return SUCCESS;

}





  int delete_UndoStack()
{
    if(UndoHead==NULL){
        return FAILURE;
    }
  UndoAction *temp = UndoHead;

	while(UndoHead!=NULL){
	    delete_UndoNodes();
	}

	UndoHead= NULL;
  return SUCCESS;

}



int delete_UndoNodes()
{
    if(UndoHead==NULL){
        return FAILURE;
    }
    UndoAction *temp=UndoHead;
    UndoHead = UndoHead->next;
    temp->next = NULL;
    temp->line_specific = NULL;
    temp->specific_end = NULL;
    Delete_copyNodes_Undo(&temp->UndoCopyHead, &temp->UndoCopyTail);
    temp->ref = NULL;
    temp->Freeaddr = NULL;
    free(temp);
    return SUCCESS;
}


int Delete_copyNodes_Undo(Node **UndoCopyHead, Node **UndoCopyTail){

    if(*UndoCopyHead==NULL && *UndoCopyTail==NULL){
      return FAILURE;
    }

    Node *p1 = *UndoCopyHead;
    Node *p2 = *UndoCopyTail;

    while(*UndoCopyHead != *UndoCopyTail){

       if(p1->next == *UndoCopyTail && p2->previous == *UndoCopyHead){
           p1->next->previous = NULL;
       p1->next = NULL;

       p2->previous = NULL;

       if(p1->line !=NULL){
        free(p1->line);
       }

       if(p2->line!=NULL){
        free(p2->line);
       }

       free(p1);
       free(p2);

       *UndoCopyTail = NULL;
       *UndoCopyHead = NULL;

      break;


      }

      *UndoCopyHead = p1->next;
      *UndoCopyTail = p2->previous;

       p1->next->previous = NULL;
       p1->next = NULL;

         if (p2->previous != NULL) {
         p2->previous->next = NULL;   // break the link first
       }

       p2->previous = NULL;


       if(p1->line !=NULL){
        free(p1->line);
       }

       if(p2->line!=NULL){
        free(p2->line);
       }

       free(p1);
       free(p2);

       p1 = *UndoCopyHead;
       p2 = *UndoCopyTail;

    }

  if((*UndoCopyHead == *UndoCopyTail) && (*UndoCopyHead!=NULL && *UndoCopyTail!=NULL)){

    Node *t = *UndoCopyHead;
    if (t->line != NULL) {
    free(t->line);
  }
    free(t);
  }
    *UndoCopyHead =  NULL;
    *UndoCopyTail = NULL;


  return SUCCESS;

}


 int delete_RedoStack()
{

    if(RedoHead==NULL){
        return FAILURE;
    }
  UndoAction *temp = RedoHead;

	while(UndoHead!=NULL){
	    delete_RedoNodes();
	}


	RedoHead= NULL;
  return SUCCESS;

}


int delete_RedoNodes()
{
    if(RedoHead==NULL){
        return FAILURE;
    }
    UndoAction *temp=RedoHead;
    RedoHead = RedoHead->next;
    temp->next = NULL;
    temp->line_specific = NULL;
    temp->specific_end = NULL;
    Delete_copyNodes_Redo(&temp->UndoCopyHead, &temp->UndoCopyTail);
    temp->ref = NULL;
    temp->Freeaddr = NULL;
    free(temp);
    return SUCCESS;
}



int Delete_copyNodes_Redo(Node **UndoCopyHead, Node **UndoCopyTail){

    if(*UndoCopyHead==NULL && *UndoCopyTail==NULL){
      return FAILURE;
    }

    Node *p1 = *UndoCopyHead;
    Node *p2 = *UndoCopyTail;

    while(*UndoCopyHead != *UndoCopyTail){

      if(p1->next == *UndoCopyTail && p2->previous == *UndoCopyHead){
           p1->next->previous = NULL;
       p1->next = NULL;

       p2->previous = NULL;

       if(p1->line !=NULL){
        free(p1->line);
       }

       if(p2->line!=NULL){
        free(p2->line);
       }

       free(p1);
       free(p2);

       *UndoCopyTail = NULL;
       *UndoCopyHead = NULL;

      break;


      }

      *UndoCopyHead = p1->next;
      *UndoCopyTail = p2->previous;

       p1->next->previous = NULL;
       p1->next = NULL;

         if (p2->previous != NULL) {
         p2->previous->next = NULL;   // break the link first
       }
       p2->previous = NULL;

       if(p1->line !=NULL){
        free(p1->line);
       }

       if(p2->line!=NULL){
        free(p2->line);
       }

       free(p1);
       free(p2);

       p1 = *UndoCopyHead;
       p2 = *UndoCopyTail;

    }


   if((*UndoCopyHead==*UndoCopyTail) && (*UndoCopyHead !=NULL && *UndoCopyTail!=NULL)){
    Node *t = *UndoCopyHead;
    if(t->line!=NULL){
      free(t->line);
    }
    free(t);
   }
    *UndoCopyHead =  NULL;
    *UndoCopyTail = NULL;


  return SUCCESS;

}


int Free_insertHashTable(){

 ChainNode *curr;
   for(int i=0;i<hash_st;i++){
     curr = UndoRedo_Table[i];
      while(curr!=NULL){
      ChainNode *next = curr->next;

       curr->addr = NULL;
       free(curr);
       curr = next;
      }
     UndoRedo_Table[i] = NULL;
   }

free(UndoRedo_Table);
}


int Free_BackSpaceTable(){

  ChainNode *curr;
  for(int i=0;i<back_st;i++){

    ChainNode *curr = UndoRedo_Backspace[i];

    while(curr!=NULL){

       ChainNode *next = curr->next;
       curr->addr = NULL;
       free(curr);
       curr = next;
    }
    UndoRedo_Backspace[i] = NULL;
  }
free(UndoRedo_Backspace);

}

int Free_EnterTable(){

   ChainNode *curr;
   for(int i=0;i<enter_st;i++){

      ChainNode *curr = enterAddress[i];

      while(curr!=NULL){

         ChainNode *next = curr->next;
         curr->addr = NULL;
        free(curr);
        curr=next;
      }
    enterAddress[i] = NULL;

   }

free(enterAddress);


}


int Free_CutTable(){

        for(int i=0;i<cut_st;i++){
            cutAddress[i] = NULL;
        }

     free(cutAddress);
}



int Free_PasteTable(){

        for(int i=0;i<paste_st;i++){
            pasteAddress[i] = NULL;
        }

     free(pasteAddress);
}
