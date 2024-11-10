fun main(): Int {
  var hello_word: String = "Hello World";
  var cond1: Boolean = false;
  var cond2: Boolean = true;
  var cond3: Boolean = false;

  when (2 + 3) {
    4 -> {
      if (cond2 && (!cond1 || cond3)) {
        print(hello_word);
      } else {
        print("Bye World");
      }
    }
    5 -> {
      while (!cond1 && cond2) {
        print("Anybody Home???");
        cond1 = !cond2 || cond3;
      }
    }
  }

  return 0;
}
