/*
 * Elliptic_Curve.cpp
 *
 *  Created on: 03-Dec-2021
 *      Author: Ayub Shaikh
 */

// Online C++ compiler to run C++ program online
/*
Elliptic curve digital signature algorithm,
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 64-bit integer type
typedef long long int dlong;
// rational ec point
typedef struct {
   dlong x, y;
} epnt;
// elliptic curve parameters
typedef struct {
   long a, b;
   dlong N;
   epnt G;
   dlong r;
} curve;
// signature pair
typedef struct {
   long a, b;
} pair;

// dlong for holding intermediate results,
// long variables in exgcd() for efficiency,
// maximum parameter size 2 * p.y
// limits the modulus size to 30 bits.

// maximum modulus
const long mxN = 1073741789;
// max order G = mxN + 65536
const long mxr = 1073807325;
// symbolic infinity
const long inf = -2147483647;

// single global curve
curve e;
// point at infinity zerO
epnt zerO;
// impossible inverse mod N
int inverr;


// return mod(v^-1, u)
long exgcd (long v, long u)
{
register long q, t;
long r = 0, s = 1;
if (v < 0) v += u;

   while (v) {
      q = u / v;
      t = u - q * v;
      u = v; v = t;
      t = r - q * s;
      r = s; s = t;
   }
   if (u != 1) {
      printf (" impossible inverse mod N, gcd = %ld\n", u);
      inverr = 1;
   }
return r;
}

// return mod(a, N)
static inline dlong modn (dlong a)
{
   a %= e.N;
   if (a < 0) a += e.N;
return a;
}

// return mod(a, r)
dlong modr (dlong a)
{
   a %= e.r;
   if (a < 0) a += e.r;
return a;
}


// return the discriminant of E
long disc (void)
{
dlong c, a = e.a, b = e.b;
   c = 4 * modn(a * modn(a * a));
return modn(-16 * (c + 27 * modn(b * b)));
}

// return 1 if P = zerO
int isO (epnt p)
{
return (p.x == inf) && (p.y == 0);
}

// return 1 if P is on curve E
int ison (epnt p)
{
long r, s;
if (! isO (p)) {
   r = modn(e.b + p.x * modn(e.a + p.x * p.x));
   s = modn(p.y * p.y);
}
return (r == s);
}


// full ec point addition
void padd (epnt *r, epnt p, epnt q)
{
dlong la, t;

if (isO(p)) {*r = q; return;}
if (isO(q)) {*r = p; return;}

if (p.x != q.x) {                    // R:= P + Q
   t = p.y - q.y;
   la = modn(t * exgcd(p.x - q.x, e.N));
}
else                                 // P = Q, R := 2P
   if ((p.y == q.y) && (p.y != 0)) {
      t = modn(3 * modn(p.x * p.x) + e.a);
      la = modn(t * exgcd (2 * p.y, e.N));
   }
   else
      {*r = zerO; return;}           // P = -Q, R := O

t = modn(la * la - p.x - q.x);
r->y = modn(la * (p.x - t) - p.y);
r->x = t; if (inverr) *r = zerO;
}

// R:= multiple kP
void pmul (epnt *r, epnt p, long k)
{
epnt s = zerO, q = p;

   for (; k; k >>= 1) {
      if (k & 1) padd(&s, s, q);
      if (inverr) {s = zerO; break;}
      padd(&q, q, q);
   }
*r = s;
}


// print point P with prefix f
void pprint (char *f, epnt p)
{
dlong y = p.y;

   if (isO (p))
      printf ("%s (0)\n", f);

   else {
      if (y > e.N - y) y -= e.N;
      printf ("%s (%lld, %lld)\n", f, p.x, y);
   }
}

// initialize elliptic curve
int ellinit (long i[])
{
long a = i[0], b = i[1];
   e.N = i[2]; inverr = 0;

if ((e.N < 5) || (e.N > mxN)) return 0;

   e.a = modn(a);
   e.b = modn(b);
   e.G.x = modn(i[3]);
   e.G.y = modn(i[4]);
   e.r = i[5];

if ((e.r < 5) || (e.r > mxr)) return 0;

printf ("\nE: y^2 = x^3 + %ldx + %ld", a, b);
printf (" (mod %lld)\n", e.N);
pprint ("base point G", e.G);
printf ("order(G, E) = %lld\n", e.r);

return 1;
}

// pseudorandom number [0..1)
double rnd(void)
{
return rand() / ((double)RAND_MAX + 1);
}

// signature primitive
pair signature (dlong s, long f)
{
long c, d, u, u1;
pair sg;
epnt V;

printf ("\nsignature computation\n");
do {
   do {
      u = 1 + (long)(rnd() * (e.r - 1));
      pmul (&V, e.G, u);
      c = modr(V.x);
   }
   while (c == 0);

   u1 = exgcd (u, e.r);
   d = modr(u1 * (f + modr(s * c)));
}
while (d == 0);
printf ("one-time u = %ld\n", u);
pprint ("V = uG", V);

sg.a = c; sg.b = d;
return sg;
}

// verification primitive
int verify (epnt W, long f, pair sg)
{
long c = sg.a, d = sg.b;
long t, c1, h1, h2;
dlong h;
epnt V, V2;

   // domain check
   t = (c > 0) && (c < e.r);
   t &= (d > 0) && (d < e.r);
   if (! t) return 0;

printf ("\nsignature verification\n");
   h = exgcd (d, e.r);
   h1 = modr(f * h);
   h2 = modr(c * h);
   printf ("h1,h2 = %ld, %ld\n", h1,h2);
   pmul (&V, e.G, h1);
   pmul (&V2, W, h2);
   pprint ("h1G", V);
   pprint ("h2W", V2);
   padd (&V, V, V2);
   pprint ("+ =", V);
   if (isO (V)) return 0;
   c1 = modr(V.x);
   printf ("c' = %ld\n", c1);

return (c1 == c);
}

// digital signature on message hash f, error bit d
void ec_dsa (long f, long d)
{
long i, s, t;
pair sg;
epnt W;

   // parameter check
   t = (disc() == 0);
   t |= isO (e.G);
   pmul (&W, e.G, e.r);
   t |= ! isO (W);
   t |= ! ison (e.G);
   if (t) goto errmsg;

printf ("\nkey generation\n");
   s = 1 + (long)(rnd() * (e.r - 1));
   pmul (&W, e.G, s);
   printf ("private key s = %ld\n", s);
   pprint ("public key W = sG", W);

   // next highest power of 2 - 1
   t = e.r;
   for (i = 1; i < 32; i <<= 1)
      t |= t >> i;
   while (f > t) f >>= 1;
   printf ("\naligned hash %lx\n", f);

   sg = signature (s, f);
   if (inverr) goto errmsg;
   printf ("signature c,d = %ld, %ld\n", sg.a, sg.b);

   if (d > 0) {
      while (d > t) d >>= 1;
      f ^= d;
      printf ("\ncorrupted hash %lx\n", f);
   }

   t = verify (W, f, sg);
   if (inverr) goto errmsg;
   if (t)
      printf ("Valid\n_____\n");
   else
      printf ("invalid\n_______\n");

   return;

errmsg:
printf ("invalid parameter set\n");
printf ("_____________________\n");
}



int main (void)
{
typedef long eparm[6];
long d, f;
zerO.x = inf; zerO.y = 0;
srand(time(NULL));

//Test case 1

// Digital signature on message hash f, to simulate
f = 0x789abcde; d = 0;
        //    a,   b,  modulus N, base point G, order(G, E), cofactor
eparm sp = {355, 671, 1073741789, 13693, 10088, 1073807281}; //valid

if (ellinit (sp))
         ec_dsa (f, d);


// Test case 2:
//fails if the modulus divides the discriminant
eparm sp2 =  { 39, 387,      22651,    95,    27,      22651};
if (ellinit (sp2))
         ec_dsa (f, d);

}
