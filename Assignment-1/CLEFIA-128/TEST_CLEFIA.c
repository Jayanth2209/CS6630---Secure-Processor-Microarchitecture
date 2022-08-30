#include <stdio.h>
//#include "TTable.h"
#include "CLEFIA.h"

void BytePut(const unsigned char *data, int bytelen)
{
  while(bytelen-- > 0){
    printf("%02x", *data++);
  }
  printf("\n");
}

int main(void)
{
  /*const unsigned char skey[16] = {
    0xffU,0xeeU,0xddU,0xccU,0xbbU,0xaaU,0x99U,0x88U,
    0x77U,0x66U,0x55U,0x44U,0x33U,0x22U,0x11U,0x00U
  };*/

  unsigned char skey[16] = {0xd0U, 0x11U, 0x7cU, 0xe0U, 0xc8U, 0x8bU, 0x89U, 0x5cU, 0x0aU, 0xd0U, 0x8bU, 0x0fU, 0x67U, 0x00U, 0xc6U, 0x0eU};

  /*const unsigned char pt[16] = {
    0x00U,0x01U,0x02U,0x03U,0x04U,0x05U,0x06U,0x07U,
    0x08U,0x09U,0x0aU,0x0bU,0x0cU,0x0dU,0x0eU,0x0fU
  };*/

  unsigned char pt[16] = {0x0bU, 0x1bU, 0xbbU, 0x86U, 0x7dU, 0x79U, 0xefU, 0xc5U, 0x70U, 0xbcU, 0x96U, 0x02U, 0x35U, 0xc9U, 0xc0U, 0x25U};

  unsigned char ct[16];
  unsigned char dst[16];
  unsigned char rk[8 * 26 + 16]; /* 8 bytes x 26 rounds(max) + whitening keys */

  printf("--- Test ---\n");
  printf("Plain Text:  "); BytePut(pt, 16);
  printf("Secret Key:  "); BytePut(skey, 16);

  /* for 128-bit key */
  printf("--- CLEFIA-128 ---\n");
  /* encryption */
  ClefiaKeySet128(rk, skey);
  ClefiaEncrypt(rk, pt, ct);
  printf("Cipher Text: "); BytePut(ct, 16);
  /* decryption */
  ClefiaDecrypt(rk, ct, dst);
  printf("Plain Text : "); BytePut(dst, 16);

  return 0;

}