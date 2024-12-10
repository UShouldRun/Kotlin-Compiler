fun vector_dot_mul_2d(v1: Int, v2: Int, u1: Int, u2: Int): Int {
  return (v1 * u1 + v2 * u2);
}

fun vector_dot_mul_3d(v1: Int, v2: Int, v3: Int, u1: Int, u2: Int, u3: Int): Int {
  return (v1 * u1 + v2 * u2 + v3 * u3);
}

enum dimension {
  _2D(2), _3D(3)
}

fun main(): Int {
  var dim2D: dimension = _2D;
  var dim3d: dimension = _3D;

  var a: Int = 10;
  var b: Int = 30;
  var c: Int = readln();

  var x: Int = 0;
  for (var count: Int = 0; count < 10; count ++) {
    x += vector_dot_mul_2d(a, b, a * b, b / a) / vector_dot_mul_3d(c, a, b, a - b, a + c, b * c);
    a += x;
    b *= x;
    c += a;
  }

  println("%d", x + a);

  return x - a - b / c;
}
