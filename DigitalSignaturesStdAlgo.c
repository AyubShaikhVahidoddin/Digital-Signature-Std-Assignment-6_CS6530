/*
 * DSS.c
 *
 *  Created on: 09-Dec-2021
 *      Author: 91883
 */


#include <time.h>
#include <gmp.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#include "sha_256.h"


#define SHA1HANDSOFF

#include <stdio.h>
#include <string.h>
#include<stdlib.h>
/* for uint32_t */
#include <stdint.h>



char message[100000] = "sdfghjhgfdsfghjhgfdghjhgfhjkhgfghjhtrfgytretyuiouytretyuiuytretyuiuytryuiuytryuiuytryuiytryuiytryuiytryuiytryuiytruuytrytryrtd";
char msg[100000] = "dhfgsdhjfhsdfsdfghdsfghsdfgsdfghsdfghsdfsdfhgsdfghsdfgsghdfghdsfgsdgfghsdfhgsdfgsdfgsghdfghsfghsdfdghsfgsdfgsdfgsdghfgshdfghdsgsdg";
mpz_t p,q,g,x,y,h;
mpz_t r, s, r1, s1;
mpz_t Hm;






void DSSigningAlgotithm()
{


	printf("\n *************************************************************** :");

    printf("\n\n**************************Signature Generation***************************************");
    char* HmBuf;;
    int count=0;
    mpz_t k,kinv,t,one;
    gmp_randstate_t k_state;

    mpz_inits(k,kinv,t,one, NULL);
    mpz_set_str(one,"1", 10);
    HmBuf = _SHA1Hash(message);

    mpz_set_str(Hm, HmBuf, 16);

    printf("\nMessage Entered              : %s", message);
    gmp_printf("\nH(m) of message              : %Zd", Hm);

    // Generate random k < q-1
    gmp_randinit_mt(k_state);

    // Check if generated k is less than q-1
    while(1)
    {
        srand(time(0));
        int seed = rand() + count++;
        gmp_randseed_ui(k_state, seed);
        mpz_urandomb(k, k_state, 100);
        mpz_sub(t,q,one);
        if (mpz_cmp(t,k) >= 1) break;
    }

    // Calculate r = (g^k mod p) mod q
    mpz_powm(r,g,k,p);
    mpz_mod(r,r,q);

    //Find k inverse mod q
    mpz_invert(kinv,k,q);

    // Calculate s = [kInv (H(M) + x*r)] mod q
    mpz_mul(t,x, r);
    mpz_add(t,Hm,t);
    mpz_mul(t,t,kinv);
    mpz_mod(s,t,q);

    gmp_printf("\nSignature (r,s) generated    : (%Zd, %Zd)", r , s);
}

