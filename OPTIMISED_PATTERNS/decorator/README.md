# Decorator Pattern

- The decorator pattern is a structural design pattern that
allows behavior to be added to individual objects dynamically
without affecting the behavior of other objects from the same
class.

- At its essence, the decorator pattern involves wrapping an
object with another object that adds or augments behavior.

- Instead of modifying the original object's code, you create
a decorator that:
    - **Implements the same interface** as the original object.
    - **Contains a reference** to the original object.
    - **Intercepts and possibly modifies calls** before delegating
    them to original object.

### Key Characteristics

- **Dynamic Behavior Extension:** decorators add responsabilities
to an object at runtime.

- **Transparent interface:** the client uses the decorator exactly
as it would the original object because both share the same interface.

- **Composable functionality:** multiple decorators can be combined
to build complex behaviors from simple, reusable components.

## Code

