```diff
// Interpreter.java

case SLASH:
    checkNumberOperands(expr.operator, left, right);

+   if ((double)right != 0) {
+       return (double)left / (double)right;
+   }

-   return (double)left / (double)right;
+   throw new RuntimeError(expr.operator, 
+         "Cannot divide by 0.");
```

        