#include "simpletools.h"
#include "badgealpha.h"

int havemessage = 0;

info their;
info storage;

int hop_counter[129];
char hop_display[129];
int hop_index = -1;

char hex_table[17] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F', 0 }; 

int x, y, z; // Accelerometer

void screen_img180();
void screen_img(char *imgaddr);
void initializeHopCounters();
void displayHopCounters();

void main()
{
  // Initialize badge
  badge_setup();
  leds_set(0b111111);
  simpleterm_close();

  // Initialize IR
  ir_start();
  pause(200);
  clear();

  // Initialize memory
  char_size(SMALL);
  memset(&storage, 0, sizeof(info));
  initializeHopCounters();
  leds_set(0b000000);

  while(1)
  {
    memset(&their, 0, sizeof(info));
    tilt_get(&x, &y, &z);
    if (y < -35)
    {
      clear();
      screen_autoUpdate(OFF);
      displayHopCounters();
      screen_img180();
      screen_autoUpdate(ON);
      while(y < -35)
      {
        tilt_get(&x, &y, &z);
        pause(200);
      }
      clear();
    }       
    else if (check_inbox() == 1 && havemessage == 0)
    {
      clear();
      message_get(&their);
      havemessage = 1;
      hop_index++;
      cursor(2, 3);
      display("GOT MESSAGE!");
      storage = their;
      cursor(0, 5);
      display("OSH to continue.");
      while(pad(6) != 1);
      rgb(L, OFF);
      rgb(R, OFF);
      clear();
    }
    else if (check_inbox() == 1 && havemessage == 1)
    {
      // reject new message
      message_get(&their);
      rgb(L, RED);
      rgb(R, RED);
      pause(100);
      rgb(L, OFF);
      rgb(R, OFF);
      pause(100);
      rgb(L, RED);
      rgb(R, RED);
      pause(100);
      rgb(L, OFF);
      rgb(R, OFF);      
    }
    else if (pad(1) == 1 && pad(4) == 1 && havemessage == 1)
    {
      // send data, increase hop counter
      clear();
      cursor(0, 4);
      display("Sending data....");
      hop_counter[hop_index]++;
      rgb(L, BLUE);
      rgb(R, BLUE);
      ir_send(&storage);
      rgb(L, OFF);
      rgb(R, OFF);
      while(pad(1) == 1 && pad(4) == 1);
      clear();
    }
    else
    {
      // default screen
      if (havemessage)
      {
        leds_set(0b010010);
        cursor(2, 3);
        display("FULL PACKET!");
        cursor(5, 5);
        display("Trash:");
        cursor(1, 6);
        display("Press  Corners");
        rgb(L, YELLOW);
        rgb(R, YELLOW);
        if (pad(0) && pad(2) && pad(3) && pad(5))
        {
          clear();
          rgb(L, OFF);
          rgb(R, OFF);
          leds_set(0b000000);
          havemessage = 0;
          memset(&storage, 0, sizeof(info));
          cursor(1, 3);
          display("PACKET TRASHED");
          cursor(0, 5);
          display("OSH to continue.");
          while(pad(6) != 1);
          clear();
        }          
      }
      else
      {
        leds_set(0b000000);
        cursor(2, 4);
        display("EMPTY PACKET");
        rgb(L, OFF);
        rgb(R, OFF);
      }
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

void initializeHopCounters()
{
  for (int i = 0; i < 128; i++)
  {
    hop_counter[i] = 0;
    hop_display[i] = 0;
  }
  hop_counter[128] = 16;
  hop_display[128] = 0;
}

void displayHopCounters()
{
  // BUG: if there's an overflow, the null (0) terminator cuts off the display
  char_size(SMALL);
  cursor(0, 0);
  for (int i = 0; i < hop_index + 1; i++)
  {
    hop_display[i] = hex_table[hop_counter[i]];
  }
  if (hop_index > -1) display(hop_display);
  else
  {
    cursor(3, 3);
    display("NO RECORDS");
  }    
}  