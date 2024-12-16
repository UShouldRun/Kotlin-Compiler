fun fibo(n: Int): Int {
  if (n == 0 || n == 1) {
    return n;
  }
  return fibo(n - 1) + fibo(n - 2);
}

fun main() {
  var n: Int = readln_int();
  var k: Int = fibo(n);
  println_int(k);
}