void DSSVerificationAlgotithm()
{
	printf("\n\n\n*************************************************************************************");
    printf("\n********************** Signature Verification *****************************************");
    printf("\n************************************************************************************* \n");
    mpz_t w,u1,u2,v,t1,t2;
    mpz_inits(w,u1,u2,v,t1,t2, NULL);


    int value; // declaration of integer variable
    char* HmBuf2;
    printf("\n Please enter the message :");
        	  scanf("%s", &msg);


        	  value=strcmp(message,msg);

        	  if(value == 0)
        	  {
        		  //printf("\n Strings are Same:");
        	  }else{

        		 // printf("\n Strings are NOT NOT  Same:");
        		  HmBuf2 = _SHA1Hash(msg);
        		  mpz_set_str(Hm, HmBuf2, 16);
        	  }


    gmp_printf("\nH(m) of message              : %Zd", Hm);

    printf("\n Please Enter r :");
    gmp_scanf("%Zd", &r1);

    printf("\n Please Enter s :");
        gmp_scanf("%Zd", &s1);
    // calculate w = sInv mod q
    mpz_invert(w,s1,q);


    // calculate u1 = [H(M)w] mod q
    mpz_mul(u1,w,Hm);
    mpz_mod(u1,u1,q);

    // calculate u2 = rw mod q
    mpz_mul(u2,w,r1);
    mpz_mod(u2,u2,q);

    // calculate = [(g^u1 * y^u2) mod p] mod q
    mpz_powm(t1,g,u1,p);
    mpz_powm(t2,y,u2,p);
    mpz_mul(t1,t1,t2);
    mpz_mod(t1,t1,p);
    mpz_mod(v,t1,q);






    gmp_printf("\nReceived r                   : %Zd", r1);
    gmp_printf("\nReceived s                   : %Zd", s1);
    gmp_printf("\nReceived H(m)                : %Zd", Hm);
    gmp_printf("\nGenerated v                  : %Zd", v);


    if (mpz_cmp(v,r1) == 0)
    {
    	 printf("\n ****************************************************************************:");
    	 if(value == 0)
    	           	  {
    	           		  printf("\n\nMessages are Same,  SIGNATURE is VERIFIED and CORRECT:");
    	           	  }
        gmp_printf("\n\nMessage received is VALID");
        gmp_printf("\n\n SIGNATURE VERIFICATION IS SUCCESSFULL!!!!!!!!!!!!!!... ACCEPTED..!! :-) :-) ");
        printf("\n ****************************************************************************:");

    }
    else
    {
    	printf("\n ****************************************************************************:");
        gmp_printf("\n\nMessage received is INVALID");
        gmp_printf("\n\n SIGNATURE VERIFICATION IS FAILED!!!!!!!!!!!!!!... REJECTED..!! ");
        printf("\n ****************************************************************************:");
    }
}

void GenerateSystemVariable()
{
    gmp_randstate_t q_state;
    mpz_t t,pMin1,one;
    int seed;

    mpz_inits(t,pMin1,one, NULL);
    mpz_set_str(one,"1",10);

    // generate prime q randomly
    gmp_randinit_mt(q_state);
    srand(time(0));
    seed = rand();
    gmp_randseed_ui(q_state, seed);
    mpz_urandomb(q, q_state, 100);
    mpz_nextprime(q,q);

    gmp_randinit_mt(q_state);
    srand(time(0));
    seed = rand();
    gmp_randseed_ui(q_state, seed);
    mpz_urandomb(t, q_state, 1000);
    mpz_nextprime(t,t);

    // generate prime p randomly such that q|(p-1)
    while(1)
    {
        mpz_mul(p,q,t);
        mpz_add(p,p,one);
        if (mpz_probab_prime_p(p, 25)==1) break;
        mpz_add(t,t,one);
    }

    // find generator h of p such that h^((p-1) / q) mod p > 1
    mpz_div(h,p,q);mpz_div(h,h,q);
    mpz_sub(pMin1,p,one);
    while(1)
    {
        // (h^p-1) modp
        mpz_powm(t,h,pMin1,p);

        // break if (h^p-1)modp =1
        if (mpz_cmp(t,one) == 0) break;
        mpz_sub(g,g,one);
    }

    // calculate (p-1)/q
    mpz_div(pMin1,pMin1,q);

    // calculate g = h^((p-1)/q) mod p
    mpz_powm(g,h,pMin1,p);
}

void GenerateKeys()
{
    gmp_randstate_t x_state;
    int seed;

    // Generate private key x randomly
    gmp_randinit_mt(x_state);
    srand(time(0));
    seed = rand();
    gmp_randseed_ui(x_state, seed);
    mpz_urandomb(x, x_state, 10);

    // Calculate public key y = g^x mod p
    mpz_powm(y,g,x,p);
}

void DSASetup()
{
    mpz_inits(p,q,g,x,y,h, NULL);

    GenerateSystemVariable();
    GenerateKeys();

    printf("\n\n***********************************************************System Elements***********************************************************");
    gmp_printf("\nPrime Number P               : %Zd", p);
    gmp_printf("\nprime divisor of (p-1) Q     : %Zd", q);
    gmp_printf("\nGenerator G                  : %Zd", g);

    printf("\n\n\n***********************************************************Key Generation***********************************************************");
    gmp_printf("\nPrivate key x                : %Zd", x);
    gmp_printf("\nPublic key y                 : %Zd", y);
}


