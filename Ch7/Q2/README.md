```diff
// Interpreter.java

case PLUS:
  if (left instanceof Double && right instanceof Double) {
    return (double)left + (double)right;
  } 
  
- if (left instanceof String && right instanceof String) {
+ if (left instanceof String || right instanceof String) {
+   return stringify(left) + stringify(right);
  }

  throw new RuntimeError(expr.operator,
-     "Operands must be two numbers or two strings.");
+     "Operands must be two numbers or include at least one string.");
```