
## ストレージ料金の確認が未実施でストレージ登録解除を試みる

### Configuration

* detector id: `unclaimed-storage-fee`
* severity: low

### Description

[NEP-145](https://github.com/near/NEPs/blob/master/neps/nep-0145.md#5-account-gracefully-closes-registration)によると、アカウントの所有者がアカウントを閉じようとする場合、`force`フラグが設定されていない限り、残高がゼロの状態でストレージの登録を解除する必要があります。したがって、NEP-145の実装はこのルールに準拠する必要があります。

### サンプルコード

こちらは`storage_unregister`の誤った例です：

```rust
fn storage_unregister(&mut self, force: Option<bool>) -> bool {
    assert_one_yocto();
    let account_id = env::predecessor_account_id();
    if let Some(balance) = self.accounts.get(&account_id) {
        self.accounts.remove(&account_id);
        self.total_supply -= balance;
        Promise::new(account_id.clone()).transfer(self.storage_balance_bounds().min.0 + 1);
        return true;
    } else {
        log!("アカウント {} は登録されていません", &account_id);
    }
    false
}
```

このコードは`balance`を確認せずに`accounts`からアカウントを削除します。正しいバージョンは以下の通りです：

```rust
fn storage_unregister(&mut self, force: Option<bool>) -> bool {
    assert_one_yocto();
    let account_id = env::predecessor_account_id();
    let force = force.unwrap_or(false);
    if let Some(balance) = self.accounts.get(&account_id) {
        if balance == 0 || force {
            self.accounts.remove(&account_id);
            self.total_supply -= balance;
            Promise::new(account_id.clone()).transfer(self.storage_balance_bounds().min.0 + 1);
            true
        } else {
            env::panic_str(
                "forceフラグなしでプラスの残高を持つアカウントの登録を解除することはできません",
            )
        }
    } else {
        log!("アカウント {} は登録されていません", &account_id);
        false
    }
}
```
