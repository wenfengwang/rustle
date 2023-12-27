
## Le transfert NEP-141 ne panique pas sur les comptes destinataires non enregistrés

### Configuration

* identifiant du détecteur : `unregistered-receiver`
* gravité : moyenne

### Description

Selon l'[implémentation](https://github.com/near/near-sdk-rs/blob/63ba6ecc9439ec1c319c1094d581653698229473/near-contract-standards/src/fungible_token/core_impl.rs#L58) de [NEP-141](https://github.com/near/NEPs/blob/master/neps/nep-0141.md), un destinataire de transfert qui n'a pas été enregistré devrait entraîner une panique.

Les développeurs peuvent tenter d'enregistrer un nouveau compte pour le destinataire sans demander les frais de stockage, ce qui pourrait conduire à un DoS. Une implémentation possible de l'enregistrement de compte se trouve dans [storage_impl.rs](https://github.com/near/near-sdk-rs/blob/1859ce4c201d2a85fbe921fdada1df59b00d2d8c/near-contract-standards/src/fungible_token/storage_impl.rs#L45)

### Exemple de code

Le segment de code ci-dessous montre deux méthodes pour dévoiler le solde d'un compte (c'est-à-dire le destinataire). La méthode sûre provoquera une panique si le compte n'est pas enregistré, tandis que la méthode non sûre retournera un solde par défaut de 0 sans panique. Dans le cas non sûr, une nouvelle clé avec `AccountId == account_id` sera insérée dans la map `accounts`, dont les frais de stockage sont payés par le sponsor du `Contract`.

Pour le code complet, veuillez consulter [examples/unregistered-receiver](/examples/unregistered-receiver).

```rust
#[near_bindgen]
#[derive(BorshDeserialize, BorshSerialize)]
pub struct Contract {
    accounts: UnorderedMap<AccountId, Balance>,
    total_supply: Balance,
}

impl Contract {
    pub fn internal_unwrap_balance_safe(&self, account_id: &AccountId) -> Balance {
        self.accounts
            .get(account_id)
            .unwrap_or_else(|| env::panic_str("Account is not registered"))
    }
    pub fn internal_unwrap_balance_unsafe(&self, account_id: &AccountId) -> Balance {
        self.accounts.get(account_id).unwrap_or(0)
    }
}
```
