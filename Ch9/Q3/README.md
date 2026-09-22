```diff 
// Parser.java
...
+ private int loopDepth = 0;
...
  private Stmt statement() {
    ...
+   if (match(BREAK)) return breakStatement();

    return expressionStatement();
  }

  private Stmt forStatement() {
    ...
+   try {
+     loopDepth++;
      ... existing code
        
+   } finally {
+     loopDepth--;
+   }
  }

    private Stmt whileStatement() {
    ...
+   try {
+     loopDepth++;
      ... existing code
        
+   } finally {
+     loopDepth--;
+   }
  }

+   private Stmt breakStatement() {
+   if (loopDepth == 0) {
+     error(previous(), "Expect 'break' to be inside a loop.");
+   }
+   consume(SEMICOLON, "Expect ';' after 'break'.");
+   return new Stmt.Break();
+ }
```

```diff
// Interpreter

+ private static class BreakException extends RuntimeException {}

+ @Override
+ public Void visitBreakStmt(Stmt.Break stmt) {
+   throw new BreakException();
+ }

  @Override
  public Void visitWhileStmt(Stmt.While stmt) {
+   try {
        while (isTruthy(evaluate(stmt.condition))) {
          execute(stmt.body);
+       }
+     } catch (BreakException ex) {
+   }
    return null;
  }
```