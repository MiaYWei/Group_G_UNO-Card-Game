/**
 * Recursively free the given deck
 * @param d deck to be freed
 */
 
 
void free_deck(Deck* d) {
  // Recursively free the deck
  if (d != NULL) {
    free_deck(d->next);
    free(d);
  }
}



/**
 * Swapping two Cards
 * @param *a address of the first card.
 * @param *b address of the sencond card.
 */

void swap(Card *a, Card *b) {
    Card temp = *a;
    *a = *b;
    *b = temp;
}


/**
 * shuffle_cards the cards in remaining_pile
 * @param length current length of remaining_pile
 * @return the shuffled deck
 */

struct Deck *shuffle_cards(int length) {
    // reset seed
    srand(time(NULL));
    // copy the cards in remaining pile into a Card array
	
    Deck *current = remaining_pile;
    Card *array = malloc(sizeof(Card)*length);
    if (array==NULL) {
      free_deck(remaining_pile);
      return NULL;
    }
    for (int i=0; i<length; i++) {
        array[i] = current->card;
        current = current->next;
    }
    
    // loop through the cards array and swap them randomly, using Fisher-Yates shuffle_cards
    for (int i=0; i<length; i++) {
        // find a random index to swap with the current one
        int random_index = rand() % (length-i) +i;
        swap(&array[random_index],&array[i]);
    }

    // Put cards in array back to the remaining pile in the shuffle_cardsd order
    current = remaining_pile;
    for (int i=0; i<length-1; i++) {
        current->card = array[i];
        current = current->next;
    }
    //To make sure that there is no memory spaces assigned to the next deck of the last element of the whole cards
    // Set the last elements's next deck to null
    current->card = array[length-1];
    current->next = NULL;
    free(array);
    return current;
}
