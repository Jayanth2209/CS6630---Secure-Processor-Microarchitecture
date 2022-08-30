#include<stdio.h>
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
  unsigned char skey[16] = {0xd0U, 0x11U, 0x7cU, 0xe0U, 0xc8U, 0x8bU, 0x89U, 0x5cU, 0x0aU, 0xd0U, 0x8bU, 0x0fU, 0x67U, 0x00U, 0xc6U, 0x0eU};
  
  unsigned char plaintext[20][16] = {
    {0x0bU, 0x1bU, 0xbbU, 0x86U, 0x7dU, 0x79U, 0xefU, 0xc5U, 0x70U, 0xbcU, 0x96U, 0x02U, 0x35U, 0xc9U, 0xc0U, 0x25U},
    {0x04U, 0xfbU, 0x00U, 0xdbU, 0x10U, 0x13U, 0x7aU, 0x1dU, 0x6fU, 0x90U, 0x07U, 0xd7U, 0x03U, 0xbaU, 0xccU, 0x79U},
    {0x10U, 0xefU, 0xe1U, 0x6eU, 0x49U, 0xc5U, 0xebU, 0x68U, 0xe7U, 0xe3U, 0xe7U, 0x70U, 0x3cU, 0xf3U, 0xb2U, 0x37U},
    {0x48U, 0xbfU, 0x27U, 0x2aU, 0x55U, 0x7aU, 0x90U, 0x38U, 0xf5U, 0xfaU, 0xb2U, 0xecU, 0xf3U, 0xc0U, 0xa9U, 0x12U},
    {0xfcU, 0xb8U, 0x69U, 0xdaU, 0x80U, 0x06U, 0x56U, 0xc7U, 0x37U, 0x83U, 0xadU, 0xb0U, 0x7cU, 0xc0U, 0x0fU, 0x06U},
    {0x8eU, 0x2bU, 0x34U, 0x02U, 0x3fU, 0xa5U, 0xdaU, 0x7eU, 0xcbU, 0x35U, 0x13U, 0x7eU, 0x48U, 0xd5U, 0x83U, 0x62U},
    {0x96U, 0x64U, 0x31U, 0xe4U, 0xe8U, 0x8eU, 0x0dU, 0x66U, 0x7aU, 0x82U, 0x45U, 0x5fU, 0x2bU, 0xf1U, 0x18U, 0x00U},
    {0xa8U, 0x99U, 0x64U, 0x89U, 0xf8U, 0x65U, 0x25U, 0xfaU, 0x6dU, 0x5eU, 0xd1U, 0xa6U, 0x1dU, 0x9eU, 0x5cU, 0x3eU},
    {0xfcU, 0x73U, 0x3eU, 0x0eU, 0x59U, 0xf5U, 0x8bU, 0x53U, 0xb9U, 0xd6U, 0x73U, 0xb2U, 0x73U, 0x2bU, 0x57U, 0x1cU},
    {0x8cU, 0x41U, 0xfcU, 0xa0U, 0xe1U, 0xf9U, 0xd7U, 0x87U, 0x9eU, 0x38U, 0xffU, 0xa4U, 0x62U, 0x23U, 0xfdU, 0xbeU},
    {0xe5U, 0xf0U, 0xdbU, 0x0fU, 0xecU, 0xbeU, 0xc4U, 0x24U, 0x70U, 0x64U, 0xa7U, 0x20U, 0x2fU, 0x7dU, 0x21U, 0xb4U},
    {0x22U, 0xc7U, 0x79U, 0x43U, 0x44U, 0x2fU, 0x7eU, 0x1aU, 0xa2U, 0xd1U, 0x1aU, 0x5dU, 0x8fU, 0x44U, 0x30U, 0x26U},
    {0x31U, 0xbaU, 0xb9U, 0x52U, 0xc5U, 0x17U, 0x62U, 0xd0U, 0xc7U, 0x43U, 0x4eU, 0x9bU, 0x80U, 0xc0U, 0xa6U, 0x0dU},
    {0x62U, 0xa5U, 0xb9U, 0x47U, 0x93U, 0x98U, 0x07U, 0x02U, 0x94U, 0x00U, 0x50U, 0x0fU, 0x74U, 0x13U, 0x51U, 0xeaU},
    {0xf7U, 0xcaU, 0x10U, 0xebU, 0xa3U, 0xf7U, 0x9dU, 0xd9U, 0x8aU, 0x58U, 0x97U, 0x01U, 0xb0U, 0xebU, 0xf5U, 0x0bU},
    {0x58U, 0x06U, 0x6eU, 0xcbU, 0x5eU, 0xa9U, 0x3eU, 0xbaU, 0x54U, 0x49U, 0xb7U, 0xcfU, 0x1bU, 0x56U, 0x18U, 0x4bU},
    {0xa3U, 0x1dU, 0x2cU, 0xa3U, 0x14U, 0x0aU, 0x6dU, 0xa2U, 0x42U, 0xdaU, 0xd1U, 0xc7U, 0x53U, 0xa8U, 0x45U, 0xa6U},
    {0xa9U, 0xe7U, 0x2bU, 0x69U, 0x56U, 0x1aU, 0x5eU, 0x62U, 0xadU, 0x55U, 0xa2U, 0x9bU, 0x8eU, 0xcfU, 0x5cU, 0x45U},
    {0x6eU, 0xa4U, 0x4aU, 0x4eU, 0x7eU, 0x07U, 0xb7U, 0x6cU, 0x1aU, 0x79U, 0xb1U, 0xa3U, 0x24U, 0x40U, 0xe2U, 0x6eU},
    {0xd2U, 0x25U, 0x42U, 0x70U, 0xa3U, 0xc1U, 0xa9U, 0x7eU, 0x30U, 0xdaU, 0x56U, 0x45U, 0x86U, 0xf9U, 0xb0U, 0x63U},
};

  unsigned char ciphertext[20][16] = {
    {0xaaU, 0x2dU, 0x49U, 0x90U, 0x2fU, 0x13U, 0x5eU, 0x31U, 0x97U, 0x60U, 0x92U, 0x2eU, 0x85U, 0xe1U, 0x39U, 0x45U},
    {0x42U, 0xebU, 0xd9U, 0x24U, 0x47U, 0x38U, 0xb7U, 0xfbU, 0xa9U, 0xcbU, 0xb1U, 0xd6U, 0xfcU, 0xe5U, 0x3cU, 0xc1U},
    {0xaeU, 0x77U, 0x85U, 0x07U, 0x30U, 0x42U, 0x46U, 0x83U, 0xb7U, 0x5bU, 0x4aU, 0x23U, 0xf7U, 0x12U, 0xcaU, 0xbeU},
    {0x82U, 0x8eU, 0x81U, 0x52U, 0x48U, 0x83U, 0xacU, 0x86U, 0xe4U, 0x7dU, 0xecU, 0x63U, 0x81U, 0xb8U, 0x05U, 0x02U},
    {0x1dU, 0xfbU, 0x04U, 0x07U, 0x66U, 0xdaU, 0xc5U, 0x06U, 0x00U, 0x76U, 0xe2U, 0x75U, 0x4dU, 0x3aU, 0xb3U, 0x9eU},
    {0xb6U, 0x06U, 0x1aU, 0xafU, 0x25U, 0x4bU, 0x5aU, 0xe1U, 0x17U, 0x87U, 0xb4U, 0x8dU, 0x34U, 0x0eU, 0xf0U, 0xcaU},
    {0x61U, 0x0fU, 0xbaU, 0x1eU, 0x63U, 0x02U, 0x61U, 0x21U, 0x5eU, 0xc8U, 0xc8U, 0xe2U, 0xebU, 0x8aU, 0x3cU, 0x33U},
    {0x91U, 0x77U, 0xf9U, 0xb9U, 0xecU, 0x34U, 0x39U, 0xf1U, 0x80U, 0xbeU, 0xf2U, 0x4bU, 0x51U, 0x4fU, 0x8aU, 0x7eU},
    {0x55U, 0x1bU, 0x78U, 0xe1U, 0x4fU, 0xeeU, 0x7eU, 0x53U, 0x2bU, 0x41U, 0xccU, 0xfbU, 0x28U, 0x7bU, 0x40U, 0x64U},
    {0x3eU, 0xf2U, 0x4bU, 0xcfU, 0x11U, 0xa6U, 0xb9U, 0xc5U, 0x42U, 0xc1U, 0x5cU, 0xdaU, 0x71U, 0xe1U, 0x30U, 0x7bU},
    {0xe3U, 0xf6U, 0x41U, 0x6eU, 0x8eU, 0x5aU, 0xd6U, 0x5dU, 0x19U, 0xe9U, 0xbeU, 0x4eU, 0x0dU, 0xd0U, 0x3bU, 0x4cU},
    {0xedU, 0x27U, 0xc4U, 0x63U, 0x0dU, 0xabU, 0xd1U, 0xbcU, 0x3cU, 0x0dU, 0x69U, 0x8aU, 0x09U, 0x91U, 0x39U, 0xc8U},
    {0xe7U, 0xe8U, 0xe8U, 0xa8U, 0x55U, 0x5fU, 0xaaU, 0x65U, 0x10U, 0xbeU, 0x3bU, 0xfcU, 0x99U, 0xffU, 0xc3U, 0x0eU},
    {0xa6U, 0x28U, 0xfbU, 0x32U, 0x55U, 0x16U, 0x14U, 0xc4U, 0x8aU, 0x9dU, 0x03U, 0x4aU, 0x15U, 0xccU, 0x68U, 0x93U},
    {0x00U, 0xf2U, 0x32U, 0x91U, 0xf9U, 0xa8U, 0x7cU, 0xbaU, 0x9fU, 0x36U, 0xaeU, 0x87U, 0x8cU, 0x21U, 0x1aU, 0x9aU},
    {0x7cU, 0x17U, 0xc3U, 0xcbU, 0x54U, 0x2dU, 0x0aU, 0x5cU, 0x9fU, 0xd4U, 0x45U, 0xc6U, 0x84U, 0x29U, 0xaaU, 0x88U},
    {0x95U, 0xcfU, 0x9cU, 0x4dU, 0x80U, 0xf8U, 0x5fU, 0x4bU, 0x3fU, 0x55U, 0xd6U, 0xddU, 0x11U, 0xdcU, 0x3fU, 0x13U},
    {0xb0U, 0xc5U, 0x27U, 0x96U, 0x9dU, 0x81U, 0x77U, 0x73U, 0xf5U, 0x38U, 0xb4U, 0x5bU, 0x3fU, 0x3aU, 0x3eU, 0xb6U},
    {0xafU, 0x85U, 0xbfU, 0xe3U, 0x13U, 0xd5U, 0x8eU, 0x30U, 0x0dU, 0x7fU, 0x69U, 0x53U, 0x21U, 0xafU, 0x46U, 0x4eU},
    {0xc6U, 0xbeU, 0x50U, 0x8bU, 0xacU, 0x61U, 0x4cU, 0x00U, 0x33U, 0x62U, 0x68U, 0xcaU, 0x05U, 0x0dU, 0x74U, 0x80U},
};

  unsigned char pt[16] = {0x00U,0x01U,0x02U,0x03U,0x04U,0x05U,0x06U,0x07U,0x08U,0x09U,0x0aU,0x0bU,0x0cU,0x0dU,0x0eU,0x0fU};

  unsigned char ct[16];
  unsigned char dst[16];
  unsigned char rk[8 * 26 + 16]; /* 8 bytes x 26 rounds(max) + whitening keys */
  ClefiaKeySet128(rk, skey);
  for(int i=0;i<20;i++)
  {
    //printf("Plain Text: "); BytePut(plaintext[i], 16);
    ClefiaEncrypt(rk, plaintext[i], ct);
    //printf("Cipher Text Obtained: "); BytePut(ct, 16);
    //printf("Cipher Text Expected: "); BytePut(ciphertext[i], 16);
    for(int j=0;j<16;j++)
    {
      if(ct[j]!=ciphertext[i][j])
        //printf("%d, %d\n",ciphertext[i][j],ct[j]);
        printf("Error in %dth round\n",i); break;
    }
  }
  printf("All passed\n");
  // printf("--- CLEFIA-128 T-Table Implementation Test ---\n");


  return 0;
}
