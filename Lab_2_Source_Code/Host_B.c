#include "Sim_Engine.h"

#define SIZE 20

struct pkt ack;

int CheckSum(char *p)
{
  int sum = 0;
  for (int i = 0; i < SIZE; i++)
  {
    sum += p[i];
  }

  return sum;
}

void make_ack(int seq)
{
  ack.acknum = seq;
  ack.seqnum = seq;

  ack.checksum = ack.acknum + ack.seqnum;
}
/* Called from layer 5, passed the data to be sent to other side */
void B_output(struct msg message)
{
  /* DON'T IMPLEMENT */
}

/* Called from layer 3, when a packet arrives for layer 4 */
int exp_pack;
void B_input(struct pkt packet)
{
  /* TODO */
  // B_INPUT är vad B får utav a, måste kolla chekcsum
  //  och skicka en NACK eller ACK
  int int_payload = CheckSum(packet.payload);
  int calc_checksum = packet.seqnum + packet.acknum + int_payload;
  if (packet.checksum == calc_checksum)
  {
    make_ack(packet.acknum);
    tolayer3(1, ack);

    printf("Packet %d received, packet.checksum: %d calc_checksum: %d, data: %s\n\n", packet.seqnum, packet.checksum, calc_checksum, packet.payload);
    if (exp_pack == packet.seqnum)
      tolayer5(1, packet.payload);

    if (exp_pack == 0)
    {
      exp_pack = 1;
      printf("ACK 0 sent\n");
    }
    else if (exp_pack == 1)
    {
      exp_pack = 0;
      printf("ACK 1 sent\n");
    }
    else
    {
      printf("Packet %d received\n", packet.seqnum);
      printf("checksum mismatch, packet checksum: %d, calc_checksum: %d", packet.checksum, calc_checksum);
    }
  }
  else
  {
    printf("Packet %d received\n", packet.seqnum);
    printf("Packet dropped, was expecting packet %d\n", exp_pack);
  }
}

/* Called when B's timer goes off */
void B_timerinterrupt()
{
  /* TODO */
}

/* The following routine will be called once (only) before any other */
/* Host B routines are called. You can use it to do any initialization */
void B_init()
{
  /* TODO */
  exp_pack = 0;
}
