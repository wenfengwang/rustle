
## コレクションへの変更は保存されません

### 設定

* detector_id: `unsaved-changes`
* 重大度: 高

### 説明

[NEAR SDK](https://crates.io/crates/near-sdk)は、キーと値のマッピングを保存できるいくつかのマップコレクションを提供しています。`get`を使用してキーによる値を取得し、指定したキーで`insert`を呼び出して値を挿入または上書きすることができます。コレクションはborshを使用してシリアライズとデシリアライズを行いますが、コレクションに変更を加えたい場合は、既存の値を`get`で取得し、変更を加えた後、再度`insert`してコレクションに挿入する必要があります。`insert`関数を使用しないと、変更はコントラクトに保存されません。

注意点として、NEAR SDKの[v4.1.0](https://docs.rs/near-sdk/4.1.0/near_sdk/index.html)以降、開発者は`near_sdk::collections`によって導入されたこの問題を避けるために、変更を自動的に書き戻す[`near_sdk::store`](https://docs.rs/near-sdk/4.1.0/near_sdk/store/index.html)内のマップを使用することができます。

### サンプルコード

```rust
#[allow(unused)]
pub fn modify(&mut self, change: I128) {
    let mut balance = self
        .accounts
        .get(&env::predecessor_account_id())
        .unwrap_or_else(|| env::panic_str("Account is not registered"));

    balance = balance
        .checked_add(change.0)
        .unwrap_or_else(|| env::panic_str("Overflow"));

    // self.accounts
    //     .insert(&env::predecessor_account_id(), &balance);
}
```

このサンプルでは、`balance`は`self.accounts`から取得した、呼び出し元のアカウントIDによってインデックス付けされた値です。コントラクトは`checked_add`を呼び出して`balance`に変更を加えますが、`insert`関数を呼び出さなければ、これらの変更は保存されません。
