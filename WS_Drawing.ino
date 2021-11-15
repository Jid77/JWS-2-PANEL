// =========================================
// Drawing Content Block====================
// =========================================
void drawToAzzan(int DrawAdd)  // Countdown adzan (5 menit)
{
  if (!dwDo(DrawAdd)) return;
  static uint16_t   lsRn;
  uint16_t          Tmr = millis();
  static int        ct;
  int               mnt, scd, cn_l ;
  char              locBuff[6];
  cn_l  = (5 * 60);                       // 5*60 jika 5 menit
  if ((Tmr - lsRn) > 1000 and ct <= cn_l)
  {
    lsRn = Tmr;
    mnt = floor((cn_l - ct) / 60);
    scd = (cn_l - ct) % 60;
    if (mnt > 0) {
      sprintf(locBuff, "%02d:%02d", mnt, scd);
    }
    else    {
      sprintf(locBuff, "%02d", scd);
    }
    fType(0);
    dwCtr(35, 0, "MENUJU");
    dwCtr(34, 8, "ADZAN");
    Disp.drawRect(0, 1, 32, 14, 1); //24kb
    fType(1);
    dwCtr(-31, 4, locBuff);
    //if (ct > (cn_l - 6)) Buzzer(1); // Buzzer off
    ct++;
    DoSwap = true;
  }
  if (ct > cn_l)
  {
    dwDone(DrawAdd);
    ct = 0;
   // Buzzer(0);
  }
}

void drawAzzan(int DrawAdd)
{
  // check RunSelector
  if (!dwDo(DrawAdd)) return;
  uint8_t           ct_limit = 120; //harus angka genap
  static uint8_t    ct;
  static uint16_t   lsRn;
  uint16_t          Tmr = millis();

  if ((Tmr - lsRn) > 500 and ct <= ct_limit)
  {
    lsRn = Tmr;
    bzr++;
    if (((ct % 2) == 0 && (bzr == 1)) ||
        ((ct % 2) == 0 && (bzr == 3)) ||
        ((ct % 2) == 0 && (bzr == 5))) {
      Buzzer(1);
    }
    if ((ct % 2) == 0)
    {
      Disp.drawRect(1, 1, 62, 14, 1); //24kb
      fType(0);
      dwCtr(0, 0, "ADZAN");
      fType(1);
      if (jumat) {
        dwCtr(0, 8, sholatN(8));
      }
      else      {
        dwCtr(0, 8, sholatN(SholatNow));
      }
    }
    else
    {
      Buzzer(0);
    }
    DoSwap = true;
    ct++;
  }
  if ((Tmr - lsRn) > 2000 and (ct > ct_limit))
  { dwDone(DrawAdd);
    ct = 0;
    bzr = 0;
    Buzzer(0);
  }
}

void drawIqomah(int DrawAdd)  // Countdown Iqomah (5 menit)
{
  // check RunSelector
  if (!dwDo(DrawAdd)) return;

  static uint16_t   lsRn;
  uint16_t          Tmr = millis();
  static int        ct;
  int               mnt, scd, cn_l ;
  char              locBuff[6];

  cn_l  = (Iqomah[SholatNow] * 60);
  //Disp.drawRect(1,2,62,13);
  if ((Tmr - lsRn) > 1000 and ct <= cn_l)
  {
    lsRn = Tmr;
    mnt = floor((cn_l - ct) / 60);
    scd = (cn_l - ct) % 60;
    if (mnt > 0) {
      sprintf(locBuff, "%02d:%02d", mnt, scd);
    }
    else    {
      sprintf(locBuff, "%02d", scd);
    }
    if ((ct % 2) == 0) {
      fType(0);
      dwCtr(0, 0, "MENUJU IQOMAH");
    }
    Disp.drawRect( 1, 11, 62, 12);
    fType(0);
    dwCtr(0, 8, locBuff);
    if (ct > (cn_l - 2)) Buzzer(1); // Buzzer on 1 second before Iqomah
    ct++;
    DoSwap = true;
  }
  if (ct > cn_l)
  {
    dwDone(DrawAdd);
    ct = 0;
    Buzzer(0);
  }
}

