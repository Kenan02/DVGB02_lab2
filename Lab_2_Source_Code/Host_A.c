#include "Sim_Engine.h"

#define SIZE 20
#define BUFF_SIZE 100000

struct pkt packet;
float Timeout;

// Skapa en int checksum
int calculate_checksum(char *p)
{
  int sum = 0;
  for (int i = 0; i < SIZE; i++)
  {
    sum += p[i];
  }

  return sum;
}

struct pkt A_createpkt(int seq, struct msg message)
{
  printf("A skapar en packet\n");
  packet.seqnum = seq;
  packet.acknum = seq;
  strcpy(packet.payload, message.data);
  int int_msg = calculate_checksum(packet.payload);
  packet.checksum = int_msg + packet.seqnum + packet.acknum;
}

int packet_num;
int ack0, ack1;
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

  if (packet_num == 0 && ack1 == 1)
  {
    ack0 = 0;
    A_createpkt(0, buffer[buff_read]);
    buff_read++;
    tolayer3(0, packet);
    starttimer(0, Timeout);
    printf("\nRound %d, buffer[%d], message: %s\n", rnd, i - 1, message.data);
    rnd++;
    printf("Packet 0 skickat, timer 0 started\n");
    packet_num = 1;
  }

  if (packet_num == 1 && ack0 == 1)
  {
    ack1 = 0;
    A_createpkt(1, buffer[buff_read]);
    buff_read++;
    tolayer3(0, packet);
    starttimer(0, Timeout);
    printf("\nRound %d, buffer[%d], message: %s\n", rnd, i - 1, message.data);
    rnd++;
    printf("Packet 1 skickat, timer 1 started\n");
    packet_num = 0;
  }
}

/* Called from layer 3, when a packet arrives for layer 4 */
void A_input(struct pkt packet)
{
  /* TODO */
  // Här hamnar packetet som B skickar till A.
  int calc_sum = packet.acknum + packet.seqnum;

  printf("checksum: %d, calculated checksum: %d\n\n", packet.checksum, calc_sum);
  if (packet.checksum == calc_sum)
  {

    if (packet.acknum == 0)
    {
      ack0 = 1;
      stoptimer(0);
      printf("ACK 0 recevied, timer 0 stopped\n");
    }
    if (packet.acknum == 1)
    {
      ack1 = 1;
      stoptimer(0);
      printf("ACK 1 received, timer 1 stopped\n");
    }
  }
}

/* Called when A's timer goes off */
void A_timerinterrupt()
{
  /* TODO */
  printf("timeout packet %d: ", packet.seqnum);

  // retransmitt package and start timer again
  tolayer3(0, packet);
  printf("Retransmitting packet:%d.\n", packet.seqnum);
  starttimer(0, Timeout);
}

/* The following routine will be called once (only) before any other */
/* Host A routines are called. You can use it to do any initialization */
void A_init()
{
  /* TODO */
  packet_num = 0;
  Timeout = 11;
  ack1 = 1;
  ack0 = 1;
}
