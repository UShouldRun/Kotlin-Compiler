fun main(): Int {
  var hello_word: String = "Hello World";
  var cond1: Boolean = false;
  var cond2: Boolean = true;
  var cond3: Boolean = false;

  when (2 + 3) {
    4 -> {
      if (cond2 && (!cond1 || cond3)) {
        println(hello_word, null);
      } else {
        println("Bye World", null);
      }
    }
    5 -> {
      while (!cond1 && cond2) {
        println("Anybody Home???", null);
        cond1 = !cond2 || cond3;
      }
    }
  }

  return 0;
}
