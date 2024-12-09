fun main(): Int {
  var x: Int = 4;

  {
    var y: Int = 5;
    x += 5;
  }

  return x;
}
