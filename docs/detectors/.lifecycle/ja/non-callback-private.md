
## 非コールバック関数での `#[private]` の不適切な使用

### Configuration

* detector id: `non-callback-private`
* severity: low

### 説明

マクロ `#[private]` は通常、`current_account_id` が `predecessor_account_id` と等しいことを保証するためにコールバック関数で使用されます。非コールバック関数での使用は避けるべきです。そうでない場合、公開関数が内部関数になってしまいます。

### サンプルコード

```rust
#[near_bindgen]
impl Pool {
    #[private]
    pub fn get_tokens(&self) -> &[AccountId] {
        &self.token_account_ids
    }
}
```

`get_tokens` は、プール内の全てのトークンタイプを確認するためのパブリックインターフェース（`#[private]` マクロが装飾されていない公開関数）であるべきです。`#[private]` で装飾すべきではありません。