void drawSholat_S(int sNum, int c) // Box Sholah Time
{
  static uint16_t ss;  /////BERKEDIP
  uint16_t          Tmr = millis();
  uint16_t y;
  char  BuffJ[6];
  char  BuffM[6];
  sprintf(BuffJ, "%02d", now.hour());
  sprintf(BuffM, "%02d", now.minute());
  fType(3);
  Disp.drawText(0, y, BuffJ); //JAM
  Disp.drawText(17, y, BuffM); //MENIT
  if (Tmr - ss < 500 and y == 0) {
    Disp.drawFilledRect(14, 5, 15, 6);
    Disp.drawFilledRect(14, 8, 15, 9);
  }
  if (Tmr - ss > 1000) ss = Tmr;
  DoSwap = true;

  char  BuffTime[10];
  char  BuffShol[7];
  float   stime   = sholatT[sNum];
  uint8_t shour   = floor(stime);
  uint8_t sminute = floor((stime - (float)shour) * 60);
  uint8_t ssecond = floor((stime - (float)shour - (float)sminute / 60) * 3600);
  sprintf(BuffTime, "%02d:%02d", shour, sminute);
  Disp.drawRect(33 + 1, 8, 62, 8);
  fType(1); dwCtr(33, 0, sholatN(sNum));  //Nama waktu Sholat
  fType(0); dwCtr(33, 9, BuffTime);       //Jadwal Sholat
  DoSwap = true;
}

void drawSholat(int DrawAdd)
{
  // check RunSelector
  //    int DrawAdd = 0b0000000000000100;
  if (!dwDo(DrawAdd)) return;

  static uint8_t    x;
  static uint8_t    s; // 0=in, 1=out
  static uint8_t    sNum;
  static uint16_t   lsRn;
  uint16_t          Tmr = millis();
  uint8_t           c = 32;
  uint8_t           first_sNum = 0;
  int               DrawWd = DWidth - c;

  if ((Tmr - lsRn) > 20)
  {
    if (s == 0 and x < (DrawWd / 2)) {
      x++;
      lsRn = Tmr;
    }
    if (s == 1 and x > 0) {
      x--;
      lsRn = Tmr;
    }
  }

  if ((Tmr - lsRn) > 2000 and x == (DrawWd / 2)) {
    s = 1;
  }
  if (x == 0 and s == 1)
  {
    if (sNum < 7) {
      sNum++;
    }
    else
    {
      dwDone(DrawAdd);
      sNum = 0;
    }
    s = 0;
  }

  if (Prm.SI == 0) {
    first_sNum = 1;
  }
  else {
    first_sNum = 0;
  }
  if (Prm.SI == 0 and sNum == 0) {
    sNum = 1;
  }
  if (Prm.ST == 0 and sNum == 2) {
    sNum = 3;
  }
  if (Prm.SU == 0 and sNum == 3) {
    sNum = 4;
  }

  /*
    if (  (((sNum == first_sNum) and s == 0) or
         ((sNum == 7) and s == 1))
        and x <= 20) { //drawSmallTS(int(x/2));
    }
    else {//drawSmallTS(10);
    }*/

  drawSholat_S(sNum, c);
  Disp.drawFilledRect(c, 8, c + DrawWd / 2 - x, 8, 0);
  Disp.drawFilledRect(DrawWd / 2 + x + c, 8, 63, 8, 0);

  Disp.drawFilledRect(32, -2, 63, 7 - x,  0);
  Disp.drawFilledRect(32, 9 + x, 63, 16, 0);
}

void drawGreg_DS(uint16_t y)   //Draw Date
{
  char  Buff[20];
  sprintf(Buff, "%02d/%02d/%02d", now.day(), now.month(), now.year() - 2000);
  dwCtr(0, y - 2, Buff);
  DoSwap = true;
}

void drawSmallTS(int x)
{
  char BuffH[3];
  char BuffM[3];
  sprintf(BuffH, "%02d", now.hour());
  sprintf(BuffM, "%02d", now.minute());
  fType(0);
  Disp.drawText((x - 10) + 1, -1, BuffH);
  Disp.drawText((x - 10) + 1, 8, BuffM);
  DoSwap = true;
}

void drawGreg_TS(uint16_t y)   // Draw Time
{
  char  Buff[20];
  sprintf(Buff, "%02d:%02d:%02d", now.hour(), now.minute(), now.second());
  dwCtr(0, y, Buff);
  DoSwap = true;
}

void drawGreg_cil(uint16_t y)   // Draw Time
{
  char  Buff[20];
  sprintf(Buff, "%02d:%02d:%02d", now.hour(), now.minute(), now.second());
  dwCtr(0, y, Buff);
  DoSwap = true;
}

