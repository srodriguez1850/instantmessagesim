#include "simpletools.h"
#include "badgealpha.h"
#include "fdserial.h"

id_address = 65335;

char id[7];
info their;
info message;

char human_name[7];

char recipient[7];

char cmd[1];

void main()
{
  // Initialize badge
  badge_setup();
  
  // Initialize IR
  leds_set(0b111111);
  ir_start();
  pause(500);
  leds_set(0b000000);
  clear();
  
  // Pull ID from EEPROM
  ee_getStr(id, 7, id_address);
  
  ///THIS LINE WOULD REPLACE THE ONE ABOVE (if the ID is going to be our logical address);
  while ( switchAndLookupUser() != 1 );
    
  while(1)
  {
    if (check_inbox() == 1)
    {
      message_get(&their);
      if (strcmp(their.name, id) == 0)
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
    display(id);
    char_size(BIG);
    cursor(0, 1);
    display("Waiting.");
    print("SEND an 'INSTANT' MESSAGE, ");
    print(human_name);
    print("\n");
    int ok = 0;
    while (ok == 0) {
      print("Enter recipient: ");
      getStr(text, 6);
      ok = validateAndStoreRecipientAddr( text );
    }      
    //strcpy(message.name, text);
    strcpy(message.name, recipient);
    print("Enter instant message: ");
    getStr(text, 140);
    strcpy(message.email, text);
    clear();
    char_size(SMALL);
    cursor(3, 1);
    display("Sending...");
    cursor(0, 2);
    display(text);
    led(4, ON); 
    led(1, ON);
    rgb(L, BLUE);
    rgb(R, BLUE);
    ir_send(&message);
    rgb(L, OFF);
    rgb(R, OFF);
    cursor(6, 4);
    display("DONE");
    led(4, OFF);
    led(1, OFF);
    pause(500);
    clear();
    int done = 0;
    while (done == 0) {  
      print("[C]ontinue, [R]esend last message, [S]witch user\n");
      getStr(cmd, 1);
      
      if (strcmp(cmd,"R") == 0 || strcmp(cmd,"r") == 0) {
        print(" -- Resending the last message...\n");
        done = 0;
      } else if (strcmp(cmd,"S") == 0 || strcmp(cmd,"s") == 0) {
        print(" -- Switching user...\n");
        done = switchAndLookupUser();
      } else if (strcmp(cmd,"C") == 0 || strcmp(cmd,"c") == 0) {
        print("\n");
        done = 1;
      } else {
        print("\nCommand not recognized; try again\n");
      }        
    }          
  }    
}  


int switchAndLookupUser() {
  char newname[6]; 
  int code = 0;
  print("Enter new user name: ");
  getStr(newname,6);
  
  if ( strcmp(newname,"corey") == 0 ) {
     strcpy(id, "100.01");
     code = 1;
  } else if ( strcmp(newname,"foo") == 0 ) {
     strcpy(id, "100.10");
     code = 1;
  } else if ( strcmp(newname,"bar") ==  0 ) {
     strcpy(id, "101.01");
     code = 1;
  } else {
     code = 0;
     print("Name not found; try again\n");
  }
  
  if ( code == 1 ) {
    strcpy(human_name, newname);
  }    
  return code;
} 


int validateAndStoreRecipientAddr( char* recname ) {
  
  if ( strcmp(recname, human_name) == 0) {
   print("You can't send a message to yourself! Try again.\n");
   return 0; 
  }    
  
  if ( strcmp(recname,"corey") == 0 ) {
     strcpy(recipient, "100.01");
     return 1;
  }
  if ( strcmp(recname,"foo") == 0 ) {
     strcpy(recipient, "100.10");
     return 1;
  } 
  if ( strcmp(recname,"bar") ==  0 ) {
     strcpy(recipient, "101.01");
     return  1;
  } 
  
  
  print("Name not found; try again\n");
  return 0;
  
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
int heldatstart = 0;

void screen_img180();
void screen_img(char *imgaddr);

void main()
{
  // Initialize badge and serial connection
  badge_setup();
  //simpleterm_close();
  
  // Pull ID from EEPROM
  leds_set(0b111111);
  char id[7];
  ee_getStr(id, 7, id_address);
  strcpy(my.name, id);
  strcpy(my_init.name, id);
  strcpy(my_resp.name, id);
  
  pause(200);
  char_size(SMALL);
  cursor(2, 3);
  display("Waiting for");
  cursor(4, 5);
  display("a MESSAGE");
  leds_set(0b000000);
  
  leds_set(0b100001);
  ir_start();
  pause(500);
  clear();
  
  while(1)
  {
    
      
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
      if (!strcmp(their.email, "RESP"))
      {
        memset(&last, 0, sizeof(info));
        last = their;
        ee_save(&their);
        cursor(2, 4);
        display("Acknowledged!");
        cursor(0, 7);
        display("OSH to Continue.");
        rgb(L, OFF);
        while(pad(6) != 1);
        rgb(R, OFF);
        clear();
      }
      else
      {
        rgb(L, OFF);
        rgb(R, OFF);
      }        
    //}
    //else 
    if(check_inbox() == 1)
    {
      clear();
      message_get(&their);
      if (!strcmp(their.email, "INIT"))
      {
        memset(&last, 0, sizeof(info));
        last = their;
        ee_save(&their);
        cursor(2, 1);
        display("INTERACTION!");
        rgb(L, BLUE);
        ir_send(&my_resp);
        rgb(L, OFF);
        cursor(3, 4);
        display("Should receive");
        cursor(0, 7);
        display("OSH to Continue.");
        rgb(L, OFF);
        while(pad(6) != 1);
        rgb(R, OFF);
        clear();
      }           
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