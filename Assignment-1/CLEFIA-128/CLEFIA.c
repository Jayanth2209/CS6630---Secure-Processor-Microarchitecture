#include <TTable.h>

void ByteCpy(unsigned char *dst, const unsigned char *src, int bytelen);
void ByteXor(unsigned char *dst, const unsigned char *a, const unsigned char *b, int bytelen);

void ClefiaF0Xor(unsigned char *y, const unsigned char *x, const unsigned char *rk);
void ClefiaF1Xor(unsigned char *y, const unsigned char *x, const unsigned char *rk);

void ClefiaGfn4(unsigned char *y, const unsigned char *x, const unsigned char *rk, int r);
void ClefiaGfn4Inv(unsigned char *y, const unsigned char *x, const unsigned char *rk, int r);

void ClefiaDoubleSwap(unsigned char *lk);

void ClefiaConSet(unsigned char *con, const unsigned char *iv, int lk);

void ClefiaKeySet128(unsigned char *rk, const unsigned char *skey);

void ClefiaEncrypt(unsigned char *key, unsigned char *plaintext, unsigned char *ciphertext);

void ClefiaDecrypt(unsigned char *key, unsigned char *ciphertext, unsigned char *plaintext);

void ByteCpy(unsigned char *dst, const unsigned char *src, int bytelen)
{
  while(bytelen-- > 0){
    *dst++ = *src++;
  }
}

void ByteXor(unsigned char *dst, const unsigned char *a, const unsigned char *b, int bytelen)
{
  while(bytelen-- > 0){
    *dst++ = *a++ ^ *b++;
  }
}

void ClefiaF0Xor(unsigned char *dst, const unsigned char *src, const unsigned char *rk)
{
  unsigned char x[4], y[4];
  unsigned char YT;
  /* F0 */
  /* Key addition */
  ByteXor(x, src, rk, 4);
 
  YT = TTB00[x[0]] ^ TTB01[x[1]] ^ TTB02[x[2]] ^ TTB03[x[3]];

  y[0] = (YT&0xff000000)>>24;
  y[1] = (YT&0x00ff0000)>>16;
  y[2] = (YT&0x0000ff00)>>8;
  y[3] = YT&0x000000ff;

  /* Xoring after F0 */
  ByteCpy(dst + 0, src + 0, 4);
  ByteXor(dst + 4, src + 4, y, 4);
}

void ClefiaF1Xor(unsigned char *dst, const unsigned char *src, const unsigned char *rk)
{
  unsigned char x[4], y[4];
  unsigned int YT;
  /* F1 */
  /* Key addition */
  ByteXor(x, src, rk, 4);
  
  YT = TTB10[x[0]] ^ TTB11[x[1]] ^ TTB12[x[2]] ^ TTB13[x[3]];

  y[0] = (YT&0xff000000)>>24;
  y[1] = (YT&0x00ff0000)>>16;
  y[2] = (YT&0x0000ff00)>>8;
  y[3] = YT&0x000000ff;

  /* Xoring after F1 */
  ByteCpy(dst + 0, src + 0, 4);
  ByteXor(dst + 4, src + 4, y, 4);
}

void ClefiaGfn4(unsigned char *y, const unsigned char *x, const unsigned char *rk, int r)
{ 
  unsigned char fin[16], fout[16];

  ByteCpy(fin, x, 16);
  while(r-- > 0){
    ClefiaF0Xor(fout + 0, fin + 0, rk + 0);
    ClefiaF1Xor(fout + 8, fin + 8, rk + 4);
    rk += 8;
    if(r){ /* swapping for encryption */
      ByteCpy(fin + 0,  fout + 4, 12);
      ByteCpy(fin + 12, fout + 0, 4);
    }
  }
  ByteCpy(y, fout, 16);
}

void ClefiaGfn4Inv(unsigned char *y, const unsigned char *x, const unsigned char *rk, int r)
{
  unsigned char fin[16], fout[16];

  rk += (r - 1) * 8;
  ByteCpy(fin, x, 16);
  while(r-- > 0){
    ClefiaF0Xor(fout + 0, fin + 0, rk + 0);
    ClefiaF1Xor(fout + 8, fin + 8, rk + 4);
    rk -= 8;
    if(r){ /* swapping for decryption */
      ByteCpy(fin + 0, fout + 12, 4);
      ByteCpy(fin + 4, fout + 0,  12);
    }
  }
  ByteCpy(y, fout, 16);
}

