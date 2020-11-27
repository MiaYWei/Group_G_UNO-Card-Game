#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

struct player_details {
   int player_id;
   int curr_score;
   char player_name[15];
   struct player_details *next;
};

struct player_details *head = NULL;
struct player_details *current = NULL;

void insertPlayerDetails(int player_id, int curr_score, char name[15]) {
   //create a link
   struct player_details *link = (struct player_details*) malloc(sizeof(struct player_details));
	
   link->player_id = player_id;
   link->curr_score = curr_score;
   strcpy_s(link->player_name,15, name);
	
   //point it to old first node
   link->next = head;
	
   //point first to new first node
   head = link;
}

void printPlayerDetails() {
   struct player_details *ptr = head;
   printf("\n[ ");
	
   //start from the beginning
   while(ptr != NULL) {
      printf("(%d,%d,%s) ",ptr->player_id,ptr->curr_score,ptr->player_name);
      ptr = ptr->next;
   }
	
   printf(" ]");
}

void getPLayerName(int player_id) {
   struct player_details* current = head;

   //if list is empty
   //navigate through list
   while(current != NULL) {
      
      //if it is last node
      //go to next link
      if(current->player_id == player_id){
        
        printf("\n%s", current->player_name);
        
      }
      current = current->next;
      
   }
}

void updatePlayerDetails(int player_id, int curr_score) {

   //start from the first link
   struct player_details* current = head;

   //if list is empty
   //navigate through list
   while(current != NULL) {
      
      //if it is last node
      //go to next link
      if(current->player_id == player_id){
        
        current-> curr_score = curr_score;
        
      }
      current = current->next;
      
   }      
	
}

#if 1
void main(){

  insertPlayerDetails(1,10,"Abhinav");
  updatePlayerDetails(1,20);
  //insertPlayerDetails(2,10);
  //insertPlayerDetails(3,130);
  //updatePlayerDetails(3,60);
  printPlayerDetails();
  getPLayerName(1);

}
#endif


