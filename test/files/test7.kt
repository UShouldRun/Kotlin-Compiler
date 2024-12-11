fun factorial(n: Int): Int {
  var result: Int = 1;
  for (var i: Int = 1; i <= n; i++) {
    result *= i;
  }
  return result;
}

fun main() {
  var n: Int = readln_int();
  println_int(factorial(n));
}
