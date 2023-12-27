
## Valeurs de retour non utilisées de fonction non-void

### Configuration

* identifiant du détecteur : `unused-ret`
* gravité : faible

### Description

La valeur de retour des fonctions devrait être utilisée. Autrement, certaines informations pourraient être perdues ou non vérifiées.

### Exemple de code

```rust
// https://github.com/ref-finance/ref-contracts/blob/117b044280053661fda217057560c8e35111856f/ref-exchange/src/lib.rs#L98
#[near_bindgen]
#[derive(BorshSerialize, BorshDeserialize, PanicOnDefault)]
pub struct Contract {
    // ...
    guardians: UnorderedSet<AccountId>,
    // ...
}

// https://github.com/ref-finance/ref-contracts/blob/536a60c842e018a535b478c874c747bde82390dd/ref-exchange/src/owner.rs#L65
#[near_bindgen]
impl Contract {
    #[payable]
    pub fn remove_guardians(&mut self, guardians: Vec<ValidAccountId>) {
        assert_one_yocto();
        self.assert_owner();
        for guardian in guardians {
            // pub fn remove(&mut self, element: &T) -> bool
            // Enlève une valeur de l'ensemble. Renvoie si la valeur était présente dans l'ensemble.
            self.guardians.remove(guardian.as_ref());
        }
    }
}
```

Dans cet exemple, le contrat ne vérifie pas la valeur de retour de `remove` pour s'assurer que le `guardian` existe dans `self.guardians`. Si le `guardian` n'existe pas, le programme ne se terminera pas de manière inattendue, ce qui pourrait entraîner un impact imprévu.

Une version corrigée possible est la suivante :

```rust
#[payable]
pub fn remove_guardians(&mut self, guardians: Vec<ValidAccountId>) -> Vec<ValidAccountId> {
    assert_one_yocto();
    self.assert_owner();
    let mut guardians_left = vec![];
    for guardian in guardians {
        if !self.guardians.remove(guardian.as_ref()) {
            guardians_left.push(guardian);
        }
    }
    guardians_left
}
```

Dans cette version, `remove_guardians` retournera un vecteur de tous les `guardians` qui ne sont pas présents dans `self.guardians`.
