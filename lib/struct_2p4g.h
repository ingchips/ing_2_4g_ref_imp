
#ifndef STRUCT__2P4G__H
#define STRUCT__2P4G__H
#include "stdint.h"


#define MAX_PACKET_NUM  1//30

#define MIN_CARRY_TIME 200


typedef struct
{
  uint32_t  DataLen;    //Data length
  uint8_t*  Data;       //Data Pointer
} ING2P4G_Data_S;

typedef struct
{
  uint8_t   DataLen;    //Data length
  uint8_t*  Data;       //Data Pointer
  uint8_t   PktFinish;  //Packet 
  uint8_t   CRCErr;     //CRC Error Flag
  uint8_t   SyncErr;    //Sync Error Flag
} ING2P4G_Packet_S;

typedef struct
{
  uint32_t  DataLen;    //Data length
  uint8_t*  Data;       //Data Pointer
  uint8_t   PktFinish;  //Packet 
  uint32_t  TxcontAddr; //
} ING2P4G_TxPacket_S;

typedef struct
{
  uint8_t   DataLen;    //Data length
  uint8_t   Data[256];       //Data Pointer
  uint32_t  RxontAddr; //
  uint8_t   PktFinish;  //Packet 
  uint8_t   CRCErr;     //CRC Error Flag
  uint8_t   SyncErr;    //Sync Error Flag
} ING2P4G_RxPacket_S;

typedef struct
{
  uint8_t PacketNum;
  ING2P4G_TxPacket_S  TxPackets[MAX_PACKET_NUM];
} ING2P4G_TxPacketBuffer_S;


#endif