void Jam_GD(uint16_t y)   // Draw Time Depan
{
  static uint16_t ss;  /////BERKEDIP
  uint16_t          Tmr = millis();
  char  BuffJ[6];
  char  BuffM[6];
  sprintf(BuffJ, "%02d", now.hour());
  sprintf(BuffM, "%02d", now.minute());
  fType(3);
  Disp.drawText(17, y, BuffJ); //JAM
  Disp.drawText((16 + 18), y, BuffM); //MENITDETIK
  if (Tmr - ss < 500) {
    Disp.drawFilledRect(31, (y + 5), 32, (y + 6));
    Disp.drawFilledRect(31, (y + 8), 32, (y + 9));
  }
  if (Tmr - ss > 1000) ss = Tmr;
  DoSwap = true;
  
  /*static uint16_t ss;  /////BERKEDIP
  uint16_t          Tmr = millis();
  char  BuffJ[6];
  char  BuffM[6];
  char  BuffD[6];
  sprintf(BuffJ, "%02d", now.hour());
  sprintf(BuffM, "%02d", now.minute());
  sprintf(BuffD, "%02d", now.second());
  fType(3);
  Disp.drawText((x + 0), 0, BuffJ); //JAM
  fType(1);
  Disp.drawText((x + 19), 0, BuffM); //MENIT
  fType(0);
  Disp.drawText((x + 20), 0 + 9, BuffD); //DETIK
  if (Tmr - ss < 1000) {
    Disp.drawFilledRect((x + 15), 5, (x + 16), 6);
    Disp.drawFilledRect((x + 15), 8, (x + 16), 9);
  }
  if (Tmr - ss > 2000) ss = Tmr;
  
  DoSwap = true;*/
}

void anim_DT(int DrawAdd)
{
  // check RunSelector
  if (!dwDo(DrawAdd)) return;

  static uint8_t    y;
  static uint8_t    s; // 0=in, 1=out
  static uint16_t   lsRn;
  uint16_t          Tmr = millis();

  if ((Tmr - lsRn) > 100)
  {
    if (s == 0 and y < 17) {
      lsRn = Tmr;
      y++;
    }
    if (s == 1 and y > 0) {
      lsRn = Tmr;
      y--;
    }
  }
  if ((Tmr - lsRn) > 10000 and y == 17) {
    s = 1;
  }
  if (y == 7)
  {
    //Disp.drawRect(1,2,62,13);
  }
  if (y == 0 and s == 1) {
    dwDone(DrawAdd);
    s = 0;
  }
  fType(1);
  drawGreg_cil(y - 16);
}

void anim_JG_lapaz(int DrawAdd)
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
    if (s == 1 and y > 0) {
      lsRn = Tmr;
      y--;
    }
  }
  if ((Tmr - lsRn) > 10000 and y == 16) {
    s = 1;
  }
  if (y == 0 and s == 1) {
    dwDone(DrawAdd);
    s = 0;
  }

  Jam_GD((-16) + y);
  lapadzMuhammad((-16) + y);
  lapadzAlloh(64 - y);
}

void dwMrq(const char* msg, int Speed, int dDT, int DrawAdd)
{
  // check RunSelector
  static uint16_t   x;
  if (!dwDo(DrawAdd)) return;
  if (reset_x != 0) {
    x = 0;
    reset_x = 0;
  }

  fType(2); //font CandooSSK12

  static uint16_t   lsRn;
  int fullScroll = Disp.textWidth(msg) + DWidth;
  uint16_t          Tmr = millis();
  if ((Tmr - lsRn) > Speed)
  { lsRn = Tmr;
    if (x < fullScroll) {
      ++x;
    }
    else {
      dwDone(DrawAdd);
      x = 0;
      return;
    }

    if (dDT == 1)                         // jam bawah - runteks atas
    {
      fType(1);                             //font SystemFont5x7
      Disp.drawText(DWidth - x, 0, msg);    //Running text diatas
      fType(0);                             //font Font4x6
      if (x <= 8) {
        drawGreg_TS(16 - x);                // jam bawah - naik
      }
      else if (x >= (fullScroll - 6))   {
        drawGreg_TS(16 - (fullScroll - x)); // jam bawah - turun
      }
      else {
        Disp.drawRect(1, 8, 62, 14);        //Bingkai tengah jam
        drawGreg_TS(9);                     //Jam dibawah diam
      }
    }

    else if (dDT == 2)                      // jam atas - runteks bawah
    {
      fType(1);                             //font SystemFont5x7
      Disp.drawText(DWidth - x, 9 , msg);   //Running text dibawah
      fType(0);                             //font Font4x6
      if (x <= 8) {
        drawGreg_TS(x - 6);                 // jam bawah - turun
      }

      else if (x >= (fullScroll - 6))   {
        drawGreg_TS((fullScroll - x) - 6);   // jam bawah - naik
      }
      else {
        Disp.drawRect(1, 7, 62, 1);          //Bingkai tengah jam
        drawGreg_TS(-1);
      }
    }
    else { //Runteks Besar
      Disp.drawRect(-1, 0, 64, 15);         //Tepian AtasBawah
      Disp.drawText(DWidth - x, 3, msg);
    }
    DoSwap = true;
  }
}

