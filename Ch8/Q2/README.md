```diff
  @Override
  public Object visitVariableExpr(Expr.Variable expr) {
-   return environment.get(expr.name);
+   Object value = environment.get(expr.name);
+   if (value == null) {
+     throw new RuntimeError(expr.name,
+         "Variable must be initialized.");
+   }
+   return value;
  }
```