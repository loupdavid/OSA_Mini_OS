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
  // Change proc to SVC (Supervisor) Mode
  __asm("cps #19");
  int test = 1;
  test = test+1;
  // Change proc to User Mode
  __asm("cps #16");
  test = 5;
  // Change proc to SVC (Supervisor) Mode
  __asm("cps #19");
  test = 6;

  int radius = 5;
  //Cp radius to r2
  __asm("mov r2, %0" : : "r"(radius));
  //Cp r3 to radius
  __asm("mov %0, r3" : "=r"(radius));
  int volume;
  dummy();
  volume = compute_volume(radius);
  return
    volume;
}
