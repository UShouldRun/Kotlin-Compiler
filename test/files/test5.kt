fun fibo(n: Int): Int {
  if (n == 0 || n == 1) {
    return n;
  }
  return fibo(n - 1) + fibo(n - 2);
}

fun main() {
  println_int(fibo(readln_int()));
  return;
}
