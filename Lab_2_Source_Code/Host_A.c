#include "Sim_Engine.h"


//Skapa en int checksum

/* Called from layer 5, passed the data to be sent to other side */
void A_output( struct msg message) {
  /* TODO */
  //Det som skickas över till B sidan
  
}

/* Called from layer 3, when a packet arrives for layer 4 */
void A_input(struct pkt packet) {
  /* TODO */
  //Här hamnar packetet som B skickar till A.
  
  
}

/* Called when A's timer goes off */
void A_timerinterrupt() {
  /* TODO */
}  

/* The following routine will be called once (only) before any other */
/* Host A routines are called. You can use it to do any initialization */
void A_init() {
  /* TODO */
}
