fun sumOfFirstN(n: Int): Int {
  var sum: Int = 0;
  var i: Int = 1;
  while (i <= n) {
    sum += i;
    i++;
  }
  return sum;
}

fun main() {
  var n: Int = readln_int();
  println_int(sumOfFirstN(n));
}
