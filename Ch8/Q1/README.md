```diff
// Parser.java

+ private boolean parseREPL = false;
+ private boolean isExpression = false;
...

- List<Stmt> parse() {
+ Object parse() {
+  parseREPL = true;
   List<Stmt> statements = new ArrayList<>();
   while (!isAtEnd()) {
     statements.add(declaration());

+    if(isExpression) {
+      Stmt.Expression expressionStatement = (Stmt.Expression) statements.get(statements.size() - 1);

+      return expressionStatement.expression;
+    }

+    parseREPL = false;
   }

    return statements; 
  }

  private Stmt expressionStatement() {
    Expr expr = expression();

+   if (parseREPL && isAtEnd()) {
+     isExpression = true;
+   } else {
      consume(SEMICOLON, "Expect ';' after expression.");
+   }

    return new Stmt.Expression(expr);
  }
```

Readded the lines that were replaced by this chapter
```diff
  void interpret(Expr expression) { 
    try {
      Object value = evaluate(expression);
      System.out.println(stringify(value));
    } catch (RuntimeError error) {
      Lox.runtimeError(error);
    }
  }
```

```diff 
// Lox.java
  private static void run(String source) {
    Scanner scanner = new Scanner(source);
    List<Token> tokens = scanner.scanTokens();

    Parser parser = new Parser(tokens);
-   Expr expression = parser.parse();
+   Object syntax = parser.parse();

    // Stop if there was a syntax error.
    if (hadError) return;

+   if (syntax instanceof Expr expr) {
+     interpreter.interpret(expr);
+   } else if (syntax instanceof List){
+     interpreter.interpret((List<Stmt>)syntax);
+   }
+ }
```