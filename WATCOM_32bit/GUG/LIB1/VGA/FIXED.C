////////////////////////////////////////////////////////////////////////////
// fixed point stuff

#define SHIFT    8
#define MULTI  256

int GUGFPAssignInt(int i)
{
  return((int)(i << SHIFT));
}

int GUGFPAssignFloat(float f)
{
  return((int)(f * MULTI));
}

int GUGFPMul(int i1, int i2)
{
  return((int)((i1 * i2) >> SHIFT));
}

int GUGFPAdd(int i1, int i2)
{
  return((int)i1+i2);
}

int GUGFPDiv(int i1, int i2)
{
  return((int)((i1 << SHIFT) / i2));
}

int GUGFPGetInt(int i)
{
  return((int)(i >> SHIFT));
}

float GUGFPGetFloat(int i)
{
  return((float)((float)i / (float)MULTI));
}
