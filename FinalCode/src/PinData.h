#ifndef _PIN_DATA_H_
#define _PIN_DATA_H_

/* Pin Output looking from front
 *   5V   A1        M11  GND
 *   D7   A2   M15  M12  M9
 *   SCL  A3   M16  M13  M8
 *   SDA  A4   A5   M14  M10
 */


/* New Pin Output Looking from front
 *  5V
 *
 *
 * 
 */

// ------ Direct Particle Connections -------
// MPU Connections
const int P_INT = D7;

// Multiplexer connections
const int P_MULP_S3 = D5;
const int P_MULP_S2 = D4;
const int P_MULP_S1 = D3;
const int P_MULP_S0 = D2;
const int P_MULP_ENABLE = D6;
const int P_MULP_SIGNAL = A0;

// ------ Multiplexer Connections ------

const int M_THUMB = 8;
const int M_POINTER = 7;
const int M_MIDDLE = 9;
const int M_RING = 12;
const int M_PINKY = 13;

#endif