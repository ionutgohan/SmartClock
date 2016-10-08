#include "Fonts_LCD.h"
#include "PounceTypes_v2.h"

/**
  Global Constant Arrays.
  These arrays have the definition for the different characters. Currently
  only numbers, capitol letters, exclamation and colon mark.
*/
const U08 _0[CHAR_SIZE] = 
{
  1,1,1,
  1,0,1,
  1,0,1,
  1,0,1,
  1,1,1,  
};
const U08 _1[CHAR_SIZE]= 
{
  0,1,0,
  1,1,0,
  0,1,0,
  0,1,0,
  1,1,1,

};
const U08 _2[CHAR_SIZE]= 
{
  1,1,1,
  0,0,1,
  1,1,1,
  1,0,0,
  1,1,1,

};
const U08 _3[CHAR_SIZE]= 
{
  1,1,1,
  0,0,1,
  0,1,1,
  0,0,1,
  1,1,1,
};
const U08 _4[CHAR_SIZE]= 
{
  1,0,1,
  1,0,1,
  1,1,1,
  0,0,1,
  0,0,1,
};
const U08 _5[CHAR_SIZE]= 
{
  1,1,1,
  1,0,0,
  1,1,1,
  0,0,1,
  1,1,1,  
};
const U08 _6[CHAR_SIZE]= 
{
  1,1,1,
  1,0,0,
  1,1,1,
  1,0,1,
  1,1,1,
};
const U08 _7[CHAR_SIZE]= 
{
  1,1,1,
  0,0,1,
  0,0,1,
  0,0,1,
  0,0,1,
};
const U08 _8[CHAR_SIZE]= 
{
  1,1,1,
  1,0,1,
  1,1,1,
  1,0,1,
  1,1,1,
};
const U08 _9[CHAR_SIZE]= 
{
  1,1,1,
  1,0,1,
  1,1,1,
  0,0,1,
  0,0,1,
};
const U08 _A[CHAR_SIZE]= 
{
  0,1,0,
  1,0,1,
  1,1,1,
  1,0,1,
  1,0,1,
};
const U08 _B[CHAR_SIZE]= 
{
  1,1,0,
  1,0,1,
  1,1,1,
  1,0,1,
  1,1,0,
};
const U08 _C[CHAR_SIZE]= 
{
  1,1,1,
  1,0,0,
  1,0,0,
  1,0,0,
  1,1,1,
};
const U08 _D[CHAR_SIZE]= 
{
  1,1,0,
  1,0,1,
  1,0,1,
  1,0,1,
  1,1,0,
};
const U08 _E[CHAR_SIZE]= 
{
  1,1,1,
  1,0,0,
  1,1,1,
  1,0,0,
  1,1,1,
};
const U08 _F[CHAR_SIZE]= 
{
  1,1,1,
  1,0,0,
  1,1,0,
  1,0,0,
  1,0,0,
};
const U08 _G[CHAR_SIZE]= 
{
  0,1,1,
  1,0,0,
  1,1,1,
  1,0,1,
  0,1,1,
};
const U08 _H[CHAR_SIZE]= 
{
  1,0,1,
  1,0,1,
  1,1,1,
  1,0,1,
  1,0,1,
};
const U08 _I[CHAR_SIZE]= 
{
  0,1,0,
  0,1,0,
  0,1,0,
  0,1,0,
  0,1,0,
};
const U08 _J[CHAR_SIZE]= 
{
  0,0,1,
  0,0,1,
  0,0,1,
  1,0,1,
  1,1,1,
};
const U08 _K[CHAR_SIZE]= 
{
  1,0,1,
  1,1,0,
  1,0,0,
  1,1,0,
  1,0,1,   
};
const U08 _L[CHAR_SIZE]= 
{
  1,0,0,
  1,0,0,
  1,0,0,
  1,0,0,
  1,1,1,
};
const U08 _M[CHAR_SIZE]= 
{
  1,0,1,
  1,1,1,
  1,0,1,
  1,0,1,
  1,0,1,
};
const U08 _N[CHAR_SIZE]= 
{
  1,0,1,
  1,0,1,
  1,1,1,
  1,0,1,
  1,0,1,
};
const U08 _O[CHAR_SIZE]= 
{
  0,1,0,
  1,0,1,
  1,0,1,
  1,0,1,
  0,1,0,
};
const U08 _P[CHAR_SIZE]= 
{
  1,1,1,
  1,0,1,
  1,1,1,
  1,0,0,
  1,0,0,
};
const U08 _Q[CHAR_SIZE]= 
{
  0,1,0,
  1,0,1,
  1,0,1,
  1,0,1,
  0,1,1,
};
const U08 _R[CHAR_SIZE]= 
{
  1,1,0,
  1,0,1,
  1,1,0,
  1,1,0,
  1,0,1,
};
const U08 _S[CHAR_SIZE]= 
{
  0,1,1,
  1,0,0,
  1,1,1,
  0,0,1,
  1,1,0,
};
const U08 _T[CHAR_SIZE]= 
{
  1,1,1,
  0,1,0,
  0,1,0,
  0,1,0,
  0,1,0,
};
const U08 _U[CHAR_SIZE]= 
{
  1,0,1,
  1,0,1,
  1,0,1,
  1,0,1,
  1,1,1,
};
const U08 _V[CHAR_SIZE]= 
{
  1,0,1,
  1,0,1,
  1,0,1,
  1,0,1,
  0,1,0,
};
const U08 _W[CHAR_SIZE]= 
{
  1,0,1,
  1,0,1,
  1,0,1,
  1,1,1,
  1,0,1,
};
const U08 _X[CHAR_SIZE]= 
{
  1,0,1,
  1,0,1,
  0,1,0,
  1,0,1,
  1,0,1,
};
const U08 _Y[CHAR_SIZE]= 
{
  1,0,1,
  1,0,1,
  0,1,0,
  0,1,0,
  0,1,0,
};
const U08 _Z[CHAR_SIZE]= 
{
  1,1,1,
  0,0,1,
  0,1,0,
  1,0,0,
  1,1,1,
};

