fun main() {
  var a: Int = readln_int();
  var b: Int = readln_int();
  if (a >= b) {
    println_int(a + b);
  } else if (a <= 2 * b) {
    println_int(a * b);
  } else {
    println_int(a - b);
  }
}
