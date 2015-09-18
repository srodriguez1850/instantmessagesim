#include "simpletools.h"
#include "badgealpha.h"
#include "logicalphysical.h"

info their;
char l_addr[7] = "100.111";
char p_addr[2] = "47";
char* p_addr_to;

int x, y, z;  // Accelerometer

void screen_img180();
void screen_img(char *imgaddr);

void main()
{
  // Initialize badge
  badge_setup();
  leds_set(0b111111);
  
  // Initialize IR
  ir_start();
  pause(200);
  clear();
  
  char_size(SMALL);
  memset(&p_addr_to, 0, 2);
  leds_set(0b000000);
  
  while(1)
  {
    tilt_get(&x, &y, &z);
    if (y < -35)
    {
      clear();
      screen_autoUpdate(OFF);
      char_size(SMALL);
      cursor(0, 0);
      display("go to");
      cursor(0, 1);
      display(p_addr_to);
      screen_img180();
      screen_autoUpdate(ON);
      while(y < -35)
      {
        tilt_get(&x, &y, &z);
        pause(200);
      }
      clear();
    }
    else if (check_inbox() == 1)
    {
      // Check incoming data from packet
      // Check destination with database
      // Then redirect to router/endpoint
      clear();
      char_size(SMALL);
      cursor(0, 0);
      display("looking up");
      message_get(&their);
      p_addr_to = logicalToPhysicalLookup(their.name, l_addr);
      pause(200);
      rgb(L, OFF);
      rgb(R, OFF);
      clear();
    }
    else
    {
      // default screen
      char_size(BIG);
      cursor(0, 0);
      display(p_addr);
    }      
  }
}

void screen_img180()
{
  uint32_t screenbuf = screen_getBuffer();
  char *scrbuf = (char *) screenbuf;
  screen_autoUpdate(OFF);
  int byte, bit, pix, xp, yp, bytep, bitp, pixp;
  for(int x = 0; x < 64; x++)
  {
    for(int y = 0; y < 64; y++)
    {
      byte = ((y >> 3) << 7) + x;
      bit = y % 8;  
      pix = 1 & (scrbuf[byte] >> bit);
      
      xp = 127 - x;
      yp = 63 - y;

      bytep = ((yp >> 3) << 7) + xp;
      bitp = yp % 8;  
      pixp = 1 & (scrbuf[bytep] >> bitp);

      scrbuf[bytep] &= ~(1 << bitp);
      scrbuf[bytep] |= (pix << bitp);
      
      scrbuf[byte] &= ~(1 << bit);
      scrbuf[byte] |= (pixp << bit);
    }
  } 
  screen_autoUpdate(ON); 
}