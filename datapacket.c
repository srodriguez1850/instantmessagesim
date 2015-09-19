#include "simpletools.h"
#include "badgealpha.h"

int havemessage = 0;

info their;
info storage;

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

  char_size(SMALL);
  memset(&storage, 0, sizeof(info));
  leds_set(0b000000);

  while(1)
  {
    memset(&their, 0, sizeof(info));
    if (check_inbox() == 1 && havemessage == 0)
    {
      clear();
      message_get(&their);
      havemessage = 1;
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
      clear();
      cursor(0, 4);
      display("Sending Contents");
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
        cursor(0, 5);
        display("Trash: P17 & P27");
        rgb(L, YELLOW);
        rgb(R, YELLOW);
        if (pad(0) == 1 && pad(5) == 1)
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

// 128x15, display when flipping