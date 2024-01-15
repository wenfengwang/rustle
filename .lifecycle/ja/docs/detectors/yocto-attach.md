
## 二要素認証の不足

### 設定

* detector id: `yocto-attach`
* 重大度: 中

### 説明

特権関数は、1 yocto NEARが添付されているかどうかを確認する必要があります。これにより、セキュリティ上の懸念からNEARウォレットで2FAが有効になります。

これは、`assert_one_yocto`を追加することでコントラクトに実装でき、すべての特権関数に推奨されます。

注: セマンティック情報がなければ、すべての特権関数を特定するのは困難です。現在、**Rustle**は`predecessor_account_id`が比較に関与しているすべての関数を特権関数とみなしています。

### サンプルコード

```rust
pub(crate) fn assert_owner(&self) {
    assert_eq!(
        env::predecessor_account_id(),
        self.owner_id,
        "{}", ERR100_NOT_ALLOWED
    );
}

// https://github.com/ref-finance/ref-contracts/blob/536a60c842e018a535b478c874c747bde82390dd/ref-exchange/src/owner.rs#L16
#[payable]
pub fn set_owner(&mut self, owner_id: ValidAccountId) {
    assert_one_yocto();
    self.assert_owner();
    self.owner_id = owner_id.as_ref().clone();
}
```

このサンプルでは、`set_owner`は特権関数であり、コントラクトの所有者のみが呼び出すべきです。関数`assert_owner`は`predecessor_account_id`をチェックすることで権限を確認します。この関数はセキュリティ上の懸念から2FAを必要とし、関数内で`assert_one_yocto`を呼び出すことによって実装できます。
