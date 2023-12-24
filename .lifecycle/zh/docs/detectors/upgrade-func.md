## 缺乏升级功能

### 配置

* 检测器 ID: `upgrade-func`
* 严重程度: 低

### 描述

合约可能需要升级功能，**Rustle** 将检查合约中是否存在这样的接口。

没有升级功能，合约无法升级，合约状态也无法迁移。

### 示例代码

以下是升级功能的示例。

```rust
// https://github.com/NearDeFi/burrowland/blob/687d72ab6c158b3160dc31d6840471a687eff9d5/contract/src/upgrade.rs#L46
mod upgrade {
    use near_sdk::{require, Gas};

    use super::*;
    use near_sys as sys;

    const GAS_TO_COMPLETE_UPGRADE_CALL: Gas = Gas(Gas::ONE_TERA.0 * 10);
    const GAS_FOR_GET_CONFIG_CALL: Gas = Gas(Gas::ONE_TERA.0 * 5);
    const MIN_GAS_FOR_MIGRATE_STATE_CALL: Gas = Gas(Gas::ONE_TERA.0 * 10);

    /// 自升级并调用迁移，通过不将代码加载到内存中来优化 gas。
    /// 以代码的非序列化字节集作为输入。
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
            // 完成此调用所需的 gas。
            let required_gas =
                env::used_gas() + GAS_TO_COMPLETE_UPGRADE_CALL + GAS_FOR_GET_CONFIG_CALL;
            require!(
                env::prepaid_gas() >= required_gas + MIN_GAS_FOR_MIGRATE_STATE_CALL,
                "没有足够的 gas 完成状态迁移"
            );
            let migrate_state_attached_gas = env::prepaid_gas() - required_gas;
            // 调度状态迁移。
            sys::promise_batch_action_function_call(
                promise_id,
                migrate_method_name.len() as _,
                migrate_method_name.as_ptr() as _,
                empty_args.len() as _,
                empty_args.as_ptr() as _,
                0 as _,
                migrate_state_attached_gas.0,
            );
            // 调度在迁移完成后返回配置。
            //
            // 升级方法将其作为一个动作附加，因此如果配置视图调用无法成功返回，则整个升级，包括部署
            // 合同操作和迁移，都可以回滚。视图调用对状态进行反序列化，并反序列化包含 owner_id 的配置。
            // 如果合同可以对当前配置进行反序列化，则可以验证所有者并重新执行升级（以防先前的升级/迁移出现问题）。
            //
            // 这是远程合同升级的额外安全保障。
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
