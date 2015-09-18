#include "simpletools.h"
#include "badgealpha.h"
#include "humanlogical.h"

int ir_attempts = 1;

char* l_addr;
char* h_addr;
info their;
info message;

void main()
{
  // Initialize badge
  badge_setup();
  leds_set(0b111111);
  
  // Initialize IR
  ir_start();
  pause(200);
  clear();
  leds_set(0b000000);
  
  memset(h_addr, 0, 7);
  memset(l_addr, 0, 8);
  
  // Set username
  do
  {
    print("Enter new username: ");
    getStr(h_addr, 6);
    l_addr = humanToLogicalLookup(h_addr);
    if (strcmp(l_addr, "000.000") == 0) {
      print("Name not found, try again.\n");
    }      
  } while(strcmp(l_addr, "000.000") == 0);   
    
  while(1)
  {
    memset(&their, 0, sizeof(info));
    memset(&message, 0, sizeof(info));
    if (check_inbox() == 1)
    {
      message_get(&their);
      if (strcmp(their.name, l_addr) == 0)
      {
        clear();
        char_size(SMALL);
        cursor(2, 1);
        display("GOT MESSAGE!");
        cursor(0, 3);
        display(their.email);
        cursor(0, 6);
        display("OSH to continue.");
        while(pad(6) != 1);
        clear();
      }
      rgb(L, OFF);
      rgb(R, OFF);
    }      
    char_size(SMALL);
    cursor(3, 1);
    display("ID: ");
    cursor(7, 1);
    display(h_addr);
    char_size(BIG);
    cursor(0, 1);
    display("Waiting.");
    print("Enter recipient: ");
    getStr(text, 6);
    strcpy(message.name, humanToLogicalLookup(text));
    print("Enter instant message: ");
    getStr(text, 15);
    strcpy(message.email, text);
    clear();
    char_size(SMALL);
    cursor(3, 1);
    display("Sending...");
    cursor(0, 2);
    display(text);
    for (int i = 0; i < ir_attempts; i++)
    {
      rgb(L, BLUE);
      rgb(R, BLUE);
      ir_send(&message);
      rgb(L, OFF);
      rgb(R, OFF);
      pause(100);
    }      
    cursor(6, 4);
    display("DONE");
    pause(3000);
    clear();
  }    
}  