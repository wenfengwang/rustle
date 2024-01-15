
## ストレージ料金のチェックを行わずにストレージ登録の解除を試みる問題

### Configuration

* detector id: `unclaimed-storage-fee`
* severity: low

### Description

[NEP-145](https://github.com/near/NEPs/blob/master/neps/nep-0145.md#5-account-gracefully-closes-registration)によれば、アカウントの所有者がアカウントを閉じようとする際には、`force`フラグが設定されていない限り、残高がゼロの状態でストレージの登録を解除する必要があります。従って、NEP-145の実装はこの規則に従うべきです。

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
        log!("The account {} is not registered", &account_id);
    }
    false
}
```

このコードは`balance`をチェックせずに`accounts`からアカウントを削除します。正しいバージョンは以下の通りです：

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
                "Can't unregister the account with the positive balance without force",
            )
        }
    } else {
        log!("The account {} is not registered", &account_id);
        false
    }
}
```
