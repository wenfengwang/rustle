
## 不正なJSON型の使用

### 設定

* 検出器ID: `incorrect-json-type`
* 重大度: 高

### 説明

パブリックインターフェース（`#[near_bindgen]`構造体内の`#[private]`マクロを持たないパブリック関数）のパラメーターや戻り値に`i64`、`i128`、`u64`、`u128`の型を使用しないでください。

これは、JSONがサポートできる最大の整数が2\^53-1であるためです。

詳細は[こちら](https://2ality.com/2012/04/number-encoding.html)をご覧ください。

開発者には、Near SDKの`I64`、`I128`、`U64`、`U128`型が推奨されます。

### サンプルコード

```rust
// https://github.com/ref-finance/ref-contracts/blob/c580d8742d80033a630a393180163ab70f9f3c94/ref-exchange/src/views.rs#L15
pub struct ContractMetadata {
    pub version: String,
    pub owner: AccountId,
    pub guardians: Vec<AccountId>,
    pub pool_count: u64,  // `U64`を使用すべきです
    pub state: RunningState,
    pub exchange_fee: u32,
    pub referral_fee: u32,
}

// https://github.com/ref-finance/ref-contracts/blob/c580d8742d80033a630a393180163ab70f9f3c94/ref-exchange/src/views.rs#L171
#[near_bindgen]
impl Contract {
    pub fn metadata(&self) -> ContractMetadata {  // 戻り値の型に`u64`が含まれています
        // ...
    }
}
```

このサンプルでは、`metadata`関数が戻り値として`ContractMetadata`構造体を使用しており、その中に`pool_count: u64`が含まれています。パブリック関数の戻り値はJSONを介してフロントエンドに送信されるため、`pool_count`の値が2\^53-1を超える可能性があります。そのため、Near SDKの文字列型`U64`を使用すべきです。
