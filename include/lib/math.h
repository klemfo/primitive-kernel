int math_binary_log(uint64_t in)
{
  if(!in) return -1;
  int i = 0;
  for(; in != 1; i++) {
    i >>= 1;
  }
  return i;
}
