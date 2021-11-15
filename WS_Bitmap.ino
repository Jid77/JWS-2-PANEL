// animasi GAMBAR MASJID = 494kb

void anim_masjid(int DrawAdd)
{
  // check RunSelector
  if (!dwDo(DrawAdd)) return;

  static uint8_t    y;
  static uint8_t    s; // 0=in, 1=out
  static uint16_t   lsRn;
  uint16_t          Tmr = millis();

  if ((Tmr - lsRn) > 50)
  {
    if (s == 0 and y < 16) {
      lsRn = Tmr;
      y++;
    }
    if (s == 1 and y > 0 ) {
      lsRn = Tmr;
      y--;
    }
  }

  if ((Tmr - lsRn) > 3000 and y == 16) {
    s = 1;
  }

  if (y == 16) {
    Disp.drawRect(1, 1, 62, 14, 1); //24kb
  }

  if (y == 0 and s == 1) {
    dwDone(DrawAdd);
    s = 0;
  }

  masjida(16 - y);
  masjidb(16 - y);
  //lapadzMuhammad(y - 16);
  //lapadzAlloh((32*2) - y); //(32*2) = 2 panel
}

//====================
void masjida(uint16_t y) {
  static const uint8_t dall[] PROGMEM = {
    16, 16,
    B00100000,  B00000001,
    B00100000,  B00000111,
    B01110000,  B00011111,
    B11111000,  B00111111,
    B01110000,  B01111111,
    B00000000,  B01111111,
    B11111000,  B00111111,
    B00000000,  B00011111,
    B01010111,  B11111111,
    B01010000,  B00000000,
    B01110111,  B11111111,
    B01110111,  B00111110,
    B01110110,  B00011100,
    B01110110,  B00011100,
    B01110110,  B00011100,
    B11111111,  B11111111
  };
  Disp.drawBitmap((16 * 1), y, dall);
  DoSwap = true;
}

void masjidb(uint16_t y) {
  static const uint8_t eall[] PROGMEM = {
    16, 16,
    B10000000,  B00000100,
    B11100000,  B00000100,
    B11111000,  B00001110,
    B11111100,  B00011111,
    B11111110,  B00001110,
    B11111110,  B00000000,
    B11111100,  B00011111,
    B11111000,  B00000000,
    B11111111,  B11101010,
    B00000000,  B00001010,
    B11111111,  B11101110,
    B01111100,  B11101110,
    B00111000,  B01101110,
    B00111000,  B01101110,
    B00111000,  B01101110,
    B11111111,  B11111111
  };
  Disp.drawBitmap((16 * 2), y, eall); //(16*2) = 2 panel
  DoSwap = true;
}

/*/ animasi lapadz = 494kb
  void anim_lapadz(int DrawAdd)
  {
  // check RunSelector
  if (!dwDo(DrawAdd)) return;

  static uint8_t    y;
  static uint8_t    s; // 0=in, 1=out
  static uint16_t   lsRn;
  uint16_t          Tmr = millis();

  if ((Tmr - lsRn) > 50)
  {
    if (s == 0 and y < 16) {
      lsRn = Tmr;
      y++;
    }
    if (s == 1 and y > 0 ) {
      lsRn = Tmr;
      y--;
    }
  }
  if ((Tmr - lsRn) > 3000 and y == 16) {
    s = 1;
  }
  if (y == 16){
  //Disp.drawRect(1,2,62,13);
  }
  if (y == 0 and s == 1) {
    dwDone(DrawAdd);
    s = 0;
  }
  lapadzMuhammad(y - 16);
  lapadzAlloh(32 - y);
  } */

void lapadzMuhammad(uint16_t x) {
  static const uint8_t lapadzMuhammad[] PROGMEM = {
    16, 16,
    B00000000, B00000000,
    B01100110, B01111110,
    B01100110, B01111110,
    B01100110, B01100110,
    B01100110, B01100110,
    B01111110, B01111110,
    B01111110, B01111110,
    B01100000, B01100000,
    B01100000, B01100000,
    B01111110, B01111110,
    B01111110, B01111110,
    B01100110, B00000110,
    B01100110, B00000110,
    B01111111, B11111110,
    B01111111, B11111110,
    B00000000, B00000000
  };
  Disp.drawBitmap(x, 0, lapadzMuhammad);
  DoSwap = true;
}

void lapadzAlloh(uint16_t x) {
  static const uint8_t lapadzAlloh[] PROGMEM = {
    16, 16,
    B00000000, B00000000,
    B01111111, B11111110,
    B01111111, B11111110,
    B00000000, B00000000,
    B00000000, B00000000,
    B01111110, B01100110,
    B01111110, B01100110,
    B00000110, B01100110,
    B00000110, B01100110,
    B01111110, B01100110,
    B01111110, B01100110,
    B01100110, B01100110,
    B01100110, B01100110,
    B01111111, B11111110,
    B01111111, B11111110,
    B00000000, B00000000
  };
  Disp.drawBitmap(x, 0, lapadzAlloh);
  DoSwap = true;
}

/*
  void nama(uint16_t y) {
  fType(2);
  dwCtr(33, y + 0, "MASJID");
  fType(2);
  dwCtr(33, y + 9, "AL-ISLAM");
  DoSwap = true;
  }*/