/*
SHA-1 in C
By Steve Reid <steve@edmweb.com>
100% Public Domain
Test Vectors (from FIPS PUB 180-1)
"abc"
  A9993E36 4706816A BA3E2571 7850C26C 9CD0D89D
"abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq"
  84983E44 1C3BD26E BAAE4AA1 F95129E5 E54670F1
A million repetitions of "a"
  34AA973C D4C4DAA4 F61EEB2B DBAD2731 6534016F
*/

/* #define LITTLE_ENDIAN * This should be #define'd already, if true. */
/* #define SHA1HANDSOFF * Copies data before messing with it. */



#define rol(value, bits) (((value) << (bits)) | ((value) >> (32 - (bits))))

/* blk0() and blk() perform the initial expand. */
/* I got the idea of expanding during the round function from SSLeay */
#if BYTE_ORDER == LITTLE_ENDIAN
#define blk0(i) (block->l[i] = (rol(block->l[i],24)&0xFF00FF00) \
    |(rol(block->l[i],8)&0x00FF00FF))
#elif BYTE_ORDER == BIG_ENDIAN
#define blk0(i) block->l[i]
#else
#error "Endianness not defined!"
#endif
#define blk(i) (block->l[i&15] = rol(block->l[(i+13)&15]^block->l[(i+8)&15] \
    ^block->l[(i+2)&15]^block->l[i&15],1))

/* (R0+R1), R2, R3, R4 are the different operations used in SHA1 */
#define R0(v,w,x,y,z,i) z+=((w&(x^y))^y)+blk0(i)+0x5A827999+rol(v,5);w=rol(w,30);
#define R1(v,w,x,y,z,i) z+=((w&(x^y))^y)+blk(i)+0x5A827999+rol(v,5);w=rol(w,30);
#define R2(v,w,x,y,z,i) z+=(w^x^y)+blk(i)+0x6ED9EBA1+rol(v,5);w=rol(w,30);
#define R3(v,w,x,y,z,i) z+=(((w|x)&y)|(w&x))+blk(i)+0x8F1BBCDC+rol(v,5);w=rol(w,30);
#define R4(v,w,x,y,z,i) z+=(w^x^y)+blk(i)+0xCA62C1D6+rol(v,5);w=rol(w,30);


/* Hash a single 512-bit block. This is the core of the algorithm. */

