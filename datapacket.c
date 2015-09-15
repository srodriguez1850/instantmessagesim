#include "simpletools.h"
#include "badgealpha.h"
#include "fdserial.h"

int havemessage = 0;

info their;
info storage;

void main()
{
  // Initialize badge
  badge_setup();
  simpleterm_close();

  // Initialize IR
  leds_set(0b111111);
  ir_start();
  pause(500);
  leds_set(0b000000);
  clear();

  char_size(SMALL);
  memset(&storage, 0, sizeof(info));

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
      cursor(0, 2);
      display("Sending...");
      ir_send(&storage);
      cursor(0, 3);
      display("Complete.");
      havemessage = 1;
      pause(500);
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
/*
info my = {{" "}, {"INFO"}, 0};
info my_init = {{" "}, {"INIT"}, 0};
info my_resp = {{" "}, {"RESP"}, 0};
info their;
info last = {{" "}, {" "}, 0};

int id_address = 65335;

char handshake[5];
fdserial *port;

int x, y, z;  // accelerometer
int havemessage = 0;

void screen_img180();
void screen_img(char *imgaddr);

void main()
{
  // Initialize badge and serial connection
  badge_setup();
  simpleterm_close();
  
  // Pull ID from EEPROM
  leds_set(0b111111);
  char id[7];
  ee_getStr(id, 7, id_address);
  strcpy(my.name, id);
  strcpy(my_init.name, id);
  strcpy(my_resp.name, id);
  
  pause(200);
  
  
  leds_set(0b100001);
  ir_start();
  pause(500);
  clear();
  
  while(1)
  {
    memset(&their, 0, sizeof(info));
    if (havemessage)
    {
      clear();
      leds_set(0b000000);
      char_size(SMALL);
      cursor(0, 2); 
      display("Bearing Message");
      cursor(5, 3);
      display("to");
      cursor(5, 4);
      display(last.name);
      cursor(0, 5);
      display(last.email);
      cursor(0, 7);
      display("OSH to Continue.");
      while(pad(6) != 1);
    }
    else if (pad(1) == 1 && pad(4) == 1)
    {
      clear();
      cursor(3, 2);
      display("Listening...");
      led(4, ON); 
      led(1, ON);
      rgb(L, BLUE);
      //ir_send(&my_init);
      rgb(L, OFF); 
      led(4, OFF);
      led(1, OFF);
      
      int t = CNT;
      int dt = CLKFREQ * 2;
      int response = 1;
      
      while (check_inbox() == 0)
      {
        if (CNT - t > dt)
        {
          clear();
          response = 0;
          break;
        }
      }
      if (response == 0) continue;
      
      clear();
      message_get(&their);
      if (strcmp(their.email, "NULL"))
      {
        memset(&last, 0, sizeof(info));
        last = their;
        ee_save(&their);
        cursor(2, 1);
        display("GOT MESSAGE!");
        cursor(3, 4);
        display("to: %s", their.name);
        cursor(0, 7);
        display("OSH to Continue.");
        rgb(L, OFF);
        while(pad(6) != 1);
        rgb(R, OFF);
        havemessage = 1;
        clear();
      }
      else
      {
        rgb(L, OFF);
        rgb(R, OFF);
      }        
    }
    else if(check_inbox() == 1)
    {
      //clear();
      //message_get(&their);
      //if (!strcmp(their.email, "INIT"))
     // {
      //  memset(&last, 0, sizeof(info));
      //  last = their;
      //  ee_save(&their);
      //  cursor(2, 1);
      //  display("INTERACTION!");
      //  rgb(L, BLUE);
     //   ir_send(&my_resp);
      //  rgb(L, OFF);
     //   cursor(3, 4);
     //   display("ID: %s", their.name);
     //   cursor(0, 7);
     //   display("OSH to Continue.");
     //   rgb(L, OFF);
      //  while(pad(6) != 1);
      //  rgb(R, OFF);
     //   clear();
     // }           
    }
    else
    {
      char_size(BIG);
      cursor(0, 0); 
      display("%s", my_init.name);
      char_size(SMALL);
      cursor(4, 6);
      display("...is ready.");
      leds_set(0b101101);
      pause(100);
    }      
  }    
}  
*/