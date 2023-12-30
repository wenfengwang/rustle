
## コレクションへの変更は保存されません

### 設定

* detector id: `unsaved-changes`
* 重大度: 高

### 説明

[NEAR SDK](https://crates.io/crates/near-sdk)は、キーと値のマッピングを格納できるいくつかのマップコレクションを提供しています。`get`を使用してキーに対応する値を取得し、`insert`を呼び出して特定のキーで値を挿入または上書きすることができます。コレクションはBorshを使用してシリアライズとデシリアライズを行います。コレクションに変更を加えたい場合は、まず`get`で既存の値を取得し、それに変更を加えた後、再び`insert`を使ってコレクションに挿入する必要があります。`insert`関数を使用しないと、変更はコントラクトに保存されません。

注記: NEAR SDKの[v4.1.0](https://docs.rs/near-sdk/4.1.0/near_sdk/index.html)以降、開発者は[`near_sdk::store`](https://docs.rs/near-sdk/4.1.0/near_sdk/store/index.html)内のマップを使用することができ、これにより`near_sdk::collections`によって導入された問題を避けるために変更が自動的に書き戻されます。

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

このサンプルでは、`balance`は`self.accounts`から呼び出し元のアカウントIDによってインデックスされた値であり、コントラクトは`checked_add`を呼び出して変更を加えます。しかし、`insert`関数を呼び出さなければ、変更は保存されません。
