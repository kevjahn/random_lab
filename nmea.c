#if 1
#include "nmea.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>

#include "rtc.h"
#include "debug.h"
#include "hw_uart1.h"
#include "hw_uart2.h"
#include "hw_timer2.h"

#include "core/arm_math.h"
#include "core/arm_common_tables.h"

static  char buff[100] , buf[100];
static  uint32_t x=0, stat=0 , j=6;
static  char *start, *end;


//if(buff[x] == '\r'){ //\r << left \n line feed

struct __attribute__((packed)) TSIP_8F_AB {
  uint32_t secondsOfWeek;
  uint16_t weekNumber;
  int16_t UTC_offset;
  uint8_t GPS_UTC_time : 1;
  uint8_t GPS_UTC_PPS  : 1;
  uint8_t time_set     : 1;
  uint8_t has_UTC      : 1;
  uint8_t from_UTC     : 1;
  uint8_t seconds;
  uint8_t minutes;
  uint8_t hours;
  uint8_t day;
  uint8_t month;
  uint16_t year;
} tsip_ab;

struct nmea_rmc{
  char UTC[20];
}rmc;

//TODO: read RMC to get date, time and GLL (position);

void nmea_init(){
  hw_uart2_Init();
  //hw_uart1_Init();
}

void gnrmc(){
int i=8;

while(buff[i++] != ',')
{
 if (buff[i-1] != ','){
  rmc.UTC[j++] = buff[i-1];
 }

}
/*
while(buff[i++] != ',')
;
*/

}

// CTRL // OR L OR D OR D
void nmea_read()
{
  #if 1
  if(hw_uart1_available()){
    hw_uart1_read(&buff[x++]);
    if(buff[x-1] == '\r'){
      //start = memchr(buff, '\r\n', strlen(buff));
      uart1Print(buff);

      if(buff[4] == 'R' && buff[5] == 'M'){ // it's working. > Was ich getan habe, funktioniert
        gnrmc();
        uart1Print(rmc.UTC);
      }
      //    uart1Print(start);
      memset(buff, '\0', x);
      memset(rmc.UTC, '\0', 20);
      x=0;
      j=0;
    }
  }
}
#endif


#endif
