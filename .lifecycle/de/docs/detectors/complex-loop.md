
## Komplexe Logik innerhalb einer Schleife

### Konfiguration

* Detektor-ID: `complex-loop`
* Schweregrad: info

### Beschreibung

Finden Sie Schleifen mit komplexer Logik, die zu DoS-Problemen führen können.

Es wird empfohlen, die Anzahl der Iterationen zu begrenzen, um das DoS-Problem zu vermeiden.

### Beispielcode

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

In diesem Beispiel können Benutzer ohne Speicherentgelt registriert werden, sodass die `users`-Liste eine sehr lange `len()` haben kann.

Nehmen wir an, die Funktion `complex_calc` beinhaltet viele komplexe Berechnungen und kann viel Gas verbrauchen.

In `update_all_users` iteriert eine Schleife über `users` und ruft dabei die Funktion `complex_calc` auf. Dies kann dazu führen, dass das gesamte Gas aufgebraucht wird.

Ein böswilliger Benutzer könnte den Angriff durchführen, indem er massenhaft Benutzer registriert, ohne ein Speicherentgelt zu entrichten.
