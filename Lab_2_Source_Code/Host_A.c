#include "Sim_Engine.h"

#define SIZE 20
#define BUFF_SIZE 100000
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct pkt packet;
float Timeout;

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

struct pkt A_createpacket(int seq, struct msg message)
{
  printf("A skapar en packet\n");
  packet.seqnum = seq;
  packet.acknum = 0;
  strcpy(packet.payload, message.data);
  packet.checksum = calculate_checksum(packet);
}

int packet_no;
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

  if(packet_no == 0 && ACK1 == 1){
    ACK0 = 0;
    A_createpacket(0, buffer[buff_read]);
    buff_read++;
    tolayer3(0, packet);
    printf("\nRound %d, buffer[%d], message: %s\n", rnd, i - 1, message.data);
    rnd++;
    starttimer(0, Timeout); printf("Packet 1 skickat, timer 1 started\n");
  }
}

/* Called from layer 3, when a packet arrives for layer 4 */
void A_input(struct pkt packet)
{
  /* TODO */
  // Här hamnar packetet som B skickar till A.
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
