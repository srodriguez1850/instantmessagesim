#include "simpletools.h"
#include "badgealpha.h"
#include "humanlogical.h"

int ir_attempts = 1;
char cmd[1];

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
  
  // Initialize address memory
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
    displayEndpoint();
    print("Enter recipient: ");
    getStr(text, 6);
    strcpy(message.name, humanToLogicalLookup(text));
    print("Enter instant message: ");
    getStr(text, 62);
    strcpy(message.email, h_addr);
    strcat(message.email, ": ");
    strcat(message.email, text);
    strcat(message.email, "\0");
    clear();
    char_size(SMALL);
    cursor(3, 3);
    display("Sending...");
    for (int i = 0; i < ir_attempts; i++)
    {
      rgb(L, BLUE);
      rgb(R, BLUE);
      ir_send(&message);
      rgb(L, OFF);
      rgb(R, OFF);
      pause(100);
    }      
    cursor(6, 5);
    display("DONE");
    print("Message sent!\n");
    pause(500);
    clear();
    int done = 0;
    while (done == 0)
    {
      displayEndpoint();
      print("[S]end message / [R]esend / [C]heck inbox\n");
      getStr(cmd, 1);
      
      if (strcmp(cmd, "S") == 0 || strcmp(cmd, "s") == 0) {
        print("\n");
        done = 1;
      }
      else if (strcmp(cmd, "R") == 0 || strcmp(cmd, "r") == 0) {
        print(" -- Resending the last message...\n");
        clear();
        char_size(SMALL);
        cursor(3, 3);
        display("Sending...");
        for (int i = 0; i < ir_attempts; i++)
        {
          rgb(L, BLUE);
          rgb(R, BLUE);
          ir_send(&message);
          rgb(L, OFF);
          rgb(R, OFF);
          pause(100);
        }
        cursor(6, 5);
        display("DONE");
        pause(500);
        clear();
      }
      else if (strcmp(cmd, "C") == 0 || strcmp(cmd, "c") == 0) {
        print(" -- Checking inbox...\n");
        if (check_inbox() == 1)
        {
          message_get(&their);
          if (strcmp(their.name, l_addr) == 0)
          {
            clear();
            char_size(SMALL);
            cursor(2, 4);
            display("GOT MESSAGE!");
            print(their.email);
            print("\n");
            pause(1000);
            clear();
          }
          rgb(L, OFF);
          rgb(R, OFF);
        }
        else
        {
          clear();
          char_size(SMALL);
          cursor(2, 4);
          display("NO MESSAGES!");
          print("No messages found.\n");
          pause(1000);
          clear();
        }          
      }      
      else {
        print("\nCommand not recognized; try again\n");
      }
    }      
    clear();
  }    
}

void displayEndpoint()
{
  char_size(SMALL);
  cursor(3, 1);
  display("ID: ");
  cursor(7, 1);
  display(h_addr);
  char_size(BIG);
  cursor(0, 1);
  display("ENDPOINT");
}  