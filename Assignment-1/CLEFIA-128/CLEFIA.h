#ifndef CLEFIA_H
#define CLEFIA_H

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

#endif // CLEFIA_H