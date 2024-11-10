fun main() {
  var x: Int = 3;
  var y: Int = 5;
  var cond: Boolean = true;

  if (cond) {
    x += y;
  } else {
    y += 2 * x;
  }

  return x;
}
