
## コレクション内での重複した id の使用

### 設定

* detector id: `dup-collection-id`
* 重大度: medium

### 説明

NEAR SDK のコレクションは、`new` 関数を使用して自身を初期化します。

```rust
pub fn new<S>(prefix: S) -> Self
where
    S: IntoStorageKey,
```

引数 `prefix` はコレクションの識別子です。各コレクションは、他のコレクションの id と異なる id を持つべきです。

### サンプルコード

```rust
#[near_bindgen]
#[derive(BorshDeserialize, BorshSerialize)]
pub struct Contract {
    orders: UnorderedMap<u16, Order>,
    users: UnorderedSet<AccountId>,
}

#[near_bindgen]
impl Contract {
    #[init]
    pub fn new() -> Self {
        Self {
            orders: UnorderedMap::new(StorageKey::Orders),
            users: UnorderedSet::new(StorageKey::Users), // ここでは `StorageKey::Users` を使用すべきです
        }
    }
}
```

この例では、`orders` と `users` が同じ id を共有しており、予期しない動作を引き起こす可能性があります。
