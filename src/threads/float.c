// Proj 3 implement
int int_to_float(int n) {
  return n * (1 << 14);
}

int float_to_int(int x) {
  return x / (1 << 14);
}

int float_to_int_round(int x) {
  if(x > 0) {
    return (x + (1 << 14) / 2) / (1 << 14);
  }
  else {
    return (x - (1 << 14) / 2) / (1 << 14);
  }
}

int float_add_float(int x, int y) {
  return x + y;
}

int float_sub_float(int x, int y) {
  return x - y;
}

int float_add_int(int x, int n) {
  return x + n * (1 << 14);
}

int float_sub_int(int x, int n) {
  return x - n * (1 << 14);
}

int float_mul_float(int x, int y) {
  return ((int64_t) x) * y / (1 << 14);
}

int float_mul_int(int x, int n) {
  return x * n;
}

int float_div_float(int x, int y) {
  return ((int64_t) x) * (1 << 14) / y;
}

int float_div_int(int x, int n) {
  return x / n;
}