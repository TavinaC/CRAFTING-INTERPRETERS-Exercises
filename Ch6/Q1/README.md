The following changes was made to line 25-39 in `jlox.lox.Parser.java`:

```diff
   private Expr expression() {
-   return equality();
+   return comma();
  }

+ private Expr comma() {
+   Expr expr = equality();
+
+   while(match(COMMA)){
+     Token operator = previous();
+     Expr right = equality();
+     expr = new Expr.Binary(expr, operator, right);
+   }
+
+   return expr;
+ }
```