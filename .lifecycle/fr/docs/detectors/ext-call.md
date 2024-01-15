
## Appels inter-contrats

### Configuration

* identifiant du détecteur : `ext-call`
* gravité : info

### Description

Trouvez tous les appels inter-contrats.

Nous fournissons ce détecteur pour aider les utilisateurs à localiser rapidement toutes les invocations inter-contrats pour une analyse plus approfondie.

### Exemple de code

```rust
// https://docs.near.org/sdk/rust/cross-contract/callbacks#calculator-example
#[ext_contract(ext_calculator)]
trait Calculator {
    fn sum(&self, a: U128, b: U128) -> U128;
}

#[near_bindgen]
impl Contract {
    pub fn sum_a_b(&mut self, a: U128, b: U128) -> Promise {
        let calculator_account_id: AccountId = "calc.near".parse().unwrap();
        ext_calculator::ext(calculator_account_id).sum(a, b)  // exécute sum(a, b) à distance
    }
}
```

> La macro `#[ext_contract(...)]` convertit un trait Rust en un module avec des méthodes statiques, ce qui permet aux utilisateurs de réaliser des appels inter-contrats. Chacune de ces méthodes statiques prend les arguments positionnels définis par le Trait, puis l'`receiver_id`, le dépôt attaché, et la quantité de gaz et retourne une nouvelle `Promise`.

Dans cet exemple, le contrat peut obtenir la somme de `a` et `b` grâce à l'appel inter-contrats (c'est-à-dire `ext_calculator::ext(calculator_account_id).sum(a, b)`).