void SHA1Transform(
    uint32_t state[5],
    const unsigned char buffer[64]
)
{
    uint32_t a, b, c, d, e;

    typedef union
    {
        unsigned char c[64];
        uint32_t l[16];
    } CHAR64LONG16;

#ifdef SHA1HANDSOFF
    CHAR64LONG16 block[1];      /* use array to appear as a pointer */

    memcpy(block, buffer, 64);
#else
    /* The following had better never be used because it causes the
     * pointer-to-const buffer to be cast into a pointer to non-const.
     * And the result is written through.  I threw a "const" in, hoping
     * this will cause a diagnostic.
     */
    CHAR64LONG16 *block = (const CHAR64LONG16 *) buffer;
#endif
    /* Copy context->state[] to working vars */
    a = state[0];
    b = state[1];
    c = state[2];
    d = state[3];
    e = state[4];
    /* 4 rounds of 20 operations each. Loop unrolled. */
    R0(a, b, c, d, e, 0);
    R0(e, a, b, c, d, 1);
    R0(d, e, a, b, c, 2);
    R0(c, d, e, a, b, 3);
    R0(b, c, d, e, a, 4);
    R0(a, b, c, d, e, 5);
    R0(e, a, b, c, d, 6);
    R0(d, e, a, b, c, 7);
    R0(c, d, e, a, b, 8);
    R0(b, c, d, e, a, 9);
    R0(a, b, c, d, e, 10);
    R0(e, a, b, c, d, 11);
    R0(d, e, a, b, c, 12);
    R0(c, d, e, a, b, 13);
    R0(b, c, d, e, a, 14);
    R0(a, b, c, d, e, 15);
    R1(e, a, b, c, d, 16);
    R1(d, e, a, b, c, 17);
    R1(c, d, e, a, b, 18);
    R1(b, c, d, e, a, 19);
    R2(a, b, c, d, e, 20);
    R2(e, a, b, c, d, 21);
    R2(d, e, a, b, c, 22);
    R2(c, d, e, a, b, 23);
    R2(b, c, d, e, a, 24);
    R2(a, b, c, d, e, 25);
    R2(e, a, b, c, d, 26);
    R2(d, e, a, b, c, 27);
    R2(c, d, e, a, b, 28);
    R2(b, c, d, e, a, 29);
    R2(a, b, c, d, e, 30);
    R2(e, a, b, c, d, 31);
    R2(d, e, a, b, c, 32);
    R2(c, d, e, a, b, 33);
    R2(b, c, d, e, a, 34);
    R2(a, b, c, d, e, 35);
    R2(e, a, b, c, d, 36);
    R2(d, e, a, b, c, 37);
    R2(c, d, e, a, b, 38);
    R2(b, c, d, e, a, 39);
    R3(a, b, c, d, e, 40);
    R3(e, a, b, c, d, 41);
    R3(d, e, a, b, c, 42);
    R3(c, d, e, a, b, 43);
    R3(b, c, d, e, a, 44);
    R3(a, b, c, d, e, 45);
    R3(e, a, b, c, d, 46);
    R3(d, e, a, b, c, 47);
    R3(c, d, e, a, b, 48);
    R3(b, c, d, e, a, 49);
    R3(a, b, c, d, e, 50);
    R3(e, a, b, c, d, 51);
    R3(d, e, a, b, c, 52);
    R3(c, d, e, a, b, 53);
    R3(b, c, d, e, a, 54);
    R3(a, b, c, d, e, 55);
    R3(e, a, b, c, d, 56);
    R3(d, e, a, b, c, 57);
    R3(c, d, e, a, b, 58);
    R3(b, c, d, e, a, 59);
    R4(a, b, c, d, e, 60);
    R4(e, a, b, c, d, 61);
    R4(d, e, a, b, c, 62);
    R4(c, d, e, a, b, 63);
    R4(b, c, d, e, a, 64);
    R4(a, b, c, d, e, 65);
    R4(e, a, b, c, d, 66);
    R4(d, e, a, b, c, 67);
    R4(c, d, e, a, b, 68);
    R4(b, c, d, e, a, 69);
    R4(a, b, c, d, e, 70);
    R4(e, a, b, c, d, 71);
    R4(d, e, a, b, c, 72);
    R4(c, d, e, a, b, 73);
    R4(b, c, d, e, a, 74);
    R4(a, b, c, d, e, 75);
    R4(e, a, b, c, d, 76);
    R4(d, e, a, b, c, 77);
    R4(c, d, e, a, b, 78);
    R4(b, c, d, e, a, 79);
    /* Add the working vars back into context.state[] */
    state[0] += a;
    state[1] += b;
    state[2] += c;
    state[3] += d;
    state[4] += e;
    /* Wipe variables */
    a = b = c = d = e = 0;
#ifdef SHA1HANDSOFF
    memset(block, '\0', sizeof(block));
#endif
}


/* SHA1Init - Initialize new context */

void SHA1Init(
    SHA1_CTX * context
)
{
    /* SHA1 initialization constants */
    context->state[0] = 0x67452301;
    context->state[1] = 0xEFCDAB89;
    context->state[2] = 0x98BADCFE;
    context->state[3] = 0x10325476;
    context->state[4] = 0xC3D2E1F0;
    context->count[0] = context->count[1] = 0;
}


