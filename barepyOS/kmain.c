#include <syscall.h>
#include <util.h>
void dummy()
{
  return;
}
int div(int dividend, int divisor)
{
  int result = 0;
  int remainder = dividend;
  while
    (remainder >= divisor) {
      result++;
      remainder -= divisor;
    }
  return
    result;
}
int compute_volume(int rad)
{
  int
    rad3 = rad * rad * rad;
  return
    div(4*355*rad3, 3*113);
}

int __attribute__((naked))naked_compute_volume(int rad)
{
  int
    rad3 = rad * rad * rad;
  return
    div(4*355*rad3, 3*113);
}
int kmain(void)
{
  //On passe en mode user
  __asm("cps 0x10");
  sys_nop();

  int radius = 5;
  int volume;
  dummy();
  volume = compute_volume(radius);
  return
    volume;
}
