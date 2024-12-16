fun mod(a: Int, b: Int): Int {
  var result: Int = a;
  while (result >= b) {
    result -= b;
  }
  while (result < 0) {
    result += b;
  }
  return result;
}

fun gcd(a: Int, b: Int): Int {
  var x: Int = a;
  var y: Int = b;
  while (y != 0) {
    var temp: Int = mod(x, y);
    x = y;
    y = temp;
  }
  return x;
}

fun main() {
  var a: Int = readln_int();
  var b: Int = readln_int();
  if (a >= b) {
    println_int(gcd(2 * a + 3 * b, a + b));
  } else if (2 * a <= b) {
    println_int(gcd(5 * a + 4 * b, 2 * a + b));
  } else {
    println_int(gcd(a, b));
  }
}
