
## Absence de fonction de mise à niveau

### Configuration

* identifiant du détecteur : `upgrade-func`
* gravité : faible

### Description

Les contrats peuvent nécessiter la fonction de mise à niveau, **Rustle** vérifiera si une telle interface existe dans le contrat.

Sans fonction de mise à niveau, le contrat ne peut pas être mis à niveau et les états du contrat ne peuvent pas être migrés.

### Exemple de code

Voici un exemple de fonction de mise à niveau.

```rust
// https://github.com/NearDeFi/burrowland/blob/687d72ab6c158b3160dc31d6840471a687eff9d5/contract/src/upgrade.rs#L46
mod upgrade {
    use near_sdk::{require, Gas};

    use super::*;
    use near_sys as sys;

    const GAS_TO_COMPLETE_UPGRADE_CALL: Gas = Gas(Gas::ONE_TERA.0 * 10);
    const GAS_FOR_GET_CONFIG_CALL: Gas = Gas(Gas::ONE_TERA.0 * 5);
    const MIN_GAS_FOR_MIGRATE_STATE_CALL: Gas = Gas(Gas::ONE_TERA.0 * 10);

    /// Auto-mise à niveau et appel à migrate, optimise le gas en ne chargeant pas le code en mémoire.
    /// Prend en entrée un ensemble de bytes non sérialisés du code.
    #[no_mangle]
    pub extern "C" fn upgrade() {
        env::setup_panic_hook();
        let contract: Contract = env::state_read().expect("ERR_CONTRACT_IS_NOT_INITIALIZED");
        contract.assert_owner();
        let current_account_id = env::current_account_id().as_bytes().to_vec();
        let migrate_method_name = b"migrate_state".to_vec();
        let get_config_method_name = b"get_config".to_vec();
        let empty_args = b"{}".to_vec();
        unsafe {
            sys::input(0);
            let promise_id = sys::promise_batch_create(
                current_account_id.len() as _,
                current_account_id.as_ptr() as _,
            );
            sys::promise_batch_action_deploy_contract(promise_id, u64::MAX as _, 0);
            // Gaz requis pour compléter cet appel.
            let required_gas =
                env::used_gas() + GAS_TO_COMPLETE_UPGRADE_CALL + GAS_FOR_GET_CONFIG_CALL;
            require!(
                env::prepaid_gas() >= required_gas + MIN_GAS_FOR_MIGRATE_STATE_CALL,
                "Pas assez de gaz pour compléter la migration d'état"
            );
            let migrate_state_attached_gas = env::prepaid_gas() - required_gas;
            // Planification de la migration d'état.
            sys::promise_batch_action_function_call(
                promise_id,
                migrate_method_name.len() as _,
                migrate_method_name.as_ptr() as _,
                empty_args.len() as _,
                empty_args.as_ptr() as _,
                0 as _,
                migrate_state_attached_gas.0,
            );
            // Planification du retour de la configuration après que la migration soit terminée.
            //
            // La méthode de mise à niveau l'attache comme une action, donc toute la mise à niveau incluant le déploiement
            // du contrat et la migration peut être annulée si l'appel de visualisation de la configuration ne peut pas être
            // retourné avec succès. L'appel de visualisation désérialise l'état et désérialise la
            // configuration qui contient l'owner_id. Si le contrat peut désérialiser la configuration actuelle,
            // alors il peut valider le propriétaire et exécuter la mise à niveau à nouveau (au cas où la précédente
            // mise à niveau/migration se serait mal passée).
            //
            // C'est une protection supplémentaire pour les mises à niveau de contrats à distance.
            sys::promise_batch_action_function_call(
                promise_id,
                get_config_method_name.len() as _,
                get_config_method_name.as_ptr() as _,
                empty_args.len() as _,
                empty_args.as_ptr() as _,
                0 as _,
                GAS_FOR_GET_CONFIG_CALL.0,
            );
            sys::promise_return(promise_id);
        }
    }
}

```
