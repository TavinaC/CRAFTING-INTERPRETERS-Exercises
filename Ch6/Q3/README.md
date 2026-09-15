The following has been added to implement the grammar rules:

```diff
// Parser.java

  private Expr primary() {
    ...

+   if(match(COMMA)) {
+     error(previous(), "Missing left-hand operand.");
+     comma();
+     return null;
+   }

+   if (match(BANG_EQUAL, EQUAL_EQUAL)) {
+     error(previous(), "Missing left-hand operand.");
+     equality();
+     return null;
+   }

+   if (match(GREATER, GREATER_EQUAL, LESS, LESS_EQUAL)) {
+     error(previous(), "Missing left-hand operand.");
+     comparison();
+     return null;
+   }

+   if (match(PLUS)) {
+     error(previous(), "Missing left-hand operand.");
+     term();
+     return null;
+   }

+   if (match(SLASH, STAR)) {
+     error(previous(), "Missing left-hand operand.");
+     factor();
+     return null;
+   }

    throw error(peek(), "Expect expression.");
  }
```