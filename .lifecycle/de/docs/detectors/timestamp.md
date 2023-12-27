
## Abhängigkeit vom Timestamp

### Konfiguration

* Detektor-ID: `timestamp`
* Schweregrad: info

### Beschreibung

Eine Abhängigkeit vom Timestamp kann zu Ausnutzung führen, da sie von Minern manipuliert werden könnte. Zum Beispiel könnte in einem Lotterievertrag der Jackpot unter Verwendung des Timestamps generiert werden. In diesem Fall könnte der Miner in der Lage sein, den Timestamp zu manipulieren, um den Jackpot zu gewinnen.

**Rustle** bietet diesen Detektor an, um Benutzern zu helfen, inkorrekte Verwendungen des Timestamps zu finden, indem alle Verwendungen von `timestamp` aufgespürt werden.

### Beispielcode

Hier ist ein Beispiel für einen Lotterievertrag. Der Gewinner wird unter Verwendung des Timestamps ermittelt, was bedeutet, dass das Ergebnis von denen manipuliert werden kann, die den Timestamp kontrollieren können.

```rust
impl Lottery{
    fn get_winner(&self) -> u32 {
        let current_time = env::block_timestamp();
        let winner_id = self.generate_winner(&current_time);

        winner_id
    }
}
```
