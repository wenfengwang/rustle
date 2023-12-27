
## Dépendance au timestamp

### Configuration

* identifiant du détecteur : `timestamp`
* gravité : info

### Description

La dépendance au timestamp peut conduire à des exploitations puisqu'elle peut être manipulée par les mineurs. Par exemple, dans un contrat de loterie, si le jackpot est généré en utilisant le timestamp, alors les mineurs pourraient trouver un moyen de manipuler le timestamp pour remporter le jackpot.

**Rustle** propose ce détecteur pour aider les utilisateurs à identifier les utilisations incorrectes du timestamp en repérant toutes ses occurrences dans le code.

### Exemple de code

Voici un exemple pour un contrat de loterie. Le gagnant est déterminé en utilisant le timestamp, ce qui signifie que le résultat peut être manipulé par ceux qui ont la capacité de contrôler le timestamp.

```rust
impl Lottery{
    fn get_winner(&self) -> u32 {
        let current_time = env::block_timestamp();
        let winner_id = self.generate_winner(&current_time);

        winner_id
    }
}
```
