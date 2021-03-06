//
// automatically generated by spin2cpp v1.93 on Tue Aug 11 09:49:47 2015
// spin2cpp --ccode --main demo.spin 
//

//   eeprom access 
// =================================================================================================
//
//   File....... tilt.spin
//   Purpose....
//   Author..... Jon "JonnyMac" McPhalen
//               Copyright (C) 2015 Jon McPhalen
//               -- see below for terms of use
//   E-mail..... jon@jonmcphalen.com
//   Started....
//   Updated.... 02 JUL 2015
//
// =================================================================================================
#include <propeller.h>
#include "badgealpha.h"
//#include "jm_mma7660fc.h"

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

static tilt badgeTilt;
static tilt *self;

static  int32_t tilt_raw_to_gforce( int32_t raw);

// Spin I2C driver
int32_t tilt_start(int32_t sclpin, int32_t sdapin)
{
  self = &badgeTilt;
  // Connect MMA7660 to I2C buss
  jm_i2c_setupx(&self->i2c, sclpin, sdapin);
  // stand-by
  tilt_write_reg(MODE, 0);
  // no interrupts
  tilt_write_reg(INTSU, 0);
  // 120 sps             
  tilt_write_reg(SR, 0);
  // active, interrupt pin active-high
  tilt_write_reg(MODE, 193);
  return 0;
}

int32_t tilt_present(void)
{
  // Returns true if device detected
  return jm_i2c_present(&self->i2c, MMA7660_WR);
}

void tilt_get(int *x, int *y, int *z)
{
  *x = tilt_getX();
  *y = tilt_getY();
  *z = tilt_getZ();
}  

int32_t tilt_getY(void)
{
  // Returns X axis as signed long (1/100th-gs)  
  return -tilt_raw_to_gforce(tilt_read_axis(XOUT));
}

int32_t tilt_getX(void)
{
  // Returns Y axis as signed long (1/100th-gs)       
  return tilt_raw_to_gforce(tilt_read_axis(YOUT));
}

int32_t tilt_getZ(void)
{
  // Returns Z axis as signed long (1/100th-gs)        
  return tilt_raw_to_gforce(tilt_read_axis(ZOUT));
}

int32_t tilt_read_tilt(void)
{
  // Returns tilt register (8 bits)
  return tilt_read_axis(TILT);
}

int32_t tilt_read_axis(int32_t reg)
{
  int32_t	value;
  // Read specified axis or tilt register
  // -- returns signed long (1/100th-gs)     
  if ((reg < XOUT) || (reg > TILT)) {
    return 0;
  }
  while (1) {
    // read axis or tilt
    value = tilt_read_reg(reg);
    if (!(value & ALERT_BIT)) {
      // reading okay to use
      // if no alert bit
      break;
    }
  }
  return value;
}

int32_t tilt_read_all(int32_t p_axes)
{
  int32_t _local__0011[1];
  // Read all axes and tilt register from MMA7660
  // -- p_axes is pointer to array of four longs (x, y, z, tilt)
  // -- writes axis values as signed longs (1/100th-gs) to array at p_axes  
  while (1) {
    jm_i2c_start(&self->i2c);
    jm_i2c_write(&self->i2c, MMA7660_WR);
    // start at X axis
    jm_i2c_write(&self->i2c, XOUT);
    // restart
    jm_i2c_start(&self->i2c);
    // read axis registers
    jm_i2c_write(&self->i2c, MMA7660_RD);
    ((uint8_t *)(int32_t)(&_local__0011[0]))[XOUT] = jm_i2c_read(&self->i2c, ACK);
    ((uint8_t *)(int32_t)(&_local__0011[0]))[YOUT] = jm_i2c_read(&self->i2c, ACK);
    ((uint8_t *)(int32_t)(&_local__0011[0]))[ZOUT] = jm_i2c_read(&self->i2c, ACK);
    ((uint8_t *)(int32_t)(&_local__0011[0]))[TILT] = jm_i2c_read(&self->i2c, NAK);
    jm_i2c_stop(&self->i2c);
    if (!(_local__0011[0] & ALERT_XYZT)) {
      //  readings are good
      // if no alert flags
      break;
    }
  }
  // convert results
  ((int32_t *)p_axes)[XOUT] = tilt_raw_to_gforce(((uint8_t *)(int32_t)(&_local__0011[0]))[XOUT]);
  ((int32_t *)p_axes)[YOUT] = tilt_raw_to_gforce(((uint8_t *)(int32_t)(&_local__0011[0]))[YOUT]);
  ((int32_t *)p_axes)[ZOUT] = tilt_raw_to_gforce(((uint8_t *)(int32_t)(&_local__0011[0]))[ZOUT]);
  ((int32_t *)p_axes)[TILT] = ((uint8_t *)(int32_t)(&_local__0011[0]))[TILT];
  return 0;
}

int32_t tilt_write_reg(int32_t reg, int32_t value)
{
  // Write value to MMA7660 register
  jm_i2c_start(&self->i2c);
  jm_i2c_write(&self->i2c, MMA7660_WR);
  // set register address
  jm_i2c_write(&self->i2c, reg);
  // write value
  jm_i2c_write(&self->i2c, value);
  jm_i2c_stop(&self->i2c);
  return 0;
}

int32_t tilt_read_reg(int32_t reg)
{
  int32_t	value;
  // Read current value of MMA7660 register
  jm_i2c_start(&self->i2c);
  jm_i2c_write(&self->i2c, MMA7660_WR);
  // set register addres
  jm_i2c_write(&self->i2c, reg);
  // restart
  jm_i2c_start(&self->i2c);
  jm_i2c_write(&self->i2c, MMA7660_RD);
  // read value
  value = jm_i2c_read(&self->i2c, NAK);
  jm_i2c_stop(&self->i2c);
  return value;
}

static int32_t tilt_raw_to_gforce(int32_t raw)
{
  // raw * 4.69
  // Convert raw axis reading to signed long
  // -- result expressed in 1/100g
  // -- * 100 = 1.00g
  return ((((raw << 26) >> 26) * 469) / 100);
}

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
