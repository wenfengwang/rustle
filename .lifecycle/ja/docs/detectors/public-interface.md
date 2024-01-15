
## すべてのパブリックインターフェイスを検索

### Configuration

* detector id: `public-interface`
* severity: info

### 説明

パブリックインターフェイスとは、他者が呼び出すことができる関数のことです。具体的には、`#[near_bindgen]` 構造体の `#[private]` マクロがないパブリック関数です。

### サンプルコード

```rust
#[near_bindgen]
impl Contract {
    pub fn withdraw(&mut self, amount: U128) -> Promise {
        unimplemented!()
    }

    pub fn check_balance(&self) -> U128 {
        unimplemented!()
    }

    #[private]
    pub fn callback_withdraw(&mut self, amount: U128) {
        unimplemented!()
    }

    fn sub_balance(&mut self, amount: u128) {
        unimplemented!()
    }
}
```

このサンプルコードでは、4つの関数はすべて `#[near_bindgen]` 構造体 `Contract` のメソッドです。しかし、`withdraw` と `check_balance` のみがパブリックインターフェイスです。`callback_withdraw` は `#[private]` で装飾されたパブリック関数なので、内部関数になります。`sub_balance` は `Contract` のプライベート関数です。
