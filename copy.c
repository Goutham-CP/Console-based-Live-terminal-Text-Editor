#include"Header.h"


void copy(){

    if(startcursor!=endcursor && startPos==0 && (( (strlen(startcursor->line)==0 || strlen(startcursor->line)>0)) && (((endPos>=strlen(endcursor->line)-1 && strlen(endcursor->line)!=0) )|| (endPos==0 && strlen(endcursor->line)==0)))){  // scaenario for cut multiple line whose cursor pos is 0 in startcursor and last character in end character

        Node *temp = startcursor;
        int i = startcursor->linenumber;

        while(i<=endcursor->linenumber){
           insert_Last_Copy(temp);
             temp = temp->next;
             i+=1;
        }

    }else if(startcursor==endcursor && startPos==0 && endPos>=strlen(startcursor->line)-1 ){

             insert_Last_Copy(startcursor);

    }else if(startcursor==endcursor && startPos==0 && endPos<strlen(editor.cursor->line)-1 && (startPos !=endPos)){

           if(startPos==0 && endPos<strlen(endcursor->line)-1){
            char *dup = strdup(startcursor->line);
              startcursor->line[endPos+1] = '\0';
              CheckAndFree_OldCopy();
              insert_Last_Copy(startcursor);
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

              insert_Last_Copy(startcursor);
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

              insert_Last_Copy(startcursor);
              startcursor->line = realloc(startcursor->line , strlen(dup)+1);
              strcpy(startcursor->line,dup);
              free(dup);

          } else if(startcursor != endcursor && startPos==0 && endPos<strlen(endcursor->line)-1){

          char *dup = strdup(endcursor->line);
          endcursor->line[endPos+1]='\0';

           Node *temp = startcursor;
        int i = startcursor->linenumber;


        while(i<=endcursor->linenumber){
            insert_Last_Copy(temp);
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
             insert_Last_Copy(temp);
             temp = temp->next;
             i+=1;
        }


      startcursor->line = realloc(startcursor->line,strlen(dup1)+1);
        strcpy(startcursor->line,dup1);
        free(dup1);

   }else if(startcursor !=endcursor && (startPos>0 && startPos<=strlen(startcursor->line)-1) && (endPos>=0 && endPos<strlen(endcursor->line)-1)) {

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
             insert_Last_Copy(temp);
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
             insert_Last_Copy(temp);
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
             insert_Last_Copy(temp);
             temp = temp->next;
             i+=1;
        }

          startcursor->line = realloc(startcursor->line,strlen(dup1)+1);
          strcpy(startcursor->line,dup1);
          strcpy(endcursor->line,dup2);
           free(dup1);
            free(dup2);

      }else if((startPos==strlen(startcursor->line) && strlen(startcursor->line)!=0) && (endPos>0 && endPos<strlen(endcursor->line) && strlen(endcursor->line)!=0)){

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
             insert_Last_Copy(temp);
             temp = temp->next;
             i+=1;
        }

          startcursor->line = realloc(startcursor->line,strlen(dup1)+1);
          strcpy(startcursor->line,dup1);
          strcpy(endcursor->line,dup2);
           free(dup1);
           free(dup2);

      }else if((startPos==strlen(startcursor->line) && strlen(startcursor->line) !=0) && (endPos==0 && strlen(endcursor->line)==0)){

             char *dup1 = strdup(startcursor->line);
             char *dup2 = strdup(endcursor->line);
             int shift = startPos - 0 ;
             int len = strlen(startcursor->line);
            startcursor->line[0] = startcursor->line[len];
            Node *temp = startcursor;
            int i = startcursor->linenumber;

        while(i<=endcursor->linenumber){
             insert_Last_Copy(temp);
             temp = temp->next;
             i+=1;
        }

          startcursor->line = realloc(startcursor->line,strlen(dup1)+1);
          strcpy(startcursor->line,dup1);
           free(dup1);

      }else if((startPos==strlen(startcursor->line) && strlen(startcursor->line)!=0) && (endPos>0 && endPos==strlen(endcursor->line) && strlen(endcursor->line)!=0)){

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
             insert_Last_Copy(temp);
             temp = temp->next;
             i+=1;
        }

          startcursor->line = realloc(startcursor->line,strlen(dup1)+1);
          strcpy(startcursor->line,dup1);
           free(dup1);
           free(dup2);
      }
    }

  void  CheckAndFree_OldCopy(){

      if(copyHead==NULL && copyTail==NULL){
         return;

      }else{

         Node *temp = copyHead;

         while(temp!=NULL){

            Node *next = temp->next;
            free(temp);
            temp = next;
         }
         copyHead=NULL;
         copyTail = NULL;

      }
  }


    int insert_Last_Copy( Node *temp){

  if(copyHead==NULL){
        Node *new = malloc(sizeof(Node));
        new->previous = NULL;
        new->line = strdup(temp->line);
        new->linenumber = 1;
        new->next=NULL;
        copyHead = new;
        copyTail=new;
        return SUCCESS;
  }


  if(copyHead==copyTail){

     Node *new = malloc(sizeof(Node));
        new->previous = NULL;
       new->line = strdup(temp->line);
        new->next=NULL;
        copyHead->next = new;
        new->previous = copyHead;
        new->linenumber = copyTail->linenumber+1;
        copyTail=new;
        return SUCCESS;
  }

   if(copyHead!=copyTail){

       Node *new = malloc(sizeof(Node));
       new->previous=NULL;
        new->line = strdup(temp->line);
       new->next=NULL;
       copyTail->next = new;
       new->previous = copyTail;
       new->linenumber = copyTail->linenumber+1;
       copyTail=new;
       return SUCCESS;
   }

}