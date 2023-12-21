
## コレクション内の重複するidの使用

### 設定

* detector id: `dup-collection-id`
* 重大度: medium

### 説明

NEAR SDKのコレクションは、`new`関数を使用して初期化されます。

```rust
pub fn new<S>(prefix: S) -> Self
where
    S: IntoStorageKey,
```

引数`prefix`はコレクションの識別子です。各コレクションは、他のコレクションのidと異なるidを持つべきです。

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
            users: UnorderedSet::new(StorageKey::Orders), // ここでは`StorageKey::Users`を使用すべきです
        }
    }
}
```

このサンプルでは、`orders`と`users`が同じidを共有しており、予期しない動作を引き起こす可能性があります。
