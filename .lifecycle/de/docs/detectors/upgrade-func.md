
## Fehlende Upgrade-Funktion

### Konfiguration

* Detektor-ID: `upgrade-func`
* Schweregrad: niedrig

### Beschreibung

Verträge benötigen möglicherweise die Upgrade-Funktion. **Rustle** wird überprüfen, ob eine solche Schnittstelle im Vertrag vorhanden ist.

Ohne eine Upgrade-Funktion kann der Vertrag nicht aktualisiert und der Vertragszustand nicht migriert werden.

### Beispielcode

Hier ist ein Beispiel für eine Upgrade-Funktion.

```rust
// https://github.com/NearDeFi/burrowland/blob/687d72ab6c158b3160dc31d6840471a687eff9d5/contract/src/upgrade.rs#L46
mod upgrade {
    use near_sdk::{require, Gas};

    use super::*;
    use near_sys as sys;

    const GAS_TO_COMPLETE_UPGRADE_CALL: Gas = Gas(Gas::ONE_TERA.0 * 10);
    const GAS_FOR_GET_CONFIG_CALL: Gas = Gas(Gas::ONE_TERA.0 * 5);
    const MIN_GAS_FOR_MIGRATE_STATE_CALL: Gas = Gas(Gas::ONE_TERA.0 * 10);

    /// Führt ein Selbst-Upgrade durch und ruft migrate auf, optimiert Gas, indem der Code nicht in den Speicher geladen wird.
    /// Nimmt als Eingabe einen nicht serialisierten Satz von Bytes des Codes.
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
            // Benötigtes Gas, um diesen Aufruf abzuschließen.
            let required_gas =
                env::used_gas() + GAS_TO_COMPLETE_UPGRADE_CALL + GAS_FOR_GET_CONFIG_CALL;
            require!(
                env::prepaid_gas() >= required_gas + MIN_GAS_FOR_MIGRATE_STATE_CALL,
                "Nicht genug Gas, um die Zustandsmigration abzuschließen"
            );
            let migrate_state_attached_gas = env::prepaid_gas() - required_gas;
            // Planung der Zustandsmigration.
            sys::promise_batch_action_function_call(
                promise_id,
                migrate_method_name.len() as _,
                migrate_method_name.as_ptr() as _,
                empty_args.len() as _,
                empty_args.as_ptr() as _,
                0 as _,
                migrate_state_attached_gas.0,
            );
            // Planung der Rückgabe der Konfiguration nach Abschluss der Migration.
            //
            // Die Upgrade-Methode fügt sie als Aktion hinzu, sodass das gesamte Upgrade einschließlich der
            // Deploy-Contract-Aktion und der Migration zurückgerollt werden kann, wenn der Konfigurations-View-Aufruf nicht 
            // erfolgreich zurückgegeben werden kann. Der View-Aufruf deserialisiert den Zustand und deserialisiert die
            // Konfiguration, die die owner_id enthält. Wenn der Vertrag die aktuelle Konfiguration deserialisieren kann,
            // dann kann er den Eigentümer validieren und das Upgrade erneut ausführen (falls das vorherige
            // Upgrade/die Migration schlecht verlief).
            //
            // Es ist eine zusätzliche Sicherheitsmaßnahme für die Fern-Vertrags-Upgrades.
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
