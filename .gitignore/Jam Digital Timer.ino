//jam_digital.c
//program jam digital menggunakan ATMega328 board arduino uno
//23 Februari 2018
//Muhammad Fithratur Rahman 13215005
//Sayyid Irsyadul Ibad 13215005

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

int N;
int A,B,C,D;
int portd_1_int, portd_2_int, portd_3_int, portd_4_int;
int portb_1, portb_2, portb_3, portb_4, portd_1, portd_2, portd_3, portd_4;
int jam_puluhan;
int jam_satuan;
int menit_puluhan;
int menit_satuan;
int detik_puluhan;
int detik_satuan;

int main () { 

  // setting mode timer dan nilai awalnya
  TCCR1B |= (1<<CS02|(1<<CS00)); //inisialisasi timer 0
  TIMSK1 |=(1<<TOIE0);
  TCNT1 = 0x48E5; //initial of timer 0
  // setting mode interupsi
  EIMSK = 0x01;
  EIFR = 0x01;
  EICRA = 0x02;
  // setting port yang akan digunakan sebagai i/o
  DDRB = 0xFC;
  DDRD = 0xFF;
  DDRC = 0x00;
  PORTC = 0xFF ;
  // enable global interrupt
  sei ();
  N = 0;

  portd_1 = 0b00000001;
  portd_2 = 0b00000001;
  portd_3 = 0b00000001;
  portd_4 = 0b00000001;
  portb_1 = 0b00100011;
  portb_2 = 0b00010011;
  portb_3 = 0b00001011;
  portb_4 = 0b00000111;
  
 while (1) {
  _delay_ms (1);
  PORTD = portd_1;
  PORTB = portb_1;
  _delay_ms (1);
  PORTD = portd_2;
  PORTB = portb_2;
  _delay_ms (1);
  PORTD = portd_3;
  PORTB = portb_3;
  _delay_ms (1);
  PORTD = portd_4;
  PORTB = portb_4;

  if (not(PINC &= (1<<0))) {
  portd_4_int = converter(portd_4);
  D = portd_4_int + 1;
    if (D >2) {
      D=0;
    }
  portd_4 = DtoNB (D);
  _delay_ms (200);
 }
 else if (not(PINC &= (1<<1))) {
  portd_3_int = converter(portd_3);
  C = portd_3_int + 1;
  if (D==2) {
    if (C>3) {
      C=0;
    }
  }
  portd_3 = DtoNB (C);
  
  _delay_ms (200);
 }
 else if (not(PINC &= (1<<2))) {
  portd_2_int = converter(portd_2);
  B = portd_2_int + 1;
    if (B>5) {
      B =0;
    }
  portd_2 = DtoNB (B);
  _delay_ms (200);
 }
 else if (not(PINC &= (1<<3))) {
  portd_1_int = converter(portd_1);
  A = portd_1_int + 1;
  portd_1 = DtoNB (A);
  _delay_ms (200);
 }
 else {
  _delay_ms (1);
 }
 }


  return 0;
}

 ISR(TIMER1_OVF_vect) {
  N++;
  if (N==20) {
  portd_1_int = converter(portd_1);
  portd_2_int = converter(portd_2);
  portd_3_int = converter(portd_3);
  portd_4_int = converter(portd_4);
  menit_satuan = portd_1_int + 1;
  menit_puluhan = portd_2_int;
  jam_satuan = portd_3_int;
  jam_puluhan = portd_4_int;
   
  //--------------------------------------------------
  if (detik_satuan == 10) {
    if (detik_puluhan == 5) {
      detik_puluhan = 0;
      menit_satuan += 1;
    }
    else {
      detik_puluhan += 1;
    }
    detik_satuan = 0;
  }

  if (menit_satuan == 10) {
    if (menit_puluhan == 5) {
      menit_puluhan = 0;
      jam_satuan += 1;
    }
    else {
      menit_puluhan += 1;
    }
    menit_satuan = 0;
  }

  if (jam_satuan == 10) {
    jam_puluhan += 1;
    jam_satuan = 0;
  }

  if ((jam_satuan == 4) && (jam_puluhan == 2)) {
    jam_puluhan = 0;
    jam_satuan = 0;
  } 
  //--------------------------------------------------------
  portd_1 = DtoNB (menit_satuan);
  portd_2 = DtoNB (menit_puluhan);
  portd_3 = DtoNB (jam_satuan);
  portd_4 = DtoNB (jam_puluhan);
  N = 0;
  }
  TCNT1 = 0x48E5;
 }

// fungsi converter hexadecimal to decimal
int converter (int toconvert) {

  int converted;
  if (toconvert == 0b10011011) {
    converted = 1;
  }
  else if (toconvert == 0b00100010) {
    converted = 2;
  }
  else if (toconvert == 0b00000001) {
    converted = 0;
  }
  else if (toconvert == 0b00001010) {
    converted = 3;
  }
  else if (toconvert == 0b10011000) {
    converted = 4;
  }
  else if (toconvert == 0b01001000) {
    converted = 5;
  }
  else if (toconvert == 0b01000000) {
    converted = 6;
  }
  else if (toconvert == 0b00011011) {
    converted = 7;
  }
  else if (toconvert == 0b00000000) {
    converted = 8;
  }
  else if (toconvert == 0b00001000) {
    converted = 9;
  }
  else {
    converted = 10;
  }
  return (converted);
}

// fungsi converter decimal to hexadecimal
int DtoNB(int angka)
  {
    int x;
    if (angka==1)
      x= 0b10011011;
    else if (angka==2)
      x=0b00100010;
    else if (angka==3)
      x=0b00001010;
    else if (angka==4)
      x=0b10011000;
    else if (angka==5)
      x=0b01001000;
    else if (angka==6)
      x=0b01000000;
    else if (angka==7)
      x=0b00011011;
    else if (angka==8)
      x=0b00000000;
    else if (angka==9)
      x=0b00001000;
    else if (angka ==0)
      x=0b00000001;
      else 
      x=0b00000001;
    return x;
  }
