//
// automatically generated by spin2cpp v1.93 on Tue Aug 11 09:49:47 2015
// spin2cpp --ccode --main demo.spin 
//

//   io control
// =================================================================================================
//
//   File....... touch.spin
//   Purpose.... Touchpad reader for Parallax boards (Quickstart, DC22 badge, eBadge)
//   Author..... Jon "JonnyMac" McPhalen
//               Copyright (C) 2015 Jon McPhalen
//               -- see below for terms of use
//   E-mail..... jon@jonmcphalen.com
//   Started....
//   Updated.... 07 JUL 2015
//
// =================================================================================================
#include <propeller.h>
//#include "jm_touchpads.h"
#include "badgealpha.h"
#include "simpletools.h"

#ifdef __GNUC__
#define INLINE__ static inline
//define PostEffect__(X, Y) __extension__({ int32_t tmp__ = (X); (X) = (Y); tmp__; })
#else
#define INLINE__ static
static int32_t tmp__;
#define PostEffect__(X, Y) (tmp__ = (X), (X) = (Y), tmp__)
#define waitcnt(n) _waitcnt(n)
#define coginit(id, code, par) _coginit((unsigned)(par)>>2, (unsigned)(code)>>2, id)
#define cognew(code, par) coginit(0x8, (code), (par))
#define cogstop(i) _cogstop(i)
#endif

static touch badgeTouch;
static touch *self;
unsigned char TPPins[7];

int32_t touch_start(int32_t count, unsigned char *p_pins, int32_t dms)
{
  self = &badgeTouch;
  int32_t _parm__0000[4];
  _parm__0000[0] = count;
  _parm__0000[1] = (uint32_t) p_pins;
  _parm__0000[2] = dms;
  // Setup object for input of count pins
  // -- count is # pins to scan
  // -- p_pins is a pointer to a list of pins (byte array)
  //    * pins in list are arranged MSB to LSB
  // -- ms is the discharge timing in milliseconds
  // copy parameters
  memmove( (void *)&self->pincount, (void *)&_parm__0000[0], 4*(3));
  // build mask of input pins
  self->pinsmask = 0;
  {
    int32_t _limit__0024 = (self->pincount - 1);
    int32_t _step__0025 = 1;
    _parm__0000[3] = 0;
    if (_parm__0000[3] >= _limit__0024) _step__0025 = -_step__0025;
    do {
      self->pinsmask = self->pinsmask | (1 << ((uint8_t *)self->p_pinslist)[((self->pincount - 1) - _parm__0000[3])]);
      _parm__0000[3] = _parm__0000[3] + _step__0025;
    } while (((_step__0025 > 0) && (_parm__0000[3] <= _limit__0024)) || ((_step__0025 < 0) && (_parm__0000[3] >= _limit__0024)));
  }
  return 0;
}

int pad( int pad )
{
  char *addr = (char *) self->p_pinslist;
  int pin = addr[6-pad];
  int ctr = 0;
  for(int i = 0; i < 5; i++)
  {
    high(pin);
    pause(1);
    input(pin);
    pause(5);
    int pb = input(pin);
    if(pb) ctr++;
    low(pin);
    pause(1);
  }
  return !(ctr == 5);
}


int pads_get(void)
{
  int pb = 0;
  int mask = self->pinsmask;
  for(int i = 0; i < 5; i++)
  {
    //high(pin);
    OUTA |= mask;
    DIRA |= mask;
    pause(1);
    //input(pin);
    DIRA &= (~mask);
    pause(5);
    //int pb = input(pin);
    pb |= ~INA;
    //low(pin);
    OUTA &= (~mask);
    DIRA |= mask;
    pause(1);
  }
  char *addr = (char *) self->p_pinslist;
  int pads = 0, pin;
  for(int i = 0; i < 7; i++)
  {
    pads <<= 1; 
    pin = addr[i];
    int bit = (pb >> pin) & 1;
    pads |= bit;
  }    
  return pads;
}



/* From port
int32_t pads_get(void)
{
  int32_t	work, pads, idx;
  // UPDATED 06 JUL 2015
  // hold 1ms
  // Reads and returns state of touch pad inputs
  // charge pads
  OUTA = OUTA | self->pinsmask;
  DIRA = DIRA | self->pinsmask;
  // hold 1ms
  waitcnt((CNT + (CLKFREQ / 1000)));
  // float pads
  DIRA = DIRA & (~self->pinsmask);
  // allow discharge through finger 
  waitcnt((CNT + ((CLKFREQ / 1000) * self->disch)));
  // capture pads (touched = "1")
  work = (~INA) & self->pinsmask;
  // clear result
  pads = 0;
  {
    int32_t _limit__0026 = (self->pincount - 1);
    int32_t _step__0027 = 1;
    idx = 0;
    if (idx >= _limit__0026) _step__0027 = -_step__0027;
    do {
      // loop through all pins
      if (work & (1 << ((uint8_t *)self->p_pinslist)[((self->pincount - 1) - idx)])) {
        // this pin active?
        //  yes, set associated bit
        pads = pads | (1 << idx);
      }
      idx = idx + _step__0027;
    } while (((_step__0027 > 0) && (idx <= _limit__0026)) || ((_step__0027 < 0) && (idx >= _limit__0026)));
  }
  return pads;
}
*/
/* 

  Copyright (C) 2015 Jon McPhalen

  Terms of Use: MIT License

  Permission is hereby granted, free of charge, to any person obtaining a copy of this
  software and associated documentation files (the "Software"), to deal in the Software
  without restriction, including without limitation the rights to use, copy, modify,
  merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
  permit persons to whom the Software is furnished to do so, subject to the following
  conditions:

  The above copyright notice and this permission notice shall be included in all copies
  or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
  INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
  PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
  HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
  CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
  OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

 */
