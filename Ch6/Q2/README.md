The following changes have been made to the following files:

This adds our new grammar rule
```diff
// Parser.java

private Expr comma() {
-    Expr expr = equality();
+    Expr expr = conditional();

    while(match(COMMA)){
      Token operator = previous();
-      Expr right = equality();
+      Expr right = conditional();
      expr = new Expr.Binary(expr, operator, right);
    }

    return expr;
  }

+ private Expr conditional() {
+   Expr expr = equality();
+
+   if (match(QUESTION)) {
+     Expr thenBranch = expression();
+     consume(COLON,
+         "Expect ':' after `if_true` expression");
+     Expr elseBranch = conditional();
+     expr = new Expr.Conditional(expr, if_true, if_false);
+   }
+
+   return expr;
+ }
```

This was executed to generate a new Expr.java file
```diff
// GenerateAst.java

    defineAst(outputDir, "Expr", Arrays.asList(
      "Binary   : Expr left, Token operator, Expr right",
      "Grouping : Expr expression",
      "Literal  : Object value",
      "Unary    : Token operator, Expr right",
+     "Conditional : Expr conditional, Expr if_true, Expr if_false"
    ));
```

New the new tokens for the ternaty operator are added here
```diff
// Scanner.java
private void scanToken() {
    char c = advance();
    switch (c) {
      ...
+     case '?': addToken(QUESTION); break;
+     case ':': addToken(COLON); break;
      ...
    }
} 
```
```diff
// TokenType.java
enum TokenType {
  // Single-character tokens.
  ...
+ QUESTION, COLON,
  ...
}
```

Lastly, AstPrinter.java and RPNPrinter.java have been updated to implement the visitConditionalExpr method.
```diff
// AstPrinter.java
+ @Override 
+ public String visitConditionalExpr(Expr.Conditional expr) {
+   return parenthesize("conditional", expr.conditional, expr.if_true, expr.if_false);
+ }
```
```diff
// RPNPrinter.java
+ @Override 
+ public String visitConditionalExpr(Expr.Conditional expr) {
+   return "(" + expr.conditional.accept(this) + " " + expr.if_true.accept(this) + " " + expr.if_false.accept(this) + ") ?:";
+ }
```

