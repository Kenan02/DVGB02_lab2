#include "Sim_Engine.h"

#define SIZE 20
#define BUFF_SIZE 100000



struct pkt packet;


// Skapa en int checksum
int calculate_checksum(struct pkt packet)
{
  int sum = 0;
  for (int i = 0; i < SIZE; i++)
  {
    sum += packet.payload[i];
  }

  sum += packet.seqnum + packet.acknum;
  return sum;
}

struct pkt A_createpkt(int seq, struct msg message)
{
  printf("A skapar en packet\n");
  packet.seqnum = seq;
  packet.acknum = 0;
  strcpy(packet.payload, message.data);
  packet.checksum = calculate_checksum(packet);
  
}

int packet_num;
int ACK0, ACK1;
struct msg buffer[BUFF_SIZE];
int buff_read = 0;
int rnd = 1;
int i = 0;
/* Called from layer 5, passed the data to be sent to other side */
void A_output(struct msg message)
{
  /* TODO */
  // Det som skickas över till B sidan
  buffer[i] = message;
  i++;

  if(packet_num == 0 && ACK1 == 1){
    ACK0 = 0;
    A_createpkt(0, buffer[buff_read]);
    buff_read++;
    tolayer3(0, packet);
    printf("\nRound %d, buffer[%d], message: %s\n", rnd, i - 1, message.data);
    rnd++;
    starttimer(0, time); printf("Packet 1 skickat, timer 1 started\n");
    packet_num = 1;
  }

  if(packet_num == 1 && ACK0 == 1){
    ACK1 = 0;
    A_createpkt(1, buffer[buff_read]);
    buff_read++;
    tolayer3(0, packet);
    printf("\nRound %d, buffer[%d], message: %s\n", rnd, i - 1, message.data);
    rnd++;
    starttimer(0, time); printf("Packet 1 skickat, timer 1 started");
    packet_num = 0;
  }
}

/* Called from layer 3, when a packet arrives for layer 4 */
void A_input(struct pkt packet)
{
  /* TODO */
  // Här hamnar packetet som B skickar till A.
  int int_payload = atoi(packet.payload);
  int calc_sum = packet.acknum + packet.seqnum + int_payload;
  printf("ACK %d recieved: \n", packet.acknum);
}

/* Called when A's timer goes off */
void A_timerinterrupt()
{
  /* TODO */
}

/* The following routine will be called once (only) before any other */
/* Host A routines are called. You can use it to do any initialization */
void A_init()
{
  /* TODO */
}
