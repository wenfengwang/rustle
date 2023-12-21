
## アップグレード機能の不足

### 設定

* detector id: `upgrade-func`
* 重大度: 低

### 説明

コントラクトにはアップグレード機能が必要になることがあります。**Rustle** はそのようなインターフェースがコントラクト内に存在するかどうかをチェックします。

アップグレード機能がなければ、コントラクトをアップグレードすることができず、コントラクトの状態を移行することもできません。

### サンプルコード

こちらはアップグレード機能のサンプルコードです。

```rust
// https://github.com/NearDeFi/burrowland/blob/687d72ab6c158b3160dc31d6840471a687eff9d5/contract/src/upgrade.rs#L46
mod upgrade {
    use near_sdk::{require, Gas};

    use super::*;
    use near_sys as sys;

    const GAS_TO_COMPLETE_UPGRADE_CALL: Gas = Gas(Gas::ONE_TERA.0 * 10);
    const GAS_FOR_GET_CONFIG_CALL: Gas = Gas(Gas::ONE_TERA.0 * 5);
    const MIN_GAS_FOR_MIGRATE_STATE_CALL: Gas = Gas(Gas::ONE_TERA.0 * 10);

    /// コードをメモリにロードしないことでガスを最適化し、自己アップグレードと移行を呼び出します。
    /// 入力としてシリアライズされていないコードのバイト列を取ります。
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
            // この呼び出しを完了するために必要なガス。
            let required_gas =
                env::used_gas() + GAS_TO_COMPLETE_UPGRADE_CALL + GAS_FOR_GET_CONFIG_CALL;
            require!(
                env::prepaid_gas() >= required_gas + MIN_GAS_FOR_MIGRATE_STATE_CALL,
                "状態移行を完了するのに十分なガスがありません"
            );
            let migrate_state_attached_gas = env::prepaid_gas() - required_gas;
            // 状態移行をスケジュールします。
            sys::promise_batch_action_function_call(
                promise_id,
                migrate_method_name.len() as _,
                migrate_method_name.as_ptr() as _,
                empty_args.len() as _,
                empty_args.as_ptr() as _,
                0 as _,
                migrate_state_attached_gas.0,
            );
            // 移行完了後に設定を返すことをスケジュールします。
            //
            // アップグレードメソッドはそれをアクションとして添付するので、設定ビューの呼び出しが
            // 正常に返されない場合、デプロイ契約アクションと移行を含むアップグレード全体を
            // ロールバックすることができます。ビュー呼び出しは状態をデシリアライズし、
            // owner_idを含む設定をデシリアライズします。契約が現在の設定をデシリアライズできる場合、
            // オーナーを検証し、アップグレードを再度実行することができます（前回の
            // アップグレード/移行がうまくいかなかった場合）。
            //
            // これはリモート契約アップグレードのための追加の安全対策です。
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