const U08 _Exclamation[CHAR_SIZE] = 
{
  0,1,0,
  0,1,0,
  0,1,0,
  0,0,0,
  0,1,0, 
};

const U08 _Dot[CHAR_SIZE] = 
{
  0,0,0,
  0,0,0,
  0,0,0,
  0,0,0,
  0,1,0,
};

const U08 _Colon[CHAR_SIZE] = 
{
  0,0,0,
  0,1,0,
  0,0,0,
  0,1,0,
  0,0,0,
};

const U08 _SPACE[CHAR_SIZE] = 
{
  0,0,0,
  0,0,0,
  0,0,0,
  0,0,0,
  0,0,0,
};

const U08 * Fonts[] = 
{
  _SPACE,
  _Exclamation,
  _NULL,
  _NULL,
  _NULL,
  _NULL,
  _NULL,
  _NULL,
  _NULL,
  _NULL,
  _NULL,
  _NULL,
  _NULL,
  _NULL,
  _Dot,
  _NULL,
  (U08 *)_0,
  (U08 *)_1,
  (U08 *)_2,
  (U08 *)_3,
  (U08 *)_4,
  (U08 *)_5,
  (U08 *)_6,
  (U08 *)_7,
  (U08 *)_8,
  (U08 *)_9,
  (U08 *)_Colon,
  _NULL,
  _NULL,
  _NULL,
  _NULL,
  _NULL,
  _NULL, 
  (U08 *)_A,
  (U08 *)_B,
  (U08 *)_C,
  (U08 *)_D,
  (U08 *)_E,
  (U08 *)_F,
  (U08 *)_G,
  (U08 *)_H,
  (U08 *)_I,
  (U08 *)_J,
  (U08 *)_K,
  (U08 *)_L,
  (U08 *)_M,
  (U08 *)_N,
  (U08 *)_O,
  (U08 *)_P,
  (U08 *)_Q,
  (U08 *)_R,
  (U08 *)_S,
  (U08 *)_T,
  (U08 *)_U,
  (U08 *)_V,
  (U08 *)_W,
  (U08 *)_X,
  (U08 *)_Y,
  (U08 *)_Z,
  _NULL,
  _NULL,
  _NULL,
  _NULL,
  _NULL,
  _NULL,
  _NULL,
  _NULL,
  _NULL,
  _NULL,
  _NULL,
  _NULL,
  _NULL,
  _NULL,
  _NULL,
  _NULL,
  _NULL,
  _NULL,
  _NULL,
  _NULL,
  _NULL,
  _NULL,
  _NULL,
  _NULL,
  _NULL,
  _NULL,
  _NULL,
  _NULL,
  _NULL,
  _NULL,
  _NULL,
  _NULL,
  _NULL,
  _NULL,
  _NULL,
  _NULL,
  _NULL
};