void ClefiaDoubleSwap(unsigned char *lk)
{
  unsigned char t[16];

  t[0]  = (lk[0] << 7) | (lk[1]  >> 1);
  t[1]  = (lk[1] << 7) | (lk[2]  >> 1);
  t[2]  = (lk[2] << 7) | (lk[3]  >> 1);
  t[3]  = (lk[3] << 7) | (lk[4]  >> 1);
  t[4]  = (lk[4] << 7) | (lk[5]  >> 1);
  t[5]  = (lk[5] << 7) | (lk[6]  >> 1);
  t[6]  = (lk[6] << 7) | (lk[7]  >> 1);
  t[7]  = (lk[7] << 7) | (lk[15] & 0x7fU);

  t[8]  = (lk[8]  >> 7) | (lk[0]  & 0xfeU);
  t[9]  = (lk[9]  >> 7) | (lk[8]  << 1);
  t[10] = (lk[10] >> 7) | (lk[9]  << 1);
  t[11] = (lk[11] >> 7) | (lk[10] << 1);
  t[12] = (lk[12] >> 7) | (lk[11] << 1);
  t[13] = (lk[13] >> 7) | (lk[12] << 1);
  t[14] = (lk[14] >> 7) | (lk[13] << 1);
  t[15] = (lk[15] >> 7) | (lk[14] << 1);

  ByteCpy(lk, t, 16);
}

void ClefiaConSet(unsigned char *con, const unsigned char *iv, int lk)
{
  unsigned char t[2];
  unsigned char tmp;

  ByteCpy(t, iv, 2);
  while(lk-- > 0){
    con[0] = t[0] ^ 0xb7U; /* P_16 = 0xb7e1 (natural logarithm) */
    con[1] = t[1] ^ 0xe1U;
    con[2] = ~((t[0] << 1) | (t[1] >> 7));
    con[3] = ~((t[1] << 1) | (t[0] >> 7));
    con[4] = ~t[0] ^ 0x24U; /* Q_16 = 0x243f (circle ratio) */
    con[5] = ~t[1] ^ 0x3fU;
    con[6] = t[1];
    con[7] = t[0];
    con += 8;

    /* updating T */
    if(t[1] & 0x01U){
      t[0] ^= 0xa8U;
      t[1] ^= 0x30U;
    }
    tmp = t[0] << 7;
    t[0] = (t[0] >> 1) | (t[1] << 7);
    t[1] = (t[1] >> 1) | tmp;
  }    
}

void ClefiaKeySet128(unsigned char *key, const unsigned char *raw_key)
{
  const unsigned char iv[2] = {0x42U, 0x8aU}; /* cubic root of 2 */
  unsigned char lk[16];
  unsigned char con128[4 * 60];
  int i;

  /* generating CONi^(128) (0 <= i < 60, lk = 30) */
  ClefiaConSet(con128, iv, 30);
  /* GFN_{4,12} (generating L from K) */
  ClefiaGfn4(lk, raw_key, con128, 12);

  ByteCpy(key, raw_key, 8); /* initial whitening key (WK0, WK1) */
  key += 8;
  for(i = 0; i < 9; i++){ /* round key (RKi (0 <= i < 36)) */
    ByteXor(key, lk, con128 + i * 16 + (4 * 24), 16);
    if(i % 2){
      ByteXor(key, key, raw_key, 16); /* Xoring K */
    }
    ClefiaDoubleSwap(lk); /* Updating L (DoubleSwap function) */
    key += 16;
  }
  ByteCpy(key, raw_key + 8, 8); /* final whitening key (WK2, WK3) */
}

void ClefiaEncrypt(unsigned char *key, unsigned char *plaintext, unsigned char *ciphertext)
{
  const int r = 18;
  unsigned char rin[16], rout[16];

  ByteCpy(rin,  plaintext,  16);

  ByteXor(rin + 4,  rin + 4,  key + 0, 4); /* initial key whitening */
  ByteXor(rin + 12, rin + 12, key + 4, 4);
  key += 8;

  ClefiaGfn4(rout, rin, key, r); /* GFN_{4,r} */

  ByteCpy(ciphertext, rout, 16);
  ByteXor(ciphertext + 4,  ciphertext + 4,  key + r * 8 + 0, 4); /* final key whitening */
  ByteXor(ciphertext + 12, ciphertext + 12, key + r * 8 + 4, 4);
}

void ClefiaDecrypt(unsigned char *key, unsigned char *ciphertext, unsigned char *plaintext)
{
  const int r = 18;
  unsigned char rin[16], rout[16];

  ByteCpy(rin, ciphertext, 16);

  ByteXor(rin + 4,  rin + 4,  key + r * 8 + 8,  4); /* initial key whitening */
  ByteXor(rin + 12, rin + 12, key + r * 8 + 12, 4);
  key += 8;

  ClefiaGfn4Inv(rout, rin, key, r); /* GFN^{-1}_{4,r} */

  ByteCpy(plaintext, rout, 16);
  ByteXor(plaintext + 4,  plaintext + 4,  key - 8, 4); /* final key whitening */
  ByteXor(plaintext + 12, plaintext + 12, key - 4, 4);
}