/* Run your data through this. */

void SHA1Update(
    SHA1_CTX * context,
    const unsigned char *data,
    uint32_t len
)
{
    uint32_t i;

    uint32_t j;

    j = context->count[0];
    if ((context->count[0] += len << 3) < j)
        context->count[1]++;
    context->count[1] += (len >> 29);
    j = (j >> 3) & 63;
    if ((j + len) > 63)
    {
        memcpy(&context->buffer[j], data, (i = 64 - j));
        SHA1Transform(context->state, context->buffer);
        for (; i + 63 < len; i += 64)
        {
            SHA1Transform(context->state, &data[i]);
        }
        j = 0;
    }
    else
        i = 0;
    memcpy(&context->buffer[j], &data[i], len - i);
}


/* Add padding and return the message digest. */

void SHA1Final(
    unsigned char digest[20],
    SHA1_CTX * context
)
{
    unsigned i;

    unsigned char finalcount[8];

    unsigned char c;

#if 0    /* untested "improvement" by DHR */
    /* Convert context->count to a sequence of bytes
     * in finalcount.  Second element first, but
     * big-endian order within element.
     * But we do it all backwards.
     */
    unsigned char *fcp = &finalcount[8];

    for (i = 0; i < 2; i++)
    {
        uint32_t t = context->count[i];

        int j;

        for (j = 0; j < 4; t >>= 8, j++)
            *--fcp = (unsigned char) t}
#else
    for (i = 0; i < 8; i++)
    {
        finalcount[i] = (unsigned char) ((context->count[(i >= 4 ? 0 : 1)] >> ((3 - (i & 3)) * 8)) & 255);      /* Endian independent */
    }
#endif
    c = 0200;
    SHA1Update(context, &c, 1);
    while ((context->count[0] & 504) != 448)
    {
        c = 0000;
        SHA1Update(context, &c, 1);
    }
    SHA1Update(context, finalcount, 8); /* Should cause a SHA1Transform() */
    for (i = 0; i < 20; i++)
    {
        digest[i] = (unsigned char)
            ((context->state[i >> 2] >> ((3 - (i & 3)) * 8)) & 255);
    }
    /* Wipe variables */
    memset(context, '\0', sizeof(*context));
    memset(&finalcount, '\0', sizeof(finalcount));
}

void SHA1(
    char *hash_out,
    const char *str,
    int len)
{
    SHA1_CTX ctx;
    unsigned int ii;

    SHA1Init(&ctx);
    for (ii=0; ii<len; ii+=1)
        SHA1Update(&ctx, (const unsigned char*)str + ii, 1);
    SHA1Final((unsigned char *)hash_out, &ctx);
    hash_out[20] = '\0';
}

  char* _SHA1Hash(char *buf){
  SHA1_CTX sha; uint8_t results[20]; int n;
  char tmp[2];
  char *str=(char*)malloc(sizeof(char)*44);
  str[43]='\0';
  n = strlen(buf);
  SHA1Init(&sha);
  SHA1Update(&sha, (uint8_t *)buf, n);
  SHA1Final(results, &sha);
  sprintf(tmp,"%02x", results[0]);
  strcpy(str,tmp);
  for (n = 1; n <20; n++){
  sprintf(tmp,"%02x", results[n]);
  strcat(str,tmp);
  }
  //printf("%s\n",str);
  return str;
  }

int main()
{
	printf(" ************************************************************************** \n\n");
		printf("-------Assignment-6 Submitted by Roll number: CS21M515 **** AYUB SHAIKH IIT Madras  \n\n");
		printf(" DIGITAL SIGNATURE STANDARDS Verification Program in C language \n\n");
    printf("\n*******************************************************************************");
    printf("\nEnter message to be signed   :");
    int num;
    gets(message);

    DSASetup();

    DSSigningAlgotithm();

    DSSVerificationAlgotithm();

    printf("\nEnter any number to exit:");
    scanf("%d", & num);

    return 0;
}
