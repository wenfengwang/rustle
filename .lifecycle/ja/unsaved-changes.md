
## コレクションへの変更は保存されません

### 設定

* detector_id: `unsaved-changes`
* severity: 高

### 説明

[NEAR SDK](https://crates.io/crates/near-sdk)は、キーと値のマッピングを保存できるいくつかのマップコレクションを提供しています。`get`を使用してキーによる値を取得し、`insert`を呼び出して特定のキーで値を挿入または上書きすることができます。コレクションはBorshを使用してシリアライズとデシリアライズを行いますが、コレクションに変更を加えたい場合は、既存の値を`get`で取得し、変更を加えた後、再びコレクションに`insert`する必要があります。`insert`関数を使用しなければ、変更はコントラクトに保存されません。

注記: NEAR SDKの[v4.1.0](https://docs.rs/near-sdk/4.1.0/near_sdk/index.html)以降、開発者は[`near_sdk::store`](https://docs.rs/near-sdk/4.1.0/near_sdk/store/index.html)内のマップを使用することができ、これにより`near_sdk::collections`によって導入されたこの問題を回避し、変更を自動的に書き戻すことができます。

### サンプルコード

```rust
#[allow(unused)]
pub fn modify(&mut self, change: I128) {
    let mut balance = self
        .accounts
        .get(&env::predecessor_account_id())
        .unwrap_or_else(|| env::panic_str("アカウントは登録されていません"));

    balance = balance
        .checked_add(change.0)
        .unwrap_or_else(|| env::panic_str("オーバーフロー"));

    // self.accounts
    //     .insert(&env::predecessor_account_id(), &balance);
}
```

このサンプルでは、`balance`は呼び出し元のアカウントIDによってインデックス付けされた`self.accounts`からの値で、コントラクトは`checked_add`を呼び出してそれに変更を加えます。しかし、`insert`関数を呼び出さなければ、変更は保存されません。
