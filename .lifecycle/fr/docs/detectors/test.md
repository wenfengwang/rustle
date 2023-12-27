
## Logique complexe à l'intérieur d'une boucle

### Configuration

* identifiant du détecteur : `complex-loop`
* gravité : info

### Description

Trouvez les boucles contenant une logique complexe, qui peuvent entraîner des problèmes de DoS.

Il est recommandé de limiter le nombre d'itérations pour éviter le problème de DoS.

### Exemple de code

```rust
impl User {
    pub fn complex_calc(&mut self) {
        // ...
    }
}

#[near_bindgen]
impl Contract {
    pub fn register_users(&mut self, user: User) {
        self.users.push(user);
    }

    pub fn update_all_users(&mut self) {
        for user in self.users.iter_mut() {
            user.complex_calc();
        }
    }
}
```

Dans cet exemple, les utilisateurs peuvent être enregistrés sans aucun frais de stockage, donc la liste `users` peut avoir une longueur (`len()`) très importante.

Supposons que la fonction `complex_calc` contienne de nombreux calculs complexes et puisse consommer beaucoup de gas.