void blinkBlock(int DrawAdd)
{
  // check RunSelector
  if (!dwDo(DrawAdd)) return;

  static uint16_t   lsRn;
  static uint16_t   ct, ct_l;
  uint16_t          Tmr = millis();
  int               mnt, scd;
  char              locBuff[6];

  if (jumat)       {
    ct_l = Prm.JM * 60;
  }
  else            {
    ct_l = Prm.SO * 60;
  }


  if ((Tmr - lsRn) > 1000)
  { lsRn = Tmr;

    //Disp.drawChar(1, 1 , ct);
    //mnt = floor((ct_l-ct)/60);
    //scd = (ct_l-ct)%60;
    //sprintf(locBuff,"%d:%02d",mnt,scd);

    sprintf(locBuff, "%02d:%02d", now.hour(), now.minute());
    fType(0);
    Disp.drawText(0, 8, locBuff); // tampil tunggu sholat
    if ((ct % 2) == 0)
    {
      //Disp.drawFilledRect(DWidth-3, DHeight-3, DWidth-2, DHeight-2); //60kb
      //
      Disp.drawRect(61, 13, 62, 14, 1); //24kb
    }
    DoSwap = true;
    ct++;
  }

  if (ct > ct_l) {
    dwDone(DrawAdd);
    azzan = false;
    ct = 0;
  }
  jumat = false;
  //Disp.drawText(1,1,String(ct_l-ct)); total detik hitung mundur
}

// =========================================
// Drawing Tools============================
// =========================================
boolean dwDo(int DrawAdd)
{ if (RunSel == DrawAdd) {
    return true;
  }
  else return false;
}

void dwDone(int DrawAdd)
{ RunFinish = DrawAdd;
  RunSel = 0;
}

void dwCtr(int x, int y, const char* Msg)
{ int   tw = Disp.textWidth(Msg);
  int   th = Disp.textHeight();
  int   c = int((DWidth - x - tw) / 2);
  Disp.drawFilledRect(x + c - 1, y, x + tw + c, y + th, 0);
  Disp.drawText(x + c, y, Msg);
}

void Buzzer(uint8_t state)
{
  if (state == 1 and Prm.BZ == 1) {
    //tone(BUZZ, 5000, 400); //pin, nada, durasi //BUZZ, 500, 400
    digitalWrite(BUZZ, HIGH);
  }
  else {
    //noTone(BUZZ);
    digitalWrite(BUZZ, LOW);
  }
}

void fType(int x)
{
  if (x == 0) Disp.setFont(Font0);
  else if (x == 1) Disp.setFont(Font1);
  else if (x == 2) Disp.setFont(Font2);
  else if (x == 3) Disp.setFont(Font3);
  //else if(x==4) Disp.setFont(Font4);
  else Disp.setFont(Font1);
}

/*/ digunakan untuk menghitung hari pasaran
  int jumlahhari(){
  DateTime  now = RTC.now();
  int d= now.day();
  int m= now.month();
  int y= now.year();
  int hb[] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365};
  int ht = (y - 1970) * 365 - 1;
  int hs = hb[m - 1] + d;
  int kab = 0;
  int i;
  if(y % 4 == 0) {
    if(m > 2) {
    hs++;
    }
  }
  for(i = 1970; i < y; i++) {
    if(i % 4 == 0) {
    kab++;
    }
  }
  return (ht + hs + kab);
  }
*/
